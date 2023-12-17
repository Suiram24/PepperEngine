#include "CPeNarrowPhaseSystem.h"

namespace engine
{
	namespace physics {
		
		
			void CPeNarrowPhaseSystem::GenerateContacts(const CPePrimitiveShape* p_shape1, const CPePrimitiveShape* p_shape2, std::vector<SPeContactInfos*>* datas)
			{
				//Determine first shape type
				EShapeTypes type1 = p_shape1->GetType();

				//Determine second shape type

				EShapeTypes type2 = p_shape2->GetType();
				

				switch (type1)
				{
				case SPHERE:
					if (type2 == SPHERE) { 
						GenContSphSph(
							dynamic_cast<const CPeSpherePrimitiveShape*>(p_shape1),
							dynamic_cast<const CPeSpherePrimitiveShape*>(p_shape2),
							datas
						); 
					}
					else if (type2 == BOX) {
						GenContBoxSph(
							dynamic_cast<const CPeBoxPrimitiveShape*>(p_shape2),
							dynamic_cast<const CPeSpherePrimitiveShape*>(p_shape1),
							datas
						);
					}
					else if (type2 == PLANE) { 
						GenContSphPla(
							dynamic_cast<const CPeSpherePrimitiveShape*>(p_shape1),
							dynamic_cast<const CPePlanePrimitiveShape*>(p_shape2),
							datas
						);
					}
					break;
				case BOX:
					if (type2 == SPHERE) {
						GenContBoxSph(
							dynamic_cast<const CPeBoxPrimitiveShape*>(p_shape1),
							dynamic_cast<const CPeSpherePrimitiveShape*>(p_shape2),
							datas
						);
					}
					else if (type2 == BOX) {
						GenContBoxBox(
							dynamic_cast<const CPeBoxPrimitiveShape*>(p_shape1),
							dynamic_cast<const CPeBoxPrimitiveShape*>(p_shape2),
							datas
						);
					}
					else if (type2 == PLANE) {
						GenContBoxPla(
							dynamic_cast<const CPeBoxPrimitiveShape*>(p_shape1),
							dynamic_cast<const CPePlanePrimitiveShape*>(p_shape2),
							datas
						);
					}
					break;
				case PLANE:
					if (type2 == SPHERE) {
						GenContSphPla(
							dynamic_cast<const CPeSpherePrimitiveShape*>(p_shape2),
							dynamic_cast<const CPePlanePrimitiveShape*>(p_shape1),
							datas
						);
					}
					else if (type2 == BOX) {
						GenContBoxPla(
							dynamic_cast<const CPeBoxPrimitiveShape*>(p_shape2),
							dynamic_cast<const CPePlanePrimitiveShape*>(p_shape1),
							datas
						); 
					}
					break;
				default:
					break;
				}
			}
		


			void CPeNarrowPhaseSystem::GenContSphSph(const CPeSpherePrimitiveShape* p_sphere1, const CPeSpherePrimitiveShape* p_sphere2, std::vector<SPeContactInfos*>* datas)
			{
				double r1 = p_sphere1->GetRadius();
				double r2 = p_sphere2->GetRadius();

				double d = p_sphere1->GetWorldPosition().DistanceTo(p_sphere2->GetWorldPosition());

				if (d > (r1 + r2))
				{
					return;
				}

				SPeContactInfos* data = new SPeContactInfos();

				data->normal = (p_sphere1->GetWorldPosition() - p_sphere2->GetWorldPosition()).NormalizeVector();
				data->interpenetration = r1 + r2 - d;
				data->contactPoint = p_sphere2->GetWorldPosition() + r2 * data->normal;

				if (AddRigidbodyToContactInfos(data, p_sphere1->GetOwningEntity(), p_sphere2->GetOwningEntity()))
				{
					datas->push_back(data);
				}
				else
				{
					delete data;
				}
			}

			void CPeNarrowPhaseSystem::GenContSphPla(const CPeSpherePrimitiveShape* p_sphere, const CPePlanePrimitiveShape* p_plane, std::vector<SPeContactInfos*>* datas)
			{
				double r  = p_sphere->GetRadius();
				double d = pemaths::CPeVector3::ScalarProduct(p_sphere->GetWorldPosition(), p_plane->GetNormal()) - p_plane->GetOffset() - r;

				if (d > 0)
				{
					return;
				}

				SPeContactInfos* data = new SPeContactInfos();

				data->normal = p_plane->GetNormal();
				data->interpenetration = d;
				data->contactPoint = p_sphere->GetWorldPosition() - r * data->normal;

				if (AddRigidbodyToContactInfos(data, p_sphere->GetOwningEntity(), p_plane->GetOwningEntity()))
				{
					datas->push_back(data);
				}
				else
				{
					delete data;
				}
			}

