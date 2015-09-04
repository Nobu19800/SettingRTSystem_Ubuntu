# -*- coding: utf-8 -*-


##
#   @file BlockBall.py
#   @brief Calcで作成したブロックボールのゲーム

import optparse
import sys,os,platform
import re


from os.path import expanduser
sv = sys.version_info


if os.name == 'posix':
    home = expanduser("~")
    sys.path += [home+'/OOoRTC', '/usr/lib/python2.' + str(sv[1]) + '/dist-packages']
elif os.name == 'nt':
    sys.path += ['.\\OOoRTC', 'C:\\Python2' + str(sv[1]) + '\\lib\\site-packages', 'C:\\Python2' + str(sv[1]) + '\\Lib\\site-packages\\OpenRTM_aist\\RTM_IDL']
    
    
    
    



import time
import random
import commands
import threading

import OpenRTM_aist


import uno
import unohelper
from com.sun.star.awt import XActionListener

from com.sun.star.script.provider import XScriptContext

from com.sun.star.view import XSelectionChangeListener

from com.sun.star.awt import XTextListener


import OOoRTC


m_gamethread = None


##
# @class GameObject
# @brief ゲームの画面に描画するオブジェクト
class GameObject:
    ##
    # @brief コンストラクタ
    # @param self
    # @param m_thread ゲームの更新スレッド
    # @param c1 行番号
    # @param r1 列番号
    # @param c2 行番号
    # @param r2 列番号
    # @param sn シート名
    def __init__(self, m_thread, c1, r1, c2, r2, sn):
        self.m_thread = m_thread
        m_c1 = str(self.m_thread.convertValToStr(c1))
        m_c2 = str(self.m_thread.convertValToStr(c2))
        m_r1 = str(r1)
        m_r2 = str(r2)
        self.cell, sheet = self.m_thread.GetCellRange(m_c1, m_r1, m_c2, m_r2, sn)
        self.c1 = 0
        self.r1 = 0
        self.c2 = 0
        self.r2 = 0
        self.sn = ""
        self.vx = 0
        self.vy = 0
        self.va = 0
        self.cell2 = None

    ##
    # @brief 描画を消す
    # @param self 
    def delete(self):
        
        self.cell2.CellBackColor = OOoRTC.RGB(0, 0, 0)

        
                
    ##
    # @brief 位置を再設定
    # @param self
    # @param c1 行番号
    # @param r1 列番号
    # @param c2 行番号
    # @param r2 列番号
    # @param sn シート名
    def movePosition(self, c1, r1, c2, r2, sn):
        if self.c1 == c1 and self.r1 == r1 and self.c2 == c2 and self.r2 == r2 and self.sn == sn:
            return
        self.delete()
        self.setPosition(c1, r1, c2, r2, sn)
        

    ##
    # @brief 図形を動かす
    # @param self
    # @param vx 速度(X軸方向)
    # @param vy 速度(Y軸方向)
    def move(self, vx, vy):
        self.delete()
        self.vx = vx
        self.vy = vy
        self.setPosition(self.c1+vx, self.r1+vy, self.c2+vx, self.r2+vy, self.sn)

    ##
    # @brief 位置の再設定
    # @param self
    # @param c1 行番号
    # @param r1 列番号
    # @param c2 行番号
    # @param r2 列番号
    # @param sn シート名
    def setPosition(self, c1, r1, c2, r2, sn):
        if self.c1 == c1 and self.r1 == r1 and self.c2 == c2 and self.r2 == r2 and self.sn == sn:
            return
        
        self.c1 = c1
        self.r1 = r1
        self.c2 = c2
        self.r2 = r2
        self.sn = sn
        
        e_c1 = str(self.m_thread.convertValToStr(c1))
        e_c2 = str(self.m_thread.convertValToStr(c2))
        e_r1 = str(r1)
        e_r2 = str(r2)
        self.cell2, sheet = self.m_thread.GetCellRange(e_c1, e_r1, e_c2, e_r2, sn)
        self.m_thread.copyColor(self.cell2, self.cell)

        

