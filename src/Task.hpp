#ifndef BTSTASK
#define BTSTASK

#include <string>

namespace BTS{
class Task{
private:
    std::string title;
    std::string date;
    std::string script_path;
    std::string output;
    pid_t pid;
    int priority;
public:
    Task();
    Task(std::string, std::string);
    ~Task();
    void launch();
};
} // namespace BTS

#endif // BTSTASK