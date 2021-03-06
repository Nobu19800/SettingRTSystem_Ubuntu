/*!
* @file  DrawThread.h
* @brief シミュレーション描画関連のクラス
*
*/

#ifndef DRAWTHREAD_H
#define DRAWTHREAD_H


#include <coil/Task.h>

#include <stdio.h>
#include <stdlib.h>
#include <drawstuff/drawstuff.h>
#include "SimulatorObj.h"



/**
* @class DrawThread
*@brief シミュレーションの描画をするスレッド
*/
class DrawThread : public virtual coil::Task
{
public:
		/**
		*@brief コンストラクタ
		*/
		DrawThread(SimulatorObj *so);
		
		/**
		*@brief スレッド実行関数
		* @return 
		*/
		virtual int svc();
		/**
		*@brief DrawStuff初期化
		*/
		void setDrawStuff();
		/**
		*@brief 直方体描画
		* @param body ボディオブジェクト
		*/
		void drawBox(MyLink *body);
		/**
		*@brief 円柱描画
		* @param body ボディオブジェクト
		*/
		void drawCylinder(MyLink *body);
		/**
		*@brief 全ボディ描画
		*/
		void drawRobot();
		

		


private:
	SimulatorObj *m_so;
	dsFunctions   fn;

};

#endif