link_directories(libs/internal/PeEngineCore)
link_directories(libs/internal/PeMaths)

add_library(PePhysics	PePhysics.h 
						"CPeForceSystem.h"							"CPeForceSystem.cpp"
						"CPeParticle.h"								"CPeParticle.cpp"
						CPeRigidBody.h								CPeRigidBody.cpp
						"CPeForce.h"								"CPeForce.cpp" 
						"EngineForces/CPeForceDrag.h"				"EngineForces/CPeForceDrag.cpp"   
						"EngineForces/CPeForceSpring.h"				"EngineForces/CPeForceSpring.cpp" 
						"EngineForces/CPeForceAnchoredSpring.h"		"EngineForces/CPeForceAnchoredSpring.cpp" 
						"EngineForces/CPeForceBuoyancy.h"			"EngineForces/CPeForceBuoyancy.cpp" 
						"EngineForces/CPeForceFree.cpp" 			"EngineForces/CPeForceFree.h"
						"EngineForces/CPeForceCustomLocal.cpp"		"EngineForces/CPeForceCustomLocal.h"
						"SPeParticleForceEntry.h"
						"CollisionSystem/CPeCollisionSystem.h" 		"CollisionSystem/CPeCollisionSystem.cpp"
						"CollisionSystem/CPeParticleContact.h" 		"CollisionSystem/CPeParticleContact.cpp"
						"CollisionSystem/CPeColliderComponent.h" 	"CollisionSystem/CPeColliderComponent.cpp"
						"CollisionSystem/CPeContactRod.h"			"CollisionSystem/CPeContactRod.cpp"
						"CollisionSystem/CPeContactCable.h"			"CollisionSystem/CPeContactCable.cpp")

target_link_libraries(PePhysics PeEngineCore PeMaths)