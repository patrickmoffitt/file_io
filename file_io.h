//
// Created by Patrick Moffitt on 10/10/17.
//

#ifndef INC_10_FILE_IO_FILE_IO_H
#define INC_10_FILE_IO_FILE_IO_H

#include <string>
#include <ctime>
#include <vector>

struct Reading {
    std::time_t time;
    double temperature;
};

class File_io {
    std::vector<Reading> data;
    double temperature{0.0};
    std::string number{};
    std::time_t epoch;

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
};

#endif //INC_10_FILE_IO_FILE_IO_H
