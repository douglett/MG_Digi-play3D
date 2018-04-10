#include "../src/d3d.h"
#include <iostream>
using namespace std;

int texture1() {
	auto* sf = SDL_CreateRGBSurface(0, 256, 256, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
	for (int i=0; i<64; i++) {
		SDL_Rect r = { 0, 0, 256, 256 };
		r.x += i, r.y += i, r.w -= i*2, r.h -= i*2;
		int shade = 170-i;
		SDL_FillRect(sf, &r, SDL_MapRGB(sf->format, shade, shade, shade));
	}
	d3d::buildtexture("tex1", sf);
	d3d::getbyid("cube")->texture = "tex1";
	//d3d::getbyid("cube")->color = { 1.0, 1.0, 1.0, 1.0 };

	int running = 1;
	SDL_Event e;
	
	while (running) {
		while (SDL_PollEvent(&e))
		switch (e.type) {
			case SDL_QUIT:  running = 0;  break;
		}
		
		d3d::getbyid("cube")->yaw += 0.01;
		d3d::paintf();
	}

	return 0;
}
