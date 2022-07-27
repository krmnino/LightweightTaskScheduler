#ifndef BTSCMD
#define BTSCMD

#include <string>
#include <iostream>

#include "Task.hpp"

namespace BTS{
class CommandLine{
private:
    void process_command(std::string&);
public:
    CommandLine();
    ~CommandLine();

    void run();
};
}

#endif // BTSCMD