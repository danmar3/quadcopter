#include "ControlStation.h"


ControlStation::ControlStation(){
}


ControlStation::~ControlStation(){
  
}


int ControlStation::initControlStation(){
  
  stopThread= false;

  // Start the thread for visualization which basically calls initVisualization();
  int result;
  result = pthread_create( &contStat_tid, NULL, &start_ControlStation_thread, this );
  if ( result ) throw result;
  
  return 0;
}

int ControlStation::initVisualization(){
  setenv("PYTHONPATH", ".", 0);
  Py_Initialize();
  //PySys_SetArgv(argc, argv);
  
  
  
  PyRun_SimpleString("from __future__ import division\n");
  PyRun_SimpleString("from visual import *\n");

  

  PyRun_SimpleString("sphere(pos = vector(-1,0,0), radius = 0.5, color = color.green)\n");
  PyRun_SimpleString("arrow(pos = vector(0,0,0), axis = vector(+2,0,0), color = color.yellow)\n");
  PyRun_SimpleString("arrow(pos = vector(0,0,0), axis = vector(0,+2,0), color = color.blue)\n");
  PyRun_SimpleString("arrow(pos = vector(0,0,0), axis = vector(0,0,+2), color = color.green)\n");
      
  updateScreen();
  
  Py_Finalize();
  
  return 0;
}

int ControlStation::updateScreen(){
  // get the python function
  pName = PyString_FromString("rotateFrame");
  pModule = PyImport_Import(pName);
  
  Py_DECREF(pName);

  if (pModule != NULL) {
    PyRun_SimpleString("print 'OK'");
    pFunc = PyObject_GetAttrString(pModule, "rotateframe");

    pArgs = PyTuple_New(3);
    pValue = PyFloat_FromDouble(robotRoll);
    PyTuple_SetItem(pArgs, 0, pValue);

    pValue = PyFloat_FromDouble(robotPitch);
    PyTuple_SetItem(pArgs, 1, pValue);

    pValue = PyFloat_FromDouble(robotYaw);
    PyTuple_SetItem(pArgs, 2, pValue);

    pValue = PyObject_CallObject(pFunc, pArgs);

  }

  //create body frame
  /*
  PyRun_SimpleString("f = frame()");
  PyRun_SimpleString("arrow(frame= f, pos = vector(0,0,0), axis = vector(+1,0,0), color = color.red)\n");
  PyRun_SimpleString("arrow(frame= f, pos = vector(0,0,0), axis = vector(0,+1,0), color = color.red)\n");
  PyRun_SimpleString("arrow(frame= f, pos = vector(0,0,0), axis = vector(0,0,+1), color = color.red)\n");
  PyRun_SimpleString("f.pos = (-1,0,0)");
  */
  while(not stopThread){
/* rotate the text about its origin by a fraction of a circle */  
    //PyRun_SimpleString("mytext.rotate(angle=pi/16.0)\n");

    // Convert sensor values to Python's tuple
    pArgs = PyTuple_New(3);
    pValue = PyFloat_FromDouble(robotRoll);
    PyTuple_SetItem(pArgs, 0, pValue);

    pValue = PyFloat_FromDouble(robotPitch);
    PyTuple_SetItem(pArgs, 1, pValue);

    pValue = PyFloat_FromDouble(robotYaw);
    PyTuple_SetItem(pArgs, 2, pValue);
    

    // call function to rotate
    pValue = PyObject_CallObject(pFunc, pArgs);

    /* slow the simulation down to 10 frames/second */
    PyRun_SimpleString("rate(10)\n");
  }
  return 0;
}

int ControlStation::shutDown(){
  // signal exit
  stopThread = true;
  
  // wait for exit
  pthread_join(contStat_tid ,NULL);
  
  return 0;
}

void ControlStation::handleQuit(int sig){
  try {
    shutDown();
    
  }
  catch (int error) {
    fprintf(stderr,"Warning, could not stop autopilot interface\n");
  }
}

// ------------------------------------------------------------------------------
//  Pthread Starter Helper Functions
// ------------------------------------------------------------------------------

void* start_ControlStation_thread(void *args){
  // takes an ControlStation object argument
  ControlStation *control_station = (ControlStation *)args;
  // run the object's read thread
  control_station->initVisualization();
  
  // done!
  return NULL;
}
