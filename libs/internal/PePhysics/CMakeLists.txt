link_directories(libs/internal/PeEngineCore)
link_directories(libs/internal/PeMaths)

add_library(PePhysics	PePhysics.h 
						"CPeForceSystem.h"									"CPeForceSystem.cpp"
						"CPeParticle.h"										"CPeParticle.cpp"
						CPeRigidBody.h										CPeRigidBody.cpp
						"CPeForce.h"										"CPeForce.cpp" 
						"EngineForces/CPeForceDrag.h"						"EngineForces/CPeForceDrag.cpp"   
						"EngineForces/CPeForceSpring.h"						"EngineForces/CPeForceSpring.cpp" 
						"EngineForces/CPeForceAnchoredSpring.h"				"EngineForces/CPeForceAnchoredSpring.cpp" 
						"EngineForces/CPeForceBuoyancy.h"					"EngineForces/CPeForceBuoyancy.cpp" 
						"EngineForces/CPeForceFree.cpp" 					"EngineForces/CPeForceFree.h"
						"EngineForces/CPeForceCustomLocal.h"				"EngineForces/CPeForceCustomLocal.cpp"
						"SPeParticleForceEntry.h"
						"CollisionSystem/CPeCollisionSystem.h" 				"CollisionSystem/CPeCollisionSystem.cpp"
						CollisionSystem/CPeCollisionResolutionSystem.h		CollisionSystem/CPeCollisionResolutionSystem.cpp
						CollisionSystem/CPeKDTree.h							CollisionSystem/CPeKDTree.cpp
						CollisionSystem/CPeNarrowPhaseSystem.h				CollisionSystem/CPeNarrowPhaseSystem.cpp
						"CollisionSystem/CPeColliderComponent.h" 			"CollisionSystem/CPeColliderComponent.cpp"	
						"CollisionSystem/CPePrimitiveShape.h"				"CollisionSystem/CPePrimitiveShape.cpp"
						"CollisionSystem/CPeSpherePrimitiveShape.h"			"CollisionSystem/CPeSpherePrimitiveShape.cpp"
						"CollisionSystem/CPePlanePrimitiveShape.h"			"CollisionSystem/CPePlanePrimitiveShape.cpp"
						"CollisionSystem/CPeBoxPrimitiveShape.h"			"CollisionSystem/CPeBoxPrimitiveShape.cpp" 
						"CollisionSystem/SPeContactInfos.h"
)

target_link_libraries(PePhysics PeEngineCore PeMaths)