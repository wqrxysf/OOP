@echo off
setlocal enabledelayedexpansion

chcp 1251

echo Running tests...

rem тесты
call :run_test "Test 1" "stupid idiot" "This stupid idiot believes that the Sun rotates around the Earth" "This believes that the Sun rotates around the Earth"
call :run_test "Test 2" "" "Hello world How are you today" "Hello world How are you today"
call :run_test "Test 3" "hello world test" "hello world test program" "program"

echo All tests completed.
del expected.txt input.txt output.txt
exit /b 0

:run_test
    set "test_name=%~1"
    set "forbidden=%~2"
    set "input_text=%~3"
    set "expected_output=%~4"

    echo %forbidden% > input.txt
    echo %input_text% >> input.txt
    echo %expected_output% > expected.txt

    C:\Users\wqrxysf\source\repos\CensoreFilter\CensoreFilter\ARM64\Debug\CensoreFilter.exe < input.txt > output.txt

    rem сравнение
    rem type expected.txt
    findstr /R /C:"%expected_output%" output.txt > nul
    if %errorlevel% neq 0 (
        echo %test_name% failed
    ) else (
        echo %test_name% passed
    )

    exit /b
