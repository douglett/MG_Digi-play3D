#include "d3d.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace d3d {

	Obj buildcamera() {
		Obj obj;
		obj.id = "camera", obj.color = {1.0, 1.0, 1.0, 0.7};
		gvec3 p[8] = {  // points
			{-0.3,-0.3,1 }, {-0.3,0.3,1},  {0.3,0.3,1 }, {0.3,-0.3,1 },
			{-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1}
		};
		obj.quads = {
			{ p[0], p[1], p[2], p[3] }, // back
			//{ p[4], p[5], p[6], p[7] }, // front
			{ p[0], p[1], p[5], p[4] }, // left
			{ p[2], p[3], p[7], p[6] }, // right
			{ p[1], p[2], p[6], p[5] }, // top
			{ p[0], p[3], p[7], p[4] }, // bottom
		};
		scale(obj.quads, 0.25);
		return obj;
	}

	Obj buildcube() {
		Obj obj;
		obj.id = "cube", obj.color = {1.0, 1.0, 1.0, 1.0};
		gvec3 p[8] = {  // points
			{-1,-1,1 }, {-1,1,1}, {1,1,1  }, {1,-1,1  },  // front
			{1,-1,-1 }, {1,1,-1}, {-1,1,-1}, {-1,-1,-1}   // back
		};
		obj.quads = {
			{ p[0], p[1], p[2], p[3] }, // front
			{ p[4], p[5], p[6], p[7] }, // back
			{ p[7], p[6], p[1], p[0] }, // left
			{ p[3], p[2], p[5], p[4] }, // right
			{ p[1], p[6], p[5], p[2] }, // top
			{ p[0], p[7], p[4], p[3] }, // bottom
		};
		scale(obj.quads, 0.5);
		return obj;
	}
	
	Obj buildpyramid() {
		Obj obj;
		obj.id = "pyramid";
		gvec3 p[8] = {  // points
			{-1,-1,1 }, {0,1,0}, {0,1,0}, {1,-1,1  },  // front
			{1,-1,-1 }, {0,1,0}, {0,1,0}, {-1,-1,-1}   // back
		};
		obj.quads = {
			{ p[0], p[1], p[2], p[3] }, // front
			{ p[4], p[5], p[6], p[7] }, // back
			{ p[7], p[6], p[1], p[0] }, // left
			{ p[3], p[2], p[5], p[4] }, // right
			{ p[1], p[6], p[5], p[2] }, // top
			{ p[0], p[7], p[4], p[3] }, // bottom
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
	
	// helpers
	
	float dist(const Obj& a, const Obj& b) {
		return sqrt( pow(b.y-a.y, 2) + pow(b.x-a.x, 2) );
	}
	
	int intersects(const Obj& a, const Obj& b) {
		//return ( dist(a, b) < (a.scale + b.scale)/2 );  // method 1 - circular
		if (a.x+a.scale/2 < b.x-b.scale/2 || a.x-a.scale/2 > b.x+b.scale/2)  return 0;  // method 2 - box
		if (a.y+a.scale/2 < b.y-b.scale/2 || a.y-a.scale/2 > b.y+b.scale/2)  return 0;
		if (a.z+a.scale/2 < b.z-b.scale/2 || a.z-a.scale/2 > b.z+b.scale/2)  return 0;
		return 1;
	}
	
	void moverelative(Obj& o, float x, float y, float z) {
		// apply roll, pitch, yaw of object then move
	}
	
} // end d3d
