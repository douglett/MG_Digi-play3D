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
		float roll, pitch, yaw;
		std::list<Obj> children;
	};
	// members
	extern Obj scene;
	// methods
	int init();
	int quit();
	int flip();
	int setPerspective(const std::string& perspective);
	int paint();
} // end d3d
