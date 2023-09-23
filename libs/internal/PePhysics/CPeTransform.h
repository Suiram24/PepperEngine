#ifndef CPETRANSFORM_CPETRANSFORM_H
#define CPETRANSFORM_CPETRANSFORM_H

#include "../PeMaths/PeMaths.h"

namespace pemaths = engine::maths;

namespace engine {
	namespace physics {
		/**
		 * @brief A class for basic components regarding the physics of a 3D elements.
		*/
		class CPeTransform
		{
			//Fields
		private:
			pemaths::CPeVector3& m_position;

			pemaths::CPeVector3& m_orientation;

			pemaths::CPeVector3& m_size;

			//Methods
		public:
			CPeTransform(pemaths::CPeVector3& p_position, pemaths::CPeVector3& p_orientation, pemaths::CPeVector3& p_size) :
				m_position(p_position),
				m_orientation(p_orientation),
				m_size(p_size)
			{
			}

			CPeTransform(pemaths::CPeVector3& p_position) :
				m_position(p_position),
				m_orientation(pemaths::CPeVector3(0., 0., 0.)),
				m_size(pemaths::CPeVector3(1., 1., 1.))
			{
			}

			/**
			 * @brief Accessor for m_position.
			 * @return m_position.
			*/
			const pemaths::CPeVector3& GetPosition() const;

			/**
			 * @brief Accessor for m_orientation.
			 * @return m_orientation.
			*/
			const pemaths::CPeVector3& GetOrientation() const;
			
			/**
			 * @brief Accessor for m_size.
			 * @return m_size.
			*/
			const pemaths::CPeVector3& GetSize() const;

			/**
			 * @brief Setter for m_position.
			 * @param The new position.
			*/
			void SetPosition(pemaths::CPeVector3& p_position);

			/**
			 * @brief Setter for m_orientation.
			 * @param The new orientation.
			*/
			void SetOrientation(pemaths::CPeVector3& p_orientation);

			/**
			 * @brief Setter for m_size.
			 * @param The new size.
			*/
			void SetSize(pemaths::CPeVector3& p_size);

		};
	}
}

#endif /* CPETRANSFORM_CPETRANSFORM_H */