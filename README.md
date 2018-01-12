## File Input and Output in C++ with Boost::filesystem
This project demonstrates how to do file input and output in C++. Robust error handling is 
provided with error messages localized to US English and FR French. The use-case assumes the 
operator wishes to record a series of temperature readings in a data file. Data are time-stamped 
as they are entered. When input is done, the data are printed for review. 

## Program Features
- The data file is protected from accidentally being overwritten.
- The program is protected from abnormal operations related to opening non-files such as 
directories, block/character devices, sockets, or fifos.
- Filesystem permission errors are reported to the user.
- Keyboard input is checked and restricted to numeric data.
- The `Boost::filesystem` library has been namespaced to `fs` to permit the seamless upgrade to 
C++17 STL `std::filesystem` library when it becomes available.
- All the methods of the class `File_io` return `*this` (a pointer to the current instance of the 
class). This design pattern enables method chaining for logical sequences of methods. (Implement 
illogical sequences at your own risk.)

## Usage Example
```bash
$ ./file_io 

Enter a filename to save the data.
temps.txt
temps.txt exists. Overwrite it? (y/n): 
y
Enter temperatures to record.
33
44.08

Fri Jan 12, 2018 01:55:32 PM EST 33.00
Fri Jan 12, 2018 01:55:36 PM EST 44.08
    
$ export LANG=fr_FR.UTF-8
$ ./file_io 

Entrez un nom de fichier pour enregistrer les données.
temps.txt
temps.txt existe. Écrasez-le? (o/n): 
o
Entrez les températures à enregistrer.
55
34.6

Ven jan 12, 2018 13:57:03 EST 55.00
Ven jan 12, 2018 13:57:06 EST 34.60
    
$ 
```

## Caveats
- The FR French translation was provided by Google Translate and is not to be taken seriously by 
any native speaker.
- The localization implementation is not suited to anything larger than a very small (stand alone) 
coding project. It is not standard at all. Those in need of proper localization are advised to 
consider 
[Boost::locale](http://www.boost.org/doc/libs/1_65_1/libs/locale/doc/html/index.html)
    
