#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import OpenRTM_aist
import RTC
 
encodedata_spec = ["implementation_id", "EncodeData",
                  "type_name",         "EncodeData",
                  "description",       "Encode inputData component",
                  "version",           "1.0",
                  "vendor",            "Miyamoto Nobuhiko",
                  "category",          "DataConversion",
                  "activity_type",     "DataFlowComponent",
                  "max_instance",      "10",
                  "language",          "Python",
                  "lang_type",         "script",
                  "conf.default.InputCode", "utf-8",
                  "conf.default.OutputCode", "utf-8",
                  "conf.__widget__.InputCode", "radio",
                  "conf.__widget__.OutputCode", "radio",
                  "conf.__constraints__.InputCode", "(utf-8,euc_jp,shift_jis)",
                  "conf.__constraints__.OutputCode", "(utf-8,euc_jp,shift_jis)",
                  ""]
 
class EncodeData(OpenRTM_aist.DataFlowComponentBase):
    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)
        self._StringIndata = RTC.TimedString(RTC.Time(0,0),"")
        self._StringInport = OpenRTM_aist.InPort("StringIn", self._StringIndata)

        self._StringOutdata = RTC.TimedString(RTC.Time(0,0),"")
        self._StringOutport = OpenRTM_aist.OutPort("StringOut", self._StringOutdata)

        self._WStringIndata = RTC.TimedWString(RTC.Time(0,0),u"")
        self._WStringInport = OpenRTM_aist.InPort("WStringIn", self._WStringIndata)

        self._WStringOutdata = RTC.TimedWString(RTC.Time(0,0),u"")
        self._WStringOutport = OpenRTM_aist.OutPort("WStringOut", self._WStringOutdata)

        self.InputCode = ["utf-8"]
        self.OutputCode = ["utf-8"]
 
    def onInitialize(self):
        
        self.registerInPort("_StringInport", self._StringInport)
        self.registerOutPort("_StringOutport", self._StringOutport)

        self.registerInPort("_WStringInport", self._WStringInport)
        self.registerOutPort("_WStringOutport", self._WStringOutport)

        self.bindParameter("InputCode", self.InputCode, "utf-8")
        self.bindParameter("OutputCode", self.OutputCode, "utf-8")

        
        
        return RTC.RTC_OK
 
    def onExecute(self, ec_id):
        if self._StringInport.isNew():
            data = self._StringInport.read()
            ans = data.data
            w_ans = data.data.decode(self.InputCode[0])
            if self.InputCode[0] != self.OutputCode[0]:
                ans = w_ans.encode(self.OutputCode[0])
                
            self._StringOutdata.data = ans
            OpenRTM_aist.setTimestamp(self._StringOutdata)
            self._StringOutport.write()

            self._WStringOutdata.data = w_ans
            OpenRTM_aist.setTimestamp(self._WStringOutdata)
            self._WStringOutport.write()

            

        if self._WStringInport.isNew():
            data = self._WStringInport.read()
            ans = data.data.encode(self.OutputCode[0])
            w_ans = data.data
            
                
            self._StringOutdata.data = ans
            OpenRTM_aist.setTimestamp(self._StringOutdata)
            self._StringOutport.write()

            self._WStringOutdata.data = w_ans
            OpenRTM_aist.setTimestamp(self._WStringOutdata)
            self._WStringOutport.write()
 
            
        return RTC.RTC_OK
 
def MyModuleInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=encodedata_spec)
    manager.registerFactory(profile,
                            EncodeData,
                            OpenRTM_aist.Delete)
    comp = manager.createComponent("EncodeData")
 
def main():
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()
 
if __name__ == "__main__":
    main()
