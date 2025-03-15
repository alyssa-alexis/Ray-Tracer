// Cone class construction

#ifndef CONE_H
#define CONE_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace CMRT
{
	class Cone : public ObjectBase
	{
	public:

		Cone();

		virtual ~Cone() override;

		virtual bool TestIntersection(	const CMRT::Ray& castRay,
										qbVector<double>& intPoint,
										qbVector<double>& localNormal,
										qbVector<double>& localColor) override;
	};
}

#endif // !CONE_H