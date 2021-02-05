#include "Map.h"
#include "Factory.h"

#define MAKERES( x, y ) ( x + y * 16 )

const char MAP[ Map::FIELD_WIDTH * Map::FIELD_HEIGHT + 1 ] =
"                                                                                                                                                                                                                                                "
"                                                                                                                                                                                                                                                "
"                   qwe              qwwe                           qwe              qwwe                           qwe              qwwe                           qwe              qwwe              o                                         "
"                   asd     qwwwe    assd                qwe        asd     qwwwe    assd                qwe        asd     qwwwe    assd                qwe        asd     qwwwe    assd              l qwe                                     "
"                           asssd                        asd                asssd                        asd                asssd                        asd                asssd                      l asd                                     "
"                      ?                                                         ========   ===?              ?           ===    =??=                                                        @@        l                                         "
"                                                                                                                                                                                           @@@        l                                         "
"                                                                                                                                                                                          @@@@        l                                         "
"                                                                                                                                                                                         @@@@@        l    111                                  "
"    ? ==        ?   =?=?=         G       G   <>      G  <>     G         G  =?=              =     ==    ?  ?  ?     =          ==      @  @          @@  @            ==?=            @@@@@@        l    234                                  "
"  t                                   <>      []  t      []                                       t                                     @@  @@    t   @@@  @@                          @@@@@@@    t   l   15551                                 "
" rfy  <>     ????t          <>        []      [] rfy     []      t                               rfy             t                     @@@  @@@  rfy @@@@  @@@   t <>              <> @@@@@@@@   rfy  l   83688  t                              "
"rfghy []   zxxxcrfy GN zxc  []  N  N  [] zxxc []rfghy    []zxxxcrfy    zxc               zxxc   rfghy      zxxxcrfy    zxc            @@@@xx@@@@rfgh@@@@@  @@@@crfy[]  zxc         []@@@@@@@@@  rfghy @   83788crfy                            #"
"#####################################################################  ###############   ################################################################  #####################################################################################"
"#####################################################################  ###############   ################################################################  #####################################################################################"
;


Map::Map( FactoryPtr factory ) :
_factory( factory ) {
	_bg_res[ ( int )BG::SKY ] = MAKERES( 3, 7 );
	_bg_res[ ( int )BG::CLOUD_TOP_LEFT ] = MAKERES( 0, 6 );
	_bg_res[ ( int )BG::CLOUD_TOP_MIDDLE ] = MAKERES( 1, 6 );
	_bg_res[ ( int )BG::CLOUD_TOP_RIGHT ] = MAKERES( 2, 6 );
	_bg_res[ ( int )BG::CLOUD_BOTTOM_LEFT ] = MAKERES( 0, 7 );
	_bg_res[ ( int )BG::CLOUD_BOTTOM_MIDDLE ] = MAKERES( 1, 7 );
	_bg_res[ ( int )BG::CLOUD_BOTTOM_RIGHT ] = MAKERES( 2, 7 );
	_bg_res[ ( int )BG::MOUNTAIN_TOP_LEFT ] = MAKERES( 8, 12 );
	_bg_res[ ( int )BG::MOUNTAIN_TOP_MIDDLE ] = MAKERES( 9, 12 );
	_bg_res[ ( int )BG::MOUNTAIN_TOP_RIGHT ] = MAKERES( 10, 12 );
	_bg_res[ ( int )BG::MOUNTAIN_BOTTOM_LEFT ] = MAKERES( 8, 13 );
	_bg_res[ ( int )BG::MOUNTAIN_BOTTOM_MIDDLE ] = MAKERES( 9, 13 );
	_bg_res[ ( int )BG::MOUNTAIN_BOTTOM_RIGHT ] = MAKERES( 10, 13 );
	_bg_res[ ( int )BG::GRASS_LEFT ] = MAKERES( 11, 13 );
	_bg_res[ ( int )BG::GRASS_MIDDLE ] = MAKERES( 12, 13 );
	_bg_res[ ( int )BG::GRASS_RIGHT ] = MAKERES( 13, 13 );
	_bg_res[ ( int )BG::POLE_HEAD ] = MAKERES( 0, 14 );
	_bg_res[ ( int )BG::POLE_BODY ] = MAKERES( 0, 15 );
	_bg_res[ ( int )BG::CASTLE_1 ] = MAKERES( 11, 8 );
	_bg_res[ ( int )BG::CASTLE_2 ] = MAKERES( 12, 8 );
	_bg_res[ ( int )BG::CASTLE_3 ] = MAKERES( 13, 8 );
	_bg_res[ ( int )BG::CASTLE_4 ] = MAKERES( 14, 8 );
	_bg_res[ ( int )BG::CASTLE_5 ] = MAKERES( 11, 9 );
	_bg_res[ ( int )BG::CASTLE_6 ] = MAKERES( 12, 9 );
	_bg_res[ ( int )BG::CASTLE_7 ] = MAKERES( 13, 9 );
	_bg_res[ ( int )BG::CASTLE_8 ] = MAKERES( 2, 8 );

	_bg_type[ 'q' ] = BG::CLOUD_TOP_LEFT;
	_bg_type[ 'w' ] = BG::CLOUD_TOP_MIDDLE;
	_bg_type[ 'e' ] = BG::CLOUD_TOP_RIGHT;
	_bg_type[ 'a' ] = BG::CLOUD_BOTTOM_LEFT;
	_bg_type[ 's' ] = BG::CLOUD_BOTTOM_MIDDLE;
	_bg_type[ 'd' ] = BG::CLOUD_BOTTOM_RIGHT;
	_bg_type[ 'r' ] = BG::MOUNTAIN_TOP_LEFT;
	_bg_type[ 't' ] = BG::MOUNTAIN_TOP_MIDDLE;
	_bg_type[ 'y' ] = BG::MOUNTAIN_TOP_RIGHT;
	_bg_type[ 'f' ] = BG::MOUNTAIN_BOTTOM_LEFT;
	_bg_type[ 'g' ] = BG::MOUNTAIN_BOTTOM_MIDDLE;
	_bg_type[ 'h' ] = BG::MOUNTAIN_BOTTOM_RIGHT;
	_bg_type[ 'z' ] = BG::GRASS_LEFT;
	_bg_type[ 'x' ] = BG::GRASS_MIDDLE;
	_bg_type[ 'c' ] = BG::GRASS_RIGHT;
	_bg_type[ 'o' ] = BG::POLE_HEAD;
	_bg_type[ 'l' ] = BG::POLE_BODY;
	_bg_type[ '1' ] = BG::CASTLE_1;
	_bg_type[ '2' ] = BG::CASTLE_2;
	_bg_type[ '3' ] = BG::CASTLE_3;
	_bg_type[ '4' ] = BG::CASTLE_4;
	_bg_type[ '5' ] = BG::CASTLE_5;
	_bg_type[ '6' ] = BG::CASTLE_6;
	_bg_type[ '7' ] = BG::CASTLE_7;
	_bg_type[ '8' ] = BG::CASTLE_8;

	_object_res[ ( int )OBJECT::BLOCK_GROUND ] = MAKERES( 0, 8 );
	_object_res[ ( int )OBJECT::BLOCK_QUESTION ] = MAKERES( 8, 10 );
	_object_res[ ( int )OBJECT::BLOCK_BRICK ] = MAKERES( 1, 8 );
	_object_res[ ( int )OBJECT::BLOCK_PIPE_HEAD_LEFT ] = MAKERES( 0, 12 );
	_object_res[ ( int )OBJECT::BLOCK_PIPE_HEAD_RIGHT ] = MAKERES( 1, 12 );
	_object_res[ ( int )OBJECT::BLOCK_PIPE_BODY_LEFT ] = MAKERES( 0, 13 );
	_object_res[ ( int )OBJECT::BLOCK_PIPE_BODY_RIGHT ] = MAKERES( 1, 13 );
	_object_res[ ( int )OBJECT::BLOCK_HARD ] = MAKERES( 0, 9 );
	_object_res[ ( int )OBJECT::BLOCK_USED ] = MAKERES( 3, 8 );

	_object_type[ '#' ] = OBJECT::BLOCK_GROUND;
	_object_type[ '?' ] = OBJECT::BLOCK_QUESTION;
	_object_type[ '=' ] = OBJECT::BLOCK_BRICK;
	_object_type[ '<' ] = OBJECT::BLOCK_PIPE_HEAD_LEFT;
	_object_type[ '>' ] = OBJECT::BLOCK_PIPE_HEAD_RIGHT;
	_object_type[ '[' ] = OBJECT::BLOCK_PIPE_BODY_LEFT;
	_object_type[ ']' ] = OBJECT::BLOCK_PIPE_BODY_RIGHT;
	_object_type[ '@' ] = OBJECT::BLOCK_HARD;

	_enemy_type[ 'G' ] = Character::TYPE::KURIBOO;
	_enemy_type[ 'N' ] = Character::TYPE::NOKONOKO;
}

