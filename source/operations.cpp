#include <iostream>
#include <3ds.h>
#include "kboard.h"

void operationNumbers(int operation)        // int operation determines what operation to use
{
    PrintConsole topScreen, bottomScreen;   // reinitialise console. because one in main is not static
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
    
    double long x, y;                       // vaiables that hold the numbers inputed
    bool numberInput = false;               // determins if the numbers have been inputed (if be is pressed this is left as false)
    
    consoleSelect(&bottomScreen);
    consoleClear();
    consoleSelect(&topScreen);
    consoleClear();
    // std::cout << operation;              // used for debugging the broken switch statements
    
        if (operation == 1)                                         // using multiple if statements because switch doesnt work
            std::cout << "\x1b[15;15HAddition Mode: B to Cancel";   // maybe idk how to use switch statements 
        if (operation == 2)
           std::cout << "\x1b[15;15HSubtraction Mode: B to Cancel";
        if (operation == 3)
           std::cout << "\x1b[15;15HMultiplication Mode: B to Cancel";
        if (operation == 4)
           std::cout << "\x1b[15;15HDivision Mode: B to Cancel"; 
    
    std::cout << "\x1b[25;16HPress A to input nubers";    
    

    while (true)                            // no option but to enter the loop
    { 
        hidScanInput();                     // scan for input
        u32 kDown = hidKeysDown();          // variable inside loop so it is temporary

        if (kDown & KEY_A)                  // if A is pressed
        {
            inputKboard(x, y, numberInput); // function call to kboard input.  x, y hold the numbers the bool value sets to true if the numbers have been inputed
            
            break;
        }

        if (kDown & KEY_B) break;           // if B is pressed exit this loop
       
		gfxSwapBuffers();                   // need to do this for every frame
		gfxFlushBuffers();                  // put it in this order because the exmample code is wrong so i have read
        gspWaitForVBlank();                 // prevents flickering double buffer
    }
  
    if(numberInput)                         // only happens if the numbers have been sucessfully inputed
    {
        consoleSelect(&bottomScreen);       // idk if consoleClear(); clears both screens
        consoleClear();                     // try making a function for this
        consoleSelect(&topScreen);          
        consoleClear();
        // std::cout << x << y;             // for debugging if the sum is wrong
        std::cout << "\x1b[15;16HThe product is: ";
        if (operation == 1)                 // idk why tf switch statements dont work
            std::cout << x+y;               // havent tried decimal numbers
        if (operation == 2)
            std::cout << x-y;
        if (operation == 3)
            std::cout << x*y;
        if (operation ==4)
            std::cout << x/y; 
    
        std::cout << "\x1b[25;16HPress A to go back";
    
    
        while (true)
        {
            hidScanInput();
            u32 kDown = hidKeysDown();
            if (kDown & KEY_A) break;

            gfxSwapBuffers();              // have to do it for each frame
		    gfxFlushBuffers();             // couldnt tell you how this works
            gspWaitForVBlank();            // just search double buffering
        }
    }

	consoleSelect(&bottomScreen);          // have to reprint this because it doesnt do this again in the loop
    consoleClear();
    std::cout <<"Press A for Addition\n\n";
    std::cout <<"Press B for Subtraction\n\n";
    std::cout <<"Press X for Multiplication\n\n";
    std::cout <<"Press Y for Division";
    consoleSelect(&topScreen);
    consoleClear();
    std::cout << "\x1b[15;16HConsole Demo V1.0.0";
    std::cout << "\x1b[25;16HPress Start to exit!";

}