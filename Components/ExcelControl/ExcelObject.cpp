/*!
 * @file  ExcelObject.cpp
 * @brief Excel�̑���
 *
 */

#include "stdafx.h"
#include "ExcelObject.h"
#include "SubFunction.h"
#include <iostream>


ExcelObject::ExcelObject()
{
	xlApplication = nullptr;
	xlWorkbooks = nullptr;
	xlWorkbook = nullptr;
	xlWorksheets = nullptr;

	xlWorksheet = gcnew System::Collections::Generic::List<Excel::Worksheet^>();
	filename = gcnew System::String(" ");
	//Open("");

	red = 255;
	green = 255;
	blue = 0;
}

void ExcelObject::setColor(int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
}

Excel::Worksheet^ ExcelObject::getWorksheet(std::string sn)
{
	for(int i=0;i < xlWorksheet->Count;i++)
	{
		std::string ts = MarshalString(xlWorksheet[i]->Name);
		
		if(ts == sn)
		{
			return xlWorksheet[i];
		}
	}
	return nullptr;
}

void ExcelObject::resetCellColor(int c, std::string l, std::string sn, std::string len)
{
	Excel::Worksheet^ws = getWorksheet(sn);
	if(ws != nullptr)
	{
		int t_l = convertStrToVal(l);
		int t_leng = convertStrToVal(len);


		if(c > 0 && t_l > 0 && t_leng >= t_l)
		{
			Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c,t_l]);
			Excel::Range^c2 = safe_cast<Excel::Range^>(ws->Cells[c,t_leng]);
			
			
			Excel::Range^mr = ws->Range[c1,c2];

			mr->Interior->ColorIndex = 0;
		}
		

	}
}

void ExcelObject::setCellStringSingle(int c, std::string l, std::string sn, std::string val)
{
	int t_l = convertStrToVal(l);
	Excel::Worksheet^ws = getWorksheet(sn);
	if(ws != nullptr)
	{
		if(c > 0 && t_l > 0)
		{
			Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c,t_l]);
			c1->Value2 = gcnew System::String(val.c_str());
		}
	}
}

void ExcelObject::saveRTC(std::vector<std::string> sf)
{
	Excel::Worksheet^ws = getWorksheet("�ۑ��p");

	if(ws != nullptr)
	{
		for(int i=0;i < sf.size();i++)
		{
			Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[1+i,1]);
			c1->Value2 = gcnew System::String(sf[i].c_str());
		}
	}
}
std::vector<std::string> ExcelObject::loadRTC()
{
	Excel::Worksheet^ws = getWorksheet("�ۑ��p");
	std::vector<std::string> v;

	if(ws != nullptr)
	{
		for(int i=0;i < 100;i++)
		{
			Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[1+i,1]);
			//c1->Value2 = gcnew System::String("");
			//c1->Text->ToString();
			try{
				std::string tmp = MarshalString(c1->Text->ToString());
				if(tmp == "")
				{
					return v;
				}
				else
				{
					v.push_back(tmp);
				}
			}
			catch(...)
			{
				return v;
			}
		}
		
	}
	return v;
}



void ExcelObject::Open(System::String^ fn)
{
	
	if(filename == fn)
	{
		return;
	}

	Excel::Application^ t_xlApplication;
	Excel::Workbooks^ t_xlWorkbooks;
	Excel::Workbook^ t_xlWorkbook;

	
	filename = fn;
	 try {
		 try {
			System::Object^tObject = System::Runtime::InteropServices::Marshal::GetActiveObject("Excel.Application");
			t_xlApplication = static_cast<Excel::Application^>(tObject);
			}
		 catch(...){
				t_xlApplication = gcnew Excel::Application();
			}
			t_xlApplication->Visible = true;
			try {
				t_xlWorkbooks = t_xlApplication->Workbooks;
				

				try {
					if(filename == "")
					{
						t_xlWorkbook = t_xlWorkbooks->Add(System::Reflection::Missing::Value);
					}
					else
					{
						t_xlWorkbook = t_xlWorkbooks->Open(filename, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value, System::Reflection::Missing::Value);
					}
					
					try{
						Close();
						xlApplication = t_xlApplication;
						xlWorkbooks = t_xlWorkbooks;
						xlWorkbook = t_xlWorkbook;


						xlWorksheets = xlWorkbook->Worksheets;
						
						int count = xlWorksheets->Count;

						for(int i=1;i <= count;i++)
						{
							xlWorksheet->Add(static_cast<Worksheet^>(xlWorksheets->Item[i]));
						}
						
					}
					catch(...)
					{

					}
				}
				catch(...)
				{

				}
			}
			catch(...)
			{

			}
	 }
	 catch(...)
	 {

	 }
	 
	 Excel::Worksheet^ws = getWorksheet("�ۑ��p");
	 if(ws == nullptr)
	 {
		 xlWorksheets->Add(System::Reflection::Missing::Value,xlWorksheet[xlWorksheet->Count-1],System::Reflection::Missing::Value,System::Reflection::Missing::Value);
		 Worksheet^ wsp = static_cast<Worksheet^>(xlWorksheets->Item[xlWorksheets->Count]);
		 wsp->Name = "�ۑ��p";
		 xlWorksheet->Add(wsp);
		 xlWorksheets->Select(System::Reflection::Missing::Value);

		 //Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[1,1]);
		 //c1->Value2 = gcnew System::String("a");
		 
		 //xlWorksheets->Add("�ۑ��p",System::Reflection::Missing::Value,System::Reflection::Missing::Value,System::Reflection::Missing::Value);
	 }
	 else
	 {
		
	 }

	
			
}

void ExcelObject::Close()
{
	int count = xlWorksheet->Count;
	for(int i=1;i < count;i++)
	{
		if (xlWorksheet[i] != nullptr) {
			System::Runtime::InteropServices::Marshal::ReleaseComObject(xlWorksheet[i]);
		}
	}
	xlWorksheet->Clear();
	if (xlWorksheets != nullptr) {
		System::Runtime::InteropServices::Marshal::ReleaseComObject(xlWorksheets);
	}
	xlWorksheets = nullptr;

	if (xlWorkbook != nullptr) {
		System::Runtime::InteropServices::Marshal::ReleaseComObject(xlWorkbook);
	}
	xlWorkbook = nullptr;

	if (xlWorkbooks != nullptr) {
		System::Runtime::InteropServices::Marshal::ReleaseComObject(xlWorkbooks);
	}
	xlWorkbooks = nullptr;

	if (xlApplication != nullptr) {
		System::Runtime::InteropServices::Marshal::ReleaseComObject(xlApplication);
	}
	xlApplication = nullptr;
}