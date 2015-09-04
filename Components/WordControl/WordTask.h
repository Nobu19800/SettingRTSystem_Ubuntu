// -*- C++ -*-
/*!
 * @file  WordTask.h
 * @brief Wordの起動、COMの参照をするスレッド
 * $Id$
 */


#ifndef WORDTASK_H
#define WORDTASK_H

#include <rtm/RTC.h>



#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

#include "WordControl.h"

class WordControl;

/*!
 * @class WordTask
 * @brief Wordの起動、COMの参照をするスレッド
 *
 */
class WordTask : public virtual coil::Task
{
public:
		/**
		*@brief コンストラクタ
		*/
		WordTask(WordControl *mrtc);
		/**
		*@brief スレッドを実行
		*/
		virtual int svc();
		WordControl *mrtc;
		


};

template <class T>
void getProperty(coil::Properties& prop, const char* key, T& value)
{
if (prop.findNode(key) != 0)
  {
    T tmp;
    if (coil::stringTo(tmp, prop[key].c_str()))
      {
        value = tmp;
      }
  }
}


#endif