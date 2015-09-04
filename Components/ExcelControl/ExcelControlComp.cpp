// -*-C++-*-
/*!
 * @file  ExcelControlComp.cpp
 * @brief Standalone component
 *
 */

#include "stdafx.h"
#include "Form1.h"
#include <rtm/Manager.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "ExcelControl.h"

using namespace ExcelRTC;



void MyModuleInit(RTC::Manager* manager)
{
  ExcelControlInit(manager);
  RTC::RtcBase* comp;

  comp = manager->createComponent("ExcelControl");

  if (comp==NULL)
  {
	  
    std::cerr << "Component create failed." << std::endl;
    abort();
  }

  


  return;
}




[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// �R���g���[�����쐬�����O�ɁAWindows XP �r�W���A�����ʂ�L���ɂ��܂�
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

	RTC::Manager* manager;


	
	int argc = args->Length;
	char** argv = new char*[argc];
	for(int i=0;i < argc;i++)
	{
		argv[i] = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(args[i]).ToPointer();
		/*array<unsigned char>^ b = System::Text::Encoding::UTF8->GetBytes(args[i]);
		argv[i] = new char[b->Length];
		for(int j=0;j < b->Length;j++)
		{
			argv[i][j] = b[j];
		}*/
		//argv[i] = const_cast<char*>(MarshalString(args[i]).c_str());
		//std::cout << argv[i] << std::endl;
		
	}
	manager = RTC::Manager::init(argc, argv);

	



	manager->init(argc, argv);
	manager->setModuleInitProc(MyModuleInit);
	manager->activateManager();
	manager->runManager(true);


	


	// ���C�� �E�B���h�E���쐬���āA���s���܂�
	System::Windows::Forms::Application::Run(gcnew Form1());
	return 0;
}
