// -*-C++-*-
/*!
 * @file  ExcelTask.cpp
 * @brief Excel�̋N���ACOM�̎Q�Ƃ�����X���b�h
 *
 */


#include "stdafx.h"
#include "ExcelTask.h"
#include "ExcelObject.h"



ExcelTask::ExcelTask(ExcelControl *m_rtc)
{
	mrtc = m_rtc;
}





int ExcelTask::svc()
{
	
	
	ExcelObject::Obj = gcnew ExcelObject();
	std::string filePath = mrtc->getFileName();
	if(filePath == "NewFile")
	{
		filePath = "";
	}
    //coil::Properties& prop(::RTC::Manager::instance().getConfig());
    //getProperty(prop, "excel.filename", filePath);
	
	coil::replaceString(filePath,  "/", "\\");
	
    ExcelObject::Obj->Open(gcnew System::String(filePath.c_str()));
	//ExcelObject::Obj->filename = "";

	

	mrtc->load();
	return 0;
}


