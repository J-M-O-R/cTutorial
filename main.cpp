#include <iostream>
#include <math.h>
/*
#define SDL_MAIN_HANDLED
#include <SDL.h>
*/
#include "screen.h"
#include "swarm.h"
#include <stdlib.h> // take this out if including particle.h
#include <time.h>
using namespace std;
using namespace cTutorial;

int main()
{
    // Intializing the random generator
    srand(time(nullptr));

    Screen screen;
    int red, green, blue;

    if(screen.init()) {
        double screenXscale{Screen::SCREEN_WIDTH/2};
        double screenYscale{Screen::SCREEN_HEIGHT/2};
        Swarm swarm;
        int x,y;
        while(true) {
            // Update particles
            /* He for unknown reasons multiplies by 128. This can make the value of
             * (1+sin(...)) go beyon 255 (the max. valid color range). He does not worry
             * because he trunk the double value of (1+sin(...)) to an int. But, there is
             * still the very small chance of (1+sin(...)) hitting 256, when sin(PI/2) = 1.
             * For this reason he uses an 'unsigned char' which maximum value is 255, when
             * assiggning 255 to the unsigned char the resulting value won't be a progress
             * in the sequence, hence there is a very tiny probabilty of some flickering
             * in the screen. His code is then:
             *    unsigned char green = unsigned char( (1 + sin(elapsed * 0.0001)) * 128 );
             */
            Uint32 elapsed {SDL_GetTicks()};
            /* Instead of clear the screen, let blur it. Which introduces "transition" or trail
             * in the movement of the particles, a more natural efect. Instead of just desappearing
             * and appearing in the next position.
             */
            // screen.clear();
            swarm.update(elapsed);

            red = (1 + sin(elapsed * 0.0001)) * 127.5;
            green = (1 + sin(elapsed * 0.0002)) * 127.5;
            blue = (1 + sin(elapsed * 0.0003)) * 127.5;

            auto particles = swarm.getParticles();
            // Draw particles
            for(auto i: particles) {
                x = (i.m_x + 1) * screenXscale;
                y = i.m_y * screenXscale + screenYscale;
                screen.setpixel(x,y,red,green,blue);
            }
            // Let blur instead of clear.
            screen.boxBlur();
            // Draw screen
            screen.update();
            // Check for messages/events
            if(!screen.processEvents()) {
                break;
            }
        }
        screen.close();
    }
    return 0;
}
