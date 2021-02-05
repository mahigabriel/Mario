#pragma once
#include "Character.h"
#include "smart_ptr.h"
#include "System.h"

PTR( Star );
PTR( System );

class Star : public Character {
public:
	Star( double wx, double wy );
	virtual ~Star( );
public:
	void update( ) override;
	void overlapped( CharacterConstPtr target ) override;
};

