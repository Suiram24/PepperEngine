#ifndef CPEMATHS_CPEMATRICE3_H
#define CPEMATHS_CPEMATRICE3_H

#include <vector>
#include <stdexcept>

#include "CPeVector3.h"


namespace engine
{
	namespace maths
	{
		/**
		 * @brief Class for a basic representation of a matrice 3x3.
		*/
		class CPeMatrix3
		{
			// Fields
		private:
			double m_matrice[9];

			// Methods
		public:

			CPeMatrix3(double p_vector[9])
			{
				m_matrice[0] = p_vector[0];
				m_matrice[1] = p_vector[1];
				m_matrice[2] = p_vector[2];
				m_matrice[3] = p_vector[3];
				m_matrice[4] = p_vector[4];
				m_matrice[5] = p_vector[5];
				m_matrice[6] = p_vector[6];
				m_matrice[7] = p_vector[7];
				m_matrice[8] = p_vector[8];
			}

			CPeMatrix3():
				m_matrice{0, 0, 0, 0, 0, 0, 0, 0, 0}
			{
			}

			static CPeMatrix3 Identity();
			
			CPeMatrix3(double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8)
			{
				m_matrice[0] = a0;
				m_matrice[1] = a1;
				m_matrice[2] = a2;
				m_matrice[3] = a3;
				m_matrice[4] = a4;
				m_matrice[5] = a5;
				m_matrice[6] = a6;
				m_matrice[7] = a7;
				m_matrice[8] = a8;
			}

			CPeMatrix3(const CPeMatrix3& p_matrice)
			{
				m_matrice[0] = p_matrice.Get(0, 0);
				m_matrice[1] = p_matrice.Get(0, 1);
				m_matrice[2] = p_matrice.Get(0, 2);

				m_matrice[3] = p_matrice.Get(1, 0);
				m_matrice[4] = p_matrice.Get(1, 1);
				m_matrice[5] = p_matrice.Get(1, 2);

				m_matrice[6] = p_matrice.Get(2, 0);
				m_matrice[7] = p_matrice.Get(2, 1);
				m_matrice[8] = p_matrice.Get(2, 2);
			}
			
			/**
			 * @brief Change the value at (p_i,p_j).
			 * @param p_i row indice (should be less than 3).
			 * @param p_j column indice (should be less than 3).
			 * @param p_value new value.
			*/
			void Set(unsigned int p_i, unsigned int p_j, double p_value);

			/**
			 * @brief Get the value at (p_i,p_j).
			 * @param p_i row indice (should be less than 3).
			 * @param p_j column indice (should be less than 3).
			 * @return the value at (p_i,p_j).
			*/
			double Get(unsigned int p_i, unsigned int p_j) const;

			/**
			 * @brief Define the operator 'multiplication' for two CPeMatrix3.
			 * @param p_matrice A CPeMatrix3 to multiply 'this'.
			 * @return  A new CPeMatrix3.
			*/
			CPeMatrix3 operator*(const CPeMatrix3& p_matrice) const;

		
			
			/**
			 * @brief Define the operator 'addition' for two CPeMatrix3.
			 * @param p_matrice A CPeMatrix3 to add with 'this'.
			 * @return  A new CPeMatrix3.
			*/
			CPeMatrix3 operator+(const CPeMatrix3& p_matrice) const;

			/**
			* @brief Define the operator 'minus' for two CPeMatrix3.
			* @param p_matrice A CPeMatrix3 to subtract to 'this'.
			* @return  A new CPeMatrix3.
			*/
			CPeMatrix3 operator-(const CPeMatrix3& p_matrice) const;

			/**
			* @brief Define the operator 'asign' between CPeMatrix3.
			* @param p_matrice A CPeMatrix3 to copy to 'this'.
			*/
			void operator=(const CPeMatrix3& p_matrice);

			/**
			 * @brief Get the transpose matrix.
			 * @return A new transpose CPeMatrix3.
			*/
			CPeMatrix3 Transpose() const;

			/**
			 * @brief Compute the determinant of the matrix.
			 * @return The CPeMatrix3's determinant.
			*/
			double Determinant() const;

			/**
			 * @brief Evaluate if the matrix is inversible.
			 * @return whether the matrix is inversible or not.
			*/
			bool IsInversible() const;

			/**
			 * @brief Get the inverse matrix. An exception is raised if the matrix is not inversible.
			 * @return A new inverse CPeMatrix3.
			*/
			CPeMatrix3 Inverse() const;

			/**
			* @brief Print the CPeMatrix3.
			*/
			void printMatrice() const;

			/**
			* @brief Define the operator 'multiplication' for CPeVector and CPeMatrix3.
			* @param p_vector A CPeVector3 to multiply the CPeMatrix3.
			* @return  A new CPeVector3.
			*/
			CPeVector3 operator*(const CPeVector3& p_vector) const;

			/**
			 * @brief Define the operator 'multiplication' for double and CPeMatrix3.
			 * @param p_vector A CPeVector3 to multiply the CPeMatrix3.
			 * @param p_matrice A CPeMatrix3 to be multiplied.
			 * @return  A new CPeMatrix3.
			*/
			CPeMatrix3 operator*(double p_number) const;
		};

		
	}
}

#endif /* CPEMATHS_CPEMATRICE3_H */