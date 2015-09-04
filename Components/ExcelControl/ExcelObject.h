// -*-C++-*-
/*!
 * @file  ExcelObject.h
 * @brief Excel�̑���
 */
#ifndef ExcelObject_H
#define ExcelObject_H

using namespace Microsoft::Office::Interop::Excel;
#define Excel   Microsoft::Office::Interop::Excel

#include <iostream>
#include <string>
#include <vector>

#include "SubFunction.h"



/**
* @class ExcelObject
*@brief Excel�𑀍삷��N���X
*/

ref class ExcelObject
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	ExcelObject();
	static ExcelObject^ Obj;	/**<�@@brief  */
	
	/**
	*@brief ���O���烏�[�N�V�[�g���擾����֐�
	* @param sn �V�[�g��
	* @return �V�[�g�I�u�W�F�N�g
	*/
	Excel::Worksheet^ getWorksheet(std::string sn);
	
	/**
	*@brief �ۑ��p���[�N�V�[�g�ɏ������ފ֐�
	* @param sf �������ޕ�����
	*/
	void saveRTC(std::vector<std::string> sf);
	
	/**
	*@brief �f�[�^�|�[�g�̏���ۑ��p���[�N�V�[�g����ǂݍ��ފ֐�
	* @return �ǂݍ��񂾕�����
	*/
	std::vector<std::string> loadRTC();
	
	/**
	*@brief �Z���̐F�𖳐F�ɂ���֐�
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param leng �s�͈̔�
	*/
	void resetCellColor(int c, std::string l, std::string sn, std::string leng);
	

	/**
	*@brief �P��̃Z���̕������ύX����֐�
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param val ���͂��镶����
	*/
	
	void setCellStringSingle(int c, std::string l, std::string sn, std::string val);
	
	/**
	*@brief �P��̃Z���̒l��ύX����֐�
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param val ���͂���l
	*/
	template <typename T>
	void setCellValueSingle(int c, std::string l, std::string sn, T val)
	{
		int t_l = convertStrToVal(l);
		Excel::Worksheet^ws = getWorksheet(sn);
		if(ws != nullptr)
		{
			if(c > 0 && t_l > 0)
			{
				Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c,t_l]);
				c1->Value2 = val;
			}
		}
	}

	
	/**
	*@brief �P��̃Z���̒l���擾����֐�
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @return �Z���̒l
	*/
	std::string getCellValueSingle(int c, std::string l, std::string sn)
	{
		int t_l = convertStrToVal(l);
		Excel::Worksheet^ws = getWorksheet(sn);
		if(ws != nullptr)
		{
			if(c > 0 && t_l > 0)
			{
				Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c,t_l]);
			
				return MarshalString(c1->Value2->ToString());
			}
		}
		return "error";
	}
	
	/**
	*@brief 1�ȏ�̃Z���̒l��ύX����֐�
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param state ����ړ�����ꍇ��True
	* @param v  ���͂���l
	*/
	template <typename T>
	void setCellValue(int c, std::string l, std::string sn, bool state, std::vector<std::vector<T>> v)
	{
		Excel::Worksheet^ws = getWorksheet(sn);

		
		if(ws != nullptr)
		{
			int t_l = convertStrToVal(l);

			int mnum = v.size();
			if(!state)
				mnum = 1;
			for(int i=0;i < mnum;i++)
			{
				if(c+i > 0 && t_l > 0)
				{
					Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c+i,t_l]);
					Excel::Range^c2 = safe_cast<Excel::Range^>(ws->Cells[c+i,t_l+v[i].size()-1]);
					
					
					Excel::Range^mr = ws->Range[c1,c2];		
					
					array<T>^dt = gcnew array<T>(v[i].size());
					//std::cout << v.size() << std::endl;
					for(int j=0;j < v[i].size();j++)
					{
						
						dt[j] = v[i][j];//gcnew System::String(v[i].c_str());
						
						//mr->Value2 = gcnew System::String(v.c_str());
						//ws->Cells[c,l] =  gcnew System::String(v.c_str());
					}

					
					
					mr->Value2 = dt;
				}
			}

			
			//System::Runtime::InteropServices::Marshal::ReleaseComObject(c1);
			//System::Runtime::InteropServices::Marshal::ReleaseComObject(c2);
			//System::Runtime::InteropServices::Marshal::ReleaseComObject(mr);
			
		}
	}

	
	
	
	/**
	*@brief 1�ȏ�̃Z���̒l���擾����֐�
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param state ����ړ�����ꍇ��True
	* @return �擾�����l
	*/
	template <typename T>
	std::vector<T> getCellValue(int c, std::string l, std::string sn, std::string leng)
	{
		Excel::Worksheet^ws = getWorksheet(sn);

		std::vector<T> v;

		

		if(ws != nullptr)
		{
			int t_l = convertStrToVal(l);
			int t_leng = t_l;
			
			try{
				t_leng = convertStrToVal(leng);		
			}
			catch(...)
			{
				t_leng = t_l;
			}
			if(t_l > t_leng)
				t_leng = t_l;
			
			

			

			if(c > 0 && t_l > 0 && t_leng >= t_l)
			{
				

				if(c > 1){
					

					Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c-1,t_l]);
					Excel::Range^c2 = safe_cast<Excel::Range^>(ws->Cells[c-1,t_leng]);
					
					
					Excel::Range^mr = ws->Range[c1,c2];

					mr->Interior->ColorIndex = 0;
				}

				{
					Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c,t_l]);
					Excel::Range^c2 = safe_cast<Excel::Range^>(ws->Cells[c,t_leng]);
					
					
					Excel::Range^mr = ws->Range[c1,c2];

					mr->Interior->ColorIndex = 6;
					//mr->Interior->Color = System::Drawing::Color::FromArgb(red, blue, green);
					
				}
			}

			//Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c,l]);
			//Excel::Range^c2 = safe_cast<Excel::Range^>(ws->Cells[c,l+leng-1]);
			
			
			//Excel::Range^mr = ws->Range[c1,c2];	


			
			for(int i=0;i < t_leng-t_l+1;i++)
			{
				if(c > 0 && t_l+i > 0)
				{
					Excel::Range^c1 = safe_cast<Excel::Range^>(ws->Cells[c,t_l+i]);
					/*if(c > 1)
					{
						Excel::Range^c2 = safe_cast<Excel::Range^>(ws->Cells[c-1,l+i]);
						c2->Interior->ColorIndex = 0;
					}
					c1->Interior->ColorIndex = 6;*/

					try{
						T c_tmp;
						coil::stringTo<T>(c_tmp,MarshalString(c1->Value2->ToString()).c_str());
						
						v.push_back(c_tmp);
						
					}
					catch(...)
					{
						v.push_back(0);
					}
				}
				//Excel::Range^mr2 = safe_cast<Excel::Range^>(mr[0,i]);
				//v.push_back(string2binary<T>(MarshalString(mr[0,i]->ToString()),10));
				//v.push_back(MarshalString(mr2->Value2->ToString()));
				//System::Runtime::InteropServices::Marshal::ReleaseComObject(mr2);
			}

			
			//mr->Text->ToString();
			
			
			//System::Runtime::InteropServices::Marshal::ReleaseComObject(mr);
			//System::Runtime::InteropServices::Marshal::ReleaseComObject(c1);
			//System::Runtime::InteropServices::Marshal::ReleaseComObject(c2);
			
			
		}

		return v;
	}
	
	/**
	*@brief Excel�t�@�C�����J���֐�
	* @param fn �t�@�C����
	*/
	void Open(System::String^ fn);
	
	/**
	*@brief COM�I�u�W�F�N�g���������֐�
	*/
	void Close();

	/**
	*@brief �f�[�^�擾���̃Z���̔w�i�̐F��ݒ�
	* @param r �w�i�̐F(R)
	* @param g �w�i�̐F(G)
	* @param b �w�i�̐F(B)
	*/
	void setColor(int r, int g, int b);

	int red, green, blue; /**<�@@brief  */

	System::String^ filename; /**<�@@brief  */
	Excel::Application^ xlApplication; /**<�@@brief  */
	Excel::Workbooks^ xlWorkbooks; /**<�@@brief  */
	Excel::Workbook^ xlWorkbook; /**<�@@brief  */
	Excel::Sheets^ xlWorksheets; /**<�@@brief  */

	System::Collections::Generic::List<Excel::Worksheet^>^ xlWorksheet; /**<�@@brief  */

};

#endif