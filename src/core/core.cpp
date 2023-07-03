#include "core.h"

Core::Core()
{
    this->executablePath = "";

#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    this->executablePath = std::string(buffer);

    std::size_t found = this->executablePath.find_last_of("\\");
    this->executablePath = this->executablePath.substr(0, found);
#else
    char buffer[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
        buffer[len] = '\0';
        this->executablePath = std::string(buffer);
    }
#endif
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

    std::fstream file(executablePath + '\\' + filename, std::ios::in);

    std::string line;

    while (std::getline(file, line))
    {
        content += line;
    }

    file.close();

    return content;
}

void Core::parseLayout(std::string layout)
{
}

void Core::parseElement(std::string element)
{
}
