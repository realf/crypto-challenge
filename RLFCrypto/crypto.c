//
//  crypto.c
//  hextobase64
//
//  Created by Sergey Dunets on 23.04.15.
//  Copyright (c) 2015 Sergey Dunets. All rights reserved.
//

#include "crypto.h"
#include <stdlib.h>
#include <stdio.h>

#pragma mark - Private

int RLFHexDigitCharacterToInt(char hexDigit) {
    if ('0' <= hexDigit && hexDigit <= '9') {
        return hexDigit - '0';
    }
    
    if (hexDigit >= 'A' && hexDigit <= 'Z') {
        return hexDigit - 'A' + 10;
    }
    
    return hexDigit - 'a' + 10;
}

#pragma mark - Public

int RLFHexByteStringToInt(char hexEncodedByte[2]) {
    if (hexEncodedByte == NULL) {
        return -1;
    }
    
    int byte = 0x10 * RLFHexDigitCharacterToInt(hexEncodedByte[0]) + RLFHexDigitCharacterToInt(hexEncodedByte[1]);
    return byte;
}

char *RLFCreateBase64StringFromHexString(char *hexEncodedString, size_t size) {
    if (hexEncodedString == NULL || size % 2 != 0) {
        return NULL;
    }
    
    static const char * const sBase = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    const size_t dataSize = size / 2; // size of raw data in bytes
    const size_t alignedBy3DataSize = (dataSize / 3 + 1) * 3; // size of raw data aligned to the next number that is a multiple of 3
    const size_t resultSize = alignedBy3DataSize * 4 / 3; // size of Base64 encoded string
    char *encodedString = malloc(sizeof(char) * (resultSize + 1));
    
    char *p = hexEncodedString;
    char *endOfString = hexEncodedString + size;
    size_t count = 0;
    int leaps = 0;
    
    while (p < endOfString) {
        uint32_t buffer = 0;
        
        for (int i = 0; i < 3; i++) {
            if (p <= endOfString - 2) {
                uint8_t byte = RLFHexByteStringToInt(p);
                buffer |= byte << (16 - 8 * i);
                p += 2;
            }
            else {
                leaps++;
            }
        }
        
        for (int i = 0; i < 4; i++) {
            size_t index = (buffer >> (18 - 6 * i)) & 0x3F;
            encodedString[i + count] = sBase[index];
        }
        
        count += 4;
    }
    
    encodedString[count] = '\0';
    
    for (size_t i = 1; i <= leaps; i++) {
        encodedString[resultSize - i] = '=';
    }
    
    return encodedString;
}
