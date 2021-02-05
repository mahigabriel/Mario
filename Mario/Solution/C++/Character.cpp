#include "Character.h"
#include "Map.h"

const double CHARACTER_GRAVITY = 0.2;
const double FLOAT_ACCEL = 0.02;
const double SIDEWAY_DECEL = 0.3;

Character::Character( ) {
	_type = Character::TYPE::DUMMY;
	_dir = Character::DIR::LEFT;
	_ox = 1;
	_oy = 11;
	_tall = false;
	_pos_wx = 0;
	_pos_wy = 0;
	_vec_wx = 0;
	_vec_wy = 0;
	_width_left_sx = 6;
	_width_right_sx = 5;
	_height_sy = 16;
	_gravity_wy = CHARACTER_GRAVITY;
	_standing = false;
	_collision = false;
	_removed = false;
	_upside_down = false;
}

Character::~Character( ) {

}

bool Character::isInvisibled( ) const {
	return _invisible;
}

double Character::getPosWX( ) const {
	return _pos_wx;
}

double Character::getPosWY( ) const {
	return _pos_wy;
}

int Character::getWidthLeftSX( ) const {
	return _width_left_sx;
}

int Character::getWidthRightSX( ) const {
	return _width_right_sx;
}

int Character::getHeightSY( ) const {
	return _height_sy;
}

double Character::getGravityWY( ) const {
	return _gravity_wy;
}

Character::TYPE Character::getType( ) const {
	return _type;
}

double Character::getVecWX( ) const { 
	return _vec_wx;
}

double Character::getVecWY( ) const {
	return _vec_wy;
}

bool Character::isStanding( ) const {
	return _standing;
}

Character::DIR Character::getDir( ) const {
	return _dir;
}

bool Character::isTall( ) const {
	return _tall;
}

int Character::getOX( ) const {
	return _ox;
}

int Character::getOY( ) const {
	return _oy;
}

bool Character::isUpsideDown( ) const {
	return _upside_down;
}

bool Character::isCollision( ) const {
	return _collision;
}

bool Character::isRemoved( ) const {
	return _removed;
}

void Character::setType( TYPE type ) {
	_type = type;
}

void Character::setPosWX( double wx ) {
	_pos_wx = wx;
}

void Character::setPosWY( double wy ) {
	_pos_wy = wy;
}

void Character::setWidthLeftSX( int sx ) {
	_width_left_sx = sx;
}

void Character::setWidthRightSX( int sx ) {
	_width_right_sx = sx;
}

void Character::setHeightSY( int sy ) {
	_height_sy = sy;
}

void Character::setGravityWY( double wy ) {
	_gravity_wy = wy;
}

void Character::setVecWX( double wx ) {
	_vec_wx = wx;
}

void Character::setVecWY( double wy ) {
	_vec_wy = wy;
}

void Character::setOX( int ox ) {
	_ox = ox;
}

void Character::setOY( int oy ) {
	_oy = oy;
}

void Character::setDir( DIR dir ) {
	_dir = dir;
}

void Character::setInvisible( bool invisible ) {
	_invisible = invisible;
}

void Character::setTall( bool tall ) {
	_tall = tall;
}

void Character::remove( ) {
	_removed = true;
}

void Character::turnUpsideDown( ) {
	_upside_down = true;
}

void Character::move( ) {
	moveHorizontal( );
	moveVertical( );
}

