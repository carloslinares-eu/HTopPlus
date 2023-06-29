#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  static float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    void GetSystemJiffies();
    long system_jiffies;
};

#endif