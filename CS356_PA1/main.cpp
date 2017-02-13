#include <iostream>
#include "BlockCipher.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    BlockCipher test("blockPlainText.txt");
    return 0;
}