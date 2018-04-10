#include "../src/d3d.h"
#include <iostream>
#include <cmath>
using namespace std;

int  mainloop();
int  mkbullet(float x, float y);
void resetscene();

int start_asteroids() {
	printf("asteroids demo. press R to restart.\n");
	// make scene
	d3d::clearscene();
	auto& scene = d3d::scene;
	{
		auto cam = d3d::makecamera();
		cam.z = 10;
		scene.children.push_back(cam);
		
		auto cube = d3d::makecube();
		cube.id = "ship";
		cube.col = {0, 1.0, 0, 1.0};
		//cube.z = -3;
		scene.children.push_back(cube);
		
		resetscene();
	}
	// go
	mainloop();
	return 0;
}

int mainloop() {
	// consts
	const float 
		HERTZ            = 60.0,
		SPEED_SCENE      = 2.0/HERTZ,  // m/s
		SPEED_SHIP       = 2.8/HERTZ, 
		SPEED_BULLET     = 8.0/HERTZ,
		SPEED_BULLETROT  = 1.0/HERTZ;  // rot/s ?
	// game vars
	int running = 1;
	int gametime = SDL_GetTicks();
	auto* cam = d3d::getbyid("camera");
	auto* ship = d3d::getbyid("ship");
	// movement
	int kleft=0, kright=0, kfire=0;
	float ttfire=0;
	
	while (running) {
		// drawing and frame limit
		int ttdelta = SDL_GetTicks()-gametime;
		if (ttdelta < 1000/HERTZ)  continue;  // short frame
		gametime += 1000/HERTZ;  // advance
		if (SDL_GetTicks()-gametime < 1000/HERTZ)  d3d::paint();  // frameskip
		
		// events
		SDL_Event e;
		while (SDL_PollEvent(&e))
		switch(e.type) {
			case SDL_QUIT:  running = 0;  break;
			case SDL_KEYDOWN:
			case SDL_KEYUP: 
				{
					int kdown = (e.type == SDL_KEYDOWN);
					switch (e.key.keysym.sym) {
						case SDLK_LEFT:   kleft  = kdown;  break;
						case SDLK_RIGHT:  kright = kdown;  break;
						case SDLK_SPACE:  kfire  = kdown;  break;
						case 'r':  if (kdown) resetscene();  break;
					}
				}
				break;
		}
		
		// timers
		ttfire = max(ttfire - 1/HERTZ, 0.0f);
			
		// move bullets
		for (auto& b : d3d::scene.children) {
			if (b.id != "bullet")  continue;
			// move
			b.y   += SPEED_BULLET;
			b.yaw += SPEED_BULLETROT;
			// collision
			for (auto& a : d3d::scene.children) {
				if (a.id != "asteroid")  continue;
				if (dist(a, b) < float(a.scale/2 + b.scale/2))  a.id = b.id = "dead";
			}
		}

		// remove offscreen
		for (auto& o : d3d::scene.children) {
			if (o.id.substr(0,6) == "camera")  continue;
			else if (o.id == "bullet") { if (dist(*ship, o) > 15.0) o.id = "dead"; }
			else if (o.id == "asteroid") { if (o.y - ship->y < -2) o.id = "dead"; }
		}
		
		{ // clear dead
			auto& objs = d3d::scene.children;
			auto it    = objs.begin();
			while (it != objs.end())
				if    (it->id == "dead")  it = objs.erase(it);
				else  it++;
		}
		
		// move ship
		if (kleft  && ship->x > -3.0)  ship->x -= SPEED_SHIP;
		if (kright && ship->x <  3.0)  ship->x += SPEED_SHIP;
		if (kfire && ttfire == 0) { mkbullet(ship->x, ship->y + 0.5);  ttfire = 0.33; }
		ship->y += SPEED_SCENE;  // ship x movement
		cam->y  = ship->y + 5;  // follow ship with camera
	}
	return 0;
}

int mkbullet(float x, float y) {
	auto obj = d3d::makecube();
	obj.id = "bullet";
	obj.col = {1.0, 1.0, 0, 1.0};
	obj.scale = 0.3;
	obj.x = x;
	obj.y = y;
	d3d::scene.children.push_back(obj);
	return 0;
}

void resetscene() {
	// clear asteroids and bullets from scene
	auto& objlist = d3d::scene.children;
	auto  it      = objlist.begin();
	while (it != objlist.end()) {
		if (it->id == "asteroid" || it->id == "bullet" || it->id == "dead") 
			it = objlist.erase(it);
		else
			it++;
	}
	// make asteroids
	auto obj = d3d::makecube();
	obj.id = "asteroid";
	obj.col = {1.0, 0, 0, 1.0};
	obj.scale = 0.8;
	for (int i=0; i<10; i++) {
		obj.y = 10 + i*1.5;
		obj.x = (i%6) - 3;
		objlist.push_back(obj);
	}
	// reset ship
	auto* ship = d3d::getbyid("ship");
	ship->x = ship->y = 0;
}

