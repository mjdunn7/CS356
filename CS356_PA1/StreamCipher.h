//
// Created by matthew on 2/12/17.
//

#ifndef CS356_PA1_STREAMCIPHER_H
#define CS356_PA1_STREAMCIPHER_H

#include <string>


class StreamCipher {
public:
    bool encrypt(std::string fileName, const char* key, std::string outputFile);
    bool unencrypt(std::string fileName, const char* key, std::string outputFile);
private:
    bool getStringFromFile(std::string& fileContents, std::string&fileName);
    bool writeToFile(std::string& text, std::string& outputFilename);
    void performXor(std::string& contents, const char* key);
};


#endif //CS356_PA1_STREAMCIPHER_H
