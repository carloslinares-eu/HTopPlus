#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "os_files.h"
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
public:
    explicit Process(OSFiles &FilesRef);

    int Pid();                               // TODO: See src/process.cpp
    std::string User();                      // TODO: See src/process.cpp
    std::string Command();                   // TODO: See src/process.cpp
    float CpuUtilization();                  // TODO: See src/process.cpp
    std::string Ram();                       // TODO: See src/process.cpp
    long int UpTime();                       // TODO: See src/process.cpp
    bool operator<(Process const &a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
private:
    OSFiles& files_ref;

};

#endif