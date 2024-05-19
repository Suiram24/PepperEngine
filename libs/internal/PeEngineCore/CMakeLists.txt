link_directories(libs/internal/PeMaths)
add_library(PeEngineCore	PeEngineCore.h 
							"CPeEntity.h" "CPeEntity.cpp"
							"CPeComponent.h" "CPeComponent.cpp"
							"CPeObjectPool.h"
							)

#Flecs
include(FetchContent)
FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs
  GIT_TAG        198607d10ab8f8fc44540043271d6e3be019250b # release v3.2.11
)

FetchContent_MakeAvailable(flecs)

target_link_libraries(PeEngineCore PeMaths flecs::flecs_static)