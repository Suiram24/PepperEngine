#include "CPeQuaternion.h"
#include <cmath>
#include <cstdio>
namespace engine {
    namespace maths {
        float CPeQuaternion::GetNorm()
        {
            return std::sqrt(
                m_value[0]*m_value[0] + 
                m_value[1]*m_value[1] +
                m_value[2]*m_value[2] +
                m_value[3]*m_value[3]
            );
        }

        CPeQuaternion::CPeQuaternion() : 
            m_value({0.0f,0.0f,0.0f,0.0f})
        {
        }

        CPeQuaternion::CPeQuaternion(float w, float x, float y, float z) : 
            m_value({w,x,y,z})
        {
        }

        CPeQuaternion::CPeQuaternion(float w, const CPeVector3 &v) : 
            m_value({w,v.GetX(),v.GetY(),v.GetZ()})
        {
        }

        CPeQuaternion::CPeQuaternion(const CPeQuaternion &q) :
            m_value({q.m_value[0],q.m_value[1],q.m_value[2],q.m_value[3]})
        {
        }

        CPeQuaternion &CPeQuaternion::operator=(const CPeQuaternion &q)
        {
            *this = CPeQuaternion(q);
            return *this;
        }

        CPeQuaternion CPeQuaternion::operator/(const float &scalar) const
        {
            CPeQuaternion q(*this);
            q /= scalar;
            return q;
        }

        CPeQuaternion &CPeQuaternion::operator/=(const float &scalar)
        {
            for(int i = 0; i < 4; ++i) {
                m_value[i] /= scalar;
            }
            return *this;
        }

        CPeQuaternion &CPeQuaternion::operator+=(const CPeQuaternion &q2)
        {
            this->m_value[0] += q2.m_value[0];
            this->m_value[1] += q2.m_value[1];
            this->m_value[2] += q2.m_value[2];
            this->m_value[3] += q2.m_value[3];
            return *this;
        }

        CPeQuaternion CPeQuaternion::operator*(float scalar) const
        {
            CPeQuaternion q(*this);
            q *= scalar;
            return q;
        }

        CPeQuaternion &CPeQuaternion::operator*=(float scalar)
        {
            this->m_value[0] *= scalar;
            this->m_value[1] *= scalar;
            this->m_value[2] *= scalar;
            this->m_value[3] *= scalar;
            return *this;
        }

        CPeQuaternion CPeQuaternion::operator*(const CPeQuaternion &q2) const
        {
            float re_q1 = this->GetRealPart(), re_q2 = q2.GetRealPart();
            CPeVector3 im_q1 = this->GetImaginaryPart();
            CPeVector3 im_q2 = q2.GetImaginaryPart();
            return CPeQuaternion(
                re_q1*re_q2 - CPeVector3::ScalarProduct(im_q1,im_q2),
                re_q1*im_q2 +
                re_q2*im_q1 +
                CPeVector3::CrossProduct(im_q1,im_q2)
            );
        }

        CPeQuaternion &CPeQuaternion::operator*=(const CPeQuaternion &q2)
        {
            *this = *this * q2;
        }

        CPeQuaternion &CPeQuaternion::RotateByVector(const CPeVector3 &vector)
        {
            CPeVector3 rotationVector = vector.NormalizeVector();
            CPeQuaternion rotationQuaternion(0,rotationVector);
            *this *= rotationQuaternion;
            return *this;
        }

        CPeQuaternion &CPeQuaternion::UpdateByAngularVelocity(const CPeVector3 &rotation, float duration)
        {
            CPeQuaternion rotationQuaternion(0,rotation);
            *this += duration/2 * rotationQuaternion * (*this);
            return *this;
        }

        float CPeQuaternion::GetRealPart() const
        {
            return m_value[0];
        }

        CPeVector3 CPeQuaternion::GetImaginaryPart() const
        {
            return CPeVector3(m_value[1],m_value[2],m_value[3]);
        }

        float CPeQuaternion::GetAngle() const
        {
            return 2*std::acos(m_value[0]);
        }

        CPeQuaternion operator*(float scalar, const CPeQuaternion &q)
        {
            return q*scalar;
        }
    }
}