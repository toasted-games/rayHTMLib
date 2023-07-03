#ifndef RAYHTMLIB_CORE_H
#define RAYHTMLIB_CORE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>

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

    std::string readFile(std::string filename);
};

#endif