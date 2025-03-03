#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include "Ctrl.h"
#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
    // ****** Detected memory leaks! ******
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Ctrl game_ctrl = Ctrl(1200,800);
    game_ctrl.initialize_game(550.f, 5);

    while (game_ctrl.get_window().isOpen()) // 1 -> 2 -> 3 loop
    {
        game_ctrl.close_events();
        game_ctrl.set_game();
        game_ctrl.update_game();

    }
    game_ctrl.terminate_game();

    //game_ctrl.running_game();
    //game_ctrl.terminate_game();
}