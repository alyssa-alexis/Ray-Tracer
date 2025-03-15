// Cylinder class construction

#ifndef CYLINDER_H
#define CYLINDER_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace CMRT 
{
	class Cylinder : public ObjectBase
	{
		public:

			Cylinder();

			virtual ~Cylinder() override;

			virtual bool TestIntersection(	const CMRT::Ray &castRay, 
											qbVector<double> &intPoint, 
											qbVector<double> &localNormal,
											qbVector<double> &localColor) override;
	};

}

#endif // !CYLINDER_H
