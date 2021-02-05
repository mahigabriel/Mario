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
	/// ���S�������̕���
	void setStarDie( );
	void setDie( );
	/// ���S����ʊO�ɔ�яo��
	void dropOut( );
	/// �ړ������̔��]
	void changeDir( );
	/// �ړ����̉摜�ύX
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

