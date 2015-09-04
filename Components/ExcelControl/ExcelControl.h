// -*-C++-*-
/*!
 * @file  ExcelControl.h
 * @brief ExcelControlComponent
 */
#ifndef EXCELCONTROL_H
#define EXCELCONTROL_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <vector>
#include <string>
#include <sstream>

#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>

#include "SubFunction.h"
#ifdef CREATE_EXE_EXCELRTC
	#include "Form1.h"
#else
	#include "ExcelObject.h"
#endif


using namespace RTC;

#include "SpreadSheetSVC_impl.h"
#include "ExcelTask.h"
#include "ExcelDataPort.h"


class ExcelTask;
class ExcelControl;
class ExcelPortBase;
class OtherPort;





void ListRecursive(CosNaming::NamingContext_ptr context,std::vector<OtherPort> &rtclist,std::string &name, TreeObject *to);

int rtc_get_rtclist(RTC::CorbaNaming &naming,std::vector<OtherPort> &rtclist, TreeObject *to, std::string IP_adress);










/**
*@brief �f�[�^�|�[�g��ڑ�
* @param p1 �ڑ�����f�[�^�|�[�g
* @param p2 �ڑ�����f�[�^�|�[�g
*/
void portConnect(PortService_ptr p1, PortService_var p2);



