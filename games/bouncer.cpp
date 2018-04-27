#include "../src/d3d.h"
#include <iostream>
using namespace std;

void resetguy();
void centercam();

const float SPEED_MAX = 7.0;
float speedy = 0;

int bouncer() {
	printf("bouncer start\n");
	
	d3d::clearscene();
	auto& objlist = d3d::scene.children;
	
	// camera
	objlist.push_back( d3d::buildcamera() );
		
	{ // main guy
		auto obj = d3d::buildpyramid();
		obj.id = "guy";
		obj.color = { 1.0, 0, 0, 1.0 };
		obj.y = 1, obj.pitch = 180;
		objlist.push_back( obj );
		resetguy();
	}

	{ // floor
		auto cube = d3d::buildcube();
		cube.id = "floor";
		cube.y = -1.5, cube.scale = 2, cube.color = { 0.3, 0.3, 0.8, 1.0 };
		for (int i=0; i<5; i++) {
			cube.z = i * -5;
			objlist.push_back( cube );
		}
		cube.id = "goal", cube.z = 6*-5, cube.color = { 0.3, 0.8, 0.3, 1.0 };
		objlist.push_back( cube );
	}
	
	// mainloop
	int running = 1;
	int keydiry = 0, keydirx = 0;
	SDL_Event e;
	
	while (running) {
		// key input
		while (SDL_PollEvent(&e))
		switch (e.type) {
			case SDL_QUIT:  running = 0;  break;
			case SDL_KEYDOWN:
			case SDL_KEYUP: {
				int kdown = (e.type == SDL_KEYDOWN);
				switch (e.key.keysym.sym) {
					case SDLK_UP:     keydiry =  1 * kdown;  break;
					case SDLK_DOWN:   keydiry = -1 * kdown;  break;
					case SDLK_LEFT:   keydirx = -1 * kdown;  break;
					case SDLK_RIGHT:  keydirx =  1 * kdown;  break;
				}
				break;
			}
		}
		
		{ // move guy
			auto* guy = d3d::getbyid("guy");
			guy->yaw += 0.2;  // spin
			guy->z += -0.1 * keydiry;  // move by keys
			guy->x +=  0.1 * keydirx;
			// gravity
			speedy = max(speedy-0.1, SPEED_MAX*-1.0);
			for (const auto& o : d3d::scene.children)
				if      (o.id == "floor" && d3d::intersects( *guy, o ))  speedy = SPEED_MAX;
				else if (o.id == "goal"  && d3d::intersects( *guy, o ))  resetguy();
			guy->y += speedy/60.0;
			// reset on drop
			if (guy->y < -15)  resetguy();
		}
		
		centercam();
		d3d::paintf();
		SDL_Delay(16);
	}

	return 0;
}

void resetguy() {
	auto* guy = d3d::getbyid("guy");
	guy->x = guy->z = 0, guy->y = 1, speedy = 0;
}

void centercam() {
	auto* cam = d3d::getbyid("camera");
	auto* target = d3d::getbyid("guy");
	cam->x = target->x;
	cam->y = target->y + 2;
	cam->z = target->z + 3;
	cam->yaw = cam->roll = 0;
	cam->pitch = -50;
}
