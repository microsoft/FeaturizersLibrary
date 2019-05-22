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

IF "%1"=="" (
    echo.
    echo This script bootstraps common library enlistment and setup.
    echo.
    echo     Usage:
    echo         %0 ^<common code dir^>
    echo.

    exit /B -1
)

if "%DEVELOPMENT_ENVIRONMENT_REPOSITORY_ACTIVATED_FLAG%" NEQ "" (
    echo.
    echo ERROR: Please run this from a standard ^(non-activated^) command prompt.
    echo.

    exit /B -1
)

REM Bootstrap enlistment and setup of Common_Environment, and then invoke
REM bootstrap_impl.py once python is available.

IF NOT EXIST "%1\Common\Environment" (
    git clone https://github.com/davidbrownell/Common_Environment_v3.git "%1\Common\Environment"
    if %ERRORLEVEL% NEQ 0 exit /B %ERRORLEVEL%
)

call "%1\Common\Environment\Setup.cmd"
if %ERRORLEVEL% NEQ 0 exit /B %ERRORLEVEL%

REM Write the environment activation and python execution statements to a temporary
REM file so this environment remains unactivated (by doing this, the current script
REM can be invoked multiple times from the same environment).
(
    echo @echo off
    echo call "%1\Common\Environment\Activate.cmd" python36
    echo python "%~dp0\bootstrap_impl.py" %*
) >bootstrap_tmp.cmd

cmd /C bootstrap_tmp.cmd
set _ERRORLEVEL=%ERRORLEVEL%
del bootstrap_tmp.cmd

if %_ERRORLEVEL% NEQ 0 exit /B %_ERRORLEVEL%
