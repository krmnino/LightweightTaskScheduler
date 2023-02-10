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
#include "Task.hpp"
#include "ConfigLoader.hpp"

namespace ts{

struct Event{
    const time_t event_time;
    EventType type;
    std::string message;

    Event(time_t in_event_time, EventType in_type, std::string in_message) :
        event_time{event_time},
        type{in_type},
        message{in_message}
    {}

    Event(const Event& src) :
        event_time{src.event_time},
        type{src.type},
        message{src.message}
    {}

    ~Event() {}
};

class Scheduler{
private:
    static Scheduler* scheduler_ptr;
    unsigned int n_tasks;
    std::string exec_path;
    std::map<std::string, Task*> task_registry;
    std::deque<Event> event_registry;
    
    Scheduler() {}
    unsigned int generate_task_id(Task*);
    std::string generate_TaskValidate_msg(ts::TaskValidate, cl::Config*);

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
    void load_tasks_from_dir(void);
    void load_task(std::string&);
    void remove_task(std::string&);
    bool task_exists(std::string&);
    const std::string& get_current_path(void);
    unsigned int get_n_tasks(void);
    Task* get_task(std::string&);
    void log_event(EventType, std::string&);
    Event get_last_event(void);
    void publish_last_event(void);
};

} // namespace ts

#endif // LTS_SCHEDULER