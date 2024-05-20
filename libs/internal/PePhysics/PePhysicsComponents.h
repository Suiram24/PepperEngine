#pragma once

#include "../PeEngineCore/PeEngineCore.h"

//Default values (singleton components, do not add to entities)
struct WorldDefaults
{
	engine::maths::CPeVector3 m_DefaultGravity;
	double m_DefaultDamping;
};

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

struct ForceReceiver
{
	engine::maths::CPeVector3 m_sumForces;
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

// Forces

struct AnchoredSpring
{
	engine::maths::CPeVector3 m_anchorPoint;
	float m_k;
	float m_restLength;
};

struct Spring
{
	engine::maths::CPeVector3 m_anchorPoint;
	float m_k;
	float m_restLength;
};

struct BuoyancyForce
{
	float m_immersionDepth;// depth for half immersion of the particle in m (particle "radius")
	float m_volume;//particle volume in m**3
	float m_liquidLevel;// in m
	float m_liquidDensity;
};

struct DragForce
{
	float k1;
	float k2;
};

struct FreeForce
{
	engine::maths::CPeVector3 m_forceValue;
};

//Rigidbody

struct Rotation
{
	engine::maths::CPeQuaternion m_rotation;
};

struct AngularVelocity
{
	engine::maths::CPeQuaternion m_angularVelocity;
};

struct AngularAcceleration
{
	engine::maths::CPeQuaternion m_angularAcceleration;
};

struct RigidBody
{
	engine::maths::CPeVector3 m_sumTorques; 
	engine::maths::CPeVector3 m_inertiaInverse; //Custom Gravity
	double m_angularDamping;
};
