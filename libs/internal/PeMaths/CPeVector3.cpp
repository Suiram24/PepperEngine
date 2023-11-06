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
				m_x + p_vector.GetX(),
				m_y + p_vector.GetY(),
				m_z + p_vector.GetZ());
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
				m_x - p_vector.GetX(),
				m_y - p_vector.GetY(),
				m_z - p_vector.GetZ());
			
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
			return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
		}

		CPeVector3 CPeVector3::NormalizeVector() const
		{
			double norm = this->GetNorm();
			CPeVector3 normVector = CPeVector3(
				m_x / norm,
				m_y / norm,
				m_z / norm);
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

		CPeVector3 CPeVector3::OrthographicProjection(const CPeVector3& p_vectorA, const CPeVector3& p_vectorB)
		{
			double normB = p_vectorB.GetNorm();
			return p_vectorB * (CPeVector3::ScalarProduct(p_vectorA, p_vectorB) / (normB * normB));
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
		
		double CPeVector3::DistanceTo(const CPeVector3& p_vector) const
		{
			return (*this - p_vector).GetNorm();
		}


		void CPeVector3::PrintCoordinate() const
		{
			printf("x: %lf; y: %lf; z: %lf\n", GetX(), GetY(), GetZ());
		}

        CPeVector3 operator*(double p_scalar, const CPeVector3 &vector)
        {
            return vector*p_scalar;
        }

    }
}