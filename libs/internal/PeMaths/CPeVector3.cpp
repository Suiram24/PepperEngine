#include "CPeVector3.h"
#include <cmath>
#include <cstdio>

namespace engine {
	namespace maths {
		
		CPeVector3& CPeVector3::operator=(const CPeVector3& p_vector)
		{
			this->m_x = p_vector.GetX();
			this->m_y = p_vector.GetY();
			this->m_z = p_vector.GetZ();
			return *this;
		}

		CPeVector3 CPeVector3::operator+(const CPeVector3& p_vector) const
		{
			CPeVector3 sumVector = CPeVector3(
				this->GetX() + p_vector.GetX(),
				this->GetY() + p_vector.GetY(),
				this->GetZ() + p_vector.GetZ());
			return sumVector;
		}

		CPeVector3& CPeVector3::operator+=(const CPeVector3& p_vector)
		{
			m_x += p_vector.GetX();
			m_y += p_vector.GetY();
			m_z += p_vector.GetZ();
			return *this;
		}

		CPeVector3 CPeVector3::operator-(const CPeVector3& p_vector) const
		{
			CPeVector3 subVector = CPeVector3(
				this->GetX() - p_vector.GetX(),
				this->GetY() - p_vector.GetY(),
				this->GetZ() - p_vector.GetZ());
			
			return subVector;
		}

		CPeVector3& CPeVector3::operator-=(const CPeVector3& p_vector)
		{
			m_x -= p_vector.GetX();
			m_y -= p_vector.GetY();
			m_z -= p_vector.GetZ();
			return *this;
		}

		CPeVector3 CPeVector3::operator*(double p_scalar) const
		{
			CPeVector3 mulVector = CPeVector3(
				p_scalar * GetX(),
				p_scalar * GetY(),
				p_scalar * GetZ());
			return mulVector;
		}

		const double CPeVector3::GetNorm() const
		{
			return sqrt(pow(this->GetX(), 2) + pow(this->GetY(), 2) + pow(this->GetZ(), 2));
		}

		CPeVector3 CPeVector3::NormalizeVector() const
		{
			double norm = this->GetNorm();
			CPeVector3 normVector = CPeVector3(
				this->GetX() / norm,
				this->GetY() / norm,
				this->GetZ() / norm);
			return normVector;
		}

		CPeVector3 CPeVector3::CrossProduct(const CPeVector3& p_vectorA, const CPeVector3& p_vectorB)
		{
			CPeVector3 prodVector = CPeVector3(
				p_vectorA.GetY() * p_vectorB.GetZ() - p_vectorA.GetZ() * p_vectorB.GetY(),
				p_vectorA.GetZ() * p_vectorB.GetX() - p_vectorA.GetX() * p_vectorB.GetZ(),
				p_vectorA.GetX() * p_vectorB.GetY() - p_vectorA.GetY() * p_vectorB.GetX());
			return prodVector;
		}

		double CPeVector3::GetX() const
		{
			return m_x;
		}

		double CPeVector3::GetY() const
		{
			return m_y;
		}
		
		double CPeVector3::GetZ() const
		{
			return m_z;
		}

		void CPeVector3::PrintCoordinate() const
		{
			printf("x: %lf; y: %lf; z: %lf\n", GetX(), GetY(), GetZ());
		}

	}
}