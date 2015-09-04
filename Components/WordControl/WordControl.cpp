// -*- C++ -*-
/*!
 * @file  WordControl.cpp
 * @brief WordControlComponent
 * @date $Date$
 *
 * $Id$
 */

#include "WordControl.h"
#include "SubFunction.h"


// Module specification
// <rtc-template block="module_spec">
static const char* wordrtc_spec[] =
  {
    "implementation_id", "WordControl",
    "type_name",         "WordControl",
    "description",       "Word Control Component",
    "version",           "0.0.1",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Office",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	"conf.default.file_path", "NewFile",
	"conf.default.fontsize", "16",
	//"conf.default.fontname", "ＭＳ 明朝",
	"conf.default.char_Red", "0",
	"conf.default.char_Blue", "0",
	"conf.default.char_Green", "0",
	"conf.default.italic", "0",
	"conf.default.bold", "0",
	"conf.default.underline", "0",
    "conf.default.shadow", "0",
    "conf.default.strikeout", "0",
    "conf.default.contoured", "0",
    "conf.default.emphasis", "0",
    "conf.default.back_Red", "255",
    "conf.default.back_Blue", "255",
    "conf.default.back_Green", "255",
	"conf.default.code", "shift_jis",
	"conf.__widget__.file_path", "text",
	"conf.__widget__.fontsize", "spin",
	//"conf.__widget__.fontname", "radio",
	"conf.__widget__.char_Red", "spin",
	"conf.__widget__.char_Blue", "spin",
	"conf.__widget__.char_Green", "spin",
	"conf.__widget__.italic", "radio",
	"conf.__widget__.bold", "radio",
	"conf.__widget__.underline", "radio",
    "conf.__widget__.shadow", "radio",
    "conf.__widget__.strikeout", "radio",
    "conf.__widget__.contoured", "radio",
    "conf.__widget__.emphasis", "radio",
    "conf.__widget__.back_Red", "spin",
    "conf.__widget__.back_Blue", "spin",
    "conf.__widget__.back_Green", "spin",
	"conf.__widget__.code", "radio",
	"conf.__constraints__.fontsize", "1<=x<=72",
	//"conf.__constraints__.fontname", "(MS UI Gothic,MS ゴシック,MS Pゴシック,MS 明朝,MS P明朝,HG ゴシック E,HGP ゴシック E,HGS ゴシック E,HG ゴシック M,HGP ゴシック M,HGS ゴシック M,HG 正楷書体-PRO,HG 丸ゴシック M-PRO,HG 教科書体,HGP 教科書体,HGS 教科書体,HG 行書体,HGP 行書体,HGS 行書体,HG 創英プレゼンス EB,HGP 創英プレゼンス EB,HGS 創英プレゼンス EB,HG 創英角ゴシック UB,HGP 創英角ゴシック UB,HGS 創英角ゴシック UB,HG 創英角ポップ体,HGP 創英角ポップ体,HGS 創英角ポップ体,HG 明朝 B,HGP 明朝 B,HGS 明朝 B,HG 明朝 E,HGP 明朝 E,HGS 明朝 E,メイリオ)",
	"conf.__constraints__.char_Red", "0<=x<=255",
	"conf.__constraints__.char_Blue", "0<=x<=255",
	"conf.__constraints__.char_Green", "0<=x<=255",
	"conf.__constraints__.italic", "(0,1)",
	"conf.__constraints__.bold", "(0,1)",
	"conf.__constraints__.underline", "(0,1)",
    "conf.__constraints__.shadow", "(0,1)",
    "conf.__constraints__.strikeout", "(0,1)",
    "conf.__constraints__.contoured", "(0,1)",
    "conf.__constraints__.emphasis", "(0,1)",
    "conf.__constraints__.back_Red", "0<=x<=255",
    "conf.__constraints__.back_Blue", "0<=x<=255",
    "conf.__constraints__.back_Green", "0<=x<=255",
	"conf.__constraints__.code", "(utf-8, shift_jis)",
    ""
  };



// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
WordControl::WordControl(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_wordIn("word", m_word),
    m_fontSizeIn("fontSize", m_fontSize),
	m_fontNameIn("fontName", m_fontName),
	m_wsCharacterIn("wsCharacter", m_wsCharacter),
    m_wsWordIn("wsWord", m_wsWord),
    m_wsLineIn("wsLine", m_wsLine),
    m_wsParagraphIn("wsParagraph", m_wsParagraph),
    m_wsWindowIn("wsWindow", m_wsWindow),
    m_wsScreenIn("wsScreen", m_wsScreen),
    m_Char_colorIn("Char_color", m_Char_color),
	m_MovementTypeIn("movementType", m_MovementType),
	m_ItalicIn("italic", m_Italic),
	m_BoldIn("bold", m_Bold),
	m_UnderlineIn("underline", m_Underline),
	m_ShadowIn("shadow", m_Shadow),
	m_StrikeoutIn("strikeout", m_Strikeout),
	m_ContouredIn("contoured", m_Contoured),
	m_EmphasisIn("emphasis", m_Emphasis),
	m_Back_colorIn("Back_color", m_Back_color),
    m_selWordOut("selWord", m_selWord),
    m_copyWordOut("copyWord", m_copyWord),
	m_WriterPort("Writer")

    // </rtc-template>
{
	
}

/*!
 * @brief destructor
 */
WordControl::~WordControl()
{
}


std::string WordControl::getFileName()
{

	return file_path;
}


RTC::ReturnCode_t WordControl::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("word", m_wordIn);
  addInPort("fontSize", m_fontSizeIn);
  addInPort("fontName", m_fontNameIn);
  addInPort("wsCharacter", m_wsCharacterIn);
  addInPort("wsWord", m_wsWordIn);
  addInPort("wsLine", m_wsLineIn);
  addInPort("wsParagraph", m_wsParagraphIn);
  addInPort("wsWindow", m_wsWindowIn);
  addInPort("wsScreen", m_wsScreenIn);
  addInPort("Char_color", m_Char_colorIn);
  addInPort("movementType", m_MovementTypeIn);
  addInPort("italic", m_ItalicIn);
  addInPort("bold", m_BoldIn);
  addInPort("underline", m_UnderlineIn);
  addInPort("shadow", m_ShadowIn);
  addInPort("strikeout", m_StrikeoutIn);
  addInPort("contoured", m_ContouredIn);
  addInPort("emphasis", m_EmphasisIn);
  addInPort("bold", m_BoldIn);
  addInPort("Back_color", m_Back_colorIn);

  
  // Set OutPort buffer
  addOutPort("selWord", m_selWordOut);
  addOutPort("copyWord", m_copyWordOut);

  // Set service provider to Ports
  m_WriterPort.registerProvider("writer", "Writer::mWriter", m_writer);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_WriterPort);


  
  

  

  
  bindParameter("file_path", file_path, "NewFile");
  
  bindParameter("fontsize", fontsize, "16");
  //bindParameter("fontname", fontname, "ＭＳ 明朝");
  bindParameter("char_Red", char_Red, "0");
  bindParameter("char_Green", char_Green, "0");
  bindParameter("char_Blue", char_Blue, "0");
  bindParameter("italic", italic, "0");
  bindParameter("bold", bold, "0");
  bindParameter("code", code, "shift_jis");

  bindParameter("underline", underline, "0");
  bindParameter("shadow", shadow, "0");
  bindParameter("strikeout", strikeout, "0");
  bindParameter("contoured", contoured, "0");
  bindParameter("emphasis", emphasis, "0");
  bindParameter("back_Red", back_Red, "255");
  bindParameter("back_Green", back_Green, "255");
  bindParameter("back_Blue", back_Blue, "255");


  this->m_configsets.update("default", "file_path");
  wt = new WordTask(this);
  wt->activate();

  /*std::string filePath = "";
  coil::Properties& prop(::RTC::Manager::instance().getConfig());
  getProperty(prop, "excel.filename", filePath);
  SetFilePath(filePath);*/


  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new WordConfigUpdateParam(this));
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>


  
  return RTC::RTC_OK;
}



void WordControl::SetFilePath(std::string FP)
{

	coil::Properties file_confSet("default");
	file_confSet.setProperty("file_path", FP.c_str());
	this->m_configsets.setConfigurationSetValues(file_confSet);
	this->m_configsets.activateConfigurationSet("default");
	


	this->m_configsets.update("default", "file_path");
	
}


void WordControl::ConfigUpdate()
{
	this->m_configsets.update("default","file_path");
	std::string sfn = file_path;
	coil::replaceString(sfn, "/", "\\");
	//std::cout << sfn << std::endl;
	System::String ^tfn = gcnew System::String(sfn.c_str());
	//System::Console::WriteLine(tfn);
	
	if(sfn ==  "NewFile")
	{
		WordObject::Obj->Open("");
	}
	else if(WordObject::Obj->filename != tfn)
	{
		
		WordObject::Obj->Open(tfn);
		 
		
	}
	
}


