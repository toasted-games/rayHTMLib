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

    parseLayout(content);
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
    Layout parsedLayout;

    parseElement(&layout);
}

Element Core::parseElement(std::string *unparsedElementStringPointer)
{
    std::string unparsedElementString = *unparsedElementStringPointer;

    Element parsedElement;

    std::smatch matchElement;
    std::smatch matchTag;
    std::smatch matchAttribute;

    // find element (e.g. <div id="test">)
    std::regex_search(unparsedElementString, matchElement, elementRegex);
    std::string element = matchElement.str(); // element string (e.g. <div id="test">)

    // find tag (e.g. div)
    std::regex_search(element, matchTag, tagRegex);
    std::string tag = matchTag[1].str();
    std::string closingTag = "</" + matchTag[1].str() + ">";

    // declare regex for searching same type of tag
    std::regex nextTagRegex("<" + tag + "[^>]*>");
    std::regex nextClosingTagRegex(closingTag);

    // create iterators for searching
    std::string::const_iterator searchStart(unparsedElementString.cbegin());
    std::string::const_iterator searchEnd(unparsedElementString.cend());
    std::string::const_iterator searchStartClosing(unparsedElementString.cbegin());
    std::string::const_iterator searchEndClosing(unparsedElementString.cend());

    size_t elementStart = matchElement.position(); // start of element (used for substring)
    size_t elementEnd = 0;                         // end of element (used for substring)

    int closingCounter = 0; // counts how many closing tags are missing

    size_t pointer = 0;        // pointer for searching next tag
    size_t pointerClosing = 0; // pointer for searching next closing tag

    do
    {
        searchStart = unparsedElementString.cbegin() + pointer;
        searchStartClosing = unparsedElementString.cbegin() + pointerClosing;

        std::smatch matchNextTag;
        std::regex_search(searchStart, searchEnd, matchNextTag, nextTagRegex);

        std::smatch matchNextClosingTag;
        std::regex_search(searchStartClosing, searchEndClosing, matchNextClosingTag, nextClosingTagRegex);

        if (matchNextTag.empty() || matchNextClosingTag.empty())
        {
            break;
        }

        int64_t nextTagIndex = matchNextTag.position() + pointer;
        int64_t nextClosingTagIndex = matchNextClosingTag.position() + pointerClosing;

        if (nextTagIndex < nextClosingTagIndex)
        {
            pointer = nextTagIndex + matchNextTag.str().size();
            closingCounter++;
        }
        else if (nextTagIndex > nextClosingTagIndex)
        {
            pointerClosing = nextClosingTagIndex + matchNextClosingTag.str().size();
            closingCounter--;
            if (closingCounter == 0)
            {
                elementEnd = pointerClosing;
            }
        }
    } while (pointer < unparsedElementString.size() && closingCounter > 0);

    std::cout << "Element end: " << elementEnd << std::endl;

    std::string elementContent = unparsedElementString.substr(elementStart + element.size(), elementEnd - element.size() - elementStart - closingTag.size());

    parsedElement.content = elementContent;

    // unparsedElement = unparsedElement.substr(elementEnd);

    // std::cout << unparsedElement << std::endl;

    // return unparsedElement.size() > 0 ? elementEnd : -1;
    return parsedElement;
}

ElementType Core::getElementType(std::string tag)
{
    if (tag == "main")
    {
        return ElementType::MAIN;
    }
    else if (tag == "div")
    {
        return ElementType::DIV;
    }
    else if (tag == "span")
    {
        return ElementType::SPAN;
    }
    else if (tag == "button")
    {
        return ElementType::BUTTON;
    }
    else if (tag == "input")
    {
        return ElementType::HTML_INPUT;
    }
    else if (tag == "label")
    {
        return ElementType::LABEL;
    }
    else if (tag == "textarea")
    {
        return ElementType::TEXTAREA;
    }
    else if (tag == "h1")
    {
        return ElementType::H1;
    }
    else if (tag == "h2")
    {
        return ElementType::H2;
    }
    else if (tag == "h3")
    {
        return ElementType::H3;
    }
    else if (tag == "h4")
    {
        return ElementType::H4;
    }
    else if (tag == "h5")
    {
        return ElementType::H5;
    }
    else if (tag == "h6")
    {
        return ElementType::H6;
    }
    else if (tag == "p")
    {
        return ElementType::P;
    }
    else if (tag == "table")
    {
        return ElementType::TABLE;
    }
    else if (tag == "tr")
    {
        return ElementType::TR;
    }
    else if (tag == "td")
    {
        return ElementType::TD;
    }
    else if (tag == "th")
    {
        return ElementType::TH;
    }
    else if (tag == "img")
    {
        return ElementType::IMG;
    }
    else if (tag == "a")
    {
        return ElementType::A;
    }
    else if (tag == "ul")
    {
        return ElementType::UL;
    }
    else if (tag == "ol")
    {
        return ElementType::OL;
    }
    else if (tag == "li")
    {
        return ElementType::LI;
    }
    else
    {
        return ElementType::SPAN;
    }
}