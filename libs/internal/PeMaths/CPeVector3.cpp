#include "CPeVector3.h"
#include <cmath>
#include <cstdio>

namespace engine {
	namespace maths {
		
		CPeVector3* CPeVector3::operator=(const CPeVector3& p_vector)
		{
			this->m_x_coordinate = new double(p_vector.getX());
			this->m_y_coordinate = new double(p_vector.getY());
			this->m_z_coordinate = new double(p_vector.getZ());
			return this;
		}

		CPeVector3* CPeVector3::operator+(const CPeVector3& p_vector) const
		{
			CPeVector3* sumVector = new CPeVector3(
				this->getX() + p_vector.getX(),
				this->getY() + p_vector.getY(),
				this->getZ() + p_vector.getZ());
			return sumVector;
		}

		CPeVector3* CPeVector3::operator+=(const CPeVector3& p_vector)
		{
			(*m_x_coordinate) += p_vector.getX();
			(*m_y_coordinate) += p_vector.getY();
			(*m_z_coordinate) += p_vector.getZ();
			return this;
		}

		CPeVector3* CPeVector3::operator-(const CPeVector3& p_vector) const
		{
			CPeVector3* subVector = new CPeVector3(
				this->getX() - p_vector.getX(),
				this->getY() - p_vector.getY(),
				this->getZ() - p_vector.getZ());
			return subVector;
		}

		CPeVector3* CPeVector3::operator-=(const CPeVector3& p_vector)
		{
			(*m_x_coordinate) -= p_vector.getX();
			(*m_y_coordinate) -= p_vector.getY();
			(*m_z_coordinate) -= p_vector.getZ();
			return this;
		}

		CPeVector3* CPeVector3::operator*(double p_scalar) const
		{
			CPeVector3* mulVector = new CPeVector3(
				p_scalar * this->getX(),
				p_scalar * this->getY(),
				p_scalar * this->getZ());
			return mulVector;
		}

		const double CPeVector3::getNorm() const
		{
			return sqrt(pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2));
		}

		CPeVector3* CPeVector3::normalizeVector() const
		{
			const double& norm = this->getNorm();
			CPeVector3* normVector = new CPeVector3(
				this->getX() / norm,
				this->getY() / norm,
				this->getZ() / norm);
			return normVector;
		}

		CPeVector3* CPeVector3::vectorProduct(const CPeVector3& p_vectorA, const CPeVector3& p_vectorB)
		{
			CPeVector3* prodVector = new CPeVector3(
				p_vectorA.getY() * p_vectorB.getZ() - p_vectorA.getZ() * p_vectorB.getY(),
				p_vectorA.getZ() * p_vectorB.getX() - p_vectorA.getX() * p_vectorB.getZ(),
				p_vectorA.getX() * p_vectorB.getY() - p_vectorA.getY() * p_vectorB.getX());
			return prodVector;
		}

		double CPeVector3::getX() const
		{
			return *m_x_coordinate;
		}

		double CPeVector3::getY() const
		{
			return *m_y_coordinate;
		}
		
		double CPeVector3::getZ() const
		{
			return *m_z_coordinate;
		}

		void CPeVector3::printCoordinate() const
		{
			printf("x: %lf; y: %lf; z: %lf\n", getX(), getY(), getZ());
		}

	}
}