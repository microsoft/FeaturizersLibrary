
Data Pipelines
==============

*Data Pipelines* are used to convert from arbitrary data into a matrix/tensor that can be consumed by machine learning algorithms.

Contributing
============

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

Developer Quick Start
=====================
Note that these commands should be invoked within the root of the repository.

**Linux**

1) Run `sudo ./bootstrap.sh ..`

    This will need to happen once per machine or after a repository has moved to a different directory. Note that `sudo` is not necessary when running within a Docker container.

2) Run `source ./Activate.sh x64`

    This will need to happen each time a new terminal window is opened.

**Windows**

1) Run `bootstrap.cmd ..`

    This will need to happen once per machine or after a repository has moved to a different directory.

2) Run `Activate.cmd x64`

    This will need to happen each time a new terminal window is opened.

Useful Development Commands
---------------------------

The following commands are available within an activated terminal window.

Name            | Command                   | Description
----------------|---------------------------|------------------------------------------------------------
DevEnvScripts   | `DevEnvScripts.sh|.cmd`   | Lists all scripts available in the activated environment.
Builder         | `Builder.sh|.cmd`         | Builds C++, Python, C#, etc. files; invoked by the CI machine.
Tester          | `Tester.sh|.cmd`          | Tests C++, Python, C#, etc. files; invoked by the CI machine.
Formatter       | `Formatter.sh|.cmd`       | Formats C++ and Python source files. (Coming Soon)

Invoking CMake
--------------

Native code is built via [CMake](https://cmake.org/). The following commands can be used to build any folder that contains a `CMakeLists.txt` file.
In each example, create a `build` directory that will contain the generated CMake content and eventual binaries.

Assumed directory structure:

    | - <Workspace dir>
        | - CMakeLists.txt
        | - ...
        | - build
            | - <Initially empty>

Within `<Workspace Dir>/build` run...

- [Debug] `cmake -G Ninja ..`
- [Debug with Code Coverage] `cmake -G Ninja -D CppCommon_CODE_COVERAGE=ON ..`
- [Release] `cmake -G Ninja -D CMAKE_BUILD_TYPE=Release ..`

Once CMake has generated the build files, within `<WorkSpace Dir>/build` run...

- [Build] `cmake --build .` or `ninja -v` (if the build generator was Ninja)
- [Test] `ctest --parallel`

Documentation
--------------
**Latest release**

-[0.3.6-preview 4](https://featurizerslibrarybuild.blob.core.windows.net/archive/0.3.6-preview.4/Documentation/Microsoft.Featurizer-cpp/v1.0/html/index.html)

-[0.3.6-preview 3](https://featurizerslibrarybuild.blob.core.windows.net/archive/0.3.6-preview.3/Documentation/Microsoft.Featurizer-cpp/v1.0/html/index.html)

-[0.3.6-preview 2](https://featurizerslibrarybuild.blob.core.windows.net/archive/0.3.6-preview.2/Documentation/Microsoft.Featurizer-cpp/v1.0/html/index.html)

-[0.3.6-preview 1](https://featurizerslibrarybuild.blob.core.windows.net/archive/0.3.6-preview.1/Documentation/Microsoft.Featurizer-cpp/v1.0/html/index.html)

## Featurizers
Information for setup/configuration of the Featurizers library can be found [here](src/FeaturizerPrep/Readme.md)
