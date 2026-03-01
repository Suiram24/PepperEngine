#ifndef CPEMATHS_CPEQUATERNION_H
#define CPEMATHS_CPEQUATERNION_H

#include "CPeVector3.h"
#include "CPeMatrix3.h"
#include "CPeMatrix4.h"

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
            double m_value[4];
        public:
        protected:

        private:
            /**
             * @brief Compute the norm of the quaternion
             * 
             * @return double - Norm of the
             */
            double GetNorm();
        public: 
            /**
             * @brief Construct a new CPeQuaternion object
             * 
             */
            CPeQuaternion();
         /**
             * @brief Construct a new CPeQuaternion object
             * 
             * @param w double - real part of the quaternion
             * @param x double - i part of the quaternion
             * @param y double - j part of the quaternion
             * @param z double - k part of the quaternion
             */
            CPeQuaternion(double w, double x, double y, double z);

            /**
             * @brief Construct a new CPeQuaternion object
             * 
             * @param w double - real part of the qauternion
             * @param v CPeVector3& - imaginary part of the quaternion
             */
            CPeQuaternion(double w, const CPeVector3& v);

                        /**
             * @brief Construct a new CPeQuaternion object with and axis-angle rotation
             * 
             * @param axis sNormalized axis of the rotation
             * @param angle the angle of the rotation in rad
             */
            CPeQuaternion(const CPeVector3& axis, double angle);

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
             * @param scalar double element to divide by
             * @return CPeQuaternion - Result of the division
             */
            CPeQuaternion operator/(const double& scalar) const;

            /**
             * @brief Auto division by a scalar
             * 
             * @param scalar double element to divide by
             * @return CPeQuaternion& - Modified quaternion
             */
            CPeQuaternion& operator/=(const double& scalar);

            /**
             * @brief Auto addition by another quaternion
             * 
             * @param q2 CPe
             * @return CPeQuaternion& 
             */
            CPeQuaternion& operator+=(const CPeQuaternion& q2);

            CPeQuaternion operator+(const CPeQuaternion& q2) const;

            /**
             * @brief Product by a scalar
             * 
             * @param scalar double scalar to multiply the quaternion with
             * @return CPeQuaternion - Result of the multiplication
             */
            CPeQuaternion operator*(double scalar) const;

            /**
             * @brief Auto product by a scalar
             * 
             * @param scalar double scalar to multiply the quaternion with
             * @return CPeQuaternion - Modified Quaternion
             */
            CPeQuaternion& operator*=(double scalar);

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
             * @param duration double representing the time to apply the angular speed
             * @return CPeQuaternion& - Modified rotation
             */
            CPeQuaternion& UpdateByAngularVelocity(const CPeVector3& rotation, double duration);

            /**
             * @brief Get the Real Part of the quaternion
             * 
             * @return double - Real part of the quaternion (w)
             */
            double GetRealPart() const;


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
             * @return double - Angle represented by the rotation quaternion.
             */
            double GetAngle() const;

            /**
             * @brief Bget norm of the quaternion.
             * 
             * @return double - The norm of the quaternion.
             */
            double GetNorm() const;

            /**
             * @brief Create a normalize quaternion from the targeted quaternion.
             * 
             * @return Normalized quaternion.
             */
            CPeQuaternion Normalize() const;

            /**
             * @brief Return the matrix 3x3 version of the quaternion.
             * @return CPeMatrix3 version of your CPeQuaternion.
             */
            CPeMatrix3 ToMatrix3() const;

            /**

            * @brief Return the matrix 3x4 version of the quaternion.
            * @return CPeMatrix3 version of your CPeQuaternion.
            */
            CPeMatrix4 ToMatrix4() const;
          
        protected:
        };

        /**
         * @brief Quaternion product by a scalar
         * 
         * @param scalar double Scalar to multiply the quaternion with
         * @param q CPeQuaternion& Quaternion to multiply
         * @return CPeQuaternion - Result of the multiplication
         */

        CPeQuaternion operator*(double scalar, const CPeQuaternion& q);


    }
}


#endif