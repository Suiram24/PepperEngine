#pragma once

#include "../PeEngineCore/PeEngineCore.h"

//Particle components

struct Position
{
	engine::maths::CPeVector3 m_position;
};

struct Velocity
{
	engine::maths::CPeVector3 m_velocity;
};

struct Acceleration
{
	engine::maths::CPeVector3 m_acceleration;
};

struct Mass
{
	double m_massInverse;
};

struct ParticleCustomValues
{
	engine::maths::CPeVector3 m_gravity; //Custom Gravity
	double m_damping;
};

//Rigidbody

//struct Rotation
//{
//	engine::maths::CPeQuaternion m_rotation;
//};
//
//double m_angularDamping;
//
//pemaths::CPeVector3 m_angularAcceleration;
//
//pemaths::CPeVector3 m_angularVelocity;
//
//pemaths::CPeVector3 m_sumTorques;
//
//pemaths::CPeMatrix3 m_inertiaInverse;