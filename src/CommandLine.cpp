#include "CommandLine.hpp"

namespace BTS{
CommandLine::CommandLine(){

}

CommandLine::~CommandLine(){}

void CommandLine::run(){
    std::string input;
    while(true){
        std::cout << ">> ";
        std::cin >> input;
        if(input == "exit"){
            break;
        }
        else if(input == "help"){
            break;
        }
    }
}
}