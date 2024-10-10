cmake_minimum_required(VERSION 3.16.3)

project(grepapp)
file(DOWNLOAD
    https://raw.githubusercontent.com/iusyk/threadpool/main/threadpool.h
    threadpool.h)
file(DOWNLOAD
    https://raw.githubusercontent.com/iusyk/threadpool/main/threadpool.cpp
    threadpool.cpp)
find_package(grepapp)
add_executable ( grepapp main.cpp highlightconsole.cpp threadpool.cpp appfactory.cpp functor.cpp filesys.cpp application.cpp)
target_link_libraries ( grepapp )
