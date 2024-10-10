
#include "application.h"
#include "filesys.h"
#include "threadpool.h"

using namespace std;

void grep(
    const string & path,
    const string & query,
    filter_func_type filter,
    output_find_func_type output
    )
{// not necessary to check the input parameters, because this is private function
 // and behaviour has been checked in factory
    iterateDirectory(
        path,
        filter,
        [&query, &output](const string &f)
        {
            // create thread poll, 
            // to unitlize all available Cores 
            // use std::thread::hardware_concurrency())
            // what allows creating optimal number of the threads
            static ThreadPool tp(std::thread::hardware_concurrency());
            TextQuery ft{query, output};
            // wait the available thread
            // no sence to add the task if it can not be processed
            // due to the threads unavailability.
            tp.waitAvailability();

            auto task=
                make_shared<packaged_task<void()>>(
                    bind(
                        [ft, f](const std::string& file){ ft(file); },
                        f
                    )
                );
            tp.push(task);
        }
    );
}
