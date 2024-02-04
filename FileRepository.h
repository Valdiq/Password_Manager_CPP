#ifndef S25195_PasswordManager_FILEREPOSITORY_H
#define S25195_PasswordManager_FILEREPOSITORY_H


#include "PasswordEntity.h"
#include "XORCipher.h"
#include <fstream>

class FileRepository {

public:
    std::vector<PasswordEntity> readFromFile(const std::string &filename, std::string key);

    void saveToFile(const std::vector<PasswordEntity> &passwords, const std::string &filename, std::string const &key);


};


#endif
