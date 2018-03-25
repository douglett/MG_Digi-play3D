#include "d3d.h"
#include <iostream>
using namespace std;

namespace d3d {

	void scale(Obj& obj, float scalef) {
		for (auto& q : obj.quads)
		for (auto& p : q)
			p *= scalef;
		for (auto& c : obj.children)
			scale(c, scalef);
	}

	Obj makecube() {
		Obj obj = { .id = "cube", .col = {1.0, 1.0, 1.0, 1.0} };
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
		scale(obj, 0.5);
		return obj;
	}
	
} // end d3d
