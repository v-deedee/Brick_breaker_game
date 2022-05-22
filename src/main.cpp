#include "MainControl.h"

int main(int argc, char** argv)
{
	MainControl main_control;

	main_control.initializeSDL();
	main_control.run();
	main_control.close();

	return 0;
}