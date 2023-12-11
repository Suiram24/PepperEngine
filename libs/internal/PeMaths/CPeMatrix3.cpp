#include <cstdio>

#include "CPeMatrix3.h"


namespace engine {
	namespace maths {

		CPeMatrix3 CPeMatrix3::Identity() {
			return CPeMatrix3(
				1.0f, 0, 0,
				0, 1.0f, 0,
				0, 0, 1.0f
			);
		}
		
		void CPeMatrix3::Set(unsigned int p_i, unsigned int p_j, double p_value)
		{
			if (p_i > 2 || p_j > 2)
			{
				throw std::invalid_argument("You cannot set values outside of the 3x3 matrice.");
			}
			m_matrice[p_i * 3 + p_j] = p_value;
		}

		double CPeMatrix3::Get(unsigned int p_i, unsigned int p_j) const
		{
			if (p_i > 2 || p_j > 2)
			{
				throw std::invalid_argument("You cannot get values outside of the 3x3 matrice.");
			}
			return m_matrice[p_i * 3 + p_j];
		}

		CPeMatrix3 CPeMatrix3::operator*(const CPeMatrix3& p_matrice) const
		{
			CPeMatrix3 multMatrice = CPeMatrix3();
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					double sum = 0;
					for (int k = 0; k < 3; k++)
					{
						sum += this->m_matrice[i * 3 + k] * p_matrice.Get(k, j);
					}
					multMatrice.Set(i, j, sum);
				}
			}
			return multMatrice;
		}

		CPeMatrix3 CPeMatrix3::operator+(const CPeMatrix3& p_matrice) const
		{
			CPeMatrix3 addMatrice = CPeMatrix3();
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					addMatrice.Set(i, j, this->m_matrice[i * 3 + j] + p_matrice.Get(i, j));
				}
			}
			return addMatrice;
		}

		CPeMatrix3 CPeMatrix3::operator-(const CPeMatrix3& p_matrice) const
		{
			CPeMatrix3 subMatrice = CPeMatrix3();
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					subMatrice.Set(i, j, this->m_matrice[i * 3 + j] - p_matrice.Get(i, j));
				}
			}
			return subMatrice;
		}

		void CPeMatrix3::operator=(const CPeMatrix3& p_matrice)
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

		CPeMatrix3 CPeMatrix3::Transpose() const
		{
			CPeMatrix3 transposeMatrice = CPeMatrix3();
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					transposeMatrice.Set(i, j, this->m_matrice[j * 3 + i]);
				}
			}
			
			return transposeMatrice;
		}

		double CPeMatrix3::Determinant() const
		{
			/*
				    ( a b c )
				M =	( d e f )
					( g h i )
			*/
			double det =
				  m_matrice[0] * m_matrice[4] * m_matrice[8] //aei
				+ m_matrice[3] * m_matrice[7] * m_matrice[2] //dhc
				+ m_matrice[6] * m_matrice[1] * m_matrice[5] //gbf
				- m_matrice[0] * m_matrice[7] * m_matrice[5] //ahf
				- m_matrice[6] * m_matrice[4] * m_matrice[2] //gec
				- m_matrice[3] * m_matrice[1] * m_matrice[8];//dbi
			return det;
		}

		bool CPeMatrix3::IsInversible() const
		{
			double det = abs(Determinant());
			return (det > 1e-12); //to prevent double imprecision
		}

		CPeMatrix3 CPeMatrix3::Inverse() const
		{
			if (!IsInversible())
			{
				throw std::invalid_argument("You cannot inverse a matrice of determinant 0.");
			}

			CPeMatrix3 inverseMatrice = CPeMatrix3();

			double det = Determinant();

			/*
					( a b c )
				M =	( d e f )
					( g h i )
			*/

			inverseMatrice.Set(0, 0, m_matrice[4] * m_matrice[8] - m_matrice[5] * m_matrice[7]); //ei - fh
			inverseMatrice.Set(0, 1, m_matrice[2] * m_matrice[7] - m_matrice[1] * m_matrice[8]); //ch - bi
			inverseMatrice.Set(0, 2, m_matrice[1] * m_matrice[5] - m_matrice[2] * m_matrice[4]); //bf - ce

			inverseMatrice.Set(1, 0, m_matrice[5] * m_matrice[6] - m_matrice[3] * m_matrice[8]); //fg - di
			inverseMatrice.Set(1, 1, m_matrice[0] * m_matrice[8] - m_matrice[2] * m_matrice[6]); //ai - cg
			inverseMatrice.Set(1, 2, m_matrice[2] * m_matrice[3] - m_matrice[0] * m_matrice[5]); //cd - af

			inverseMatrice.Set(2, 0, m_matrice[3] * m_matrice[7] - m_matrice[4] * m_matrice[6]); //dh - eg
			inverseMatrice.Set(2, 1, m_matrice[1] * m_matrice[6] - m_matrice[0] * m_matrice[7]); //bg - ah
			inverseMatrice.Set(2, 2, m_matrice[0] * m_matrice[4] - m_matrice[1] * m_matrice[3]); //ae - bd


			return inverseMatrice * (1/det);
		}

		void CPeMatrix3::printMatrice() const
		{
			std::printf("	| %lf %lf %lf |\n	| %lf %lf %lf |\n	| %lf %lf %lf |\n\n",
				m_matrice[0],m_matrice[1],m_matrice[2],
				m_matrice[3],m_matrice[4],m_matrice[5],
				m_matrice[6],m_matrice[7],m_matrice[8]
			);
		}

		CPeVector3 CPeMatrix3::operator*(const CPeVector3& p_vector) const
		{
			CPeVector3 mult= CPeVector3(
				p_vector.GetX() * this->Get(0, 0) + p_vector.GetY() * this->Get(0, 1) + p_vector.GetZ() * this->Get(0, 2),
				p_vector.GetX() * this->Get(1, 0) + p_vector.GetY() * this->Get(1, 1) + p_vector.GetZ() * this->Get(1, 2),
				p_vector.GetX() * this->Get(2, 0) + p_vector.GetY() * this->Get(2, 1) + p_vector.GetZ() * this->Get(2, 2)
			);
			return mult;
		}

		CPeMatrix3 CPeMatrix3::operator*(double p_number) const
		{
			CPeMatrix3 multMatrice = CPeMatrix3(
				p_number * this->Get(0, 0), p_number * this->Get(0, 1), p_number * this->Get(0, 2),
				p_number * this->Get(1, 0), p_number * this->Get(1, 1), p_number * this->Get(1, 2),
				p_number * this->Get(2, 0), p_number * this->Get(2, 1), p_number * this->Get(2, 2)
			);
			return multMatrice;
		}

		CPeVector3 CPeMatrix3::GetAxis1() const
		{
			CPeVector3 axis = CPeVector3(Get(0, 0), Get(1, 0), Get(2, 0));
			return axis;
		}

		CPeVector3 CPeMatrix3::GetAxis2() const
		{
			CPeVector3 axis = CPeVector3(Get(0, 1), Get(1, 1), Get(2, 1));
			return axis;
		}

		CPeVector3 CPeMatrix3::GetAxis3() const
		{
			CPeVector3 axis = CPeVector3(Get(0, 2), Get(1, 2), Get(2, 2));
			return axis;
		}

	}
}