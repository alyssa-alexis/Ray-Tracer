// Sphere methods (3 total)
#define _USE_MATH_DEFINES

#include "objsphere.hpp"
#include <cmath>


CMRT::ObjSphere::ObjSphere()
{
}

CMRT::ObjSphere::~ObjSphere()
{
}

bool CMRT::ObjSphere::TestIntersection(const CMRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{

	/* Apply Geo-Transform */

	/* done before testing because (1) the cast ray exists in the 3D world coordinate system
	and (2) the object exists in its own local coordinate system.

	we therefore can place objects anywhere in the scene with any radius we like. */

	CMRT::Ray bckRay = m_transformMatrix.Apply(castRay, CMRT::BCKTFORM);


	/* Line-Sphere Intersection */

	// direction vector of line
	qbVector<double> vhat = bckRay.m_lab;
	vhat.Normalize();

		/* note: a is the squared magnitude of the direction of the cast ray.
			Since the cast ray is a unit vector, the value of a will always be 1.0.*/

	double b = 2.0 * qbVector<double>::dot(bckRay.m_point1, vhat);

	// in this case, the dot product is the squared magnitude
	double c = qbVector<double>::dot(bckRay.m_point1, bckRay.m_point1) - 1.0;


	/* test whether intersection is real or not */
	double intTest = (b * b) - 4.0 * c;

	// find poi in local coordinate system
	qbVector<double> poi;
	if (intTest > 0.0)								// show where intersection happened
	{
		double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;

		if ((t1 < 0.0) || (t2 < 0.0))				// part of object is behind camera and ignored
		{
			return false;
		}
		else
		{
			// shading happens here
			// determine point-of-intersection closest to camera
			
			if (t1 < t2)							// t1 is closer to camera
			{
				poi = bckRay.m_point1 + (vhat * t1);			// start point + (direction * scalar)
			}
			else
			{
				poi = bckRay.m_point1 + (vhat * t2);
			}

			/*	transform local intersections back to world coordinates.
				shows where intersections actually occurred in the scene */

			intPoint = m_transformMatrix.Apply(poi, CMRT::FWDTFORM);
		
			qbVector<double> objOrigin = qbVector<double>{ std::vector<double>{0.0, 0.0, 0.0} };
			qbVector<double> newObjOrigin = m_transformMatrix.Apply(objOrigin, CMRT::FWDTFORM);
			localNormal = intPoint - newObjOrigin;
			localNormal.Normalize();

			localColor = m_baseColor;

			double x = poi.GetElement(0);
			double y = poi.GetElement(1);
			double z = poi.GetElement(2);
			double u = atan2(sqrtf(pow(x, 2.0) + pow(y, 2.0)), z);
			double v = atan2(y, x);
		
			/*if (x < 0)
				v += M_PI;*/
		
			u /= M_PI;
			v /= M_PI;

			m_uvCoords.SetElement(0, u);
			m_uvCoords.SetElement(1, v);
		
		}

		return true;
	}
	else
	{
		return false;
	}

}