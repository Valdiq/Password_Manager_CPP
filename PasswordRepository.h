#ifndef S25195_PasswordManager_PASSWORDREPOSITORY_H
#define S25195_PasswordManager_PASSWORDREPOSITORY_H

#include <vector>
#include <ctime>
#include "PasswordEntity.h"
#include "FileRepository.h"

class PasswordRepository {

public:
    std::string getTime();

    void searchPasswords(const std::vector<PasswordEntity> &passwords, const std::string &keyword);

    void sortPasswords(std::vector<PasswordEntity> &passwords);

    std::string generateRandomPass();

    void addPassword(std::vector<PasswordEntity> &passwords, std::string file, std::string key);

    void editPassword(std::vector<PasswordEntity> &passwords, const std::string &entityName);

    void deletePassword(std::vector<PasswordEntity> &passwords, std::string &file, std::string const &key);

    void addCategory();

    void deleteCategory(std::vector<PasswordEntity> &passwords, const std::string &category, std::string file,
                        std::string key);


};


#endif
