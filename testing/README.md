# **Light-weight Task Scheduler - Testing**
This directory contains unit tests for all specific functions, classes and its methods to verify the appropiate execution and handling of different cases (and edge-cases).

---
## **Organization**
The `/testing` directory contains exclusive test-related source files. That includes:
- **`\*.cpp` files:** testcase implementation source files
- **`Makefile` file:** contains rules to compile testcase builds
- **`RunTests.sh` script:** a bash scripts that runs testcase builds
- **`scripts` directory:** contains Bash shell files required by certain testcases
- **`tasks` directory:** contains configuration files required by certain testcases

---
## **Tests**
### **Task_constructor.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify Task object instantiation with constructor.|`Task(std::string, std::string, std::string, std::string, std::string)`<br/>`Task::get_name(void)`<br/> `Task::get_description(void)`<br/>`Task::get_script_name(void)`<br/>`Task::get_frequency(void)` |<span style="color:green">Passed|

### **Task_methods.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Obtain the `time_t` value when `Task` is created.|`Task::get_creation_datetime(bool)`|<span style="color:green">Passed|
|`test2()`|Obtain system's current time + 5 seconds for `Task`'s execution time attribute. Then, verify the returned `time_t` time of execution value.|`Task::get_execution_datetime(bool)`|<span style="color:green">Passed|
|`test3()`|Obtain formated time of creation `string` value.|`Task::get_creation_datetime_fmt(void)`|<span style="color:green">Passed|
|`test4()`|Obtain formated time of execution `string` value.|`Task::get_execution_datetime_fmt(void)`|<span style="color:green">Passed|
|`test5()`|Obtain system's current time + 5 seconds for `Task`'s execution time attribute in `HH:MM:SS` format. Then, verify the returned `DatetimeFormat` value.|`Task::get_execution_datetime_format_attr(void)`|<span style="color:green">Passed|
|`test6()`|Set and get task id and status values.|`Task::set_id(int)`<br/>`Task::get_id(void)`<br/>`Task::set_status(TaskStatus)`<br/>`Task::get_status(void)`<br/>|<span style="color:green">Passed|
|`test7()`|Create `Task` object and run it. Then, verify that the command-line output has been successfully routed to output data member.|`Task::run_task(void)`<br/>`Task::get_output(void)`<br/>|<span style="color:green">Passed|
|`test8()`|Verify method for retriving configuration filename.|`Task::get_config_filename(void)`|<span style="color:green">Passed|

### **validate_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass a valid `HH:MM:SS` string. Expected return code of `ValidationCode::OK`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass an invalid `HH:MM:SS` string with missing `SS` field. Expected return code of `ValidationCode::BAD_HMS_LENGTH`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass an invalid `HH:MM:SS` string with alphabetic character in `HH` field. Expected return code of `ValidationCode::BAD_NUMBER_CHARACTER`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass an invalid `HH:MM:SS` string with alphabetic character in `MM` field. Expected return code of `ValidationCode::BAD_NUMBER_CHARACTER`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass an invalid `HH:MM:SS` string with alphabetic character in `SS` field. Expected return code of `ValidationCode::BAD_NUMBER_CHARACTER`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass an invalid `HH:MM:SS` string with `HH` field out of range. Expected return code of `ValidationCode::HOURS_OUT_OF_RANGE`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass an invalid `HH:MM:SS` string with `MM` field out of range. Expected return code of `ValidationCode::MINUTES_OUT_OF_RANGE`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test8()`|Pass an invalid `HH:MM:SS` string with `SS` field out of range. Expected return code of `ValidationCode::SECONDS_OUT_OF_RANGE`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test9()`|Pass an invalid `HH:MM:SS` string with missing first colon. Expected return code of `ValidationCode::MISSING_DATETIME_COLON`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test10()`|Pass an invalid `HH:MM:SS` string with missing second colon. Expected return code of `ValidationCode::MISSING_DATETIME_COLON`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test11()`|Pass an invalid `HH:MM:SS` string with missing `:MM:SS` fields. Expected return code of `ValidationCode::BAD_HMS_LENGTH`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test12()`|Pass an invalid `HH:MM:SS` string with bad length and all alphabetic characters. Expected return code of `ValidationCode::BAD_HMS_LENGTH`.|`validate_hms(std::string)`|<span style="color:green">Passed|
|`test13()`|Pass an invalid `HH:MM:SS` string with valid length and all alphabetic characters. Expected return code of `ValidationCode::BAD_NUMBER_CHARACTER`.|`validate_hms(std::string)`|<span style="color:green">Passed|

### **validate_wday.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid full week day names.|`validate_wday(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass valid abbreviated week day names.|`validate_wday(std::string)`|<span style="color:green">Passed|
|`test3()`|Invalid week day name.|`validate_wday(std::string)`|<span style="color:green">Passed|

### **validate_wday_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid full week day names and `HH:MM:SS` string.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass valid abbreviated week day names and `HH:MM:SS` string.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `WDAY HH:MM:SS` string with missing space.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `WDAY HH:MM:SS` string with bad `WDAY` field.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `WDAY HH:MM:SS` string with bad `HH:MM:SS` field.|`validate_wday_hms(std::string)`|<span style="color:green">Passed|

### **validate_yyyymmdd.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid `YYYY-MM-DD` strings, lower and upper bound days for each month.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass invalid `YYYY-MM-DD` string with bad length.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `YYYY-MM-DD` strings: bad `YYYY` field, bad `MM` field, and bad `DD` field.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `YYYY-MM-DD` strings with misplaced dashes.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD` string with `MM` out of range.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `YYYY-MM-DD` string with `DD` out of range.|`validate_yyyymmdd(std::string)`|<span style="color:green">Passed|

