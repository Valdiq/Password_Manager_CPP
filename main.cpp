#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <filesystem>
#include "PasswordEntity.h"
#include "PasswordRepository.h"
#include "FileRepository.h"
#include "XORCipher.h"


int main() {
    std::string key;
    std::string sourceFile;
    auto fr = FileRepository();
    auto pr = PasswordRepository();
    std::vector<PasswordEntity> passwords;

    //========== Menu wyboru pliku =========//

    int option;

    std::cout << "Choose a sourse file: " << std::endl;
    int counter = 0;
    std::vector<std::string> filesVec;
    auto dirIt = std::filesystem::directory_iterator(std::filesystem::current_path());

    for (auto el: dirIt) {
        if (!el.is_directory() && el.path().extension() == ".txt") {
            std::cout << ++counter << ". " << el.path().filename() << std::endl;
            filesVec.push_back(el.path().filename().string());
        }
    }

    std::cout << counter + 1 << ". " << "Enter path" << std::endl;

    std::cin >> option;

    sourceFile = std::filesystem::current_path().string() + "/" + filesVec.at(option - 1);

    std::cout << "Enter the encryption key: ";
    std::cin >> key;

    passwords = fr.readFromFile(sourceFile, key);


    //================ Menu Glowne ===================//

    int menuOption;

    do {
        std::cout << '\n' << "===============================" << '\n'
                  << "Enter your choice: " << '\n'
                  << "1. Search passwords" << '\n'
                  << "2. Sort passwords" << '\n'
                  << "3. Add new password" << '\n'
                  << "4. Edit password" << '\n'
                  << "5. Delete password" << '\n'
                  << "6. Add category" << '\n'
                  << "7. Delete category" << '\n'
                  << "8. Exit" << std::endl;

        std::cin >> menuOption;

        switch (menuOption) {
            case 1: {
                std::cout << "Enter keyword: ";
                std::string keyword;
                std::cin >> keyword;

                pr.searchPasswords(passwords, keyword);
                break;
            }
            case 2: {
                pr.sortPasswords(passwords);
                break;
            }
            case 3: {
                pr.addPassword(passwords, sourceFile, key);
                break;
            }
            case 4: {
                std::cout << "Enter name of password that you want to edit: ";
                std::string name;
                std::cin >> name;
                pr.editPassword(passwords, name);
                break;
            }
            case 5: {
                pr.deletePassword(passwords, sourceFile, key);
                break;
            }
            case 6: {
                pr.addCategory();
                break;
            }
            case 7: {
                std::cout << "Enter name of category that you want to remove: ";
                std::string category;
                std::cin >> category;
                pr.deleteCategory(passwords, category, sourceFile, key);
                break;
            }
            default:
                if (menuOption != 8) {
                    std::cout << "Invalid choice" << std::endl;
                    break;
                }
        }

    } while (menuOption != 8);


    //======== W zakonczeniu programu zapisujemu wszystko do pliku (lub tworzy sie plik i zapisuje sie do niego) =========//

    fr.saveToFile(passwords, sourceFile, key);


    return 0;
}


