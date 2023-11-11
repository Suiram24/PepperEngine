#include "CPePhysicalObject.h"

namespace engine {
    namespace physics {

        CPePhysicalObject::CPePhysicalObject() : 
            CPeComponent()
            , m_velocity(pemaths::CPeVector3(0., 0., 0.))
            , m_acceleration(pemaths::CPeVector3(0., 0., 0.))
            , m_massInverse(0)
            , m_damping(0)
            , m_sumForces(pemaths::CPeVector3(0., 0., 0.))
        {}
    }
} 