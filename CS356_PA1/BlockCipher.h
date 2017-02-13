//
// Created by matt on 2/12/17.
//

#ifndef CS356_PA1_BLOCKCIPHER_H
#define CS356_PA1_BLOCKCIPHER_H

#include <string>
#include <vector>


class BlockCipher {
public:
    BlockCipher(std::string fileName);
private:
    bool parseBlocks();
    void printBlocks();
    void freeBlocks();
    void xorBlocks();
    void performSwap();

    std::string m_fileName;
    std::vector<char*> m_blocks;
    char* m_key;
};


#endif //CS356_PA1_BLOCKCIPHER_H
