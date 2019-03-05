#include "Window.h"
#include "Game.h"
#include <memory>

int main(int argc, const char * argv[]) {
    
//    Window* window = new Window;
    std::unique_ptr<Window> window = std::make_unique<Window>();
    
    window->run();
    
//    delete window;
    
    return 0;
}
