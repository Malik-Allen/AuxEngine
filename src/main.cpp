#include "AuxEngine.h"

using namespace  AuxEngine;

int main(int argc, char* argv[])
{
    Engine::Get().Start(Mode::Standalone);
    Engine::Get().Run();
    
    return 0;
}