RTC::ReturnCode_t WordControl::onFinalize()
{
  WordObject::Obj->Close();
  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t WordControl::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WordControl::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t WordControl::onActivated(RTC::UniqueId ec_id)
{
	WordObject::Obj->setFontSize(fontsize);
	WordObject::Obj->setFontName(fontname);
	WordObject::Obj->setFontColor(char_Red, char_Green, char_Blue);
	if(italic == 0)
		WordObject::Obj->italic = false;
	else
		WordObject::Obj->italic = true;
	if(bold == 0)
		WordObject::Obj->bold = false;
	else
		WordObject::Obj->bold = true;

	if(underline == 0)
		WordObject::Obj->underline = false;
	else
		WordObject::Obj->underline = true;

	if(shadow == 0)
		WordObject::Obj->shadow = false;
	else
		WordObject::Obj->shadow = true;

	if(strikeout == 0)
		WordObject::Obj->strikeout = false;
	else
		WordObject::Obj->strikeout = true;

	if(contoured == 0)
		WordObject::Obj->contoured = false;
	else
		WordObject::Obj->contoured = true;

	if(emphasis == 0)
		WordObject::Obj->emphasis = false;
	else
		WordObject::Obj->emphasis = true;

	WordObject::Obj->setBackColor(back_Red, back_Green, back_Blue);

	

	WordObject::Obj->movementType = false;

	//ofs.open("test.txt");

  return RTC::RTC_OK;
}


RTC::ReturnCode_t WordControl::onDeactivated(RTC::UniqueId ec_id)
{
	//ofs.close();
  return RTC::RTC_OK;
}



RTC::ReturnCode_t WordControl::onExecute(RTC::UniqueId ec_id)
{
	

	if(m_fontSizeIn.isNew())
	{
		m_fontSizeIn.read();
		WordObject::Obj->setFontSize(m_fontSize.data);
	}

	if(m_MovementTypeIn.isNew())
	{
		m_MovementTypeIn.read();
		WordObject::Obj->movementType = m_MovementType.data;
	}


	if(m_fontNameIn.isNew())
	{
		m_fontNameIn.read();
		WordObject::Obj->setFontName((const char*)m_fontName.data);
	}
	if(m_wsCharacterIn.isNew())
	{
		m_wsCharacterIn.read();
		WordObject::Obj->moveSelection(Word::WdUnits::wdCharacter, m_wsCharacter.data);
	}
	if(m_wsWordIn.isNew())
	{
		m_wsWordIn.read();
		WordObject::Obj->moveSelection(Word::WdUnits::wdWord, m_wsWord.data);
	}
	if(m_wsLineIn.isNew())
	{
		m_wsLineIn.read();
		WordObject::Obj->moveSelection(Word::WdUnits::wdLine, m_wsLine.data);
	}
	if(m_wsParagraphIn.isNew())
	{
		m_wsParagraphIn.read();
		WordObject::Obj->moveSelection(Word::WdUnits::wdParagraph, m_wsParagraph.data);
	}
	if(m_wsWindowIn.isNew())
	{
		m_wsWindowIn.read();
		WordObject::Obj->moveSelection(Word::WdUnits::wdWindow, m_wsWindow.data);
	}
	if(m_wsScreenIn.isNew())
	{
		m_wsScreenIn.read();
		WordObject::Obj->moveSelection(Word::WdUnits::wdScreen, m_wsScreen.data);
	}
	if(m_Char_colorIn.isNew())
	{
		m_Char_colorIn.read();
		WordObject::Obj->setFontColor(m_Char_color.data.r*255,m_Char_color.data.g*255,m_Char_color.data.b*255);
	}

	if(m_ItalicIn.isNew())
	{
		m_ItalicIn.read();
		WordObject::Obj->italic = m_Italic.data;
	}
	if(m_BoldIn.isNew())
	{
		m_BoldIn.read();
		WordObject::Obj->bold = m_Bold.data;
	}

	if(m_UnderlineIn.isNew())
	{
		m_UnderlineIn.read();
		WordObject::Obj->underline = m_Underline.data;
	}

	if(m_ShadowIn.isNew())
	{
		m_ShadowIn.read();
		WordObject::Obj->shadow = m_Shadow.data;
	}

	if(m_StrikeoutIn.isNew())
	{
		m_StrikeoutIn.read();
		WordObject::Obj->strikeout = m_Strikeout.data;
	}

	if(m_ContouredIn.isNew())
	{
		m_ContouredIn.read();
		WordObject::Obj->contoured = m_Contoured.data;
	}

	if(m_EmphasisIn.isNew())
	{
		m_EmphasisIn.read();
		WordObject::Obj->emphasis = m_Emphasis.data;
	}

	if(m_Back_colorIn.isNew())
	{
		m_Back_colorIn.read();
		WordObject::Obj->setBackColor(m_Back_color.data.r*255,m_Back_color.data.g*255,m_Back_color.data.b*255);
	}

	
	

	if(m_wordIn.isNew())
	{
		m_wordIn.read();
		const char *tmp = m_word.data;
		//coil::TimeValue t1(coil::gettimeofday());
		WordObject::Obj->setWord(tmp, code);
		//coil::TimeValue t2(coil::gettimeofday());
		//ofs << t2 - t1 << std::endl;
	}

	m_selWord.data = MarshalString(WordObject::Obj->getSelWord()).c_str();
	m_selWordOut.write();

	

	


  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t WordControl::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WordControl::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WordControl::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WordControl::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t WordControl::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void WordControlInit(RTC::Manager* manager)
  {
    coil::Properties profile(wordrtc_spec);
    manager->registerFactory(profile,
                             RTC::Create<WordControl>,
                             RTC::Delete<WordControl>);
  }
  
};


