#ifndef __FILESYS_H__
#define __FILESYS_H__

#include <functional>

typedef std::function<void(const std::string &)> callback_func_type;
typedef std::function<bool(const std::string &)> filter_func_type;

void iterateDirectory(
    const std::string &path,
    filter_func_type filter,
    callback_func_type callback
    );

#endif