#include "Core.hpp"
#include "EventHandler.hpp"
#include "UDPClient.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    std::vector<std::string> av(argv, argv + argc);

    srand(time(NULL));
    RType::Core* core = new RType::Core(av, 1280, 720, "R-Type");
    delete (core);
}
