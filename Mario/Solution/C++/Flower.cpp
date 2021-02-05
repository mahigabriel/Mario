#include "Flower.h"

const int FLOWER_WIDTH_LEFT_SX = 8;
const int FLOWER_WIDTH_RIGHT_SX = 7;
const int FLOWER_HEIGHT_SY = 15;
const int FLOWER_OX = 12;
const int FLOWER_OY = 6;

Flower::Flower( double wx, double wy ) {
	setType( Character::TYPE::FLOWER );
	setPosWX( wx );
	setPosWY( wy );
	setWidthLeftSX( FLOWER_WIDTH_LEFT_SX );
	setWidthRightSX( FLOWER_WIDTH_RIGHT_SX );
	setHeightSY( FLOWER_HEIGHT_SY );
	setOX( FLOWER_OX );
	setOY( FLOWER_OY );
}

Flower::~Flower( ) {

}

void Flower::update( ) {

}

void Flower::overlapped( CharacterConstPtr target ) {
	if ( target->getType( ) == Character::TYPE::MARIO ) {
		remove( );
	}
}