### **validate_yyyymmdd_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass valid `YYYY-MM-DD HH:MM:SS` string.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with missing space.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings: alphabetic character in `YYYY-MM-DD` section, and alphabetic character in `HH:MM:SS` section.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings with missing dash characters.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD HH:MM:SS` strings with missing colon characters.|`validate_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|

### **init_today.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify that `init_today()` returns the correct `time_t` value that corresponds to the very beginning of the current day in UTC time.|`init_today()`|<span style="color:green">Passed|

### **init_year.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify that `init_year()` returns the correct `time_t` value that corresponds to the very beginning of the current year in UTC time.|`init_year()`|<span style="color:green">Passed|

### **today_add_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one minute in seconds to input `HH:MM:SS` string. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Subtract one minute in seconds to input `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass invalid `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_hms(std::string)`|<span style="color:green">Passed|

### **today_add_dhms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one minute in seconds to input `HH:MM:SS` string and zero days. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test2()`|Add one minute in seconds to input `HH:MM:SS` string and two days. Call should succeed and return `time_t` with a value two days and one minute in the future.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test3()`|Subtract one minute in seconds to input `HH:MM:SS` string and zero days. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass negative value for days attribute. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_dhms(std::string)`|<span style="color:green">Passed|

### **today_add_wday_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Verify week day full name. Add one minute in seconds to input `HH:MM:SS` section. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Verify week day abbreviated name. Add one minute in seconds to input `HH:MM:SS` section. Call should succeed and return `time_t` with a value one minute in the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Subtract 24 hours from current time to obtain previous week day name; then, use this week day as input for the function. Call should succeed and return `time_t` with a value 6 days into the future.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass invalid string input with bad `HH:MM:SS` section. Call should fail and return `time_t` with a value of zero.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid string input with bad `WDAY` section. Call should fail and return `time_t` with a value of zero.|`today_add_wday_hms(std::string)`|<span style="color:green">Passed|

### **today_add_yyyymmdd.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one day in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of one day into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test2()`|Add 30 days in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of 30 days into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test3()`|Add 365 days in seconds to input `YYYY-MM-DD` string. Call should succeed and return `time_t` with a value of 365 days into the future.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test4()`|Subtract one day in seconds to input `YYYY-MM-DD` string. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass invalid `YYYY-MM-DD` string with missing dashes. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `YYYY-MM-DD` string with `MM` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass invalid `YYYY-MM-DD` string with `DD` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd(std::string)`|<span style="color:green">Passed|

### **today_add_yyyymmdd_hms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Add one day in seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of one day into the future.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test2()`|Add 30 days in seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of 30 days into the future.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test3()`|Add 365 days in seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of 365 days into the future.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test4()`|Add 60 seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should succeed and return `time_t` with a value of 60 seconds into the future.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test5()`|Subtract one day in seconds to input `YYYY-MM-DD HH:MM:SS` string. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass invalid `YYYY-MM-DD  HH:MM:SS` string with missing dashes. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test7()`|Pass invalid `YYYY-MM-DD  HH:MM:SS` string with missing colons. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test8()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `MM` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test9()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `DD` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test10()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `HH` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test11()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `MM` (minutes) field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|
|`test12()`|Pass invalid `YYYY-MM-DD HH:MM:SS` string with `SS` field out of range. Call should fail and return `time_t` with a value of zero.|`today_add_yyyymmdd_hms(std::string)`|<span style="color:green">Passed|

### **compute_datetime_format.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Pass strings with a valid `HH:MM:SS` datetime format. The calls should succeed with return value of `DatetimeFormat::HHMMSS`.|`compute_datetime_format(std::string)`|<span style="color:green">Passed|
|`test2()`|Pass strings with a valid `WDAY HH:MM:SS` datetime format with `WDAY` section being abbreviated week day name for all days in the week. The calls should succeed with return value of `DatetimeFormat::WDAY_HHMMSS`.|`compute_datetime_format(std::string)`|<span style="color:green">Passed|
|`test3()`|Pass strings with a valid `WDAY HH:MM:SS` datetime format with `WDAY` section being full week day name for all days in the week. The calls should succeed and the return value of `WDAY_HHMMSS`.|`compute_datetime_format(std::string)`|<span style="color:green">Passed|
|`test4()`|Pass strings with a valid `YYYY-MM-DD` datetime format. The calls should succeed with return value of `DatetimeFormat::YYYYMMDD`.|`compute_datetime_format(std::string)`|<span style="color:green">Passed|
|`test5()`|Pass string with a valid `YYYY-MM-DD HH:MM:SS` datetime format. Call should succeed with return value of `DatetimeFormat::YYYYMMDD_HHMMSS`.|`compute_datetime_format(std::string)`|<span style="color:green">Passed|
|`test6()`|Pass strings with invalid datetime format. The calls should fail with return value of  `DatetimeFormat::INVALID_DATE_FORMAT`.|`compute_datetime_format(std::string)`|<span style="color:green">Passed|

