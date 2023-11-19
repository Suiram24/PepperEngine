#include <cstdio>

#include "CPeMatrix4.h"


namespace engine {
	namespace maths {

		void CPeMatrix4::Set(unsigned int p_i, unsigned int p_j, double p_value)
		{
			if (p_i > 2 || p_j > 3)
			{
				throw std::invalid_argument("You cannot set values outside of the 3x4 matrice.");
			}
 
			if (p_j == 3)
			{
				m_translation[p_i] = p_value;
			}
			else
			{
				m_matrice.Set(p_i, p_j, p_value);
			}
			
		}

		double CPeMatrix4::Get(unsigned int p_i, unsigned int p_j) const
		{
			if (p_i > 3 || p_j > 3)
			{
				throw std::invalid_argument("You cannot get values outside of the 4x4 matrice.");
			}

			if (p_i == 3)//Hardcoded last line of the model matrix to save memory
			{
				if (p_j == 3)
				{
					return 1.0;
				}
				else
				{
					return .0;
				}
			}
			else if (p_j == 3)
			{
				return m_translation[p_i];
			}
			else
			{
				return m_matrice.Get(p_i, p_j);
			}
			
		}

		CPeMatrix4 CPeMatrix4::operator*(const CPeMatrix4& p_matrice) const
		{
			CPeMatrix4 multMatrice = CPeMatrix4();
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					double sum = 0;
					for (int k = 0; k < 3; k++)
					{
						sum += this->Get(i, k) * p_matrice.Get(k, j);
					}
					multMatrice.Set(i, j, sum);
				}

				double tmp = 0;
				for (int l = 0; l < 4; l++)
				{
					tmp += this->Get(i, l) * p_matrice.Get(l, 3);
				}
				multMatrice.Set(i, 3, tmp);
			}
			return multMatrice;
		}

		CPeMatrix4 CPeMatrix4::operator+(const CPeMatrix4& p_matrice) const
		{
			CPeMatrix4 addMatrice = CPeMatrix4();
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					addMatrice.Set(i, j, this->m_matrice.Get(i,j) + p_matrice.Get(i, j));
				}
			}
			return addMatrice;
		}

		CPeMatrix4 CPeMatrix4::operator-(const CPeMatrix4& p_matrice) const
		{
			CPeMatrix4 subMatrice = CPeMatrix4();
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					subMatrice.Set(i, j, this->m_matrice.Get(i, j) - p_matrice.Get(i, j));
				}
			}
			return subMatrice;
		}

		void CPeMatrix4::operator=(const CPeMatrix4& p_matrice)
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

		bool CPeMatrix4::IsInversible() const
		{
			return m_matrice.IsInversible();
		}

		CPeMatrix4 CPeMatrix4::Inverse() const
		{
			if (!IsInversible())
			{
				throw std::invalid_argument("You cannot inverse a matrice of determinant 0.");
			}

			double minusV[3] = { -m_translation[0], -m_translation[1] , -m_translation[2] };

			CPeMatrix4 inverseMatrice = CPeMatrix4(m_matrice.Inverse(), minusV);
			return inverseMatrice;
		}

		void CPeMatrix4::printMatrice() const
		{
			std::printf("	| %lf %lf %lf %lf |\n	| %lf %lf %lf %lf |\n	| %lf %lf %lf %lf |\n\n",
				m_matrice.Get(0,0), m_matrice.Get(0,1), m_matrice.Get(0,2), m_matrice.Get(0,3),
				m_matrice.Get(1,0), m_matrice.Get(1,1), m_matrice.Get(1,2), m_matrice.Get(1,3),
				m_matrice.Get(2,0), m_matrice.Get(2,1), m_matrice.Get(2,2), m_matrice.Get(2,3)
			);
		}

		CPeVector3 CPeMatrix4::operator*(const CPeVector3& p_vector) const
		{
			CPeVector3 mult = CPeVector3(
				p_vector.GetX() * Get(0, 0) + p_vector.GetY() * Get(0, 1) + p_vector.GetZ() * Get(0, 2) + Get(0,3),
				p_vector.GetX() * Get(1, 0) + p_vector.GetY() * Get(1, 1) + p_vector.GetZ() * Get(1, 2) + Get(1,3),
				p_vector.GetX() * Get(2, 0) + p_vector.GetY() * Get(2, 1) + p_vector.GetZ() * Get(2, 2) + Get(2,3)
			);
			return mult;
		}

		CPeMatrix3 CPeMatrix4::ToMatrix3() const
		{
			CPeMatrix3 mat = CPeMatrix3(
				Get(0, 0), Get(0, 1), Get(0, 2),
				Get(1, 0), Get(1, 1), Get(1, 2),
				Get(2, 0), Get(2, 1), Get(2, 2)
			);
			return mat;
		}

	}
}