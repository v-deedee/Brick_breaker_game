#include "Bullet.h"

Bullet::Bullet()
{
    x = 0;
    y = 0;
    is_move = true;
    is_set_left_start_pos = true;
    is_set_right_start_pos = true;
    //first_play_sound = true;
    bullet_texture = NULL;
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(bullet_texture);
    bullet_texture = NULL;
}

Bullet& Bullet::operator=(const Bullet& other)
{
    this->x = other.x;
    this->y = other.y;
    this->is_move = other.is_move;
    this->bullet_texture = other.bullet_texture;
    return *this;
}

void Bullet::load_bullet_texture(SDL_Renderer* renderer)
{
    load_texture(renderer, "assets/sprites/Laser_bullet.png", bullet_texture);
}

void Bullet::set_left_start_pos(const int& paddle_x, const int& paddle_y)
{
    if (is_set_left_start_pos)
    {
        x = paddle_x + 20;
        y = paddle_y - BULLET_HEIGHT;
        is_set_left_start_pos = false;
    }
}

void Bullet::set_right_start_pos(const int& paddle_x, const int& paddle_y, const int& paddle_width)
{
    if (is_set_right_start_pos)
    {
        x = paddle_x + paddle_width - 20;
        y = paddle_y - BULLET_HEIGHT;
        is_set_right_start_pos = false;
    }
}

void Bullet::move()
{
    y -= BULLET_SPEED;
    if (y < (SCREEN_HEIGHT - PLAY_GROUND_HEIGHT)/2)
    {
        is_move = false;
    }
}

void Bullet::render(SDL_Renderer* renderer, Mix_Chunk* gun_sound)
{
    if (first_play_sound)
    {
        Mix_PlayChannel(-1, gun_sound, 0);
        first_play_sound = false;
    }
    SDL_Rect bullet_rect = {x, y, BULLET_WIDTH, BULLET_HEIGHT};
    SDL_RenderCopy(renderer, bullet_texture, NULL, &bullet_rect);
}