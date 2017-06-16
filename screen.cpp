#include "screen.h"

namespace cTutorial {

Screen::Screen() :
    m_window{nullptr},m_renderer{nullptr},m_texture{nullptr},m_buffer1{nullptr},m_buffer2{nullptr} {
}

bool Screen::init() {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }
    // The window where graphics will be displayed
    m_window = SDL_CreateWindow("Particle Fire Explosion",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(m_window == nullptr) {
        SDL_Quit();
        return false;
    }
    // Renderer: what will write in the window
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(m_renderer == nullptr) {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    // What will be rendered by the renderer
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
                                  SCREEN_WIDTH, SCREEN_HEIGHT);
    if(m_texture == nullptr) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    return true;
}

void Screen::update() {
    SDL_UpdateTexture(m_texture, nullptr, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
}

void Screen::boxBlur() {
    /* Box Blur is a blurring(?) technique. Another more natural, i.e. better looking, technique
     * is Gaussian Blur.
     */
    // Swapping buffers.
    m_temp = m_buffer1;
    m_buffer1 = m_buffer2;
    m_buffer2 = m_temp;

    for(int y{0}; y < SCREEN_HEIGHT; y++) {
        for(int x{0}; x < SCREEN_WIDTH; x++) {
            /*  0 0 0   The Box Blur technique is to average the color of the surrounding pixels
             *  0 1 0   of a pixel (plus the pixel itselft), and update with this value the color
             *  0 0 0   of the pixel.
             */
            int redTotal{0}, greenTotal{0}, blueTotal{0};
            for(int row{-1}; row <= 1; row++) {
                for(int col{-1}; col <= 1; col++) {
                    int currentX{x + col};
                    int currentY{y + row};
                    if(currentX >= 0 && currentX < SCREEN_WIDTH &&
                       currentY >= 0 && currentY < SCREEN_HEIGHT){
                        Uint32 color{m_buffer2[currentY*SCREEN_WIDTH + currentX]};

                        Uint8 red{color >> 24}, green{color >> 16}, blue{color >> 8};

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }
                }
            }
            Uint8 red{redTotal / 9}, green{greenTotal / 9}, blue{blueTotal / 9};

            setpixel(x,y,red,green,blue);
        }
    }
}

void Screen::clear() {
    memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}

void Screen::setpixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

    /* This checking of EVERY pixel of the screen for not plotting ouside the screen
     * area is very inefficient. It's better to look for other way, e.g. make sure
     * no pixel is generated outside the screen.
     */
    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }
    Uint32 color {0};
    // RGBA
    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

bool Screen::processEvents() {
    while(SDL_PollEvent(&m_event)) {
        if(m_event.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

void Screen::close() {
    delete [] m_buffer1;
    delete [] m_buffer2;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

} // namespace cTutorial
