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

#include "../ui/element.h"

struct Layout
{
    int id;
    std::vector<Element> elements;
};

class Core
{
public:
    Core();

    int loadLayout(std::string layout);

private:
    std::string elementRegex = "<[^>]*>";
    std::string tagRegex = "<([a-zA-Z]+).{0,}>";
    std::string attributeRegex = "([a-zA-Z]+)=\"([^\"]+)\"";
    std::string contentRegex = ">([^<]+)<";

    std::string executablePath;

    std::string readFile(std::string filename);

    void parseLayout(std::string layout);
    void parseElement(std::string element);
};

#endif