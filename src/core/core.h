#ifndef RAYHTMLIB_CORE_H
#define RAYHTMLIB_CORE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

class Core
{
public:
    Core();

    int loadLayout(std::string layout);

private:
    std::string elementRegex = "<[^\/](\X[^>]+)>";
    std::string tagRegex = "<([a-zA-Z]+).{0,}>";
    std::string tagCloseRegex = "<\/([a-zA-Z]+)>";
    std::string idRegex = "id=\"([a-zA-Z0-9]+)\"";
    std::string classRegex = "class=\"([a-zA-Z0-9 ]+)\"";

    std::string executablePath;

    std::string readFile(std::string filename);
};

#endif