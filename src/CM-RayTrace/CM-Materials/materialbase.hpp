// Base Class: Materials

#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "../CM-Textures/texturebase.hpp"
#include "../CM-Primitives/objectbase.hpp"
#include "../CM-Lights/lightbase.hpp"
#include "\qbLinAlg-main\qbVector.h"
#include "../ray.hpp"

namespace CMRT
{
	class MaterialBase
	{
		public:

			MaterialBase();

			virtual ~MaterialBase();

			virtual qbVector<double> ComputeColor(	const std::vector<std::shared_ptr<CMRT::ObjectBase>> &objectList,
													const std::vector<std::shared_ptr<CMRT::LightBase>> &lightList,
													const std::shared_ptr<CMRT::ObjectBase> &currentObject,
													const qbVector<double> &intPoint, const qbVector<double> &localNormal,
													const CMRT::Ray &cameraRay);


			qbVector<double> ComputeReflectionColor(	const std::vector<std::shared_ptr<CMRT::ObjectBase>> &objectList,
														const std::vector<std::shared_ptr<CMRT::LightBase>> &lightList,
														const std::shared_ptr<CMRT::ObjectBase> &currentObject,
														const qbVector<double> &intPoint, const qbVector<double> &localNormal,
														const CMRT::Ray &incidentRay);

			
			static qbVector<double> ComputeDiffuseColor(	const std::vector<std::shared_ptr<CMRT::ObjectBase>> &objectList,
															const std::vector<std::shared_ptr<CMRT::LightBase>> &lightList,
															const std::shared_ptr<CMRT::ObjectBase> &currentObject,
															const qbVector<double> &intPoint, const qbVector<double> &localNormal,
															const qbVector<double> &baseColor);


			bool CastRay(	const CMRT::Ray &castRay, const std::vector<std::shared_ptr<CMRT::ObjectBase>> &objectList,
							const std::shared_ptr<CMRT::ObjectBase> &thisObject,
							std::shared_ptr<CMRT::ObjectBase> &closestObject,
							qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
							qbVector<double> &closestLocalColor);


			void AssignTexture(const std::shared_ptr<CMRT::Texture::TextureBase> &inputTexture);


		public:
			
			inline static int m_maxReflectionRays;
			inline static int m_reflectionRayCount;

			std::vector<std::shared_ptr<CMRT::Texture::TextureBase>> m_textureList;

			bool m_hasTexture = false;

	};
}

#endif // !MATERIALBASE_H