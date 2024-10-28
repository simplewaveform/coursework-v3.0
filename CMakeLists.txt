cmake_minimum_required(VERSION 3.10)
project(CircuitWave)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable app bundle creation on macOS
set(MACOSX_BUNDLE TRUE)
set(MACOSX_BUNDLE_BUNDLE_NAME "CircuitWave")

# Specify the icon file
set(MACOSX_BUNDLE_ICON_FILE myapp.icns)
set(app_ICON ${CMAKE_CURRENT_SOURCE_DIR}/Resources/myapp.icns)
set_source_files_properties(${app_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Find the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include the wxWidgets headers and libraries
include(${wxWidgets_USE_FILE})

# Add the source files, and specify it as a macOS bundle
add_executable(CircuitWave MACOSX_BUNDLE
        Src/main.cpp
        Src/tabRCfilter.cpp
        Src/tabregulator.cpp
        Src/tabopamp.cpp
        Src/lowpassRC.cpp
        Src/imageProcessor.cpp
        Src/lowpassLC.cpp
        Src/tabLCfilter.cpp
        Src/TL431.cpp
        Src/circuitComponent.cpp
        Src/LM317.cpp

        Inc/tabRCfilter.h
        Inc/main.h
        Inc/tabregulator.h
        Inc/tabopamp.h
        Inc/circuitComponent.h
        Inc/filter.h
        Inc/lowpassRC.h
        Inc/lowpassLC.h
        Inc/imageProcessor.h
        Inc/tabLCfilter.h
        Inc/TL431.h
        Inc/regulator.h
        Inc/LM317.h

        ${app_ICON}
        Inc/opamp.h
        Src/opamp.cpp
)




# Include wxWidgets directories
include_directories(${wxWidgets_INCLUDE_DIRS})

# Link wxWidgets libraries
target_link_libraries(CircuitWave ${wxWidgets_LIBRARIES})