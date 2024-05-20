#ifndef CPEMATHS_CPETRANSFORM_H
#define CPEMATHS_CPETRANSFORM_H

#include "CPeVector3.h"
#include "CPeQuaternion.h"
#include "CPeMatrix4.h"

namespace engine {
	namespace maths {
		/**
		 * @brief A class that allow to position, rotate and scale objects in a 3D space
		*/
		class CPeTransform
		{
			//Fields
		private:
			CPeVector3 m_position;

			CPeQuaternion m_orientation;

			//The transform matrix (4*4), it is computed every time the transform is modified, to avoid computations every times it it read.
			//Changing this does not update the position, rotation or size, so this should always be used as read only.
			CPeMatrix4 m_transformMatrix; 

			CPeVector3 m_size;

			//Methods
		public:
			CPeTransform(
				const CPeVector3& p_position,
				const CPeQuaternion& p_orientation,
				const CPeVector3& p_size
			) :
				m_position(p_position),
				m_orientation(p_orientation),
				m_transformMatrix(1,0,0,0,1,0,0,0,1,0,0,0),
				m_size(p_size)
			{
				UpdateTransformMatrix();
			}

			CPeTransform(const CPeVector3& p_position) :
				m_position(p_position),
				m_orientation(CPeQuaternion(1,0,0,0)),
				m_transformMatrix(1,0,0,0,1,0,0,0,1,0,0,0),
				m_size(CPeVector3(1., 1., 1.))
			{
				UpdateTransformMatrix();
			}

			CPeTransform(double p_x, double p_y, double p_z) :
				m_position(CPeVector3(p_x, p_y, p_z)),
				m_orientation(CPeQuaternion(1,0,0,0)),
				m_transformMatrix(1,0,0,0,1,0,0,0,1,0,0,0),
				m_size(CPeVector3(1., 1., 1.))
			{
				UpdateTransformMatrix();
			}

			CPeTransform() :
				m_position(CPeVector3(0., 0., 0.)),
				m_orientation(CPeQuaternion(1,0,0,0)),
				m_transformMatrix(1,0,0,0,1,0,0,0,1,0,0,0),
				m_size(CPeVector3(1., 1., 1.))
			{
				UpdateTransformMatrix();
			}

			/**
			 * @brief Accessor for m_position.
			 * @return m_position.
			*/
			const CPeVector3& GetPosition() const;

			/**
			 * @brief Return the world space coordinates of a point in the local space coordinates of this transform
			 * 
			 */
			CPeVector3 GetPositionPoint(const CPeVector3& p_localPoint);

			/**
			 * @brief Return local space coordinates of a point in world space coordinates
			 *
			 */
			CPeVector3 GetPositionPointInLocal(const CPeVector3& p_globalPoint) const;

			/**
			 * @brief Return the global vector multiplyed by this transform rotation matrix
			 */
			CPeVector3 GetVectorInLocal(const CPeVector3& p_globalVector) const;

			/**
			 * @brief Accessor for m_orientation.
			 * @return m_orientation.
			*/
			const CPeQuaternion& GetOrientation() const;
			
			/**
			 * @brief Accessor for m_size.
			 * @return m_size.
			*/
			const CPeVector3& GetSize() const;

			/**
			 * @brief Accessor for m_transformMatrix.
			 * @return the transform matrix.
			*/
			const CPeMatrix4& GetTransformMatrix() const;

			/**
			 * @brief Setter for m_position.
			 * @param The new position.
			*/
			void SetPosition(const CPeVector3& p_position);

			/**
			 * @brief Setter for m_orientation.
			 * @param The new orientation.
			*/
			void SetOrientation(const CPeQuaternion& p_orientation);



			/**
			 * @brief Setter for m_size.
			 * @param The new size.
			*/
			void SetSize(const CPeVector3& p_size);

			static void ComputeMatrixFromTransform(CPeMatrix4& resultMatrix, const CPeVector3& _position, const CPeQuaternion& _orientation = CPeQuaternion(1,0,0,0), const CPeVector3& _size = CPeVector3(1,1,1));

		private:
			/**
				* @brief Update transform matrix with the current position, orientation & size
				*
			*/
			void UpdateTransformMatrix();

			

		};
	}
}

#endif /* CPEMATHS_CPETRANSFORM_H */