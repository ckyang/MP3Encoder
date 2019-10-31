//
//  factory.h
//  MP3Encoder
//
//  Created by Chung-kaiYang on 10/31/19.
//  Copyright © 2019 Chung-kaiYang. All rights reserved.
//

#ifndef factory_h
#define factory_h

class encoder;

class factory
{
public:
    ~factory();

    static encoder* GetEncoder();

private:
    static encoder* m_encoder;
};

#endif /* factory_h */
