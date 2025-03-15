// Plane class for reflections and shadows

// note: plane object is defined in its own coordinate system, centered at origin, in xy plane.

#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace CMRT
{
	class ObjPlane : public ObjectBase
	{
	public:

		ObjPlane();

		virtual ~ObjPlane() override;

		virtual bool TestIntersection(	const CMRT::Ray &castRay, 
										qbVector<double> &intPoint, 
										qbVector<double> &localNormal, 
										qbVector<double> &localColor) override;


	private:


	};
}
#endif // !OBJPLANE_H