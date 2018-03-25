#include <SDL2/SDL.h>
#include <string>
#include <list>
#include <array>

namespace d3d {
	// types
	struct   gvec3 { float  x, y, z; };
	struct   gvec4 { float  x, y, z, a; };
	typedef  std::array<float,12>  gquad;
	struct Obj {
		std::string id;
		gvec4 col;
		std::list<gquad> quads;
		float x, y, z, roll, pitch, yaw;
		std::list<Obj> children;
	};
	// main
	extern Obj scene;
	int init();
	int quit();
	int flip();
	int setPerspective(const std::string& perspective);
	int paint();
	// buildobj
	void scale(Obj& obj, float scalef);
	Obj  makecube();
	int  intersects(const Obj& a, const Obj& b);
} // end d3d
