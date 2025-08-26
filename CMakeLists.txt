# CMakeLists.txt for RDS1 Engine, Primary project
# Written by APAMk2, 2025 (C)
#

cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	option(64BIT "Enabling 64-bit building" OFF)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	option(64BIT "Enabling 64-bit building" ON)
endif()

project ("RDS1Engine")

set(SDL3_DIR "${PROJECT_SOURCE_DIR}/3RDPARTY/SDL3/CMake")
include_directories(SDL3 "${PROJECT_SOURCE_DIR}/SRC/SHARED")
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

set(SHARED_SRC
	"${PROJECT_SOURCE_DIR}/SRC/SHARED/Common.cpp"
	"${PROJECT_SOURCE_DIR}/SRC/SHARED/Buffer.cpp"
	"${PROJECT_SOURCE_DIR}/SRC/SHARED/Logging.cpp"
)

file(GLOB IMGUI_SRC
     "${PROJECT_SOURCE_DIR}/3RDPARTY/IMGUI/*.cpp"
)

add_subdirectory("SRC/CLIENT")
add_subdirectory("SRC/SERVER")