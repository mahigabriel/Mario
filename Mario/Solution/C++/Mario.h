#pragma once
#include "Character.h"

PTR( Mario );
PTR( Character );

class Mario : public Character {
public:
	enum class TYPE {
		CHIBI,
		DEKA,
		FIRE,
		TO_DEKA,
		TO_FIRE,
		TO_CHIBI,
	};
public:
	Mario( double wx, double wy, TYPE type );
	virtual ~Mario( );
public:
	bool isStaring( ) const;
	bool isInvincible( ) const;
	bool isBig( ) const;
private:
	void update( ) override;
	void overlapped( CharacterConstPtr target ) override;
private:
	void adjustCamera( );
	void shootFireball(  );
	void move( );
	void updateGravity( );
	void jump( );
	void setJumpPower( );
	void squat( );
	bool setAccordingToType( );
	void fallIntoHole( );
	void hitEnemy( CharacterConstPtr target );
private:
	int _start_count;
	int _star_count;
	int _invincible_count;
	TYPE _type;
	bool _squat;
	bool _jumping;
	bool _staring;
	bool _invincible;
	double _max_speed;
};
