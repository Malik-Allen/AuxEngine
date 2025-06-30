#include "AuxEngine.h"

using namespace  AuxEngine;

int main(int argc, char* argv[])
{
    Engine::Get().Start();
    Engine::Get().Run();
    
    return 0;
}