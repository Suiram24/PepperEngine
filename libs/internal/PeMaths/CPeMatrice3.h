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
		class CPeMatrice3
		{
			// Fields
		private:
			std::vector<double> m_matrice;

			const std::vector<double> m_identity{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

			// Methods
		public:

			CPeMatrice3(std::vector<double> p_vector)
			{
				if (p_vector.size() != 9)
				{
					throw std::invalid_argument("CPeMatrice3 can only be instanciate with a vector of size 9.");
				}
				m_matrice = p_vector;
			}

			CPeMatrice3() :
				m_matrice(std::vector<double>(9))
			{
			}
			
			CPeMatrice3(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9)
			{
				m_matrice = std::vector<double>{ a1, a2, a3, a4, a5, a6, a7, a8, a9 };
			}

			CPeMatrice3(const CPeMatrice3& p_matrice) :
				m_matrice(std::vector<double>(9))
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
			 * @brief Define the operator 'multiplication' for two CPeMatrice3.
			 * @param p_matrice A CPeMatrice3 to multiply 'this'.
			 * @return  A new CPeMatrice3.
			*/
			CPeMatrice3 operator*(const CPeMatrice3& p_matrice) const;

		
			
			/**
			 * @brief Define the operator 'addition' for two CPeMatrice3.
			 * @param p_matrice A CPeMatrice3 to add with 'this'.
			 * @return  A new CPeMatrice3.
			*/
			CPeMatrice3 operator+(const CPeMatrice3& p_matrice) const;

			/**
			* @brief Define the operator 'minus' for two CPeMatrice3.
			* @param p_matrice A CPeMatrice3 to subtract to 'this'.
			* @return  A new CPeMatrice3.
			*/
			CPeMatrice3 operator-(const CPeMatrice3& p_matrice) const;

			/**
			* @brief Define the operator 'asign' between CPeMatrice3.
			* @param p_matrice A CPeMatrice3 to copy to 'this'.
			*/
			void operator=(const CPeMatrice3& p_matrice);

			/**
			 * @brief Get the transpose matrix.
			 * @return A new transpose CPeMatrice3.
			*/
			CPeMatrice3 Transpose() const;

			/**
			 * @brief Compute the determinant of the matrix.
			 * @return The CPeMatrice3's determinant.
			*/
			double Determinant() const;

			/**
			 * @brief Evaluate if the matrix is inversible.
			 * @return whether the matrix is inversible or not.
			*/
			bool IsInversible() const;

			/**
			 * @brief Get the inverse matrix. An exception is raised if the matrix is not inversible.
			 * @return A new inverse CPeMatrice3.
			*/
			CPeMatrice3 Inverse() const;

			/**
			* @brief Print the CPeMatrice3.
			*/
			void printMatrice() const;

			/**
			* @brief Define the operator 'multiplication' for CPeVector and CPeMatrice3.
			* @param p_vector A CPeVector3 to multiply the CPeMatrice3.
			* @return  A new CPeMatrice3.
			*/
			CPeMatrice3 operator*(const CPeVector3& p_vector) const;

			/**
			 * @brief Define the operator 'multiplication' for double and CPeMatrice3.
			 * @param p_vector A CPeVector3 to multiply the CPeMatrice3.
			 * @param p_matrice A CPeMatrice3 to be multiplied.
			 * @return  A new CPeMatrice3.
			*/
			CPeMatrice3 operator*(double p_number) const;
		};

		
	}
}

#endif /* CPEMATHS_CPEMATRICE3_H */