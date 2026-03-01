#include "CPeVector2.h"
#include "CPeVector3.h"
#include <cmath>
#include <cstdio>
#include <cassert>

namespace engine {
	namespace maths {

		CPeVector2::CPeVector2(const CPeVector3& p_vector) :
			m_x(p_vector.GetX()),
			m_y(p_vector.GetY())
		{
		}
		
		CPeVector2& CPeVector2::operator=(const CPeVector2& p_vector)
		{
			this->m_x = p_vector.GetX();
			this->m_y = p_vector.GetY();
			return *this;
		}

		CPeVector2 CPeVector2::operator+(const CPeVector2& p_vector) const
		{
			CPeVector2 sumVector = CPeVector2(
				m_x + p_vector.GetX(),
				m_y + p_vector.GetY());
			return sumVector;
		}

		CPeVector2& CPeVector2::operator+=(const CPeVector2& p_vector)
		{
			m_x += p_vector.GetX();
			m_y += p_vector.GetY();
			return *this;
		}

		CPeVector2 CPeVector2::operator-(const CPeVector2& p_vector) const
		{
			CPeVector2 subVector = CPeVector2(
				m_x - p_vector.GetX(),
				m_y - p_vector.GetY());
			return subVector;
		}

		CPeVector2& CPeVector2::operator-=(const CPeVector2& p_vector)
		{
			m_x -= p_vector.GetX();
			m_y -= p_vector.GetY();
			return *this;
		}

		CPeVector2 CPeVector2::operator*(double p_scalar) const
		{
			CPeVector2 mulVector = CPeVector2(
				p_scalar * GetX(),
				p_scalar * GetY());
			return mulVector;
		}

		const double CPeVector2::GetNorm() const
		{
			return sqrt(m_x * m_x + m_y * m_y);
		}

		const double CPeVector2::GetSquaredNorm() const
		{
			return m_x * m_x + m_y * m_y;
		}

		CPeVector2 CPeVector2::NormalizeVector() const
		{
			double norm = this->GetNorm();
			if (norm == 0) //To avoid divisions by 0
			{
				return *this;
			}
			CPeVector2 normVector = CPeVector2(
				m_x / norm,
				m_y / norm);
			return normVector;
		}



		double CPeVector2::GetX() const
		{
			return m_x;
		}

		double CPeVector2::GetY() const
		{
			return m_y;
		}


		double CPeVector2::Get(int p_indice) const
		{
			switch (p_indice)
			{
			case 0:
				return m_x;
				break;
			case 1:
				return m_y;
				break;
			default:
				assert(false);
				break;
			}
		}

		
		double CPeVector2::DistanceTo(const CPeVector2& p_vector) const
		{
			return (*this - p_vector).GetNorm();
		}

		double CPeVector2::SquaredDistanceTo(const CPeVector2& p_vector) const
		{
			return (*this - p_vector).GetSquaredNorm();
		}


		void CPeVector2::PrintCoordinate() const
		{
			printf("x: %lf; y: %lf\n", GetX(), GetY());
		}

		void CPeVector2::SetX(double p_x)
		{
			m_x = p_x;
		}
		void CPeVector2::SetY(double p_y)
		{
			m_y = p_y;
		}

		void CPeVector2::Set(int p_indice, double p_value)
		{
			switch (p_indice)
			{
			case 0:
				m_x = p_value;
				break;
			case 1:
				m_y = p_value;
				break;
			default:
				assert(false);
				break;
			}
		}


		CPeVector2 operator*(double p_scalar, const CPeVector2 &vector)
		{
			return vector*p_scalar;
		}


	}
}