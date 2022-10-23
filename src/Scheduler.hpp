#ifndef TSSSCH
#define TSSSCH

#include <string>
#include <iostream>
#include <map>
#include <thread>
#include <filesystem>
#include <functional>

#include "Task.hpp"
#include "ConfigLoader.hpp"

namespace ts{

class Scheduler{
private:
    long long n_tasks;
    std::string top_level_dir;
    std::string tasks_dir;
    std::string scripts_dir;
    std::map<std::string, Task*> task_registry;
    std::map<int, std::thread> thread_collection;

public:
    Scheduler(std::string&, std::string&, std::string&);
    Scheduler();
    ~Scheduler();
    void launch_task_thread(std::string&);
    int generate_task_id(Task*);
    void run();
    void help();
};

} // namespace ts

#endif // TSSCH