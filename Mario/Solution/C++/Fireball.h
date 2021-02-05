#pragma once
#include "Character.h"

PTR( Fireball );
PTR( Map );
PTR( System );

class Fireball : public Character {
public:
	Fireball( double wx, double wy, Character::DIR dir );
	virtual ~Fireball( );
private:
	void update( ) override;
	void overlapped( CharacterConstPtr target ) override;
};

