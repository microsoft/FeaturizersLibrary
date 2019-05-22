#!/bin/bash
# ----------------------------------------------------------------------
# |  
# |  Setup.sh
# |  
# |  David Brownell <db@DavidBrownell.com>
# |      2018-05-09 10:37:21
# |  
# ----------------------------------------------------------------------
# |  
# |  Copyright David Brownell 2018-19.
# |  Distributed under the Boost Software License, Version 1.0.
# |  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# |  
# ----------------------------------------------------------------------
set -e                                      # Exit on error
set +v                                      # Disable output

# ----------------------------------------------------------------------
# |  
# |  Run as:
# |     ./Setup.sh [/debug] [/verbose] [/configuration=<config_name>]*
# |  
# ----------------------------------------------------------------------
# Note that sudo is necessary because the process will create symbolic links

if [[ "${DEVELOPMENT_ENVIRONMENT_FUNDAMENTAL}" = "" ]]
then
    echo 
    echo "ERROR: Please run Activate.sh within a repository before running this script. It may be necessary to Setup and Activate the Common_Environment repository before setting up this one."
    echo 
    
    exit -1
fi

pushd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" > /dev/null
source $DEVELOPMENT_ENVIRONMENT_FUNDAMENTAL/RepositoryBootstrap/Impl/Setup.sh "$@"
popd > /dev/null
