#include "Viewer.h"
#include "Map.h"
#include "Camera.h"
#include "Characters.h"
#include "Character.h"
#include "System.h"
#include "EGL.h"

Viewer::Viewer( CameraConstPtr camera, 
				MapConstPtr map, 
				CharactersConstPtr characters,
				SystemConstPtr system ) :
_camera( camera ),
_map( map ),
_characters( characters ),
_system( system ) {

}

Viewer::~Viewer( ) {

}

void Viewer::draw( ) const {
	drawBackground( );
	drawObject( );
	drawCharacters( );
	drawDeadMario( );
}

void Viewer::drawBackground( ) const {
	int camera_sx = _camera->getSX( );
	int sky_res = _map->getBGRes( Map::BG::SKY );
	for ( int i = 0; i < Map::FIELD_SHOW_WIDTH; i++ ) {
		int fx = camera_sx / Map::CHIP_SIZE + i - 1;
		for ( int j = 0; j < Map::FIELD_HEIGHT; j++ ) {
			int fy = j;

			int sx = fx * Map::CHIP_SIZE - camera_sx;
			int sy = fy * Map::CHIP_SIZE;

			// SKY
			drawImage(
				sx, sy,
				sky_res % 16 * Map::CHIP_SIZE, sky_res / 16 * Map::CHIP_SIZE,
				Map::CHIP_SIZE, Map::CHIP_SIZE );

			// OTHER
			Map::BG bg = _map->getBGType( fx, fy );
			if ( bg == Map::BG::SKY ) {
				continue;
			}
			int res = _map->getBGRes( bg );
			drawImage(
				sx, sy,
				res % 16 * Map::CHIP_SIZE, res / 16 * Map::CHIP_SIZE,
				Map::CHIP_SIZE, Map::CHIP_SIZE );
		}
	}
}

void Viewer::drawObject( ) const {
	int camera_sx = _camera->getSX( );
	for ( int i = 0; i < Map::FIELD_SHOW_WIDTH; i++ ) {
		int fx = camera_sx / Map::CHIP_SIZE + i - 1;
		for ( int j = 0; j < Map::FIELD_HEIGHT; j++ ) {
			int fy = j;

			Map::OBJECT object = _map->getObjectType( fx, fy );
			if ( object == Map::OBJECT::NONE ) {
				continue;
			}

			int res = _map->getObjectRes( object );

			int sx = fx * Map::CHIP_SIZE - camera_sx;
			int sy = fy * Map::CHIP_SIZE;

			drawImage(
				sx, sy,
				res % 16 * Map::CHIP_SIZE, res / 16 * Map::CHIP_SIZE,
				Map::CHIP_SIZE, Map::CHIP_SIZE );
		}
	}
}

void Viewer::drawCharacters( ) const {
	int num = _characters->getNum( );
	debugLog( "Character Num : %d", num );
	for ( int i = 0; i < num; i++ ) {
		CharacterConstPtr character = _characters->getInstance( i );
		drawCharacter( character );
	}
}

void Viewer::drawCharacter( CharacterConstPtr character ) const {
	int camera_sx = _camera->getSX( );

	int h = 1;
	if ( character->isTall( ) ) {
		h = 2;
	}
	int tx = character->getOX( ) * Map::CHIP_SIZE;
	int ty = character->getOY( ) * Map::CHIP_SIZE;
	int tw = Map::CHIP_SIZE;
	int th = Map::CHIP_SIZE;
	if ( character->isTall( ) ) {
		th += Map::CHIP_SIZE;
	}
	int sx = ( int )( character->getPosWX( )- camera_sx ) - Map::CHIP_SIZE / 2;
	int sy = ( int )( character->getPosWY( ) ) - th + 1;

	bool dir_right = false;
	if ( character->getDir( ) == Character::DIR::LEFT ) {
		dir_right = true;
	}

	drawImage( sx, sy, tx, ty, tw, th, dir_right, character->isUpsideDown( ) );

	// デバッグ
	int x1 = ( int )character->getPosWX( ) - character->getWidthLeftSX( ) - camera_sx;
	int y1 = ( int )character->getPosWY( ) - character->getHeightSY( );
	int x2 = ( int )character->getPosWX( ) + character->getWidthRightSX( ) - camera_sx + 1;
	int y2 = ( int )character->getPosWY( ) + 1;
	debugBox( x1, y1, x2, y2 );
	debugString( x1, y1 - 20, character->getDir( ) == Character::DIR::LEFT ? "L" : "R" );
}

void Viewer::drawDeadMario( ) const {
	if ( !_system->isFreezing( ) ) {
		return;
	}

	int tx = 6 * Map::CHIP_SIZE;
	int ty = 4 * Map::CHIP_SIZE;
	int th = Map::CHIP_SIZE;
	int tw = Map::CHIP_SIZE;
	int sx = ( int )( _system->getMarioDeadPosWX( ) - _camera->getSX( ) ) - Map::CHIP_SIZE / 2;;
	int sy = ( int )( _system->getMarioDeadPosWY( ) ) + 1;
	drawImage( sx, sy, tx, ty, tw, th );
}
