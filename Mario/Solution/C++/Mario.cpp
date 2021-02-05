#include "Mario.h"
#include "EGL.h"
#include "Map.h"
#include "Camera.h"
#include "System.h"
#include "Factory.h"
#include "Nokonoko.h"
//
//定数
//

const int MARIO_SMALL_WIDTH_LEFT_SX = 6;
const int MARIO_SMALL_WIDTH_RIGHT_SX = 5;
const int MARIO_SMALL_HEIGHT_SY = 15;
const int MARIO_BIG_WIDTH_LEFT_SX = 7;
const int MARIO_BIG_WIDTH_RIGHT_SX = 6;
const int MARIO_BIG_HEIGHT_SY = 31;
const int MARIO_SQUAT_HEIGHT_SY = 14;
const int MARIO_DASH_WIDTH_EXPANSION = 8;
const int MARIO_WAIT_OX = 0;
const int MARIO_JUMP_OX = 5;
const int MARIO_WALK_OX[ 4 ] = { 1, 2, 3, 2 };
const int MARIO_CHIBI_OY = 4;
const int MARIO_DEKA_OY = 0;
const int MARIO_FIRE_OY = 2;
const int MARIO_GROW_OX = 9;
const int MARIO_GROW_OY = 0;
const int MARIO_CHIBI_OX = 4;
const int MARIO_ABSENT_OX = 15;
const int MARIO_SWIM_OX = 13;
const double FLOAT_ACCEL = 0.02;
const double STAND_ACCEL = 0.04;
const int MAX_WALK_SPEED = 1;
const int MAX_DASH_SPEED = 2;
const double GRAVITY_FALL_POWER = 0.2;
const double GRAVITY_JUMP_POWER = 0.02;
const double MAX_FALL_SPEED = 8.0;
const double JUMP_MIN_POWER = 1.9;
const double JUMP_MAX_POWER = 2.1;
const double JUMP_VY_LIMIT = -1.0;
const int STAR_COUNT = 300;
const int INVINCIBLE_COUNT = 120;
const int FALSE = 0;
const int TRUE = 1;
const int GROW_COUNT = 60;
const int DEADLINE = Map::CHIP_SIZE * Map::FIELD_HEIGHT;

//
//パブリック関数
//

Mario::Mario( double wx, double wy, TYPE type ) {
	setType( Character::TYPE::MARIO );
	setPosWX( wx );
	setPosWY( wy );
	setOX( MARIO_WAIT_OX );

	_type = type;
	_start_count = 0;
	_star_count = -STAR_COUNT;
	_invincible_count = -INVINCIBLE_COUNT;
	_squat = false;
	_jumping = false;
	_staring = false;
	_invincible = false;
	_max_speed = 0;
}

Mario::~Mario( ) {

}

void Mario::update( ) {
	if ( !setAccordingToType( ) ) {
		return;
	}
	adjustCamera( );
	shootFireball( );
	move( );
	jump( );
	updateGravity( );
	squat( );
	fallIntoHole( );
}

void Mario::adjustCamera( ) {
	CameraPtr camera = getCamera( );
	camera->adjust( getPosWX( ), getVecWX( ) );
}

void Mario::overlapped( CharacterConstPtr target ) {
	SystemPtr system = getSystem( );

	switch ( target->getType( ) ) {
	case Character::TYPE::KINOKO:
		if ( _type == TYPE::CHIBI ) {
			_type = TYPE::TO_DEKA;
			_start_count = system->getNowCount( );
		}
		break;
	case Character::TYPE::FLOWER:
		if ( _type == TYPE::CHIBI ) {
			_type = TYPE::TO_DEKA;
			_start_count = system->getNowCount( );
		} else if ( _type == TYPE::DEKA ) {
			_type = TYPE::TO_FIRE;
			_start_count = system->getNowCount( );
		}
		break;
	case Character::TYPE::STAR:
		_star_count = system->getNowCount( );
		_staring = true;
		break;
	case Character::TYPE::KURIBOO:
	case Character::TYPE::NOKONOKO:
	case Character::TYPE::SHELL:
		hitEnemy( target );
		break;
	default:
		break;
	}
}

