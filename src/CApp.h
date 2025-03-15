// Window class construction

#pragma once

#ifndef CAPP_H
#define CAPP_H

#include "SDL.h"
#include "./CM-RayTrace/scene.hpp"
#include "./CM-RayTrace/camera.hpp"
#include "./CM-RayTrace/CM-Textures/flat.hpp"
#include "./CM-RayTrace/CM-Textures/checker.hpp"


class CApp
{
public:
	CApp();
	
	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event *event);
	void OnLoop();
	void OnRender();
	void OnExit();

private:
	// for debugging
	void PrintVector(const qbVector<double> &inputVector);

private:
	Image m_image;

	CMRT::Scene m_scene;

	bool isRunning;
	SDL_Window *pWindow;
	SDL_Renderer *pRenderer;
};


#endif // !CAPP_H