### **validate_task_parms.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Provide the mandatory valid attributes to instantiate `Task` object. These include `Name`, `ScriptFilename`, `Frequency`, and `Datetime`. Call should succeed with return value of  `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Provide all possible valid attributes to instantiate `Task` object. These include `Name`, `ScriptFilename`, `Frequency`, and `Datetime`. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Fail to pass `Name` attribute. Call should fail with return value of `ValidationCode::MISSING_NAME_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Fail to pass `ScriptFilename` attribute. Call should fail with return value of `ValidationCode::MISSING_SCRIPTFN_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Fail to pass `Frequency` attribute. Call should fail with return value of `ValidationCode::MISSING_FREQUENCY_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Fail to pass `Datetime` attribute with `Frequency` of `Once`. Call should fail with return value of  `ValidationCode::MISSING_DATETIME_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Fail to pass `Datetime` attribute with `Frequency` of `Hourly`. Call should fail with return value of  `ValidationCode::MISSING_DATETIME_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Fail to pass `Datetime` attribute with `Frequency` of `Weekly`. Call should fail with return value of  `ValidationCode::MISSING_DATETIME_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test9()`|Fail to pass `Datetime` attribute with `Frequency` of `Weekly`. Call should fail with return value of  `ValidationCode::MISSING_DATETIME_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test10()`|Fail to pass `Datetime` attribute with `Frequency` of `Monthly`. Call should fail with return value of  `ValidationCode::MISSING_DATETIME_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test11()`|Fail to pass `Datetime` attribute with `Frequency` of `Yearly`. Call should fail with return value of  `ValidationCode::MISSING_DATETIME_KEYVAL`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test12()`|Provide all possible valid attributes to instantiate `Task` object. `ScriptFilename` value should point to an invalid file location. Call should fail with return value of  `ValidationCode::SCRIPT_NOT_FOUND`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test13()`|Provide all possible valid attributes to instantiate `Task` object. `Frequency` value should be invalid. Call should fail with return value of `ValidationCode::BAD_FREQUENCY_VALUE`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test14()`|Provide all possible valid attributes to instantiate `Task` object. `Name` value should be over 32 characters long. Call should fail with return value of `ValidationCode::INVALID_NAME_LENGTH`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Once.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` (abbreviated and full week day names). Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `WDAY HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with `YYYY-MM-DD` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `ValidationCode::INCOMPATIBLE_ONCE_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS`, and `YYYY-MM-DD HH:MM:SS`. The format `WDAY HH:MM:SS` does not require to be tested because it will always rollover to the next week. The datetime value is one minute in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test9()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. The datetime value is one day in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test10()`|Test the datetime format `WDAY HH:MM:SS` of the `Datetime` attribute. The datetime value is 60 seconds in the past. This format allows wrapping the resulting `time_t` to the next week day if the indicated week day already passed. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Hourly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `ValidationCode::INCOMPATIBLE_ONCE_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. The datetime value is one minute in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Daily.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` (abbreviated and full week day names). Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the incompatible datetime format `YYYY-MM-DD`. Call should fail with return value of `ValidationCode::INCOMPATIBLE_DAILY_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `WDAY HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `ValidationCode::INCOMPATIBLE_DAILY_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. The format `WDAY HH:MM:SS` does not require to be tested because it will always rollover to the next week and next year, respectively. The datetime value is one minute in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format `WDAY HH:MM:SS` of the `Datetime` attribute. The datetime value is 60 seconds in the past. This format allows wrapping the resulting `time_t` to the next week day if the indicated week day already passed. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Weekly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` (abbreviated and full week day names). Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `WDAY HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with `YYYY-MM-DD` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `ValidationCode::INCOMPATIBLE_WEEKLY_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. The format `WDAY HH:MM:SS` does not require to be tested because it will always rollover to the next year. The datetime value is one minute in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test9()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. The datetime value is one day in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test10()`|Test the datetime format `WDAY HH:MM:SS` of the `Datetime` attribute. The datetime value is 60 seconds in the past. This format allows wrapping the resulting `time_t` to the next week day if the indicated week day already passed. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Monthly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a valid `Datetime` value with the format `WDAY HH:MM:SS`. The datetime format `WDAY HH:MM:SS` is incompatible with `Monthly` frequency attribute. Call should fail with return value of `ValidationCode::INCOMPATIBLE_MONTHLY_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with `YYYY-MM-DD` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `ValidationCode::INCOMPATIBLE_MONTHLY_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format of the following `Datetime` attribute values: `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS`. The datetime value is one minute in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test9()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. The datetime value is one day in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **validate_task_parms_Yearly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Test the datetime format `YYYY-MM-DD HH:MM:SS` of the `Datetime` attribute. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test2()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. Call should succeed with return value of `ValidationCode::OK`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test3()`|Pass a valid `Datetime` values with the format `HH:MM:SS` and `WDAY HH:MM:SS`. The datetime formats `HH:MM:SS` and `WDAY HH:MM:SS` are incompatible with `Yearly` frequency attribute. Call should fail with return value of `ValidationCode::INCOMPATIBLE_YEARLY_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test4()`|Pass a `Datetime` attribute with `YYYY-MM-DD HH:MM:SS` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test5()`|Pass a `Datetime` attribute with `YYYY-MM-DD` format. The `Datetime` attribute is invalid. Calls should fail with their expected return values.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test6()`|Pass a `Datetime` attribute with invalid value that does not follow any datetime format. Call should fail with return value of `ValidationCode::INCOMPATIBLE_YEARLY_FREQ_DATETIME_FORMAT`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test7()`|Test the datetime format `YYYY-MM-DD HH:MM:SS` of the `Datetime` attribute. The datetime value is one minute in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|
|`test8()`|Test the datetime format `YYYY-MM-DD` of the `Datetime` attribute. The datetime value is one minute in the past. Call should fail with return value of `ValidationCode::PASSED_DATETIME`.|`validate_task_parms(cl::Config*, std::string)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Once.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Call the method with tasks using the following `Datetime` formats: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` (abbreviated and full week day names). Tasks with `Frequency` of `Once` should not have the execution datetime value updated.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Call the method with task using the `Datetime` format `YYYY-MM-DD`. Tasks with `Frequency` of `Once` should not have the execution datetime value updated.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Hourly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Hourly`. After a successful method call, the execution datetime value should have increased by 1 hour.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Hourly`. After a successful method call, the execution datetime value should have increased by 1 hour.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
### **Task_update_execution_datetime_Daily.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Daily`. After a successful method call, the execution datetime value should have increased by 1 day.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Daily`. After a successful method call, the execution datetime value should have increased by 1 day.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Daily`. After a successful method call, the execution datetime value should have increased by 1 day.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Daily`. After a successful method call, the execution datetime value should have increased by 1 day.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Weekly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Weekly`. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Weekly`. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Weekly`. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Weekly`. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Weekly`. Initial execution datetime has an offset of one day into the future. After a successful method call, the execution datetime value should have increased by 7 days.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Monthly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Monthly`. After a successful method call, the execution datetime value should correspond the calendar day of the next month.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Monthly`. After a successful method call, the execution datetime value should correspond the calendar day of the next month.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Monthly`. Initial execution datetime has an offset of one day into the future. After a successful method call, the execution datetime value should correspond the calendar day of the next month.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_update_execution_datetime_Yearly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Yearly`. After a successful method call, the execution datetime value should correspond the calendar day of the next year.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Yearly`. Initial execution datetime has an offset of one day into the future. After a successful method call, the execution datetime value should correspond the calendar day of the next year.|`Task::update_execution_datetime(void)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Once.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Once`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Once`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, `WDAY HH:MM:SS`, and `YYYY-MM-DD` and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Hourly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Hourly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Hourly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Hourly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` datetime format and `Frequency` of `Hourly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with incompatible datetime format `YYYY-MM-DD` datetime format and `Frequency` of `Hourly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS` and `YYYY-MM-DD HH:MM:SS` and `Frequency` of `Hourly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Daily.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Daily`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Daily`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Daily`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Daily`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with incompatible datetime format `YYYY-MM-DD` datetime format and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `WDAY HH:MM:SS` and `Frequency` of `Daily`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Weekly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with a `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Weekly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Weekly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, `WDAY HH:MM:SS`, and `YYYY-MM-DD` and `Frequency` of `Weekly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Monthly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `HH:MM:SS` datetime format and `Frequency` of `Monthly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Monthly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Monthly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, and `YYYY-MM-DD` and `Frequency` of `Monthly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Task_setting_exec_datetime_Yearly.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Task` with a `YYYY-MM-DD HH:MM:SS` datetime format and `Frequency` of `Yearly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test2()`|Initialize `Task` with a `YYYY-MM-DD` datetime format and `Frequency` of `Yearly`. After a successful `Task` initialization, the execution datetime value should correspond to the verification execution datetime string.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test3()`|Initialize `Task` with an invalid datetime format and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test4()`|Initialize `Task` with incompatible datetime format `HH:MM:SS` datetime format and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test5()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` (full week day names) datetime format and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test6()`|Initialize `Task` with incompatible datetime format `WDAY HH:MM:SS` (abbreviated week day names) datetime format and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|
|`test7()`|Attempt to initialize `Task` with invalid datetime values with datetime formats `YYYY-MM-DD HH:MM:SS` and `YYYY-MM-DD` and `Frequency` of `Yearly`. The constructor call must end with the `Task->status` set to `TaskStatus::INIT_ERROR`.|`Task::Task(std::string, std::string, std::string, std::string, std::string)`|<span style="color:green">Passed|

