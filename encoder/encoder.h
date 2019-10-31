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

class encoder
{
public:
    encoder();
    ~encoder();

    void encode(const std::string& wavPath);
private:
};

#endif /* encoder_h */