##
# @class GameThread
# @brief ゲームの画面の更新を行うスレッド
#
class GameThread (OpenRTM_aist.Task):


    ##
    # @brief コンストラクタ
    # @param self 
    #
    def __init__(self):

        OpenRTM_aist.Task.__init__(self)
        try:
          self.calc = OOoCalc()
        except NotOOoCalcException:
          return

        
        
        

        self._period = 0.01
        
        guard = None
        if OOoRTC.calc_comp:
            guard = OpenRTM_aist.ScopedLock(OOoRTC.calc_comp._mutex)
            
        self.calc.document.addActionLock()
        self.blocks = self.CreateBlocks()

        self.ball = GameObject(self, 1, 1, 8, 8, "Sheet3")
        bx = 3
        by = 8
        self.ball.setPosition(bx*24+1+8, by*8+1, bx*24+8+8, by*8+8, "Sheet2")
        self.ball.move(-2, -2)

        self.bar = GameObject(self, 9, 9, 32, 16, "Sheet3")
        bx = 3
        by = 9
        
        barpos = int(float(self.get_string("A", "1", "Sheet2"))/360.*4.*24. + 4.*24.)
        self.bar.setPosition(barpos+1, by*8+1, barpos+12, by*8+5, "Sheet2")
        
        
        
        

        self.calc.document.removeActionLock()

        if guard:
            del guard
        
        time.sleep(0.1)
        self.exec_flag = True

        
    ##
    # @brief ボールとバーもしくはブロックとの接触判定
    # @param self 
    # @param ball ボール
    # @param block バー、もしくはブロック
    #
    def contact(self, ball, block):
        ballx1 = ball.c1 + ball.vx
        ballx2 = ball.c2 + ball.vx
        bally1 = ball.r1 + ball.vy
        bally2 = ball.r2 + ball.vy

        blockx1 = block.c1 + block.vx
        blockx2 = block.c2 + block.vx
        blocky1 = block.r1 + block.vy
        blocky2 = block.r2 + block.vy

        
        

        xf = 0
        xflag = False
        
        if ballx1 < blockx1 and ballx2 > blockx1:
            xf = -2
            xflag = True
            
        if ballx1 < blockx2 and ballx2 > blockx2:
            xf = 2
            xflag = True
            
        if ballx1 > blockx1 and ballx2 < blockx2:
            xf = 0
            xflag = True
            
        if ballx1 < blockx1 and ballx2 > blockx2:
            xf = 0
            xflag = True
            
        yf = 0
        yflag = False
        if bally1 < blocky1 and bally2 > blocky1:
            yf = -2
            yflag = True
            
            
        if bally1 < blocky2 and bally2 > blocky2:
            yf = 2
            yflag = True
            
                
        if bally1 > blocky1 and bally2 < blocky2:
            yf = 0
            yflag = True
            
                
        if bally1 < blocky1 and bally2 > blocky2:
            yf = 0
            yflag = True
            
        if xflag and yflag:
            """if yf > 0:
                ball.vx += int(ball.va)
                ball.va -= ball.vx*0.5
            if yf < 0:
                ball.vx -= int(ball.va)
                ball.va += ball.vx*0.5
            if xf < 0:
                ball.vy += int(ball.va)
                ball.va -= ball.vy*0.5
            if xf > 0:
                ball.vy -= int(ball.va)
                ball.va += ball.vy*0.5"""

            
            
            if xf < 0 and ball.vx > 0:
                ball.vx = -ball.vx
            elif xf > 0 and ball.vx < 0:
                ball.vx = -ball.vx
            
            if yf < 0 and ball.vy > 0:
                ball.vy = -ball.vy
            elif yf > 0 and ball.vy < 0:
                ball.vy = -ball.vy
                
            
            return True
        return False
        
    ##
    # @brief スレッド実行関数
    # @param self 
    def svc(self):
        while self.exec_flag:
            t0_ = OpenRTM_aist.Time()
            guard = None
            if OOoRTC.calc_comp:
                guard = OpenRTM_aist.ScopedLock(OOoRTC.calc_comp._mutex)
            
            self.calc.document.addActionLock()
            


            barpos = int(float(self.get_string("A", "1", "Sheet2"))/360.*4.*24. + 4.*24.)
            self.bar.movePosition(barpos+1, self.bar.r1, barpos+12, self.bar.r2, self.bar.sn)
            self.contact(self.ball, self.bar)
            
            for b in self.blocks:
                if self.contact(self.ball, b):
                    b.delete()
                    time.sleep(0.1)
                    self.blocks.remove(b)
                    time.sleep(0.1)
                    
                    
            if self.ball.c1 + self.ball.vx < 0:
                self.ball.vx = -self.ball.vx
                self.ball.vy += int(self.ball.va)
                self.ball.va -= self.ball.vy*0.2
            if self.ball.c2 + self.ball.vx > 9*24:
                self.ball.vx = -self.ball.vx
                self.ball.vy -= int(self.ball.va)
                self.ball.va += self.ball.vy*0.2
            if self.ball.r1 + self.ball.vy < 0:
                self.ball.vy = -self.ball.vy
                self.ball.vx -= int(self.ball.va)
                self.ball.va += self.ball.vx*0.2
            if self.ball.r2 + self.ball.vy > 10*8:
                self.ball.vy = -self.ball.vy
                self.ball.vx += int(self.ball.va)
                self.ball.va -= self.ball.vx*0.2
                
            
            self.ball.move(self.ball.vx, self.ball.vy)
            
            self.calc.document.removeActionLock()
            if guard:
                del guard
            
            t1_ = OpenRTM_aist.Time()
            slptm_ = self._period - (t1_ - t0_).getTime().toDouble()
            if slptm_ > 0:
                time.sleep(slptm_)

        
        return 0
    ##
    # @brief ブロックを作成
    # @param self 
    #
    def CreateBlocks(self):
        self.data = GameObject(self, 1, 9, 8, 16, "Sheet3")
        vr = self.getValueRange(self.data.cell)
        blocks = []
        for i in range(0, len(vr)):
            for j in range(0, len(vr[i])):
                if vr[i][j] == 1:
                    time.sleep(0.1)
                    obj = GameObject(self, 9, 1, 32, 8, "Sheet3")
                    obj.setPosition(24*i+1, 8*j+1, 24*i+24, 8*j+8, "Sheet2")
                    blocks.append(obj)
        return blocks

    ##
    # @brief 範囲でセルの値を取得
    # @param self 
    # @param cell1 セル
    #
    def getValueRange(self, cell):
        m_data = []
        m_col = cell.getRangeAddress().EndColumn - cell.getRangeAddress().StartColumn + 1
        m_row = cell.getRangeAddress().EndRow - cell.getRangeAddress().StartRow + 1

        for i in range(0, m_col):
            e_d = []
            for j in range(0, m_row):
                e_d.append(int(cell.getCellByPosition(i, j).Value))
            m_data.append(e_d)
            
        return m_data
                

    ##
    # @brief セルの色をコピー
    # @param self 
    # @param cell1 コピー先のセル
    # @param cell2 コピー元のセル
    #
    def copyColor(self, cell1, cell2):
        m_col = cell1.getRangeAddress().EndColumn - cell1.getRangeAddress().StartColumn + 1
        m_row = cell1.getRangeAddress().EndRow - cell1.getRangeAddress().StartRow + 1

        for i in range(0, m_col):
            for j in range(0, m_row):
                if str(cell1.getCellByPosition(i, j).CellBackColor) != str(cell2.getCellByPosition(i, j).CellBackColor):
                    cell1.getCellByPosition(i, j).CellBackColor = str(cell2.getCellByPosition(i, j).CellBackColor)

    ##
    # @brief シート番号(アルファベット)を数値に変換
    # @param self 
    # @param m_val 変換前のシート番号
    #
    def convertStrToVal(self, m_str):
        if len(m_str) > 0:
            m_c = ord(m_str[0]) - 64
            if len(m_str) == 1:
                return int(m_c)
            else:
                if ord(m_str[1]) < 91 and ord(m_str[1]) > 64:
                    m_c2  = ord(m_str[1]) - 64
                    return int(m_c2) + int(m_c)*26
                else:
                    return int(m_c)

    ##
    # @brief 数値をシート番号(アルファベット)に変換
    # @param self 
    # @param m_val 変換前の数値
    #
    def convertValToStr(self, m_val):
        if m_val < 27:
            return chr(m_val+64)
        else:
            return chr((m_val-1)/26+64) + chr((m_val-1)%26+64+1)

        

    ##
    # @brief セルオブジェクト、シートオブジェクトの取得
    # @param self 
    # @param l 行番号
    # @param c 列番号
    # @param l2 行番号
    # @param c2 列番号
    # @param sn シート名
    # @return セルオブジェクト、シートオブジェクト
    #

    def GetCellRange(self, l, c, l2, c2, sn):
        if self.calc.sheets.hasByName(sn):
            sheet = self.calc.sheets.getByName(sn)
            CN = l+c+':'+l2+c2
            try:
                cell = sheet.getCellRangeByName(CN)
                return cell, sheet
            except:
                pass
        else:
            return None


    ##
    # @brief セルオブジェクト、シートオブジェクトの取得
    # @param self 
    # @param l 行番号
    # @param c 列番号
    # @param sn シート名
    # @return セルオブジェクト、シートオブジェクト
    #

    def GetCell(self, l, c, sn):
        if self.calc.sheets.hasByName(sn):
            sheet = self.calc.sheets.getByName(sn)
            CN = l+c
            try:
                cell = sheet.getCellRangeByName(CN)
                return cell, sheet
            except:
                pass
        else:
            return None



    ##
    # @brief セルの文字列を取得
    # @param self 
    # @param l 行番号
    # @param c 列番号
    # @param sn シート名
    # @return セルの文字列
    #
    def get_string(self, l, c, sn):
        cell, sheet = self.GetCell(l,c,sn)
        if cell:
                return str(cell.String)

        return "error"
        
        

    ##
    # @brief セルの値を設定
    # @param self 
    # @param l 行番号
    # @param c 列番号
    # @param sn シート名
    # @param v 設定する値
    ##
    def set_value(self, l, c, sn, v):
        cell, sheet = self.GetCell(l,c,sn)
        if cell:
            cell.Value = v
            return
        
        

    
    ##
    # @brief セルの文字列を設定
    # @param self 
    # @param l 行番号
    # @param c 列番号
    # @param sn シート名
    # @param v 設定する文字列
    #
    def set_string(self, l, c, sn, v):
        cell, sheet = self.GetCell(l,c,sn)
        if cell:
            cell.String = v
            return
            
        
        
