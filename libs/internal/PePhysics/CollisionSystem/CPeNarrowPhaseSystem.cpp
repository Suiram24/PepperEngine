#include "CPeNarrowPhaseSystem.h"

namespace engine
{
	namespace physics {
			void CPeNarrowPhaseSystem::GenerateContacts(const CPeSpherePrimitiveShape& p_sphere1, const CPeSpherePrimitiveShape& p_sphere2, std::vector<SPeContactInfos*>* datas)
			{
				double r1 = p_sphere1.GetRadius();
				double r2 = p_sphere1.GetRadius();

				double d = p_sphere1.GetWorldPosition().DistanceTo(p_sphere2.GetWorldPosition());

				if (d * d < r1 * r1 + r2 * r2)
				{
					return;
				}

				SPeContactInfos* data = new SPeContactInfos();

				data->normal = (p_sphere1.GetWorldPosition() - p_sphere2.GetWorldPosition()).NormalizeVector();
				data->interpenetration = r1 + r2 - d;
				data->contactPoint = p_sphere2.GetWorldPosition() + r2 * data->normal;

				datas->push_back(data);
			}

			void CPeNarrowPhaseSystem::GenerateContacts(const CPeSpherePrimitiveShape& p_sphere, const CPePlanePrimitiveShape& p_plane, std::vector<SPeContactInfos*>* datas)
			{
				double r  = p_sphere.GetRadius();
				double d = pemaths::CPeVector3::ScalarProduct(p_sphere.GetWorldPosition(), p_plane.GetNormal()) - p_plane.GetOffset() - r;

				if (d > 0)
				{
					return;
				}

				SPeContactInfos* data = new SPeContactInfos();

				data->normal = p_plane.GetNormal();
				data->interpenetration = d;
				data->contactPoint = p_sphere.GetWorldPosition() - r * data->normal;

				datas->push_back(data);
			}

			void CPeNarrowPhaseSystem::GenerateContacts(const CPeBoxPrimitiveShape& p_box, const CPePlanePrimitiveShape& p_plane, std::vector<SPeContactInfos*>* datas)
			{
				
			}

			void CPeNarrowPhaseSystem::GenerateContacts(const CPeBoxPrimitiveShape& p_box, const CPeSpherePrimitiveShape& p_sphere, std::vector<SPeContactInfos*>* datas)
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
					return;
				}

				SPeContactInfos* data = new SPeContactInfos();

				data->normal = (closestPoint - spherePos).NormalizeVector();
				data->interpenetration = r - d;
				data->contactPoint = spherePos + r * data->normal;

