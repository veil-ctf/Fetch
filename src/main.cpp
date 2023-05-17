#include <cstdlib>
#include <iostream>
#include "../include/fetch.hpp"
#include <cstring>
#include <string>
#include <fstream>

int main(int argc, char **argv) {
    Fetch f;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0) {
                std::cout << argv[0] << " [OPTIONS]..\n"
                << std::endl << "--help\tShows this page"
                << std::endl << "--clean\tClears the screen"
                << std::endl << "--save [FILE]\tSaves info in custom file"
                << std::endl << "\nExamples:\n" << argv[0] << " --clean\n"
                << argv[0] << " --save info.txt\n";
                exit(0);
            }
            if (strcmp(argv[i], "--clean") == 0) {
                system("clear");
            }
            if (strcmp(argv[i], "--save") == 0) {
                std::string fileName;
                if (argv[i] + 1) {
                    fileName = argv[i + 1];
                } else {
                    fileName = "info.txt";
                }
                std::ofstream outputFile(fileName);
                if (outputFile.is_open()) {
                    outputFile << "User: " << f.getUser();
                    outputFile << "Hostname: " << f.getHostname();
                    outputFile << "\nOS: " << f.getOs();
                    outputFile << "\nShell: " << f.getShell();
                    outputFile << "\nUptime: " << f.getUptime();
                    outputFile << "Ram Usage: " << f.getRamUsage();
                    outputFile << "\n" << f.getKernelInfo();
                    outputFile << "\nTerminal:" << f.getTerminal();
                    outputFile << "\nDE: " << f.getDE();
                    outputFile.close();
                } else {
                    std::cout << "Failed to write to output file.";
                }
            }
        }
    }
    std::cout << "\t\033[35m╔═╗┌─┐┌┬┐┌─┐┬ ┬\033[0m" << "        Time: \033[32m" << f.getTime();
    std::cout << "\t\033[35m╠╣ ├┤  │ │  ├─┤\033[0m" << "        User: \033[32m" << f.getUser();
    std::cout << "\t\033[35m╚  └─┘ ┴ └─┘┴ ┴\033[0m\n\n";
    // std::cout << "\033[35m" << R"(
    //     ╔═╗┌─┐┌┬┐┌─┐┬ ┬
    //     ╠╣ ├┤  │ │  ├─┤
    //     ╚  └─┘ ┴ └─┘┴ ┴
    // )" << "\033[0m" << std::endl;
    std::cout << "\033[1;36m\tHostname: \033[0m" << f.getHostname();
    std::cout << "\033[1;36m\n\tCurrent user: \033[0m" << f.getUser();
    std::cout << "\033[1;36m\tOS: \033[0m" << f.getOs();
    std::cout << "\033[1;36m\n\tShell: \033[0m" << f.getShell();
    std::cout << "\033[1;36m\n\tUptime: \033[0m" << f.getUptime();
    std::cout << "\033[1;36m\tRam: \033[0m" << f.getRamUsage();
    std::cout << "\033[1;36m\n\tKernel: \033[0m" << f.getKernelInfo();
    std::cout << "\033[1;36m\n\tTerminal: \033[0m" << f.getTerminal();
    std::cout << "\033[1;36m\n\tDE: \033[0m" << f.getDE();
    std::cout << "\033[1;36m\n\n";

    return 0;
};