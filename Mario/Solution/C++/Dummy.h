#pragma once
#include "Character.h"

PTR( Dummy );

class Dummy : public Character {
public:
	Dummy( double wx, double wy, bool gravity, bool moving, bool tall );
	virtual ~Dummy( );
private:
	void update( ) override;
	void overlapped( CharacterConstPtr target ) override;
private:
	bool _moving;
};

