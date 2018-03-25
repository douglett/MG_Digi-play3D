#include "d3d.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

namespace d3d {
	
	static int paintobj(const Obj& obj);
	
	static const int  WIN_W = 512,  WIN_H = 512;
	static const float FOV = 75.0;
	static SDL_Window* win = NULL;
	static SDL_GLContext ctx;
	Obj scene;
	
	int init() {
		// init sdl2
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			fprintf(stderr, "Failed to init SDL2\n");
			return 1;
		}
		// Create our window centered at 512x512 resolution
		const int  C = SDL_WINDOWPOS_CENTERED;
		win = SDL_CreateWindow( "Digi-play 3D", C, C, WIN_W, WIN_H, SDL_WINDOW_OPENGL );
		if (!win) {
			fprintf(stderr, "Failed to open SDL2 window\n");
			return 1;
		}
		
		// set GL window attributes
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		ctx = SDL_GL_CreateContext(win);  // create window
		// set GL basic options
		glEnable(GL_DEPTH_TEST),  glDepthFunc(GL_LESS);  // stuff in background
		glEnable(GL_BLEND),       glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // transparency
		glEnable(GL_TEXTURE_2D);  // allow textures
		// set some defaults
		glClearColor(0.0, 0.0, 0.0, 1.0);
		// simple opengl error checking
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			fprintf(stderr, "Error initialising OpenGL! %s\n", gluErrorString(error));
			//fprintf(stderr, "Error initialising OpenGL! %d\n", error);
			return 1;
		}
		//SDL_Delay(2000);		
		return 0;
	}
	
	int quit() {
		SDL_Quit();
		return 0;
	}
	
	int flip() {
		SDL_GL_SwapWindow(win);
		return 0;
	}
	
	int setPerspective(const std::string& perspective) {
		if (perspective == "2d") {
			glMatrixMode(GL_PROJECTION); 	// change to the projection matrix
			glLoadIdentity();
			glDepthFunc(GL_ALWAYS); 		// normal draw order
			glOrtho(0.0f, WIN_W, WIN_H, 0.0f, 0.0f, 1.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
		if (perspective == "3d") {
			glMatrixMode(GL_PROJECTION); 	// change to the projection matrix
			glLoadIdentity();  				// reset matrix to identity position
			glDepthFunc(GL_LESS);
			gluPerspective(FOV, float(WIN_W)/WIN_H, 0.1f, 100.0f);  // Set our perspective. this will show a warning that we can ignore
			glMatrixMode(GL_MODELVIEW); 	// Make sure we're changing the model from here on
			glLoadIdentity(); 				// reset matrix to identity position
		}
		return 0;
	}
	
	int paint() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();  // clear matrix stack
		// repaint ui objects
		//setPerspective("2d");
		//paintsquares();
		// reset cam
		setPerspective("3d");
		//glRotatef( cam->pitch,  -1, 0,0 );
		//glRotatef( cam->yaw,     0,-1,0 );
		//glTranslatef( -cam->x, -cam->y, -cam->z );
		// repaint 3d objects
		glPushMatrix();
			paintobj(scene);
			//if (showcam)  paintobjs(camlist);
		glPopMatrix();
		// flip
		return flip();
	}
	
	static int paintobj(const Obj& obj) {
		glPushMatrix();
			// set initial vars
			glColor4f    ( obj.col.x, obj.col.y, obj.col.z, obj.col.a );
			glTranslatef ( obj.x, obj.y, obj.z );
			glRotatef    ( obj.roll,    0, 0,-1 );
			glRotatef    ( obj.pitch,  -1, 0, 0 );
			glRotatef    ( obj.yaw,     0,-1, 0 );
			// draw all quads
			glBegin(GL_QUADS);
				for (const auto& q : obj.quads) {
					glVertex3f( q[0],  q[1],  q[2]  );
					glVertex3f( q[3],  q[4],  q[5]  );
					glVertex3f( q[6],  q[7],  q[8]  );
					glVertex3f( q[9],  q[10], q[11] );
				}
			glEnd();
			// draw all children
			for (const auto& c : obj.children)
				paintobj( c );
		glPopMatrix();
		return 0;
	}
	
} // end d3d
