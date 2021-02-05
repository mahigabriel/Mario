#include "System.h"
#include "Camera.h"
#include "Characters.h"
#include "Factory.h"

const double GRAVITY = 0.1;

System::System( ) :
_count( 0 ) {
	_freezing = false;
	_mario_dead_wx = 0;
	_mario_dead_wy = 0;
	_mario_dead_vy = 0;
}

System::~System( ) {

}
void System::update( ) {
	_count++;
	
	if ( _freezing ) {
		_mario_dead_vy += GRAVITY;
		_mario_dead_wy += _mario_dead_vy;
	}
}
int System::getNowCount( ) const {
	return _count;
}

void System::freeze( double mario_wx, double mario_wy ) {
	_freezing = true;
	_mario_dead_wx = mario_wx;
	_mario_dead_wy = mario_wy;
	_mario_dead_vy = -5.0;
}

bool System::isFreezing( ) const {
	return _freezing;
}

double System::getMarioDeadPosWX( ) const {
	return _mario_dead_wx;
}

double System::getMarioDeadPosWY( ) const {
	return _mario_dead_wy;
}