#ifndef PEMATHS_PEMATHS_H
#define PEMATHS_PEMATHS_H

namespace engine
{
	namespace maths
	{
		/**
		 * @brief Class for auxiliary math functions.
		*/
		class CPeMaths {

		};

		/**
		 * @brief Class for a basic representation of a 3D vector.
		*/
		class CPe3DVector
		{
			// Fields
		private:
			double * m_x_coordinate;
			double * m_y_coordinate;
			double * m_z_coordinate;

			// Methods
		public:
			CPe3DVector(double p_x, double p_y, double p_z) : m_x_coordinate(new double(p_x)),
				m_y_coordinate(new double(p_y)),
				m_z_coordinate(new double(p_z))
			{
			}

			CPe3DVector(const CPe3DVector& p_vector) : m_x_coordinate(new double(p_vector.getX())),
				m_y_coordinate(new double(p_vector.getY())),
				m_z_coordinate(new double(p_vector.getZ()))
			{
			}

			/**
			 * @brief Redefine the operator 'equal' to make a deep copy of an other CPe3DVector.
			 * @param p_vector A CPe3DVector to copy
			 * @return 'this'.
			*/
			CPe3DVector* operator=(const CPe3DVector& p_vector);

			/**
			 * @brief Define the operator 'plus' for two CPe3DVector. None of the vectors are modified.
			 * @param p_vector A CPe3DVector to add to 'this'
			 * @return  A new CPe3DVector.
			*/
			CPe3DVector* operator+(const CPe3DVector& p_vector) const;

			/**
			 * @brief Define the operator 'minus' for two CPe3DVector. None of the vectors are modified.
			 * @param p_vector A CPe3DVector to substract from 'this'
			 * @return  A new CPe3DVector.
			*/
			CPe3DVector* operator-(const CPe3DVector& p_vector) const;

			/**
			 * @brief Define the operator 'multiplication' for a double and a CPe3DVector. 'this' is not modified.
			 * @param p_scalar A double to multipliate 'this'
			 * @return  A new CPe3DVector.
			*/
			CPe3DVector* operator*(double p_scalar) const;

			/**
			 * @brief Compute the norm of the CPe3DVector.
			 * @return A double.
			*/
			const double getNorm() const;

			/**
			 * @brief Compute the normalize vector associated with 'this'.
			 * @return A new CPe3DVector.
			*/
			CPe3DVector* normalizeVector() const;

			/**
			 * @brief Compute the scalar product (or dot product) between two CPe3DVector.
			 * @param p_vector_a A CPe3DVector.
			 * @param p_vector_b A CPe3DVector.
			 * @return A double.
			*/
			static const double scalarProduct(const CPe3DVector& p_vector_a, const CPe3DVector& p_vector_b)
			{
				return
					p_vector_a.getX() * p_vector_b.getX() +
					p_vector_a.getY() * p_vector_b.getY() +
					p_vector_a.getZ() * p_vector_b.getZ();
			}

			/**
			 * @brief Compute the vector product (or cross product) between to CPe3DVector.
			 * 
			 * @param p_vector_a A CPe3DVector.
			 * @param p_vector_b A CPe3DVector.
			 * @return A new CPe3DVector.
			*/
			static CPe3DVector* vectorProduct(const CPe3DVector& p_vector_a, const CPe3DVector& p_vector_b)
			{
				CPe3DVector* prod_vector = new CPe3DVector(
					p_vector_a.getY() * p_vector_b.getZ() - p_vector_a.getZ() * p_vector_b.getY(),
					p_vector_a.getZ() * p_vector_b.getX() - p_vector_a.getX() * p_vector_b.getZ(),
					p_vector_a.getX() * p_vector_b.getY() - p_vector_a.getY() * p_vector_b.getX());
				return prod_vector;
			}

			/**
			 * @brief Accessor to m_x_coordinate
			*/
			double getX() const;

			/**
			 * @brief Accessor to m_y_coordinate
			*/
			double getY() const;

			/**
			 * @brief Accessor to m_z_coordinate
			*/
			double getZ() const;

			/**
			 * @brief A simple print method. Meant for deggug.
			*/
			void printCoordinate() const;

			~CPe3DVector()
			{
				delete m_x_coordinate;
				delete m_y_coordinate;
				delete m_z_coordinate;
			}
		};
	}
}



#endif /* PEMATHS_PEMATHS_H */