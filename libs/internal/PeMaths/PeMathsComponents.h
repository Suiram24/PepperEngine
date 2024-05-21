#pragma once

#include "CPeVector3.h"
#include "CPeQuaternion.h"

struct Position
{
	engine::maths::CPeVector3 m_position;
};

struct Rotation
{
	engine::maths::CPeQuaternion m_rotation;
};

struct Scale
{
	engine::maths::CPeVector3 m_scale;
};