#include "Characters.h"
#include "Character.h"

Characters::Characters( ) :
_num( 0 ) {

}

Characters::~Characters( ) {

}

void Characters::add( CharacterPtr character ) {

	if ( _num >= MAX_NUM ) {
		_num = MAX_NUM - 1;
	}

	_character[ _num ] = character;
	_num++;
}

int Characters::getNum( ) const {
	return _num;
}

CharacterConstPtr Characters::getInstance( int idx ) const {
	return _character[ idx ];
}

void Characters::update( ) {
	for ( int i = 0; i < _num; i++ ) {
		_character[ i ]->update( );
		_character[ i ]->move( );
	}
	
	for ( int i = 0; i < _num; i++ ) {
		overlapped( _character[ i ] );
	}

	remove( );
}

void Characters::remove( ) {
	int idx = 0;
	while ( idx < _num ) {
		if ( !_character[ idx ]->isRemoved( ) ) {
			idx++;
			continue;
		}

		_num--;
		for ( int i = idx; i < _num; i++ ) {
			_character[ i ] = _character[ i + 1 ];
		}
		_character[ _num ].reset( );
	}
}


void Characters::overlapped( CharacterPtr character ) {
	if ( character->isInvisibled( ) ) {
		return;
	}

	double src_left = character->getPosWX( ) - character->getWidthLeftSX( );
	double src_right = character->getPosWX( ) + character->getWidthRightSX( );
	double src_bottom = character->getPosWY( );
	double src_up = character->getPosWY( ) - character->getHeightSY( );
	for ( int i = 0; i < _num; i++ ) {
		CharacterPtr target = _character[ i ];
		if ( character == target ) {
			continue;
		}
		if ( target->isInvisibled( ) ) {
			continue;
		}

		double dst_right = target->getPosWX( ) + target->getWidthRightSX( );
		if ( dst_right < src_left ) {
			continue;
		}
		double dst_left = target->getPosWX( ) - target->getWidthLeftSX( );
		if ( src_right < dst_left ) {
			continue;
		}
		double dst_bottom = target->getPosWY( );
		if ( dst_bottom < src_up ) {
			continue;
		}
		double dst_up = target->getPosWY( ) - target->getHeightSY( );
		if ( src_bottom < dst_up ) {
			continue;
		}

		character->overlapped( target );
	}
}
