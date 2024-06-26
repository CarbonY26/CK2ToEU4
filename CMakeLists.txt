cmake_minimum_required(VERSION 3.16)

project(CK2ToEU4)
set(CONVERTER_SOURCE_DIR ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/Source)
set(CONVERTER_DIR ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(FRONTER_DIR ${CMAKE_SOURCE_DIR}/Fronter/)
set(FRONTER_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Fronter/Fronter/Source)
set(FRONTER_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release-Linux)
set(CONVERTER_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release-Linux/${PROJECT_NAME})
set(TEST_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test/Release-Linux)
set(CMAKE_CXX_STANDARD 20)
set(UNICODE_DEFAULT OFF)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

include_directories("/usr/include/wx-3.2-unofficial")
include_directories("/usr/lib/x86_64-linux-gnu/wx/include/gtk3-unicode-3.2-unofficial")
include_directories("commonItems")
include_directories("commonItems/external/zip/src")
include_directories("commonItems/external/googletest/googletest")
include_directories("commonItems/external/googletest/googletest/include")
include_directories("commonItems/external/googletest/googlemock")
include_directories("commonItems/external/googletest/googlemock/include")
include_directories("commonItems/external/zip/src")
include_directories("commonItems/external/json/single_include")
include_directories("Fronter/external/SQLiteCpp/include")
include_directories("Fronter/external/SQLiteCpp/sqlite3")
include_directories("Fronter/Fronter/Source")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${CONVERTER_SOURCE_DIR}")

add_compile_options(-D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__ -pthread -O2)

#### Converter ####

set(PCH_SOURCES "commonItems/BulkParser.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/Color.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/CommonFunctions.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/CommonRegexes.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/ConvenientParser.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/ConverterVersion.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/Date.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/GameVersion.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/Log.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/OSCompatibilityLayer.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/Parser.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/ParserHelpers.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/StringUtils.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/targa.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/ModLoader/ModFilesystem.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/ModLoader/Mod.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/ModLoader/ModLoader.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/ModLoader/ModParser.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/Localization/LocalizationBlock.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/Localization/LocalizationDatabase.h")
set(PCH_SOURCES ${PCH_SOURCES} "commonItems/Localization/LocalizationLambdas.h")

set(COMMON_SOURCES "commonItems/CommonFunctions.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/Color.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/ConvenientParser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/ConverterVersion.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/Date.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/GameVersion.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/LinuxUtils.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/Log.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/ModLoader/ModLoader.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/ModLoader/ModParser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/Parser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/ParserHelpers.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/OSCommonLayer.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/StringUtils.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/ModLoader/ModFilesystem.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/ModLoader/ModLoader.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/ModLoader/ModParser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "commonItems/external/zip/src/zip.c")

add_library(CommonItems ${COMMON_SOURCES})

file(GLOB MAIN_SOURCES "${CONVERTER_SOURCE_DIR}/*.cpp")
file(GLOB CONFIGURATION_SOURCES "${CONVERTER_SOURCE_DIR}/Configuration/*.cpp")
file(GLOB CK2WORLD_SOURCES "${CONVERTER_SOURCE_DIR}/CK2World/*.cpp")
file(GLOB CK2WORLD_SUBDIR_SOURCES "${CONVERTER_SOURCE_DIR}/CK2World/*/*.cpp")
file(GLOB MAPPER_SOURCES "${CONVERTER_SOURCE_DIR}/Mappers/*/*.cpp")
file(GLOB EU4WORLD_SOURCES "${CONVERTER_SOURCE_DIR}/EU4World/*.cpp")
file(GLOB EU4WORLD_SUBDIR_SOURCES "${CONVERTER_SOURCE_DIR}/EU4World/*/*.cpp")

add_library(CK2ToEU4lib
	${CONFIGURATION_SOURCES}
	${CK2WORLD_SOURCES}
	${CK2WORLD_SUBDIR_SOURCES}
	${MAPPER_SOURCES}
	${EU4WORLD_SOURCES}
	${EU4WORLD_SUBDIR_SOURCES}
)
target_precompile_headers(CK2ToEU4lib PUBLIC ${PCH_SOURCES})
target_link_libraries(CK2ToEU4lib LINK_PUBLIC CommonItems)

add_executable(CK2ToEU4Converter
	${MAIN_SOURCES}
)
set_target_properties(CK2ToEU4Converter
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CONVERTER_OUTPUT_DIRECTORY}
)
target_precompile_headers(CK2ToEU4Converter REUSE_FROM CK2ToEU4lib)
target_link_libraries(CK2ToEU4Converter LINK_PUBLIC CommonItems CK2ToEU4lib)

### FRONTER ###

file(GLOB F_MAIN_SOURCES "${FRONTER_SOURCE_DIR}/*.cpp")
file(GLOB F_CONFIGURATION_SOURCES "${FRONTER_SOURCE_DIR}/Configuration/*.cpp")
file(GLOB F_CONFIGURATION_OPTIONS_SOURCES "${FRONTER_SOURCE_DIR}/Configuration/Options/*.cpp")
file(GLOB F_FRAMES_SOURCES "${FRONTER_SOURCE_DIR}/Frames/*.cpp")
file(GLOB F_FRAMES_TABS_SOURCES "${FRONTER_SOURCE_DIR}/Frames/Tabs/*.cpp")
file(GLOB F_UTILS_SOURCES "${FRONTER_SOURCE_DIR}/Utils/*.cpp")
file(GLOB F_UTILS_LOCALIZATION_SOURCES "${FRONTER_SOURCE_DIR}/Utils/Localization/*.cpp")
file(GLOB F_CONVERTERLAUNCHER_SOURCES "${FRONTER_SOURCE_DIR}/WorkerThreads/ConverterLauncher/*.cpp")
list(REMOVE_ITEM F_CONVERTERLAUNCHER_SOURCES "${FRONTER_SOURCE_DIR}/WorkerThreads/ConverterLauncher/WinConverterLauncher.cpp")
file(GLOB F_LOGWATCHER_SOURCES "${FRONTER_SOURCE_DIR}/WorkerThreads/LogWatcher/*.cpp")
file(GLOB F_MODCOPIER_SOURCES "${FRONTER_SOURCE_DIR}/WorkerThreads/ModCopier/*.cpp")
file(GLOB F_UPDATECHECKER_SOURCES "${FRONTER_SOURCE_DIR}/UpdateChecker/*.cpp")
file(GLOB F_SQLITE_SOURCES "${FRONTER_SOURCE_DIR}/../../external/SQLiteCpp/src/*.cpp")
file(GLOB F_SQLITE3_SOURCES "${FRONTER_SOURCE_DIR}/../../external/SQLiteCpp/sqlite3/*.c")

add_executable(ConverterFrontend
	${F_MAIN_SOURCES}
	${F_CONFIGURATION_SOURCES}
	${F_CONFIGURATION_OPTIONS_SOURCES}
	${F_FRAMES_SOURCES}
	${F_FRAMES_TABS_SOURCES}
	${F_UTILS_SOURCES}
	${F_UTILS_LOCALIZATION_SOURCES}
	${F_CONVERTERLAUNCHER_SOURCES}
	${F_LOGWATCHER_SOURCES}
	${F_MODCOPIER_SOURCES}
	${F_UPDATECHECKER_SOURCES}
	${F_SQLITE_SOURCES}
	${F_SQLITE3_SOURCES}
)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
set_target_properties(ConverterFrontend
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${FRONTER_OUTPUT_DIRECTORY}
)
target_link_libraries(ConverterFrontend LINK_PUBLIC ${wxWidgets_LIBRARIES} ${CURL_LIBRARIES} CommonItems)

add_custom_command(TARGET CK2ToEU4Converter POST_BUILD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND git rev-parse HEAD > Release-Linux/commit_id.txt)
add_custom_command(TARGET CK2ToEU4Converter POST_BUILD WORKING_DIRECTORY ${CONVERTER_DIR} COMMAND chmod u+x Copy_Files.sh)
add_custom_command(TARGET CK2ToEU4Converter POST_BUILD WORKING_DIRECTORY ${CONVERTER_DIR} COMMAND ./Copy_Files.sh)

### TESTS ###

file(GLOB TEST_SOURCES "${PROJECT_NAME}Tests/*.cpp")
file(GLOB TEST_SUB_SOURCES "${PROJECT_NAME}Tests/*/*.cpp")
file(GLOB TEST_SUB_SUB_SOURCES "${PROJECT_NAME}Tests/*/*/*.cpp")
set(GTEST_SOURCES ${GTEST_SOURCES} "commonItems/external/googletest/googletest/src/gtest_main.cc")
set(GTEST_SOURCES ${GTEST_SOURCES} "commonItems/external/googletest/googletest/src/gtest-all.cc")
set(GTEST_SOURCES ${GTEST_SOURCES} "commonItems/external/googletest/googlemock/src/gmock-all.cc")

add_executable(
	CK2ToEU4Tests
	${TEST_SOURCES}
	${TEST_SUB_SOURCES}
	${TEST_SUB_SUB_SOURCES}
	${GTEST_SOURCES}
)

set_target_properties(CK2ToEU4Tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY}
)

target_precompile_headers(CK2ToEU4Tests REUSE_FROM CK2ToEU4lib)
target_link_libraries(CK2ToEU4Tests LINK_PUBLIC CommonItems CK2ToEU4lib)
