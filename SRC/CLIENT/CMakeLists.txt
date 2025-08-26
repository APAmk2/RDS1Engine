# CMakeLists.txt for RDS1 Engine, Client-Side
# Written by APAMk2, 2025 (C)
#

cmake_minimum_required (VERSION 3.12)

include_directories("${PROJECT_SOURCE_DIR}/3RDPARTY/GLEW/include" 
					"${PROJECT_SOURCE_DIR}/3RDPARTY/GLM" 
					"${PROJECT_SOURCE_DIR}/3RDPARTY/LODEPNG")
find_package(OpenGL)

set (1STPARTY_SRC
	"RNDRCOMN/Texture.cpp"
	"RNDRCOMN/Model.cpp"
	"OGL/ShaderOGL.cpp"
	"OGL/RenderOGL.cpp"
#	"NET/NetClient.cpp"
	"Client.cpp"
	"MainClient.cpp")

set (3RDPARTY_SRC
	"${PROJECT_SOURCE_DIR}/3RDPARTY/LODEPNG/lodepng.cpp"	
)

add_executable (CLIENT ${SHARED_SRC} ${1STPARTY_SRC} ${3RDPARTY_SRC})
if(64BIT)
	target_link_libraries (CLIENT debug "${PROJECT_SOURCE_DIR}/3RDPARTY/GLEW/lib/Debug/x64/glew32sd.lib" 
										"${PROJECT_SOURCE_DIR}/3RDPARTY/GLEW/lib/Release/x64/glew32s.lib"
										SDL3::SDL3
										OpenGL::GL
										OpenGL::GLU)
else()
	target_link_libraries (CLIENT debug "${PROJECT_SOURCE_DIR}/3RDPARTY/GLEW/lib/Debug/Win32/glew32sd.lib" 
										"${PROJECT_SOURCE_DIR}/3RDPARTY/GLEW/lib/Release/Win32/glew32s.lib"
										SDL3::SDL3
										OpenGL::GL
										OpenGL::GLU)
endif()

if(WIN32)
	target_link_libraries(CLIENT wsock32 ws2_32)
endif()

set_property(TARGET CLIENT PROPERTY CXX_STANDARD 20)
set_target_properties(CLIENT PROPERTIES
					  RUNTIME_OUTPUT_NAME "CLIENT"
					  RUNTIME_OUTPUT_NAME_DEBUG "CLNTDEBG"
)

if(64BIT)
	set_target_properties(CLIENT PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/BIN/CLIENT/X64/DEBUG"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/BIN/CLIENT/X64/RELEASE"
					  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_SOURCE_DIR}/BIN/CLIENT/X64/DEBUGREL"
					  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${PROJECT_SOURCE_DIR}/BIN/CLIENT/X64/MINREL")
else()
	set_target_properties(CLIENT PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/BIN/CLIENT/X86/DEBUG"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/BIN/CLIENT/X86/RELEASE"
					  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_SOURCE_DIR}/BIN/CLIENT/X86/DEBUGREL"
					  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${PROJECT_SOURCE_DIR}/BIN/CLIENT/X86/MINREL")
endif()