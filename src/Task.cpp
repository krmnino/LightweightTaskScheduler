#include <unistd.h>
#include <array>
#include <memory>
#include <exception>
#include <filesystem>

#include "Task.hpp"

namespace ts{

Task::Task(std::string name, std::string script_filename, std::string frequency){
    this->name = name;
    this->script_filename = script_filename;
    this->output = "";
}

Task::Task(){}

Task::~Task() {}

void Task::launch(void){
    pid_t pid = fork();
    if(pid < 0){
        throw std::runtime_error("fork() failed!");
    }
    else if(pid == 0){
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(this->script_filename.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            this->output += buffer.data();
        }
    }
    this->pid = pid;
}

std::string Task::get_name(void){
    return this->name;
}

std::string Task::get_description(void){
    return this->description;
}

std::string Task::get_frequency(void){
    return this->frequency;
}

time_t Task::get_starting_date(void){
    return this->starting_date;
}

time_t Task::get_task_creation_date(void){
    return this->task_creation_date;
}

time_t Task::get_execution_date(void){
    return this->execution_date;
}

std::string Task::get_output(void){
    return this->output;
}

std::string Task::get_starting_date_fmt(void){
    return std::string(ctime(&this->starting_date));
}

std::string Task::get_task_creation_date_fmt(void){
    return std::string(ctime(&this->task_creation_date));
}

std::string Task::get_execution_date_fmt(void){
    return std::string(ctime(&this->execution_date)); 
}

DatetimeValidate validate_hms(std::string hms){
    if(hms.length() != 8){
        return DatetimeValidate::BAD_HMS_LENGTH;
    }
    unsigned int num;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
    num = hms.at(0);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = hms.at(1);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    // Validate range of hour
    hours = ((hms.at(0) & 0x0F) * 10) + 
            (hms.at(1) & 0x0F);
    if(hours < 0 | hours > 9999){
        return DatetimeValidate::HOURS_OUT_OF_RANGE;
    }
    if(hms.at(2) != ':'){
        return DatetimeValidate::MISSING_COLON;
    }
    num = hms.at(3);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = hms.at(4);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    // Validate range of minute
    hours = ((hms.at(3) & 0x0F) * 10) + 
            (hms.at(4) & 0x0F);
    if(hours < 0 | hours > 9999){
        return DatetimeValidate::MINUTES_OUT_OF_RANGE;
    }
    if(hms.at(5) != ':'){
        return DatetimeValidate::MISSING_COLON;
    }
    num = hms.at(6);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = hms.at(7);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    // Validate range of second
    hours = ((hms.at(6) & 0x0F) * 10) + 
            (hms.at(7) & 0x0F);
    if(hours < 0 | hours > 9999){
        return DatetimeValidate::SECONDS_OUT_OF_RANGE;
    }
    return DatetimeValidate::OK;
}

DatetimeValidate validate_wday(std::string wday){
    if(wday != "Mon" && wday != "Monday" && 
       wday != "Tue" && wday != "Tuesday" &&
       wday != "Wed" && wday != "Wednesday" &&
       wday != "Thu" && wday != "Thursday" &&
       wday != "Fri" && wday != "Friday" &&
       wday != "Sat" && wday != "Saturday" &&
       wday != "Sun" && wday != "Sunday"){
        return DatetimeValidate::BAD_WDAY;
    }
    return DatetimeValidate::OK;
}

DatetimeValidate validate_yyyymmdd(std::string yyyymmdd){
    if(yyyymmdd.length() != 10){
        return DatetimeValidate::BAD_YYYYMMDD_LENGTH;
    }
    unsigned int num;
    unsigned int year;
    unsigned int month;
    unsigned int day;
    // Validate year individual digits
    num = yyyymmdd.at(0);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(1);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(2);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(3);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    // Validate range of year
    year = ((yyyymmdd.at(0) & 0x0F) * 1000) + 
           ((yyyymmdd.at(1) & 0x0F) * 100) + 
           ((yyyymmdd.at(2) & 0x0F) * 10) + 
           (yyyymmdd.at(3) & 0x0F);
    if(year < 0 | year > 9999){
        return DatetimeValidate::YEAR_OUT_OF_RANGE;
    }
    // Check if dash delimiter exists
    if(yyyymmdd.at(4) != '-'){
        return DatetimeValidate::MISSING_DASH;
    }
    // Validate month individual characters
    num = yyyymmdd.at(5);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(6);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    // Validate range of months
    month = ((yyyymmdd.at(5) & 0x0F) * 10) + 
            (yyyymmdd.at(6) & 0x0F);
    if(month < 1 | month > 12){
        return DatetimeValidate::MONTH_OUT_OF_RANGE;
    }
    // Check if dash delimiter exists
    if(yyyymmdd.at(7) != '-'){
        return DatetimeValidate::MISSING_DASH;
    }
    // Validate day individual characters
    num = yyyymmdd.at(8);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(9);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    // Validate range of days by month
    day = ((yyyymmdd.at(8) & 0x0F) * 10) + 
          (yyyymmdd.at(9) & 0x0F);
    switch (month)
    {
    case JANUARY:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case FEBRARY:
        // If year is a leap year, then up to 29 days
        if(year % 4 == 0){
            if(day < 1 || day > 29){
                return DatetimeValidate::DAY_OUT_OF_RANGE;
            }
        }
        else{
            if(day < 1 || day > 28){
                return DatetimeValidate::DAY_OUT_OF_RANGE;
            }
        }
        break;
    case MARCH:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case APRIL:
        if(day < 1 || day > 30){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case MAY:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case JUNE:
        if(day < 1 || day > 30){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case JULY:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    case AUGUST:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }       
        break;
    case SEPTEMBER:
        if(day < 1 || day > 30){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    case OCTOBER:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    case NOVEMBER:
        if(day < 1 || day > 30){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    case DECEMBER:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    default:
        return DatetimeValidate::INVALID_DATETIME_INPUT;
        break;
    }
    return DatetimeValidate::OK;
}

DatetimeValidate validate_mmdd(std::string mmdd){
    if(mmdd.length() != 5){
        return DatetimeValidate::BAD_MMDD_LENGTH;
    }
    
    time_t today = init_day();
    std::tm* today_struct = std::gmtime(&today);

    unsigned int year = today_struct->tm_year;
    unsigned int num;
    unsigned int month;
    unsigned int day;

    // Validate month individual characters
    num = mmdd.at(0);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = mmdd.at(1);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    // Validate range of months
    month = ((mmdd.at(0) & 0x0F) * 10) + 
            (mmdd.at(1) & 0x0F);
    if(month < 1 | month > 12){
        return DatetimeValidate::MONTH_OUT_OF_RANGE;
    }
    // Check if dash delimiter exists
    if(mmdd.at(2) != '-'){
        return DatetimeValidate::MISSING_DASH;
    }
    // Validate day individual characters
    num = mmdd.at(3);
    if(num < '0' | num > '3'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    num = mmdd.at(4);
    if(num < '0' | num > '9'){
        return DatetimeValidate::BAD_NUMBER_CHARACTER;
    }
    // Validate range of days by month
    day = ((mmdd.at(3) & 0x0F) * 10) + 
          (mmdd.at(4) & 0x0F);
    switch (month)
    {
    case JANUARY:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case FEBRARY:
        // If year is a leap year, then up to 29 days
        if(year % 4 == 0){
            if(day < 1 || day > 29){
                return DatetimeValidate::DAY_OUT_OF_RANGE;
            }
        }
        else{
            if(day < 1 || day > 28){
                return DatetimeValidate::DAY_OUT_OF_RANGE;
            }
        }
        break;
    case MARCH:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case APRIL:
        if(day < 1 || day > 30){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case MAY:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case JUNE:
        if(day < 1 || day > 30){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }
        break;
    case JULY:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    case AUGUST:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }       
        break;
    case SEPTEMBER:
        if(day < 1 || day > 30){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    case OCTOBER:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    case NOVEMBER:
        if(day < 1 || day > 30){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    case DECEMBER:
        if(day < 1 || day > 31){
            return DatetimeValidate::DAY_OUT_OF_RANGE;
        }    
        break;
    default:
        return DatetimeValidate::INVALID_DATETIME_INPUT;
        break;
    }
    return DatetimeValidate::OK;
}

time_t init_day(){
    std::time_t time_now;
    std::tm* struct_time_now;

    // Get current time
    std::time(&time_now);
    // Convert to struct
    struct_time_now = std::gmtime(&time_now);

    // Get hours, minutes, and seconds. Convert to seconds 
    int hrs_2_sec = (struct_time_now->tm_hour + TIMEZONE) * 60 * 60;
    int min_2_sec = struct_time_now->tm_min * 60;
    int sec = struct_time_now->tm_sec;

    // Add converted hours and minutes to total seconds
    sec += hrs_2_sec + min_2_sec;

    // Subtract time
    time_now -= sec;

    return time_now;
}

time_t init_day_add_hms(std::string hms){
    if(validate_hms(hms) != DatetimeValidate::OK){
        return 0;
    }
    std::tm time_input_hms;
    std::istringstream hms_ss(hms.c_str());
    hms_ss >> std::get_time(&time_input_hms, "%H:%M:%S");

    std::time_t time_hms = mktime(&time_input_hms);

    // Get hours, minutes, and seconds. Convert to seconds 
    int hrs_2_sec = time_input_hms.tm_hour * 60 * 60;
    int min_2_sec = time_input_hms.tm_min * 60;
    int sec = time_input_hms.tm_sec;

    // Add converted hours and minutes to total seconds
    sec += hrs_2_sec + min_2_sec;

    std::time_t time_now = init_day();

    time_now += sec;

    return time_now;
}

time_t init_day_add_dhms(int d, std::string hms){
    if(validate_hms(hms) != DatetimeValidate::OK | d < 0){
        return 0;
    }
    std::tm time_input_hms;
    std::istringstream hms_ss(hms.c_str());
    hms_ss >> std::get_time(&time_input_hms, "%H:%M:%S");

    std::time_t time_hms = mktime(&time_input_hms);

    // Get hours, minutes, and seconds. Convert to seconds 
    time_t days_2_sec = d * 24 * 60 * 60;
    int hrs_2_sec = time_input_hms.tm_hour * 60 * 60;
    int min_2_sec = time_input_hms.tm_min * 60;
    int sec = time_input_hms.tm_sec;

    // Add converted days, hours, and minutes to total seconds
    sec += days_2_sec + hrs_2_sec + min_2_sec;

    std::time_t time_now = init_day();

    time_now += sec;

    return time_now;
}

time_t init_day_add_wdhms(std::string wday, std::string hms){
    if(validate_wday(wday) != DatetimeValidate::OK){
        return 0;
    }
    if(validate_hms(hms) != DatetimeValidate::OK){
        return 0;
    }
    // Concatenate wday with hms
    wday += " " + hms;
    std::tm time_input_whms;
    std::istringstream whms_ss(wday.c_str());
    whms_ss >> std::get_time(&time_input_whms, "%a %H:%M:%S");
    
    // Get current time and convert to struct
    std::time_t time_now = init_day();
    std::tm* time_now_struct;
    time_now_struct = gmtime(&time_now);

    // Calculate days until desired weekday
    int diff_day;
    if(time_now_struct->tm_wday == time_input_whms.tm_wday){
        std::time_t now;
        std::time_t now_add_hms = init_day_add_hms(hms);
        std::time(&now);
        if(now < now_add_hms){
            time_now = now_add_hms;
        }
        else{
            time_now = init_day_add_dhms(DAYS_IN_WEEK, hms);
        }
    }
    else if(time_now_struct->tm_wday > time_input_whms.tm_wday){
        diff_day = time_now_struct->tm_wday - time_input_whms.tm_wday;
        diff_day = DAYS_IN_WEEK - diff_day;
        time_now = init_day_add_dhms(diff_day, hms);
    }
    else{
        diff_day = time_input_whms.tm_wday - time_now_struct->tm_wday;
        time_now = init_day_add_dhms(diff_day, hms);
    }
    return time_now;
}

DatetimeFormat get_datetime_format(std::string datetime){
    // Each character in datetime will have a score
    // Numbers : 1 pts
    // Dash: 2 pts
    // Colon: 4 pts
    // Space: 6 pts
    // Letters: 8 pts
    // A valid datetime will have a unique point sum which will
    //   then be assigned to their specific validation function.
    int point_sum = 0;
    char c;
    for(int i = 0; i < datetime.length(); i++){
        c = datetime.at(i);
        switch(c){
            case ' ':
                point_sum += 6;
                break;
            case '-':
                point_sum += 2;
                break;
            case ':':
                point_sum += 4;
                break;
            default:
                if((c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a)){
                    point_sum += 8; // Alphabetic char
                }
                else if(c >= 0x30 && c <= 0x39){
                    point_sum += 1; // Number char
                }
                else{
                    point_sum += 0; // Invalid char
                }
                break;
        }
    }

    int space_idx;
    std::string date_day;
    std::string time;
    DatetimeValidate validate_return;

    switch((DatetimeFormat)point_sum){
        case DatetimeFormat::YYYYMMDD_HHMMSS:
            space_idx = datetime.find(" ");
            date_day = datetime.substr(0, space_idx);
            time = datetime.substr(space_idx + 1, datetime.length());
            validate_return = validate_yyyymmdd(date_day);
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            validate_return = validate_hms(time);
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            break;
        case DatetimeFormat::WDAY6_HHMMSS:
        case DatetimeFormat::WDAY7_HHMMSS:
        case DatetimeFormat::WDAY8_HHMMSS:
        case DatetimeFormat::WDAY9_HHMMSS:
        case DatetimeFormat::WDAY_HHMMSS:
            space_idx = datetime.find(" ");
            date_day = datetime.substr(0, space_idx);
            time = datetime.substr(space_idx + 1, datetime.length());
            validate_return = validate_wday(date_day); 
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            validate_return = validate_hms(time);
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            break;
        case DatetimeFormat::MMDD_HHMMSS:
            space_idx = datetime.find(" ");
            date_day = datetime.substr(0, space_idx);
            time = datetime.substr(space_idx + 1, datetime.length());
            validate_return = validate_mmdd(date_day);
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            validate_return = validate_hms(time);
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            break;
        case DatetimeFormat::YYYYMMDD:
            validate_return = validate_yyyymmdd(datetime);
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            break;
        case DatetimeFormat::HHMMSS:
            validate_return = validate_hms(datetime);
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            break;
        case DatetimeFormat::MMDD:
            validate_return = validate_mmdd(datetime);
            if(validate_return != DatetimeValidate::OK){
                return DatetimeFormat::INVALID_DATE_FORMAT;
            }
            break;
        default:
            break;
    }
    return (DatetimeFormat)point_sum;
}

TaskValidate validate_task_parms(cl::Config* task_config, std::string scripts_dir){
    // Check if required fields exist
    if(!task_config->key_exists("Name") ||
       !task_config->key_exists("ScriptFilename") ||
       !task_config->key_exists("Frequency") ||
       !task_config->key_exists("Datetime")){
           return TaskValidate::MISSING_REQUIRED_KEYVALS;
    }
    
    std::string value;
    // Check if script file exists
    value = task_config->get_value("ScriptFilename")->get_data<std::string>();
    if(!std::filesystem::exists(scripts_dir + value)){
        return TaskValidate::SCRIPT_NOT_FOUND;
    }

    // Check if frequency value if valid
    value = task_config->get_value("Frequency")->get_data<std::string>();
    if(value != "Once" && value != "Hourly" && value != "Daily" &&
       value != "Weekly" && value != "Monthly" && value != "Yearly"){
           return TaskValidate::BAD_FREQUENCY_VALUE;
    }

    // Validate datetime depending on frequency value
    if(value == "Once"){

    }
    else if(value == "Hourly"){
        
    }
    else if(value == "Daily"){
        
    }
    else if(value == "Weekly"){
        
    }
    else if(value == "Monthly"){
        
    }
    else if(value == "Yearly"){
        
    }

    return TaskValidate::OK;
}

} // namespace ts