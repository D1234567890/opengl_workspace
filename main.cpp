#define STB_IMAGE_IMPLEMENTATION
#define PI 3.14159265358979323

#include "SDL2/SDL.h"
#include "OpenGL/gl.h"
#include "stb_image.h"
#include <math.h>

void drawCircle(int x, int y, int r){
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_MULTISAMPLE);

        /*glTexCoord2f(0, 0);
        glVertex2f(-1, 1);
        glTexCoord2f(1, 0);
        glVertex2f(1, 1);
        glTexCoord2f(0, 1);
        glVertex2f(-1, -1);
        glTexCoord2f(0, 1);
        glVertex2f(-1, -1);
        glTexCoord2f(1, 1);
        glVertex2f(1, -1);
        glTexCoord2f(1, 0);
        glVertex2f(1, 1);*/

        glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(0.5, 0.5);
        glVertex2f(x, y);
        glTexCoord2f(0.5, 1);
        glVertex2f(x, y + r);

        for (int i = 0; i < 10000; i++) {
            glVertex2f(x + sin(((2 * PI) / 10000) * i) * r, y + cos(((2 * PI) / 10000) * i) * r);
        }
        
        glEnd();
}

int main(int argc, char** argv){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Mantle", 100, 100, 1000, 1000, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_Event event;

    glClearColor(0, 0, 0, 0);

    bool isRunning = true;

    unsigned char texData[] = {255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 0, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 255, 0, 0, 255};

    int w, h, n;
    //unsigned char *texData = stbi_load("rat.jpg", &w, &h, &n, 0);
    unsigned int textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 3, 3, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);

    while(isRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: {
                    isRunning = false;
                }
                case SDL_KEYDOWN: {
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;
                    }
                    break;
                }
            }
        }
        drawCircle(250, 250, 250);
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);

    return 0;
}

