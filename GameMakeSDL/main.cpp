#include "window.h"

int main(int argc, char** argv) {
	window myWidow;
	
	

	if (!myWidow.loadMedia()) {
		std::cout << "failed to load media\n";
	}

	myWidow.update();

	return 0;
}