// Base class for all object characteristics.

#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include <memory>
#include "\qbLinAlg-main\qbVector.h"
#include "../ray.hpp"
#include "../gtfm.hpp"

namespace CMRT
{
	class MaterialBase;			// forward declared to prevent circular definitions.

	class ObjectBase
	{
	public:

		ObjectBase();

		virtual ~ObjectBase();

		virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

		void SetTransformMatrix(const CMRT::GTform &transformMatrix);

		bool CloseEnough(const double f1, const double f2);

		bool AssignMaterial(const std::shared_ptr<CMRT::MaterialBase> &objectMaterial);
		

	public:
		qbVector<double> m_baseColor	{ 3 };

		CMRT::GTform m_transformMatrix;

		std::shared_ptr<CMRT::MaterialBase> m_pMaterial;

		bool m_hasMaterial = false;

		qbVector<double> m_uvCoords	{ 2 };
	};
}


#endif // !OBJECTBASE_H
