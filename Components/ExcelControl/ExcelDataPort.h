// -*-C++-*-
/*!
 * @file  ExcelDataPort.h
 * @brief ExcelDataPort
 */
#ifndef EXCELDATAPORT_H
#define EXCELDATAPORT_H


#include "ExcelControl.h"

class ExcelPortBase;
class ExcelControl;


/**
 * @class DataListener
*@brief �C���|�[�g���f�[�^���󂯂����̃R�[���o�b�N
*/
template <class T, class T2>
class DataListener
  : public ConnectorDataListenerT<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param mp �f�[�^�|�[�g�I�u�W�F�N�g
	* @param sv �f�[�^�i�[�p�R���e�i
	* @param mrtc ExcelRTC
	*/
	DataListener(ExcelPortBase *mp, std::vector<std::vector<T2>> &sv, ExcelControl *mrtc){
		m_port = mp;
		m_data = &sv;
		m_rtc = mrtc;
	}
	/**
	*@brief �f�X�g���N�^
	*/
  virtual ~DataListener()
  {
  
  }

  /**
	*@brief
	* @param info �R�l�N�^�̏��
	* @param data �f�[�^
	*/
  virtual void operator()(const ConnectorInfo& info,
                          const T& data)
  {

	 

	  std::vector<T2> tmp;
	
	  
	  tmp.push_back(data.data);
	
	  m_port->_mutex.lock();
	  m_data->push_back(tmp);
	  m_port->_mutex.unlock();

	  m_rtc->updateAPort(m_port);
       
  };
  ExcelPortBase *m_port;	/**<�@@brief  */
  std::vector<std::vector<T2>> *m_data; /**<�@@brief  */
  ExcelControl *m_rtc; /**<�@@brief  */
  
};


/**
 * @class SeqDataListener
*@brief �V�[�P���X�^�̃C���|�[�g���f�[�^���󂯎�����Ƃ��̃R�[���o�b�N
*/
template <class T, class T2>
class SeqDataListener
  : public ConnectorDataListenerT<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param mp �f�[�^�|�[�g�I�u�W�F�N�g
	* @param sv �f�[�^�i�[�p�R���e�i
	* @param mrtc ExcelRTC
	*/
	SeqDataListener(ExcelPortBase *mp, std::vector<std::vector<T2>> &sv, ExcelControl *mrtc){
		m_port = mp;
		m_data = &sv;
		m_rtc = mrtc;
	}
	/**
	*@brief �f�X�g���N�^
	*/
  virtual ~SeqDataListener()
  {
  
  }

  /**
	*@brief
	* @param info �R�l�N�^�̏��
	* @param data �f�[�^
	*/
  virtual void operator()(const ConnectorInfo& info,
                          const T& data)
  {
	std::vector<T2> tmp;
	
	for(int i=0;i < data.data.length();i++)
	{
		tmp.push_back(data.data[i]);
	}
	
	m_port->_mutex.lock();
	m_data->push_back(tmp);
	m_port->_mutex.unlock();

	m_rtc->updateAPort(m_port);
  };
  ExcelPortBase *m_port; /**<�@@brief  */
  std::vector<std::vector<T2>> *m_data; /**<�@@brief  */
  ExcelControl *m_rtc; /**<�@@brief  */
  
};



/**
 * @class OtherPort
*@brief ����RTC�̃f�[�^�|�[�g�̃N���X
*/
class OtherPort
{
	public:
		/**
		*@brief �R���X�g���N�^
		* @param p �f�[�^�|�[�g�I�u�W�F�N�g
		* @param s �p�X
		*/
		OtherPort(PortService_var p, std::vector<std::string> s)
		{
			pb = p;
			buff = s;
			mpb = NULL;
		};
		PortService_var pb; /**<�@@brief  */
		std::vector<std::string> buff; /**<�@@brief  */
		ExcelPortBase *mpb; /**<�@@brief  */
};



/**
 * @class ExcelPortBase
*@brief ExcelRTC�̃f�[�^�|�[�g�̃N���X
*/
class ExcelPortBase
{
public:
	/**
	*@brief �f�X�g���N�^
	*/
	virtual ~ExcelPortBase()
	{
		delete pb;
	}

	
	/**
	*@brief GUI�œ��͂����l��ݒ肷��֐�
	* @param c ��ԍ�
	* @param l �s�ԍ�
	* @param sn �V�[�g��
	* @param leng �s�͈̔�
	* @param mstate ����ړ�����ꍇ��True
	*/
	virtual void setParam(int c, std::string l, std::string sn, std::string leng, bool mstate)
	{
		col = c;
		low = l;
		sheetName = sn;
		length = leng;
		num = 0;
		state = mstate;
		//update_cellName();
	}

	/**
	*@brief �f�[�^���擾�������𔻒肷��֐�
	*/
	virtual bool isNew()
	{
		return false;
	}
	/**
	*@brief �󂯂��f�[�^���Z���ɏ������ފ֐�
	* @param moption True�̏ꍇ�̓o�b�t�@�̃f�[�^���܂Ƃ߂ď�������BFalse�̏ꍇ��1�񂾂��f�[�^��ǂݍ��ށB
	*/
	virtual void putData(bool moption)
	{

	}
	/**
	*@brief �f�[�^�|�[�g�Ɗ֘A�t�������Z���ɖ��O�����
	*/
	virtual void update_cellName()
	{
		
		ExcelObject::Obj->setCellStringSingle(col, low, sheetName, name);
	}


	std::string name; /**<�@@brief  */
	
	int col; /**<�@@brief  */
	std::string low; /**<�@@brief  */
	std::string length; /**<�@@brief  */
	int sheetnum; /**<�@@brief  */
	
	std::string sheetName; /**<�@@brief  */
	int num; /**<�@@brief  */
	OtherPort *mop; /**<�@@brief  */
	PortBase *pb; /**<�@@brief  */
	std::string data_type; /**<�@@brief  */
	std::vector<std::string> attachPort;  /**<�@@brief  */

	bool state; /**<�@@brief  */
	ExcelControl *mexc; /**<�@@brief  */
	coil::Mutex _mutex; /**<�@@brief  */

	
	

	/*template <typename T>T GetOutPort()
	{
		return static_cast<ExcelOutPort<T>*>this;
	}

	template <typename T>T GetInPort()
	{
		return static_cast<ExcelInPort<T>*>this;
	}*/
};


/**
 * @class ExcelInPort
*@brief �C���|�[�g�̃N���X
*/
template <class T, class T2>
class ExcelInPort : public ExcelPortBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param id �f�[�^�I�u�W�F�N�g
	* @param ip �f�[�^�|�[�g�I�u�W�F�N�g
	* @param n ����
	* @param dt �f�[�^�^
	* @param m_mexc ExcelRTC
	*/
	ExcelInPort(T *id, RTC::InPort<T> *ip, std::string n, std::string dt, ExcelControl *m_mexc){
		In = id;
		inIn = ip;
		name = n;
		data_type = dt;
		
		col = 1;
		low = 1;
		sheetnum = 1;
		

		
		pb = ip;

		
		mexc = m_mexc;

		
		inIn->addConnectorDataListener(ON_BUFFER_WRITE, new DataListener<T,T2>(this, buff, mexc));
		
	}
	/**
	*@brief �f�X�g���N�^
	*/
	~ExcelInPort()
	{
		//delete inIn;
		//delete In;
	}
	
	/**
	*@brief �f�[�^���擾�������𔻒肷��֐�
	*/
	virtual bool isNew()
	{
		return inIn->isNew();
	}

	
	
	/**
	*@brief �󂯂��f�[�^���Z���ɏ������ފ֐�
	* @param moption True�̏ꍇ�̓o�b�t�@�̃f�[�^���܂Ƃ߂ď�������BFalse�̏ꍇ��1�񂾂��f�[�^��ǂݍ��ށB
	*/
	virtual void putData(bool moption)
	{
		
		
		std::vector<std::vector<T2>> v;
		if(!moption)
		{
			
			if(inIn->isNew())
			{
				inIn->read();
				//std::cout << ip->In->data << std::endl;
				
				
				std::vector<T2> v2;
				v2.push_back(In->data);
				v.push_back(v2);

				
			}
		}
		else
		{

			_mutex.lock();
			v = buff;
			buff.clear();
			_mutex.unlock();
		}
		
		

		mexc->setCellData<T2>(v, this);

		if(state)
			num += v.size();
		

		

		
	}

	T *In; /**<�@@brief  */
	RTC::InPort<T> *inIn; /**<�@@brief  */
	std::vector<std::vector<T2>> buff; /**<�@@brief  */
	
};


/**
 * @class ExcelInPortSeq
*@brief �V�[�P���X�^�̃C���|�[�g�̃N���X
*/
template <class T, class T2>
class ExcelInPortSeq : public ExcelPortBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param id �f�[�^�I�u�W�F�N�g
	* @param ip �f�[�^�|�[�g�I�u�W�F�N�g
	* @param n ����
	* @param dt �f�[�^�^
	* @param m_mexc ExcelRTC
	*/
	ExcelInPortSeq(T *id, RTC::InPort<T> *ip, std::string n, std::string dt, ExcelControl *m_mexc){
		In = id;
		inIn = ip;
		name = n;
		data_type = dt;
		
		col = 1;
		low = 1;
		sheetnum = 1;
		

		
		pb = ip;

		
		mexc = m_mexc;

		
		inIn->addConnectorDataListener(ON_BUFFER_WRITE, new SeqDataListener<T,T2>(this, buff, mexc));


	}
	/**
	*@brief �f�X�g���N�^
	*/
	~ExcelInPortSeq()
	{
		//delete inIn;
		//delete In;
	}
	
	/**
	*@brief �f�[�^���擾�������𔻒肷��֐�
	*/
	virtual bool isNew()
	{
		return inIn->isNew();
	}

	
		

		
		
	
	/**
	*@brief �󂯂��f�[�^���Z���ɏ������ފ֐�
	* @param moption True�̏ꍇ�̓o�b�t�@�̃f�[�^���܂Ƃ߂ď�������BFalse�̏ꍇ��1�񂾂��f�[�^��ǂݍ��ށB
	*/
	virtual void putData(bool moption)
	{
		std::vector<std::vector<T2>> v;
		if(!moption)
		{
			
			if(inIn->isNew())
			{
				inIn->read();
				
				std::vector<T2> v2;
				

				for(int i=0;i < In->data.length();i++)
				{
					v2.push_back(In->data[i]);
					
				}
				v.push_back(v2);

			}
		}
		else
		{

			_mutex.lock();
			v = buff;
			buff.clear();
			_mutex.unlock();
		}

		mexc->setCellData<T2>(v, this);

		if(state)
			num += v.size();

		
				
				

			
		
	}

	T *In; /**<�@@brief  */
	RTC::InPort<T> *inIn; /**<�@@brief  */
	std::vector<std::vector<T2>> buff; /**<�@@brief  */
	
};



/**
 * @class ExcelOutPort
*@brief �A�E�g�|�[�g�̃N���X
*/
template <class T, class T2>
class ExcelOutPort : public ExcelPortBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param id �f�[�^�I�u�W�F�N�g
	* @param ip �f�[�^�|�[�g�I�u�W�F�N�g
	* @param n ����
	* @param dt �f�[�^�^
	* @param m_mexc ExcelRTC
	*/
	ExcelOutPort(T *od, RTC::OutPort<T> *op, std::string n, std::string dt, ExcelControl *m_mexc){
		Out = od;
		outOut = op;
		name = n;
		data_type = dt;

		col = 1;
		low = 1;
		sheetnum = 1;
		

		
		pb = op;

		mexc = m_mexc;

		

		
	}
	/**
	*@brief �f�X�g���N�^
	*/
	~ExcelOutPort()
	{
		//delete outOut;
		//delete Out;
	}
	
	/**
	*@brief �Z���̒l���f�[�^�|�[�g����o�͂���֐�
	* @param moption True�̏ꍇ�̓o�b�t�@�̃f�[�^���܂Ƃ߂ď�������BFalse�̏ꍇ��1�񂾂��f�[�^��ǂݍ��ށB
	*/
	virtual void putData(bool moption)
	{
				
		std::vector<T2> v = mexc->getCellData<T2>(this);
		
		Out->data = v[0];
		if(state)
			num += 1;
		
		
		outOut->write();
	}
	T *Out; /**<�@@brief  */
	RTC::OutPort<T> *outOut; /**<�@@brief  */
};


/**
 * @class ExcelOutPortSeq
*@brief �V�[�P���X�^�̃A�E�g�|�[�g�̃N���X
*/
template <class T, class T2>
class ExcelOutPortSeq : public ExcelPortBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param id �f�[�^�I�u�W�F�N�g
	* @param ip �f�[�^�|�[�g�I�u�W�F�N�g
	* @param n ����
	* @param dt �f�[�^�^
	* @param m_mexc ExcelRTC
	*/
	ExcelOutPortSeq(T *od, RTC::OutPort<T> *op, std::string n, std::string dt, ExcelControl *m_mexc){
		Out = od;
		outOut = op;
		name = n;
		data_type = dt;

		col = 1;
		low = 1;
		sheetnum = 1;
		

		
		pb = op;

		mexc = m_mexc;

		

		
	}
	/**
	*@brief �f�X�g���N�^
	*/
	~ExcelOutPortSeq()
	{
		//delete outOut;
		//delete Out;
	}


	
	/**
	*@brief �Z���̒l���f�[�^�|�[�g����o�͂���֐�
	* @param moption True�̏ꍇ�̓o�b�t�@�̃f�[�^���܂Ƃ߂ď�������BFalse�̏ꍇ��1�񂾂��f�[�^��ǂݍ��ށB
	*/
	virtual void putData(bool moption)
	{
		int t_l = convertStrToVal(low);
		int t_leng = convertStrToVal(length);

		int leng = t_leng-t_l+1;

		Out->data.length(leng);
		std::vector<T2> v = mexc->getCellData<T2>(this);
		if(leng != v.size())return;
		for(int i=0;i < leng;i++)
		{
			Out->data[i] = v[i];
		}
		if(state)
			num += 1;
		
		
		outOut->write();
	}
	T *Out; /**<�@@brief  */
	RTC::OutPort<T> *outOut; /**<�@@brief  */
};


#endif