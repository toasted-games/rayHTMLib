#include <rayHTMLib.h>

rayHTMLib::rayHTMLib()
{
}

int rayHTMLib::loadLayout(std::string layout)
{
    return core.loadLayout(layout);
}

int rayHTMLib::loadStylesheet(std::string stylesheet)
{
    return core.loadStylesheet(stylesheet);
}