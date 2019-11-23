# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
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
