#ifndef LTS_SCHEDULER
#define LTS_SCHEDULER

#include <string>
#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <filesystem>
#include <functional>
#include <deque>

#include "Constants.hpp"
#include "ConfigLoader.hpp"
#include "Task.hpp"
#include "EventReporter.hpp"

namespace ts{

class Scheduler{
private:
    std::map<std::string, Task*> task_registry;
    std::string exec_path;
    static Scheduler* scheduler_ptr;
    EventReporter* event_reporter_ptr;
    unsigned int n_tasks;
    
    Scheduler() {}
    unsigned int generate_task_id(Task*);
    Task* get_task_from_registry(std::string&);

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
    void Scheduler_init(EventReporter*);
    void Scheduler_delete(void);
    void obtain_exec_path(void);
    void load_tasks_from_dir(void);
    void load_task(std::string&);
    void remove_task(std::string&);
    bool task_exists(std::string&);
    std::string display_registry(void);
    std::string display_task(std::string&);
    std::string display_scheduler_status(void);
    const std::string& get_current_path(void);
    unsigned int get_n_tasks(void);
    const Task* get_task(std::string&) const;
    unsigned int get_n_tasks_by_status(ts::TaskStatus);
};

} // namespace ts

#endif // LTS_SCHEDULER