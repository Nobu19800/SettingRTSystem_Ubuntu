// -*-C++-*-
/*!
 * @file  SpreadSheetSVC_impl.h
 * @brief Service implementation header of SpreadSheet.idl
 *
 */

#include "SpreadSheetSkel.h"

#ifndef SPREADSHEETSVC_IMPL_H
#define SPREADSHEETSVC_IMPL_H
 
/*!
 * @class mSpreadSheetSVC_impl
 */
class mSpreadSheetSVC_impl
 : public virtual POA_SpreadSheet::mSpreadSheet,
   public virtual PortableServer::RefCountServantBase
{
 private:
   

 public:
  /*!
   * @brief standard constructor
   */
   mSpreadSheetSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~mSpreadSheetSVC_impl();

   // attributes and operations
   /**
   *@brief �Z���̕�������擾
   * @param l �s�ԍ�
   * @param c ��ԍ�
   * @param sn �V�[�g��
   * @return �Z���̕�����
   */
   char* get_string(const char* l, const char* c, const char* sn);
   /**
   *@brief �Z���̒l��ݒ�
   * @param l �s�ԍ�
   * @param c ��ԍ�
   * @param sn �V�[�g��
   * @param v �ݒ肷��l
   */
   void set_value(const char* l, const char* c, const char* sn, CORBA::Float v);
   /**
   *@brief ������
   */
   StringList* get_string_range(const char* l1, const char* c1, const char* l2, const char* c2, const char* sn);
   /**
   *@brief ������
   */
   void set_value_range(const char* l, const char* c, const char* sn, const FloatList v);
   /**
   *@brief �Z���̕������ݒ�
   * @param l �s�ԍ�
   * @param c ��ԍ�
   * @param sn �V�[�g��
   * @param v �ݒ肷�镶����
   */
   void set_string(const char* l, const char* c, const char* sn, const char* v);
   /**
   *@brief ������
   */
   void set_string_range(const char* l, const char* c, const char* sn, const StringList v);
   

};



#endif // SPREADSHEETSVC_IMPL_H


