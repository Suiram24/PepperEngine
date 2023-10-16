link_directories(libs/internal/PeMaths)
add_library(PeEngineCore PeEngineCore.h "CPeEntity.cpp" "CPeEntity.h")
target_link_libraries(PeEngineCore PeMaths)