bool Mario::isStaring( ) const {
	return _staring;
}

bool Mario::isInvincible( ) const {
	return _invincible;
}

bool Mario::isBig( ) const {
	return
		_type == TYPE::DEKA ||
		_type == TYPE::FIRE;
}

//
//インナー関数

void Mario::squat(  ) {
	if ( _type == TYPE::CHIBI ) {
		_squat = false;
		return;
	}
	if ( !isStanding( ) ) {
		return;
	}

	if ( isArrowDown( false ) ) {
		_squat = true;
	} else {
		int head_fx = ( int )( getPosWX( ) ) / Map::CHIP_SIZE;
		int head_fy = ( int )( getPosWY( ) - getHeightSY( ) ) / Map::CHIP_SIZE - 1;
		MapConstPtr map = getMap( );
		Map::OBJECT head_type = map->getObjectType( head_fx, head_fy );
		if ( head_type == Map::OBJECT::NONE ) {
			_squat = false;
		}
	}

	if ( _squat ) {
		setOX( 6 );
		setHeightSY( MARIO_SQUAT_HEIGHT_SY );
	} else {
		setHeightSY( MARIO_BIG_HEIGHT_SY );
	}
}

void Mario::jump(  ) {
	if ( !isButtonA( false ) || getVecWY( ) > JUMP_VY_LIMIT ) {
		_jumping = false;
	}
	if ( isButtonA( true ) && isStanding( ) ) {
		setJumpPower( );
	}
}

void Mario::setJumpPower(  ) {
	double jump_power = JUMP_MIN_POWER;
	double range = MAX_DASH_SPEED - MAX_WALK_SPEED;
	double over = getVecWX( );
	if ( over < 0 ) {
		over *= -1;
	}
	over -= MAX_WALK_SPEED;
	if ( over > 0 ) {
		jump_power += ( JUMP_MAX_POWER - JUMP_MIN_POWER ) * over / range;
	}
	setVecWY( -jump_power );
	_jumping = true;
	if ( !isArrowDown( false ) ) {
		setOX( MARIO_JUMP_OX );
	}
}

void Mario::updateGravity(  ) {
	if ( _jumping ) {
		setGravityWY( GRAVITY_JUMP_POWER );
	} else {
		setGravityWY( GRAVITY_FALL_POWER );
	}
}

void Mario::shootFireball( ) {
	if ( _type != TYPE::FIRE ) {
		return;
	}

	if ( isButtonB( true ) ) {
		double wx;
		if ( getDir( ) == Character::DIR::RIGHT ) {
			wx = getPosWX( ) + getWidthRightSX( );
		} else {
			wx = getPosWX( ) - getWidthLeftSX( );
		}
		double wy = getPosWY( ) - getHeightSY( ) / 2;

		FactoryPtr factory = getFactory( );
		factory->createFireball( wx, wy, getDir( ) );
	}
}

