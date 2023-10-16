#ifndef CPEMATHS_CPETRANSFORM_H
#define CPEMATHS_CPETRANSFORM_H

#include "CPeVector3.h"

namespace engine {
	namespace maths {
		/**
		 * @brief A class for basic components regarding the physics of a 3D elements.
		*/
		class CPeTransform
		{
			//Fields
		private:
			CPeVector3 m_position;

			CPeVector3 m_orientation;

			CPeVector3 m_size;

			//Methods
		public:
			CPeTransform(const CPeVector3& p_position, const CPeVector3& p_orientation, const CPeVector3& p_size) :
				m_position(p_position),
				m_orientation(p_orientation),
				m_size(p_size)
			{
			}

			CPeTransform(const CPeVector3& p_position) :
				m_position(p_position),
				m_orientation(CPeVector3(0., 0., 0.)),
				m_size(CPeVector3(1., 1., 1.))
			{
			}

			CPeTransform(double p_x, double p_y, double p_z) :
				m_position(CPeVector3(p_x, p_y, p_z)),
				m_orientation(CPeVector3(0., 0., 0.)),
				m_size(CPeVector3(1., 1., 1.))
			{
			}

			CPeTransform() :
				m_position(CPeVector3(0., 0., 0.)),
				m_orientation(CPeVector3(0., 0., 0.)),
				m_size(CPeVector3(1., 1., 1.))
			{
			}

			/**
			 * @brief Accessor for m_position.
			 * @return m_position.
			*/
			const CPeVector3& GetPosition() const;

			/**
			 * @brief Accessor for m_orientation.
			 * @return m_orientation.
			*/
			const CPeVector3& GetOrientation() const;
			
			/**
			 * @brief Accessor for m_size.
			 * @return m_size.
			*/
			const CPeVector3& GetSize() const;

			/**
			 * @brief Setter for m_position.
			 * @param The new position.
			*/
			void SetPosition(const CPeVector3& p_position);

			/**
			 * @brief Setter for m_orientation.
			 * @param The new orientation.
			*/
			void SetOrientation(const CPeVector3& p_orientation);

			/**
			 * @brief Setter for m_size.
			 * @param The new size.
			*/
			void SetSize(const CPeVector3& p_size);

		};
	}
}

#endif /* CPEMATHS_CPETRANSFORM_H */