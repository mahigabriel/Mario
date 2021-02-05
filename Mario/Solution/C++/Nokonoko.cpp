#include "Nokonoko.h"
#include "System.h"
#include "Factory.h"
#include "Mario.h"
#include "Shell.h"

const int NOKONOKO_WIDTH_LEFT_SX = 8;
const int NOKONOKO_WIDTH_RIGHT_SX = 7;
const int NOKONOKO_HEIGHT_SY = 20;
const int NOKONOKO_OX = 14;
const int NOKONOKO_OY = 4;
const double NOKONOKO_SPEED = 0.5;
const int DATA_COLLAPSE = 0;
const int DATA_START_COUNT = 1;
const int COLLAPSE_TIME = 30;

const int SHELL_WIDTH_LEFT_SX = 8;
const int SHELL_WIDTH_RIGHT_SX = 7;
const int SHELL_HEIGHT_SY = 20;
const int SHELL_OX = 10;
const int SHELL_OY = 4;

Nokonoko::Nokonoko( double wx, double wy ) {
	setType( Character::TYPE::NOKONOKO );
	setPosWX( wx );
	setPosWY( wy );
	setWidthLeftSX( NOKONOKO_WIDTH_LEFT_SX );
	setWidthRightSX( NOKONOKO_WIDTH_RIGHT_SX );
	setHeightSY( NOKONOKO_HEIGHT_SY );
	setOX( NOKONOKO_OX );
	setOY( NOKONOKO_OY );
	setTall( true );

	_start_count = 0;
	_collapse = false;
}

Nokonoko::~Nokonoko( ) {
}

void Nokonoko::update( ) {
	move( );
	anim( );
}

void Nokonoko::overlapped( CharacterConstPtr target ) {

	switch ( target->getType( ) ) {
	case Character::TYPE::MARIO:
		overlappedWithMario( std::dynamic_pointer_cast< const Mario >( target ) );
		break;
	case Character::TYPE::FIREBALL:
		overlappedWithFireball( );
		break;
	case Character::TYPE::SHELL:
		overlappedWithShell( std::dynamic_pointer_cast< const Shell > ( target ) );
		break;
	}
}

void Nokonoko::die( ) {
	SystemPtr system = getSystem( );

	setOX( SHELL_OX );
	setOY( SHELL_OY );
	setHeightSY( SHELL_HEIGHT_SY );
	setWidthLeftSX( SHELL_WIDTH_LEFT_SX );
	setWidthRightSX( SHELL_WIDTH_RIGHT_SX );
	setTall( false );

	turnUpsideDown( );
	setInvisible( true );

	_collapse = true;
	_start_count = system->getNowCount( );
}

void Nokonoko::anim( ) {
	if ( _collapse ) {
		SystemPtr system = getSystem( );
		int count = system->getNowCount( ) - _start_count;
		if ( count > COLLAPSE_TIME ) {
			remove( );
		}
	} else {
		SystemPtr system = getSystem( );
		int pattern = NOKONOKO_OX + system->getNowCount( ) / 10 % 2;
		setOX( pattern );
	}
}

void Nokonoko::move( ) {
	if ( isCollision( ) ) {
		if ( getDir( ) == Character::DIR::RIGHT ) {
			setDir( Character::DIR::LEFT );
		} else {
			setDir( Character::DIR::RIGHT );
		}
	}

	if ( getDir( ) == Character::DIR::RIGHT ) {
		setVecWX( NOKONOKO_SPEED );
	} else {
		setVecWX( -NOKONOKO_SPEED );
	}
}

void Nokonoko::overlappedWithMario( MarioConstPtr mario ) {
	if ( mario->isStaring( ) ) {
		die( );
	} else if ( getPosWY( ) > mario->getPosWY( ) ) {
		remove( );
		FactoryPtr factory = getFactory( );
		factory->createShell( getPosWX( ), getPosWY( ) );
	}
}

void Nokonoko::overlappedWithFireball( ) {
	die( );
}

void Nokonoko::overlappedWithShell( ShellConstPtr shell ) {
	if ( shell->getVecWX( ) != 0 ) {
		die( );
	}
}