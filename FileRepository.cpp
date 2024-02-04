#include "FileRepository.h"
#include "XORCipher.h"
#include "PasswordRepository.h"

auto cipher = XORCipher();
auto pr = PasswordRepository();

/** Wczytanie i odszyfrowanie haseł z pliku
 *
 * @param filename
 *      nazwa/sciezka do pliku
 * @param key
 *      klucz do odszyfrowania
 * @return
 *      vector z odszyfrowanymi hasłami
 */

std::vector<PasswordEntity> FileRepository::readFromFile(const std::string &filename, std::string key) {
    auto file = std::fstream(filename, std::ios::in);
    std::vector<PasswordEntity> passwords;
    std::string name, password, category, website, login;


    std::vector<std::string> wordsRes;
    std::string line;
    std::string word;
    int tmp = 0;

    if (file.is_open()) {

        while (std::getline(file, line)) {
            name.clear();
            password.clear();
            category.clear();
            website.clear();
            login.clear();
            wordsRes.clear();
            tmp = 0;
            if (line.empty() || line.starts_with("timestamp:")) {
                //skip
                continue;
            } else {
                //do
                line = cipher.decrypt(line, key);
                for (int i = 0; i < line.size() - 1; i++) {
                    if (line[i] == ' ') {
                        wordsRes.push_back(word);
                        word.clear();
                        tmp++;
                    }
                    word.push_back(line[i]);
                }

            }
            switch (tmp) {
                case 5: {
                    name = cipher.decrypt(wordsRes.at(0), key);
                    password = cipher.decrypt(wordsRes.at(1), key);
                    category = cipher.decrypt(wordsRes.at(2), key);
                    website = cipher.decrypt(wordsRes.at(3), key);
                    login = cipher.decrypt(wordsRes.at(4), key);
                    break;
                }
                case 4: {

                    if (wordsRes.at(3).contains(".")) {
                        name = cipher.decrypt(wordsRes.at(0), key);
                        password = cipher.decrypt(wordsRes.at(1), key);
                        category = cipher.decrypt(wordsRes.at(2), key);
                        website = cipher.decrypt(wordsRes.at(3), key);
                        login.clear();
                    } else {
                        name = cipher.decrypt(wordsRes.at(0), key);
                        password = cipher.decrypt(wordsRes.at(1), key);
                        category = cipher.decrypt(wordsRes.at(2), key);
                        website.clear();
                        login = cipher.decrypt(wordsRes.at(3), key);
                    }

                    break;
                }
                case 3: {
                    name = cipher.decrypt(wordsRes.at(0), key);
                    password = cipher.decrypt(wordsRes.at(1), key);
                    category = cipher.decrypt(wordsRes.at(2), key);
                    break;
                }
                default: {
                    name.clear();
                    password.clear();
                    category.clear();
                    website.clear();
                    login.clear();
                }
            }

            passwords.push_back({name, password, category, website, login});
        }
        file.close();
    } else {
        std::cout << "Error in opening file" << std::endl;
    }
    file.close();
    return passwords;
}

/** szyfrowanie i zapisanie haseł do pliku
 *
 * @param passwords
 *      waktor z hasłami
 * @param filename
 *      nazwa/sciezka do pliku
 * @param key
 *      klucz do szyfrowania
 */

void FileRepository::saveToFile(const std::vector<PasswordEntity> &passwords, const std::string &filename,
                                const std::string &key) {

    auto file = std::fstream(filename, std::ios::out | std::ios::trunc);

    if (file.is_open()) {
        int tmp = 0;
        for (auto &pass: passwords) {
            auto encName = cipher.encrypt(pass.name, key);
            auto encPass = cipher.encrypt(pass.password, key);
            auto encCat = cipher.encrypt(pass.category, key);
            auto encSite = cipher.encrypt(pass.website, key);
            auto encLog = cipher.encrypt(pass.login, key);

            std::string line = encName + encPass + encCat + encSite + encLog + '~';
            if (tmp > 0) {
                line.erase(line.begin());
            }

            file << line << std::endl;
            file << "timestamp:" << pr.getTime() << std::endl;
            tmp++;
        }

        file.close();
    } else {
        std::cout << "Error in opening file" << std::endl;
    }
    file.close();
}