void Character::moveHorizontal( ) {
	_pos_wx += _vec_wx;
	_collision = false;
	if ( _invisible ) {
		return;
	}

	int foot_fy = ( ( int )_pos_wy ) / Map::CHIP_SIZE;
	int head_fy = ( ( int )_pos_wy - _height_sy ) / Map::CHIP_SIZE;
	int body_fy = ( ( int )_pos_wy - _height_sy / 2 ) / Map::CHIP_SIZE;

	// âEë§
	int right_fx = ( ( int )_pos_wx + _width_right_sx ) / Map::CHIP_SIZE;
	Map::OBJECT right_foot_type = _map->getObjectType( right_fx, foot_fy );
	Map::OBJECT right_body_type = _map->getObjectType( right_fx, body_fy );
	Map::OBJECT right_head_type = _map->getObjectType( right_fx, head_fy );
	if ( right_foot_type != Map::OBJECT::NONE ||
		 right_body_type != Map::OBJECT::NONE ||
		 right_head_type != Map::OBJECT::NONE ) {
		_pos_wx = right_fx * Map::CHIP_SIZE - ( _width_right_sx - 1 ) - 1.0 - FLOAT_ACCEL;
		_collision = true;

		// marioÇ≈çsÇ§
		_vec_wx -= SIDEWAY_DECEL;
		if ( _vec_wx < 0 ) {
			_vec_wx = 0;
		}
	}

	//ç∂ë§
	int left_fx = ( ( int )_pos_wx - _width_left_sx ) / Map::CHIP_SIZE;
	Map::OBJECT left_foot_type = _map->getObjectType( left_fx, foot_fy );
	Map::OBJECT left_body_type = _map->getObjectType( left_fx, body_fy );
	Map::OBJECT left_head_type = _map->getObjectType( left_fx, head_fy );
	if ( left_foot_type != Map::OBJECT::NONE ||
		 left_body_type != Map::OBJECT::NONE ||
		 left_head_type != Map::OBJECT::NONE ) {
		_pos_wx = left_fx * Map::CHIP_SIZE + Map::CHIP_SIZE + _width_left_sx;
		_collision = true;

		// marioÇ≈Ç®Ç±Ç»Ç§
		_vec_wx += SIDEWAY_DECEL;
		if ( _vec_wx > 0 ) {
			_vec_wx = 0;
		}
	}
}

void Character::moveVertical( ) {
	_vec_wy += _gravity_wy;
	_pos_wy += _vec_wy;
	_standing = false;
	if ( _invisible ) {
		return;
	}

	if ( _vec_wy < 0 ) {
		int head_fx = ( int )( _pos_wx ) / Map::CHIP_SIZE;
		int head_fy = ( int )( _pos_wy - _height_sy ) / Map::CHIP_SIZE;
		Map::OBJECT head_type = _map->getObjectType( head_fx, head_fy );
		if ( head_type != Map::OBJECT::NONE ) {
			_pos_wy = head_fy * Map::CHIP_SIZE + Map::CHIP_SIZE + _height_sy;
			//bool big = false;
			//if ( character.type == Character::TYPE::MARIO ) {
			//	big = marioIsBig( character );
			//}
			//if ( objectPushUp( head_fx, head_fy, big ) ) {
			//	character.vec_wy = 0;
			//}

			bool big = false;
			if ( _type == Character::TYPE::MARIO ) {
				//big = _mario->isBig();
			}
			if ( _map->pushUp( head_fx, head_fy, big ) ) {
				_vec_wy = 0;
			}
		}
	} else {
		int left_fx = ( int )( _pos_wx - _width_left_sx ) / Map::CHIP_SIZE;
		int right_fx = ( int )( _pos_wx + _width_right_sx ) / Map::CHIP_SIZE;
		int foot_fy = ( int )_pos_wy / Map::CHIP_SIZE;

		Map::OBJECT left_type = _map->getObjectType( left_fx, foot_fy );
		Map::OBJECT right_type = _map->getObjectType( right_fx, foot_fy );
		if ( left_type != Map::OBJECT::NONE ||
			 right_type != Map::OBJECT::NONE ) {
			_pos_wy = foot_fy * Map::CHIP_SIZE - 1;
			_vec_wy = 1;
			_standing = true;
		}
	}
}

MapPtr Character::getMap( ) const {
	return _map;
}

CameraPtr Character::getCamera( ) const {
	return _camera;
}

SystemPtr Character::getSystem( ) const {
	return _system;
}

CharactersPtr Character::getCharacters( ) const {
	return _characters;
}

FactoryPtr Character::getFactory( ) const {
	return _factory;
}
