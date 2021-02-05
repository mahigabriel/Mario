#include "Camera.h"
#include "Map.h"
#include "EGL.h"

const int SCROLL_RANGE = 256 / 2;

Camera::Camera( int screen_width ) :
SCREEN_WIDTH( screen_width ),
_sx( 0 ) {
}

Camera::~Camera( ) {

}

void Camera::debugScroll( ) {
	if ( debugKeyD( false ) ) {
		_sx += 5;
	}
	if ( debugKeyA( false ) ) {
		_sx += -5;
	}

	if ( _sx < 0 ) {
		_sx = 0;
	}

	const int terminal_sx = Map::FIELD_WIDTH * Map::CHIP_SIZE - SCREEN_WIDTH;
	if ( _sx > terminal_sx ) {
		_sx = terminal_sx;
	}
}

int Camera::getSX( ) const {
	return _sx;
}

void Camera::adjust( double pos_wx, double vec_wx ) {
	if ( _sx < ( int )pos_wx - SCROLL_RANGE && vec_wx > 0 ) {
		_sx = ( int )pos_wx - SCROLL_RANGE;
	}
}