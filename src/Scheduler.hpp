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
    unsigned int n_tasks;
    std::string exec_path;
    std::map<std::string, Task*> task_registry;
    std::map<unsigned int, std::thread> thread_collection;
    
    Scheduler() {};
    unsigned int generate_task_id(Task*);

public:
    static Scheduler* Scheduler_get_instance(void){
        if(scheduler_ptr == nullptr){
            scheduler_ptr = new Scheduler();
        }
        return scheduler_ptr;
    }
    static void Scheduler_end_instance(void){
        delete scheduler_ptr;
    }

    Scheduler(const Scheduler& s) = delete;
    void Scheduler_init(void);
    void Scheduler_delete(void);
    void obtain_exec_path(void);
    void launch_task_thread(std::string&);
    void load_tasks_from_dir(void);
    void load_task(std::string&);
    void remove_task(std::string&);
    const std::string& get_current_path(void);
    unsigned int get_n_tasks(void);
};

} // namespace ts

#endif // LTS_SCHEDULER