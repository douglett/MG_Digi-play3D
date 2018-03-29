#include "d3d.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	printf("hello world\n");
	if (d3d::init())  return 1;
	
	{  // make test scene
		auto& obj = d3d::scene;
		obj.col = { 1.0, 0, 0, 1.0 };		
		d3d::gquad q = {{
			{-0.5, -0.5, -3},
			{ 0.5, -0.5, -3},
			{ 0.5,  0.5, -3},
			{-0.5,  0.5, -3}
		}};
		obj.quads.push_back(q);
		
		auto cube = d3d::makecube();
		cube.col = {0, 1.0, 0, 1.0};
		cube.z = -2;
		cube.scale = 0.3;
		obj.children.push_back( cube );
		auto cam = d3d::makecamera();
		cam.z = -1.5;
		obj.children.push_back( cam );

		
	}
	
	int running = 1;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
		switch (e.type) {
			case SDL_QUIT:  running = 0;  break;
		}
		d3d::paint();
		//d3d::scene.roll += 0.01;
		for (d3d::Obj* obj = d3d::getbyid(d3d::scene, "cube"); obj!=NULL; obj=NULL)
			obj->pitch += 0.01;
		if (d3d::getbyid(d3d::scene, "camera"))
			d3d::getbyid(d3d::scene, "camera")->roll += 0.01;
	}
	
	d3d::quit();
	return 0;
}