### **Scheduler_get_instance.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Instantiate and remove instance of `Scheduler` singleton object.|`Scheduler::Scheduler_get_instance(void)`<br/>`Scheduler::Scheduler_end_instance(void)`|<span style="color:green">Passed|

### **Scheduler_methods.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `Scheduler` object and verify its data members were properly zeroed out.  The `Event Reporter` should not register any events.|`Scheduler::Scheduler_init(void)`<br/>`Scheduler::Scheduler_delete(void)`<br/>`Scheduler::get_n_tasks(void)`<br/>`Scheduler::get_current_path(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test2()`|Verify that the `exec_path` data member is updated to the directory path where the test build is located. The `Event Reporter` should not register any events.|`Scheduler::obtain_exec_path(void)`<br/>`Scheduler::get_current_path(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test3()`|Load tasks from `tasks` directory. After a successful call, all tasks defined in the `tasks` directory (total of 2) should be loaded to the `Scheduler`. The `Event Reporter` should register exactly 2 events after loading both tasks.|`Scheduler::load_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test4()`|Load one task from `tasks` directory. After a successful call, just one task should be loaded to the `Scheduler`. The `Event Reporter` should register exactly 1 event after loading the task.|`Scheduler::load_task(std::string&)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test5()`|Load tasks from `tasks` directory. Then, remove one task from `Scheduler`. After a successful call, there should only be 1 task left in  the `Scheduler`. The `Event Reporter` should register exactly 3 events after loading both tasks and removing one.|`Scheduler::remove_task(std::string&)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test6()`|Load tasks from `tasks` directory. Then, remove two tasks from `Scheduler`, one by one. After a successful call, there should be 0 tasks in  the `Scheduler`. The `Event Reporter` should register exactly 4 events after loading and removing both tasks.|`Scheduler::remove_task(std::string&)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test7()`|Query a task name for a task that does not exist in `Scheduler`. The call should return false. The `Event Reporter` should not register any events.|`Scheduler::task_exists(std::string&)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test8()`|Generate `TestTask` and load it into the `Scheduler`. The `Event Reporter` should report exactly 1 event after loading the task. Then query the loaded task validate its attributes. The `Event Reporter` should not register any events when quering a task.|`Scheduler::get_task(std::string&)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|

