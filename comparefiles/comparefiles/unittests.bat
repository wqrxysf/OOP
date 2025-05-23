@echo off
setlocal enabledelayedexpansion

REM Создание тестовых файлов
echo Hello World > file1.txt
echo Hello World > file2.txt
echo Different Line > file3.txt
echo Hello World > file4.txt
echo Extra Line >> file4.txt

echo Running tests...

REM Тест 1: Одинаковые файлы
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe file1.txt file2.txt > output.txt
findstr "Files are equal" output.txt > nul
if %errorlevel% neq 0 (
    echo Test 1 failed!
) else (
    echo Test 1 passed!
)

REM Тест 2: Разные файлы (различие в строке)
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe file1.txt file3.txt > output.txt
findstr "Files are different" output.txt > nul
if %errorlevel% neq 0 (
    echo Test 2 failed!
) else (
    echo Test 2 passed!
)

REM Тест 3: Один файл длиннее другого
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe file1.txt file4.txt > output.txt
findstr "Files are different" output.txt > nul
if %errorlevel% neq 0 (
    echo Test 3 failed!
) else (
    echo Test 3 passed!
)

REM Тест 4: Несуществующий файл
C:\Users\wqrxysf\source\repos\comparefiles\comparefiles\ARM64\Debug\comparefiles.exe file1.txt nonexistent.txt > output.txt
findstr "Error opening" output.txt > nul
if %errorlevel% neq 0 (
    echo Test 4 failed!
) else (
    echo Test 4 passed!
)

REM Очистка временных файлов
del file1.txt file2.txt file3.txt file4.txt output.txt

echo All tests completed!
exit /b 0