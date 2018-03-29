#include <SDL2/SDL.h>
#include <string>
#include <array>
#include <list>

namespace d3d {
	// types
	struct   gvec3 { float  x, y, z; };
	struct   gvec4 { float  x, y, z, a; };
	typedef  std::array<float,12>  gquad;
	struct Obj {
		std::string id;
		float x=0, y=0, z=0, roll=0, pitch=0, yaw=0, scale=1;
		gvec4 col={ 1.0, 1.0, 1.0, 1.0 };
		std::list<gquad> quads;
		std::list<Obj> children;
	};
	// main
	extern Obj scene;
	int  init();
	int  quit();
	int  flip();
	int  setPerspective(const std::string& perspective);
	int  paint();
	Obj* getbyid(Obj& root, const std::string& id);
	// buildobj
	Obj  makecamera();
	Obj  makecube();
	void scale(std::list<gquad>& quads, float scalef);
	int  intersects(const Obj& a, const Obj& b);
} // end d3d
