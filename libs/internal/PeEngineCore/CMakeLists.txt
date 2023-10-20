link_directories(libs/internal/PeMaths)
add_library(PeEngineCore	PeEngineCore.h 
							"CPeEntity.h" "CPeEntity.cpp"
							"CPeComponent.h" "CPeComponent.cpp"
							"CPeObjectPool.h"
							)
target_link_libraries(PeEngineCore PeMaths)