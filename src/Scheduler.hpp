#ifndef BTSCMD
#define BTSCMD

#include <string>
#include <iostream>
#include <map>

#include "Task.hpp"
#include "ConfigLoader.hpp"

namespace ts{
class Scheduler{
private:
    std::string top_level_dir;
    std::string tasks_dir;
    std::string scripts_dir;
    std::map<std::string, Task*> tasks_registry;
public:
    Scheduler(std::string&, std::string&, std::string&);
    Scheduler();
    ~Scheduler();

    void load_task();
    void run();
    void help();
};
}

#endif // BTSCMD