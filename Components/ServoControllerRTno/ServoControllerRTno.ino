
#include <ctype.h>
#include <string.h>
#include <Wire.h>
#include <Servo.h>
#include <UART.h>
#include <RTno.h>

#define servoNum 12


void rtcconf(config_str& conf, exec_cxt_str& exec_cxt) {
  conf._default.connection_type = ConnectionTypeSerial1;
  conf._default.baudrate = 57600;
  exec_cxt.periodic.type = ProxySynchronousExecutionContext;
  
 }



TimedDoubleSeq in;
InPort<TimedDoubleSeq> inIn("in", in);

int pin[servoNum] = {2,3,4,5,6,7,8,9,10,11,12,13};
Servo servoList[servoNum];


int RTno::onInitialize() {

  addInPort(inIn);
  
  for(int i=0;i < servoNum;i++)
  {
       servoList[i].attach(pin[i]);
  }
  

  return RTC_OK; 
}


int RTno::onActivated() {
 
  return RTC_OK; 
}


int RTno::onDeactivated()
{


  return RTC_OK;
}


 


 


int RTno::onExecute() {


  
  
  if(inIn.isNew()) {
    inIn.read();
    for(int i = 0;i < in.data.length();i++) {
      if(i < servoNum)
      {
      servoList[i].write(in.data[i]*180/3.141592);
      }
    }
  }
 
  


    
  return RTC_OK; 
}



int RTno::onError()
{
  return RTC_OK;
}


int RTno::onReset()
{
  return RTC_OK;
}

