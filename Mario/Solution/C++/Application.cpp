#include "Application.h"

Application::Application( ) {
	_camera = CameraPtr( new Camera( SCREEN_WIDTH ) );
	_characters = CharactersPtr( new Characters );

	_system = SystemPtr( new System( ) );

	MapPtr map( new Map( _factory ) );

	_factory = FactoryPtr( new Factory( map, _camera, _system, _characters ) );
	_viewer = ViewerPtr( new Viewer( _camera, map, _characters, _system ) );

	//_factory->createDummy( 50, 100, false, true, true );
	//_factory->createDummy( 100, 100, false, false, false );
	
	_factory->createMario( 120, 100 );

	_factory->createKinoko( 150, 100 );
	 
	_factory->createStar( 180, 100 );

	_factory->createFlower( 180, 100 );
}

Application::~Application( ) {
}

void Application::update( ) {
	_system->update( );

	if ( !_system->isFreezing( ) ) {
		_characters->update( );
		_factory->update( );
	}

	_camera->debugScroll( );
	_viewer->draw( );
}