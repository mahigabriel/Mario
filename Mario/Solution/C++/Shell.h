#pragma once
#include "Character.h"

PTR( Shell );
PTR( Mario );

class Shell : public Character {
public:
	Shell( double wx, double wy );
	virtual ~Shell( );
private:
	void update( ) override;
	void overlapped( CharacterConstPtr target ) override;
private:
	void die( );
	void collapse( );
	void rebirthNokonoko( );
	void collision( );
	void overlappedWithFireball( );
	void overlappedWithShell( ShellConstPtr shell );
	void overlappedWithMario( MarioConstPtr mario );
private:
	int _rebirth;
	int _trampled;
	int _start_count;
	bool _collapse;
};

