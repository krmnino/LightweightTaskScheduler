#ifndef LTS_SCHEDULER
#define LTS_SCHEDULER

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
    static Scheduler* scheduler_ptr;
    long long n_tasks;
    std::string top_level_dir;
    std::string tasks_dir;
    std::string scripts_dir;
    std::map<std::string, Task*> task_registry;
    std::map<int, std::thread> thread_collection;
    
    Scheduler() {};

public:
    static Scheduler* Scheduler_get_instance(){
        if(scheduler_ptr == nullptr){
            scheduler_ptr = new Scheduler();
        }
        return scheduler_ptr;
    }

    Scheduler(const Scheduler& s) = delete;
    void Scheduler_init(std::string&, std::string&, std::string&);
    void Scheduler_delete();
    void launch_task_thread(std::string&);
    int generate_task_id(Task*);
    void run();
    void help();
};

} // namespace ts

#endif // LTS_SCHEDULER