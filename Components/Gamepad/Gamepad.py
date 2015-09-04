#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file Gamepad.py
 @brief Gamepad
 @date $Date$


 LGPL

"""
import sys
import time
sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist

import pygame
from pygame.locals import *


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
gamepad_spec = ["implementation_id", "Gamepad", 
		 "type_name",         "Gamepad", 
		 "description",       "Gamepad", 
		 "version",           "1.0.0", 
		 "vendor",            "Miyamoto Nobuhiko", 
		 "category",          "Game", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 "conf.default.id", "0",
		 "conf.__widget__.id", "spin",
		 "conf.__constraints__.id", "0<=x<=100",
		 ""]
# </rtc-template>


class Joystick:

    accuracy = 4
    def __init__(self, mode=0):
        self.joystick = pygame.joystick
        self.joystick.init()
        self._mode = mode
    def initialize(self, id=0):
        
        if not self.joystick.get_init():
            return False
            self.sticknum = 0
        else:
            self.sticknum = self.joystick.get_count()
            if self.sticknum == 0:
                        return False
            #self._setup(id)
            return self.ChangeStick(id)
            
        
    def close(self):
        self.joystick.quit()

    def ChangeStick(self, id):
        if id < self.sticknum:
            return self._setup(id)
        elif 0 < self.sticknum:
            return self._setup(0)
        else:
            return False

    def _setup(self, id):
        try:
            self.stick = pygame.joystick.Joystick(id)
        except pygame.error, message:
            print "Joystick ID Error: %d"%id
            raise SystemExit, message
        self.stick.init()
        return self.stick.get_init()



    def get_button(self):
        inputs = []
        if self.stick.get_numbuttons() > 0:
            for i in range(self.stick.get_numbuttons()):
                inputs.append(self.stick.get_button(i))
            return inputs
        else:
            return []

    def get_ball(self):
        inputs = []
        if self.stick.get_numballs() > 0:
            for i in range(self.stick.get_numballs):
                inputs.append(self.stick.get_ball(i))
            return inputs
        else:
            return []

    def get_axis(self):
        inputs = []
        if not self._mode == 0:
            for i in range(self.stick.get_numaxes()):
                axis = round(self.stick.get_axis(i), self.accuracy)
                #axis = self.stick.get_axis(i)
                inputs.append(axis)
            return inputs
        else:
            hat = []
            for i in range(self.stick.get_numaxes()):
                if i < 2:
                    axis = round(self.stick.get_axis(i), self.accuracy)
                    if i == 1:
                        hat.append(-axis)
                    else:
                        hat.append(axis)
            inputs = self._get_arrow(hat)
            return inputs

    def get_hat(self):

        if self.stick.get_numhats() > 0:
            inputs = self._get_arrow(self.stick.get_hat(0))
            return inputs
        else:
            return []

    def _get_arrow(self, inputpos):

        inputs = []
        for h in inputpos:
            if h < 0:
                inputs.append(1)
                inputs.append(0)
            elif h > 0:
                inputs.append(0)
                inputs.append(1)
            else:
                inputs.append(0)
                inputs.append(0)
        return inputs
    
##
# @class Gamepad
# @brief Gamepad
# 
# ゲームのコントローラーへの入力をDataOutPortから出力するRTCです。
# 
# 
class Gamepad(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		self._d_ball = RTC.TimedFloat(RTC.Time(0,0),0)
		"""
		トラックボールの相対位置
		 - Type: RTC::TimedFloat
		"""
		self._ballOut = OpenRTM_aist.OutPort("ball", self._d_ball)
		self._d_button = RTC.TimedBooleanSeq(RTC.Time(0,0),[])
		"""
		ボタンの入力
		左、上、下、右、L1、R1、L2、R2、？、？、セレクト、スタートの順
		 - Type: RTC::TimedBooleanSeq
		"""
		self._buttonOut = OpenRTM_aist.OutPort("button", self._d_button)
		self._d_hat = RTC.TimedBooleanSeq(RTC.Time(0,0),[])
		"""
		十字キーの押している方向
		右、左、下、上の順序
		 - Type: RTC::TimedBooleanSeq
		"""
		self._hatOut = OpenRTM_aist.OutPort("hat", self._d_hat)
		self._d_axis0 = RTC.TimedFloatSeq(RTC.Time(0,0),[])
		"""
		アナログスティックの方向
		アナログスティックが2つの場合は、右側のアナログスティックの入力値を取得
		 - Type: RTC::TimedFloatSeq
		"""
		self._axis0Out = OpenRTM_aist.OutPort("axis0", self._d_axis0)
		self._d_axis1 = RTC.TimedFloatSeq(RTC.Time(0,0),[])
		"""
		アナログスティックの方向
		アナログスティックが2つの場合は、左側のアナログスティックの入力値を取得
		 - Type: RTC::TimedFloatSeq
		"""
		self._axis1Out = OpenRTM_aist.OutPort("axis1", self._d_axis1)


		


		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		"""
		ゲームパッドのID
		 - Name: id id
		 - DefaultValue: 0
		 - Constraint: 0<=x<=100
		"""
		self._id = [0]
		
		# </rtc-template>


		 
	##
	#
	# The initialize action (on CREATED->ALIVE transition)
	# formaer rtc_init_entry() 
	# 
	# @return RTC::ReturnCode_t
	# 
	#
	def onInitialize(self):
		# Bind variables and configuration variable
		self.bindParameter("id", self._id, "0")
		
		# Set InPort buffers
		
		# Set OutPort buffers
		self.addOutPort("ball",self._ballOut)
		self.addOutPort("button",self._buttonOut)
		self.addOutPort("hat",self._hatOut)
		self.addOutPort("axis0",self._axis0Out)
		self.addOutPort("axis1",self._axis1Out)

		self.joy = Joystick(1)
		pygame.init()
		# Set service provider to Ports
		
		# Set service consumers to Ports
		
		# Set CORBA Service Ports
		
		return RTC.RTC_OK
	
		##
		# 
		# The finalize action (on ALIVE->END transition)
		# formaer rtc_exiting_entry()
		# 
		# @return RTC::ReturnCode_t
	
		# 
	def onFinalize(self):
		self.joy.close()
		pygame.quit()
		return RTC.RTC_OK
	
		##
		#
		# The startup action when ExecutionContext startup
		# former rtc_starting_entry()
		# 
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onStartup(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The shutdown action when ExecutionContext stop
		# former rtc_stopping_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onShutdown(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The activated action (Active state entry action)
		# former rtc_active_entry()
		#
		# @param ec_id target ExecutionContext Id
		# 
		# @return RTC::ReturnCode_t
		#
		#
	def onActivated(self, ec_id):
		if self.joy.initialize(self._id[0]) == False:
			return RTC.RTC_ERROR
		return RTC.RTC_OK
	
		##
		#
		# The deactivated action (Active state exit action)
		# former rtc_active_exit()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onDeactivated(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The execution action that is invoked periodically
		# former rtc_active_do()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onExecute(self, ec_id):
		for event in pygame.event.get():
			pass
		self._d_ball.data = self.joy.get_ball()
		self._ballOut.write()
		self._d_button.data = self.joy.get_button()
		self._buttonOut.write()
		self._d_hat.data = self.joy.get_hat()
		self._hatOut.write()
		axis_data = self.joy.get_axis()
		if len(axis_data) >= 2:
			self._d_axis0.data = [axis_data[0],axis_data[1]]
			self._axis0Out.write()
		if len(axis_data) >= 4:
			self._d_axis1.data = [axis_data[2],axis_data[3]]
			self._axis1Out.write()

		
		return RTC.RTC_OK
	
		##
		#
		# The aborting action when main logic error occurred.
		# former rtc_aborting_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onAborting(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The error action in ERROR state
		# former rtc_error_do()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onError(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The reset action that is invoked resetting
		# This is same but different the former rtc_init_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onReset(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The state update action that is invoked after onExecute() action
		# no corresponding operation exists in OpenRTm-aist-0.2.0
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#

		#
	def onStateUpdate(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The action that is invoked when execution context's rate is changed
		# no corresponding operation exists in OpenRTm-aist-0.2.0
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onRateChanged(self, ec_id):
	
		return RTC.RTC_OK
	



def GamepadInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=gamepad_spec)
    manager.registerFactory(profile,
                            Gamepad,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    GamepadInit(manager)

    # Create a component
    comp = manager.createComponent("Gamepad")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