				datas->push_back(data);
			}

			void CPeNarrowPhaseSystem::GenerateContacts(const CPeBoxPrimitiveShape& p_box1, const CPeBoxPrimitiveShape& p_box2, std::vector<SPeContactInfos*>* datas)
			{
				pemaths::CPeVector3 axes[15];

				pemaths::CPeMatrix3 transform1 = p_box1.GetWorldTransform().ToMatrix3();
				pemaths::CPeMatrix3 transform2 = p_box2.GetWorldTransform().ToMatrix3();

				pemaths::CPeVector3 toCenter = p_box2.GetWorldPosition() - p_box1.GetWorldPosition();

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
						axis[6 + i * 3 + j] = pemaths::CPeVector3::CrossProduct(axis[i], axis[3 + j]).NormalizeVector();
					}
				}

				double bestOverlap = DOUBLE_MAX;
				int bestCase;

				for (int i = 0; i < 15; i++)
				{
					pemaths::CPeVector3 axe = axes[i];
					double magnitude = axe.GetNorm();

					if (magnitude * magnitude < 0.001)
					{
						break;
					}

					//Compute penetration on axis
					double proj1 = max(
						pemaths::CPeVector3::ScalarProduct(axes[0] * p_box1.GetHalfSize().GetX(),axe),
						pemaths::CPeVector3::ScalarProduct(axes[1] * p_box1.GetHalfSize().GetY(),axe),
						pemaths::CPeVector3::ScalarProduct(axes[2] * p_box1.GetHalfSize().GetZ(),axe)
					);
					double proj2 = max(
						pemaths::CPeVector3::ScalarProduct(axes[3] * p_box2.GetHalfSize().GetX(), axe),
						pemaths::CPeVector3::ScalarProduct(axes[4] * p_box2.GetHalfSize().GetY(), axe),
						pemaths::CPeVector3::ScalarProduct(axes[5] * p_box2.GetHalfSize().GetZ(), axe)
					);

					double dist = abs(pemaths::CPeVector3::ScalarProduct(toCenter, axe));

					double overlap = proj1 + proj2 - dist;

					//Save best overlap
					if (overlap < 0)
					{
						break;
					}
					if (overlap < bestOverlap)
					{
						bestOverlap = overlap;
						bestCase = i;
					}
				}

				
				pemaths::CPeVector3 contactAxis = axis[bestCase];
				// Contact based on face axis
				if (bestCase < 6)
				{
					const CPeBoxPrimitiveShape& one;
					const CPeBoxPrimitiveShape& two;

					if (pemaths::CPeVector3::ScalarProduct(contactAxis, toCenter) < 0)
					{
						contactAxis = contactAxis * -1;
					}

					pemaths::CPeVector3 vertex;

					// Contact based on face axis of box two
					if (best case < 3)
					{
						one = p_box1;
						two = p_box2;

						vertex = two.GetHalfSize();
						if (pemaths::CPeVector3::ScalarProduct(axis[3], contactAxis) < 0)
						{
							vertex.SetX(-vertex.GetX());
						}
						if (pemaths::CPeVector3::ScalarProduct(axis[4], contactAxis) < 0)
						{
							vertex.SetY(-vertex.GetY());
						}
						if (pemaths::CPeVector3::ScalarProduct(axis[5], contactAxis) < 0)
						{
							vertex.SetY(-vertex.GetY());
						}
					}
					// Contact based on face axis of box two
					else
					{
						one = p_box2;
						two = p_box1;

						vertex = two.GetHalfSize();
						if (pemaths::CPeVector3::ScalarProduct(axis[0], contactAxis) < 0)
						{
							vertex.SetX(-vertex.GetX());
						}
						if (pemaths::CPeVector3::ScalarProduct(axis[1], contactAxis) < 0)
						{
							vertex.SetY(-vertex.GetY());
						}
						if (pemaths::CPeVector3::ScalarProduct(axis[2], contactAxis) < 0)
						{
							vertex.SetY(-vertex.GetY());
						}
					}

					vertex = two.GetWorldTransform() * vertex;

					SPeContactInfos* data = new SPeContactInfos();

					data->normal = contactAxis;
					data->interpenetration = bestOverlap;
					data->contactPoint = vertex;

					datas->push_back(data);
				}
				//Contact based on edge-edge
				else
				{
					int oneAxisIndex = (bestCase - 6)/3;
					int twoAxisIndex = (bestCase - 6) % 3;

					pemaths::CPeVector3 pointOnEdge1 = p_box1.GetHalfSize();
					pemaths::CPeVector3 pointOnEdge2 = p_box2.GetHalfSize();
					for (int i = 0; i < 3; i++)
					{
						if (i == oneAxisIndex)
						{
							pointOnEdge1[i] = 0;
						}
						else if (pemaths::CPeVector3::ScalarProduct(axis[i], contactAxis) > 0)
						{
							pointOnEdge1[i] = -pointOnEdge1[i];
						}

						if (i == twoAxisIndex)
						{
							pointOnEdge2[i] = 0;
						}
						else if (pemaths::CPeVector3::ScalarProduct(axis[3+i], contactAxis) < 0)
						{
							pointOnEdge2[i] = -pointOnEdge2[i];
						}
					}

					//Get world translations
					pemaths::CPeMatrix4 translation1 = p_box1.GetWorldTransform();
					pemaths::CPeMatrix4 translation2 = p_box1.GetWorldTransform();
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
					data->contactPoint = getContactPoint(axis[oneAxisIndex], axis[3+twoAxisIndex], pointOnEdge1, pointOnEdge2);

					datas->push_back(data);
				}
			}

			pemaths::CPeVector3 CPeNarrowPhaseSystem::GetContactPoint(const pemaths::CPeVector3& axisOne, const pemaths::CPeVector3& axisTwo, const pemaths::CPeVector3& pointOnEdgeOne, const pemaths::CPeVector3& pointOnEdgeTwo) const
			{
				pemaths::CPeVector3 toSt pointOnEdgeOne - pointOnEdgeTwo;

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

	}
}