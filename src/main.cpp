#include "d3d.h"
#include "../games/games.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	printf("hello world\n");
	if (d3d::init())  return 1;
	
	//testscene();
	//start_asteroids();
	texture1();
	
	d3d::quit();
	return 0;
}

