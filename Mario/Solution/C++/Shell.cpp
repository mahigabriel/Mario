#include "Shell.h"
#include "Factory.h"
#include "System.h"
#include "Mario.h"

const int SHELL_WIDTH_LEFT_SX = 8;
const int SHELL_WIDTH_RIGHT_SX = 7;
const int SHELL_HEIGHT_SY = 20;
const int SHELL_OX = 10;
const int SHELL_OY = 4;

const int REBIRTH_COUNT = 240;
const int SOON_COUNT = 60;
const int MOTION_PITCH = 10;

const double SHELL_SPEED = 2;
const int COLLAPSE_TIME = 30;

const double SHELL_DIE_VEC_WY = -2.0;
const int TRAMPLED_COUNT = 10;


Shell::Shell( double wx, double wy ) :
	_rebirth( 0 ),
	_trampled( 0 ) {
	setType( Character::TYPE::SHELL );
	setPosWX( wx );
	setPosWY( wy );
	setWidthLeftSX( SHELL_WIDTH_LEFT_SX );
	setWidthRightSX( SHELL_WIDTH_RIGHT_SX );
	setHeightSY( SHELL_HEIGHT_SY );
	setOX( SHELL_OX );
	setOY( SHELL_OY );
	setTall( false );
	_collapse = false;
	_start_count = 0;
	
}

Shell::~Shell( ) {

}

void Shell::update( ) {
	//マリオがスターだった時にremoveする
	collapse( );
	
	//時間経過でのこのこに戻す
	rebirthNokonoko( );

	if ( getVecWX( ) == 0 ) {
		_rebirth++;
	}

	//当たり判定
	collision( );

	_trampled--;
}

void Shell::overlapped( CharacterConstPtr target ) {
	SystemPtr system = getSystem( );
	switch ( target->getType( ) ) {
	case Character::TYPE::MARIO:
		overlappedWithMario( std::dynamic_pointer_cast< const Mario >( target ) );
		break;
	case Character::TYPE::FIREBALL:
		overlappedWithFireball( );
		break;
	case Character::TYPE::SHELL:
		overlappedWithShell( std::dynamic_pointer_cast< const Shell > ( target ) );
		break;
	default:
		break;
	}
}

void Shell::die( ) {
	turnUpsideDown( );
	_collapse = true;
	setVecWX( 0 );
	setVecWY( SHELL_DIE_VEC_WY );

	SystemPtr system = getSystem( );
	_start_count = system->getNowCount( );
}

void Shell::collapse( ) {
	if ( _collapse ) {
		SystemPtr system = getSystem( );
		setInvisible( true );
		int count = system->getNowCount( ) - _start_count;
		if ( count > COLLAPSE_TIME ) {
			remove( );
		}
		return;
	}
}

void Shell::rebirthNokonoko( ) {
	if ( _rebirth >= REBIRTH_COUNT - SOON_COUNT ) {
		int ox = SHELL_OX + _rebirth / MOTION_PITCH % 2;
		setOX( ox );
	}

	if ( _rebirth >= REBIRTH_COUNT ) {
		remove( );
		FactoryPtr factory = getFactory( );
		factory->createNokonoko( getPosWX( ), getPosWY( ) );
	}
}

void Shell::collision( ) {
	if ( isCollision( ) ) {
		if ( getDir( ) == Character::DIR::RIGHT ) {
			setDir( Character::DIR::LEFT );
			setVecWX( -SHELL_SPEED );
		} else {
			setDir( Character::DIR::RIGHT );
			setVecWX( SHELL_SPEED );
		}
	}
}

void Shell::overlappedWithFireball( ) {
	die( );
}

void Shell::overlappedWithShell( ShellConstPtr shell ) {
	if ( shell->getVecWX( ) != 0 ) {
		die( );
	}
}

void Shell::overlappedWithMario( MarioConstPtr mario ) {
	if ( mario->isStaring( ) ) {
		die( );
	}

	if ( _trampled > 0 ) {
		return;
	}

	double speed = SHELL_SPEED;
	if ( getPosWX( ) < mario->getPosWX( ) ) {
		speed = -SHELL_SPEED;
	}
	bool trampled = false;

	if ( getVecWX( ) == 0 ) {
		trampled = true;
	} else if ( getPosWY( ) > mario->getPosWY( ) ) {
		speed = 0;
		trampled = true;
	}

	if ( trampled ) {
		setVecWX( speed );
		_rebirth = 0;
		setOX( SHELL_OX );
		_trampled = TRAMPLED_COUNT;
	}
}
