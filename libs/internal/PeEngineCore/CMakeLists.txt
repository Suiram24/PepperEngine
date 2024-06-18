link_directories(libs/internal/PeMaths)
add_library(PeEngineCore	PeEngineCore.h 
							"CPeEntity.h" "CPeEntity.cpp"
							"CPeComponent.h" "CPeComponent.cpp"
							"CPeObjectPool.h"
							"CPeWorld.h" "CPeWorld.cpp"
							 "CRC32.h")
target_link_libraries(PeEngineCore PeMaths)