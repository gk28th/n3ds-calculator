/*created by gk28th
  File Name: kboard.cpp
  Purpose: to use software keyboard to input numbers 
*/

#include <string>
#include <stdlib.h>
#include <iostream>
#include <3ds.h>

void inputKboard(double long &x, double long &y, bool &inputSucess) // passed by reference so values can be changed
{
	
    PrintConsole topScreen, bottomScreen;   //initialise both screens as consoles
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
    
    SwkbdState swkbd;       // pass by reference so values can be changed
    char textBuffer[10];    // hold the inputed text have to use char array

    swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 8);                                                                             // the type of kboard(numbpad)
    swkbdSetHintText(&swkbd, "Enter 1st Number");                                                                           // the text that shows when nothing is inputed. to use this get rid of SWKBD_FIXED_WIDTH
    swkbdSetPasswordMode(&swkbd, SWKBD_PASSWORD_NONE);                                                                      // no password mode shit
	swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);                                                              // what can be inputed. SWKBD_NOTEMPTY_NOTBLANK disallows empty input or whitespaces
	swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH | SWKBD_ALLOW_HOME | SWKBD_ALLOW_RESET | SWKBD_ALLOW_POWER);                 // when inputing numbers, they are inputed in boxes
	swkbdSetNumpadKeys(&swkbd, L'.', L'0');                                                                                 // the 2 buttons on the left and right. 0 means no button

    
    consoleSelect(&bottomScreen);   // clear screens
    consoleClear();                 // need to make function
    consoleSelect(&topScreen);
    consoleClear();
    
    std::cout << "\x1b[15;13HA to input 1st number";

    while(true)
    {
        hidScanInput();             // scan for input
        u32 kDown = hidKeysDown();  // variable destroyed once you exit out of loop

        if(kDown & KEY_A)           // if a is presses, open the keyboard and sent input to our buffer then break this loop
        {
            swkbdInputText(&swkbd, textBuffer, sizeof(textBuffer) ); // actualy use the keyboard
            break;
        }
        gfxSwapBuffers();             // do this for every fame
		gfxFlushBuffers();            // examples have it in the wrong order apparently
        gspWaitForVBlank();
    }

    x = strtod(textBuffer, NULL);     // x equals to whatever has been inputed

    consoleSelect(&bottomScreen);     // clear screens
    consoleClear();                   // should really create a function to do this
    consoleSelect(&topScreen);
    consoleClear();
    std::cout << "\x1b[15;13HA to input 2nd number";

    while(true)                     // loop cannot be avoided
    {
        hidScanInput();             // scan for input
        u32 kDown = hidKeysDown();

        if(kDown & KEY_A)           // if a is presses, open the keyboard and sent input to our buffer then break this loop
        {
            swkbdInputText(&swkbd, textBuffer, sizeof(textBuffer) ); // actualy use the keyboard
            break;
        }
        gfxSwapBuffers();           // make a function ??
		gfxFlushBuffers();          // search double buffering
        gspWaitForVBlank();
    }

    y = strtod(textBuffer, NULL);    // y equals to whatever has just been inputed

    if(y == 0 && x == 0)        // prevent any divide by 0 errors which can cause crashes
        y = 1.0;

    inputSucess = true;             // confirm that both numbers have been inputed

}