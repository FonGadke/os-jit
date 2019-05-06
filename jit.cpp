//
// Created by Кирилл Чулков on 2019-05-06.
//

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>

#include <iostream>


using func_t = int (*)(int);

size_t const MAPPED_SIZE = 4096;

static u_char binFunc[] = {
        0x55,
        0x48, 0x89, 0xe5,
        0x89, 0x7d, 0xfc,
        0x8b, 0x7d, 0xfc,
        0x0f, 0xaf, 0x7d, 0xfc,
        0x89, 0xf8,
        0x5d,
        0xc3
};

int main() {


    void* square = mmap(0, MAPPED_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (square == MAP_FAILED) {
        std::cerr << "Can't mmap memory. " << strerror(errno);
        return EXIT_FAILURE;
    }
    memcpy(square, binFunc, sizeof(binFunc));
    if (mprotect(square, MAPPED_SIZE, PROT_EXEC | PROT_WRITE)) {
        std::cerr << "Can't adjust permissions. " << strerror(errno);
        return EXIT_FAILURE;
    }

    int a = 0;
    std::cout << "Enter number\n";
    std::cin >> a;
    std::cout << ((func_t) square)(a) << std::endl;

    if (munmap(square, MAPPED_SIZE)) {
        std::cerr << "Can't unmap. " << strerror(errno);
        return EXIT_FAILURE;
    }
    return 0;
}
