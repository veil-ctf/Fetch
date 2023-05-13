#include <iostream>
#include "fetch.hpp"
#include <cstring>

int main(int argc, char **argv) {
    if (argc > 1) {
        if (strcmp(argv[1], "--clean") == 0) {
            system("clear");
        }
    }
    Fetch f;

    std::cout << "\033[35m" << R"(                       
        ╔═╗┌─┐┌┬┐┌─┐┬ ┬
        ╠╣ ├┤  │ │  ├─┤
        ╚  └─┘ ┴ └─┘┴ ┴
    )" << "\033[0m" << std::endl;
    std::cout << "\033[1;36m\tOS: \033[0m" << f.getOs();
    std::cout << "\033[1;36m\n\tShell: \033[0m" << f.getShell();
    std::cout << "\033[1;36m\n\tUptime: \033[0m" << f.getUptime();
    std::cout << "\033[1;36m\n\tRam: \033[0m" << f.getRamUsage();
    std::cout << "\033[1;36m\n\tKernel: \033[0m" << f.getKernelInfo();
    std::cout << "\033[1;36m\n\tTerminal: \033[0m" << f.getTerminal();
    std::cout << "\033[1;36m\n\tDE: \033[0m" << f.getDE();
    std::cout << "\033[1;36m\n\tHostname: \033[0m" << f.getHostname();
    std::cout << "\033[1;36m\n\n";
};