#include "core.h"

Core::Core()
{
}

int Core::loadLayout(std::string layout)
{
    std::cout << "Loading layout: " << layout << std::endl;

    std::string content = readFile(layout);

    std::cout << "Layout content: " << content << std::endl;
    return 0;
}

std::string Core::readFile(std::string filename)
{
    std::string content = "";

    std::fstream file(filename, std::ios::in);

    std::string line;

    while (std::getline(file, line))
    {
        content += line;
    }

    file.close();

    return content;
}