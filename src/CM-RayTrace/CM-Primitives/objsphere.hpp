// Sphere class construction

#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace CMRT
{
	class ObjSphere : public ObjectBase
	{
	public:
		
		ObjSphere();		//	note: this defines a unit sphere at origin

		virtual ~ObjSphere() override;

		virtual bool TestIntersection(const CMRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;


	private:


	};
}


#endif // !OBJSPHERE_H
