#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "CommonFunc.h"

class Bullet : public CommonFunc
{
public:
    const int BULLET_WIDTH = 5;
    const int BULLET_HEIGHT = 25;

    const int BULLET_SPEED = 10;

    Bullet();
    ~Bullet();

    void load_bullet_texture(SDL_Renderer* renderer);
    void move();
    void render(SDL_Renderer* renderer);

    bool get_is_move() {return is_move;};
    void set_is_move(bool value) {is_move = value;};
    void set_x(int value) {x = value;};
    void set_y(int value) {y = value;};

private:
    int x, y;
    bool is_move;
    SDL_Texture* bullet_texture;
};