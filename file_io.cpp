//
// Created by Patrick Moffitt on 10/10/17.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <clocale>
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
using std::string;
using std::strcat;


void File_io::reset_cin() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

void File_io::filename_prompt() {
    std::cout << endl << FILE_IO_ASK_FILENAME_PROMPT << std::endl;
};

File_io File_io::get_filename() {
    char overwrite{'y'};
    filename_prompt();
    cin >> filename;
    if (filename.length() == 0) get_filename();
    if (fs::is_directory(fs::status(filename))) {
        cerr << filename << FILE_IO_FILE_IS_DIR << endl;
        get_filename();
    }
    if (fs::is_symlink(fs::status(filename))) {
        cerr << filename << FILE_IO_FILE_IS_SYM_LINK << endl;
        get_filename();
    }
    if (fs::is_other(fs::status(filename))) {
        cerr << filename << FILE_IO_FILE_IS_OTHER << endl;
        get_filename();
    }
    if (fs::is_regular_file(fs::status(filename))) {
        cerr << filename << FILE_IO_FILE_EXISTS_PROMPT << endl;
        while (cin >> overwrite) {
            if (overwrite == *FILE_IO_NO_CHAR) {
                get_filename();
            } else if (overwrite == *FILE_IO_YES_CHAR) {
                break;
            }
        }
    }
    return *this;
};

File_io File_io::get_temps() {
    reset_cin();
    cout << FILE_IO_ENTER_TEMPS_PROMPT << endl;
    while (std::getline(std::cin, number) and number.length() > 0) {
        try {
            temperature = boost::lexical_cast<double>(number);
            epoch = time(nullptr);
            data.push_back(Reading{epoch, temperature});
        } catch (boost::bad_lexical_cast &) {
            cerr << FILE_IO_ERROR << number << FILE_IO_INPUT_NOT_NUMBER << endl;
        }
    }
    return *this;
};

File_io File_io::save() {
    std::ofstream ofs{filename};
    if (!ofs) {
        cerr << FILE_IO_OPEN_ERROR << filename << FILE_IO_FILE_MODE_WRITING << endl;
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
        cerr << FILE_IO_OPEN_ERROR << filename << FILE_IO_FILE_MODE_READING << endl;
    } else {
        data.clear();
        while (ifs >> epoch >> temperature) {
            data.push_back(Reading{epoch, temperature});
        }
    }
    return *this;
};

File_io File_io::print() {
    cout.imbue(std::locale(posix_lang));
    const char *localtime_format = ("%a %b %d, %Y " + time_format  + " %Z").c_str();
    if (data.empty()) {
        cerr << FILE_IO_NO_DATA_ERROR << filename << endl;
    } else {
        for (auto item : data) {
            cout << std::put_time(std::localtime(&item.time), localtime_format)
                 << " "
                 << boost::format("%.2f") % item.temperature
                 << endl;
        }
    }
    return *this;
};

File_io File_io::set_locale() {
    std::array<string, 3> env_langs = {"LANG", "LC_CTYPE", "LC_ALL"};
    char *locale_name = nullptr;
    for (string &lang : env_langs) {
        locale_name = std::getenv(lang.c_str());
        if (locale_name != nullptr) break;
    }
    if (locale_name == nullptr) {
        std::setlocale(LC_CTYPE, "C");
    }
    posix_lang = static_cast<std::string>(locale_name);
    if (posix_lang == "fr_FR.UTF-8") {
        time_format = "%T";
        FILE_IO_ASK_FILENAME_PROMPT = "Entrez un nom de fichier pour enregistrer les données.";
        FILE_IO_FILE_IS_DIR         = " est un répertoire.";
        FILE_IO_FILE_IS_SYM_LINK    = " est un lien symbolique.";
        FILE_IO_FILE_IS_OTHER       = " est peut-être un périphérique bloc / caractère,"
                                      " socket ou fifo.";
        FILE_IO_FILE_EXISTS_PROMPT  = " existe. Écrasez-le? (o/n): ";
        FILE_IO_ENTER_TEMPS_PROMPT  = "Entrez les températures à enregistrer.";
        FILE_IO_INPUT_NOT_NUMBER    = " n'est pas un nombre.";
        FILE_IO_ERROR               = "Erreur: ";
        FILE_IO_OPEN_ERROR          = "Erreur: impossible d'ouvrir ";
        FILE_IO_FILE_MODE_WRITING   = " pour l'écriture.";
        FILE_IO_FILE_MODE_READING   = " pour la lecture.";
        FILE_IO_NO_DATA_ERROR       = "Erreur: aucune donnée trouvée dans ";
        FILE_IO_YES_CHAR            = "o";
        FILE_IO_NO_CHAR             = "n";
    } else {
        if (posix_lang == "en_US.UTF-8") std::setlocale(LC_CTYPE, locale_name);
        time_format = "%r";
        FILE_IO_ASK_FILENAME_PROMPT = "Enter a filename to save the data.";
        FILE_IO_FILE_IS_DIR         = " is a directory.";
        FILE_IO_FILE_IS_SYM_LINK    = " is a symbolic link.";
        FILE_IO_FILE_IS_OTHER       = " is possibly a block/character device, socket, or fifo.";
        FILE_IO_FILE_EXISTS_PROMPT  = " exists. Overwrite it? (y/n): ";
        FILE_IO_ENTER_TEMPS_PROMPT  = "Enter temperatures to record.";
        FILE_IO_INPUT_NOT_NUMBER    = " isn't a number.";
        FILE_IO_ERROR               = "Error: ";
        FILE_IO_OPEN_ERROR          = "Error: can't open ";
        FILE_IO_FILE_MODE_WRITING   = " for writing.";
        FILE_IO_FILE_MODE_READING   = " for reading.";
        FILE_IO_NO_DATA_ERROR       = "Error: no data found in ";
        FILE_IO_YES_CHAR            = "y";
        FILE_IO_NO_CHAR             = "n";
    }
    return *this;
}