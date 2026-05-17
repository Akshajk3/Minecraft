file(GLOB SOURCES "src/*.cpp" "src/*.c")

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Dependencies
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (WIN32)
    target_link_directories(main PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Dependencies/GLFW/lib-vc2022
    )
    target_link_libraries(main PRIVATE
        glfw3
        opengl32
    )
elseif (APPLE)
    target_include_directories(main PRIVATE
        /opt/homebrew/include
    )
    target_link_directories(main PRIVATE
        /opt/homebrew/lib
    )
    target_link_libraries(main PRIVATE
        glfw.3.4
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
    )
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()