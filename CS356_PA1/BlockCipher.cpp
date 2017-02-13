//
// Created by matt on 2/12/17.
//

#include <vector>
#include <iostream>
#include "BlockCipher.h"

BlockCipher::BlockCipher(std::string fileName) {
    m_fileName = fileName;
    m_key = "ParaNoiA";
    parseBlocks();
}

bool BlockCipher::parseBlocks() {
    FILE* fileToEncrypt;
    fileToEncrypt = fopen(m_fileName.c_str(), "r");

    m_blocks.push_back(new char[8]);
    int position = 0;

    if (fileToEncrypt) {
        char c;
        while ((c = getc(fileToEncrypt)) != EOF){
            if(position >= 8){
                m_blocks.push_back(new char[8]);
                position = 0;
            }

            m_blocks[m_blocks.size() - 1][position] = c;
            ++position;
        }
        if (position < 7){
            for(int i = position; i < 8; ++i)
                m_blocks[m_blocks.size() -1][i] = 0x80;
        }
        fclose(fileToEncrypt);


    } else{
        std::cerr << "Error. Could not open file " << m_fileName;
        return false;
    }

    printBlocks();
    return true;
}

void BlockCipher::xorBlocks(){
    for(int i = 0; i < m_blocks.size(); ++i){
        for(int j = 0; j < 8; ++j){
            m_blocks[i][j] = m_blocks[i][j] xor m_key[j];
        }
    }
}

void BlockCipher::printBlocks() {
    for(int i = 0; i < m_blocks.size(); ++i){
        std::cout << m_blocks[i];
    }
}

void BlockCipher::performSwap() {
    int start = 0;
    int end = 7;

    std::string allText = "";
    for(int i = 0; i < m_blocks.size(); ++i){
        allText += m_blocks[i];
    }
}

void BlockCipher::freeBlocks() {

}