#ifndef SCREEN_H
#define SCREEN_H

#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace cTutorial {

class Screen {
public:
    const static int SCREEN_WIDTH {800};
    const static int SCREEN_HEIGHT {600};

    Screen();
    bool init();
    void update();
    void setpixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    bool processEvents();
    void close();
    void clear();
    void boxBlur();
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    Uint32* m_buffer1;
    Uint32* m_buffer2;
    Uint32* m_temp;

    SDL_Event m_event;
}; // class Screen

} // namespace cTutorial


#endif // SCREEN_H
