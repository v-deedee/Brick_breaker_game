#include "Bullet.h"

Bullet::Bullet()
{
    x = 0;
    y = 0;
    is_move = false;
    bullet_texture = NULL;
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(bullet_texture);
    bullet_texture = NULL;
}

void Bullet::load_bullet_texture(SDL_Renderer* renderer)
{
    load_texture(renderer, "assets/sprites/Laser_bullet.png", bullet_texture);
}

void Bullet::move()
{
    y -= BULLET_SPEED;
    if (y < PLAY_GROUND_HEIGHT)
    {
        is_move = false;
    }
}

void Bullet::render(SDL_Renderer* renderer)
{
    SDL_Rect bullet_rect = {x, y, BULLET_WIDTH, BULLET_HEIGHT};
    SDL_RenderCopy(renderer, bullet_texture, NULL, &bullet_rect);
}