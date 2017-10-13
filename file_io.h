//
// Created by Patrick Moffitt on 10/10/17.
//

#ifndef INC_10_FILE_IO_FILE_IO_H
#define INC_10_FILE_IO_FILE_IO_H

#include <string>
#include <ctime>
#include <vector>

using std::string;

struct Reading {
    std::time_t time;
    double temperature;
};

class File_io {
    std::vector<Reading> data;
    double temperature{0.0};
    string number{};
    std::time_t epoch{0};
    string posix_lang{"en_US.UTF-8"};
    string time_format{"%T"};
    void reset_cin();


    void filename_prompt();

public:
    File_io() = default;

    std::string filename{};

    File_io get_filename();

    File_io get_temps();

    File_io save();

    File_io restore();

    File_io print();

    File_io set_locale();

    const char *FILE_IO_ASK_FILENAME_PROMPT;
    const char *FILE_IO_FILE_IS_DIR;
    const char *FILE_IO_FILE_IS_SYM_LINK;
    const char *FILE_IO_FILE_IS_OTHER;
    const char *FILE_IO_FILE_EXISTS_PROMPT;
    const char *FILE_IO_ENTER_TEMPS_PROMPT;
    const char *FILE_IO_INPUT_NOT_NUMBER;
    const char *FILE_IO_ERROR;
    const char *FILE_IO_OPEN_ERROR;
    const char *FILE_IO_FILE_MODE_WRITING;
    const char *FILE_IO_FILE_MODE_READING;
    const char *FILE_IO_NO_DATA_ERROR;
    const char *FILE_IO_YES_CHAR;
    const char *FILE_IO_NO_CHAR;
};

#endif //INC_10_FILE_IO_FILE_IO_H
