#ifndef RAYHTMLIB_H
#define RAYHTMLIB_H

#include <iostream>
#include <string>
#include <vector>

#include "../src/core/core.h"

class rayHTMLib
{
public:
    rayHTMLib();

    int loadLayout(std::string layout);
    int loadStylesheet(std::string stylesheet);

private:
    Core core;
};

extern rayHTMLib DOM;

#endif // RAYHTMLIB_H
