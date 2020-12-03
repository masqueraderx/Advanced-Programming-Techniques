cmake_minimum_required(VERSION 3.17)
project(Project)

set(CMAKE_CXX_STANDARD 14)
# 添加头文件
#use glew
#set(GLEW_H /usr/local/Cellar/glew/2.1.0_1/include/GL)
#set(GLFW_H /usr/local/Cellar/glfw/3.3.2/include/GLFW)
#include_directories(${GLEW_H} ${GLFW_H})
#
## 添加目标链接
#set(GLEW_LINK /usr/local/Cellar/glew/2.1.0_1/lib/libGLEW.2.1.dylib)
#set(GLFW_LINK /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.dylib)
#link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

# 执行编译命令
#set(SOURCE_FILES main.cpp ECE_Ghost.cpp ECE_Ghost.h ECE_Pacman.cpp ECE_Pacman.h)
add_executable(Project main.cpp ghost.cpp ghost.h pacman.cpp pacman.h maze.cpp maze.h)
#add_executable(Lab4 ${SOURCE_FILES})


FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

if (APPLE)
    target_link_libraries(Project "-framework OpenGL")
    target_link_libraries(Project "-framework GLUT")
endif()