file(GLOB_RECURSE CPPS  ./models.cpp ./main.cpp)
file(GLOB_RECURSE HPPS  ./models.hpp )

add_executable(flow ${CPPS} ${HPPS})

target_link_libraries(flow QtNodes)
