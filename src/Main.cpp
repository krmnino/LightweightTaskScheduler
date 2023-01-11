#include <iomanip>

#include "Scheduler.hpp"
#include "Task.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;

int main(int argc, char* argv[]){
    cl::Config* main_config = new cl::Config("config/main_config.cl");

    std::string top_level_dir = main_config->get_value("TopLevel")->get_data<std::string>();
    std::string tasks_dir = main_config->get_value("TasksDir")->get_data<std::string>();
    std::string scripts_dir = main_config->get_value("ScriptsDir")->get_data<std::string>();

    delete main_config;

    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();
    s->Scheduler_init(top_level_dir, tasks_dir, scripts_dir);
    s->Scheduler_delete();

    return 0;
}