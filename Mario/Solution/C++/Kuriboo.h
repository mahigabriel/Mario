#pragma once
#include "Character.h"

PTR( Kuriboo );

class Kuriboo : public Character {
public:
	Kuriboo( double wx, double wy );
	virtual ~Kuriboo( );
private:
	void update( ) override;
	void overlapped( CharacterConstPtr target ) override;
private:
	/// €–Sˆ—‚Ì•ªŠò
	void setStarDie( );
	void setDie( );
	/// €–S‰æ–ÊŠO‚É”ò‚Ño‚é
	void dropOut( );
	/// ˆÚ“®•ûŒü‚Ì”½“]
	void changeDir( );
	/// ˆÚ“®‚Ì‰æ‘œ•ÏX
	void setAnimation( );
	void marioOverlapped( CharacterConstPtr target );
	void fireballOverlapped( );
	void shellOverlapped( CharacterConstPtr target );
private:
	SystemPtr _system;
private:
	int _start_count;
	bool _collapse;
};

