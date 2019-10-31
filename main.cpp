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
        cout << endl << "Please input the .wav files location: (Press Q to quit)" << endl;
        string wavPath;
        cin >> wavPath;

        if(wavPath == "Q" || wavPath == "q") {
            cout << "Bye!" << endl;
            break;
        }

        if(encoderObject->encode(wavPath)) {
            cout << "Encoding all .wav files in " << wavPath << " successfully." << endl;
        }
        else {
            cerr << "Failed to encode .wav files in " << wavPath << "!" << endl;
        }
    }

    return 0;
}
