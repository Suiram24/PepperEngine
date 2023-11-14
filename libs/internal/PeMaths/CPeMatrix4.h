#ifndef CPEMATHS_CPEMATRICE4_H
#define CPEMATHS_CPEMATRICE4_H

#include <vector>
#include <stdexcept>

#include "CPeVector3.h"
#include "CPeMatrix3.h"

namespace engine
{
	namespace maths
	{
		/**
		*@brief Class for a basic representation of a matrice 4x4.
		*/
		class CPeMatrix4
		{
			// Fields
		private:
			CPeMatrix3 m_matrice;
			double m_translation[3];
			// Methods
		public:

			CPeMatrix4(double p_vector[12]) 
				: m_matrice(p_vector[0], p_vector[1], p_vector[2], p_vector[3], p_vector[4], p_vector[5], p_vector[6], p_vector[7], p_vector[8])
			{
				m_translation[0] = p_vector[9];
				m_translation[1] = p_vector[10];
				m_translation[2] = p_vector[11];
			}

			CPeMatrix4()
				: m_matrice(CPeMatrix3())
			{
			}

			CPeMatrix4(const CPeMatrix3& p_matrice, double p_translation[3])
				: m_matrice(p_matrice)
			{
				m_translation[0] = p_translation[0];
				m_translation[1] = p_translation[1];
				m_translation[2] = p_translation[2];
			}

			CPeMatrix4(const CPeMatrix3& p_matrice, CPeVector3& p_translation)
				: m_matrice(p_matrice)
			{
				m_translation[0] = p_translation.GetX();
				m_translation[1] = p_translation.GetY();
				m_translation[2] = p_translation.GetZ();
			}

			CPeMatrix4(double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9, double a10, double a11)
				: m_matrice(a0, a1, a2, a3, a4, a5, a6, a7, a8)
			{
				m_translation[0] = a9;
				m_translation[1] = a10;
				m_translation[2] = a11;
			}

			CPeMatrix4(const CPeMatrix4& p_matrice)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)

					{
						m_matrice.Set(i, j, p_matrice.Get(i, j));
					}
				}
        
				m_translation[0] = p_matrice.Get(0, 3);
				m_translation[1] = p_matrice.Get(1, 3);
				m_translation[2] = p_matrice.Get(2, 3);

			}

			/**
			 * @brief Change the value at (p_i,p_j).
			 * @param p_i row indice (should be less than 3).
			 * @param p_j column indice (should be less than 4).
			 * @param p_value new value.
			*/
			void Set(unsigned int p_i, unsigned int p_j, double p_value);

			/**
			 * @brief Get the value at (p_i,p_j).
			 * @param p_i row indice (should be less than 3).
			 * @param p_j column indice (should be less than 4).
			 * @return the value at (p_i,p_j).
			*/
			double Get(unsigned int p_i, unsigned int p_j) const;

			/**
			 * @brief Define the operator 'multiplication' for two CPeMatrix4.
			 * @param p_matrice A CPeMatrix4 to multiply 'this'.
			 * @return  A new CPeMatrix4.
			*/
			CPeMatrix4 operator*(const CPeMatrix4& p_matrice) const;



			/**
			 * @brief Define the operator 'addition' for two CPeMatrix4.
			 * @param p_matrice A CPeMatrix4 to add with 'this'.
			 * @return  A new CPeMatrix4.
			*/
			CPeMatrix4 operator+(const CPeMatrix4& p_matrice) const;

			/**
			* @brief Define the operator 'minus' for two CPeMatrix4.
			* @param p_matrice A CPeMatrix4 to subtract to 'this'.
			* @return  A new CPeMatrix4.
			*/
			CPeMatrix4 operator-(const CPeMatrix4& p_matrice) const;

			/**
			* @brief Define the operator 'asign' between CPeMatrix4.
			* @param p_matrice A CPeMatrix4 to copy to 'this'.
			*/
			void operator=(const CPeMatrix4& p_matrice);

			/**
			 * @brief Evaluate if the matrix is inversible.
			 * @return whether the matrix is inversible or not.
			*/
			bool IsInversible() const;

			/**
			 * @brief Get the inverse matrix. An exception is raised if the matrix is not inversible.
			 * @return A new inverse CPeMatrix4.
			*/
			CPeMatrix4 Inverse() const;

			/**
			* @brief Print the CPeMatrix4.
			*/
			void printMatrice() const;

			/**
			* @brief Define the operator 'multiplication' for CPeVector and CPeMatrix4.
			* @param p_vector A CPeVector3 to multiply the CPeMatrix4.
			* @return  A new CPeVector3.
			*/
			CPeVector3 operator*(const CPeVector3& p_vector) const;

			CPeMatrix3 ToMatrix3() const;

		};



	}
}

#endif /* CPEMATHS_CPEMATRICE4_H */