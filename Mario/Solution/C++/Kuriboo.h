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
	/// 死亡時処理の分岐
	void setStarDie( );
	void setDie( );
	/// 死亡時画面外に飛び出る
	void dropOut( );
	/// 移動方向の反転
	void changeDir( );
	/// 移動時の画像変更
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

