// -*-C++-*-
/*!
 * @file  WordObject.h
 * @brief Wordの操作
 */
#ifndef WordObject_H
#define WordObject_H

//using namespace Microsoft::Office::Interop::Word;
#define Word   Microsoft::Office::Interop::Word

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "SubFunction.h"


/**
 * @class WordObject
*@brief Wordを操作するクラス
*/
ref class WordObject
{
public:
	/**
	*@brief コンストラクタ
	*/
	WordObject();

	static WordObject^ Obj; /**<　@brief  */

	
	/**
	*@brief Wordファイルを開く関数
	* @param fn ファイルパス
	*/
	void Open(System::String^ fn);
	
	/**
	*@brief COMオブジェクトを解放する関数
	*/
	void Close();

	
	/**
	*@brief 文字列を書き込む関数
	* @param st 書き込む文字列
	* @param m_code 文字コード
	*/
	void setWord(std::string st, std::string m_code);
	
	/**
	*@brief フォントのサイズを変更する関数
	* @param fs フォントサイズ
	*/
	void setFontSize(float fs);
	
	/**
	*@brief フォントの種類を変更する関数
	* @param fn フォントの種類
	*/
	void setFontName(std::string fn);

	
	/**
	*@brief 選択位置を変更する関数
	* @param m_type 移動のタイプ
	* @param leng 移動量
	*/
	void moveSelection(Word::WdUnits m_type, int leng);

	
	/**
	*@brief 選択位置の文字列を取得する関数
	* @return 取得した文字列
	*/
	System::String^ getSelWord();

	
	/**
	*@brief 文字の色を変更する関数
	* @param r 文字の色(R)
	* @param g 文字の色(G)
	* @param b 文字の色(B)
	*/
	void setFontColor(int r, int g, int b);

	
	/**
	*@brief 背景色を変更する関数
	* @param r 文字の色(R)
	* @param g 文字の色(G)
	* @param b 文字の色(B)
	*/
	void setBackColor(int r, int g, int b);

	/**
	*@brief カーソル位置のX座標取得(単位はmm)
	* @return カーソル位置のX座標
	*/
	float oCurrentCursorPositionX();
	/**
	*@brief カーソル位置のY座標取得(単位はmm)
	* @return カーソル位置のX座標
	*/
	float oCurrentCursorPositionY();
	/**
	*@brief カーソルをドキュメント先頭へ移動
	*/
	void gotoStart();
	/**
	*@brief カーソルをドキュメント最後尾へ移動
	*/
	void gotoEnd();
	/**
	*@brief カーソルを行先頭へ移動
	*/
	void gotoStartOfLine();
	/**
	*@brief カーソルを行最後尾へ移動
	*/
	void gotoEndOfLine();


	System::String^ filename; /**<　@brief  */
	Word::Application^ dcApplication; /**<　@brief  */
	Word::Documents^ dcDocuments; /**<　@brief  */
	Word::Document^ dcDocument; /**<　@brief  */

	System::String^ fontName; /**<　@brief  */
	float fontSize; /**<　@brief  */

	int char_Red, char_Green, char_Blue; /**<　@brief  */

	bool movementType; /**<　@brief  */
	bool italic; /**<　@brief  */
	bool bold; /**<　@brief  */

	bool underline; /**<　@brief  */
	bool shadow; /**<　@brief  */
	bool strikeout; /**<　@brief  */
	bool contoured; /**<　@brief  */
	bool emphasis; /**<　@brief  */

	int back_Red, back_Green, back_Blue; /**<　@brief  */

	/**
	*@brief
	* @param pUtf8Str
	* @param nBytesOut
	* @return 
	*/
	static char* utf8_to_sjis(const char *pUtf8Str, int *nBytesOut);
	
	/**
	*@brief
	* @param pUcsStr
	* @param nBytesOut
	* @return 
	*/
	static char* utf16be_to_sjis(const wchar_t *pUcsStr, int *nBytesOut);

	/**
	*@brief
	* @param pUcs2
	* @param pUtf8
	* @param nUtf8Num
	* @param bCountOnly
	* @param bBigEndian
	* @return 
	*/
	static int utf8_to_utf16be_sub( wchar_t *pUcs2, const char *pUtf8, int nUtf8Num, BOOL bCountOnly, BOOL bBigEndian);

	/**
	*@brief
	* @param pUtf8Str
	* @param nNumOut
	* @param bBigEndian
	* @return 
	*/
	static wchar_t* utf8_to_utf16be(const char *pUtf8Str, int *nNumOut, BOOL bBigEndian);
	
};



#endif