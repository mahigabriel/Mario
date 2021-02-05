#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Kinoko );

class Kinoko : public Character {
public:
	Kinoko( double wx, double wy );
	virtual ~Kinoko( );
private:
	void update( ) override;
	void overlapped( CharacterConstPtr target ) override;
};

