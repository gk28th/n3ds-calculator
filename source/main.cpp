#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include "operations.h"
#include "kboard.h"

int main(int argc, char **argv)
{
	
	gfxInitDefault();						// initialize services
	
	PrintConsole topScreen, bottomScreen;	// we need one PrintConsole for each screen
	
	consoleInit(GFX_TOP, &topScreen);		// initialize console for each screen
	consoleInit(GFX_BOTTOM, &bottomScreen); // pass by referece so it can be changed

	consoleSelect(&topScreen);						// use console select to choose which screen to print to
	std::cout << "\x1b[15;16HConsole Demo V1.0.0";  // sent to the top
	std::cout << "\x1b[25;16HPress Start to exit!";

	consoleSelect(&bottomScreen);					// sent to bottom
	std::cout <<"Press A for Addition\n\n";			//treat consoleSelect like a variable. you only have to initialise it once unless you want to change the value of it
	std::cout <<"Press B for Subtraction\n\n";		
	std::cout <<"Press X for Multiplication\n\n";
	std::cout <<"Press Y for Division";

	while (aptMainLoop())	// main loop
	{

		
		hidScanInput();		// Scan all the inputs. This should be done once for each frame
		
		
		u32 kDown = hidKeysDown();				// hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		
		if (kDown & KEY_A) operationNumbers(1); // call functions for operations
		if (kDown & KEY_B) operationNumbers(2); // 1 for add, 2 for sub, 3 for multiplication, 4 for division 
		if (kDown & KEY_X) operationNumbers(3);
		if (kDown & KEY_Y) operationNumbers(4);

		if (kDown & KEY_START) break; 			// break in order to return to hbmenu

			
		gfxSwapBuffers();	// Flush and swap framebuffers
		gfxFlushBuffers();	// do this order apparently 
		gspWaitForVBlank(); // Wait for VBlank
	}

	gfxExit();				// Exit services
	return 0;
}