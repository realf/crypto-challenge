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

/// Creates new Base64 encoded string from hex string
char *CreateBase64StringFromHexString(char *hexString, size_t hexSize);

#endif
