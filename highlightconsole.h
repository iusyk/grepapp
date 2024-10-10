
#ifndef __HIGHLIGHTCONSOLE_H__
#define __HIGHLIGHTCONSOLE_H__
#include <iostream>
#include <string>

class HighlightConsole final
{
public:
    HighlightConsole(const std::string &highlight);
    HighlightConsole& operator<<(const std::string& text);
protected:
    static void setColor(int textColor)
    {
        std::cout << "\033[" << textColor << "m";
    }
    static void resetColor() { std::cout << "\033[0m"; }
private:
    std::string mHighlight;
};

#endif