//
//  main.cpp
//  MP3Encoder
//
//  Created by Chung-kaiYang on 10/31/19.
//  Copyright © 2019 Chung-kaiYang. All rights reserved.
//

#include <iostream>

#include "factory.h"
#include "encoder.h"

int main(void) {
    encoder* encoderObject = factory::GetEncoder();
    encoderObject->encode();
    return 0;
}
