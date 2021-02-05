#include "Kuriboo.h"
#include "System.h"
#include "Mario.h"

const int KURIBOO_WIDTH_LEFT_SX = 8;
const int KURIBOO_WIDTH_RIGHT_SX = 7;
const int KURIBOO_HEIGHT_SY = 15;
const int KURIBOO_OX = 9;
const int KURIBOO_OY = 5;
const double KURIBOO_SPEED = 0.5;
const int DATA_COLLAPSE = 0;
const int DATA_START_COUNT = 1;
const int TRUE = 1;
const int FALSE = 0;
const int COLLAPSE_TIME = 30;

Kuriboo::Kuriboo( double wx, double wy ) {
	setType( Character::TYPE::KURIBOO );
	setPosWX( wx );
	setPosWY( wy );
	setWidthLeftSX( KURIBOO_WIDTH_LEFT_SX );
	setWidthRightSX( KURIBOO_WIDTH_RIGHT_SX );
	setHeightSY( KURIBOO_HEIGHT_SY );
	setOX( KURIBOO_OX );
	setOY( KURIBOO_OY );
	_collapse = false;
	_start_count = 0;
}

Kuriboo::~Kuriboo( ) {
}

void Kuriboo::update( ) {
	_system = getSystem( );

	if ( _collapse ) {
		dropOut( );
		return;
	}

	changeDir( );
	setAnimation( );
}

void Kuriboo::overlapped( CharacterConstPtr target ) {
	switch ( target->getType( ) ) {
	case Character::TYPE::MARIO :
	{
		marioOverlapped( target );
		break;
	}
	case Character::TYPE::FIREBALL:
		fireballOverlapped( );
		break;
	case Character::TYPE::SHELL:
		shellOverlapped( target );
		break;
	default:
		break;
	}
}

void Kuriboo::setStarDie( ) {
	_collapse = true;
	_start_count = _system->getNowCount( );

	turnUpsideDown( );
}

void Kuriboo::setDie( ) {
	_collapse = true;
	_start_count = _system->getNowCount( );

	setOX( KURIBOO_OX + 2 );
	setGravityWY( 0 );
	setVecWX( 0 );
	setVecWY( 0 );
}

void Kuriboo::dropOut( ) {
	int count = _system->getNowCount( ) - _start_count;
	setInvisible( true );
	if ( count > COLLAPSE_TIME ) {
		remove( );
	}
}

void Kuriboo::changeDir( ) {
	if ( isCollision( ) ) {
		if ( getDir( ) == Character::DIR::RIGHT ) {
			setDir( Character::DIR::LEFT );
		} else {
			setDir( Character::DIR::RIGHT );
		}
	}

	if ( getDir( ) == Character::DIR::RIGHT ) {
		setVecWX( KURIBOO_SPEED );
	} else {
		setVecWX( -KURIBOO_SPEED );
	}
}

void Kuriboo::setAnimation( ) {
	int pattern = _system->getNowCount( ) / 10 % 2;
	setOX( KURIBOO_OX + pattern );
}

void Kuriboo::marioOverlapped( CharacterConstPtr target ) {
	MarioConstPtr mario = std::dynamic_pointer_cast< const Mario >( target );

	if ( mario->isStaring( ) ) {
		setStarDie( );
		return;
	}

	if ( getPosWY( ) > target->getPosWY( ) ) {
		setDie( );
		return;
	}
}

void Kuriboo::fireballOverlapped( ) {
	setStarDie( );
}

void Kuriboo::shellOverlapped( CharacterConstPtr target ) {
	if ( target->getVecWX( ) != 0 ) {
		_collapse = true;
		_start_count = _system->getNowCount( );
	}
}
