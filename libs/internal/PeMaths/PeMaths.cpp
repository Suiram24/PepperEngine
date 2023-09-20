#include "PeMaths.h"
#include <cmath>
#include <cstdio>

namespace engine {
	namespace maths {
		
		CPe3DVector* CPe3DVector::operator=(const CPe3DVector& p_vector)
		{
			this->m_x_coordinate = new double(p_vector.getX());
			this->m_y_coordinate = new double(p_vector.getY());
			this->m_z_coordinate = new double(p_vector.getZ());
			return this;
		}

		CPe3DVector* CPe3DVector::operator+(const CPe3DVector& p_vector) const
		{
			CPe3DVector* sum_vector = new CPe3DVector(
				this->getX() + p_vector.getX(),
				this->getY() + p_vector.getY(),
				this->getZ() + p_vector.getZ());
			return sum_vector;
		}

		CPe3DVector* CPe3DVector::operator-(const CPe3DVector& p_vector) const
		{
			CPe3DVector* sub_vector = new CPe3DVector(
				this->getX() - p_vector.getX(),
				this->getY() - p_vector.getY(),
				this->getZ() - p_vector.getZ());
			return sub_vector;
		}

		CPe3DVector* CPe3DVector::operator*(double p_scalar) const
		{
			CPe3DVector* mul_vector = new CPe3DVector(
				p_scalar * this->getX(),
				p_scalar * this->getY(),
				p_scalar * this->getZ());
			return mul_vector;
		}

		const double CPe3DVector::getNorm() const
		{
			return sqrt(pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2));
		}

		CPe3DVector* CPe3DVector::normalizeVector() const
		{
			const double& norm = this->getNorm();
			CPe3DVector* norm_vector = new CPe3DVector(
				this->getX() / norm,
				this->getY() / norm,
				this->getZ() / norm);
			return norm_vector;
		}

		double CPe3DVector::getX() const
		{
			return *m_x_coordinate;
		}

		double CPe3DVector::getY() const
		{
			return *m_y_coordinate;
		}
		
		double CPe3DVector::getZ() const
		{
			return *m_z_coordinate;
		}

		void CPe3DVector::printCoordinate() const
		{
			printf("x: %lf; y: %lf; z: %lf\n", getX(), getY(), getZ());
		}

	}
}