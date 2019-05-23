#!/bin/bash
# ----------------------------------------------------------------------
# |
# |  bootstrap.sh
# |
# |  David Brownell <db@DavidBrownell.com>
# |      2019-05-21 11:27:06
# |
# ----------------------------------------------------------------------
# |
# |  Copyright David Brownell 2019
# |  Distributed under the Boost Software License, Version 1.0. See
# |  accompanying file LICENSE_1_0.txt or copy at
# |  http://www.boost.org/LICENSE_1_0.txt.
# |
# ----------------------------------------------------------------------
set -e                                      # Exit on error
set +v                                      # Disable output

should_continue=1

if [[ ${should_continue} == 1 && "$1" == "" ]]
then
    echo ""
    echo "This script bootstraps common library enlistment and setup."
    echo ""
    echo "    Usage:"
    echo "        $0 <common code dir>"
    echo ""

    should_continue=0
fi

if [[ ${should_continue} == 1 && ${DEVELOPMENT_ENVIRONMENT_REPOSITORY_ACTIVATED_FLAG} ]]
then
    echo ""
    echo "ERROR: Please run this from a standard (non-activated) command prompt."
    echo ""

    should_continue=0
fi

if [[ ${should_continue} == 1 ]]
then
    # Bootstrap enlistment and setup of Common_Environment, and then invoke
    # bootstrap_impl.py once python is available.

    if [[ ! -e "$1/Common/Environment" ]]
    then
        git clone https://github.com/davidbrownell/Common_Environment_v3.git "$1/Common/Environment"
    fi

    name=""
    ARGS=()

    for var in "${@:2}"
    do
        if [[ $var == /name=* ]] || [[ $var == -name=* ]]
        then
            name=`echo $var | cut -d'=' -f 2`
        else
            ARGS+=("$var")
        fi
    done

    if [[ ! -z "${name}" ]]
    then
        name_arg="/name=${name}"
    else
        name_arg=""
    fi

    "$1/Common/Environment/Setup.sh" ${name_arg} ${ARGS[@]}
    
    # Write the environment activation and python execution statements to a temporary
    # file so this environment remains unactivated (by doing this, the current script
    # can be invoked multiple times from the same environment).
    if [[ ! -z "${name}" ]]
    then
        activate_cmd="Activate.${name}.sh"
    else
        activate_cmd="Activate.sh"
    fi

    this_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

    cat >bootstrap_tmp.sh <<EOL
#!/bin/bash
. "$1/Common/Environment/${activate_cmd}" python36
python "${this_dir}/bootstrap_impl.py" "$1" ${ARGS[@]}
EOL

    chmod +x bootstrap_tmp.sh
    ./bootstrap_tmp.sh
    error_code=${error_code}

    rm bootstrap_tmp.sh

    if [[ ${error_code} -ne 0 ]]
    then
        should_continue=0
    fi
fi
