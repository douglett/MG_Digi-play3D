#include "d3d.h"
#include <iostream>
#include <cmath>
using namespace std;

int mainloop();
int mkbullet(float x, float y);

int start_asteroids() {
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
		
		for (int i=0; i<10; i++) {
			auto obj = d3d::makecube();
			obj.id = "asteroid";
			obj.col = {1.0, 0, 0, 1.0};
			obj.y = 5 + i*1.5;
			obj.x = (i%6) - 3;
			scene.children.push_back(obj);
		}
	}
	// go
	mainloop();
	return 0;
}

int mainloop() {
	int running = 1;
	auto* cam = d3d::getbyid("camera");
	auto* ship = d3d::getbyid("ship");
	
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
		switch(e.type) {
			case SDL_QUIT:  running = 0;  break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_LEFT:  if (ship->x > -3) ship->x -= 1;  break;
					case SDLK_RIGHT:  if (ship->x < 3) ship->x += 1;  break;
					case SDLK_SPACE:  mkbullet(ship->x, ship->y + 0.5);  break;
				}
				break;
		}
		
		// move bullets
		for (auto& b : d3d::scene.children) {
			if (b.id != "bullet")  continue;
			// move
			b.y += 0.0008;
			b.yaw += 0.01;
			// collision
			for (auto& a : d3d::scene.children) {
				if (a.id != "asteroid")  continue;
				float dist = sqrt( pow(b.y-a.y, 2) + pow(b.x-a.x, 2) );
				if (dist < float(0.5 + 0.5*0.3))  a.id = b.id = "dead";
			}
		}
		
		// clear dead
		clearstart:
		for (auto it = d3d::scene.children.begin(); it != d3d::scene.children.end(); it++) {
			if (it->id != "dead")  continue;
			d3d::scene.children.erase(it);
			goto clearstart;
		}
		
		// move ship
		ship->y += 0.0002;
		cam->y = ship->y + 5;
		
		d3d::paint();
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
