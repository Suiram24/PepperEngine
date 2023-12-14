#ifndef CPENARROWPHASESYSTEM_CPENARROWPHASESYSTEM_H
#define CPENARROWPHASESYSTEM_CPENARROWPHASESYSTEM_H

#include <vector>
#include "CPePrimitiveShape.h"
#include "CPeSpherePrimitiveShape.h"
#include "CPePlanePrimitiveShape.h"
#include "CPeBoxPrimitiveShape.h"
#include "SPeContactInfos.h"

namespace engine
{
	namespace physics {
		/**
		 * @brief The class that detect contacts between primitive shapes. Provides contacts infos.
		*/
		class CPeNarrowPhaseSystem {
		private:
			const double DOUBLE_MAX = 1000000;

			enum EShapeTypes
			{
				SPHERE, BOX, PLANE
			};

			
		public:

			static CPeNarrowPhaseSystem& GetInstance()
			{
				static CPeNarrowPhaseSystem instance;
				return instance;
			}


			/**
			 * @brief Generate contact between the two primitives.
			 * @param CPePrimitiveShape the first primitive.
			 * @param CPePrimitiveShape the second primitive.
			 * @param SPeContactInfos the contact info to fill.
			*/
			void GenerateContacts(const CPePrimitiveShape* p_shape1, const CPePrimitiveShape* p_shape2, std::vector<SPeContactInfos*>* datas);

		private:
			void GenContSphSph(const CPeSpherePrimitiveShape* p_sphere1, const CPeSpherePrimitiveShape* p_sphere2, std::vector<SPeContactInfos*>* datas);
			void GenContSphPla(const CPeSpherePrimitiveShape* p_sphere, const CPePlanePrimitiveShape* p_plane, std::vector<SPeContactInfos*>* datas);
			void GenContBoxPla(const CPeBoxPrimitiveShape* p_box, const CPePlanePrimitiveShape* p_plane, std::vector<SPeContactInfos*>* datas);
			void GenContBoxSph(const CPeBoxPrimitiveShape* p_box, const CPeSpherePrimitiveShape* p_sphere, std::vector<SPeContactInfos*>* datas);
			void GenContBoxBox(const CPeBoxPrimitiveShape* p_box1, const CPeBoxPrimitiveShape* p_box2, std::vector<SPeContactInfos*>* datas);
			
			static bool AddRigidbodyToContactInfos(SPeContactInfos* data, pecore::CPeEntity& entity1, pecore::CPeEntity& entity2);


			CPeNarrowPhaseSystem()
			{
			}

			pemaths::CPeVector3 GetContactPoint(const pemaths::CPeVector3& axisOne, const pemaths::CPeVector3& axisTwo, const pemaths::CPeVector3& pointOnEdgeOne, const pemaths::CPeVector3& pointOnEdgeTwo) const;
		};
	}
}

#endif /* CPENARROWPHASESYSTEM_CPENARROWPHASESYSTEM_H */