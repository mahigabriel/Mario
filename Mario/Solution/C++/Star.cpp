#include "Star.h"

const int STAR_WIDTH_LEFT_SX = 8;
const int STAR_WIDTH_RIGHT_SX = 7;
const int STAR_HEIGHT_SY = 15;
const int STAR_OX = 12;
const int STAR_OY = 7;
const double STAR_SPEED = 1.0;
const double STAR_JUMP_POWER = 5.0;

Star::Star( double wx, double wy ) {
	setType( Character::TYPE::STAR );
	setPosWX( wx );
	setPosWY( wy );
	setVecWX( STAR_SPEED );
	setDir( Character::DIR::RIGHT );
	setWidthLeftSX( STAR_WIDTH_LEFT_SX );
	setWidthRightSX( STAR_WIDTH_RIGHT_SX );
	setHeightSY( STAR_HEIGHT_SY );
	setOX( STAR_OX );
	setOY( STAR_OY );
}

Star::~Star( ) {
}

void Star::update( ) {
	SystemPtr system = getSystem( );

	int count = system->getNowCount( );
	setOX( STAR_OX + count % 4 );

	if ( isStanding( ) ) {
		setVecWY( -STAR_JUMP_POWER );
	}
	if ( isCollision( ) ) {
		if ( getVecWX( ) > 0 ) {
			setVecWX( -STAR_SPEED );
		} else {
			setVecWX( STAR_SPEED );
		}
	}
}

void Star::overlapped( CharacterConstPtr target ) {
	if ( target->getType( ) == Character::TYPE::MARIO ) {
		remove( );
	}
}
