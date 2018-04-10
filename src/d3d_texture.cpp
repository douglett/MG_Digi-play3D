#include "d3d.h"
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <map>
using namespace std;

namespace d3d {

	static map<string, uint32_t> texlist;
	
	int buildtexture(const std::string& id, SDL_Surface* sf) {
		// error checking
		if (id == "" || texlist.count(id) || sf == NULL)  return 1;
		// send texture info to gpu
		uint32_t texID = 0;  // holds texture id
		glGenTextures( 1, &texID );
		glBindTexture( GL_TEXTURE_2D, texID );
			SDL_LockSurface(sf);
				glTexImage2D   ( GL_TEXTURE_2D, 0, GL_RGBA, sf->w, sf->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, sf->pixels );
			SDL_UnlockSurface(sf);
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );  // simple pixel-perfect scaling
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );  // needed?
		glBindTexture( GL_TEXTURE_2D, 0 );  // unbind
		// save
		texlist[id] = texID;
		return 0;
	}
	
	uint32_t gettexture(const std::string& id) {
		if (id == "" || texlist.count(id) == 0)  return 0;
		return texlist.at( id );
	}
	
} // end d3d
