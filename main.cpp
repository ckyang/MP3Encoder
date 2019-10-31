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

using namespace std;

int main(void) {
    cout << "Welcome to the WAV -> MP3 converter!" << endl;
    encoder* encoderObject = factory::GetEncoder();

    if(!encoderObject) {
        cerr << "Cannot initialize encoder object!" << endl;
        return 1;
    }

    while(true) {
        cout << "Please input the .wav files location: (Press Q to quit)" << endl;
        string wavPath;
        cin >> wavPath;

        if(wavPath == "Q" || wavPath == "q") {
            cout << "Bye!" << endl;
            break;
        }

        cout << "Starting to encode .wav files in " << wavPath << "..." << endl;
        encoderObject->encode(wavPath);
        cout << "Encoding .wav files in " << wavPath << " successfully." << endl;
    }

    return 0;
}
