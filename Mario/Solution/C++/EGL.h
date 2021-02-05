#pragma once
#pragma comment(lib,"EGL.lib")

#define VERSION "20200726"

//�ݒ�


void setupScreen( int width, int height );
void setupImage( const char * filename );


//����

/// <summary>
/// ���̓���
/// </summary>
/// <param name="push">�������̔���</param>
bool isArrowRight( bool push );

/// <summary>
/// ���̓���
/// </summary>
/// <param name="push">�������̔���</param>
bool isArrowLeft( bool push );

/// <summary>
/// ���̓���
/// </summary>
/// <param name="push">�������̔���</param>
bool isArrowUp( bool push );

/// <summary>
/// ���̓���
/// </summary>
/// <param name="push">�������̔���</param>
bool isArrowDown( bool push );

/// <summary>
/// A�{�_���̓���
/// </summary>
/// <param name="push">�������̔���</param>
bool isButtonA( bool push );

/// <summary>
/// B�{�_���̓���
/// </summary>
bool isButtonB( bool push );

//�C���[�W

/// <summary>
/// 
/// </summary>
void drawImage( int x, int y, int tx, int ty, int tw, int th,  bool rev_x = false, bool rev_y = false );


// �f�o�b�O

///
void debugLog( const char *fmt, ... );

///
void debugString( int sx, int sy, const char *fmt, ... );

/// <summary>
/// 
/// </summary>
void debugBox( int x1, int x2, int y1, int y2 );

/// <summary>
/// �f�o�b�O�L�[
/// </summary>
bool debugKeyW( bool push );
bool debugKeyS( bool push );
bool debugKeyA( bool push );
bool debugKeyD( bool push );
bool debugKeyF1( bool push );
bool debugKeyF2( bool push );
bool debugKeyF3( bool push );
bool debugKeyF4( bool push );

//����

/// <summary>
/// ���[�v
/// </summary>
void setup( );
void update( );
