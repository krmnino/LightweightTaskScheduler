#include <iomanip>

#include "Scheduler.hpp"
#include "CommandLine.hpp"
#include "EventReporter.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;

int main(int argc, char* argv[]){
    ts::EventReporter* e = ts::EventReporter::EventReporter_get_instance();
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();
    ts::CommandLine* c = ts::CommandLine::CommandLine_get_instance();
    
    // Initialize Scheduler and CommandLine data members
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e);
    
    // Obtain directory where LTS executable , scripts and tasks directories live
    s->obtain_exec_path();

    // Load all Task configuration files from the task directory
    s->load_tasks_from_dir();
    
    // Initialize and launch command line 
    c->start();

    // Delete Scheduler and CommandLine
    s->Scheduler_delete();
    c->CommandLine_delete();

    return 0;
}