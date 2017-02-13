//
// Created by matthew on 2/12/17.
//

#include "StreamCipher.h"
#include <iostream>
#include <fstream>

bool StreamCipher::encrypt(std::string fileName, const char* key, std::string outputFile){
    std::string fileContents;
    getStringFromFile(fileContents, fileName);
    performXor(fileContents, key);
    writeToFile(fileContents, outputFile);
}

bool StreamCipher::unencrypt(std::string fileName, const char *key, std::string outputFile) {
    std::string fileContents;
    getStringFromFile(fileContents, fileName);
    performXor(fileContents, key);
    writeToFile(fileContents, outputFile);
}

bool StreamCipher::getStringFromFile(std::string& fileContents, std::string& fileName) {
    fileContents = "";
    FILE* fileToEncrypt;
    fileToEncrypt = fopen(fileName.c_str(), "r");

    if(fileToEncrypt) {
        char c;
        while ((c = getc(fileToEncrypt)) != EOF) {
            fileContents += c;
        }
        fclose(fileToEncrypt);
    } else{
        std::cerr << "Error. Could not open file " << fileName;
        return false;
    }

    return true;
}

void StreamCipher::performXor(std::string &contents, const char *key) {
    std::string stringKey(key);

    int keyPos = 0;
    for(int i = 0; i < contents.size(); ++i){
        contents[i] = contents[i] xor stringKey[keyPos];
        ++keyPos;

        if(keyPos >= stringKey.size())
            keyPos = 0;
    }
}

bool StreamCipher::writeToFile(std::string& text, std::string& outputFilename) {
    //FILE *file = fopen(outputFilename.c_str(), "w");
    //int results = fputs(text.c_str(), file);

    std::ofstream myfile;
    myfile.open (outputFilename);
    myfile << text;
    myfile.close();

}