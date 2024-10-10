#include <string>
#include <filesystem>

#include "filesys.h"

using namespace std;

void iterateDirectory(
    const string &path,
    filter_func_type filter,
    callback_func_type callback
    )
{
   for(const auto& p: filesystem::recursive_directory_iterator(path)) {
        if (filter(p.path())) {
            callback(p.path());
        }
    }
}
