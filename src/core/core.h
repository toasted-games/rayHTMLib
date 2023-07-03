#ifndef RAYHTMLIB_CORE_H
#define RAYHTMLIB_CORE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

class Core
{
public:
    Core();

    int loadLayout(std::string layout);

private:
    std::string readFile(std::string filename);
};

#endif