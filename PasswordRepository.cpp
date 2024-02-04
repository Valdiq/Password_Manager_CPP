#include "PasswordRepository.h"
#include "PasswordEntity.cpp"

auto fr = FileRepository();

/**
 * @return
 *      Zwraca timestamp tej chwili
 */

std::string PasswordRepository::getTime() {
    std::time_t currTime = std::time(0);
    char *toStr = ctime(&currTime);

    return toStr;
}

/** wyszukiwanie hasła (po wszystkich polach) za slowem kluczowym
 *
 * @param passwords
 *      wektor z hasłami
 * @param keyword
 *      slowo kluczowe
 */

void PasswordRepository::searchPasswords(const std::vector<PasswordEntity> &passwords, const std::string &keyword) {
    // https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
    bool isHere = false;

    std::cout << "Result: " << std::endl;
    std::cout << "---PASSWORDS---" << std::endl;
    for (const auto &pass: passwords) {
        if (pass.name.contains(keyword) ||
            pass.category.contains(keyword) ||
            pass.website.contains(keyword) ||
            pass.login.contains(keyword)) {
            std::cout << pass << std::endl;
            isHere = true;
        }
    }

    if (!isHere) {
        std::cout << "There is no such passwords" << std::endl;
    }
}

/** Sortowanie haseł po wybranym przez uzytkiwnika polu (A-Z)
 *
 * @param passwords
 *      Wektor z hasłami (dane)
 */

