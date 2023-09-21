#ifndef CPEVECTOR3_CPEVECTOR3_H
#define CPEVECTOR3_CPEVECTOR3_H

namespace engine
{
	namespace maths
	{
		/**
		 * @brief Class for a basic representation of a 3D vector.
		*/
		class CPeVector3
		{
			// Fields
		private:
			double* m_x_coordinate;
			double* m_y_coordinate;
			double* m_z_coordinate;

			// Methods
		public:
			CPeVector3(double p_x, double p_y, double p_z) : m_x_coordinate(new double(p_x)),
				m_y_coordinate(new double(p_y)),
				m_z_coordinate(new double(p_z))
			{
			}

			CPeVector3(const CPeVector3& p_vector) : m_x_coordinate(new double(p_vector.getX())),
				m_y_coordinate(new double(p_vector.getY())),
				m_z_coordinate(new double(p_vector.getZ()))
			{
			}

			/**
			 * @brief Redefine the operator 'equal' to make a deep copy of an other CPeVector3.
			 * @param p_vector A CPeVector3 to copy.
			 * @return 'this'.
			*/
			CPeVector3* operator=(const CPeVector3& p_vector);

			/**
			 * @brief Define the operator 'plus' for two CPeVector3. None of the vectors are modified.
			 * @param p_vector A CPeVector3 to add with 'this'.
			 * @return  A new CPeVector3.
			*/
			CPeVector3* operator+(const CPeVector3& p_vector) const;

			/**
			 * @brief Redefine the operator '+=' to work on CPeVector3.
			 * @param p_vector A CPeVector3 to add to 'this'.
			 * @return 'this'.
			*/
			CPeVector3* operator+=(const CPeVector3& p_vector);

			/**
			 * @brief Define the operator 'minus' for two CPeVector3. None of the vectors are modified.
			 * @param p_vector A CPeVector3 to substract from 'this'.
			 * @return  A new CPeVector3.
			*/
			CPeVector3* operator-(const CPeVector3& p_vector) const;

			/**
			 * @brief Redefine the operator '-=' to work on CPeVector3.
			 * @param p_vector A CPeVector3 to substract from 'this'.
			 * @return 'this'.
			*/
			CPeVector3* operator-=(const CPeVector3& p_vector);

			/**
			 * @brief Define the operator 'multiplication' for a double and a CPeVector3. 'this' is not modified.
			 * @param p_scalar A double to multipliate 'this'
			 * @return  A new CPeVector3.
			*/
			CPeVector3* operator*(double p_scalar) const;

			/**
			 * @brief Compute the norm of the CPeVector3.
			 * @return A double.
			*/
			const double getNorm() const;

			/**
			 * @brief Compute the normalize vector associated with 'this'.
			 * @return A new CPeVector3.
			*/
			CPeVector3* normalizeVector() const;

			/**
			 * @brief Compute the scalar product (or dot product) between two CPeVector3.
			 * @param p_vectorA A CPeVector3.
			 * @param p_vectorB A CPeVector3.
			 * @return A double.
			*/
			static const double scalarProduct(const CPeVector3& p_vectorA, const CPeVector3& p_vectorB)
			{
				return
					p_vectorA.getX() * p_vectorB.getX() +
					p_vectorA.getY() * p_vectorB.getY() +
					p_vectorA.getZ() * p_vectorB.getZ();
			}

			/**
			 * @brief Compute the vector product (or cross product) between to CPeVector3.
			 *
			 * @param p_vectorA A CPeVector3.
			 * @param p_vectorB A CPeVector3.
			 * @return A new CPeVector3.
			*/
			static CPeVector3* vectorProduct(const CPeVector3& p_vectorA, const CPeVector3& p_vectorB);

			/**
			 * @brief Accessor to m_x_coordinate.
			*/
			double getX() const;

			/**
			 * @brief Accessor to m_y_coordinate.
			*/
			double getY() const;

			/**
			 * @brief Accessor to m_z_coordinate.
			*/
			double getZ() const;

			/**
			 * @brief A simple print method. Meant for deggug.
			*/
			void printCoordinate() const;

			~CPeVector3()
			{
				delete m_x_coordinate;
				delete m_y_coordinate;
				delete m_z_coordinate;
			}
		};
	}
}

#endif /* CPEVECTOR3_CPEVECTOR3_H */