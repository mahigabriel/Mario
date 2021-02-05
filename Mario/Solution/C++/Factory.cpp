#include "Factory.h"
#include "Characters.h"
#include "Character.h"
#include "Camera.h"
#include "Mario.h"
#include "Dummy.h"
#include "Fireball.h"
#include "Kinoko.h"
#include "Flower.h"
#include "Kuriboo.h"
#include "Star.h"
#include "Camera.h"
#include "Map.h"
#include "Nokonoko.h"
#include "Shell.h"

Factory::Factory( MapPtr map, CameraPtr camera, SystemPtr system, CharactersPtr characters ) :
_map( map ),
_camera( camera ),
_system( system ),
_characters( characters ),
_last_generating_fx( -Map::FIELD_ACTIVE_WIDTH ){

}

Factory::~Factory( ) {

}

void Factory::update( ) {
	int camera_fx = _camera->getSX( ) / Map::CHIP_SIZE;
	if ( camera_fx > _last_generating_fx ) {
		generateEnemies( camera_fx );
	}
	_last_generating_fx = camera_fx;
}

void Factory::generateEnemies( const int camera_fx ) {
	int far_fx = camera_fx + Map::FIELD_GENERATING_WIDTH;
	int near_fx = camera_fx;
	if ( near_fx < _last_generating_fx + Map::FIELD_GENERATING_WIDTH ) {
		near_fx = _last_generating_fx + Map::FIELD_GENERATING_WIDTH;
	}
	for ( int i = near_fx; i < far_fx; i++ ) {
		for ( int j = 0; j < Map::FIELD_HEIGHT; j++ ) {
			Character::TYPE type = _map->getEnemyType( i, j );
			double wx = i * Map::CHIP_SIZE + Map::CHIP_SIZE / 2;
			double wy = j * Map::CHIP_SIZE + Map::CHIP_SIZE / 2;
			generateEnemy( type, wx, wy );
		}
	}
}

void Factory::generateEnemy( const Character::TYPE type, const double wx, const double wy ) {
	// XV‘ÎÛ‚ª‚ ‚é‚©H
	switch ( type ) {
	case Character::TYPE::KURIBOO:
		createKuriboo( wx, wy );
		break;
	case Character::TYPE::NOKONOKO:
		createNokonoko( wx, wy );
		break;
	default:
		break;
	}
}

void Factory::createDummy( double wx, double wy, bool gravity, bool moving, bool tall ) {
	DummyPtr dummy( new Dummy( wx, wy, gravity, moving, tall ) );
	add( dummy );
}

void Factory::createMario( double wx, double wy ) {
	MarioPtr mario( new Mario( wx, wy, Mario::TYPE::DEKA ) );
	add( mario );
}

void Factory::createFireball( double wx, double wy, Character::DIR dir ) {
	FireballPtr fireball = FireballPtr( new Fireball( wx, wy, dir ) );
	add( fireball );
}

void Factory::createKinoko( double wx, double wy ) {
	KinokoPtr kinoko = KinokoPtr( new Kinoko( wx, wy ) );
	add( kinoko );
}

void Factory::createFlower( double wx, double wy ) {
	FlowerPtr flower = FlowerPtr( new Flower( wx, wy ) );
	add( flower );
}

void Factory::createStar( double wx, double wy ) {
	StarPtr star = StarPtr( new Star( wx, wy ) );
	add( star );
}

void Factory::createShell( double wx, double wy ) {
	ShellPtr shell = ShellPtr( new Shell( wx, wy ) );
	add( shell );
}

void Factory::createKuriboo( double wx, double wy ) {
	KuribooPtr kuriboo = KuribooPtr( new Kuriboo( wx, wy ) );
	add( kuriboo );
}

void Factory::createNokonoko(double wx,double wy) {
	NokonokoPtr nokonoko = NokonokoPtr( new Nokonoko( wx, wy ) );
	add( nokonoko );
}

void Factory::add( CharacterPtr character ) {
	character->_map = _map;
	character->_camera = _camera;
	character->_system = _system;
	character->_characters = _characters;
	character->_factory = shared_from_this( );
	_characters->add( character );
}



