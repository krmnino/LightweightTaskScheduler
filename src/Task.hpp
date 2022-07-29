#ifndef TSTASK
#define TSTASK

#include <string>

#include "ConfigLoader.hpp"

namespace ts{
class Task{
private:
    std::string name;
    std::string description;
    std::string script_filename;
    std::string frequency;
    std::string datetime;
    std::string output;
    pid_t pid;
    int status;
public:
    Task();
    Task(std::string, std::string, std::string);
    ~Task();
    void launch();
    std::string get_name(void);
    std::string get_description(void);
    std::string get_frequency(void);
    std::string get_datetime(void);
    std::string get_output(void);
};

bool validate_task_parms(cl::Config*, std::string);
} // namespace ts

#endif // TSTASK