#ifndef CONTROLSTATION_H_
#define CONTROLSTATION_H_

#include <Python.h>
#include <pthread.h>
#include <stdlib.h>
void* start_ControlStation_thread(void *args);

class ControlStation{
 public:
  ControlStation();
  ~ControlStation();
  
  PyObject *pName, *pModule, *pDict, *pFunc;
  PyObject *pArgs, *pValue;
  
  float robotRoll;
  float robotPitch;
  float robotYaw;

  int initControlStation();
    
  int shutDown();

  int initVisualization();

  void handleQuit(int sig);
      
 private:
  
  bool stopThread;
  pthread_t contStat_tid;

  int updateScreen();

};


#endif // CONTROLSTATION_H_
