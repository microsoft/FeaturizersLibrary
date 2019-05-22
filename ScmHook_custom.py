# ----------------------------------------------------------------------
# |
# |  ScmHook_custom.py
# |
# |  David Brownell <db@DavidBrownell.com>
# |      2018-05-07 13:21:00
# |
# ----------------------------------------------------------------------
# |
# |  Copyright David Brownell 2018-19.
# |  Distributed under the Boost Software License, Version 1.0.
# |  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
# |
# ----------------------------------------------------------------------
"""Contains SCM hooks"""

import os
import sys

sys.path.insert(0, os.getenv("DEVELOPMENT_ENVIRONMENT_FUNDAMENTAL"))
from RepositoryBootstrap.Impl import CommonEnvironmentImports

del sys.path[0]

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironmentImports.CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# <Unused argument> pylint: disable = W0613

# ----------------------------------------------------------------------
def OnCommitting(data, output_stream):                                                                                                                                                                                                                                                                                                                                                                                                 # , configuration):
    """
    Called when the repository is in the process of committing (but not 
    yet committed); return -1 or raise an exception to prevent the change 
    from being committed to the local repository.

    If the method includes the 'configuration' argument, it will be called
    once for each configuration defined by the repository. If the method
    doesn't include the value, it will only be called once.
    """

    return


# ----------------------------------------------------------------------
def OnPushing(data, output_stream):                                                                                                                                                                                                                                                                                                                                                                                            # , configuration):
    """
    Called when the repository is in the process of pushing (but not 
    yet pushed); return -1 or raise an exception to prevent the change from 
    being pushed to the remote repository.

    If the method includes the 'configuration' argument, it will be called
    once for each configuration defined by the repository. If the method
    doesn't include the value, it will only be called once.
    """

    return


# ----------------------------------------------------------------------
def OnPulled(data, output_stream):                                                                                                                                                                                                                                                                                                                                                                                                        # , configuration):
    """
    Called when the repository is in the process of pulling (but has not 
    yet committed the pulled changes); return -1 or raise an exception to 
    prevent the remote change from being persisted.

    If the method includes the 'configuration' argument, it will be called
    once for each configuration defined by the repository. If the method
    doesn't include the value, it will only be called once.
    """

    return
