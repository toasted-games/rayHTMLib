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
    std::regex elementRegex = std::regex("<[^>]*>");
    std::regex tagRegex = std::regex("<([a-zA-Z]+).{0,}>");
    std::regex attributeRegex = std::regex("([a-zA-Z]+)=\"([^\"]+)\"");
    std::regex contentRegex = std::regex(">([^<]+)<");

    std::string executablePath;

    std::string readFile(std::string filename);

    void parseLayout(std::string layout);
    Element parseElement(std::string *unparsedElementStringPointer);

    ElementType getElementType(std::string tag);
    std::string trimWhitespace(std::string str);
    ElementAttributes getAttributes(std::string element);
};

#endif