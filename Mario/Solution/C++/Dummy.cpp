#include "Dummy.h"
#include "EGL.h"

Dummy::Dummy( double wx, double wy, bool gravity, bool moving, bool tall ) {
	setType( Character::TYPE::DUMMY );
	setPosWX( wx );
	setPosWY( wy );
	setWidthLeftSX( 8 );
	setWidthRightSX( 7 );
	setHeightSY( 15 );
	if ( tall ) {
		setHeightSY( 31 );
	}
	setGravityWY( 0 );
	if ( gravity ) {
		setGravityWY( 0.1 );
	}

	_moving = moving;
}

Dummy::~Dummy( ) {

}

void Dummy::update( ) {
	if ( !_moving ) {
		return;
	}

	setVecWX( 0 );

	if ( isArrowRight( false ) ) {
		setVecWX( 2 );
	}
	if ( isArrowLeft( false ) ) {
		setVecWX( -2 );
	}

	if ( getGravityWY( ) == 0 ) {
		setVecWY( 0 );
		if ( isArrowUp( false ) ) {
			setVecWY( -2 );
		}
		if ( isArrowDown( false ) ) {
			setVecWY( 2 );
		}
	}
}

void Dummy::overlapped( CharacterConstPtr target ) {
	switch ( getType( ) ) {
	case Character::TYPE::KINOKO:
		debugLog( "�_�~�[���X�[�p�[�L�m�R" );
		break;
	case Character::TYPE::FLOWER:
		debugLog( "�_�~�[���t�@�C�A�[�t�����[" );
		break;
	case Character::TYPE::STAR:
		debugLog( "�_�~�[���X�^�[" );
		break;
	case Character::TYPE::DUMMY:
		debugLog( "�_�~�[���_�~�[" );
		break;
	case Character::TYPE::MARIO:
		debugLog( "�_�~�[���}���I" );
		break;
	}
}
