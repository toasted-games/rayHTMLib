#ifndef RAYHTMLIB_UI_ELEMENT_H
#define RAYHTMLIB_UI_ELEMENT_H

#include <iostream>
#include <string>
#include <vector>

enum ElementType
{
    MAIN,
    DIV,
    SPAN,
    BUTTON,
    INPUT,
    LABEL,
    TEXTAREA,
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    P,
    TABLE,
    TR,
    TD,
    TH,
    IMG,
    A,
    UL,
    OL,
    LI,
};

struct ElementAttributes
{
    std::string id;
    std::vector<std::string> classes;
};

class Element
{
public:
    Element();

private:
    ElementType type;
    ElementAttributes attributes;
    std::vector<Element> children;
};

#endif