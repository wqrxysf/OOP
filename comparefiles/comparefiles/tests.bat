rem SET ProgramPath="%~1"
rem echo ProgramPath

rem %ProgramPath% t1_file1.txt t1_file2.txt || goto err
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe t1_file1.txt t1_file2.txt
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe t2_file1.txt t2_file2.txt
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe t3_file1.txt t3_file2.txt
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe t4_file1.txt t4_file2.txt
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe arg1 arg2 arg3
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe arg1 arg2

rem fc t1_file1.txt t1_file2.txt || goto err
REM sucess exit
exit /B 0
REM errors
:err
echo Test failed
exit /B 1

rem error levels
rem ифы вайлы можно тут юзать
rem перенаправоять ввод и вывод через > и <