// Point-Light methods (3 total)

#include "pointlight.hpp"

CMRT::PointLight::PointLight()
{
	m_color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_intensity = 1.0;

	// note: qbVector class sets default location as origin, so m_location not needed
}


CMRT::PointLight::~PointLight()
{
}


bool CMRT::PointLight::ComputeIllumination(	const qbVector<double> &intPoint,
											const qbVector<double> &localNormal,
											const std::vector<std::shared_ptr<CMRT::ObjectBase>> &objectList,
											const std::shared_ptr<CMRT::ObjectBase> &currentObject,
											qbVector<double> &color,
											double &intensity)
{
	/* Math Implementation */
	
	// 1 - Construct a vector pointing from intPoint to the point-light
	qbVector<double> lightDir = (m_location - intPoint).Normalized();
	double lightDist = (m_location - intPoint).norm();

	// 2 - Compute a starting point	(for making other shapes)
	qbVector<double> startPoint = intPoint;

	// 3 - Construct a ray from poi to the light
	CMRT::Ray lightRay(startPoint, startPoint + lightDir);

		// 3.1 - check for intersections with all objects in scene -- except current one
	qbVector<double> poi		{ 3 };
	qbVector<double> poiNormal	{ 3 };
	qbVector<double> poiColor	{ 3 };
	bool validInt = false;

	for (auto sceneObject : objectList)
	{
		if (sceneObject != currentObject)
		{
			validInt = sceneObject->TestIntersection(lightRay, poi, poiNormal, poiColor);

			if (validInt)
			{
				double dist = (poi - startPoint).norm();
				if (dist > lightDist)
					validInt = false;
			}
		}
		
		if (validInt)
			break;
	}

		// 3.2 - If no objects cast a shadow from this light source, continue calculating illumination.
	if (!validInt)
	{
		double angle = acos(qbVector<double>::dot(localNormal, lightDir));

			// normal points away from light
		if (angle > 1.5708)
		{
			color = m_color;
			intensity = 0.0;
			return false;
		}
		else
		{
			color = m_color;
			intensity = m_intensity * (1.0 - (angle / 1.5708));
			return true;
		}
	}
	else
	{
		// invalid intersection -> shadows
		color = m_color;
		intensity = 0.0;
		return false;
	}
}