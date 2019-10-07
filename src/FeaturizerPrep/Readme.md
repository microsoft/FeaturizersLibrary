# VSCode CMake Build and Debugging setup

## Setup and Configuration
### Plugins
1. Install [CMake plugin](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)

2. Install [CMake Tools plugin](https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools)

3. Install [C/C++ plugin](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

### Settings
Open your settings (Ctrl + ',' or File -> Preferences -> Settings) and edit these settings:

* CMake: Build Directory -> `${workspaceRoot}/UnitTests/build/${env:DEVELOPMENT_ENVIRONMENT_OPERATING_SYSTEM}/${env:DEVELOPMENT_ENVIRONMENT_CPP_COMPILER_NAME}/${env:DEVELOPMENT_ENVIRONMENT_CPP_ARCHITECTURE}/${buildType}`

* CMake: Configure on Open -> `false`

* CMake: Source Directory -> `${workspaceRoot}/UnitTests`

* CMake: Use CMake Server -> `false` 

## Building
The first time you are building a folder you must additionally do this.  
1. Launch VSCode from an activated environment.  
    * You can build with any activated environment, but to debug on Windows it needs to be `x64_MSVC`.
2. Open the command palette (Ctrl + Shift + P) and run the `CMake: Configure` command. 

Once the above steps are completed in a folder you won't need to run them in that folder again. You will then follow these steps from then on to build.

1. Launch VSCode from an activated `x64_MSVC` environment.  
2. You will need to open VSCode directly from the folder above the unit test folder.  
For example. If you structure looks like this you should open the Featurizers folder to build the Unit Tests:
>        Featuriziers/  
>            FeaturizerOne.cpp  
>            FeaturizierTwo.cpp  
>            UnitTests/  
>                FeaturizerOne_UnitTest.pp  
>                CMakeLists.txt  

3. You can now hit f7 to build your code. If it prompts you to select a kit, pick "[Unspecified]".

## Debugging

1. Launch VSCode from an activated `x64_MSVC` environment.
2. The first time you are debugging you will need to create the launch.json file. To do this:
    1. Switch to the debug tab (Ctrl + Shift + D).
    2. At the top left you will see a green arrow with the words "No Configurations" to the right of it ![NoConfig](NoConfigurations.png)
    3. Click on "No Configurations" and click "Add Configuration"
    4. When it prompts you to select the environment, pick "C++ (Windows)". This will create and open the "launch.json" file automatically.
3. With your launch.json file open, replece the configuration object inside the `configurations` list with:  
    ```
    {  
        "name": "(Windows) Launch: <ExecutibleName>.exe [Debug]",  
        "type": "cppvsdbg",  
        "request": "launch",  
        "program": "${workspaceRoot}/UnitTests/build/${env:DEVELOPMENT_ENVIRONMENT_OPERATING_SYSTEM}/${env:DEVELOPMENT_ENVIRONMENT_CPP_COMPILER_NAME}/${env:DEVELOPMENT_ENVIRONMENT_CPP_ARCHITECTURE}/Debug/<ExecutibleName>.exe",  
        "args": [],  
        "stopAtEntry": false,  
        "cwd": "${workspaceFolder}",  
        "environment": [],  
        "externalConsole": false  
    }
4. Make sure you replace `<ExecutibleName>` with the correct name.
5. You will have to create one of these launch configs for every test file you want to run. Alternatively, you can only create one and edit it every time. 

You can now place breakpoints and run/debug the executible you setup in the launch.json configuration.

## Additional Notes
We also have others tests besides unit tests. When wanting to build/debug these, change all settings that have "UnitTests" in them to match the correct folder name. For example, when dealing with our integration tests, change the `CMake: Build Directory` and `CMake: Source Directory` to use `IntegrationTests` instead of `UnitTests`. This change is also required in the `program` section of the `launch.json` file.