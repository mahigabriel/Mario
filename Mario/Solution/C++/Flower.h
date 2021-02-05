#pragma once
#include "Character.h"

PTR( Flower );

class Flower : public Character {
public:
	Flower( double wx, double wy );
	virtual ~Flower( );
private:
	void update( )override;
	void overlapped( CharacterConstPtr target )override;
};