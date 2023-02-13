#include <iomanip>

#include "Scheduler.hpp"
#include "CommandLine.hpp"
#include "EventReporter.hpp"

ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;
ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;

int main(int argc, char* argv[]){
    ts::EventReporter* e = ts::EventReporter::EventReporter_get_instance();
    ts::CommandLine* c = ts::CommandLine::CommandLine_get_instance();
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();
    
    // Initialize Scheduler and CommandLine data members
    e->EventReporter_init();
    c->CommandLine_init(e);
    s->Scheduler_init(e);
    
    // Obtain directory where LTS executable , scripts and tasks directories live
    s->obtain_exec_path();

    // Load all Task configuration files from the task directory
    s->load_tasks_from_dir();
    
    // Initialize and launch command line 
    c->start();

    // Delete Scheduler contents
    s->Scheduler_delete();

    s->Scheduler_end_instance();
    c->CommandLine_end_instance();
    e->EventReporter_end_instance();

    return 0;
}