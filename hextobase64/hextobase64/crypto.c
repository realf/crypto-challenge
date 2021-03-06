//
//  crypto.c
//  hextobase64
//
//  Created by Sergey Dunets on 23.04.15.
//  Copyright (c) 2015 Sergey Dunets. All rights reserved.
//

#include "crypto.h"
#include <stdlib.h>

int FromHexToDecimal(char hex) {
    if ('0' <= hex && hex <= '9') {
        return hex - '0';
    }
    
    if (hex >= 'A' && hex <= 'Z') {
        return hex - 'A' + 10;
    }
    
    return hex - 'a' + 10;
}

char *CreateBase64StringFromHexString(char *hexString, size_t hexSize) {
    if (hexString == NULL || hexSize % 2 != 0) {
        return NULL;
    }
    
    static const char * const sBase = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    const size_t dataSize = hexSize / 2; // size of raw data in bytes
    const size_t alignedBy3DataSize = (dataSize / 3 + 1) * 3; // size of raw data aligned to the next number that is a multiple of 3
    const size_t resultSize = alignedBy3DataSize * 4 / 3; // size of Base64 encoded string
    char *encodedString = malloc(sizeof(char) * (resultSize + 1));
    
    char *p = hexString;
    char *endOfString = hexString + hexSize;
    size_t count = 0;
    int leaps = 0;
    
    while (p < endOfString) {
        uint32_t buffer = 0;
        
        for (int i = 0; i < 3; i++) {
            if (p <= endOfString - 2) {
                uint8_t byte = 16 * FromHexToDecimal(*p++) + FromHexToDecimal(*p++);
                buffer |= byte << (16 - 8 * i);
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