### **Scheduler_Task_run_task.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Generate a temporary `Task` called `TestTask` and load it in the `Scheduler`. This task has a `Once` frequency value and set to run 1 second after its creation. Check its output value and that the `Task` remains in `Scheduler`.|`Scheduler::load_task(std::string&)`<br/>`Task::run_task(void)`<br/>`Task::launch_thread(Task*)`<br/>`Task::stop_thread(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test2()`|Generate a temporary `Task` called `TestTask` and load it in the `Scheduler`. This task has a `Daily` frequency value and set to run 1 second after its creation. Check its output value and that the `Task` remains in `Scheduler`.|`Scheduler::load_task(std::string&)`<br/>`Task::run_task(void)`<br/>`Task::launch_thread(Task*)`<br/>`Task::stop_thread(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test3()`|Generate a temporary `Task` called `TestTask` and load it in the `Scheduler`. This task has a `Weekly` frequency value and set to run 1 second after its creation. Check its output value and that the `Task` remains in `Scheduler`.|`Scheduler::load_task(std::string&)`<br/>`Task::run_task(void)`<br/>`Task::launch_thread(Task*)`<br/>`Task::stop_thread(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test4()`|Generate a temporary `Task` called `TestTask` and load it in the `Scheduler`. This task has a `Monthly` frequency value and set to run 1 second after its creation. Check its output value and that the `Task` remains in `Scheduler`.|`Scheduler::load_task(std::string&)`<br/>`Task::run_task(void)`<br/>`Task::launch_thread(Task*)`<br/>`Task::stop_thread(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test5()`|Generate a temporary `Task` called `TestTask` and load it in the `Scheduler`. This task has a `Yearly` frequency value and set to run 1 second after its creation. Check its output value and that the `Task` remains in `Scheduler`.|`Scheduler::load_task(std::string&)`<br/>`Task::run_task(void)`<br/>`Task::launch_thread(Task*)`<br/>`Task::stop_thread(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|

### **Scheduler_reload_all_tasks.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Load tasks `cat_test.cl` and `ls_test.cl` from tasks directory. Then, reload all the tasks from their corresponding configuration files. Verify that tasks' attributes are loaded correctly by checking they match the expected values. The `EventReporter` should record 4 events after loading and reloading the tasks. Two tasks should still be loaded in the `Scheduler`.|`Scheduler::reload_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test2()`|Load all tasks available in `tasks` directory. Rename `tasks` directory to simulate it does not exist. The `EventReporter` should record 3 events after attempting to find the `tasks` directory. Two tasks should be loaded in the `Scheduler`.|`Scheduler::reload_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test3()`|Load all tasks available in `tasks` directory. Rename `scripts` directory to simulate it does not exist. The `EventReporter` should record 3 events after attempting to find the `scripts` directory. Two tasks should be loaded in the `Scheduler`.|`Scheduler::reload_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test4()`|Generate a temporary task in `tasks` directory. Then, remove the temporary task's configuration file. Only the temporary task should fail to reload. The `EventReporter` should record 6 events after attempting to reload all tasks. Three tasks should be loaded in the `Scheduler`.|`Scheduler::reload_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test5()`|Generate a temporary task in `tasks` directory. Then, modify the temporary task's configuration file with an invalid frequency attribute. Only the temporary task should fail to reload. The `EventReporter` should record 6 events after attempting to reload all tasks. Three tasks should be loaded in the `Scheduler`.|`Scheduler::reload_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|

### **Scheduler_reload_task.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
`test1()`|Load a task in the scheduler; then, create a modified version of task's configuration file. Then, reload the task with the modified configuration file. Verify that the task attributes are loaded correctly by checking they match the expected values. The `EventReporter` should record 2 events after reloading the task. One task should still be loaded in the `Scheduler`.|`Scheduler::reload_task(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
`test2()`|Load tasks in the scheduler; then, attempt to reload a task that does not exist in the scheduler. The `EventReporter` should record 3 events after loading 2 tasks and attempting to reload 1 task. Two tasks should still be loaded in the `Scheduler`.|`Scheduler::reload_task(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test3()`|Load all tasks and rename `tasks` directory to simulate it does not exist. The `EventReporter` should record 3 events after attempting to find the `tasks` directory. Two tasks should still be loaded in the `Scheduler`.|`Scheduler::reload_task(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test4()`|Load all tasks and rename `scripts` directory to simulate it does not exist. The `EventReporter` should record 3 events after attempting to find the `scripts` directory. Two tasks should still be loaded in the `Scheduler`.|`Scheduler::reload_task(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test5()`|Generate a temporary task in `tasks` directory. Then, remove the temporary task's configuration file and attempt to reload it. The `EventReporter` should record 2 events after attempting to reload task from missing configuration file. One task should still be loaded in the `Scheduler`.|`Scheduler::reload_task(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test6()`|Load temporary task from `ZZZTestTask.cl` and modify its configuration file with an invalid frequency value. Then, attempt to reload the task `ZZZTestTask` and detect the invalid frequency attribute. The `EventReporter` should record 3 events after attempting to reload task. The original `ZZZTestTask` task should still be loaded in the `Scheduler`.|`Scheduler::reload_task(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|

