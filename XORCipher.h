#ifndef S25195_PasswordManager_XORCIPHER_H
#define S25195_PasswordManager_XORCIPHER_H

#include <iostream>


class XORCipher {

public:
    std::string encrypt(const std::string &text, const std::string &key);

    std::string decrypt(const std::string &encryptedText, const std::string &key);

};


#endif
