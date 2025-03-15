// Scene methods (3 total)

#include "scene.hpp"
#include "./CM-Materials/simplematerial.hpp"
#include "./CM-Textures/checker.hpp"

CMRT::Scene::Scene()
{
	m_camera.SetPosition(qbVector<double>{std::vector<double> {2.0, -5.0, -2.0}});
	m_camera.SetLookAt(qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}});
	m_camera.SetUp(qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}});
	m_camera.SetHorzSize(0.75);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();


	auto floorTexture = std::make_shared<CMRT::Texture::Checker>(CMRT::Texture::Checker());
	auto coneTexture = std::make_shared<CMRT::Texture::Checker>(CMRT::Texture::Checker());
	
	floorTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
												  0.0,
												  qbVector<double>{std::vector<double>{16.0, 16.0}});

	coneTexture->SetColor(qbVector<double>{std::vector<double>{0.0, 0.6, 0.3}}, qbVector<double>{std::vector<double>{0.9, 0.9, 0.0}});
	coneTexture->SetTransform(qbVector<double>{	std::vector<double>{0.0, 0.0}},
													0.0,
													qbVector<double>{std::vector<double>{4.0*M_PI, 4.0}});


	auto silverMetal = std::make_shared<CMRT::SimpleMaterial> (CMRT::SimpleMaterial());
	auto goldMetal = std::make_shared<CMRT::SimpleMaterial>(CMRT::SimpleMaterial());
	auto blueDiffuse = std::make_shared<CMRT::SimpleMaterial>	(CMRT::SimpleMaterial());
	auto floorMaterial = std::make_shared<CMRT::SimpleMaterial> (CMRT::SimpleMaterial());
	auto wallMaterial = std::make_shared<CMRT::SimpleMaterial>(CMRT::SimpleMaterial());

	silverMetal -> m_baseColor = qbVector<double>{ std::vector<double>{0.5, 0.5, 0.8} };
	silverMetal -> m_reflectivity = 0.5;
	silverMetal -> m_shininess = 20.0;

	goldMetal -> m_baseColor = qbVector<double>{ std::vector<double>{0.8, 0.8, 0.8} };
	goldMetal -> m_reflectivity = 0.25;
	goldMetal -> m_shininess = 20.0;
	goldMetal -> AssignTexture(coneTexture);

	blueDiffuse -> m_baseColor = qbVector<double>{ std::vector<double> {0.3, 0.5, 0.8} };
	blueDiffuse -> m_reflectivity = 0.05;
	blueDiffuse -> m_shininess = 5.0;

	floorMaterial -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
	floorMaterial -> m_reflectivity = 0.5;
	floorMaterial -> m_shininess = 0.0;
	floorMaterial -> AssignTexture(floorTexture);

	wallMaterial -> m_baseColor = qbVector<double>{ std::vector<double>{0.8, 0.8, 0.8} };
	wallMaterial->m_reflectivity = 0.25;
	wallMaterial -> m_shininess = 0.0;


	auto sphere = std::make_shared<CMRT::ObjSphere>(CMRT::ObjSphere());
	sphere->SetTransformMatrix(CMRT::GTform{	qbVector<double>{std::vector<double>{1.5, 0.0, -0.5}},
												qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}} });
	sphere -> AssignMaterial(blueDiffuse);


	auto floor = std::make_shared<CMRT::ObjPlane>(CMRT::ObjPlane());
	floor -> SetTransformMatrix(CMRT::GTform{	qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
												qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												qbVector<double>{std::vector<double>{16.0,16.0,1.0}} });
	floor -> AssignMaterial(floorMaterial);


	auto leftWall = std::make_shared<CMRT::ObjPlane>(CMRT::ObjPlane());
	leftWall -> SetTransformMatrix(CMRT::GTform{	qbVector<double>{std::vector<double>{-4.0, 0.0, 0.0}},
													qbVector<double>{std::vector<double>{0.0, -M_PI / 2.0, -M_PI / 2.0}},
													qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}} });
	leftWall -> AssignMaterial(wallMaterial);

	auto backWall = std::make_shared<CMRT::ObjPlane>(CMRT::ObjPlane());
	backWall -> SetTransformMatrix(CMRT::GTform{	qbVector<double>{std::vector<double>{0.0, 4.0, 0.0}},
													qbVector<double>{std::vector<double>{-M_PI / 2.0, 0.0, 0.0}},
													qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}} });
	backWall -> AssignMaterial(wallMaterial);


	auto cylinder = std::make_shared<CMRT::Cylinder>(CMRT::Cylinder());
	cylinder -> SetTransformMatrix(CMRT::GTform{	qbVector<double>{std::vector<double>{-1.0, -2.0, 0.0}},
													qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
													qbVector<double>{std::vector<double>{0.25, 0.25, 1.0}} });
	cylinder -> AssignMaterial(silverMetal);

	auto cone = std::make_shared<CMRT::Cone>(CMRT::Cone());
	cone->SetTransformMatrix(CMRT::GTform{ qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
													qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
													qbVector<double>{std::vector<double>{0.25, 0.25, 1.0}} });
	cone->AssignMaterial(goldMetal);


	m_objectList.push_back(sphere);
	m_objectList.push_back(floor);
	m_objectList.push_back(leftWall);
	m_objectList.push_back(backWall);
	m_objectList.push_back(cylinder);
	m_objectList.push_back(cone);
	

	m_lightList.push_back(std::make_shared<CMRT::PointLight> (CMRT::PointLight()));
	m_lightList.at(0)->m_location = qbVector<double>{ std::vector<double> {3.0, -10.0, -5.0} };
	m_lightList.at(0)->m_color = qbVector<double>{ std::vector<double>	  {1.0, 1.0, 1.0} };

	m_lightList.push_back(std::make_shared<CMRT::PointLight> (CMRT::PointLight()));
	m_lightList.at(1)->m_location = qbVector<double>{ std::vector<double> {0.0, -10.0, -5.0} };
	m_lightList.at(1)->m_color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };

	m_lightList.push_back(std::make_shared<CMRT::PointLight>(CMRT::PointLight()));
	m_lightList.at(2)->m_location = qbVector<double>{ std::vector<double> {-2.0, 2.0, 0.0} };
	m_lightList.at(2)->m_color = qbVector<double>{ std::vector<double> {1.0, 0.8, 0.8} };
	m_lightList.at(2)->m_intensity = 0.5;

	m_lightList.push_back(std::make_shared<CMRT::PointLight>(CMRT::PointLight()));
	m_lightList.at(3)->m_location = qbVector<double>{ std::vector<double> {4.0, 2.0, 0.0} };
	m_lightList.at(3)->m_color = qbVector<double>{ std::vector<double> {1.0, 0.8, 0.8} };		
	m_lightList.at(3)->m_intensity = 0.5;
}


