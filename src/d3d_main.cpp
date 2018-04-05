#include "d3d.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

namespace d3d {
	
	static int paintobj(const Obj& obj);
	
	static const int  WIN_W = 512,  WIN_H = 512;
	static const float FOV = 70.0;  // vertical FOV
	static SDL_Window* win = NULL;
	static SDL_GLContext ctx;
	Obj scene;
	std::string cameraid = "camera";
	
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
		//SDL_GL_SetSwapInterval(1);  // vsync on
		// set some defaults
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glShadeModel(GL_SMOOTH);
		// simple opengl error checking
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			fprintf(stderr, "Error initialising OpenGL! %s\n", gluErrorString(error));
			//fprintf(stderr, "Error initialising OpenGL! %d\n", error);
			return 1;
		}
		// setup default scene
		clearscene();
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
	
	int clearscene() {
		scene = Obj();  // identity scene
		scene.id = "scene";  // default name
		cameraid = "camera";  // default camera
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
		Obj* cam = getbyid(scene, cameraid);
		//if (cam && getparent(cam) == &scene) {
		if (cam) {
			glRotatef   ( cam->roll,   0,0,-1 );
			glRotatef   ( cam->pitch,  -1,0,0 );
			glRotatef   ( cam->yaw,    0,-1,0 );
			glTranslatef( -cam->x, -cam->y, -cam->z );
		}
		// repaint 3d objects
		glPushMatrix();
			//paintobj(scene);
			for (const auto& c : scene.children)
				paintobj( c );
			//if (showcam)  paintobjs(camlist);
		glPopMatrix();
		// flip
		return flip();
	}
	
	static int paintobj(const Obj& obj) {
		glPushMatrix();
			// set initial vars
			glTranslatef ( obj.x, obj.y, obj.z );
			glRotatef    ( obj.yaw,     0,1,0 ); // note: follows right hand rule (negative = clockwise)
			glRotatef    ( obj.pitch,   1,0,0 );
			glRotatef    ( obj.roll,    0,0,1 );
			glScalef     ( obj.scale, obj.scale, obj.scale );
			glColor4f    ( obj.col.x, obj.col.y, obj.col.z, obj.col.a );
			// draw all quads
			glBegin(GL_QUADS);
				for (const auto& q : obj.quads) {
					glVertex3f( q[0].x,  q[0].y,  q[0].z );
					glVertex3f( q[1].x,  q[1].y,  q[1].z );
					glVertex3f( q[2].x,  q[2].y,  q[2].z );
					glVertex3f( q[3].x,  q[3].y,  q[3].z );
				}
			glEnd();
			// draw all children
			for (const auto& c : obj.children)
				paintobj( c );
		glPopMatrix();
		return 0;
	}
	
	Obj* getbyid(const std::string& id) {
		return getbyid(scene, id);
	}
	
	Obj* getbyid(Obj& root, const std::string& id) {
		if (root.id == id)  return &root;
		for (auto& c : root.children) {
			Obj* r = getbyid(c, id);
			if (r != NULL)  return r;
		}
		return NULL;
	}
	
//	Obj* getparent(Obj& root, Obj* obj) {
//		//if (obj == NULL || obj == &root)  return NULL;
//		for (Obj& c : root.children) {
//			if (&c == obj)  return &c;
//			Obj* res = getparent(c, obj);
//			if (res)  return res;
//		}
//		return NULL;
//	}
	
} // end d3d
