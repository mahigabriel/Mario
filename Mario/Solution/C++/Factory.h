#pragma once

#include "smart_ptr.h"
#include "Character.h"

PTR( Map );
PTR( Camera );
PTR( System );
PTR( Characters );
PTR( Character );
PTR( Factory );

class Factory : public std::enable_shared_from_this< Factory > {
public:
	Factory( MapPtr map, CameraPtr camera, SystemPtr system, CharactersPtr characters );
	virtual ~Factory( );
public:
	void update( );
	void createDummy( double wx, double wy, bool gravity, bool moving, bool tall );
	void createMario( double wx, double wy );
	void createFireball( double wx, double wy, Character::DIR dir );
	void createKinoko( double wx, double wy );
	void createFlower( double wx, double wy );
	void createNokonoko( double wx, double wy );
	void createKuriboo( double wx, double wy );
	void createStar( double wx, double wy );
	void createShell( double wx, double wy );
private:
	void add( CharacterPtr character );
	void generateEnemies( const int camera_fx );
	void generateEnemy( const Character::TYPE type, const double wx, const double wy );
private:
	MapPtr _map;
	CameraPtr _camera;
	SystemPtr _system;
	CharactersPtr _characters;
	int _last_generating_fx;
};

