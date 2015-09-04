// -*- C++ -*-
/*!
 * @file  ExcelTask.h
 * @brief Excel�̋N���ACOM�̎Q�Ƃ�����^�X�N
 * $Id$
 */


#ifndef EXCELTASK_H
#define EXCELTASK_H

#include <rtm/RTC.h>



#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

#include "ExcelControl.h"


class ExcelControl;
/*!
 * @class ExcelTask
 * @brief Excel�̋N���ACOM�̎Q�Ƃ�����X���b�h
 *
 */
class ExcelTask : public virtual coil::Task
{
public:
		/**
		*@brief �R���X�g���N�^
		*/
		ExcelTask(ExcelControl *m_rtc);
		/**
		*@brief �X���b�h�����s
		*/
		virtual int svc();
		
		ExcelControl *mrtc;	/**<�@@brief  */


};


#endif