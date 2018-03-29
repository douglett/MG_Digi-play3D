#include "d3d.h"
#include <iostream>
using namespace std;

namespace d3d {

	Obj makecamera() {
		Obj obj;
		obj.id = "camera", obj.col = {1.0, 1.0, 1.0, 0.7};
//		float p[8*3] = {  // points
//			-1,-1,1,   -1,1,1,   1,1,1,   1,-1,1,
//			-1,-1,-1,  -1,1,-1,  1,1,-1,  1,-1,-1
//		};
//		obj.quads = {
//			{ // front
//			p[0],p[1],p[2],
//			p[3],p[4],p[5],
//			p[6],p[7],p[8],
//			p[9],p[10],p[11]
//			},
//			{ // back
//			p[12],p[13],p[14],
//			p[15],p[16],p[17],
//			p[18],p[19],p[20],
//			p[21],p[22],p[23]
//			},
//			{ // left
//			p[0], p[1], p[2],
//			p[3], p[4], p[5],
//			p[15],p[16],p[17],
//			p[12],p[13],p[14]
//			},
//			{ // right
//			p[6],p[7], p[8],
//			p[9],p[10],p[11],
//			p[21],p[22],p[23],
//			p[18],p[19],p[20]
//			},
//		};
		
		gvec3 p[8] = {  // points
			{-1,-1,1 }, {-1,1,1},  {1,1,1 }, {1,-1,1 },
			{-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1}
		};
		obj.quads = {
			{ // front
			p[0].x, p[0].y, p[0].z,
			p[1].x, p[1].y, p[1].z,
			p[2].x, p[2].y, p[2].z,
			p[3].x, p[3].y, p[3].z
			},
			{ // back
			p[4].x, p[4].y, p[4].z,
			p[5].x, p[5].y, p[5].z,
			p[6].x, p[6].y, p[6].z,
			p[7].x, p[7].y, p[7].z
			},
			{ // left
			p[0].x, p[0].y, p[0].z,
			p[1].x, p[1].y, p[1].z,
			p[5].x, p[5].y, p[5].z,
			p[4].x, p[4].y, p[4].z
			},
			{ // right
			p[2].x, p[2].y, p[2].z,
			p[3].x, p[3].y, p[3].z,
			p[7].x, p[7].y, p[7].z,
			p[6].x, p[6].y, p[6].z
			},
			{ // top
			p[1].x, p[1].y, p[1].z,
			p[2].x, p[2].y, p[2].z,
			p[6].x, p[6].y, p[6].z,
			p[5].x, p[5].y, p[5].z
			},
			{ // bottom
			p[0].x, p[0].y, p[0].z,
			p[3].x, p[3].y, p[3].z,
			p[7].x, p[7].y, p[7].z,
			p[4].x, p[4].y, p[4].z
			}
		};
		
		scale(obj.quads, 0.25);
		return obj;
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
	
	void scale(std::list<gquad>& quads, float scalef) {
		for (auto& q : quads)
		for (auto& p : q)
			p *= scalef;
	}
	
	int intersects(const Obj& a, const Obj& b) {
		return 0;
	}
	
} // end d3d