			void CPeNarrowPhaseSystem::GenContBoxPla(const CPeBoxPrimitiveShape* p_box, const CPePlanePrimitiveShape* p_plane, std::vector<SPeContactInfos*>* datas)
			{
				pemaths::CPeVector3 corners[8];
				pemaths::CPeVector3 pos = p_box->GetWorldPosition();

				double x = p_box->GetHalfSize().GetX();
				double y = p_box->GetHalfSize().GetY();
				double z = p_box->GetHalfSize().GetZ();

				corners[0] = pos + pemaths::CPeVector3( x,  y,  z);
				corners[1] = pos + pemaths::CPeVector3( x,  y, -z);
				corners[2] = pos + pemaths::CPeVector3( x, -y,  z);
				corners[3] = pos + pemaths::CPeVector3( x, -y, -z);
				corners[4] = pos + pemaths::CPeVector3(-x,  y,  z);
				corners[5] = pos + pemaths::CPeVector3(-x,  y, -z);
				corners[6] = pos + pemaths::CPeVector3(-x, -y,  z);
				corners[7] = pos + pemaths::CPeVector3(-x, -y, -z);

				for (int i = 0; i < 8; i++)
				{
					double d = pemaths::CPeVector3::ScalarProduct(corners[i], p_plane->GetNormal()) - p_plane->GetOffset();

					if (d > 0)
					{
						break;
					}

					SPeContactInfos* data = new SPeContactInfos();

					data->normal = p_plane->GetNormal();
					data->interpenetration = d;
					data->contactPoint = corners[i];

					if (AddRigidbodyToContactInfos(data, p_box->GetOwningEntity(), p_plane->GetOwningEntity()))
					{
						datas->push_back(data);
					}
					else
					{
						delete data;
					}
				}
			}

			void CPeNarrowPhaseSystem::GenContBoxSph(const CPeBoxPrimitiveShape* p_box, const CPeSpherePrimitiveShape* p_sphere, std::vector<SPeContactInfos*>* datas)
			{
				pemaths::CPeMatrix4 T = p_box->GetWorldTransform();

				pemaths::CPeVector3 boxPos = T.Inverse() * p_box->GetWorldPosition();
				pemaths::CPeVector3 spherePos = T.Inverse() * p_sphere->GetWorldPosition();
				
				pemaths::CPeVector3 closestPoint = pemaths::CPeVector3();



				double dist;
				double pos;
				
				pos = p_box->GetHalfSize().GetX();
				dist = spherePos.GetX();
				if (dist > pos) dist = pos;
				if (dist < -pos) dist = -pos;
				closestPoint.SetX(dist);

				pos = p_box->GetHalfSize().GetY();
				dist = spherePos.GetY();
				if (dist > pos) dist = pos;
				if (dist < -pos) dist = -pos;
				closestPoint.SetY(dist);

				pos = p_box->GetHalfSize().GetZ();
				dist = spherePos.GetZ();
				if (dist > pos) dist = pos;
				if (dist < -pos) dist = -pos;
				closestPoint.SetZ(dist);

				double d = (closestPoint - spherePos).GetNorm();
				double r = p_sphere->GetRadius();

				if (d - r > 0) // Box doesn't collide
				{
					return;
				}

				SPeContactInfos* data = new SPeContactInfos();
				pemaths::CPeVector3 cp = T * closestPoint;
				pemaths::CPeVector3 sp = T * spherePos;
				data->normal = ((cp - sp).NormalizeVector());
				data->interpenetration = r - d;
				data->contactPoint = (sp + r * data->normal);

				if (AddRigidbodyToContactInfos(data, p_box->GetOwningEntity(), p_sphere->GetOwningEntity()))
				{
					datas->push_back(data);
				}
				else
				{
					delete data;
				}
			}

