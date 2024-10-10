
#include <filesystem>
#include <iostream>
#include <fstream>
#include <mutex>

#include "functor.h"
#include "highlightconsole.h"

using namespace std;

TextQuery::TextQuery(const string& txt,
        const output_find_func_type out
        ):mText(txt), mOutput(out)
{

}

TextQuery::TextQuery(const TextQuery &src):
    mText(src.mText), mOutput(src.mOutput)
{}

TextQuery::TextQuery(TextQuery &&src):
    mText(move(src.mText)),
    mOutput(move(src.mOutput))
{
}

TextQuery& TextQuery::operator()(const TextQuery& src)
{
    if(this != &src)
    {
        mText= src.mText;
        mOutput= src.mOutput;
    }
    return *this;
}

TextQuery& TextQuery::operator()(TextQuery&& src)
{
    if(this != &src)
    {
        mText= move(src.mText);
        mOutput= move(src.mOutput);
    }
    return *this;
}

void TextQuery::operator()(const string &fileName)const
{
    ifstream f(fileName);
    string s;
    
    while (getline( f, s ))
    {
        if(!s.empty())
        {
            auto pos = s.find(mText);
            
            if (pos == string::npos)
                continue;
            if(mOutput)
                mOutput(fileName, s);
        }
    };
}

void FileOutput::operator()(const string &file, const string &line)
{
    lock_guard<mutex> locker(outputMutex);
    
    auto iter= processeFiles.find(file);
    
    if(iter == processeFiles.end())
    {
        processeFiles.insert(file);
        cout << file
             << endl;
    }
}

void FileTextOutput::operator()(const string &file, const string &line)
{
    lock_guard<mutex> locker(outputMutex);

    cout << file 
        << " :";
    HighlightConsole(mText) << line;
    cout << endl;
}
