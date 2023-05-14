#include <cstddef>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <algorithm>
#include <cstring>
#include "fetch.hpp"
#include <ctime>

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
        return "Error: getUptime()\n";
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        uptime += buffer.data();
    }

    std::string old_ = "up ";
    std::string new_ = "";

    size_t pos = uptime.find(old_);

    while (pos != std::string::npos) {
        uptime.replace(pos, old_.length(), new_);
        pos = uptime.find(old_, pos + new_.length());
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
        // Use this for exact ram, example: 3300.1314513mb
        //double usedRAMMB = static_cast<double>(usedRAM) / (1024 * 1024);
        //double totalRAMMB = static_cast<double>(totalRAM) / (1024 * 1024);

        size_t usedRAMMB = static_cast<size_t>(usedRAM) / (1024 * 1024);
        size_t totalRAMMB = static_cast<size_t>(totalRAM) / (1024 * 1024);

        return "" + std::to_string(usedRAMMB) + " MB / " + std::to_string(totalRAMMB) + " MB";
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

        return "" + kernelName + " " + kernelVersion + " (" + machine + ")";
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
        return std::string(currentDE);
    } else {
        const char* session = std::getenv("XDG_CURRENT_DESKTOP");
        if (session != nullptr) {
            return std::string(currentDE);
        } else {
            return "Error: getDE()";
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

std::string Fetch::getUser() {
    char* currentUser = std::getenv("USERNAME");
    if (currentUser != nullptr) {
        std::string temp(currentUser);
        size_t pos = temp.find('\n');

        while (pos != std::string::npos) {
            temp.erase(pos, 1);
            pos = temp.find('\n', pos);
        }
        strcpy(currentUser, temp.c_str());
        return currentUser;
    } else {
        std::array<char, 128> buf;
        std::string userName;
        FILE *pipe = popen("whoami", "r");
        if (!pipe) {
            return "Error in getUser()";
        } else {
            while (fgets(buf.data(), buf.size(), pipe) != nullptr) {
                userName += buf.data();
            }
            pclose(pipe);
            return userName;
        }
    }
}

std::string Fetch::getTime() {
    std::time_t currentTime = std::time(nullptr);
    std::string timeString = std::ctime(&currentTime);

    return timeString;
}