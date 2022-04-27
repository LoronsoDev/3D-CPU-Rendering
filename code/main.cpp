#include "View.hpp"
#include <SFML/Window.hpp>

using namespace sf;
using namespace example;

int main ()
{
    // Create the window and the view that will be shown within the window:

    constexpr auto window_width  = 800u;
    constexpr auto window_height = 600u;

    View::CameraDemoMove camMovement = View::CameraDemoMove::stopped;
    Window window(VideoMode(window_width, window_height), "Practica 3D", Style::Default);
    View   view(window_width, window_height, camMovement);

    window.setVerticalSyncEnabled (true);

    // Run the main loop:

    bool exit = false;

    do
    {
        Event event;

        while (window.pollEvent (event))
        {
            //Por alguna razon si no se comprueba KeyPressed se llama al evento key.A cuando la ventana gana el focus ¿?¿?¿?
            if (event.type == event.KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    exit = true;
                }
                if (event.key.code == Keyboard::W)
                {
                    camMovement = View::CameraDemoMove::forward;
                }
                if (event.key.code == Keyboard::S)
                {
                    camMovement = View::CameraDemoMove::back;
                }
                if (event.key.code == Keyboard::A)
                {
                    camMovement = View::CameraDemoMove::left;
                }
                if (event.key.code == Keyboard::D)
                {
                    camMovement = View::CameraDemoMove::right;
                }
                if (event.key.code == Keyboard::Up)
                {
                    camMovement = View::CameraDemoMove::lookUp;
                }
                if (event.key.code == Keyboard::Down)
                {
                    camMovement = View::CameraDemoMove::lookDown;
                }
                if (event.key.code == Keyboard::Left)
                {
                    camMovement = View::CameraDemoMove::lookLeft;
                }
                if (event.key.code == Keyboard::Right)
                {
                    camMovement = View::CameraDemoMove::lookRight;
                }
            }

            if (event.type == event.KeyReleased)
            {
                camMovement = View::CameraDemoMove::stopped;
            }
            

            if (event.type == Event::Closed) exit = true;
        }

        view.update ();
        view.render ();
        window.display ();


    }
    while (not exit);

    return 0;
}
