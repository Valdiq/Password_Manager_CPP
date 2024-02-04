#ifndef S25195_PasswordManager_PASSWORDENTITY_H
#define S25195_PasswordManager_PASSWORDENTITY_H


#include <string>
#include <iostream>
#include <vector>

class PasswordEntity {
public:
    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;

public:

    PasswordEntity(const std::string &name, const std::string &password, const std::string &category,
                   const std::string &website, const std::string &login) : name(name), password(password),
                                                                           category(category), website(website),
                                                                           login(login) {}


    friend std::ostream &operator<<(std::ostream &os, const PasswordEntity &pe) {
        os << "Name:" << pe.name
           << " | Category:" << pe.category
           << " | Website:" << pe.website
           << " | Login:" << pe.login << '\n'
           << "==========================" << '\n';
        return os;
    }

    /** Sprawdza czy haslo jest unikalne
     *
     * @param passwords
     *      wektor z hasłami
     * @param password
     *      haslo
     * @return
     *      true/false
     */

    bool isUniquePassword(const std::vector<PasswordEntity> &passwords, const std::string &password) {
        for (const auto &pass: passwords) {
            if (pass.password == password) {
                return true;
            }
        }
        return false;
    }

};


#endif
