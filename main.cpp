// Example program:
// Using SDL2 to create an application window

#include "SDL.h"
#include <iostream>

bool coord_within_rect(int x, int y, const SDL_Rect& rect) {
  return
    x > rect.x && x < rect.x + rect.w &&
    y > rect.y && y < rect.y + rect.h;
}

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer
    SDL_Surface* testBmp = SDL_LoadBMP("test.bmp");

    if(!testBmp) {
      SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        "Failed to load test.bmp",
        SDL_GetError(),
        NULL
      );
      return 1;
    }

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Test",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
      window,
      -1,
      0
    );

    SDL_Texture* testBmpTexture = SDL_CreateTextureFromSurface(renderer, testBmp);

    bool quitting = false;

    int boxPositionX = 0;
    int boxPositionY = 0;

    int drawColorR = 255;
    int drawColorG = 0;
    int drawColorB = 0;

    bool mouseDown = false;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 25;
    rect.h = 25;

    SDL_ShowWindow(window);

    while(!quitting) {
      SDL_Event event;
      while(SDL_PollEvent(&event)) {
        switch(event.type) {
          case SDL_QUIT:
            quitting = true;
            break;
          case SDL_MOUSEWHEEL:
            rect.w += event.wheel.y;
            rect.h += event.wheel.y;
            break;
          case SDL_MOUSEBUTTONDOWN:
            if(coord_within_rect(event.button.x, event.button.y, rect)) {
              if(event.button.button == SDL_BUTTON_LEFT) {
                mouseDown = true;
                drawColorR = 0;
                drawColorG = 255;
                drawColorB = 0;
                SDL_SetRelativeMouseMode(SDL_TRUE);
              }
            }

            break;
          case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT) {
              mouseDown = false;
              drawColorR = 255;
              drawColorG = 0;
              drawColorB = 0;
              SDL_SetRelativeMouseMode(SDL_FALSE);
            }
            break;
          case SDL_MOUSEMOTION:
            if(mouseDown) {
              rect.x += event.motion.xrel;
              rect.y += event.motion.yrel;
            }

            break;
        }
      }

      if(!mouseDown) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
      }

      SDL_SetRenderDrawColor(renderer, drawColorR, drawColorG, drawColorB, 255);

      SDL_RenderCopy(renderer, testBmpTexture, NULL, &rect);

      SDL_RenderDrawRect(renderer, &rect);

      SDL_RenderPresent(renderer);
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);
    // Clean up
    SDL_Quit();
    return 0;
}
