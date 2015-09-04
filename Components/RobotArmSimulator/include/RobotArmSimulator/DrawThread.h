#ifndef DRAWTHREAD_H
#define DRAWTHREAD_H


#include <coil/Task.h>

#include <stdio.h>
#include <stdlib.h>
#include <drawstuff/drawstuff.h>
#include "SimulatorObj.h"



class DrawThread : public virtual coil::Task
{
public:
		DrawThread(SimulatorObj *so);
		/*
		*スレッド実行関数
		*/
		virtual int svc();
		void setDrawStuff();
		void drawBox(MyLink *body);
		void drawCylinder(MyLink *body);
		void drawRobot();
		

		


private:
	SimulatorObj *m_so;
	dsFunctions   fn;

};

#endif