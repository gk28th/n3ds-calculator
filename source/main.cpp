#include <3ds.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{
	// Initialize services
	gfxInitDefault();

	//In this example we need one PrintConsole for each screen
	PrintConsole topScreen, bottomScreen;

	//Initialize console for both screen using the two different PrintConsole we have defined
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	//Before doing any text printing we should select the PrintConsole in which we are willing to write, otherwise the library will print on the last selected/initialized one
	//Let's start by printing something on the top screen
	consoleSelect(&topScreen);
	std::cout << "\x1b[15;16HConsole Demo V1.0.0";
	printf("\x1b[25;16HPress Start to exit!");

	//Now write something else on the bottom screen
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

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();

	return 0;
}