### **Scheduler_load_all_tasks.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Load tasks `cat_test.cl` and `ls_test.cl` from tasks directory. Verify that tasks' attributes are loaded correctly by checking they match the expected values. The `EventReporter` should record 2 events after loading the tasks. Two tasks should be loaded in the `Scheduler`.|`Scheduler::load_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test2()`|Rename `tasks` directory to simulate it does not exist. The `EventReporter` should record 1 event after attempting to find the `tasks` directory. No tasks should be loaded in the `Scheduler`.|`Scheduler::load_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test3()`|Rename `scripts` directory to simulate it does not exist. The `EventReporter` should record 1 event after attempting to find the `scripts` directory. No tasks should be loaded in the `Scheduler`.|`Scheduler::load_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test4()`|Generate a task with a `Datetime` value in the past. The `EventReporter` should record 2 events after loading valid existing tasks, plus 1 event after attempting to load a task in the past. Only 2 tasks should be loaded in the `Scheduler`.|`Scheduler::load_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test5()`|Generate a task with a duplicate `Name`. The `EventReporter` should record 2 events after loading valid existing tasks, plus 1 event after attempting to load a task with a duplicate `Name`. Only 2 tasks should be loaded in the `Scheduler`.|`Scheduler::load_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
|`test6()`|Generate a temporary invalid task configuration file with missing semicolons on every entry. The `EventReporter` should record 2 events after loading valid existing tasks, plus 1 event after attempting to load an invalid task. Only 2 tasks should be loaded in the `Scheduler`.|`Scheduler::load_all_tasks(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|

### **Scheduler_load_task.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Load task `cat_test.cl` from tasks directory. Verify that task's attributes are loaded correctly by checking they match the expected values. The `EventReporter` should record 1 event after loading the task.|`Scheduler::load_task(std::string&)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test2()`|Rename `tasks` directory to simulate it does not exist. The `EventReporter` should record 1 event after attempting to find the `tasks` directory. No task should be loaded in the loaded in the `Scheduler`.|`Scheduler::load_task(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test3()`|Rename `scripts` directory to simulate it does not exist. The `EventReporter` should record 1 event after attempting to find the `scripts` directory. No task should be loaded in the `Scheduler`.|`Scheduler::load_task(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test4()`|Attempt loading task that does not exists in the tasks directory. The `EventReporter` should record 1 event after attempting to find the `tasks` directory. No task should be loaded in the loaded in the `Scheduler`.|`Scheduler::load_task(std::string&)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test5()`|Generate a task with a `Datetime` value in the past. The `EventReporter` should record 1 event after attempting to load a task in the past. No task should be loaded in the `Scheduler`.|`Scheduler::load_task(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test6()`|Generate a task with a duplicate `Name`. The `EventReporter` should record 1 events after loading first task with the shared name, plus 1 event after attempting to load a task with a duplicate `Name`. Only 1 task should be loaded in the `Scheduler`.|`Scheduler::load_task(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test7()`|Generate a temporary invalid task configuration file with missing semicolons on every entry. The `EventReporter` should record 1 events attempting to load the invalid task. No tasks should be loaded in the `Scheduler`.|`Scheduler::load_task(void)`<br/>`EventReporter::get_n_events(void)`<br/>`Scheduler::get_n_tasks(void)`|<span style="color:green">Passed|
### **EventReporter_get_instance.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Instantiate and remove instance of `EventReporter` singleton object.|`EventReporter::EventReporter_get_instance(void)`<br/>`EventReporter::EventReporter_end_instance(void)`|<span style="color:green">Passed|

### **EventReporter_methods.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `EventReporter` object and verify its data members were properly zeroed out.  The `EventReporter` should not register any events.|`EventReporter::EventReporter_init(void)`<br/>`EventReporter::EventReporter_delete(void)`<br/>`EventReporter::get_n_events(void)`|<span style="color:green">Passed|
|`test2()`|Log one event and retrieve it. The `EventReporter` should register only one event. Then, verify that the event attributes match the initial values.|`EventReporter::log_event(EventType, std::string&)`<br/>`unsigned int get_n_events(void)`<br/>`EventReporter::get_last_event(void)`|<span style="color:green">Passed|
|`test3()`|Log three events and retrieve them. The `EventReporter` should register only three events. Then, verify that the attributes of each event match their initial values.|`EventReporter::log_event(EventType, std::string&)`<br/>`unsigned int get_n_events(void)`<br/>`EventReporter::get_event_at(unsigned int)`|<span style="color:green">Passed|
|`test4()`|Log three events and retrieve them. Verify that `EventReporter::get_event_at(unsigned int)` and `EventReporter::get_last_event(void)` will the retrieve same most recent task by verifying the attributes.| `EventReporter::log_event(EventType, std::string&)`<br/>`unsigned int get_n_events(void)`<br/>`EventReporter::get_event_at(unsigned int)`<br/>`EventReporter::get_last_event(void)`|<span style="color:green">Passed|
|`test5()`|Generate and verify event messages based on the `ValidationCode`, a string indicating the filename of a task configuration file, and the a configuration object passed to the method being tested.|`EventReporter::generate_load_task_msg(ValidationCode, std::string&, cl::Config*)`|<span style="color:green">Passed|
|`test6()`|Attempt to retrieve the latest event from `EventReporter` when no event has been recorded yet. A warning-type event should be logged and returned with an appropiate message and update the event count.|`EventReporter::get_last_event(void)`|<span style="color:green">Passed|
|`test7()`|Log an event and attempt to retrieve an event from `EventReporter` with an negative index. A warning-type event should be logged and returned with an appropiate message and update the event count.|`EventReporter::get_event_at(unsigned int)`|<span style="color:green">Passed|
|`test8()`|Log an event and attempt to retrieve an event from `EventReporter` with an index equal to the number of events recorded. A warning-type event should be logged and returned with an appropiate message and update the event count.|`EventReporter::get_event_at(unsigned int)`|<span style="color:green">Passed|
|`test9()`|Log an event and attempt to retrieve an event from `EventReporter` with an index greater than the number of events recorded. A warning-type event should be logged and returned with an appropiate message and update the event count.|`EventReporter::get_event_at(unsigned int)`|<span style="color:green">Passed|

### **CommandLine_get_instance.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Instantiate and remove instance of `CommandLine` singleton object.|`CommandLine::CommandLine_get_instance(void)`<br/>`CommandLine::CommandLine_end_instance(void)`|<span style="color:green">Passed|

### **CommandLine_methods.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Initialize `CommandLine` object and verify its data members were properly zeroed out.|`CommandLine::CommandLine_init(void)`<br/>`CommandLine::CommandLine_delete(void)`|<span style="color:green">Passed|
|`test2()`|Set the `cmd_input` data member to an arbitrary value and verify it remains unchanged.|`CommandLine::set_cmd_input(void)`<br/>`CommandLine::get_cmd_input(void)`|<span style="color:green">Passed|
|`test3()`|Issue the command `help check` and verify the `cmds_issued` data member has been updated to 1.|`CommandLine::get_cmds_issued(void)`<br/>`CommandLine::parse_command(void)`|<span style="color:green">Passed|
|`test4()`|Issue the command `help check` and verify the `cmd_output` data member has been updated after a successful execution.|`CommandLine::parse_command(void)`<br/>`CommandLine::get_cmd_input(void)`|<span style="color:green">Passed|

### **CommandLine_verb_check.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Issue the command `check`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test2()`| Issue the command `check registry invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test3()`|Issue the command `check registry`. It should print an empty task registry table since the schduler has not loaded any tasks. Verify the table header and count of commands issued.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`<br/>`Scheduler::display_registry(void)`|<span style="color:green">Passed|
|`test4()`|Issue the command `check registry`. It should print a task registry table with 2 loaded tasks. Verify the table header, loaded task attributes, and count of commands issued.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`<br/>`Scheduler::display_registry(void)`|<span style="color:green">Passed|
|`test5()`|Issue the command `check task`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test6()`|Issue the command `check task ls invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test7()`|Issue the command `check task ls`. Then, verify the task attributes to be printed by the scheduler.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`<br/>`Scheduler::display_task(std::string&)`|<span style="color:green">Passed|
|`test8()`|Issue the command `check task invalid_name`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, event type, and command count.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`<br/>`Scheduler::display_task(std::string&)`|<span style="color:green">Passed|
|`test9()`|Issue the command `check status invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, event type, and command count.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test10()`|Issue the command `check status`. Then, verify the current status output of the `Scheduler` and count of commands issued.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`<br/>`Scheduler::display_scheduler_status(void)`|<span style="color:green">Passed|
|`test11()`|Issue the command `check output`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test12()`|Issue the command `check output ls invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test13()`|Generate a temporary task and load it. Then, wait until it runs so it generates an output. Issue the command `check output ls`. Verify that the output matches the expected value and verify the command count.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`<br/>`Scheduler::display_task_output(std::string&)`|<span style="color:green">Passed|
|`test14()`|Issue the command `check output invalid_name`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, event type, and command count.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`<br/>`Scheduler::display_task_output(std::string&)`|<span style="color:green">Passed|
|`test15()`|Issue the command `check invalid args`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_check(std::vector<std::string>&)`|<span style="color:green">Passed|

### **CommandLine_verb_remove.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Issue the command `remove`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_remove(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test2()`|Issue the command `remove task ls invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_remove(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test3()`|Load task in the `Scheduler` and then issue the command `remove task ls`. The operation should succeed. Verify the event's attributes and status of the `Scheduler` after the task removal.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_remove(std::vector<std::string>&)`<br/>`Scheduler::remove_task(std::string&)`|<span style="color:green">Passed|
|`test4()`|Load task in the `Scheduler` and then issue the command `remove task invalid`. It should cause the `Scheduler` to report an error event. Verify the event message, event time, event type, and command count. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_remove(std::vector<std::string>&)`<br/>`Scheduler::remove_task(std::string&)`|<span style="color:green">Passed|
|`test5()`|Issue the command `remove tasks`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_remove(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test6()`|Remove two tasks by issuing the command `remove task cat ls`. The operation should succeed. Verify the event's attributes and status of the `Scheduler` after the tasks has been removed. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_remove(std::vector<std::string>&)`<br/>`Scheduler::remove_task(std::string&)`|<span style="color:green">Passed|
|`test7()`|Attempt to remove two tasks in the `Scheduler` by issuing the command `remove tasks cat invalid`. It should cause the `Scheduler` only remove the `cat` task but also report an event error on the second task name. Verify the events message, events time, and events type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_remove(std::vector<std::string>&)`<br/>`Scheduler::remove_task(std::string&)`|<span style="color:green">Passed|
|`test8()`|Issue the command `remove invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_remove(std::vector<std::string>&)`|<span style="color:green">Passed|

### **CommandLine_verb_reload.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Issue the command `reload`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test2()`|Attempt to reload task in the `Scheduler` by issuing the command `reload task ls invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test3()`|Reload one task by issuing the command `reload task ls`. The operation should succeed. Verify the event's attributes and status of the `Scheduler` after the task has been reloaded. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`<br/>`Scheduler::reload_task(std::string&)`|<span style="color:green">Passed|
|`test4()`|Attempt to reload task that does not exist in the `Scheduler` by issuing the command `reload task invalid`. It should cause the `Scheduler` to report an error event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`<br/>`Scheduler::reload_task(std::string&)`|<span style="color:green">Passed|
|`test5()`|Issue the command `reload tasks`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test6()`|Reload two tasks by issuing the command `reload task cat ls`. The operation should succeed. Verify the event's attributes and status of the `Scheduler` after the tasks has been reloaded. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`<br/>`Scheduler::reload_task(std::string&)`|<span style="color:green">Passed|
|`test7()`|Attempt to reload two tasks in the `Scheduler` by issuing the command `reload tasks cat invalid`. It should cause the `Scheduler` only reload the `cat` task but also report an event error on the second task name. Verify the events message, events time, and events type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`<br/>`Scheduler::reload_task(std::string&)`|<span style="color:green">Passed|
|`test8()`|Attempt to reload all tasks in the `Scheduler` by issuing the command `reload all invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`<br/>`Scheduler::reload_all_tasks(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test9()`|Reload all tasks in the `Scheduler` by issuing the command `reload all`. The operation should succeed. Verify the event's attributes and status of the `Scheduler` after the tasks has been reloaded. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_reload(std::vector<std::string>&)`<br/>`Scheduler::reload_all_tasks(void)`|<span style="color:green">Passed|
|`test10()`|Issue the command `reload invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`|<span style="color:green">Passed|

### **CommandLine_verb_load.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Issue the command `load`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test2()`|Attempt to load task in the `Schdeuler` by issuing the command `load task ls_test.cl invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test3()`|Load one task in the `Scheduler` by issuing the command `load task ls_test.cl`. The operation should succeed. Verify the event's attributes and status of the `Scheduler` after the task has been loaded.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`<br/>`Scheduler::load_task(std::string&)`|<span style="color:green">Passed|
|`test4()`|Attempt to load task in the `Scheduler` from a configuration file that does not exist by issuing the command `load task invalid`. It should cause the `Scheduler` to report an error event. Verify the event message, event time, event type, and command count. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`<br/>`Scheduler::load_task(std::string&)`|<span style="color:green">Passed|
|`test5()`|Issue the command `load tasks`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test6()`|Load two tasks by issuing the command `load task cat_test.cl ls_test.cl`. The operation should succeed. Verify the event's attributes and status of the `Scheduler` after the tasks has been loaded. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`<br/>`Scheduler::load_task(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test7()`|Attempt to load two tasks in the `Scheduler` by issuing the command `load tasks cat_test.cl invalid`. It should cause the `Scheduler` only load the `cat` task but report an event error. Verify the events message, events time, and events type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test8()`|Attempt to load all tasks in the `tasks` directory by issuing the command `load all invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test9()`|Load all tasks in the `tasks` directory by issuing the command `load all`. The operation should succeed. Verify the event's attributes and status of the `Scheduler` after the tasks has been loaded. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`<br/>`Scheduler::load_all_tasks(void)`|<span style="color:green">Passed|
|`test10()`|Load all tasks in the `tasks` directory. Then, generate a temporary task. Issue the command `load all` and it should cause the `Scheduler` to generate 2 error events indicating that the tasks `cat` and `ls` already exist. The third event should be of type `INFO` and indicate that the temporary task was successfully loaded.|`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`<br/>`Scheduler::load_all_tasks(std::vector<std::string>&)`|<span style="color:green">Passed|
|`test11()`|Issue the command `load invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_load(std::vector<std::string>&)`|<span style="color:green">Passed|

### **CommandLine_verb_help.cpp**

|Testcase|Description|Part Tested|Status|
|-|-|-|-|
|`test1()`|Issue the command `help`. It should print the full menu describing usage of all available verbs in the schduler. Verify output and command count. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_help(std::vector<std::string>&)`<br/>`CommandLine::help_msg(void)`<br/>`CommandLine::help_check_msg(void)`<br/>`CommandLine::help_remove_msg(void)`<br/>`CommandLine::help_load_msg(void)`<br/>`CommandLine::help_reload_msg(void)`|<span style="color:green">Passed|
|`test2()`|Issue the command `help check`. It should print text describing usage of the `check` verb. Verify output and command count. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_help(std::vector<std::string>&)`<br/>`CommandLine::help_check_msg(void)`|<span style="color:green">Passed|
|`test3()`|Issue the command `help remove`. It should print text describing usage of the `remove` verb. Verify output and command count. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_help(std::vector<std::string>&)`<br/>`CommandLine::help_remove_msg(void)`|<span style="color:green">Passed|
|`test4()`|Issue the command `help load`. It should print text describing usage of the `load` verb. Verify output and command count. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_help(std::vector<std::string>&)`<br/>`CommandLine::help_load_msg(void)`|<span style="color:green">Passed|
|`test5()`|Issue the command `help reload`. It should print text describing usage of the `reload` verb. Verify output and command count. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_help(std::vector<std::string>&)`<br/>`CommandLine::help_reload_msg(void)`|<span style="color:green">Passed|
|`test6()`|Issue the command `help invalid`. It should cause the `Scheduler` to report a warning event. Verify the event message, event time, and event type. |`CommandLine::parse_command(void)`<br/>`CommandLine::verb_help(std::vector<std::string>&)`<br/>`CommandLine::help_msg(void)`|<span style="color:green">Passed|