//
//  factory.cpp
//  MP3Encoder
//
//  Created by Chung-kaiYang on 10/31/19.
//  Copyright © 2019 Chung-kaiYang. All rights reserved.
//

#include "factory.h"
#include "encoder.h"

using namespace std;

encoder* factory::m_encoder = nullptr;

encoder* factory::GetEncoder() {
    if(!m_encoder) {
        m_encoder = new encoder();
    }
    
    return m_encoder;
}

factory::~factory(void) {
    if(m_encoder) {
        delete m_encoder;
        m_encoder = nullptr;
    }
}
