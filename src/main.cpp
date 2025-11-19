#include <entt/entt.hpp>
#include <iostream>
#include "view/App.h"
int main()
{
    try
    {
        App app("害虫杀", 1280, 720);
        app.run();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return -1;
    }
}