/**
 * @class ExcelControl
*@brief Excel�𑀍삷��RT�R���|�[�l���g
*/
class ExcelControl
  : public RTC::DataFlowComponentBase
{
 public:
  
	/**
	*@brief �R���X�g���N�^
	* @param manager �}�l�[�W���I�u�W�F�N�g
	*/
  ExcelControl(RTC::Manager* manager);

  /**
	*@brief �f�X�g���N�^
	*/
  ~ExcelControl();

   
  /**
  *@brief �����������p�R�[���o�b�N�֐�
  * @return RTC::ReturnCode_t
  */
   virtual RTC::ReturnCode_t onInitialize();

   
   /**
   *@brief ���������p�R�[���o�b�N�֐�
   * @param ec_id target ExecutionContext Id
   * @return RTC::ReturnCode_t
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);
   
   
   /**
   *@brief �s���������̃R�[���o�b�N�֐�
   * @param ec_id target ExecutionContext Id
   * @return RTC::ReturnCode_t
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

   /**
   *@brief �I�������̃R�[���o�b�N�֐�
   * @return RTC::ReturnCode_t
   */
   virtual RTC::ReturnCode_t onFinalize();

   
   /**
   *@brief �f�[�^�|�[�g���쐬����֐�
   * @param op �ڑ�����f�[�^�|�[�g
   * @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param leng �s�͈̔�
	* @param mstate ����ړ�����ꍇ��True
   * @return �쐬�����f�[�^�|�[�g
   */
   ExcelPortBase* createPort(OtherPort &op, int c, std::string l, std::string sn, std::string leng, bool mstate);
   
   /**
   *@brief �f�[�^�|�[�g���폜����֐�
   * @param op �폜����f�[�^�|�[�g
   */
   void deleteOtherPort(OtherPort &op);
   /**
   *@brief �S�Ẵf�[�^�|�[�g���폜����֐�
   */
   void deleteAllPort();
   
   /**
   *@brief RTC�̏���ۑ��p�V�[�g�ɏ������ފ֐�
   */
   void save();
   
   /**
   *@brief RTC�̏����ُ�p�V�[�g���ǂݍ��ފ֐�
   */
   void load();
   
   /**
   *@brief �f�[�^���������ޗ������������
   * @param mpb �f�[�^�|�[�g�I�u�W�F�N�g
   */
   void resetPort(ExcelPortBase* mpb);
   
   /**
   *@brief �S�Ẵf�[�^���������ޗ������������
   */
   void resetAllPort();
   
   /**
   *@brief �R���t�B�M�����[�V�����p�����[�^���ύX���ꂽ�Ƃ��ɌĂяo�����֐�
   */
   void configUpdate();

   /**
   *@brief �Z���̖��O���L��
   */
   void update_cellName();


  
   /**
   *@brief �֘A�t�������f�[�^�|�[�g�̏���
   * @param ip �C���|�[�g
   */
   void updateAPort(ExcelPortBase* ip);

   
   /**
   *@brief �Z���ɒl���������ފ֐�
   * @param dt �������ރf�[�^
   * @param pb �f�[�^�|�[�g�I�u�W�F�N�g
   */
    template <typename T>
   void setCellData(std::vector<std::vector<T>> dt, ExcelPortBase *pb)
	{
		
		ExcelObject::Obj->setCellValue<T>(pb->col+pb->num, pb->low, pb->sheetName, pb->state, dt);
		
	}
   
   /**
   *@brief �Z���̒l���擾����֐�
   * @param pb �f�[�^�|�[�g�I�u�W�F�N�g
   * @return �擾�����f�[�^
   */
    template <typename T>
	std::vector<T> getCellData(ExcelPortBase *pb)
	{
		std::vector<T> td = ExcelObject::Obj->getCellValue<T>(pb->col+pb->num, pb->low, pb->sheetName, pb->length);
		
		return td;
	}
	
	/**
	*@brief �V�[�P���X�^�̃f�[�^�|�[�g���쐬����֐�
	* @param op �ڑ�����f�[�^�|�[�g
	* @param tdt �f�[�^�^
    * @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param leng �s�͈̔�
	* @param mstate ����ړ�����ꍇ��True
	* @return �f�[�^�|�[�g�I�u�W�F�N�g
	*/
	template <typename T, typename T2> ExcelPortBase* crPortSeq(OtherPort &op, std::string tdt, int c, std::string l, std::string sn, std::string leng, bool mstate)
   {
		string PortType = NVUtil::toString(op.pb->get_port_profile()->properties,"port.port_type");
		
	   string tname = op.buff[op.buff.size()-2];
		tname += op.buff[op.buff.size()-1];
	  
		if(PortType == "DataInPort")
		{
			T *m_out = new T();
			OutPort<T> *m_outOut = new OutPort<T>(tname.c_str(),*m_out);
			addOutPort(tname.c_str(), *m_outOut);
			
			ExcelPortBase *mip;
			
			mip= new ExcelOutPortSeq<T,T2>(m_out,m_outOut,tname,tdt,this);
			mip->mop = &op;
			
			mip->setParam(c,l,sn,leng,mstate);
			OutPorts.push_back(mip);
			
			portConnect(m_outOut->getPortRef(), op.pb);

			op.mpb = mip;

			return mip;
		
		}
		else if(PortType == "DataOutPort")
		{
			T *m_in = new T();
			InPort<T> *m_inIn = new InPort<T>(tname.c_str(),*m_in);

			addInPort(tname.c_str(), *m_inIn);

			ExcelPortBase *mip = new ExcelInPortSeq<T,T2>(m_in,m_inIn,tname,tdt,this);
			mip->mop = &op;
			

			mip->setParam(c,l,sn,leng,mstate);
			InPorts.push_back(mip);
			
			portConnect(m_inIn->getPortRef(), op.pb);

			op.mpb = mip;

			return mip;
		}
		return NULL;
	}
	
	/**
	*@brief �f�[�^�|�[�g���쐬����֐�
	* @param op �ڑ�����f�[�^�|�[�g
	* @param tdt �f�[�^�^
    * @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param leng �s�͈̔�
	* @param mstate ����ړ�����ꍇ��True
	* @return �f�[�^�|�[�g�I�u�W�F�N�g
	*/
   template <typename T, typename T2> ExcelPortBase* crPort(OtherPort &op, std::string tdt, int c, std::string l, std::string sn, std::string leng, bool mstate)
   {
	   string PortType = NVUtil::toString(op.pb->get_port_profile()->properties,"port.port_type");
		
	   string tname = op.buff[op.buff.size()-2];
		tname += op.buff[op.buff.size()-1];
	  
		if(PortType == "DataInPort")
		{
			T *m_out = new T();
			OutPort<T> *m_outOut = new OutPort<T>(tname.c_str(),*m_out);
			addOutPort(tname.c_str(), *m_outOut);
			
			ExcelPortBase *mip;
			
			mip= new ExcelOutPort<T,T2>(m_out,m_outOut,tname,tdt,this);
			mip->mop = &op;
			
			mip->setParam(c,l,sn,leng,mstate);
			OutPorts.push_back(mip);
			
			portConnect(m_outOut->getPortRef(), op.pb);

			op.mpb = mip;

			return mip;
		
		}
		else if(PortType == "DataOutPort")
		{
			T *m_in = new T();
			InPort<T> *m_inIn = new InPort<T>(tname.c_str(),*m_in);
			

			addInPort(tname.c_str(), *m_inIn);

			ExcelPortBase *mip = new ExcelInPort<T,T2>(m_in,m_inIn,tname,tdt,this);
			mip->mop = &op;
			

			mip->setParam(c,l,sn,leng,mstate);
			InPorts.push_back(mip);
			
			portConnect(m_inIn->getPortRef(), op.pb);

			op.mpb = mip;

			return mip;
		}
		return NULL;
   }
   
   /**
   *@brief �R���t�B�M�����[�V�����p�����[�^�ɂ��V�[�P���X�^�̃f�[�^�|�[�g���쐬����֐�
    * @param tname ����
	* @param PortType �f�[�^�|�[�g�̃^�C�v
	* @param tdt �f�[�^�^
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param leng �s�͈̔�
	* @param mstate ����ړ�����ꍇ��True
	* @return �f�[�^�|�[�g�I�u�W�F�N�g
   */
   template <typename T, typename T2> ExcelPortBase* confcrPortSeq(std::string tname, std::string PortType, std::string tdt, int c, std::string l, std::string sn, std::string leng, bool mstate)
   {
		
	  
		if(PortType == "DataOutPort")
		{
			T *m_out = new T();
			OutPort<T> *m_outOut = new OutPort<T>(tname.c_str(),*m_out);
			addOutPort(tname.c_str(), *m_outOut);
			
			ExcelPortBase *mip;
			
			mip= new ExcelOutPortSeq<T,T2>(m_out,m_outOut,tname,tdt,this);
			
			mip->setParam(c,l,sn,leng,mstate);
			ConfOutPorts.push_back(mip);
			

			

			return mip;
		
		}
		else if(PortType == "DataInPort")
		{
			T *m_in = new T();
			InPort<T> *m_inIn = new InPort<T>(tname.c_str(),*m_in);

			addInPort(tname.c_str(), *m_inIn);

			ExcelPortBase *mip = new ExcelInPortSeq<T,T2>(m_in,m_inIn,tname,tdt,this);
			
			

			mip->setParam(c,l,sn,leng,mstate);
			ConfInPorts.push_back(mip);
			

			

			return mip;
		}
		return NULL;
	}
	
   /**
   *@brief �R���t�B�M�����[�V�����p�����[�^�ɂ��f�[�^�|�[�g���쐬����֐�
    * @param tname ����
	* @param PortType �f�[�^�|�[�g�̃^�C�v
	* @param tdt �f�[�^�^
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param leng �s�͈̔�
	* @param mstate ����ړ�����ꍇ��True
	* @return �f�[�^�|�[�g�I�u�W�F�N�g
   */
   template <typename T, typename T2> ExcelPortBase* confcrPort(std::string tname, std::string PortType, std::string tdt, int c, std::string l, std::string sn, std::string leng, bool mstate)
   {
	  
	  
		if(PortType == "DataOutPort")
		{
			T *m_out = new T();
			OutPort<T> *m_outOut = new OutPort<T>(tname.c_str(),*m_out);
			addOutPort(tname.c_str(), *m_outOut);
			
			ExcelPortBase *mip;
			
			mip= new ExcelOutPort<T,T2>(m_out,m_outOut,tname,tdt,this);
			
			mip->setParam(c,l,sn,leng,mstate);
			ConfOutPorts.push_back(mip);
			

			

			return mip;
		
		}
		else if(PortType == "DataInPort")
		{
			T *m_in = new T();
			InPort<T> *m_inIn = new InPort<T>(tname.c_str(),*m_in);
			

			addInPort(tname.c_str(), *m_inIn);

			ExcelPortBase *mip = new ExcelInPort<T,T2>(m_in,m_inIn,tname,tdt,this);
			
			

			mip->setParam(c,l,sn,leng,mstate);
			ConfInPorts.push_back(mip);
			

			

			return mip;
		}
		return NULL;
   }


   

   
   
   
   /**
   *@brief �f�[�^�|�[�g�̍쐬�A�l�̐ݒ���s���֐�
    * @param pt �ڑ�����f�[�^�|�[�g�̃p�X
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param leng �s�͈̔�
	* @param mstate ����ړ�����ꍇ��True
	* @param msflag True�̏ꍇ�̓��b�Z�[�W�{�b�N�X�̕\���ƃZ���ɖ��O�̏������݂��s��
	* @return �f�[�^�|�[�g�I�u�W�F�N�g  
   */
   ExcelPortBase* setDPort(std::vector<std::string> pt, int c, std::string l, std::string sn, std::string leng, bool mstate, bool msflag);
   
   /**
   *@brief �f�[�^�|�[�g���폜����֐�
   * @param pt �폜����f�[�^�|�[�g�̃p�X
   */
   void delDPort(std::vector<std::string> pt);
   
   /**
   *@brief �f�[�^�|�[�g���擾����֐�
   * @param pt �擾����f�[�^�|�[�g�̃p�X
   * @return �f�[�^�|�[�g�I�u�W�F�N�g
   */
   ExcelPortBase* getDPort(std::vector<std::string> pt);
   
   
   /**
   *@brief �f�[�^�|�[�g���֘A�t����֐�
   * @param mpb �֘A�t����A�E�g�|�[�g
   * @param n �֘A�t����C���|�[�g�̖��O
   */
   void attachPort(ExcelPortBase *mpb, std::string n);
   
   /**
   *@brief �f�[�^�|�[�g�̊֘A�t������������֐�
   * @param mpb �֘A�t������������A�E�g�|�[�g
   * @param n �֘A�t������������C���|�[�g�̖��O
   */
   void detachPort(ExcelPortBase *mpb, std::string n);
   
   /**
   *@brief �C���|�[�g���擾����֐�
   * @param n �C���|�[�g�̖��O
   * @return �f�[�^�|�[�g�I�u�W�F�N�g
   */
   ExcelPortBase *getInPort(std::string n);
   
   /**
   *@brief �A�E�g�|�[�g���擾����֐�
   * @param n �A�E�g�|�[�g�̖��O
   * @return �f�[�^�|�[�g�I�u�W�F�N�g
   */
   ExcelPortBase *getOutPort(std::string n);
   
   /**
   *@brief �R���t�B�M�����[�V�����p�����[�^�Őݒ肵���A�E�g�|�[�g���擾����֐�
   * @param n �A�E�g�|�[�g�̖��O
   * @return �f�[�^�|�[�g�I�u�W�F�N�g
   */
   ExcelPortBase *getConfOutPort(std::string n);
   /**
   *@brief �R���t�B�M�����[�V�����p�����[�^�Őݒ肵���C���|�[�g���擾����֐�
   * @param n �C���|�[�g�̖��O
   * @return �f�[�^�|�[�g�I�u�W�F�N�g
   */
   ExcelPortBase *getConfInPort(std::string n);

   
   /**
   *@brief RTC�̃f�[�^�|�[�g�̃c���[���擾����֐�
   * @param IP_adress �l�[���T�[�o�̖��O
   * @return �c���[�I�u�W�F�N�g
   */
   TreeObject* getRTCTree(std::string IP_adress);

   /**
   *@brief �t�@�C�����̃R���t�B�M�����[�V�����p�����[�^�ύX�̊֐�
   * @param FP �t�@�C����
   */
   void setFilePath(std::string FP);

   std::vector<ExcelPortBase*> InPorts;	/**<�@@brief  */
   std::vector<ExcelPortBase*> OutPorts;	/**<�@@brief  */

   std::vector<ExcelPortBase*> ConfInPorts;	/**<�@@brief  */
   std::vector<ExcelPortBase*> ConfOutPorts;	/**<�@@brief  */

   RTC::Manager* m_manager;	/**<�@@brief  */

   std::vector<OtherPort> rtclist;	/**<�@@brief  */

   RTC::CorbaPort m_SpreadSheetPort;	/**<�@@brief  */
   mSpreadSheetSVC_impl m_spreadsheet;	/**<�@@brief  */


   
   std::string getFileName();

 protected:
	std::string file_path;	/**<�@@brief  */
	std::string conf_data_type;	/**<�@@brief  */
	std::string conf_port_type;	/**<�@@brief  */
	int conf_column;	/**<�@@brief  */
	std::string conf_start_row;	/**<�@@brief  */
	std::string conf_end_row;	/**<�@@brief  */
	std::string conf_sheetname;	/**<�@@brief  */
	int c_move;
	std::string attach_Port;

	
	

	int actionLock;	/**<�@@brief  */
	int red;	/**<�@@brief  */
	int green;	/**<�@@brief  */
	int blue;	/**<�@@brief  */

	coil::Mutex _mutex; /**<�@@brief  */

	ExcelTask *et;


 private:


};

/**
 * @class ExcelConfigUpdateParam
*@brief �R���t�B�M�����[�V�����p�����[�^���X�V���ꂽ�Ƃ��̃R�[���o�b�N
*/
class ExcelConfigUpdateParam
    : public RTC::ConfigurationSetListener
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param e_rtc ExcelRTC
	*/
    ExcelConfigUpdateParam(ExcelControl *e_rtc)
    {
		m_rtc = e_rtc;
    }
	/**
	*@brief 
	* @param config_set 
	*/
    void operator()(const coil::Properties& config_set)
	{
		
		m_rtc->configUpdate();
		
    }
	ExcelControl *m_rtc; /**<�@@brief  */

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


extern "C"
{
  DLL_EXPORT void ExcelControlInit(RTC::Manager* manager);
};

#endif