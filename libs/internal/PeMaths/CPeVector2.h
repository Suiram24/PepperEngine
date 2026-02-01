#ifndef CPEMATHS_CPEVECTOR2_H
#define CPEMATHS_CPEVECTOR2_H

namespace engine
{
	namespace maths
	{
		class CPeVector3;
		/**
		 * @brief Class for a basic representation of a 3D vector.
		*/
		class CPeVector2
		{
			// Fields
		private:
			double m_x; 
			double m_y;

			// Methods
		public:

			CPeVector2(double p_x, double p_y) : 
				m_x(p_x),
				m_y(p_y)
			{
			}

			CPeVector2(const CPeVector2& p_vector) :
				m_x(p_vector.GetX()),
				m_y(p_vector.GetY())
			{
			}
			
			CPeVector2(const CPeVector3& p_vector);

			CPeVector2() :
				m_x(0),
				m_y(0)
			{
			}

			/**
			 * @brief Redefine the operator 'equal' to make a deep copy of an other CPeVector2.
			 * @param p_vector A CPeVector2 to copy.
			 * @return 'this'.
			*/
			CPeVector2& operator=(const CPeVector2& p_vector);

			/**
			 * @brief Define the operator 'plus' for two CPeVector2. None of the vectors are modified.
			 * @param p_vector A CPeVector2 to add with 'this'.
			 * @return  A new CPeVector2.
			*/
			CPeVector2 operator+(const CPeVector2& p_vector) const;

			/**
			 * @brief Redefine the operator '+=' to work on CPeVector2.
			 * @param p_vector A CPeVector2 to add to 'this'.
			 * @return 'this'.
			*/
			CPeVector2& operator+=(const CPeVector2& p_vector);

			/**
			 * @brief Define the operator 'minus' for two CPeVector2. None of the vectors are modified.
			 * @param p_vector A CPeVector2 to substract from 'this'.
			 * @return  A new CPeVector2.
			*/
			CPeVector2 operator-(const CPeVector2& p_vector) const;

			/**
			 * @brief Redefine the operator '-=' to work on CPeVector2.
			 * @param p_vector A CPeVector2 to substract from 'this'.
			 * @return 'this'.
			*/
			CPeVector2& operator-=(const CPeVector2& p_vector);

			/**
			 * @brief Define the operator 'multiplication' for a double and a CPeVector2. 'this' is not modified.
			 * @param p_scalar A double to multipliate 'this'
			 * @return  A new CPeVector2.
			*/
			CPeVector2 operator*(double p_scalar) const;

			/**
			 * @brief Compute the norm of the CPeVector2.
			 * @return A double.
			*/
			const double GetNorm() const;

			/**
			 * @brief Compute the squared norm of the CPeVector2.
			 * @return A double.
			*/
			const double GetSquaredNorm() const;

			/**
			 * @brief Compute the normalize vector associated with 'this'.
			 * @return A new CPeVector2.
			*/
			CPeVector2 NormalizeVector() const;

			/**
			 * @brief Compute the scalar product (or dot product) between two CPeVector2.
			 * @param p_vectorA A CPeVector2.
			 * @param p_vectorB A CPeVector2.
			 * @return A double.
			*/
			static const double ScalarProduct(const CPeVector2& p_vectorA, const CPeVector2& p_vectorB)
			{
				return
					p_vectorA.GetX() * p_vectorB.GetX() +
					p_vectorA.GetY() * p_vectorB.GetY();
			}

			/**
			 * @brief Compute the vector product (or cross product) between to CPeVector2.
			 *
			 * @param p_vectorA A CPeVector2.
			 * @param p_vectorB A CPeVector2.
			 * @return A new CPeVector2.
			*/
			static CPeVector2 CrossProduct(const CPeVector2& p_vectorA, const CPeVector2& p_vectorB);

			/**
			 * @brief Compute the orthographic projection of vector A on vector B.
			 *
			 * @param p_vectorA A CPeVector2.
			 * @param p_vectorB A CPeVector2.
			 * @return A new CPeVector2.
			*/
			static CPeVector2 OrthographicProjection(const CPeVector2& p_vectorA, const CPeVector2& p_vectorB);

			/**
			 * @brief Accessor to m_x.
			*/
			double GetX() const;

			/**
			 * @brief Accessor to m_y.
			*/
			double GetY() const;


			/**
			 * @brief Accessor to axes indentified by p_indice.
			*/
			double Get(int p_indice) const;


			/**
			 * @brief Setter for m_x.
			*/
			void SetX(double p_x);

			/**
			 * @brief Setter for m_y.
			*/
			void SetY(double p_y);

			/**
			 * @brief Setter for any m_x/m_y (0/1 indices).
			*/
			void Set(int p_indice, double p_value);

			/**
			 * @brief Compute the distance to an other vector.
			 *
			 * @param p_vector A CPeVector2.
			 * @return Distance to p_vector.
			*/
			double DistanceTo(const CPeVector2& p_vector) const;

			/**
			 * @brief Compute the distance to an other vector.
			 *
			 * @param p_vector A CPeVector2.
			 * @return Distance to p_vector.
			*/
			double SquaredDistanceTo(const CPeVector2& p_vector) const;

			void RotateSelfAroundZAxis(double p_angle);

			/**
			 * @brief A simple print method. Meant for deggug.
			*/
			void PrintCoordinate() const;

			~CPeVector2()
			{

			}
		};

		/**
		 * @brief Define the operator 'multiplication' for a double and a CPeVector2.
		 * 
		 * @param p_scalar A double to multipliate by the vector
		 * @param vector CPeVector2& to duplicate with the scalar
		 * @return CPeVector2 - Result of the multiplication
		 */
		CPeVector2 operator*(double p_scalar, const CPeVector2& vector);
	}
}

#endif /* CPEMATHS_CPEVECTOR3_H */