##
# @brief メッセージボックス表示の関数
# @param title ウインドウのタイトル
# @param message 表示する文章
# http://d.hatena.ne.jp/kakurasan/20100408/p1のソースコード(GPLv2)の一部
#

def MyMsgBox(title, message):
    try:
        m_bridge = Bridge()
    except:
        return
    m_bridge.run_infodialog(title, message)



##
# @brief OpenOfficeを操作するためのクラス
# http://d.hatena.ne.jp/kakurasan/20100408/p1のソースコード(GPLv2)の一部
#

class Bridge(object):
  def __init__(self):
    self._desktop = XSCRIPTCONTEXT.getDesktop()
    self._document = XSCRIPTCONTEXT.getDocument()
    self._frame = self._desktop.CurrentFrame
    self._window = self._frame.ContainerWindow
    self._toolkit = self._window.Toolkit
  def run_infodialog(self, title='', message=''):
    try:
        msgbox = self._toolkit.createMessageBox(self._window,uno.createUnoStruct('com.sun.star.awt.Rectangle'),'infobox',1,title,message)
        msgbox.execute()
        msgbox.dispose()
    except:
        msgbox = self._toolkit.createMessageBox(self._window,'infobox',1,title,message)
        msgbox.execute()
        msgbox.dispose()



##
# @brief OpenOffice Calcを操作するためのクラス
# @class OOoCalc
# http://d.hatena.ne.jp/kakurasan/20100408/p1のソースコード(GPLv2)の一部
#

class OOoCalc(Bridge):
  def __init__(self):
    Bridge.__init__(self)
    if not self._document.supportsService('com.sun.star.sheet.SpreadsheetDocument'):
      self.run_errordialog(title='エラー', message='このマクロはOpenOffice.org Calcの中で実行してください')
      raise NotOOoCalcException()
    self.__current_controller = self._document.CurrentController
    self.__sheets = self._document.Sheets
  def get_active_sheet(self):
    return self.__current_controller.ActiveSheet
  def set_active_sheet(self, value):
    self.__current_controller.ActiveSheet = value
  active_sheet = property(get_active_sheet, set_active_sheet)
  @property
  def sheets(self): return self.__sheets
  @property
  def document(self): return self._document





            
        
##
# @brief ゲーム開始
#         
def StartGame():
    global m_gamethread
    if m_gamethread == None:
        m_gamethread = GameThread()
        m_gamethread.activate()
        

##
# @brief ゲーム終了
#
def StopGame():
    global m_gamethread
    if m_gamethread != None:
        m_gamethread.exec_flag = False
        #m_gamethread.wait()
        #m_gamethread.close()
        m_gamethread = None


g_exportedScripts = (StartGame, StopGame)
