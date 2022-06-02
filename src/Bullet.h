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
    const int BULLET_WIDTH = 4;
    const int BULLET_HEIGHT = 20;

    const int BULLET_SPEED = 10;

    Bullet();
    ~Bullet();

    Bullet& operator=(const Bullet& other);

    void load_bullet_texture(SDL_Renderer* renderer);
    void set_left_start_pos(const int& paddle_x, const int& paddle_y);
    void set_right_start_pos(const int& paddle_x, const int& paddle_y, const int& paddle_width);
    void move();
    void render(SDL_Renderer* renderer, Mix_Chunk* gun_sound);

    bool get_is_move() {return is_move;};
    void set_is_move(const bool& value) {is_move = value;};
    void set_x(const int& value) {x = value;};
    void set_y(const int& value) {y = value;};
    int get_x() {return x;};
    int get_y() {return y;};
    bool get_first_play_sound() { return first_play_sound; };
    void set_first_play_sound(const bool& value) { first_play_sound = value; };

private:
    int x, y;
    bool is_move;
    bool is_set_left_start_pos;
    bool is_set_right_start_pos;
    bool first_play_sound = true;
    SDL_Texture* bullet_texture;
};