#pragma once
#include "smart_ptr.h"

PTR( System );

class System {
public:
	System( );
	virtual ~System( );
	void update( );
	int getNowCount( ) const;
	void freeze( double mario_wx, double mario_wy );
	bool isFreezing( ) const;
	double getMarioDeadPosWX( ) const;
	double getMarioDeadPosWY( ) const;
private:
	int _count;
	bool _freezing;
	double _mario_dead_wx;
	double _mario_dead_wy;
	double _mario_dead_vy;
};

