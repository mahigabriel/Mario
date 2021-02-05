#pragma once
#include "smart_ptr.h"

PTR( Camera );
PTR( Map );
PTR( Viewer );
PTR( Character );
PTR( Characters );
PTR( System );

class Viewer {
public:
	Viewer( CameraConstPtr camera, MapConstPtr map, CharactersConstPtr characters, SystemConstPtr sysytem );
	virtual ~Viewer( );
	void draw( ) const;
private:
	void drawBackground( ) const;
	void drawObject( ) const;
	void drawCharacters( ) const;
	void drawCharacter( CharacterConstPtr character ) const;
	void drawDeadMario( ) const;
private:
	CameraConstPtr _camera;
	MapConstPtr _map;
	CharactersConstPtr _characters;
	SystemConstPtr _system;
};
