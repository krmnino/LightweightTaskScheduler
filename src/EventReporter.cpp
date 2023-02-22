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

void EventReporter::EventReporter_init(){
    this->events_recorded = 0;
}

void EventReporter::log_event(EventType event_type, std::string& event_message){
    time_t time_now;
    std::time(&time_now);
    this->event_registry.push_back(Event(time_now, event_type, event_message));
    this->events_recorded++;
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

std::string EventReporter::generate_load_task_msg(ts::ValidationCode vc_code, std::string& task_fn, cl::Config* task_config){
    std::string event_message = "";
    switch(vc_code){
	case ValidationCode::MISSING_NAME_KEYVAL:
        event_message = "The configuration file \""  + task_fn + "\" does not contain the "
                        "required key-value pair Name.";
        break;
	case ValidationCode::MISSING_SCRIPTFN_KEYVAL:
        event_message = "The configuration file \""  + task_fn + "\" does not contain the "
                        "required key-value pair ScriptFilename.";
        break;
	case ValidationCode::MISSING_FREQUENCY_KEYVAL:
        event_message = "The configuration file \""  + task_fn + "\" does not contain the "
                        "required key-value pair Frequency.";
        break;
	case ValidationCode::MISSING_DATETIME_KEYVAL:
        event_message = "The configuration file \""  + task_fn + "\" does not contain the "
                        "required key-value pair Datetime.";
        break;
	case ValidationCode::SCRIPT_NOT_FOUND:
        event_message = "The configuration file \""  + task_fn + "\" specifies the script file \"" +
                        task_config->get_value("ScriptFilename")->get_data<std::string>() + "\" " + 
                        "that could not be found.";
        break;
	case ValidationCode::BAD_FREQUENCY_VALUE:
        event_message = "An invalid frequency value of \"" + 
                        task_config->get_value("Frequency")->get_data<std::string>() +
                        "\" was specified in the configuration file: " + task_fn;
        break;
    case ValidationCode::INCOMPATIBLE_ONCE_FREQ_DATETIME_FORMAT:
        event_message = "The configuration file \"" + task_fn + "\" specifies a datetime value of \"" + 
                        task_config->get_value("Datetime")->get_data<std::string>() +
                        "\" that has an invalid format for a Once frequency.";
        break;
    case ValidationCode::INCOMPATIBLE_DAILY_FREQ_DATETIME_FORMAT:
        event_message = "The configuration file \"" + task_fn + "\" specifies a datetime value of \"" + 
                        task_config->get_value("Datetime")->get_data<std::string>() +
                        "\" that has an invalid format for a Daily frequency.";
        break;
    case ValidationCode::INCOMPATIBLE_WEEKLY_FREQ_DATETIME_FORMAT:
        event_message = "The configuration file \"" + task_fn + "\" specifies a datetime value of \"" + 
                        task_config->get_value("Datetime")->get_data<std::string>() +
                        "\" that has an invalid format for a Weekly frequency.";
        break;
    case ValidationCode::INCOMPATIBLE_MONTHLY_FREQ_DATETIME_FORMAT:
        event_message = "The configuration file \"" + task_fn + "\" specifies a datetime value of \"" + 
                        task_config->get_value("Datetime")->get_data<std::string>() +
                        "\" that has an invalid format for a Monthly frequency.";
        break;
    case ValidationCode::INCOMPATIBLE_YEARLY_FREQ_DATETIME_FORMAT:
        event_message = "The configuration file \"" + task_fn + "\" specifies a datetime value of \"" + 
                        task_config->get_value("Datetime")->get_data<std::string>() +
                        "\" that has an invalid format for a Yearly frequency.";
        break;
    case ValidationCode::PASSED_DATETIME:
        event_message = "The configuration file \"" + task_fn + "\" specifies a datetime value of \"" + 
                        task_config->get_value("Datetime")->get_data<std::string>() +
                        "\" that is in the past.";
        break;
    case ValidationCode::BAD_HMS_LENGTH:
        event_message = "The HH:MM:SS section of datetime value in the configuration file \"" +
                        task_fn  + "\" has an invalid length.";
        break;
    case ValidationCode::BAD_YYYYMMDD_LENGTH:
        event_message = "The YYYY-MM-DD section of datetime value in the configuration file \"" +
                        task_fn  + "\" has an invalid length.";
        break;
    case ValidationCode::BAD_NUMBER_CHARACTER:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains a character that is expected to be an integer."; 
        break;
    case ValidationCode::MISSING_DATETIME_COLON:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains a character that is expected to be a colon \":\"."; 
        break;
    case ValidationCode::MISSING_DATETIME_DASH:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains a character that is expected to be a dash \"-\"."; 
        break;
    case ValidationCode::MISSING_DATETIME_SPACE:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains a character that is expected to be a space \" \".";
        break;
    case ValidationCode::BAD_WDAY:
        event_message = "The WDAY section of datetime value in the configuration file \"" +
                        task_fn  + "\" is not a valid full or abbreviated weekday name.";
        break;
    case ValidationCode::YEAR_OUT_OF_RANGE:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains an out of range year value."; 
        break;
    case ValidationCode::MONTH_OUT_OF_RANGE:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains an out of range month value.";
        break;
    case ValidationCode::DAY_OUT_OF_RANGE:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains an out of range day value.";
        break;
    case ValidationCode::HOURS_OUT_OF_RANGE:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains an out of range hours value.";
        break;
    case ValidationCode::MINUTES_OUT_OF_RANGE:
        event_message = "The datetime value specified in the configuration file \"" + 
                        task_fn  + "\" contains an out of range minutes value.";
        break;
    case ValidationCode::SECONDS_OUT_OF_RANGE:
        event_message = "The datetime value specified in the configuration file \"" + 
                    task_fn  + "\" contains an out of range seconds value.";
        break;
    default:
        event_message = "An undefined error has occured.";
    }
    return event_message;
}

}