#pragma once

#include <array>
#include <map>
#include "Character.h"
#include "Factory.h"

class Map {
public:
	Map( FactoryPtr factory );
	virtual ~Map( );
public:
	static const int FIELD_WIDTH = 240;
	static const int FIELD_HEIGHT = 15;
	static const int CHIP_SIZE = 16;
	static const int FIELD_ACTIVE_WIDTH = 36;
	static const int FIELD_SHOW_WIDTH = 18;
	static const int FIELD_GENERATING_WIDTH = 26;

	enum class BG {
		SKY,
		CLOUD_TOP_LEFT,
		CLOUD_TOP_MIDDLE,
		CLOUD_TOP_RIGHT,
		CLOUD_BOTTOM_LEFT,
		CLOUD_BOTTOM_MIDDLE,
		CLOUD_BOTTOM_RIGHT,
		MOUNTAIN_TOP_LEFT,
		MOUNTAIN_TOP_MIDDLE,
		MOUNTAIN_TOP_RIGHT,
		MOUNTAIN_BOTTOM_LEFT,
		MOUNTAIN_BOTTOM_MIDDLE,
		MOUNTAIN_BOTTOM_RIGHT,
		GRASS_LEFT,
		GRASS_MIDDLE,
		GRASS_RIGHT,
		POLE_HEAD,
		POLE_BODY,
		CASTLE_1,
		CASTLE_2,
		CASTLE_3,
		CASTLE_4,
		CASTLE_5,
		CASTLE_6,
		CASTLE_7,
		CASTLE_8,
		MAX,
	};
	enum class OBJECT {
		NONE,
		BLOCK_GROUND,
		BLOCK_QUESTION,
		BLOCK_BRICK,
		BLOCK_PIPE_HEAD_LEFT,
		BLOCK_PIPE_HEAD_RIGHT,
		BLOCK_PIPE_BODY_LEFT,
		BLOCK_PIPE_BODY_RIGHT,
		BLOCK_HARD,
		BLOCK_USED,
		MAX,
	};
private:
	struct Data {
		int slide;
	};
public:
	int getBGRes( BG type ) const;
	BG getBGType( int fx, int fy ) const;
	int getObjectRes( OBJECT type ) const;
	OBJECT getObjectType( int fx, int fy ) const;
	Character::TYPE getEnemyType( int fx, int fy ) const;
	bool pushUp( int fx, int fy, bool big );
private:
	void setObjectType( int fx, int fy, OBJECT type );
private:
	std::array< int, ( int )BG::MAX > _bg_res;
	std::map< char, BG > _bg_type;
	std::array< int, ( int )OBJECT::MAX > _object_res;
	std::array< int, FIELD_WIDTH * FIELD_HEIGHT > _slide;
	std::map< char, OBJECT > _object_type;
	std::map< char, Character::TYPE > _enemy_type;
private:
	FactoryPtr _factory;
};

