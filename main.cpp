#include <iostream>

#include "factory.h"
#include "encoder.h"

using namespace std;

int main(void) {
    encoder* encoderObject = factory::GetEncoder();
    encoderObject->encode();
    return 0;
}
