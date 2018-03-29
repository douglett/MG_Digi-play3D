#include "d3d.h"
#include <iostream>
using namespace std;

namespace d3d {

	Obj makecamera() {
		Obj obj;
		obj.id = "camera", obj.col = {1.0, 1.0, 1.0, 0.7};
		gvec3 p[8] = {  // points
			{-0.3,-0.3,1 }, {-0.3,0.3,1},  {0.3,0.3,1 }, {0.3,-0.3,1 },
			{-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1}
		};
		obj.quads = {
			//{ p[0], p[1], p[2], p[3] }, // front
			{ p[4], p[5], p[6], p[7] }, // back
			{ p[0], p[1], p[5], p[4] }, // left
			{ p[2], p[3], p[7], p[6] }, // right
			{ p[1], p[2], p[6], p[5] }, // top
			{ p[0], p[3], p[7], p[4] }, // bottom
		};
		scale(obj.quads, 0.25);
		return obj;
	}

	Obj makecube() {
		Obj obj;
		obj.id = "cube", obj.col = {1.0, 1.0, 1.0, 1.0};
		gvec3 p[8] = {  // points
			{-1,-1,1 }, {-1,1,1},  {1,1,1 }, {1,-1,1 },
			{-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1}
		};
		obj.quads = {
			{ p[0], p[1], p[2], p[3] }, // front
			{ p[4], p[5], p[6], p[7] }, // back
			{ p[0], p[1], p[5], p[4] }, // left
			{ p[2], p[3], p[7], p[6] }, // right
			{ p[1], p[2], p[6], p[5] }, // top
			{ p[0], p[3], p[7], p[4] }, // bottom
		};
		scale(obj.quads, 0.5);
		return obj;
	}
	
	void scale(std::list<gquad>& quads, float scalef) {
		for (auto& q : quads)
		for (auto& p : q)
			p.x *= scalef, p.y *= scalef, p.z *= scalef;
	}
	
	void translate(std::list<gquad>& quads, float x, float y, float z) {
		for (auto& q : quads)
		for (auto& p : q)
			p.x += x, p.y += y, p.z += z;
	}
	
	int intersects(const Obj& a, const Obj& b) {
		return 0;
	}
	
} // end d3d
