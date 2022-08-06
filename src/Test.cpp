#include <iostream>
#include <iomanip>

#define DAYS_IN_WEEK 7
#define TIMEZONE -4

#define JANUARY 1
#define FEBRARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

enum class DatetimeFormat {
    YYYYMMDD_HHMMSS = 32,
    WDAY6_HHMMSS = 68,
    WDAY7_HHMMSS = 76,
    WDAY8_HHMMSS = 84,
    WDAY9_HHMMSS = 92,
    MMDD_HHMMSS = 26,
    WDAY_HHMMSS = 44,
    YYYYMMDD = 12,
    HHMMSS = 14,
    MMDD = 6,
    INVALID_DATE_FORMAT = -1,
};

enum class DatetimeValidate{
    OK,
    BAD_HMS_LENGTH,
    BAD_YYYYMMDD_LENGTH,
    BAD_MMDD_LENGTH,
    BAD_NUMBER_CHARACTER,
    BAD_APHABETIC_CHARACTER,
    MISSING_COLON,
    MISSING_DASH,
    BAD_WDAY,
    YEAR_OUT_OF_RANGE,
    MONTH_OUT_OF_RANGE,
    DAY_OUT_OF_RANGE,
    HOURS_OUT_OF_RANGE,
    MINUTES_OUT_OF_RANGE,
    SECONDS_OUT_OF_RANGE,
    INVALID_DATETIME_INPUT
};

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

int main(){
    time_t ret;
    
    ret = init_day();
    std::cout << ctime(&ret) << std::endl;

    ret = init_day_add_hms("09:34:00");
    std::cout << ctime(&ret) << std::endl;
    
    ret = init_day_add_dhms(1, "01:34:00");
    std::cout << ctime(&ret) << std::endl;
    
    ret = init_day_add_dhms(90, "01:34:00");
    std::cout << ctime(&ret) << std::endl;
    

    ret = init_day_add_wdhms("Sun", "05:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Mon", "05:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Tue", "05:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Wed", "05:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Thu", "05:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Fri", "05:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Sat", "05:34:00"); 
    std::cout << ctime(&ret) << std::endl;

    DatetimeValidate v;
    v = validate_hms("01:34:00");
    std::cout << (int)v << std::endl;
    v = validate_yyyymmdd("2024-02-29");
    std::cout << (int)v << std::endl;
    v = validate_mmdd("02-29");
    std::cout << (int)v << std::endl;

    DatetimeFormat f;
    f = get_datetime_format("2024-02-29 12:12:12");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("Sunday 12:12:12");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("Tuesday 12:12:12");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("Thursday 12:12:12");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("Wednesday 12:12:12");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("02-28 12:12:12");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("Mon 12:12:12");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("2024-02-29");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("12:12:12");
    std::cout << (int)f << std::endl;
    f = get_datetime_format("02-28");
    std::cout << (int)f << std::endl;

    return 0;
}