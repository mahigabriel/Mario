#include "EGL.h"
#include "Application.h"

ApplicationPtr g_app;

void setup( ) {
	setupImage( "mario.png" );
	setupScreen( Application::SCREEN_WIDTH, Application::SCREEN_HEIGHT );

	g_app = ApplicationPtr( new Application );
}

void update( ) {
	g_app->update( );
}