bool CMRT::Scene::Render(Image &outputImage)
{
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();


	CMRT::Ray cameraRay;
	qbVector<double> intPoint		{ 3 };
	qbVector<double> localNormal	{ 3 };
	qbVector<double> localColor		{ 3 };

		// precalculate multiplication factors to keep the scaling loops as simple as possible
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;

	for (int y = 0; y < ySize; ++y)
	{
		std::cout << "Processing line: " << y << " of " << ySize << "." << " \r";
		std::cout.flush();

		for (int x = 0; x < xSize; ++x)
		{
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;

			m_camera.GenerateRay(normX, normY, cameraRay);

			std::shared_ptr<CMRT::ObjectBase> closestObject;
			qbVector<double> closestIntPoint	{ 3 };
			qbVector<double> closestLocalNormal	{ 3 };
			qbVector<double> closestLocalColor	{ 3 };

			bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

			if (intersectionFound)
			{
				if (closestObject -> m_hasMaterial)
				{
					CMRT::MaterialBase::m_reflectionRayCount = 0;
					qbVector<double> color = closestObject -> m_pMaterial -> ComputeColor(	m_objectList, m_lightList,
																							closestObject, closestIntPoint,
																							closestLocalNormal, cameraRay);
					
					outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					qbVector<double> matColor = CMRT::MaterialBase::ComputeDiffuseColor(	m_objectList, m_lightList, 
																							closestObject, closestIntPoint, 
																							closestLocalNormal, closestObject->m_baseColor);

					outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
		}
	}
	
	std::cout << std::endl;
	return true;
}


bool CMRT::Scene::CastRay(	CMRT::Ray &castRay, std::shared_ptr<CMRT::ObjectBase> &closestObject,
							qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
							qbVector<double> &closestLocalColor)
{
	qbVector<double> intPoint		{ 3 };
	qbVector<double> localNormal	{ 3 };
	qbVector<double> localColor		{ 3 };

	double minDist = 1e6;
	bool intersectionFound = false;

	for (auto& currentObject : m_objectList)
	{
		bool validInt = currentObject->TestIntersection(castRay, intPoint, localNormal, localColor);

		if (validInt)
		{
			intersectionFound = true;

			// compute distance between camera and point-of-intersection
			double dist = (intPoint - castRay.m_point1).norm();

			// if object is closer to camera than any objects seen before, then store a reference to it.
			if (dist < minDist)
			{
				minDist = dist;
				closestObject = currentObject;
				closestIntPoint = intPoint;
				closestLocalNormal = localNormal;
				closestLocalColor = localColor;
			}
		}
	}

	return intersectionFound;
}