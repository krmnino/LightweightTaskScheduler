#include <iomanip>

#include "Scheduler.hpp"
#include "Task.hpp"

int main(int argc, char* argv[]){
    cl::Config* main_config = new cl::Config("config/main_config.cl");

    std::string top_level_dir = main_config->get_value("TopLevel")->get_data<std::string>();
    std::string tasks_dir = main_config->get_value("TasksDir")->get_data<std::string>();
    std::string scripts_dir = main_config->get_value("ScriptsDir")->get_data<std::string>();

    delete main_config;

    ts::Scheduler* s = new ts::Scheduler(top_level_dir, tasks_dir, scripts_dir);
    delete s;

    return 0;
}