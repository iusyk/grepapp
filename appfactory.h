#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <string>
#include <functional>
#include "functor.h"

typedef std::function<int(void)> app_type;

app_type createApplication(
    int argc,
    char *argv[]
    );

#endif