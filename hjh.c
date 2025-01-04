#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_DIFFICULTY 5

void generate_simple_hash(unsigned char *input, char *output) {
    int hash_value = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        hash_value += input[i];
    }
    sprintf(output, "%x", hash_value); 
}


int meets_difficulty(char *hash, int difficulty) {
    for (int i = 0; i < difficulty; i++) {
        if (hash[i] != '0') {
            return 0;
        }
    }
    return 1;
}

void visualize_pow(int num_computers) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *window = SDL_CreateWindow("Proof of Work Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    char input[] = "data_for_hashing";
    char hash_output[64];

    int difficulty = MAX_DIFFICULTY;
    int finished_computers = 0;

    while (finished_computers < num_computers) {
        for (int i = 0; i < num_computers; i++) {
            unsigned char modified_input[256];
            sprintf((char *)modified_input, "%s%d", input, i);

            generate_simple_hash(modified_input, hash_output);

            
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect rect = {50 + (i * 120), WINDOW_HEIGHT / 2 - 50, 100, 100};
            SDL_RenderFillRect(renderer, &rect);

            
            if (meets_difficulty(hash_output, difficulty)) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
                finished_computers++;
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(100);
    }

    SDL_Delay(2000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_computers>\n", argv[0]);
        return 1;
    }

    int num_computers = atoi(argv[1]);
    if (num_computers <= 0) {
        printf("Number of computers must be a positive integer.\n");
        return 1;
    }

    visualize_pow(num_computers);
    return 0;
}
