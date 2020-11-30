add_executable(
    launcher
    launcher.cpp
)

target_compile_options(launcher PRIVATE "-std=c++2a" "-g")
set(CMAKE_EXE_LINKER_FLAGS "-g")