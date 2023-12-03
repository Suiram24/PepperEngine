#include "CPeNarrowPhaseSystem.h"

namespace engine
{
	namespace physics {
			bool CPeNarrowPhaseSystem::GenerateContacts(const CPeSpherePrimitiveShape& p_sphere1, const CPeSpherePrimitiveShape& p_sphere2, SPeContactInfos* data)
			{
				double r1 = p_sphere1.GetRadius();
				double r2 = p_sphere1.GetRadius();

				double d = p_sphere1.GetWorldPosition().DistanceTo(p_sphere2.GetWorldPosition());

				if (d * d < r1 * r1 + r2 * r2)
				{
					return false;
				}

				data->normal = (p_sphere1.GetWorldPosition() - p_sphere2.GetWorldPosition()).NormalizeVector();
				data->interpenetration = r1 + r2 - d;
				data->contactPoint = p_sphere2.GetWorldPosition() + r2 * data->normal;

				return true;
			}

			bool CPeNarrowPhaseSystem::GenerateContacts(const CPeSpherePrimitiveShape& p_sphere, const CPePlanePrimitiveShape& p_plane, SPeContactInfos* data)
			{
				double r  = p_sphere.GetRadius();
				double d = pemaths::CPeVector3::ScalarProduct(p_sphere.GetWorldPosition(), p_plane.GetNormal()) - p_plane.GetOffset() - r;

				if (d > 0)
				{
					return false;
				}

				data->normal = p_plane.GetNormal();
				data->interpenetration = d;
				data->contactPoint = p_sphere.GetWorldPosition() - r * data->normal;

				return true;
			}

			bool CPeNarrowPhaseSystem::GenerateContacts(const CPeBoxPrimitiveShape& p_box, const CPePlanePrimitiveShape& p_plane, SPeContactInfos* data)
			{
			
			}

			bool CPeNarrowPhaseSystem::GenerateContacts(const CPeBoxPrimitiveShape& p_box, const CPeSpherePrimitiveShape& p_sphere, SPeContactInfos* data)
			{
				pemaths::CPeVector3 boxPos = p_box.GetWorldPosition();
				pemaths::CPeVector3 spherePos = p_box.GetWorldPosition();
				
				pemaths::CPeVector3 closestPoint = pemaths::CPeVector3();

				double dist;
				double pos;
				
				pos = p_box.GetHalfSize().GetX() + boxPos.GetX();
				dist = spherePos.GetX();
				if (dist > pos) dist = pos;
				if (dist < -pos) dist = -pos;
				closestPoint.SetX(dist);

				pos = p_box.GetHalfSize().GetY() + boxPos.GetY();
				dist = spherePos.GetY();
				if (dist > pos) dist = pos;
				if (dist < -pos) dist = -pos;
				closestPoint.SetY(dist);

				pos = p_box.GetHalfSize().GetZ() + boxPos.GetZ();
				dist = spherePos.GetZ();
				if (dist > pos) dist = pos;
				if (dist < -pos) dist = -pos;
				closestPoint.SetZ(dist);

				double d = (closestPoint - spherePos).GetNorm();
				double r = p_sphere.GetRadius();

				if (d - r > 0)
				{
					return false;
				}

				data->normal = (closestPoint - spherePos).NormalizeVector();
				data->interpenetration = r - d;
				data->contactPoint = spherePos + r * data->normal;

				return true;
			}

			bool CPeNarrowPhaseSystem::GenerateContacts(const CPeBoxPrimitiveShape& p_box1, const CPeBoxPrimitiveShape& p_box2, SPeContactInfos* data) 
			{

			}

	}
}