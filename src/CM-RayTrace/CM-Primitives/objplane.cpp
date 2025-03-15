// Plane methods (3 total)
// goal is to construct a unit plane, as opposed to an infinite one


#include "objplane.hpp"
#include <cmath>

CMRT::ObjPlane::ObjPlane()
{
}

CMRT::ObjPlane::~ObjPlane()
{
}

bool CMRT::ObjPlane::TestIntersection(const CMRT::Ray& castRay,
	qbVector<double>& intPoint,
	qbVector<double>& localNormal,
	qbVector<double>& localColor)
{
	CMRT::Ray bckRay = m_transformMatrix.Apply(castRay, CMRT::BCKTFORM);

	qbVector<double> k = bckRay.m_lab;
	k.Normalize();

	// check that castRay is not parallel to the plane
	if (!CloseEnough(k.GetElement(2), 0.0))						// there is an intersection
	{
		double t = bckRay.m_point1.GetElement(2) / -k.GetElement(2);
				
		if (t > 0.0)											// intersection is behind the camera and ignored
		{
			double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
			double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1) * t);
						
			if ((abs(u) < 1.0) && (abs(v) < 1.0))				// intersection is within the plane
			{
				qbVector<double> poi = bckRay.m_point1 + (t * k);

				intPoint = m_transformMatrix.Apply(poi, CMRT::FWDTFORM);

				qbVector<double> localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
				qbVector<double> normalVector{ std::vector<double>{0.0, 0.0, -1.0} };
				qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, CMRT::FWDTFORM);
				localNormal = m_transformMatrix.Apply(normalVector, CMRT::FWDTFORM) - globalOrigin;
				localNormal.Normalize();

				localColor = m_baseColor;

				m_uvCoords.SetElement(0, u);
				m_uvCoords.SetElement(1, v);

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	
	return false;
}