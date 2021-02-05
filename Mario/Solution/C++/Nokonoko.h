#pragma once
#include "Character.h"

PTR( Nokonoko );
PTR( Mario );
PTR( Shell );

class Nokonoko : public Character {
public:
	Nokonoko( double wx, double wy );
	virtual ~Nokonoko( );
private:
	void update( ) override;
	void overlapped( CharacterConstPtr target ) override;
private:
	void die( );
	void anim( );
	void move( );
	void overlappedWithMario( MarioConstPtr mario );
	void overlappedWithFireball( );
	void overlappedWithShell( ShellConstPtr shell );
private:
	int _start_count;
	bool _collapse;
};

