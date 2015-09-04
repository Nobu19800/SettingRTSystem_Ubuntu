#ifndef SIMULATOROBJ_H
#define SIMULATOROBJ_H

#define dDOUBLE

#include <coil/Mutex.h>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <ode/ode.h>


#include "RobotArm.h"



#ifdef _MSC_VER
#pragma warning(disable:4244 4305)  // for VC++, no precision loss complaints
#endif






typedef struct {
  dBodyID  body;
  dGeomID  geom;
  dJointID joint;
  int  dir;
  float  red, green, blue;
  dReal    m,r,x,y,z,lx,ly,lz, the, dthe, ddthe, axisx, axisy, axisz, Tthe, Tdthe, Tddthe, tau, jx,jy,jz; // éøó (weight)ÅCîºåa(radius)ÅCà íu(positin:x,y,z)
} MyLink;



class SimulatorObj
{
public:
	SimulatorObj();
	~SimulatorObj();
	coil::Mutex mu;
	MyLink link0, link1, link2, link3, linkhs, linkh, linkf[2];
	RobotArm *rb;
	double st;
	double gravity;
	bool pause;
	dWorldID      world;       
	dSpaceID      space;       
	dGeomID       ground;       
	dJointGroupID contactgroup; 

	void makeParam();
	void setBox(MyLink *body);
	void setCylinder(MyLink *body);
	void setHinge(MyLink *body1, MyLink *body2);
	void setSlider(MyLink *body1, MyLink *body2);
	void setFixed(MyLink *body1, MyLink *body2);
	void makeRobot();
	void controlHinge(MyLink *body, dReal theta);
	void controlSlider(MyLink *body, dReal length);
	void control();
	void update();
	void destroyRobot();


	void m_nearCallback(dGeomID o1, dGeomID o2);


	



};



#endif