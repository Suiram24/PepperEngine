#ifndef CPEMATHS_CPEQUATERNION_H
#define CPEMATHS_CPEQUATERNION_H

#include "CPeVector3.h"

namespace engine
{
	namespace maths
	{
        /**
         * @brief Class that implement quaternion
         * 
         */
        class CPeQuaternion {
        private:
            /// @brief Values w, x, y & z of the quaternion
            float m_value[4];
        public:
        protected:

        private:
            /**
             * @brief Compute the norm of the quaternion
             * 
             * @return float - Norm of the
             */
            float GetNorm();
        public: 
            /**
             * @brief Construct a new CPeQuaternion object
             * 
             */
            CPeQuaternion();
            /**
             * @brief Construct a new CPeQuaternion object
             * 
             * @param w float - real part of the quaternion
             * @param x float - i part of the quaternion
             * @param y float - j part of the quaternion
             * @param z float - k part of the quaternion
             */
            CPeQuaternion(float w, float x, float y, float z);

            /**
             * @brief Construct a new CPeQuaternion object
             * 
             * @param w float - real part of the qauternion
             * @param v CPeVector3& - imaginary part of the quaternion
             */
            CPeQuaternion(float w, const CPeVector3& v);

            /**
             * @brief Construct a new CPeQuaternion object by copy
             * 
             * @param q CPeQuaternion& - Quaternion to copy
             */
            CPeQuaternion(const CPeQuaternion& q);

            /**
             * @brief Assignation operator
             * 
             * @param q CPeQuaternion - Quaternion to assign
             * @return CPeQuaternion& - Reference to the quaternion
             */
            CPeQuaternion& operator=(const CPeQuaternion& q);

            /**
             * @brief Division by a scalar
             * 
             * @param scalar float element to divide by
             * @return CPeQuaternion - Result of the division
             */
            CPeQuaternion operator/(const float& scalar) const;

            /**
             * @brief Auto division by a scalar
             * 
             * @param scalar float element to divide by
             * @return CPeQuaternion& - Modified quaternion
             */
            CPeQuaternion& operator/=(const float& scalar);

            /**
             * @brief Auto addition by another quaternion
             * 
             * @param q2 CPe
             * @return CPeQuaternion& 
             */
            CPeQuaternion& operator+=(const CPeQuaternion& q2);

            /**
             * @brief Product by a scalar
             * 
             * @param scalar float scalar to multiply the quaternion with
             * @return CPeQuaternion - Result of the multiplication
             */
            CPeQuaternion operator*(float scalar) const;

            /**
             * @brief Auto product by a scalar
             * 
             * @param scalar float scalar to multiply the quaternion with
             * @return CPeQuaternion - Modified Quaternion
             */
            CPeQuaternion& operator*=(float scalar);

            /**
             * @brief Quaternion product
             * 
             * @param q2 CPeQuaternion& Other quaternion to multiply with
             * @return CPeQuaternion - Result of the multiplication
             */
            CPeQuaternion operator*(const CPeQuaternion& q2) const;

            /**
             * @brief Auto quaternion product
             * 
             * @param q2 CPeQuaternion& Other quaternion to multiply with
             * @return CPeQuaternion& - Modified Quaternion
             */
            CPeQuaternion& operator*=(const CPeQuaternion& q2);

            /**
             * @brief Rotate Quaternion around a vector
             * 
             * @param vector CPeVector3& to rotate the quaternion around
             * @return CPeQuaternion& - Modified quaternion
             */
            CPeQuaternion& RotateByVector(const CPeVector3& vector);

            /**
             * @brief Update the quaternion thanks to the angular velocity given a
             * specific period of time to apply it
             * 
             * @param rotation CPeVector3& representing the angular rotation
             * @param duration float representing the time to apply the angular speed
             * @return CPeQuaternion& - Modified rotation
             */
            CPeQuaternion& UpdateByAngularVelocity(const CPeVector3& rotation, float duration);

            /**
             * @brief Get the Real Part of the quaternion
             * 
             * @return float - Real part of the quaternion (w)
             */
            float GetRealPart() const;


            /**
             * @brief Get the Imaginary Part of the quaternion
             * 
             * @return CPeVector3 - Imaginary part of the quaternion (x,y,z)
             */
            CPeVector3 GetImaginaryPart() const;

            /**
             * @brief Get the Angle represented by the quaternion.
             * It only works if the quaternion represents a rotation.
             * 
             * @return float - Angle represented by the rotation quaternion.
             */
            float GetAngle() const;

        protected:
        };

        /**
         * @brief Quaternion product by a scalar
         * 
         * @param scalar float Scalar to multiply the quaternion with
         * @param q CPeQuaternion& Quaternion to multiply
         * @return CPeQuaternion - Result of the multiplication
         */
        CPeQuaternion operator*(float scalar, const CPeQuaternion& q);
    }
}


#endif