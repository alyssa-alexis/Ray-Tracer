// Cylinder methods (3 total)
#define _USE_MATH_DEFINES

#include "cylinder.hpp"
#include <array>
#include <cmath>

CMRT::Cylinder::Cylinder() { }

CMRT::Cylinder::~Cylinder() { }

bool CMRT::Cylinder::TestIntersection(	const CMRT::Ray &castRay, qbVector<double> &intPoint,
										qbVector<double> &localNormal, qbVector<double> &localColor)
{
	CMRT::Ray bckRay = m_transformMatrix.Apply(castRay, CMRT::BCKTFORM);

	qbVector<double> v = bckRay.m_lab;
	v.Normalize();

	qbVector<double> p = bckRay.m_point1;

	// quadratic
	double a = std::pow(v.GetElement(0), 2.0) + std::pow(v.GetElement(1), 2.0);
	double b = 2.0 * (p.GetElement(0) * v.GetElement(0) + p.GetElement(1) * v.GetElement(1));
	double c = std::pow(p.GetElement(0), 2.0) + std::pow(p.GetElement(1), 2.0) - 1.0;

	// quadratic, top half
	double numSQRT = sqrtf(std::pow(b, 2.0) - 4 * a * c);


	// intersection tests

		// with cylinder
	std::array<qbVector<double>, 4> poi;		// 4 poi max: 2 for cylinder, 1 for each end cap
	std::array<double, 4> t;					// 4 scalars
	bool t1Valid, t2Valid, t3Valid, t4Valid;

	if (numSQRT > 0.0)
	{
		t.at(0) = (-b + numSQRT) / (2 * a);
		t.at(1) = (-b - numSQRT) / (2 * a);

		poi.at(0) = bckRay.m_point1 + (v * t[0]);
		poi.at(1) = bckRay.m_point1 + (v * t[1]);

		if ((t.at(0) > 0.0) && (fabs(poi.at(0).GetElement(2)) < 1.0))
		{
			t1Valid = true;
		}
		else
		{
			t1Valid = false;
			t.at(0) = 100e6;
		}

		if ((t.at(1) > 0.0) && (fabs(poi.at(1).GetElement(2)) < 1.0))
		{
			t2Valid = true;
		}
		else
		{
			t2Valid = false;
			t.at(1) = 100e6;
		}
	}
	else
	{
		t1Valid = false;
		t2Valid = false;
		t.at(0) = 100e6;
		t.at(1) = 100e6;
	}


		// with end caps
	if (CloseEnough(v.GetElement(2), 0.0))		// parallel to end caps
	{
		t3Valid = false;
		t4Valid = false;
		t.at(2) = 100e6;
		t.at(3) = 100e6;
	}
	else										// intersection with at least 1 end cap
	{
		t.at(2) = (bckRay.m_point1.GetElement(2) - 1.0) / -v.GetElement(2);
		t.at(3) = (bckRay.m_point1.GetElement(2) + 1.0) / -v.GetElement(2);

		poi.at(2) = bckRay.m_point1 + t.at(2) * v;
		poi.at(3) = bckRay.m_point1 + t.at(3) * v;

		if ((t.at(2) > 0.0) && (sqrtf(std::pow(poi.at(2).GetElement(0), 2.0) + std::pow(poi.at(2).GetElement(1), 2.0)) < 1.0))
		{
			t3Valid = true;
		}
		else
		{
			t3Valid = false;
			t.at(2) = 100e6;
		}

		if ((t.at(3) > 0.0) && (sqrtf(std::pow(poi.at(3).GetElement(0), 2.0) + std::pow(poi.at(3).GetElement(1), 2.0)) < 1.0))
		{
			t4Valid = true;
		}
		else
		{
			t4Valid = false;
			t.at(3) = 100e6;
		}
	}

	if ((!t1Valid) && (!t2Valid) && (!t3Valid) && (!t4Valid))
		return false;
	
		// otherwise, check for smallest valid t-value
	int minIndex = 0;
	double minValue = 10e6;
	for (int i = 0; i < 4; ++i)
	{
		if (t.at(i) < minValue)
		{
			minValue = t.at(i);
			minIndex = i;
		}
	}

		/* note: minIndex of 0 or 1 means there is a valid intersection with the cylinder itself.*/
	qbVector<double> validPOI = poi.at(minIndex);
	if (minIndex < 2)
	{
		intPoint = m_transformMatrix.Apply(validPOI, CMRT::FWDTFORM);
		
		qbVector<double> orgNormal {3};
		qbVector<double> newNormal {3};
		qbVector<double> localOrigin {std::vector<double> {0.0, 0.0, 0.0}};
		qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, CMRT::FWDTFORM);
		orgNormal.SetElement(0, validPOI.GetElement(0));
		orgNormal.SetElement(1, validPOI.GetElement(1));
		orgNormal.SetElement(2, 0.0);
		newNormal = m_transformMatrix.Apply(orgNormal, CMRT::FWDTFORM) - globalOrigin;
		newNormal.Normalize();
		localNormal = newNormal;
		
		localColor = m_baseColor;

		double x = validPOI.GetElement(0);
		double y = validPOI.GetElement(1);
		double z = validPOI.GetElement(2);
		double u = atan2(y, x) / M_PI;
		double v = z;

		m_uvCoords.SetElement(0, u);
		m_uvCoords.SetElement(1, v);
		
		return true;
	}
	else
	{
		// check endcaps
		if (!CloseEnough(v.GetElement(2), 0.0))
		{
			// are we inside the disk?
			if (sqrtf(std::pow(validPOI.GetElement(0), 2.0) + std::pow(validPOI.GetElement(1), 2.0)) < 1.0)
			{
				intPoint = m_transformMatrix.Apply(validPOI, CMRT::FWDTFORM);

				qbVector<double> localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
				qbVector<double> normalVector{ std::vector<double> {0.0, 0.0, 0.0 + validPOI.GetElement(2)} };		// sets local normal to +1 or -1 depending on z-of-validPOI
				qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, CMRT::FWDTFORM);

				localNormal = m_transformMatrix.Apply(normalVector, CMRT::FWDTFORM) - globalOrigin;
				localNormal.Normalize();

				localColor = m_baseColor;

				double x = validPOI.GetElement(0);
				double y = validPOI.GetElement(1);
				double z = validPOI.GetElement(2);		// just in case

				m_uvCoords.SetElement(0, x);
				m_uvCoords.SetElement(1, y);

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