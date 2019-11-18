@REM ----------------------------------------------------------------------
@REM Copyright (c) Microsoft Corporation. All rights reserved.
@REM Licensed under the MIT License
@REM ----------------------------------------------------------------------
@echo off

@REM ----------------------------------------------------------------------
@REM |
@REM |  Run as:
@REM |     Setup.cmd [/debug] [/verbose] [/configuration_EQ_<config_name>]*
@REM |
@REM ----------------------------------------------------------------------

if "%DEVELOPMENT_ENVIRONMENT_FUNDAMENTAL%"=="" (
    echo.
    echo ERROR: Please run Activate.cmd within a repository before running this script. It may be necessary to Setup and Activate the Common_Environment repository before setting up this one.
    echo.
    goto end
)

pushd "%~dp0"
call %DEVELOPMENT_ENVIRONMENT_FUNDAMENTAL%\RepositoryBootstrap\Impl\Setup.cmd %*
set _SETUP_ERROR=%ERRORLEVEL%
popd

if %_SETUP_ERROR% NEQ 0 (exit /B %_SETUP_ERROR%)

:end
