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

    bool encode(const std::string& wavPath);

private:
    static std::string m_wavPath;
    static std::vector<std::string> m_wavFiles;
    static std::mutex m_mutexEncode, m_mutexProcess;
    static std::condition_variable m_cvEncode;
    static int m_processed;

    bool dispatchEncodeJobs();
    static void* createEnc(void* arg);
    static bool encodeOneFile(const std::string& wavFile);
    void retrieveWavFiles();
    std::string toLowerCase(const std::string& s);
};

#endif /* encoder_h */
