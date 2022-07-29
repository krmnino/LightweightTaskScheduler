#ifndef TSTASK
#define TSTASK

#include <string>
#include <iomanip>

#include "ConfigLoader.hpp"

namespace ts{
enum class TaskStatus {
	FINISHED,
	ERROR,
	QUEUED,
	RUNNING,
};

enum class TaskValidate {
	OK,
	MISSING_REQUIRED_KEYVALS,
	SCRIPT_NOT_FOUND,
	BAD_FREQUENCY_VALUE,
};


class Task{
private:
    std::tm datetime;
    std::string name;
    std::string description;
    std::string script_filename;
    std::string frequency;
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
    //std::string get_datetime(void);
    std::string get_output(void);
};

TaskValidate validate_task_parms(cl::Config*, std::string);
} // namespace ts

#endif // TSTASK