			void CPeNarrowPhaseSystem::GenContBoxBox(const CPeBoxPrimitiveShape* p_box1, const CPeBoxPrimitiveShape* p_box2, std::vector<SPeContactInfos*>* datas)
			{
				pemaths::CPeVector3 axes[15];

				pemaths::CPeMatrix3 transform1 = p_box1->GetWorldTransform().ToMatrix3();
				pemaths::CPeMatrix3 transform2 = p_box2->GetWorldTransform().ToMatrix3();

				pemaths::CPeVector3 toCenter = p_box2->GetWorldPosition() - p_box1->GetWorldPosition();

				axes[0] = transform1.GetAxis1().NormalizeVector();
				axes[1] = transform1.GetAxis2().NormalizeVector();
				axes[2] = transform1.GetAxis3().NormalizeVector();
				axes[3] = transform2.GetAxis1().NormalizeVector();
				axes[4] = transform2.GetAxis2().NormalizeVector();
				axes[5] = transform2.GetAxis3().NormalizeVector();

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						axes[6 + i * 3 + j] = pemaths::CPeVector3::CrossProduct(axes[i], axes[3 + j]).NormalizeVector();
					}
				}

				double bestOverlap = DOUBLE_MAX;
				int bestCase = -1;

				for (int i = 0; i < 15; i++)
				{
					pemaths::CPeVector3 axe = axes[i];
					double magnitude = axe.GetNorm();

					if (magnitude * magnitude < 0.001)
					{
						continue;
					}

					//Compute penetration on axis
					double proj1 = std::max({
						abs(pemaths::CPeVector3::ScalarProduct(axes[0] * p_box1->GetHalfSize().GetX(),axe)),
						abs(pemaths::CPeVector3::ScalarProduct(axes[1] * p_box1->GetHalfSize().GetY(),axe)),
						abs(pemaths::CPeVector3::ScalarProduct(axes[2] * p_box1->GetHalfSize().GetZ(),axe))
					});
					double proj2 = std::max({
						abs(pemaths::CPeVector3::ScalarProduct(axes[3] * p_box2->GetHalfSize().GetX(), axe)),
						abs(pemaths::CPeVector3::ScalarProduct(axes[4] * p_box2->GetHalfSize().GetY(), axe)),
						abs(pemaths::CPeVector3::ScalarProduct(axes[5] * p_box2->GetHalfSize().GetZ(), axe))
					});

					double dist = abs(pemaths::CPeVector3::ScalarProduct(toCenter, axe));

					double overlap = proj1 + proj2 - dist;

					//Save best overlap
					if (overlap < 0)
					{
						return;
					}
					if (overlap < bestOverlap)
					{
						bestOverlap = overlap;
						bestCase = i;
					}
				}

