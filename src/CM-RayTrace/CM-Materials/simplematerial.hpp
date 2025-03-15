// Sub-Class: Simple Materials

#ifndef SIMPLEMATERIAL_H
#define	SIMPLEMATERIAL_H

#include "materialbase.hpp"

namespace CMRT
{
	class SimpleMaterial : public MaterialBase
	{
		public:

			SimpleMaterial();

			virtual ~SimpleMaterial() override;

			virtual qbVector<double> ComputeColor(	const std::vector<std::shared_ptr<CMRT::ObjectBase>> &objectList,
													const std::vector<std::shared_ptr<CMRT::LightBase>> &lightList,
													const std::shared_ptr<CMRT::ObjectBase> &currentObject,
													const qbVector<double> &intPoint, const qbVector<double> &localNormal,
													const CMRT::Ray &cameraRay) override;


			qbVector<double> ComputeSpecular(	const std::vector<std::shared_ptr<CMRT::ObjectBase>> &objectList,
												const std::vector<std::shared_ptr<CMRT::LightBase>> &lightList,
												const qbVector<double> &intPoint, const qbVector<double> &localNormal,
												const CMRT::Ray &cameraRay);
	

		public:
			qbVector<double> m_baseColor	{ std::vector<double> {1.0, 1.0, 1.0} };
			double m_reflectivity = 0.0;
			double m_shininess = 0.0;

	};
}

#endif // !SIMPLEMATERIAL_H