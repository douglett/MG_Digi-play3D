#include "../src/d3d.h"
#include <iostream>
using namespace std;

int testscene() {
	d3d::clearscene();
	{  // make test scene		
		auto cube = d3d::buildcube();
		cube.color = {0, 1.0, 0, 1.0};
		cube.z = -3;
		//cube.scale = 0.3;
		d3d::scene.children.push_back( cube );
		
		auto cam = d3d::buildcamera();
		cam.x = 1;
		cam.y = 1;
		d3d::scene.children.push_back( cam );
		
		cam.id += "2";
		cam.z = -6;
		d3d::scene.children.push_back( cam );
	}
	
	int running = 1;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
		switch (e.type) {
			case SDL_QUIT:  running = 0;  break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_1:  d3d::cameraid = "camera";  break;
					case SDLK_2:  d3d::cameraid = "camera2";  break;
					case SDLK_3:  d3d::cameraid = "camera3";  break;
				}
				break;
		}
		d3d::paint();
		d3d::flip();
		for (auto* obj = d3d::getbyid(d3d::scene, "cube"); obj!=NULL; obj=NULL)
			obj->pitch += 0.01;
		for (auto* obj = d3d::getbyid(d3d::scene, "camera"); obj!=NULL; obj=NULL)
			obj->yaw = 5;
		for (auto* obj = d3d::getbyid(d3d::scene, "camera2"); obj!=NULL; obj=NULL) {
			// obj->yaw += 0.01;
			obj->yaw = 180;
			obj->roll += 0.01;
		}
	}
	
	return 0;
}
