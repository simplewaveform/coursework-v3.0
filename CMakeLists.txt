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
        Src/app.cpp
        Src/TabRCfilter.cpp
        Src/TabRegulator.cpp
        Src/TabOpamp.cpp
        Src/LowpassRC.cpp
        Src/ImageProcessor.cpp
        Src/TL431.cpp
        Src/LM317.cpp
        Src/InvertingOpamp.cpp
        Src/NonInvertingOpamp.cpp
        Src/TextManipulator.cpp
        Src/TabTools.cpp
        Src/GraphRenderer.cpp
        Src/ExceptionHandler.cpp

        Inc/TabRCfilter.h
        Inc/app.h
        Inc/TabRegulator.h
        Inc/TabOpamp.h
        Inc/CircuitComponent.h
        Inc/Filter.h
        Inc/LowpassRC.h
        Inc/ImageProcessor.h
        Inc/TL431.h
        Inc/Regulator.h
        Inc/LM317.h
        Inc/Opamp.h
        Inc/InvertingOpamp.h
        Inc/NonInvertingOpamp.h
        Inc/TextManipulator.h
        Inc/TabTools.h
        Inc/GraphRenderer.h
        Inc/magic.h
        Inc/ExceptionHandler.h
        Inc/BaseTab.h

        ${app_ICON}
)

# Include wxWidgets directories
include_directories(${wxWidgets_INCLUDE_DIRS})

# Link wxWidgets libraries
target_link_libraries(CircuitWave ${wxWidgets_LIBRARIES})