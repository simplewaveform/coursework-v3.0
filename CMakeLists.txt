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
        Src/TabRCfilter.cpp
        Src/TabRegulator.cpp
        Src/TabOpamp.cpp
        Src/LowpassRC.cpp
        Src/imageProcessor.cpp
        Src/TL431.cpp
        Src/CircuitComponent.cpp
        Src/LM317.cpp
        Src/InvOpamp.cpp
        Src/NonInvOpamp.cpp
        Src/textManipulations.cpp

        Inc/TabRCfilter.h
        Inc/main.h
        Inc/TabRegulator.h
        Inc/TabOpamp.h
        Inc/CircuitComponent.h
        Inc/Filter.h
        Inc/LowpassRC.h
        Inc/imageProcessor.h
        Inc/TL431.h
        Inc/Regulator.h
        Inc/LM317.h
        Inc/Opamp.h
        Inc/InvOpamp.h
        Inc/NonInvOpamp.h
        Inc/textManipulations.h

        ${app_ICON}
        Src/TabBase.cpp
        Inc/TabBase.h
        Src/GraphRenderer.cpp
        Inc/GraphRenderer.h
        Inc/magic.h

)

# Include wxWidgets directories
include_directories(${wxWidgets_INCLUDE_DIRS})

# Link wxWidgets libraries
target_link_libraries(CircuitWave ${wxWidgets_LIBRARIES})