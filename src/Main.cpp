#include <iomanip>

#include "Scheduler.hpp"
#include "CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int main(int argc, char* argv[]){
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();
    ts::CommandLine* c = ts::CommandLine::CommandLine_get_instance();
    
    // Initialize Scheduler data members
    s->Scheduler_init();
    
    // Obtain directory where LTS executable , scripts and tasks directories live
    s->obtain_exec_path();

    // Load all Task configuration files from the task directory
    s->load_tasks_from_dir();
    std::string fn = "cat_test.cl";
    s->load_task(fn);
    
    // Initialize and launch command line 
    c->CommandLine_init();
    c->start();

    // Delete any tasks in Scheduler's task registry
    s->Scheduler_delete();
    c->CommandLine_delete();
    
    return 0;
}