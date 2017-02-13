#include <iostream>
#include <stdio.h>
#include <string.h>
#include "BlockCipher.h"
#include "StreamCipher.h"

void usage(){
    std::cerr << "Invalid usage. Arguments should be as follows:" << std::endl
            << "First:'B' or 'S' to indicate block or stream cipher." << std::endl
            << "Second: Input file" << std::endl
            << "Third: Output file" << std::endl
            << "Fourth: encryption key file" << std::endl
            << "Fifth: 'E' for encrypt mode, 'D' for decrypt mode." << std::endl;
}

bool getStringFromFile(std::string& fileContents, std::string& fileName) {
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

int main(int argc, char *argv[]) {
    if(argc != 6){
        usage();
    }

    std::string keyFile = argv[4];
    std::string keyFileContents = "";
    getStringFromFile(keyFileContents, keyFile);

    if(strcmp(argv[1], "B") == 0){
        BlockCipher blockCipher;

        if(strcmp(argv[5],"E") == 0){
            blockCipher.encrypt(argv[2], keyFileContents.c_str(), argv[3]);
        } else if(strcmp(argv[5], "D") == 0){
            blockCipher.unencrypt(argv[2], keyFileContents.c_str(), argv[3]);
        } else{
            usage();
        }
    }

    else if(strcmp(argv[1], "S") == 0){
        StreamCipher streamCipher;
        if(strcmp(argv[5],"E") == 0){
            streamCipher.encrypt(argv[2], keyFileContents.c_str(), argv[3]);
        } else if(strcmp(argv[5], "D") == 0){
            streamCipher.unencrypt(argv[2], keyFileContents.c_str(), argv[3]);
        } else{
            usage();
        }
    } else{
        usage();
    }


    return 0;
}