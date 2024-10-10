#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

#include <string>
#include <functional>
#include <unordered_set>
#include <future>

typedef std::function<void(const std::string &, const std::string &)> output_find_func_type;

class TextQuery final
{
public:
    TextQuery()= delete;

    explicit TextQuery(const std::string& txt, const output_find_func_type out);
    TextQuery(const TextQuery &src);
    TextQuery(TextQuery &&src);

    TextQuery& operator()(const TextQuery& src);
    TextQuery& operator()(TextQuery&& src);
    void operator()(const std::string &fileName)const;

private:
    std::string mText;
    output_find_func_type mOutput;
};

class OutputInterface
{
public:
    virtual ~OutputInterface(){}
    virtual void operator()(const std::string &file, const std::string &line)= 0;
};

class FileOutput : public OutputInterface
{
public:
    void operator()(const std::string &file, const std::string &line) override;
private:
    std::unordered_set<std::string> processeFiles;
    std::mutex outputMutex;
};

class FileTextOutput : public OutputInterface
{
public:
    explicit FileTextOutput(const std::string &text):mText{text}{}
    void operator()(const std::string &file, const std::string &line) override;
private:
    std::string mText;
    std::mutex outputMutex;
};

#endif
