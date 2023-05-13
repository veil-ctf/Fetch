#include <iostream>
#include "fetch.hpp"
#include <cstring>
#include <string>
#include <fstream>

int main(int argc, char **argv) {
    Fetch f;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--clean") == 0) {
                system("clear");
            }
            if (strcmp(argv[i], "--save") == 0) {
                std::ofstream outputFile("output.txt");
                if (outputFile.is_open()) {
                    outputFile << "Hostname: " << f.getHostname();
                    outputFile << "\nOS: " << f.getOs();
                    outputFile << "\nShell: " << f.getShell();
                    outputFile << "\nUptime: " << f.getUptime();
                    outputFile << "Ram Usage: " << f.getRamUsage();
                    outputFile << "\nKernel: " << f.getKernelInfo();
                    outputFile << "\nTerminal Emulator:" << f.getTerminal();
                    outputFile << "\nDE: " << f.getDE();
                    outputFile.close();
                } else {
                    std::cout << "Failed to open output file.";
                }
            }
        }
    }

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

    return 0;
};