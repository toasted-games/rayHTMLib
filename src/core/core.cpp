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

    std::regex elementRegex(this->elementRegex);
    std::regex tagRegex(this->tagRegex);
    std::regex attributeRegex(this->attributeRegex);

    std::smatch matchElement;
    std::smatch matchTag;
    std::smatch matchAttribute;

    std::regex_search(layout, matchElement, elementRegex);
    std::string element = matchElement.str();

    std::regex_search(element, matchTag, tagRegex);
    std::string tag = matchTag[1].str();
    std::string closingTag = "</" + matchTag[1].str() + ">";

    std::regex nextTagRegex("<" + tag + "[^>]*>");
    std::regex nextClosingTagRegex(closingTag);

    std::string::const_iterator searchStart(layout.cbegin());
    std::string::const_iterator searchEnd(layout.cend());
    std::string::const_iterator searchStartClosing(layout.cbegin());
    std::string::const_iterator searchEndClosing(layout.cend());

    size_t elementStart = matchElement.position();
    size_t elementEnd;

    int closingCounter = 0;
    size_t pointer = 0;
    size_t pointerClosing = 0;

    do
    {
        searchStart = layout.cbegin() + pointer;
        searchStartClosing = layout.cbegin() + pointerClosing;

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
    } while (pointer < layout.size() && closingCounter > 0);

    std::string elementContent = layout.substr(elementStart, elementEnd - elementStart);

    std::cout << "Element: " << elementContent << std::endl;

    layout = layout.substr(elementEnd);

    std::cout << layout << std::endl;
}

void Core::parseElement(std::string element)
{
}
