
#include <filesystem>
#include <iostream>
#include "appfactory.h"

using namespace std;
 
int main(int argc, char *argv[])
{
    int ret= 0;
    try
    {
        auto app = createApplication(argc, argv);
        ret= app();
    }
    catch(const exception& e)
    {
        std::cout << e.what() << endl;
    }
    return ret;
}