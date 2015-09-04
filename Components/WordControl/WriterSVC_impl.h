// -*-C++-*-
/*!
 * @file  WriterSVC_impl.h
 * @brief Service implementation header of Writer.idl
 *
 */

#include "WriterSkel.h"

#ifndef WRITERSVC_IMPL_H
#define WRITERSVC_IMPL_H
 
/*!
 * @class mWriterSVC_impl
 * Example class implementing IDL interface Writer::mWriter
 */
class mWriterSVC_impl
 : public virtual POA_Writer::mWriter,
   public virtual PortableServer::RefCountServantBase
{
 private:
   

 public:
  /*!
   * @brief standard constructor
   */
   mWriterSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~mWriterSVC_impl();

   // attributes and operations
   /**
   *@brief 現在のカーソル位置X座標取得(単位はmm)
   * @return カーソル位置X座標
   */
   
   CORBA::Float oCurrentCursorPositionX();
   /**
   *@brief 現在のカーソル位置Y座標取得(単位はmm)
   * @return カーソル位置Y座標
   */
   CORBA::Float oCurrentCursorPositionY();
   /**
   *@brief カーソルをドキュメント先頭に移動
   *@param sel Trueなら移動範囲を選択
   */
   void gotoStart(CORBA::Boolean sel);
   /**
   *@brief カーソルをドキュメント最後尾に移動
   *@param sel Trueなら移動範囲を選択
   */
   
   void gotoEnd(CORBA::Boolean sel);
   /**
   *@brief カーソルを行先頭に移動
   *@param sel Trueなら移動範囲を選択
   */
   void gotoStartOfLine(CORBA::Boolean sel);
   /**
   *@brief カーソルを行最後尾に移動
   *@param sel Trueなら移動範囲を選択
   */
   void gotoEndOfLine(CORBA::Boolean sel);
   

};



#endif // WRITERSVC_IMPL_H


