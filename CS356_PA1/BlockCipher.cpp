//
// Created by matt on 2/12/17.
//

#include <vector>
#include <iostream>
#include <fstream>
#include "BlockCipher.h"

BlockCipher::BlockCipher() {
    //m_fileName = fileName;
    //m_key = "ParaNoiA";
    //parseBlocks();
}

bool BlockCipher::encrypt(std::string fileName, const char* key, std::string outputFile) {
    m_fileName = fileName;
    m_key = key;

    if(!parseBlocks())
        return false;

    xorBlocks();
    std::string text = getStringFromBlocks();
    performSwap(text);
    writeToFile(text, outputFile);
    freeBlocks();

    return true;
}

bool BlockCipher::unencrypt(std::string fileName, const char *key, std::string outputFile) {
    m_fileName = fileName;
    m_key = key;
    std::string fileContents;

    if(!getStringFromFile(&fileContents))
        return false;

    performSwap(fileContents);
    writeStringIntoBlocks(fileContents);
    xorBlocks();
    fileContents = getStringFromBlocks();
    writeToFile(fileContents, outputFile);
}

bool BlockCipher::parseBlocks() {
    freeBlocks();

    FILE* fileToEncrypt;
    fileToEncrypt = fopen(m_fileName.c_str(), "r");

    m_blocks.push_back(new char[9]);
    int position = 0;

    if (fileToEncrypt) {
        char c;
        while ((c = getc(fileToEncrypt)) != EOF){
            if(position >= 8){
                m_blocks[m_blocks.size() - 1][position] = '\0';
                m_blocks.push_back(new char[9]);
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

std::string BlockCipher::getStringFromBlocks() {
    std::string allText = "";
    //printBlocks();
    for(int i = 0; i < m_blocks.size(); ++i){
        for(int j = 0; j < 8; ++j){
            if(m_blocks[i][j] != (char) 0x80) {
                allText += m_blocks[i][j];
            }
        }
    }

    return allText;
}

std::string BlockCipher::performSwap(std::string& text) {
    int binaryKey[8];

    for(int i = 0; i < 8; ++i){
        binaryKey[i] = ((int)m_key[i]) % 2;
    }

    int keyPosition = 0;
    int end = text.size() - 1;
    for(int i = 0; i < text.size(); ++i){
        if(binaryKey[keyPosition] == 1){
            char temp = text[i];
            text[i] = text[end];
            text[end] = temp;
            --end;
        }

        if(i == end){
            break;
        }

        ++keyPosition;
        if(keyPosition == 8)
            keyPosition = 0;
    }

    //writeToFile(text);
    return text;
}

bool BlockCipher::writeToFile(std::string& text, std::string& outputFilename) {
    std::ofstream myfile;
    myfile.open (outputFilename);
    myfile << text;
    myfile.close();
}

void BlockCipher::freeBlocks() {
    m_blocks.clear();
}

bool BlockCipher::getStringFromFile(std::string* fileContents) {
    *fileContents = "";
    FILE* fileToEncrypt;
    fileToEncrypt = fopen(m_fileName.c_str(), "r");

    if(fileToEncrypt) {
        char c;
        while ((c = getc(fileToEncrypt)) != EOF) {
            *fileContents += c;
        }
        fclose(fileToEncrypt);
    } else{
        std::cerr << "Error. Could not open file " << m_fileName;
        return false;
    }

    return true;
}

void BlockCipher::writeStringIntoBlocks(std::string &fileContents) {
    freeBlocks();

    m_blocks.push_back(new char[9]);

    int position = 0;
    for(int i = 0; i < fileContents.size(); ++i){
        if(position >= 8){
            m_blocks[m_blocks.size() - 1][position] = '\0';
            m_blocks.push_back(new char[9]);
            position = 0;
        }

        m_blocks[m_blocks.size() - 1][position] = fileContents[i];
        ++position;
    }

    if (position < 7){
        for(int i = position; i < 8; ++i)
            m_blocks[m_blocks.size() -1][i] = 0x80;
    }
}