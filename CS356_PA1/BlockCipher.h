//
// Created by matt on 2/12/17.
//

#ifndef CS356_PA1_BLOCKCIPHER_H
#define CS356_PA1_BLOCKCIPHER_H

#include <string>
#include <vector>


class BlockCipher {
public:
    BlockCipher();
    bool encrypt(std::string fileName, const char* key, std::string outputFile);
    bool unencrypt(std::string fileName, const char* key, std::string outputFile);

private:
    bool parseBlocks();
    void printBlocks();
    void freeBlocks();
    void xorBlocks();
    std::string performSwap(std::string& text);
    std::string getStringFromBlocks();
    bool writeToFile(std::string& text, std::string& outputFilename);
    bool getStringFromFile(std::string* fileContents);
    void writeStringIntoBlocks(std::string& fileContents);

    std::string m_fileName;
    std::vector<char*> m_blocks;
    const char* m_key;
};


#endif //CS356_PA1_BLOCKCIPHER_H
