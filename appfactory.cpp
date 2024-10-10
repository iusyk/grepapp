#include <filesystem>
#include <iostream>
#include <fstream>
#include <future>
#include <exception>

#include "appfactory.h"
#include "application.h"
#include "threadpool.h"

using namespace std;

static void checkQueryThrowIfError(const string & query)
{
    if(query.empty())
    {
        throw runtime_error("No text.");
    }
}

static void checkDirectoryThrowIfError(const string & dir)
{
    if(dir.empty())
    {
        throw runtime_error("No directory.");
    }
}

app_type createApplication(
    int argc,
    char *argv[]
    )
{
    static const string od{"-d"};
    static const string ot{"-t"};
    static const string ol{"-l"};
    static const string oh{"-h"};

    string dir,
            query;

    int i= 0;
    bool list {false};
    while(i < argc)
    {
        if(od == argv[i])
        {
            ++i;
            if(argc <= i)
                throw runtime_error("No directory.");
            dir= argv[i];
        }
        else if(ot == argv[i])
        {
            ++i;
            if(argc <= i){
                throw runtime_error("No query.");
            }
            query= argv[i];
        }
        else if(ol == argv[i])
        {
            list= true;
        }
        else if(oh == argv[i])
        {
            cout << "The following options are available: "
                << endl
                << "-d \"path to the directory\"" 
                << endl
                << "-t\"query to search\""
                << endl 
                << "[-l] - hide the the text line and list just the files where text has been found."
                << endl
                << "[-h] - show the help. All the rest options are ignored."
                << endl;
                return[](){return 0;};
        }
        ++i;
    };

    checkDirectoryThrowIfError(dir);
    checkQueryThrowIfError(query);

    shared_ptr<OutputInterface> output;
    
    if(list)
    {
        output= make_shared<FileOutput>();
    }
    else
    {
        output= make_shared<FileTextOutput>(query);
    };

    return [dir, query, list, output]()
        {
            grep(
                dir,
                query,
                [](const string & path){ // ignore the executable files.
                    return filesystem::is_regular_file(path) &&
                        !filesystem::is_symlink(path);
                },
                [output]
                (const string &file, const string &line)
                {
                    (*output)(file, line);
                }
            );
            return 0;
        };
}
