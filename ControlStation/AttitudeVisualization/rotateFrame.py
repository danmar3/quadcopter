from __future__ import division
from visual import *
import numpy

xa= arrow(pos = vector(0,0,0), axis = vector(+1,0,0), color = color.red)
ya= arrow(pos = vector(0,0,0), axis = vector(0,+1,0), color = color.red)
za= arrow(pos = vector(0,0,0), axis = vector(0,0,+1), color = color.red)
scene.up= vector(0,0,1)

def rotX(a):
    R=numpy.identity(3)
    R[1,1]= numpy.cos(a)
    R[1,2]= -numpy.sin(a)
    R[2,1]= numpy.sin(a)
    R[2,2]= numpy.cos(a)
    return R

def rotY(a):
    R=numpy.identity(3)
    R[0,0]= numpy.cos(a)
    R[0,2]= numpy.sin(a)
    R[2,0]= -numpy.sin(a)
    R[2,2]= numpy.cos(a)
    return R

def rotZ(a):
    R=numpy.identity(3)
    R[0,0]= numpy.cos(a)
    R[0,1]= -numpy.sin(a)
    R[1,0]= numpy.sin(a)
    R[1,1]= numpy.cos(a)
    return R

def rotateframe(roll, pitch, yaw):
    print 'roll: ',roll,'pitch: ',pitch,'yaw: ',yaw
    global xa
    global xb
    global xc
    #f.rotate(angle= pitch)
    
    # get rotation matrix
    Rz= rotZ(yaw)
    Ry= rotY(roll) 
    Rx= rotX(pitch)
    
    R= Rx.dot(Ry.dot(Rz))
    
    xa.axis = vector(R[0,0],R[1,0],R[2,0])
    ya.axis = vector(R[0,1],R[1,1],R[2,1])
    za.axis = vector(R[0,2],R[1,2],R[2,2])
    return 1
