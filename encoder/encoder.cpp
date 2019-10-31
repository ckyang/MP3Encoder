//
//  encoder.cpp
//  MP3Encoder
//
//  Created by Chung-kaiYang on 10/31/19.
//  Copyright © 2019 Chung-kaiYang. All rights reserved.
//

#include <iostream>
#include <lame/lame.h>
#include <pthread.h>
#include <filesystem>

#include "encoder.h"

#define PCM_SIZE 8192
#define MP3_SIZE 8192
#define SAMPLE_RATE 44100

using namespace std;
namespace fs = std::__fs::filesystem;

encoder::encoder() {

}

encoder::~encoder() {

}

bool encoder::encode(const string& wavPath) {
    vector<string> wavFiles = retrieveWavFiles(wavPath);

    if(wavFiles.empty()) {
        return false;
    }

    bool res = true;

    for(const auto& wavFile : wavFiles) {
        if(!encodeOneFile(wavPath + "/" + wavFile)) {
            res = false;
        }
    }

    return res;
}

bool encoder::encodeOneFile(const string& wavFile) {
    int read, write;
    string mp3File = wavFile.substr(0, wavFile.size() - 3) + "mp3";

    cout << "Starting to encode " << mp3File << "..." << endl;

    FILE *pcm = fopen(wavFile.c_str(), "rb");
    FILE *mp3 = fopen(mp3File.c_str(), "wb");

    short int pcm_buffer[PCM_SIZE * 2];
    unsigned char mp3_buffer[MP3_SIZE];

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, SAMPLE_RATE);
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);

    do{
        read = fread(pcm_buffer, 2 * sizeof(short int), PCM_SIZE, pcm);

        if(read == 0) {
            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        }
        else {
            write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
        }

        fwrite(mp3_buffer, write, 1, mp3);
    }while (read != 0);

    lame_close(lame);
    fclose(mp3);
    fclose(pcm);

    cout << "Encode " << mp3File << " successfully." << endl;

    return true;
}

vector<string> encoder::retrieveWavFiles(const string& wavPath) {
    cout << "Starting to check .wav path " << wavPath << "..." << endl;

    if(!fs::exists(wavPath)) {
        cerr << wavPath << " not existed!" << endl;
        return vector<string>();
    }

    if(fs::perms::none == (fs::status(wavPath).permissions() & fs::perms::owner_write)) {
        cerr << wavPath << " has no write permission!" << endl;
        return vector<string>();
    }

    cout << "Checking .wav path " << wavPath << " successfully." << endl;

    vector<string> res;
    fs::recursive_directory_iterator it(wavPath), endit;

    while(it != endit) {
        if(fs::is_regular_file(*it) && toLowerCase(it->path().extension()) == ".wav") {
            res.push_back(it->path().filename());
        }

        ++it;
    }

    if(res.empty()) {
        cerr << "No .wav file inside " << wavPath << "!" << endl;
    }
 
    return res;
}

string encoder::toLowerCase(const string& s) {
    string res = s;

    for(auto& c : res) {
        if(c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
        }
    }

    return res;
}
