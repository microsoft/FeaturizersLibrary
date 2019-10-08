@REM ----------------------------------------------------------------------
@REM |
@REM |  bootstrap.cmd
@REM |
@REM |  David Brownell <db@DavidBrownell.com>
@REM |      2019-05-21 08:07:40
@REM |
@REM ----------------------------------------------------------------------
@REM |
@REM |  Copyright David Brownell 2019
@REM |  Distributed under the Boost Software License, Version 1.0. See
@REM |  accompanying file LICENSE_1_0.txt or copy at
@REM |  http://www.boost.org/LICENSE_1_0.txt.
@REM |
@REM ----------------------------------------------------------------------
@echo off

IF "%~1"=="" (
    echo.
    echo This script bootstraps common library enlistment and setup.
    echo.
    echo     Usage:
    echo         %0 ^<common code dir^> ["/name=<custom environment name>"]
    echo.

    exit /B -1
)

set _COMMON_CODE_DIR=%~1
shift /1

if "%DEVELOPMENT_ENVIRONMENT_REPOSITORY_ACTIVATED_FLAG%" NEQ "" (
    echo.
    echo ERROR: Please run this from a standard ^(non-activated^) command prompt.
    echo.

    exit /B -1
)

REM Bootstrap enlistment and setup of Common_Environment, and then invoke
REM enlistment and setup once python is available.

IF NOT EXIST "%_COMMON_CODE_DIR%\Common\Environment" (
    git clone https://github.com/davidbrownell/Common_Environment_v3.git "%_COMMON_CODE_DIR%\Common\Environment.tmp"
    if %ERRORLEVEL% NEQ 0 exit /B %ERRORLEVEL%

    move "%_COMMON_CODE_DIR%\Common\Environment.tmp" "%_COMMON_CODE_DIR%\Common\Environment"
    if %ERRORLEVEL% NEQ 0 exit /B %ERRORLEVEL%
)

REM Note that the following loop has been crafted to work around batch's crazy
REM expansion rules. Modify at your own risk!
set _BOOTSTRAP_NAME=
set _BOOTSTRAP_CLA=

:GetRemainingArgs_Begin

if "%~1"=="" goto :GetRemainingArgs_End

set _ARG=%~1

if "%_ARG:~,6%"=="/name=" goto :GetRemainingArgs_Name1
if "%_ARG:~,6%"=="-name=" goto :GetRemainingArgs_Name1

if "%_ARG:~,9%"=="/name_EQ_" goto :GetRemainingArgs_Name2
if "%_ARG:~,9%"=="-name_EQ_" goto :GetRemainingArgs_Name2

REM If here, we are looking at an arg that should be passed to the script
set _BOOTSTRAP_CLA=%_BOOTSTRAP_CLA% "%_ARG%"
goto :GetRemainingArgs_Continue

:GetRemainingArgs_Name1
REM If here, we are looking at a name argument
set _BOOTSTRAP_NAME=%_ARG:~6%
goto :GetRemainingArgs_Continue

:GetRemainingArgs_Name2
REM If here, we are looking at a name argument
set _BOOTSTRAP_NAME=%_ARG:~9%
goto :GetRemainingArgs_Continue

:GetRemainingArgs_Continue
shift /1
goto :GetRemainingArgs_Begin

:GetRemainingArgs_End

set _BOOTSTRAP_NAME_ARG=
if "%_BOOTSTRAP_NAME%" NEQ "" (
    set _BOOTSTRAP_NAME_ARG="/name=%_BOOTSTRAP_NAME%"
)

REM This works around a strange problem when attempting to invoke a command file using
REM a relative path.
pushd "%_COMMON_CODE_DIR%"
set _COMMON_CODE_ABSOLUTE_DIR=%CD%
popd

call "%_COMMON_CODE_ABSOLUTE_DIR%\Common\Environment\Setup.cmd" %_BOOTSTRAP_NAME_ARG%
if %ERRORLEVEL% NEQ 0 exit /B %ERRORLEVEL%

REM Write the environment activation and python execution statements to a temporary
REM file so this environment remains unactivated (by doing this, the current script
REM can be invoked multiple times from the same environment).
set _ACTIVATE_CMD=Activate.cmd

if "%_BOOTSTRAP_NAME%" NEQ "" (
    set _ACTIVATE_CMD=Activate.%_BOOTSTRAP_NAME%.cmd
)

(
    echo @echo off
    echo.
    echo call "%_COMMON_CODE_DIR%\Common\Environment\%_ACTIVATE_CMD%" python36
    echo if %%ERRORLEVEL%% NEQ 0 exit /B %%ERRORLEVEL%%
    echo.
    echo call %~dp0Setup.cmd Enlist "%_COMMON_CODE_DIR%" /recurse %_BOOTSTRAP_CLA%
    echo if %%ERRORLEVEL%% NEQ 0 exit /B %%ERRORLEVEL%%
    echo.
    echo call %~dp0Setup.cmd /recurse %_BOOTSTRAP_CLA%
    echo if %%ERRORLEVEL%% NEQ 0 exit /B %%ERRORLEVEL%%
) >bootstrap_tmp.cmd

cmd /C bootstrap_tmp.cmd
set _ERRORLEVEL=%ERRORLEVEL%
del bootstrap_tmp.cmd

set _ACTIVATE_CMD=
set _ARG=
set _BOOTSTRAP_CLA=
set _BOOTSTRAP_NAME=
set _BOOTSTRAP_NAME_ARG=
set _COMMON_CODE_DIR=
set _COMMON_CODE_ABSOLUTE_DIR=

if %_ERRORLEVEL% NEQ 0 exit /B %_ERRORLEVEL%
