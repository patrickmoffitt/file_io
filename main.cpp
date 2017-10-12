//
// Created by Patrick Moffitt on 10/10/17.
//

#include "file_io.h"

int main() {

    File_io fio;

    fio.get_filename()
            .get_temps()
            .save()
            .restore()
            .print();
    
    return 0;
}