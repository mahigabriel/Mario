#pragma once
#include "smart_ptr.h"

PTR( Camera );

class Camera {
public:
	Camera( int screen_width );
	virtual ~Camera( );
public:
	void debugScroll( );
	void adjust( double pos_wx, double vec_wx );
	int getSX( ) const;
private:
	const int SCREEN_WIDTH;
	int _sx;
};