void PasswordRepository::sortPasswords(std::vector<PasswordEntity> &passwords) {

    //https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
    //sortuje za pomoca okreslonej nami metody (lambdy), ktora przyjmuje 2 argumenty(PasswordEntity) i porownuje ich pola
    //Zwraca true jesli haslo A "wieksze" od B (patrzac na alfabet (zlykly compatator stringa) bazujac na wybranym polu

    std::cout << "Enter a field on wthich you want to sort passwords: " << '\n'
              << "1. Name" << '\n'
              << "2. Category" << '\n'
              << "3. Website" << '\n'
              << "4. Login" << std::endl;

    int option;
    std::cin >> option;

    switch (option) {
        case 1: {
            std::cout << "---PASSWORDS---" << std::endl;
            std::sort(passwords.begin(), passwords.end(), [](const PasswordEntity &a, const PasswordEntity &b) {
                return a.name < b.name;
            });
            for (const auto &pass: passwords) {
                std::cout << pass << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "---PASSWORDS---" << std::endl;
            std::sort(passwords.begin(), passwords.end(), [](const PasswordEntity &a, const PasswordEntity &b) {
                return a.category < b.category;
            });
            for (const auto &pass: passwords) {
                std::cout << pass << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "---PASSWORDS---" << std::endl;
            std::sort(passwords.begin(), passwords.end(), [](const PasswordEntity &a, const PasswordEntity &b) {
                return a.website < b.website;
            });
            for (const auto &pass: passwords) {
                std::cout << pass << std::endl;
            }
            break;
        }
        case 4: {
            std::cout << "---PASSWORDS---" << std::endl;
            std::sort(passwords.begin(), passwords.end(), [](const PasswordEntity &a, const PasswordEntity &b) {
                return a.login < b.login;
            });
            for (const auto &pass: passwords) {
                std::cout << pass << std::endl;
            }
            break;
        }
        default:
            std::cout << "Invalid sort option" << std::endl;
    }
}

/** Generuje randomowe haslo bazujac na parametrach uzytkownika (dlugosc, upper/lower case, znaki specjalne)
 *
 * @return
 *      zwraca zgenerowane haslo
 */

std::string PasswordRepository::generateRandomPass() {

    std::cout << '\n' << "Enter a length: ";

    int len;
    std::cin >> len;

    std::cout << '\n' << "Is there should be upper and lower cased letters? (y/n): ";

    std::string isUpperAndLowerIncluded;
    std::cin >> isUpperAndLowerIncluded;

    std::cout << '\n' << "Is there should be special symbols? (y/n): ";

    std::string isCharIncluded;
    std::cin >> isCharIncluded;

    std::string password = std::string();
    auto lowerLetters = "qwertyuiopasdfghjklzxcvbnm";
    auto upperLetters = "QWERTYUIOPASDFGHJKLZXCVBNM";
    auto chars = "!@#$%^&*()_+-=[]{}./|,~'><";

    if (isUpperAndLowerIncluded != "y" && isUpperAndLowerIncluded != "n" ||
        isCharIncluded != "y" && isCharIncluded != "n") {
        std::cout << "Wrong answers" << std::endl;
        generateRandomPass();
    } else {
        for (int i = 0; i <= len; i++) {
            if (isCharIncluded == "y" && isUpperAndLowerIncluded == "n") {
                password += lowerLetters[int(rand() % 26)];
                password += chars[int(rand() % 26)];
                password += std::to_string(int(rand() % 9));
            } else if (isCharIncluded == "y" && isUpperAndLowerIncluded == "y") {
                password += lowerLetters[int(rand() % 26)];
                password += upperLetters[int(rand() % 26)];
                password += chars[int(rand() % 26)];
                password += std::to_string(int(rand() % 9));
            } else if (isCharIncluded == "n" && isUpperAndLowerIncluded == "y") {
                password += lowerLetters[int(rand() % 26)];
                password += upperLetters[int(rand() % 26)];
                password += std::to_string(int(rand() % 9));
            } else if (isCharIncluded == "n" && isUpperAndLowerIncluded == "n") {
                password += lowerLetters[int(rand() % 26)];
                password += std::to_string(int(rand() % 9));
            }
        }
    }

    return password;
}


/** Dodaje nowe haslo do wektora i zapisuje do pliku
 *
 * @param passwords
 *      Wektor z hasłami
 * @param file
 *      Nazwa pliku / sciezka
 * @param key
 *      Klucz do szyfrowania
 */

void PasswordRepository::addPassword(std::vector<PasswordEntity> &passwords, std::string file, std::string key) {

    std::cout << "Enter the name: ";
    std::string name;
    std::cin >> name;

    std::cout << "1. Enter the password " << '\n' << "2. Generate randomly" << '\n';
    int chose;
    std::cin >> chose;

    std::string password;

    if (chose == 1) {
        std::cout << "Password: ";
        std::cin >> password;
    } else if (chose == 2) {
        password = generateRandomPass();
    } else {
        std::cout << "There is no such option" << std::endl;
    }

    std::cout << "Enter the category: ";
    std::string category;
    std::cin >> category;

    std::cout << "Enter the website (optional, enter 's' to skip): ";
    std::string website;
    std::cin >> website;
    if (website == "s") {
        website.clear();
    }

    std::cout << "Enter the login (optional, enter 's' to skip): ";
    std::string login;
    std::cin >> login;
    if (login == "s") {
        login.clear();
    }

    passwords.push_back({name, password, category, website, login});
    fr.saveToFile(passwords, file, key);
    std::cout << "Password added successfully" << std::endl;

}

/** Edytuje wtbrane dane w hasle
 *
 * @param passwords
 *      Wektor z hasłami
 * @param entityName
 *      Nazwa hasla do edycji
 */

void PasswordRepository::editPassword(std::vector<PasswordEntity> &passwords, const std::string &entityName) {

    bool isPresent = false;

    for (auto &pass: passwords) {
        if (pass.name == entityName) {
            isPresent = true;

            std::cout << "Choose field to edit: " << '\n'
                      << "1. Name" << '\n'
                      << "2. Password" << '\n'
                      << "3. Category" << '\n'
                      << "4. Website" << '\n'
                      << "5. Login" << std::endl;
            int chose;
            std::cin >> chose;

            switch (chose) {
                case 1: {
                    std::cout << "Enter the new name: ";
                    std::string newName;
                    std::cin >> newName;
                    pass.name = newName;
                    std::cout << "Name updated successfully" << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter the new password: ";
                    std::string newPassword;
                    std::cin >> newPassword;
                    pass.password = newPassword;
                    std::cout << "Password updated successfully" << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter the new Category: ";
                    std::string newCategory;
                    std::cin >> newCategory;
                    pass.category = newCategory;
                    std::cout << "Category updated successfully" << std::endl;
                    break;
                }
                case 4: {
                    std::cout << "Enter the new Website: ";
                    std::string newWebsite;
                    std::cin >> newWebsite;
                    pass.website = newWebsite;
                    std::cout << "Website updated successfully" << std::endl;
                    break;
                }
                case 5: {
                    std::cout << "Enter the new Login: ";
                    std::string newLogin;
                    std::cin >> newLogin;
                    pass.login = newLogin;
                    std::cout << "Login updated successfully" << std::endl;
                    break;
                }
            }
            break;
        }
    }
    if (!isPresent) {
        std::cout << "Password not found" << std::endl;
    }
}

/** Usuniecie wybranego hasla
 *
 * @param passwords
 *      Wektor z haslami
 * @param file
 *      Nazwa pliku / sciezka (dla zapisu zmian)
 * @param key
 *      Klucz do szyfrowania (dla zapisu zmian)
 */

void PasswordRepository::deletePassword(std::vector<PasswordEntity> &passwords, std::string &file,
                                        const std::string &key) {
    std::cout << "Choose password to delete : " << std::endl;
    std::cout << "---PASSWORDS---" << std::endl;

    int nr = 0;
    int res = 0;

    for (auto &pass: passwords) {
        std::cout << nr++ << ". " << pass << std::endl;
    }

    if (nr == 0) {
        std::cout << "File is empty" << std::endl;
    } else {
        std::cin >> res;
        if (res >= 0 && res <= nr) {
            std::cout << "Do you comfirm deleting? (y/n): ";

            std::string agree;
            std::cin >> agree;

            if (agree == "y") {
                passwords.erase(passwords.begin() + res);
                std::cout << "Password was deleted" << std::endl;
            } else {
                std::cout << "Deleting was declined" << std::endl;
            }
        } else {
            std::cout << "Invalid number of password" << std::endl;

        }
    }
}

/** Dodanie kategorii hasel
 *
 */

void PasswordRepository::addCategory() {

}

/** Usuniencie kategorii wraz z jej hasłami
 *
 * @param passwords
 *  Wektor z aslami
 * @param category
 *  Nazwa kategorii do usuniecia
 * @param file
 *  Nazwa pliku / sciezka (dla zapisy zmian)
 * @param key
 *  Klucz do szyfrowania (dla zapisu zmian)
 */

void PasswordRepository::deleteCategory(std::vector<PasswordEntity> &passwords, const std::string &category,
                                        std::string file, std::string key) {
    std::string agree = "";
    bool isExist = false;
    int id = 0;

    for (auto pass: passwords) {
        if (pass.category == category) {
            isExist = true;
            break;
        }
    }

    if (isExist) {
        std::cout << "Do ypu comfirm deleting whole category " << category << " ? (y/n)" << std::endl;
        std::cin >> agree;

        if (agree == "y") {
            for (auto &pass: passwords) {
                //https://stackoverflow.com/questions/39019806/using-erase-remove-if-idiom
                //Usuniecie hasla za pomoca metody remove_if(<algorithm>) z parametrem w postaci lambdy ktora wykonuje wyszukiwania
                //hasla w wektorze kategoria ktorego byla podana przez uzytkownika

                passwords.erase(
                        std::remove_if(passwords.begin(), passwords.end(),
                                       [&category](const PasswordEntity &pass) {
                                           return pass.category == category;
                                       }), passwords.end());
                id++;
            }
            std::cout << "Category '" << category << "' was deleted" << std::endl;
        } else {
            std::cout << "Deleting was declined" << std::endl;
        }
    } else {
        std::cout << "Category doesnt exist" << std::endl;
    }
}