void Mario::move(  ) {

	if ( getVecWY( ) > MAX_FALL_SPEED ) {
		setVecWY( MAX_FALL_SPEED );
	}

	int dir = 0;
	if ( isArrowRight( false ) && !isArrowDown( false ) ) {
		dir += 1;
	}
	if ( isArrowLeft( false ) && !isArrowDown( false ) ) {
		dir += -1;
	}

	double accel = FLOAT_ACCEL;
	if ( isStanding( ) ) {
		accel = STAND_ACCEL;
		_max_speed = MAX_WALK_SPEED;
		if ( isButtonB( false ) ) {
			_max_speed = MAX_DASH_SPEED;
		}
	}

	if ( dir != 0 ) {
		double vec_wx = getVecWX( );
		vec_wx += accel * dir;
		setVecWX( vec_wx );

		if ( getVecWX( ) * dir > _max_speed ) {
			setVecWX( _max_speed * dir );
		}
	}

	if ( getVecWX( ) * dir <= 0 ) {
		if ( getVecWX( ) < 0 ) {
			double vec_wx = getVecWX( );
			vec_wx += accel;
			setVecWX( vec_wx );
			if ( getVecWX( ) > 0 ) {
				setVecWX( 0 );
			}
		}
		if ( getVecWX( ) > 0 ) {
			double vec_wx = getVecWX( );
			vec_wx += -accel;
			setVecWX( vec_wx );
			if ( getVecWX( ) < 0 ) {
				setVecWX( 0 );
			}
		}
	}

	CameraPtr camera = getCamera( );
	double camera_sx = camera->getSX( );
	if ( getPosWX( ) < camera_sx ) {
		setPosWX( camera_sx );
		setVecWX( 0 );
	}

	if ( isStanding( ) ) {
		if ( getVecWX( ) * dir > MAX_WALK_SPEED ) {
			setWidthLeftSX( MARIO_DASH_WIDTH_EXPANSION );
			setWidthRightSX( MARIO_DASH_WIDTH_EXPANSION );
		}

		if ( getVecWX( ) != 0 ) {
			int idx = ( int )( getPosWX( ) / 5 ) % 4;
			if ( getVecWX( ) < 0 ) {
				setDir( Character::DIR::LEFT );
			} else {
				setDir( Character::DIR::RIGHT );
			}
			setOX( MARIO_WALK_OX[ idx ] );
			if ( getVecWX( ) < 0 && dir > 0 ) {
				setOX( 4 ); 
				setDir( Character::DIR::RIGHT );
			}
			if ( getVecWX( ) > 0 && dir < 0 ) {
				setOX( 4 );
				setDir( Character::DIR::LEFT );
			}
		} else {
			setOX( MARIO_WAIT_OX );
		}
	}
}

