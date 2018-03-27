#include "d3d.h"
#include <iostream>
using namespace std;

namespace d3d {

	void scale(std::list<gquad>& quads, float scalef) {
		for (auto& q : quads)
		for (auto& p : q)
			p *= scalef;
	}

	Obj makecube() {
		Obj obj;
		obj.id = "cube", obj.col = {1.0, 1.0, 1.0, 1.0};
		obj.quads = {
			{ // front
			-1, -1, 1,
			-1,  1, 1,
			 1,  1, 1,
			 1, -1, 1,
			},
			{ // back
			-1, -1, 1,
			-1,  1, 1,
			 1,  1, 1,
			 1, -1, 1,
			},
			{ // left
			-1, -1, -1,
			-1, -1,  1,
			-1,  1,  1,
			-1,  1, -1,
			},
			{ // right
			 1, -1, -1,
			 1, -1,  1,
			 1,  1,  1,
			 1,  1, -1,
			},
			{ // top
			-1,  1, -1,
			-1,  1,  1,
			 1,  1,  1,
			 1,  1, -1,
			},
			{ // bottom
			-1, -1, -1,
			-1, -1,  1,
			 1, -1,  1,
			 1, -1, -1,
			}
		};
		scale(obj.quads, 0.5);
		return obj;
	}
	
	int intersects(const Obj& a, const Obj& b) {
		return 0;
	}
	
} // end d3d
