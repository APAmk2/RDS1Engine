# CMakeLists.txt for RDS1Engine
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
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3RDPARTY/GLEW/include" SDL3)
set(SDL3_DIR "3RDPARTY/SDL3/CMake")
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(OpenGL)

set (1STPARTY_SRC
	"SRC/Common.cpp"
	"SRC/Engine.cpp"
	"SRC/Main.cpp")

set (3RDPARTY_SRC
	)

add_executable (RDS1Engine ${1STPARTY_SRC} ${3RDPARTY_SRC})
if(64BIT)
	target_link_libraries (RDS1Engine debug "${CMAKE_CURRENT_SOURCE_DIR}/3RDPARTY/GLEW/lib/Debug/x64/glew32sd.lib" 
											"${CMAKE_CURRENT_SOURCE_DIR}/3RDPARTY/GLEW/lib/Release/x64/glew32s.lib"
											SDL3::SDL3
											OpenGL::GL
											OpenGL::GLU)
else()
	target_link_libraries (RDS1Engine debug "${CMAKE_CURRENT_SOURCE_DIR}/3RDPARTY/GLEW/lib/Debug/Win32/glew32sd.lib" 
											"${CMAKE_CURRENT_SOURCE_DIR}/3RDPARTY/GLEW/lib/Release/Win32/glew32s.lib"
											SDL3::SDL3
											OpenGL::GL
											OpenGL::GLU)
endif()

set_property(TARGET RDS1Engine PROPERTY CXX_STANDARD 20)
set_target_properties(RDS1Engine PROPERTIES
					  RUNTIME_OUTPUT_NAME "ENGINE"
					  RUNTIME_OUTPUT_NAME_DEBUG "ENGNDBG"
)

if(64BIT)
	set_target_properties(RDS1Engine PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/BIN/X64/DEBUG"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/BIN/X64/RELEASE"
					  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/X64/BIN/DEBUGREL"
					  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/BIN/X64/MINREL")
else()
	set_target_properties(RDS1Engine PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/BIN/X86/DEBUG"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/BIN/X86/RELEASE"
					  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/BIN/X86/DEBUGREL"
					  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/BIN/X86/MINREL")
endif()