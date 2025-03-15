// Camera methods (17 total)

#include "camera.hpp"
#include "ray.hpp"
#include <math.h>


CMRT::Camera::Camera()
{
	m_cameraPosition = qbVector<double>		{ std::vector<double> {0.0, -10.0, 0.0} };
	m_cameraLookAt = qbVector<double>		{ std::vector<double> {0.0, 0.0, 0.0} };
	m_cameraUp = qbVector<double>			{ std::vector<double> { 0.0, 0.0, 1.0} };
	m_cameraLength = 1.0;
	m_cameraHorzSize = 1.0;
	m_cameraAspectRatio = 1.0;
}


/* Camera Parameters */

void CMRT::Camera::SetPosition(const qbVector<double> &newPosition)
{
	m_cameraPosition = newPosition;
}

void CMRT::Camera::SetLookAt(const qbVector<double> &newLookAt)
{
	m_cameraLookAt = newLookAt;
}

void CMRT::Camera::SetUp(const qbVector<double> &upVector)
{
	m_cameraUp = upVector;
}

void CMRT::Camera::SetLength(double newLength)
{
	m_cameraLength = newLength;
}

void CMRT::Camera::SetHorzSize(double newHorzSize)
{
	m_cameraHorzSize = newHorzSize;
}

void CMRT::Camera::SetAspect(double newAspect)
{
	m_cameraAspectRatio = newAspect;
}


qbVector<double> CMRT::Camera::GetPosition()
{
	return m_cameraPosition;
}

qbVector<double> CMRT::Camera::GetLookAt()
{
	return m_cameraLookAt;
}

qbVector<double> CMRT::Camera::GetUp()
{
	return m_cameraUp;
}

double CMRT::Camera::GetLength()
{
	return m_cameraLength;
}

double CMRT::Camera::GetHorzSize()
{
	return m_cameraHorzSize;
}

double CMRT::Camera::GetAspect()
{
	return m_cameraAspectRatio;
}

qbVector<double> CMRT::Camera::GetU()
{
	return m_projectionScreenU;
}

qbVector<double> CMRT::Camera::GetV()
{
	return m_projectionScreenV;
}

qbVector<double> CMRT::Camera::GetScreenCenter()
{
	return m_projectionScreenCenter;
}


/* Camera Geometry */

void CMRT::Camera::UpdateCameraGeometry()
{
	m_alignmentVector = m_cameraLookAt - m_cameraPosition;
	m_alignmentVector.Normalize();

	m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
	m_projectionScreenU.Normalize();

	m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
	m_projectionScreenV.Normalize();

	m_projectionScreenCenter = m_cameraPosition + (m_cameraLength * m_alignmentVector);


	m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

bool CMRT::Camera::GenerateRay(float proScreenX, float proScreenY, CMRT::Ray &cameraRay)
{
	// note: float values range from -1 to 1

	// map UV screen coordinates to XYZ world coordinates
	qbVector<double> screenWorldPart1 = m_projectionScreenCenter + (m_projectionScreenU * proScreenX);
	qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);


	cameraRay.m_point1 = m_cameraPosition;
	cameraRay.m_point2 = screenWorldCoordinate;
	cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;

	return true;
}