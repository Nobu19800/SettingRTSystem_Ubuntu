cd /d %~dp0
cmake ./ -G "Visual Studio 9 2008 Win64" -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ./
copy .\RTC.xml RTC.xml
