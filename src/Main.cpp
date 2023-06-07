#include <iomanip>

#include "Scheduler.hpp"
#include "CommandLine.hpp"
#include "EventReporter.hpp"

lts::CommandLine* lts::CommandLine::command_line_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;
lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;

int main(int argc, char* argv[]){
    lts::EventReporter* e = lts::EventReporter::EventReporter_get_instance();
    lts::CommandLine* c = lts::CommandLine::CommandLine_get_instance();
    lts::Scheduler* s = lts::Scheduler::Scheduler_get_instance();
    
    // Initialize Scheduler and CommandLine data members
    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);
    
    // Obtain directory where LTS executable , scripts and tasks directories live
    s->obtain_exec_path();

    // Load all Task configuration files from the task directory
    s->load_all_tasks();
    
    // Initialize and launch command line 
    c->start();

    // Delete Scheduler contents
    s->Scheduler_delete();

    s->Scheduler_end_instance();
    c->CommandLine_end_instance();
    e->EventReporter_end_instance();

    return 0;
}