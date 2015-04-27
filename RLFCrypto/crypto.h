//
//  crypto.h
//  hextobase64
//
//  Created by Sergey Dunets on 23.04.15.
//  Copyright (c) 2015 Sergey Dunets. All rights reserved.
//

#ifndef hextobase64_crypto_h
#define hextobase64_crypto_h

#include <stdio.h>

/// @param hexEncodedString Source hex encoded string in format "HHHH..." where H is a hexadecimal digit. Number of digits must be even.
/// @param size Size of the string without terminating NULL character.
/// @return New Base64 encoded string from the hex encoded string.
char *RLFCreateBase64StringFromHexString(char *hexEncodedString, size_t size);

/// @param hexEncodedByte String representing a one byte long hexadecimal number in format "HH" where H is a hexadecimal digit.
/// @return Non-negative integer value of hex encoded byte. If \code hexEncodedByte is an invalid string, returns a negative value.
int RLFHexByteStringToInt(char hexEncodedByte[2]);

#endif
