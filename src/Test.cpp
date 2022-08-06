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

bool validate_hms(std::string hms){
    if(hms.length() != 8){
        return false;
    }
    unsigned int num;
    num = hms.at(0) & 0x0F;
    if(num < 0 | num > 2){
        return false;
    }
    num = hms.at(1) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    if(hms.at(2) != ':'){
        return false;
    }
    num = hms.at(3) & 0x0F;
    if(num < 0 | num > 5){
        return false;
    }
    num = hms.at(4) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    if(hms.at(5) != ':'){
        return false;
    }
    num = hms.at(6) & 0x0F;
    if(num < 0 | num > 5){
        return false;
    }
    num = hms.at(7) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    return true;
}

bool validate_wday(std::string wday){
    if(wday != "Mon" && wday != "Monday" && 
       wday != "Tue" && wday != "Tuesday" &&
       wday != "Wed" && wday != "Wednesday" &&
       wday != "Thu" && wday != "Thursday" &&
       wday != "Fri" && wday != "Friday" &&
       wday != "Sat" && wday != "Saturday" &&
       wday != "Sun" && wday != "Sunday"){
        return 0;
    }
    return true;
}

bool validate_yyyymmdd(std::string yyyymmdd){
    if(yyyymmdd.length() != 10){
        return false;
    }
    unsigned int num;
    unsigned int year;
    unsigned int month;
    unsigned int day;
    // Validate year individual digits
    num = yyyymmdd.at(0) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    num = yyyymmdd.at(1) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    num = yyyymmdd.at(2) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    num = yyyymmdd.at(3) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    // Validate range of year
    year = ((yyyymmdd.at(0) & 0x0F) * 1000) + 
           ((yyyymmdd.at(1) & 0x0F) * 100) + 
           ((yyyymmdd.at(2) & 0x0F) * 10) + 
           (yyyymmdd.at(3) & 0x0F);
    if(year < 0 | year > 9999){
        return false;
    }
    // Check if dash delimiter exists
    if(yyyymmdd.at(4) != '-'){
        return false;
    }
    // Validate month individual characters
    num = yyyymmdd.at(5) & 0x0F;
    if(num < 0 | num > 1){
        return false;
    }
    num = yyyymmdd.at(6) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    // Validate range of months
    month = ((yyyymmdd.at(5) & 0x0F) * 10) + 
            (yyyymmdd.at(6) & 0x0F);
    if(month < 1 | month > 12){
        return false;
    }
    // Check if dash delimiter exists
    if(yyyymmdd.at(7) != '-'){
        return false;
    }
    // Validate day individual characters
    num = yyyymmdd.at(8) & 0x0F;
    if(num < 0 | num > 3){
        return false;
    }
    num = yyyymmdd.at(9) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    // Validate range of days by month
    day = ((yyyymmdd.at(8) & 0x0F) * 10) + 
          (yyyymmdd.at(9) & 0x0F);

    switch (month)
    {
    case JANUARY:
        if(day < 1 || day > 31){
            return false;
        }
        break;
    case FEBRARY:
        // If year is a leap year, then up to 29 days
        if(year % 4 == 0){
            if(day < 1 || day > 29){
                return false;
            }
        }
        else{
            if(day < 1 || day > 28){
                return false;
            }
        }
        break;
    case MARCH:
        if(day < 1 || day > 31){
            return false;
        }
        break;
    case APRIL:
        if(day < 1 || day > 30){
            return false;
        }
        break;
    case MAY:
        if(day < 1 || day > 31){
            return false;
        }
        break;
    case JUNE:
        if(day < 1 || day > 30){
            return false;
        }
        break;
    case JULY:
        if(day < 1 || day > 31){
            return false;
        }    
        break;
    case AUGUST:
        if(day < 1 || day > 31){
            return false;
        }       
        break;
    case SEPTEMBER:
        if(day < 1 || day > 30){
            return false;
        }    
        break;
    case OCTOBER:
        if(day < 1 || day > 31){
            return false;
        }    
        break;
    case NOVEMBER:
        if(day < 1 || day > 30){
            return false;
        }    
        break;
    case DECEMBER:
        if(day < 1 || day > 31){
            return false;
        }    
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool validate_mmdd(std::string mmdd){
    if(mmdd.length() != 5){
        return false;
    }
    
    time_t today = init_day();
    std::tm* today_struct = std::gmtime(&today);

    unsigned int year = today_struct->tm_year;
    unsigned int num;
    unsigned int month;
    unsigned int day;

    // Validate month individual characters
    num = mmdd.at(0) & 0x0F;
    if(num < 0 | num > 1){
        return false;
    }
    num = mmdd.at(1) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    // Validate range of months
    month = ((mmdd.at(0) & 0x0F) * 10) + 
            (mmdd.at(1) & 0x0F);
    if(month < 1 | month > 12){
        return false;
    }
    // Check if dash delimiter exists
    if(mmdd.at(2) != '-'){
        return false;
    }
    // Validate day individual characters
    num = mmdd.at(3) & 0x0F;
    if(num < 0 | num > 3){
        return false;
    }
    num = mmdd.at(4) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    // Validate range of days by month
    day = ((mmdd.at(3) & 0x0F) * 10) + 
          (mmdd.at(4) & 0x0F);

    switch (month)
    {
    case JANUARY:
        if(day < 1 || day > 31){
            return false;
        }
        break;
    case FEBRARY:
        // If year is a leap year, then up to 29 days
        if(year % 4 == 0){
            if(day < 1 || day > 29){
                return false;
            }
        }
        else{
            if(day < 1 || day > 28){
                return false;
            }
        }
        break;
    case MARCH:
        if(day < 1 || day > 31){
            return false;
        }
        break;
    case APRIL:
        if(day < 1 || day > 30){
            return false;
        }
        break;
    case MAY:
        if(day < 1 || day > 31){
            return false;
        }
        break;
    case JUNE:
        if(day < 1 || day > 30){
            return false;
        }
        break;
    case JULY:
        if(day < 1 || day > 31){
            return false;
        }    
        break;
    case AUGUST:
        if(day < 1 || day > 31){
            return false;
        }       
        break;
    case SEPTEMBER:
        if(day < 1 || day > 30){
            return false;
        }    
        break;
    case OCTOBER:
        if(day < 1 || day > 31){
            return false;
        }    
        break;
    case NOVEMBER:
        if(day < 1 || day > 30){
            return false;
        }    
        break;
    case DECEMBER:
        if(day < 1 || day > 31){
            return false;
        }    
        break;
    default:
        return false;
        break;
    }
    return true;
}

time_t init_day_add_hms(std::string hms){
    if(!validate_hms(hms)){
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
    if(!validate_hms(hms) | d < 0){
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
    if(!validate_wday(wday)){
        return 0;
    }
    if(!validate_hms(hms)){
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

    bool v;
    v = validate_hms("01:34:00");
    std::cout << v << std::endl;
    v = validate_yyyymmdd("2024-02-29");
    std::cout << v << std::endl;
    v = validate_mmdd("02-28");
    std::cout << v << std::endl;

    return 0;
}