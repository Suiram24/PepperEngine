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
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 4; j++)
				{
					double sum = 0;
					for (size_t k = 0; k < 4; k++)
					{
						sum += this->Get(i, k) * p_matrice.Get(k, j);
					}
					multMatrice.Set(i, j, sum);
				}
			}

			//CPeMatrix4 multMatrice2 = CPeMatrix4();
			//for (int i = 0; i < 3; i++)
			//{
			//	for (int j = 0; j < 3; j++)
			//	{
			//		double sum = 0;
			//		for (int k = 0; k < 3; k++)
			//		{
			//			sum += this->Get(i, k) * p_matrice.Get(k, j);
			//		}
			//		multMatrice2.Set(i, j, sum);
			//	}

			//	double tmp = 0;
			//	for (int l = 0; l < 4; l++)
			//	{
			//		tmp += this->Get(i, l) * p_matrice.Get(l, 3);
			//	}
			//	multMatrice2.Set(i, 3, tmp);
			//}
			return multMatrice;
		}

		CPeMatrix4 CPeMatrix4::operator*(double p_scalar) const
		{
			CPeMatrix4 multMatrice = CPeMatrix4();
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 4; j++)
				{
					multMatrice.Set(i, j, this->Get(i, j) * p_scalar);
				}
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

			double a = m_matrice.Get(0,0);
			double b = m_matrice.Get(0,1);
			double c = m_matrice.Get(0,2);
			double d = m_matrice.Get(1,0);
			double e = m_matrice.Get(1,1);
			double f = m_matrice.Get(1,2);
			double g = m_matrice.Get(2,0);
			double h = m_matrice.Get(2,1);
			double i = m_matrice.Get(2,2);
			double x = m_translation[0];
			double y = m_translation[1];
			double z = m_translation[2];

			double det = m_matrice.Determinant();

			minusV[0] = ((-b) * f * z + b * i * y + c * e * z - c * h * y - e * i * x + f * h * x) / ( det);
			minusV[1] = (a * f * z - a * i * y +c * d * z - c * g * y + d * i * x - f * g * x) / (det);
			minusV[2] = ((-a) *e*z + a*h*y + b*d*z - b*g*y - d*h*x + e*g*x) / (det);


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

		bool CPeMatrix4::operator!=(const CPeMatrix4& p_matrix) const
		{
			return (m_translation[0] != p_matrix.m_translation[0]) || (m_translation[1] != p_matrix.m_translation[1]) || (m_translation[2] != p_matrix.m_translation[2]) || (m_matrice != p_matrix.m_matrice);
		}

		bool CPeMatrix4::operator==(const CPeMatrix4& p_matrix) const
		{
			return !(*this != p_matrix);
		}


		CPeMatrix3 CPeMatrix4::ToMatrix3() const
		{
			//CPeMatrix3 mat = m_matrice;
			return m_matrice;
		}

	}
}