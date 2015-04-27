//
//  main.c
//  fixedxor
//
//  Created by Sergey Dunets on 28.04.15.
//  Copyright (c) 2015 Sergey Dunets. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"

char RLFIntToHexDigitCharacter(int number);
void RLFByteToHexString(int byte, char **stringRef);

void testRLFIntToHexDigitCharacter(void) {
    assert(RLFIntToHexDigitCharacter(11) == 'b');
}

void testRLFByteToHexString(void) {
    char *hexString = malloc(sizeof(typeof(hexString)) * 3);
    
    RLFByteToHexString(16, &hexString);
    hexString[2] = '\0';
    
    assert(strcmp(hexString, "10") == 0);
    
    free(hexString);
}

void testRLFCreateStringXORingStringWithKey(void) {
    char *source = "1c0111001f010100061a024b53535009181c";
    char *key = "686974207468652062756c6c277320657965";
    char *correctXoredString = "746865206b696420646f6e277420706c6179";
    
    char *xoredString = RLFCreateStringXORingStringWithKey(source, key, strlen(source));
    
    assert(strcmp(xoredString, correctXoredString) == 0);
    
    free(xoredString);
}

int main(int argc, const char * argv[]) {
    testRLFIntToHexDigitCharacter();
    testRLFByteToHexString();
    
    testRLFCreateStringXORingStringWithKey();
    
    return 0;
}
