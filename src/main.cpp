#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>

#include "Engine.hpp"

using namespace cgf;

int main(int argc, char *argv[])
{
    Engine engine{};

    try
    {
        engine.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
