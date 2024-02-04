#include "XORCipher.h"

/** szyfrowanie algorytmem XOR
 *
 * @param text
 *      tekst do szyfrowania
 * @param key
 *      klucz da szyfrowania
 * @return
 *      zaszyfrowany tekst z dodaną na koncu spacją dla ulatwienia czytania z pliku
 */

std::string XORCipher::encrypt(const std::string &text, const std::string &key) {
    std::string encryptedText = text;
    for (int i = 0; i < text.size(); i++) {
        encryptedText[i] = text[i] ^ key[i % key.size()];
    }
    return encryptedText + ' ';
}

/** Odszyfrowanie (wykonując algorytm XOR ponownie z tym samym kluczem)
 *
 * @param text
 *      tekst do odszyfrowania
 * @param key
 *      klucz do odszyfrowania
 * @return
 *      odszyfrowany text za pomoca metody encrypt z tym samym kluczem i wraz z usunętą spacją na koncu
 *      dla poprawnego zapisania wartosci do pól objektu PasswordEntity
 */

std::string XORCipher::decrypt(const std::string &text, const std::string &key) {
    std::string res = encrypt(text, key);
    res.pop_back();
    return res;
}