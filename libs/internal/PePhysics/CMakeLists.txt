link_directories(libs/internal/PeEngineCore)
link_directories(libs/internal/PeMaths)

add_library(PePhysics	PePhysics.h 
						"CPeForceSystem.h"						"CPeForceSystem.cpp"
						CPePhysicalObject.h						CPePhysicalObject.cpp
						"CPeParticle.h"							"CPeParticle.cpp"
						CPeRigidBody.h							CPeRigidBody.cpp
						"CPeForce.h"							"CPeForce.cpp" 
						"EngineForces/CPeForceDrag.h"			"EngineForces/CPeForceDrag.cpp"   
						"EngineForces/CPeForceSpring.h"			"EngineForces/CPeForceSpring.cpp" 
						"EngineForces/CPeForceAnchoredSpring.h"	"EngineForces/CPeForceAnchoredSpring.cpp" 
						"EngineForces/CPeForceBuoyancy.h"		"EngineForces/CPeForceBuoyancy.cpp" 
						"SPeParticleForceEntry.h" "CollisionSystem/CPeCollisionSystem.h" "CollisionSystem/CPeParticleContact.h" "CollisionSystem/CPeColliderComponent.h"  "CollisionSystem/CPeParticleContact.cpp" "CollisionSystem/CPeCollisionSystem.cpp" "CollisionSystem/CPeContactCable.cpp" "CollisionSystem/CPeContactRod.h" "CollisionSystem/CPeContactRod.cpp" "CollisionSystem/CPeColliderComponent.cpp")

target_link_libraries(PePhysics PeEngineCore PeMaths)