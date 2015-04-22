//
//  main.c
//  hextobase64
//
//  Created by Sergey Dunets on 22.04.15.
//  Copyright (c) 2015 Sergey Dunets. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int FromHexToDecimal(char hex) {
    if ('0' <= hex && hex <= '9') {
        return hex - '0';
    }
    
    if (hex >= 'A' && hex <= 'Z') {
        return hex - 'A'  + 10;
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
        
        uint8_t byte = 16 * FromHexToDecimal(*p++) + FromHexToDecimal(*p++);
        buffer |= byte << 16;
        
        if (p <= endOfString - 2) {
            byte = 16 * FromHexToDecimal(*p++) + FromHexToDecimal(*p++);
            buffer |= byte << 8;
        }
        else {
            leaps++;
        }
        
        if (p <= endOfString - 2) {
            byte = 16 * FromHexToDecimal(*p++) + FromHexToDecimal(*p++);
            buffer |= byte;
        }
        else {
            leaps++;
        }
        
        size_t index = (buffer >> 18) & 0x3F;
        encodedString[0 + count] = sBase[index];
        
        index = (buffer >> 12) & 0x3F;
        encodedString[1 + count] = sBase[index];
        
        index = (buffer >> 6) & 0x3F;
        encodedString[2 + count] = sBase[index];
        
        index = buffer & 0x3F;
        encodedString[3 + count] = sBase[index];
        
        count += 4;
    }
    
    encodedString[count] = '\0';
    
    for (size_t i = 1; i <= leaps; i++) {
        encodedString[resultSize - i] = '=';
    }
    
    return encodedString;
}

int main(int argc, const char * argv[]) {
    char *hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char *base64String = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    char *convertedString = CreateBase64StringFromHexString(hexString, strlen(hexString));
    
    assert(strcmp(convertedString, base64String) == 0);
    
    free(convertedString);
    
    return 0;
}
