//
//  encoder.cpp
//  MP3Encoder
//
//  Created by Chung-kaiYang on 10/31/19.
//  Copyright © 2019 Chung-kaiYang. All rights reserved.
//

#include <iostream>
#include <lame/lame.h>
#include <dirent.h>
#include <pthread.h>

#include "encoder.h"

#define PCM_SIZE 8192
#define MP3_SIZE 8192
#define SAMPLE_RATE 44100

using namespace std;

string encoder::m_wavPath = "";
vector<string> encoder::m_wavFiles = vector<string>();
mutex encoder::m_mutexProcess;
mutex encoder::m_mutexEncode;
condition_variable encoder::m_cvEncode;
int encoder::m_processed = 0;

encoder::encoder() {

}

encoder::~encoder() {

}

bool encoder::encode(const string& wavPath) {
    m_wavPath = wavPath;
    retrieveWavFiles();

    if(m_wavFiles.empty()) {
        return false;
    }

    return dispatchEncodeJobs();
}

bool encoder::dispatchEncodeJobs() {
    bool res = true;
    m_processed = 0;

    for(int i = 0; i < m_wavFiles.size(); ++i) {
        pthread_t threadEnc;
        int *arg = (int*)malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&threadEnc, NULL , encoder::createEnc, arg);
    }

    {
        unique_lock<mutex> lk(m_mutexEncode);
        m_cvEncode.wait(lk, []{return m_processed == m_wavFiles.size();});
    }

    return res;
}

void* encoder::createEnc(void* arg) {
    pthread_detach(pthread_self());
    encoder::encodeOneFile(m_wavPath + "/" + m_wavFiles[*((int*)arg)]);
    free(arg);

    {
        lock_guard<mutex> lk(m_mutexProcess);
        ++m_processed;
    }

    m_cvEncode.notify_all();
    pthread_exit(0);
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

void encoder::retrieveWavFiles() {
    m_wavFiles.clear();
    cout << "Starting to check .wav path " << m_wavPath << "..." << endl;

    DIR *d = opendir(m_wavPath.c_str());

    if(!d) {
        cerr << "Cannot open " << m_wavPath << endl;
        return;
    }

    cout << "Checking .wav path " << m_wavPath << " successfully." << endl;

    struct dirent *dir;

    while((dir = readdir(d)) != NULL) {
        string fileName = dir->d_name;

        if(fileName.size() > 4 && toLowerCase(fileName.substr((int)fileName.size() - 4)) == ".wav") {
            m_wavFiles.emplace_back(fileName);
        }
    }

    closedir(d);

    if(m_wavFiles.empty()) {
        cerr << "No .wav file inside " << m_wavPath << "!" << endl;
    }
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
