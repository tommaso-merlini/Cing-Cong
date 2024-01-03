#include <SDL2/SDL.h>  
#include <stdbool.h>  

bool canMoveFurtherDown(SDL_Rect* player, int windowHeight);
bool canMoveFurtherUp(SDL_Rect* player);
bool hasBallTouchedPlayerRight(SDL_Rect* player, SDL_Rect* ball);
bool hasBallTouchedPlayerLeft(SDL_Rect* player, SDL_Rect* ball);
bool hasBallTouchedTop(SDL_Rect* ball);
bool hasBallTouchedBottom(SDL_Rect* ball, int windowHeight);

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event e;

    int windowWidth = 1920;
    int windowHeight = 1080;
    int playerWidth = 50;
    int playerHeight = 400;
    bool isRunning = true;

    //objects
    SDL_Rect playerLeft = {0, windowHeight / 2 - 200, playerWidth, playerHeight};
    SDL_Rect playerRight = {windowWidth - playerWidth, windowHeight / 2 - 200, playerWidth, playerHeight};
    SDL_Rect ball = {windowWidth / 2, windowHeight / 2, 20, 20};

    //velocity
    int ballVelocityX = 10;
    int ballVelocityY = 2;
    int playerStep = 10;

    //ballMovements
    int ballNextStepX = ballVelocityX;
    int ballNextStepY = 0;

    bool isPlayerRightMovingUp;
    bool isPlayerRightMovingDown;
    bool isPlayerLeftMovingUp;
    bool isPlayerLeftMovingDown;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer);
    
    while(isRunning) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                isRunning = false;
            }

            //keyboard inputs
            if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_UP && canMoveFurtherUp(&playerLeft))
                    playerLeft.y -= playerStep;
                    isPlayerLeftMovingUp = true;
                if(e.key.keysym.sym == SDLK_DOWN && canMoveFurtherDown(&playerLeft, windowHeight))
                    playerLeft.y += playerStep;
                    isPlayerRightMovingDown = true;
                if(e.key.keysym.sym == SDLK_w && canMoveFurtherUp(&playerRight))
                    playerRight.y -= playerStep;
                    isPlayerRightMovingUp = true;
                if(e.key.keysym.sym == SDLK_s && canMoveFurtherDown(&playerRight, windowHeight))
                    playerRight.y += playerStep;
                    isPlayerRightMovingDown = true;
            } 
            if (e.type == SDL_KEYUP) {
                    isPlayerLeftMovingUp = false;
                    isPlayerLeftMovingDown = false;
                    isPlayerRightMovingUp = false;
                    isPlayerRightMovingDown = false;
            }
        }


        //clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if(hasBallTouchedPlayerRight(&playerRight, &ball)) {
            ballNextStepX = -ballVelocityX;

            if(isPlayerRightMovingDown) {
                ballNextStepY = ballVelocityY;
            }

            if(isPlayerRightMovingUp) {
                ballNextStepY = -ballVelocityY;
            }
        }

        if(hasBallTouchedPlayerLeft(&playerLeft, &ball)) {
            ballNextStepX = ballVelocityX;

            if(isPlayerLeftMovingDown) {
                ballNextStepY = ballVelocityY;
            }

            if(isPlayerLeftMovingUp) {
                ballNextStepY = -ballVelocityY;
            }
        }

        if(hasBallTouchedTop(&ball)) {
            ballNextStepY = ballVelocityY;
        }

        if(hasBallTouchedBottom(&ball, windowHeight)) {
            ballNextStepY = -ballVelocityY;
        }

        ball.x += ballNextStepX;
        ball.y += ballNextStepY;

        //render players
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &playerLeft);
        SDL_RenderFillRect(renderer, &playerRight);
        SDL_RenderFillRect(renderer, &ball);


        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    return 0;
}

bool canMoveFurtherDown(SDL_Rect* player, int windowHeight) {
    return (player->y + player->h < windowHeight);
}

bool canMoveFurtherUp(SDL_Rect* player) {
    return (player->y > 0);
}

bool hasBallTouchedPlayerRight(SDL_Rect* player, SDL_Rect* ball) {
    return (ball->x + 20 == player->x && (ball->y > player->y && ball->y < player->y + 400));
}

bool hasBallTouchedPlayerLeft(SDL_Rect* player, SDL_Rect* ball) {
    return (ball->x == player->x + 50 && (ball->y > player->y && ball->y < player->y + 400));
}

bool hasBallTouchedTop(SDL_Rect* ball) {
    return (ball->y == 0);
}

bool hasBallTouchedBottom(SDL_Rect* ball, int windowHeight) {
    return (ball->y + 20 == windowHeight);
}