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

private:
    Core core;
};

extern rayHTMLib DOM;

#endif // RAYHTMLIB_H
