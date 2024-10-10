#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "functor.h"
#include "filesys.h"

void grep(
    const std::string & path,
    const std::string & query,
    filter_func_type filter,
    output_find_func_type output
    );

#endif