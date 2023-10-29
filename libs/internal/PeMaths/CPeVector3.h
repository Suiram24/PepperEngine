#ifndef CPEMATHS_CPEVECTOR3_H
#define CPEMATHS_CPEVECTOR3_H

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
			double m_x; 
			double m_y;
			double m_z;

			// Methods
		public:

			CPeVector3(double p_x, double p_y, double p_z) : 
				m_x(p_x),
				m_y(p_y),
				m_z(p_z)
			{
			}

			CPeVector3(const CPeVector3& p_vector) : 
				m_x(p_vector.GetX()),
				m_y(p_vector.GetY()),
				m_z(p_vector.GetZ())
			{
			}

			CPeVector3() :
				m_x(0),
				m_y(0),
				m_z(0)
			{
			}

			/**
			 * @brief Redefine the operator 'equal' to make a deep copy of an other CPeVector3.
			 * @param p_vector A CPeVector3 to copy.
			 * @return 'this'.
			*/
			CPeVector3& operator=(const CPeVector3& p_vector);

			/**
			 * @brief Define the operator 'plus' for two CPeVector3. None of the vectors are modified.
			 * @param p_vector A CPeVector3 to add with 'this'.
			 * @return  A new CPeVector3.
			*/
			CPeVector3 operator+(const CPeVector3& p_vector) const;

			/**
			 * @brief Redefine the operator '+=' to work on CPeVector3.
			 * @param p_vector A CPeVector3 to add to 'this'.
			 * @return 'this'.
			*/
			CPeVector3& operator+=(const CPeVector3& p_vector);

			/**
			 * @brief Define the operator 'minus' for two CPeVector3. None of the vectors are modified.
			 * @param p_vector A CPeVector3 to substract from 'this'.
			 * @return  A new CPeVector3.
			*/
			CPeVector3 operator-(const CPeVector3& p_vector) const;

			/**
			 * @brief Redefine the operator '-=' to work on CPeVector3.
			 * @param p_vector A CPeVector3 to substract from 'this'.
			 * @return 'this'.
			*/
			CPeVector3& operator-=(const CPeVector3& p_vector);

			/**
			 * @brief Define the operator 'multiplication' for a double and a CPeVector3. 'this' is not modified.
			 * @param p_scalar A double to multipliate 'this'
			 * @return  A new CPeVector3.
			*/
			CPeVector3 operator*(double p_scalar) const;

			/**
			 * @brief Compute the norm of the CPeVector3.
			 * @return A double.
			*/
			const double GetNorm() const;

			/**
			 * @brief Compute the normalize vector associated with 'this'.
			 * @return A new CPeVector3.
			*/
			CPeVector3 NormalizeVector() const;

			/**
			 * @brief Compute the scalar product (or dot product) between two CPeVector3.
			 * @param p_vectorA A CPeVector3.
			 * @param p_vectorB A CPeVector3.
			 * @return A double.
			*/
			static const double ScalarProduct(const CPeVector3& p_vectorA, const CPeVector3& p_vectorB)
			{
				return
					p_vectorA.GetX() * p_vectorB.GetX() +
					p_vectorA.GetY() * p_vectorB.GetY() +
					p_vectorA.GetZ() * p_vectorB.GetZ();
			}

			/**
			 * @brief Compute the vector product (or cross product) between to CPeVector3.
			 *
			 * @param p_vectorA A CPeVector3.
			 * @param p_vectorB A CPeVector3.
			 * @return A new CPeVector3.
			*/
			static CPeVector3 CrossProduct(const CPeVector3& p_vectorA, const CPeVector3& p_vectorB);

			/**
			 * @brief Compute the orthographic projection of vector A on vector B.
			 *
			 * @param p_vectorA A CPeVector3.
			 * @param p_vectorB A CPeVector3.
			 * @return A new CPeVector3.
			*/
			static CPeVector3 OrthographicProjection(const CPeVector3& p_vectorA, const CPeVector3& p_vectorB);

			/**
			 * @brief Accessor to m_x.
			*/
			double GetX() const;

			/**
			 * @brief Accessor to m_y.
			*/
			double GetY() const;

			/**
			 * @brief Accessor to m_z.
			*/
			double GetZ() const;

			void SetX(double p_x);
			void SetY(double p_y);
			void SetZ(double p_z);

			/**
			 * @brief Compute the distance to an other vector.
			 *
			 * @param p_vector A CPeVector3.
			 * @return Distance to p_vector.
			*/
			double DistanceTo(const CPeVector3& p_vector) const;

			/**
			 * @brief A simple print method. Meant for deggug.
			*/
			void PrintCoordinate() const;

			~CPeVector3()
			{

			}
		};
	}
}

#endif /* CPEMATHS_CPEVECTOR3_H */