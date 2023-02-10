#include "EventReporter.hpp"

namespace ts{

Event::Event(time_t in_event_time, EventType in_type, std::string in_message) :
    event_time{event_time},
    type{in_type},
    message{in_message}
{}

Event::Event(const Event& src) :
    event_time{src.event_time},
    type{src.type},
    message{src.message}
{}

Event::~Event() {}

const time_t Event::get_event_time(){
    return this->event_time;
}
EventType Event::get_type(){
    return this->type;
}

std::string& Event::get_message(){
    return this->message;
}


void EventReporter::log_event(EventType event_type, std::string& event_message){
    time_t time_now;
    std::time(&time_now);
    this->event_registry.push_back(Event(time_now, event_type, event_message));
}

Event EventReporter::get_last_event(void){
    Event ret = this->event_registry.back();
    return ret;
}

void EventReporter::publish_last_event(void){
    Event last_event = this->event_registry.back();
    switch(last_event.get_type()){
        case EventType::INFO:
            std::cout << "[INFO]: ";
            break;
        case EventType::WARNING:
            std::cout << "[WARNING]: ";
            break;
        case EventType::ERROR:
            std::cout << "[ERROR]: ";
            break;
        default:
            break;
    }
    std::cout << last_event.get_message() << std::endl;
}

}