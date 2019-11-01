//
//  encoder.h
//  MP3Encoder
//
//  Created by Chung-kaiYang on 10/31/19.
//  Copyright © 2019 Chung-kaiYang. All rights reserved.
//

#ifndef encoder_h
#define encoder_h

#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>

class encoder
{
public:
    encoder();
    ~encoder();

    // The encoding function that would be called outside.
    // This function will do following:
    // 1. Check the integrity of given wavPath
    // 2. Retrieve all xxx.wav (case-ignored, i.e., .WAV/.Wav/.waV... also accepted) files from given wavPath
    // 3. Parse all xxx.wav files and encode to xxx.mp3 files
    bool encode(const std::string& wavPath);

private:
    static std::string m_wavPath;
    static std::vector<std::string> m_wavFiles;
    static std::mutex m_mutexEncode, m_mutexProcess;
    static std::condition_variable m_cvEncode;
    static int m_processed;

    // Dispatch each encoding job to separated threads
    bool dispatchEncodeJobs();

    // The thread creation funciton, creating a new thread for encoding job
    static void* createEnc(void* arg);

    // Encode a new xxx.mp3 file, from given xxx.wav file, using LAME library (thread-safe)
    static bool encodeOneFile(const std::string& wavFile);

    // For given wavPath (stored in m_wavPath), check its integrity
    // Then, retrive all xxx.wav files from m_wavPath and store into m_wavFiles
    void retrieveWavFiles();

    // Convert given string to lower case (For non-capical letter, do nothing and preserve it)
    std::string toLowerCase(const std::string& s);
};

#endif /* encoder_h */
