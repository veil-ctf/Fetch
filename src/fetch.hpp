#ifndef FETCH_H
#define FETCH_H

class Fetch {
    public:
        std::string getOs();
        std::string getShell();
        std::string getUptime();
        std::string getRamUsage();
        std::string getKernelInfo();
        std::string getTerminal();
        std::string getDE();
        std::string getHostname();
};

#endif