bool Mario::setAccordingToType( ) {
	bool ret = true;
	SystemPtr system = getSystem( );
	int star_count = system->getNowCount( ) - _star_count;
	int invincible_count = system->getNowCount( ) - _invincible_count;
	setInvisible( false );

	switch ( _type ) {
	case TYPE::DEKA:
		setOY( MARIO_DEKA_OY );
		setTall( true );
		setWidthLeftSX( MARIO_BIG_WIDTH_LEFT_SX );
		setWidthRightSX( MARIO_BIG_WIDTH_RIGHT_SX );
		setHeightSY( MARIO_BIG_HEIGHT_SY );
		if ( star_count < STAR_COUNT && star_count % 2 ) {
			setOY( MARIO_FIRE_OY );
		}
		break;
	case TYPE::FIRE:
		setOY( MARIO_FIRE_OY );
		setTall( true );
		setWidthLeftSX( MARIO_BIG_WIDTH_LEFT_SX );
		setWidthRightSX( MARIO_BIG_WIDTH_RIGHT_SX );
		setHeightSY( MARIO_BIG_HEIGHT_SY );
		if ( star_count < STAR_COUNT && star_count % 2 ) {
			setOY( MARIO_DEKA_OY );
		}
		break;
	case TYPE::CHIBI:
		setOY( MARIO_CHIBI_OY );
		setTall( false );
		setWidthLeftSX( MARIO_SMALL_WIDTH_LEFT_SX );
		setWidthRightSX( MARIO_SMALL_WIDTH_RIGHT_SX );
		setHeightSY( MARIO_SMALL_HEIGHT_SY );
		if ( star_count < STAR_COUNT && star_count % 2 ) {
			setOY( MARIO_CHIBI_OY + 1 );
		}
		break;
	case TYPE::TO_DEKA:
	{
		ret = false;
		setInvisible( true );
		setOY( MARIO_DEKA_OY );
		setGravityWY( 0 );
		setVecWX( 0 );
		setVecWY( 0 );
		int count = system->getNowCount( ) - _start_count;
		if ( count < GROW_COUNT / 2 ) {
			if ( count / 5 % 2 ) {
				setOX( MARIO_WAIT_OX );
				setOY( MARIO_CHIBI_OY );
				setTall( false );
			} else {
				setOX( MARIO_GROW_OX );
				setOY( MARIO_GROW_OY );
				setTall( true );
			}
		} else if ( count < GROW_COUNT ) {
			if ( count / 5 % 2 ) {
				setOX( MARIO_WAIT_OX );
				setOY( MARIO_DEKA_OY );
				setTall( true );
			} else {
				setOX( MARIO_GROW_OX );
				setOY( MARIO_GROW_OY );
				setTall( true );
			}
		} else {
			_type = TYPE::DEKA;
		}
		break;
	}
	case TYPE::TO_FIRE:
	{
		ret = false;
		setInvisible( true );
		setOY( MARIO_DEKA_OY );
		setGravityWY( 0 );
		setVecWX( 0 );
		setVecWY( 0 );
		int count = system->getNowCount( ) - _start_count;
		if ( count < GROW_COUNT ) {
			setTall( true );
			if ( count / 5 % 2 ) {
				setOY( MARIO_DEKA_OY );
			} else {
				setOY( MARIO_FIRE_OY );
			}
		} else {
			_type = TYPE::FIRE;
		}
		break;
	}
	case TYPE::TO_CHIBI:
	{
		ret = false;
		setInvisible( true );
		setOY( MARIO_CHIBI_OY );
		setGravityWY( 0 );
		setVecWX( 0 );
		setVecWY( 0 );
		if ( invincible_count < GROW_COUNT / 2 ) {
			if ( invincible_count / 5 % 2 ) {
				setOX( MARIO_SWIM_OX );
				setOY( MARIO_GROW_OY );
				setTall( true );
			} else {
				setOX( MARIO_ABSENT_OX );
				setOY( MARIO_GROW_OY );
				setTall( false );
			}
		} else if ( invincible_count < GROW_COUNT ) {
			if ( invincible_count / 5 % 2 ) {
				setOX( MARIO_CHIBI_OX );
				setOY( MARIO_CHIBI_OY );
				setTall( false );
			} else {
				setOX( MARIO_ABSENT_OX );
				setOY( MARIO_GROW_OY );
				setTall( false );
			}
		} else {
			_type = TYPE::CHIBI;
		}
		
		break;
	}
	}

	if ( star_count > STAR_COUNT&& isStaring( ) ) {
		_staring = false;
	}

	if ( invincible_count > INVINCIBLE_COUNT && isInvincible( ) ) {
		_invincible = false;
	}

	return ret;
}

void Mario::fallIntoHole(  ) {
	if ( getPosWY( ) > DEADLINE ) {
		remove( );

		SystemPtr system = getSystem( );
		system->freeze( getPosWX( ), getPosWY( ) );
	}
}

void Mario::hitEnemy( CharacterConstPtr target ) {
	SystemPtr system = getSystem( );
	// 甲羅が動いていなかったら
	if ( target->getType( ) == Character::TYPE::SHELL &&
		 target->getVecWX( ) == 0 ) {
		return;
	}
	// 上から踏んだら
	if ( getPosWY( ) < target->getPosWY( ) ) {
		setJumpPower( );
	}
	// チビで当たったら
	if ( _type == TYPE::CHIBI &&
		 getPosWY( ) == target->getPosWY( ) &&
		 !_staring && !_invincible ) {
		remove( );
		system->freeze( getPosWX( ), getPosWY( ) );
	}
	// デカで当たったら
	if ( _type == TYPE::DEKA &&
		 getPosWY( ) == target->getPosWY( ) &&
		 !_staring ) {
		_type = TYPE::TO_CHIBI;
		_invincible_count = system->getNowCount( );
		_invincible = true;
	}
	// ファイヤーで当たったら
	if ( _type == TYPE::FIRE &&
		 getPosWY( ) == target->getPosWY( ) &&
		 !_staring ) {
		_type = TYPE::TO_CHIBI;
		_invincible_count = system->getNowCount( );
		_invincible = true;
	}
}