				pemaths::CPeVector3 contactAxis = axes[bestCase];
				// Contact based on face axis
				if (bestCase < 6)
				{
					const CPeBoxPrimitiveShape* one;
					const CPeBoxPrimitiveShape* two;

					if (pemaths::CPeVector3::ScalarProduct(contactAxis, toCenter) < 0)
					{
						contactAxis = contactAxis * -1;
					}

					pemaths::CPeVector3 vertex;

					// Contact based on face axis of box two
					if (bestCase < 3)
					{
						one = p_box1;
						two = p_box2;

						vertex = two->GetHalfSize();
						if (pemaths::CPeVector3::ScalarProduct(axes[3], contactAxis) < 0)
						{
							vertex.SetX(-vertex.GetX());
						}
						if (pemaths::CPeVector3::ScalarProduct(axes[4], contactAxis) < 0)
						{
							vertex.SetY(-vertex.GetY());
						}
						if (pemaths::CPeVector3::ScalarProduct(axes[5], contactAxis) < 0)
						{
							vertex.SetZ(-vertex.GetZ());
						}
					}
					// Contact based on face axis of box one
					else
					{
						one = p_box2;
						two = p_box1;

						vertex = two->GetHalfSize();
						if (pemaths::CPeVector3::ScalarProduct(axes[0], contactAxis) < 0)
						{
							vertex.SetX(-vertex.GetX());
						}
						if (pemaths::CPeVector3::ScalarProduct(axes[1], contactAxis) < 0)
						{
							vertex.SetY(-vertex.GetY());
						}
						if (pemaths::CPeVector3::ScalarProduct(axes[2], contactAxis) < 0)
						{
							vertex.SetZ(-vertex.GetZ());
						}
					}

					vertex = two->GetWorldTransform() * vertex;

					SPeContactInfos* data = new SPeContactInfos();

					data->normal = contactAxis;
					data->interpenetration = bestOverlap;
					data->contactPoint = vertex;

					if (AddRigidbodyToContactInfos(data, one->GetOwningEntity(), two->GetOwningEntity()))
					{
						datas->push_back(data);
					}
					else
					{
						delete data;
					}
				}
				//Contact based on edge-edge
				else
				{
					int oneAxisIndex = (bestCase - 6)/3;
					int twoAxisIndex = (bestCase - 6) % 3;

					pemaths::CPeVector3 pointOnEdge1 = p_box1->GetHalfSize();
					pemaths::CPeVector3 pointOnEdge2 = p_box2->GetHalfSize();
					for (int i = 0; i < 3; i++)
					{
						if (i == oneAxisIndex)
						{
							pointOnEdge1.Set(i,0);
						}
						else if (pemaths::CPeVector3::ScalarProduct(axes[i], contactAxis) > 0)
						{
							pointOnEdge1.Set(i, -pointOnEdge1.Get(i));
						}

						if (i == twoAxisIndex)
						{
							pointOnEdge2.Set(i, 0);
						}
						else if (pemaths::CPeVector3::ScalarProduct(axes[3+i], contactAxis) < 0)
						{
							pointOnEdge2.Set(i, -pointOnEdge2.Get(i));
						}
					}

					//Get world translations
					pemaths::CPeMatrix4 translation1 = p_box1->GetWorldTransform();
					pemaths::CPeMatrix4 translation2 = p_box1->GetWorldTransform();
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							translation1.Set(i, j, 0);
							translation2.Set(i, j, 0);
						}
					}

					pointOnEdge1 = translation1 * pointOnEdge1;
					pointOnEdge2 = translation2 * pointOnEdge2;

					SPeContactInfos* data = new SPeContactInfos();

					data->normal = contactAxis;
					data->interpenetration = bestOverlap;
					data->contactPoint = GetContactPoint(axes[oneAxisIndex], axes[3+twoAxisIndex], pointOnEdge1, pointOnEdge2);
					
					if (AddRigidbodyToContactInfos(data, p_box1->GetOwningEntity(), p_box2->GetOwningEntity()))
					{
						datas->push_back(data);
					}
					else
					{
						delete data;
					}
				}
			}

			pemaths::CPeVector3 CPeNarrowPhaseSystem::GetContactPoint(const pemaths::CPeVector3& axisOne, const pemaths::CPeVector3& axisTwo, const pemaths::CPeVector3& pointOnEdgeOne, const pemaths::CPeVector3& pointOnEdgeTwo) const
			{
				pemaths::CPeVector3 toSt = pointOnEdgeOne - pointOnEdgeTwo;

				double dpStaOne = pemaths::CPeVector3::ScalarProduct(axisOne, toSt);
				double dpStaTwo = pemaths::CPeVector3::ScalarProduct(axisTwo, toSt);
				
				double smOne = axisOne.GetNorm() * axisOne.GetNorm();
				double smTwo= axisTwo.GetNorm() * axisTwo.GetNorm();
				double dotProductEdges = pemaths::CPeVector3::ScalarProduct(axisOne, axisTwo);
				double denom = smOne * smTwo - dotProductEdges * dotProductEdges;
				double a = (dotProductEdges * dpStaTwo - smTwo * dpStaOne) / denom;
				double b = (smOne * dpStaTwo - dotProductEdges * dpStaOne) / denom;

				pemaths::CPeVector3 nearestPointOne = pointOnEdgeOne + axisOne * a;
				pemaths::CPeVector3 nearestPointTwo = pointOnEdgeTwo + axisTwo * b;

				return	nearestPointOne * 0.5 + nearestPointTwo * 0.5;
			}


			bool CPeNarrowPhaseSystem::AddRigidbodyToContactInfos(SPeContactInfos* data, const pecore::CPeEntity& entity1, const pecore::CPeEntity& entity2)
			{
				CPeRigidBody* body1 = entity1.GetComponent<CPeRigidBody>();
				CPeRigidBody* body2 = entity2.GetComponent<CPeRigidBody>();

				if (body1 == nullptr || body1->GetMassInverse() == 0)
				{
					if (body2 == nullptr || body2->GetMassInverse() == 0)
					{
						return false;
					}
					else
					{
						data->obj1 = body2;
						data->obj2 = nullptr;
						
					}
				}
				else
				{
					data->normal = -1 * data->normal;
					data->obj1 = body1;
					if (body2 == nullptr || body2->GetMassInverse() == 0)
					{
						data->obj2 = nullptr;
					}
					else
					{
						data->obj2 = body2;
					}
				}

				return true;
			}

	}
}