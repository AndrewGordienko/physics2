#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const double ORBIT_RADIUS = 200.0;
const double ORBIT_SPEED = 0.01;

struct Shape {
    double angle;
    double initialX;
    double initialY;
    double distanceToCenter;
    double radius;
};

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Shape Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window creation error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer creation error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear the renderer with black color
    SDL_RenderClear(renderer);

    // Seed the random number generator
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Calculate the center of the screen
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;

    // Create shapes
    const int NUM_SHAPES = 1000000;
    std::vector<Shape> shapes;
    for (int i = 0; i < NUM_SHAPES; ++i) {
        Shape shape;
        shape.angle = (std::rand() / static_cast<double>(RAND_MAX)) * 2.0 * M_PI;
        shape.radius = 20;

        // Generate random initial position with a gap in the middle
		shape.initialX = (std::rand() / static_cast<double>(RAND_MAX)) * (SCREEN_WIDTH - 200) + 100;
		shape.initialY = (std::rand() / static_cast<double>(RAND_MAX)) * (SCREEN_HEIGHT - 200) + 100;


        // Calculate the distance to the center
        shape.distanceToCenter = std::sqrt(std::pow(shape.initialX - centerX, 2) + std::pow(shape.initialY - centerY, 2));

        shapes.push_back(shape);

        // Print the starting coordinates
        // std::cout << "Starting Coordinate for Shape " << i + 1 << ": (" << shape.initialX << ", " << shape.initialY << ")" << std::endl;
    }

    // Game loop
    bool isRunning = true;
    while (isRunning) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear the renderer with black color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Update and draw shapes
        for (int i = 0; i < NUM_SHAPES; ++i) {
            Shape& shape = shapes[i];

            // Update the position of the shape
            shape.angle += ORBIT_SPEED;
            shape.initialX = centerX + shape.distanceToCenter * std::cos(shape.angle);
            shape.initialY = centerY + shape.distanceToCenter * std::sin(shape.angle);

            // Set the drawing color to white
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // Draw the filled shape at the updated position
            filledCircleColor(renderer, static_cast<int>(shape.initialX), static_cast<int>(shape.initialY), static_cast<int>(shape.radius), 0xFFFFFFFF);
        }

        // Update the screen
        SDL_RenderPresent(renderer);

        // Delay for a short duration
        SDL_Delay(10);
    }

    // Cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
