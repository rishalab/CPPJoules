@echo off
curl -L0 https://github.com/Shiva9361/CPP_Joules/releases/download/v1.0/CPP_Joules_windows.tar.gz --output "%~dp0CPP_Joules_windows.tar.gz"
cd "%~dp0"
tar -xvzf "%~dp0CPP_Joules_windows.tar.gz"
del "%~dp0CPP_Joules_windows.tar.gz"
cd "%~dp0cppJoules"
xcopy /h "%~dp0cppJoules\libCPP_Joules.dll" "%windir%\system32\"
xcopy /h "%~dp0cppJoules\EnergyLib64.dll" "%windir%\system32\"
pause
