#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <cstdint>
#include <array>
#include <list>

namespace d3d {
	// types
	struct   gvec3 { float  x, y, z; };
	struct   gvec4 { float  x, y, z, a; };
	typedef  std::array<gvec3,4>  gquad;
	struct Obj {
		std::string id;
		float x=0, y=0, z=0, roll=0, pitch=0, yaw=0, scale=1;
		gvec4 color={ 1.0, 1.0, 1.0, 1.0 };
		std::string texture;
		std::list<gquad> quads;
		std::list<Obj> children;
	};
	// main
	extern Obj scene;
	extern std::string cameraid;
	int   init();
	int   quit();
	int   flip();
	int   clearscene();
	int   setPerspective(const std::string& perspective);
	int   paint();
	int   paintf();
	Obj*  getbyid(const std::string& id);
	Obj*  getbyid(Obj& root, const std::string& id);
	// buildobj
	Obj   buildcamera();
	Obj   buildcube();
	Obj   buildpyramid();
	void  scale(std::list<gquad>& quads, float scalef);
	void  translate(std::list<gquad>& quads, float x, float y, float z);
	float dist(const Obj& a, const Obj& b);
	int   intersects(const Obj& a, const Obj& b);
	void  moverelative(Obj& o, float x, float y, float z);
	// textures
	SDL_Surface* qbfont();
	int      buildtexture(const std::string& id, SDL_Surface* sf);
	uint32_t gettexture(const std::string& id);
} // end d3d
