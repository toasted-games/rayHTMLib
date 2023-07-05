#include <iostream>

#include <rayHTMLib.h>

rayHTMLib DOM;

int main(int, char **)
{
    DOM.loadLayout("assets/layouts/testLayout.html");
    DOM.loadStylesheet("assets/stylesheets/testStylesheet.css");
    return 0;
}