#include "Kinoko.h"

const int KINOKO_WIDTH_LEFT_SX = 8;
const int KINOKO_WIDTH_RIGHT_SX = 7;
const int KINOKO_HEIGHT_SY = 15;
const int KINOKO_OX = 11;
const int KINOKO_OY = 6;
const double KINOKO_SPEED = 0.5;

Kinoko::Kinoko( double wx, double wy ) {
	setType( Character::TYPE::KINOKO );
	setPosWX( wx );
	setPosWY( wy );
	setDir( Character::DIR::RIGHT );
	setWidthLeftSX( KINOKO_WIDTH_LEFT_SX );
	setWidthRightSX( KINOKO_WIDTH_RIGHT_SX );
	setHeightSY( KINOKO_HEIGHT_SY );
	setOX( KINOKO_OX );
	setOY( KINOKO_OY );
	setVecWX( KINOKO_SPEED );
}

Kinoko::~Kinoko( ) {
}

void Kinoko::update( ) {
	if ( isCollision( ) ) {
		if ( getVecWX( ) < 0 ) {
			setVecWX( KINOKO_SPEED );
		} else {
			setVecWX( -KINOKO_SPEED );
		}
	}
}

void Kinoko::overlapped( CharacterConstPtr target ) {
	if ( target->getType( ) == Character::TYPE::MARIO ) {
		remove( );
	}
}
