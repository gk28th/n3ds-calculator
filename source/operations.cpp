#include <iostream>
#include <3ds.h>
#include "kboard.h"

void operationNumbers(int operation)
{
    PrintConsole topScreen, bottomScreen;
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
    
    double long x, y;
    bool numberInput = false;
    
    consoleSelect(&bottomScreen);
    consoleClear();
    consoleSelect(&topScreen);
    consoleClear();
    std::cout << operation;    
    
        if (operation == 1)                                         // using multiple if statements because switch doesnt work
            std::cout << "\x1b[15;15HAddition Mode: B to Cancel";
        if (operation == 2)
           std::cout << "\x1b[15;15HSubtraction Mode: B to Cancel";
        if (operation == 3)
           std::cout << "\x1b[15;15HMultiplication Mode: B to Cancel";
        if (operation == 4)
           std::cout << "\x1b[15;15HDivision Mode: B to Cancel"; 
    
    std::cout << "\x1b[25;16HPress A to input nubers";    
    

    while (true)
    { 
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_A)
        {
            inputKboard(x, y, numberInput);
            
            break;
        }

        if (kDown & KEY_B) break;
       
		gfxSwapBuffers();
		gfxFlushBuffers();
        gspWaitForVBlank();   
    }
  
    if(numberInput)
    {
        consoleSelect(&bottomScreen);
        consoleClear();
        consoleSelect(&topScreen);
        consoleClear();
        std::cout << x << y;
        std::cout << "\x1b[15;16HThe product is: ";
        
        if (operation == 1)         // idk why tf switch statements dont work
            std::cout << x+y;
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

            gfxSwapBuffers();
		    gfxFlushBuffers();
            gspWaitForVBlank();
        }
    }

	consoleSelect(&bottomScreen);
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