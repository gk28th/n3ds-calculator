#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include "operations.h"
#include "kboard.h"

int main(int argc, char **argv)
{
	//initialize services
	gfxInitDefault();

	//we need one PrintConsole for each screen
	PrintConsole topScreen, bottomScreen;

	//initialize console for each screen
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	//use console select to choose which screen to print to
	//sent to top
	consoleSelect(&topScreen);
	std::cout << "\x1b[15;16HConsole Demo V1.0.0";
	std::cout << "\x1b[25;16HPress Start to exit!";

	//sent to bottom
	//treat consoleSelect like a variable. you only have to initialise it once unless you want to change the value of it
	consoleSelect(&bottomScreen);
	std::cout <<"Press A for Addition\n\n";
	std::cout <<"Press B for Subtraction\n\n";
	std::cout <<"Press X for Multiplication\n\n";
	std::cout <<"Press Y for Division";

	// Main loop
	while (aptMainLoop())
	{

		//Scan all the inputs. This should be done once for each frame
		hidScanInput();
		
		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		
		if (kDown & KEY_A) operationNumbers(1); //call functions for operations
		if (kDown & KEY_B) operationNumbers(2);
		if (kDown & KEY_X) operationNumbers(3);
		if (kDown & KEY_Y) operationNumbers(4);

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		// Flush and swap framebuffers	
		gfxSwapBuffers();
		gfxFlushBuffers();
		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();

	return 0;
}
