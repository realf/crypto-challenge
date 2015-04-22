//
//  main.c
//  hextobase64
//
//  Created by Sergey Dunets on 22.04.15.
//  Copyright (c) 2015 Sergey Dunets. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"

int main(int argc, const char * argv[]) {
    char *hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char *base64String = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    char *convertedString = CreateBase64StringFromHexString(hexString, strlen(hexString));
    
    assert(strcmp(convertedString, base64String) == 0);
    
    free(convertedString);
    
    return 0;
}
