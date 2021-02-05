#include "Fireball.h"
#include "System.h"

const int FIREBALL_WIDTH_LEFT_SX = 4;
const int FIREBALL_WIDTH_RIGHT_SX = 4;
const int FIREBALL_HEIGHT_SY = 8;
const int FIREBALL_OX = 12;
const int FIREBALL_OY = 10;
const int FIREBALL_PATTERN_NUM = 4;
const int FIREBALL_PATTERN_PITCH = 5;
const double FIREBALL_BOUNDING_POWER = 2.0;
const double FIREBALL_GRAVITY = 0.1;
const double FIREBALL_MAX_VEC_WY = 2;


Fireball::Fireball( double wx, double wy, Character::DIR dir ) {
	setType( Character::TYPE::FIREBALL );
	setDir( dir );
	setPosWX( wx );
	setPosWY( wy );
	if ( dir == Character::DIR::RIGHT ) {
		setVecWX( 1.0 );
	} else {
		setVecWX( -1.0 );
	}
	setVecWY( FIREBALL_MAX_VEC_WY );
	setGravityWY( FIREBALL_GRAVITY );
	setWidthLeftSX( FIREBALL_WIDTH_LEFT_SX );
	setWidthRightSX( FIREBALL_WIDTH_RIGHT_SX );
	setHeightSY( FIREBALL_HEIGHT_SY );
	setOX( FIREBALL_OX );
	setOY( FIREBALL_OY );

}

Fireball::~Fireball( ) {

}

void Fireball::update( ) {
	SystemPtr system = getSystem( );
	int pattern = ( system->getNowCount( ) / FIREBALL_PATTERN_PITCH ) % FIREBALL_PATTERN_NUM;
	setOX( FIREBALL_OX + pattern ); // 0,1,2,3

	if ( isStanding( ) ) {
		setVecWY( -FIREBALL_BOUNDING_POWER );
	}
	if ( getVecWY( ) > FIREBALL_MAX_VEC_WY ) {
		setVecWY( FIREBALL_MAX_VEC_WY );
	}
	if ( isCollision( ) ) {
		remove( );
	}
}

void Fireball::overlapped( CharacterConstPtr target ) {
	switch ( target->getType( ) ) {
	case Character::TYPE::KURIBOO:
	case Character::TYPE::NOKONOKO:
	case Character::TYPE::SHELL:
		remove( );
		break;
	}
}
