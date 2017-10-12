//
// Created by Patrick Moffitt on 10/10/17.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "file_io.h"
#include "boost/lexical_cast.hpp"
#include "boost/format.hpp"
#include "boost/filesystem.hpp"

namespace std {
    namespace filesystem = boost::filesystem;
}

namespace fs = std::filesystem;

using std::cout;
using std::cerr;
using std::cin;
using std::endl;


void File_io::reset_cin() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

void File_io::filename_prompt() {
    std::cout << endl << "Enter a filename to save the data." << std::endl;
};

File_io File_io::get_filename() {
    char overwrite{'y'};
    filename_prompt();
    cin >> filename;
    if (fs::is_directory(fs::status(filename))) {
        cerr << filename << " is a directory." << endl;
        get_filename();
    }
    if (fs::is_symlink(fs::status(filename))) {
        cerr << filename << " is a symbolic link." << endl;
        get_filename();
    }
    if (fs::is_other(fs::status(filename))) {
        cerr << filename << " is possibly a block/character device, socket, or fifo." << endl;
        get_filename();
    }
    if (fs::is_regular_file(fs::status(filename))) {
        cerr << filename << " exists. Overwrite it? (y/n): " << endl;
        cin >> overwrite;
        if (overwrite == 'n') get_filename();
    }
    return *this;
};

File_io File_io::get_temps() {
    reset_cin();
    cout << "Enter temperatures to record." << endl;
    while (std::getline(std::cin, number) and number.length() > 0) {
        try {
            temperature = boost::lexical_cast<double>(number);
            epoch = time(nullptr);
            data.push_back(Reading{epoch, temperature});
        } catch (boost::bad_lexical_cast &) {
            cerr << __FUNCTION__ << " Error: " << number << " isn't a number." << endl;
        }
    }
    return *this;
};

File_io File_io::save() {
    std::ofstream ofs{filename};
    if (!ofs) {
        cerr << "Error: can't open " << filename << " for writing." << endl;
    } else {
        for (auto item : data) {
            ofs << item.time << " " << item.temperature << endl;
        }
        data.clear();
    }
    return *this;
};

File_io File_io::restore() {
    std::ifstream ifs{filename};
    if (!ifs) {
        cerr << "Error: can't open " << filename << " for reading." << endl;
    } else {
        data.clear();
        while (ifs >> epoch >> temperature) {
            data.push_back(Reading{epoch, temperature});
        }
    }
    return *this;
};

File_io File_io::print() {
    cout.imbue(std::locale("en_US.utf-8"));
    if (data.empty()) {
        cerr << "Error: no data found." << endl;
    } else {
        for (auto item : data) {
            cout << std::put_time(std::localtime(&item.time), "%a %b %d, %Y %r %Z")
                 << " "
                 << boost::format("%.2f") % item.temperature
                 << endl;
        }
    }
    return *this;
};
