// Base class methods that all subsequent objects will inherit. (6 total)

#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

CMRT::ObjectBase::ObjectBase()
{ 
}

CMRT::ObjectBase::~ObjectBase()
{ 
}

bool CMRT::ObjectBase::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	// inheritors will overwrite, so false is ok.
	return false;
}

void CMRT::ObjectBase::SetTransformMatrix(const CMRT::GTform &transformMatrix)
{
	m_transformMatrix = transformMatrix;
}

bool CMRT::ObjectBase::AssignMaterial(const std::shared_ptr<CMRT::MaterialBase> &objectMaterial)
{
	m_pMaterial = objectMaterial;
	m_hasMaterial = true;
	return m_hasMaterial;
}

bool CMRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}