Map::~Map( ) {

}

int Map::getBGRes( BG bg ) const {
	return _bg_res[ ( int )bg ];
}

Map::BG Map::getBGType( int fx, int fy ) const {
	int idx = fx + fy * FIELD_WIDTH;
	char ch = MAP[ idx ];

	if ( _bg_type.count( ch ) == 0 ) {
		return Map::BG::SKY;
	}

	return _bg_type.at( ch );
}

int Map::getObjectRes( OBJECT type ) const {
	return _object_res[ ( int )type ];
}

Map::OBJECT Map::getObjectType( int fx, int fy ) const {
	int idx = fx + fy * FIELD_WIDTH;
	char ch = MAP[ idx ];

	if ( _object_type.count( ch ) == 0 ) {
		return OBJECT::NONE;
	}

	return _object_type.at( ch );
}

Character::TYPE Map::getEnemyType( int fx, int fy ) const {
	int idx = fx + fy * FIELD_WIDTH;
	char ch = MAP[ idx ];

	if ( _enemy_type.count( ch ) == 0 ) {
		return Character::TYPE::NONE;
	}

	return _enemy_type.at( ch );
}

void Map::setObjectType( int fx, int fy, OBJECT type ) {
	int idx = fx + fy * FIELD_WIDTH;
	char ch = MAP[ idx ];

	_object_type.at( ch ) = type;
}

bool Map::pushUp( int fx, int fy, bool big ) {
	if ( fx < 0 || fx >= FIELD_WIDTH ||
		 fy < 0 || fy >= FIELD_HEIGHT ) {
		return false;
	}

	int idx = fx + fy * FIELD_WIDTH;
	OBJECT type = getObjectType( fx, fy );

	if ( type == OBJECT::BLOCK_QUESTION ) {
		//_slide[ idx ] = 10;
		setObjectType( fx, fy, OBJECT::BLOCK_USED );
		_factory->createKinoko( fx * CHIP_SIZE + CHIP_SIZE / 2, fy * CHIP_SIZE - 1 );
		return true;
	}

	if ( type == OBJECT::BLOCK_BRICK ) {
		if ( big ) {
			setObjectType( fx, fy, OBJECT::NONE );
		} else {
			//_slide[ idx ] = 10;
		}
		return true;
	}

	return false;
}


