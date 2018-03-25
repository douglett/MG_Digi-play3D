#include "d3d.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	printf("hello world\n");
	if (d3d::init())  return 1;
	
	// test scene
	d3d::scene = d3d::Obj{
		.id = "test",
		.col = { 1.0, 0, 0, 1.0 },
		.quads = {{
			-0.5, -0.5, -3,
			 0.5, -0.5, -3,
			 0.5,  0.5, -3,
			-0.5,  0.5, -3
		}}
	};
	auto cube = d3d::makecube();
	cube.z = -2;
	d3d::scale(cube, 0.3);
	d3d::scene.children.push_back( cube );
	
	int running = 1;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
		switch (e.type) {
			case SDL_QUIT:  running = 0;  break;
		}
		d3d::paint();
		d3d::scene.roll += 0.01;
		d3d::scene.children.begin()->pitch += 0.01;
	}
	
	d3d::quit();
	return 0;
}
