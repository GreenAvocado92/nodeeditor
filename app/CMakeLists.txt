file(GLOB_RECURSE CPPS  ./*.cpp)
file(GLOB_RECURSE HPPS  ./*.hpp )

add_executable(flow ${CPPS} ${HPPS})

target_link_libraries(flow QtNodes)
