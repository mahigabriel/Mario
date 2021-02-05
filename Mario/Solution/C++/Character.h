#pragma once
#include "smart_ptr.h"

PTR( Character );
PTR( Map );
PTR( Camera );
PTR( System );
PTR( Characters );
PTR( Factory );
PTR( Mario );

class Character {
	friend class Factory;
public:
	enum class TYPE {
		NONE,
		DUMMY,
		MARIO,
		KINOKO,
		FLOWER,
		STAR,
		FIREBALL,
		KURIBOO,
		NOKONOKO,
		SHELL,
	} type;

	enum class DIR {
		LEFT,
		RIGHT,
	} dir;

public:
	Character( );
	virtual ~Character( );
public:
	virtual void update( ) = 0;
	virtual void overlapped( CharacterConstPtr target ) = 0;
public:
	bool isInvisibled( ) const;
	double getPosWX( ) const;
	double getPosWY( ) const;
	int getWidthLeftSX( ) const;
	int getWidthRightSX( ) const;
	int getHeightSY( ) const;
	double getGravityWY( ) const;
	TYPE getType( ) const;
	double getVecWX( ) const;
	double getVecWY( ) const;
	bool isStanding( ) const;
	DIR getDir( ) const;
	bool isTall( ) const;
	int getOX( ) const;
	int getOY( ) const;
	bool isUpsideDown( ) const;
	bool isCollision( ) const;
	bool isRemoved( ) const;
public:
	void move( );
	void remove( );
	void turnUpsideDown( );
protected:
	MapPtr getMap( ) const;
protected:
	CameraPtr getCamera( ) const;
	SystemPtr getSystem( ) const;
	CharactersPtr getCharacters( ) const;
	FactoryPtr getFactory( ) const;
protected:
	void setType( TYPE type );
	void setPosWX( double wx );
	void setPosWY( double wy );
	void setWidthLeftSX( int sx );
	void setWidthRightSX( int sx );
	void setHeightSY( int sy );
	void setGravityWY( double wy );
	void setVecWX( double wx );
	void setVecWY( double wy );
	void setOX( int ox );
	void setOY( int oy );
	void setDir( DIR dir );
	void setInvisible( bool invisible );
	void setTall( bool tall );
private:
	void moveHorizontal( );
	void moveVertical( );
private:
	MapPtr _map;
	CameraPtr _camera;
	SystemPtr _system;
	CharactersPtr _characters;
	MarioConstPtr _mario;
	FactoryPtr _factory;
	TYPE _type;
	DIR _dir;
	int _ox;
	int _oy;
	bool _tall;
	bool _upside_down;
	bool _invisible;
	int _width_left_sx;
	int _width_right_sx;
	int _height_sy;
	double _pos_wx;
	double _pos_wy;
	double _vec_wx;
	double _vec_wy;
	double _gravity_wy;
	bool _standing;
	bool _collision;
	bool _removed;
};

