#pragma once
#include "smart_ptr.h"
#include <array>

PTR( Characters );
PTR( Character );

class Characters {
public:
	Characters( );
	virtual ~Characters( );
	int getNum( ) const;
	CharacterConstPtr getInstance( int idx ) const;
	void add( CharacterPtr character );
	void update( );
private:
	static const int MAX_NUM = 100;
private:
	void overlapped( CharacterPtr character );
	void remove( );
private:
	int _num;
	std::array< CharacterPtr, MAX_NUM > _character;
};

