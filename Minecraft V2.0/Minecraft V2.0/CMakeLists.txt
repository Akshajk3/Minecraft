file(GLOB SOURCES "src/*.cpp" "src/*.c")

add_executable (CMakeTarget ${SOURCES})

target_include_directories(CMakeTarget PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_directories(CMakeTarget PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/lib-vc2022
)

target_link_libraries(CMakeTarget PRIVATE
	glfw3
	opengl32
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()