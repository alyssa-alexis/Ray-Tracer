// Scene class construction


#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "image.hpp"
#include "camera.hpp"
#include "./CM-Primitives/objsphere.hpp"
#include "./CM-Primitives/objplane.hpp"
#include "./CM-Primitives/cylinder.hpp"
#include "./CM-Primitives/cone.hpp"
#include "./CM-Lights/pointlight.hpp"


namespace CMRT
{
	class Scene
	{
	public:
		Scene();

		bool Render(Image& outputImage);

		bool CastRay(	CMRT::Ray &castRay, std::shared_ptr<CMRT::ObjectBase> &closestObject,
						qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
						qbVector<double> &closestLocalColor);

	// Private functions
	private:

	// Private members
	private:
		CMRT::Camera m_camera;

		std::vector<std::shared_ptr<CMRT::ObjectBase>> m_objectList;

		std::vector<std::shared_ptr<CMRT::LightBase>> m_lightList;
	};
}


#endif // !SCENE_H