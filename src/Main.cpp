#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "CommandLine.hpp"
#include "Task.hpp"

pid_t create_proc(const char* cmd, std::string& out_buff){
    pid_t pid = fork();
    int status;
    if(pid < 0){
        // failed fork
        return -1;
    }
    else if(pid == 0){
        //child proc
        /*
        std::string program = "sh";
        std::string path = "/home/kurt/remote/github/BatchTaskScheduler/src/hello.sh";

        char* const command[] = {(char*)program.c_str(), (char*)path.c_str(), NULL};
        execv("/bin/sh", command);
        printf("Return not expected. Must be an execv error.n");
        */
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            out_buff += buffer.data();
        }
    }
    // parent proc
    return pid;
}

std::string create_popen(const char* cmd){
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(){
    BTS::Task* t = new BTS::Task("my task", "sh hello.sh");
    t->launch();
    delete t;
    //BTS::CommandLine* cl = new BTS::CommandLine();
    //cl->run();
    //delete cl;
    //std::string out = "";
    //create_proc("sh hello.sh", out);
    //std::cout << out << std::endl;
    return 0;
}