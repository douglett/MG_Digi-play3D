#include "../src/d3d.h"
#include <iostream>
using namespace std;

void resetguy();
void centercam();
int  nextlevel();

const float SPEED_MAX = 7.0;
int game_level = 0;
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
	
	// level setup
	nextlevel();
	
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
					case 'r':  game_level = 0;  nextlevel();  resetguy();  break;
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
				if      (o.id == "floor" && d3d::intersects( *guy, o )) { speedy = SPEED_MAX;  break; }
				else if (o.id == "goal"  && d3d::intersects( *guy, o )) { nextlevel(); resetguy();  break; }
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

int nextlevel() {
	game_level++;
	// clear existing
	auto& objlist = d3d::scene.children;
	for (auto it = objlist.begin(); it != objlist.end(); )
		if (it->id == "floor" || it->id == "goal")  it = objlist.erase(it);
		else  it++;
	// default items
	auto floor = d3d::buildcube();
	floor.id = "floor", floor.y = -1.5, floor.scale = 2, floor.color = { 0.3, 0.3, 0.8, 1.0 };
	auto goal = floor;
	goal.id = "goal", goal.color = { 0.3, 0.8, 0.3, 1.0 };
	// build level
	if (game_level == 1) {
		for (int i=0; i<5; i++) {
			floor.z = i * -5;
			objlist.push_back( floor );
		}
		goal.z = 6*-5;
		objlist.push_back( goal );
		return 0;
	}
	else if (game_level == 2) {
		for (int i=0; i<3; i++) {
			floor.z = i * -7;
			floor.y = i * 3;
			objlist.push_back( floor );
		}
		goal.z = 3 * -7;
		goal.y = 3 * 3;
		objlist.push_back( goal );
		return 0;
	}
	else if (game_level == 3) {
		for (int i=0; i<10; i++)
		for (int x=0; x<3; x++) {
			floor.z = i * -2;
			floor.y = i * 2;
			floor.x = (x - 1) * 2;
			floor.color.x = floor.color.y = ( i % 2 ? 0.3 : 0.2 );
			objlist.push_back( floor );
		}
		goal.z = 10 * -2,  goal.y = 0;
		objlist.push_back( goal );
	}
	// unknown level
	objlist.push_back( floor );
	return 1;
}

