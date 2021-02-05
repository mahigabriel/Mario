#pragma once
#pragma comment(lib,"EGL.lib")

#define VERSION "20200726"

//設定


void setupScreen( int width, int height );
void setupImage( const char * filename );


//入力

/// <summary>
/// →の入力
/// </summary>
/// <param name="push">長押しの判定</param>
bool isArrowRight( bool push );

/// <summary>
/// ←の入力
/// </summary>
/// <param name="push">長押しの判定</param>
bool isArrowLeft( bool push );

/// <summary>
/// ↑の入力
/// </summary>
/// <param name="push">長押しの判定</param>
bool isArrowUp( bool push );

/// <summary>
/// ↓の入力
/// </summary>
/// <param name="push">長押しの判定</param>
bool isArrowDown( bool push );

/// <summary>
/// Aボダンの入力
/// </summary>
/// <param name="push">長押しの判定</param>
bool isButtonA( bool push );

/// <summary>
/// Bボダンの入力
/// </summary>
bool isButtonB( bool push );

//イメージ

/// <summary>
/// 
/// </summary>
void drawImage( int x, int y, int tx, int ty, int tw, int th,  bool rev_x = false, bool rev_y = false );


// デバッグ

///
void debugLog( const char *fmt, ... );

///
void debugString( int sx, int sy, const char *fmt, ... );

/// <summary>
/// 
/// </summary>
void debugBox( int x1, int x2, int y1, int y2 );

/// <summary>
/// デバッグキー
/// </summary>
bool debugKeyW( bool push );
bool debugKeyS( bool push );
bool debugKeyA( bool push );
bool debugKeyD( bool push );
bool debugKeyF1( bool push );
bool debugKeyF2( bool push );
bool debugKeyF3( bool push );
bool debugKeyF4( bool push );

//実装

/// <summary>
/// ループ
/// </summary>
void setup( );
void update( );
