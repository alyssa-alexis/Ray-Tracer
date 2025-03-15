// Camera class

#ifndef CAMERA_H
#define CAMERA_H

#include "\qbLinAlg-main\qbVector.h"
#include "../CM-RayTrace/ray.hpp"


namespace CMRT
{
	class Camera
	{
	public:
		Camera();

		void SetPosition	(const qbVector<double> &newPosition);
		void SetLookAt		(const qbVector<double> &newLookAt);
		void SetUp			(const qbVector<double> &upVector);
		void SetLength		(double newLength);							// distance between screen and camera pinhole
		void SetHorzSize	(double newSize);	
		void SetAspect		(double newAspect);
	

		qbVector<double> GetPosition();
		qbVector<double> GetLookAt();
		qbVector<double> GetUp();
		qbVector<double> GetU();
		qbVector<double> GetV();
		qbVector<double> GetScreenCenter();

		double			 GetLength();
		double			 GetHorzSize();
		double			 GetAspect();


		// floats range from -1 to 1. 0 is considered center of screen.
		bool GenerateRay(float proScreenX, float proScreenY, CMRT::Ray &cameraRay);

			// proScreenX is fraction of U vector
			// proScreenY is fraction of V vector


		void UpdateCameraGeometry();


	private:
		qbVector<double> m_cameraPosition		{ 3 };				// pinhole of camera
		qbVector<double> m_cameraLookAt			{ 3 };
		qbVector<double> m_cameraUp				{ 3 };
		
		double m_cameraLength;
		double m_cameraHorzSize;
		double m_cameraAspectRatio;

		qbVector<double> m_alignmentVector			{ 3 };			// principal camera axis
		qbVector<double> m_projectionScreenU		{ 3 };
		qbVector<double> m_projectionScreenV		{ 3 };
		qbVector<double> m_projectionScreenCenter	{ 3 };
	};
}


#endif // !CAMERA_H
