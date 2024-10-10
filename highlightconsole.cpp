
#include <list>
#include "highlightconsole.h"

using namespace std;

HighlightConsole::HighlightConsole(const string &highlight):
        mHighlight(highlight)
{

}
HighlightConsole& HighlightConsole::operator<<(const string& text)
{
    if(mHighlight.empty())
    {
        cout << text;
        return *this;
    }

    list<string> words;
    auto pos= 0;
    auto spos= string::npos;

    while((spos = text.find(mHighlight, pos)) != string::npos)
    {
        words.push_back(text.substr(pos, spos - pos));
        words.push_back(text.substr(spos, mHighlight.length()));
        pos= spos + mHighlight.length();
    }

    words.push_back(text.substr(pos, text.length()- pos));

    for(const auto &s: words)
    {
        if(s == mHighlight)
        {
            setColor(45);//31);
            cout << s;
            resetColor();
        }
        else
        {
            cout << s;
        }
    }
    return *this;
}
