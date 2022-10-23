#include <iomanip>

#include "Scheduler.hpp"
#include "Task.hpp"

//pid_t create_proc(const char* cmd, std::string& out_buff){
//    pid_t pid = fork();
//    int status;
//    if(pid < 0){
//        // failed fork
//        return -1;
//    }
//    else if(pid == 0){
//        //child proc
//        /*
//        std::string program = "sh";
//        std::string path = "/home/kurt/remote/github/BatchTaskScheduler/src/hello.sh";
//
//        char* const command[] = {(char*)program.c_str(), (char*)path.c_str(), NULL};
//        execv("/bin/sh", command);
//        printf("Return not expected. Must be an execv error.n");
//        */
//        std::array<char, 128> buffer;
//        std::string result;
//        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//        if (!pipe) {
//            throw std::runtime_error("popen() failed!");
//        }
//        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//            out_buff += buffer.data();
//        }
//    }
//    // parent proc
//    return pid;
//}
//
//std::string create_popen(const char* cmd){
//    std::array<char, 128> buffer;
//    std::string result;
//    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//    if (!pipe) {
//        throw std::runtime_error("popen() failed!");
//    }
//    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//        result += buffer.data();
//    }
//    return result;
//}

int main(){
    
    cl::Config* main_config = new cl::Config("config/main_config.cl");
    std::string top_level_dir = main_config->get_value("TopLevel")->get_data<std::string>();
    std::string tasks_dir = main_config->get_value("TasksDir")->get_data<std::string>();
    std::string scripts_dir = main_config->get_value("ScriptsDir")->get_data<std::string>();
    delete main_config;

    ts::Scheduler* s = new ts::Scheduler(top_level_dir, tasks_dir, scripts_dir);
    delete s;

    //ts::Task* t = new ts::Task("my task", "sh hello.sh");
    //t->launch();
    //std::cout << t->get_output() << std::endl;
    //delete t;
    //BTS::CommandLine* cl = new BTS::CommandLine();
    //cl->run();
    //delete cl;
    //std::string out = "";
    //create_proc("sh hello.sh", out);
    //std::cout << out << std::endl;
    return 0;
}