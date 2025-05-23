@echo off
setlocal enabledelayedexpansion

REM �������� �������� ������
echo Hello World > file1.txt
echo Hello World > file2.txt
echo Different Line > file3.txt
echo Hello World > file4.txt
echo Extra Line >> file4.txt

echo Running tests...

REM ���� 1: ���������� �����
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe file1.txt file2.txt > output.txt
findstr "Files are equal" output.txt > nul
if %errorlevel% neq 0 (
    echo Test 1 failed!
) else (
    echo Test 1 passed!
)

REM ���� 2: ������ ����� (�������� � ������)
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe file1.txt file3.txt > output.txt
findstr "Files are different" output.txt > nul
if %errorlevel% neq 0 (
    echo Test 2 failed!
) else (
    echo Test 2 passed!
)

REM ���� 3: ���� ���� ������� �������
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe file1.txt file4.txt > output.txt
findstr "Files are different" output.txt > nul
if %errorlevel% neq 0 (
    echo Test 3 failed!
) else (
    echo Test 3 passed!
)

REM ���� 4: �������������� ����
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe file1.txt nonexistent.txt > output.txt
findstr "Error opening" output.txt > nul
if %errorlevel% neq 0 (
    echo Test 4 failed!
) else (
    echo Test 4 passed!
)

REM ������� ��������� ������
del file1.txt file2.txt file3.txt file4.txt output.txt

echo All tests completed!
exit /b 0