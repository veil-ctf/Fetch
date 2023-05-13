#include <iostream>
#include <string>
#include <fstream>
#include "fetch.hpp"
#include <array>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <cstdlib>

std::string Fetch::getOs() {
    std::ifstream osRelease("/etc/os-release");
    std::string line;
    std::string distributionName;

    while (std::getline(osRelease, line)) {
        if (line.substr(0, 5) == "NAME=") {
            size_t found = line.find("NAME=");
            if (found != std::string::npos) {
                distributionName = line.substr(found + 5);
                break;
            }
        }
    }

    if (!distributionName.empty()) {
        return distributionName;
    }
}

std::string Fetch::getShell() {
    char* shell = std::getenv("SHELL");

    if (shell != nullptr) {
        return std::string(shell);
    } else {
        shell = "unknown";
        return std::string(shell);
    }
}

std::string Fetch::getUptime() {
    std::array<char, 128> buffer;
    std::string uptime;

    FILE *pipe = popen("uptime -p", "r");
    if (!pipe) {
        return "Error occured in getUptime()\n";   
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        uptime += buffer.data();
    }

    pclose(pipe);

    return uptime;
}

std::string Fetch::getRamUsage() {
    struct sysinfo info;

    if (sysinfo(&info) == 0) {
        long totalRAM = info.totalram * info.mem_unit;
        long freeRAM = info.freeram * info.mem_unit;
        long usedRAM = totalRAM - freeRAM;
        double usedRAMMB = static_cast<double>(usedRAM) / (1024 * 1024);
        double totalRAMMB = static_cast<double>(totalRAM) / (1024 * 1024);

        return "RAM Usage: " + std::to_string(usedRAMMB) + " MB / " + std::to_string(totalRAMMB) + " MB";
    } else {
        return "Failed to retrieve RAM usage.";
    }
}

std::string Fetch::getKernelInfo() {
    struct utsname kernelInfo;

    if (uname(&kernelInfo) == 0) {
        std::string kernelVersion = kernelInfo.release;
        std::string kernelName = kernelInfo.sysname;
        std::string machine = kernelInfo.machine;

        return "Kernel: " + kernelName + " " + kernelVersion + " (" + machine + ")";
    } else {
        return "Failed to retrieve kernel information.";
    }
}

std::string Fetch::getTerminal() {
    const char *termEnv = std::getenv("TERM");
    if (termEnv != nullptr) {
        return std::string(termEnv);
    } else {
        return "Unable to retrieve terminal emulator.";
    }
}

std::string Fetch::getDE() {
    const char* currentDE = std::getenv("DESKTOP_SESSION");
    if (currentDE != nullptr) {
        return currentDE;
    } else {
        const char* session = std::getenv("XDG_CURRENT_DESKTOP");
        if (session != nullptr) {
            return currentDE;
        } else {
            return "Error getDE()";
        }
    }
}

std::string Fetch::getHostname() {
    std::ifstream file("/etc/hostname");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            return line;
        }
    }
}