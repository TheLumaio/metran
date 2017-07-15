#include <iostream>
#include "engine.h"

#include "editor.h"
#include "playstate.h"

int main(int argc, char** argv)
{

    Engine engine;
    engine.init("Title", 1280, 720);
    engine.changeState("play", new Playstate{&engine});
    engine.start();

    return 0;
}

