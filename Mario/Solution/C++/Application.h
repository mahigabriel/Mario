#pragma once
#include "Viewer.h"
#include "Camera.h"
#include "Map.h"
#include "System.h"
#include "Characters.h"
#include "Dummy.h"
#include "Mario.h"
#include "Factory.h"
#include "smart_ptr.h"

PTR( Application );

class Application {
public:
	Application( );
	virtual ~Application( );
public:
	void update( );
public:
	static const int SCREEN_WIDTH = 256;
	static const int SCREEN_HEIGHT = 220;
private:
	ViewerPtr _viewer;
	SystemPtr _system;
	FactoryPtr _factory;
	CharactersPtr _characters;
	CameraPtr _camera;
};

