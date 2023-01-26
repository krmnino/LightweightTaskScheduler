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
    void stop_thread(Task*);

    static void launch_thread(Task* t){
        std::unique_lock<std::mutex> lock(t->mtx);
        t->set_running_thread_flag(true);
        time_t execution_datetime = t->get_execution_datetime(false);
        std::chrono::_V2::system_clock::time_point end_time = std::chrono::system_clock::now();
        while(!t->cv.wait_until(lock, std::chrono::system_clock::from_time_t(execution_datetime), [t] {return !t->get_running_thread_flag();})){
            // Before running task, update its status
            t->set_status(TaskStatus::RUNNING);
            // Run the task
            t->run_task();
            // Update next execution time based on frequency
            t->update_execution_datetime();
            // If task frequency is Once, then it is finished
            if(t->get_frequency() == "Once"){
                t->set_status(TaskStatus::FINISHED);
                t->set_running_thread_flag(false);
            }
            else{
                // Otherwise, set it to queued status again
                t->set_status(TaskStatus::QUEUED);
                execution_datetime = t->get_execution_datetime(false);
            }
        }
    }

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
    const std::string& get_current_path(void);
    unsigned int get_n_tasks(void);
    const Task* get_task(std::string&);
    void set_running_thread_flag(bool);
};

} // namespace ts

#endif // LTS_SCHEDULER