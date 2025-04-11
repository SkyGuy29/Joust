#include "Joust.h"
#include <Windows.h>


int main()
{
#ifdef NDEBUG
    FreeConsole();
#endif

    Joust joustGame;

    joustGame.run();
    return 0;
}

/*
easter eggs are illegal only ostrich eggs here
(paste as many inch cats as you want honestly idc)
*/