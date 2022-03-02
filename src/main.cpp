#include <p6/p6.h>
#include <iostream>
#include "menu.h"

int main()
{
    // show_menu();
    auto ctx = p6::Context{{1280, 720, "Window"}};
    ctx.start();
}