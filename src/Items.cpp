#include "Items.h"

Items::Items()
{
    is_activated = false;
    is_appeared = false;
}
Items::~Items()
{

}
void Items::set_start_pos(const int& start_pos_x, const int& start_pos_y, int& x, int& y)
{
    x = start_pos_x;
    y = start_pos_y;
}
void Items::start_falling(int& x, int& y, const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height)
{
    y += FALLING_SPEED;
    if (y + ITEM_HEIGHT > PLAY_GROUND_HEIGHT + (SCREEN_HEIGHT - PLAY_GROUND_HEIGHT)/2)
    {
        is_appeared = false;
    }
    SDL_Rect item_rect = {x, y, ITEM_WIDTH, ITEM_HEIGHT};
    SDL_Rect paddle_rect = {paddle_x, paddle_y, paddle_width, paddle_height};
    if (SDL_HasIntersection(&item_rect, &paddle_rect))
    {
        is_activated = true;
    }
}
void Items::render_items(SDL_Renderer* renderer, SDL_Texture* &item_texture, const int& x, const int& y)
{
    if (is_appeared)
    {
        SDL_Rect item_rect = {x, y, ITEM_WIDTH, ITEM_HEIGHT};
        SDL_RenderCopy(renderer, item_texture, NULL, &item_rect);
    }
    if (is_activated)
    {
        is_appeared = false;
    }
}
void Items::set_as_default()
{
    is_activated = false;
    is_appeared = false;
}


GunItems::GunItems()
{
    set_is_activated(false);
    set_is_appeared(false);
    gun_item_x = 0;
    gun_item_y = 0;
}
GunItems::~GunItems()
{
    SDL_DestroyTexture(gun_item_texture);
    gun_item_texture = NULL;
}
void GunItems::load_gun_items_texture(SDL_Renderer* renderer)
{
    load_texture(renderer, "assets/sprites/Gun_item.png", gun_item_texture);
}
void GunItems::render_gun_items(SDL_Renderer* renderer)
{
    render_items(renderer, gun_item_texture, gun_item_x, gun_item_y);
}
void GunItems::set_gun_start_pos(const int& start_pos_x, const int& start_pos_y)
{
    set_start_pos(start_pos_x, start_pos_y, gun_item_x, gun_item_y);
}
void GunItems::gun_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height)
{
    start_falling(gun_item_x, gun_item_y, paddle_x, paddle_y, paddle_width, paddle_height);
}


MultiItems::MultiItems()
{
    set_is_activated(false);
    set_is_appeared(false);
    multi_item_x = 0;
    multi_item_y = 0;   
}
MultiItems::~MultiItems()
{
    SDL_DestroyTexture(multi_item_texture);
    multi_item_texture = NULL;
}
void MultiItems::load_multi_items_texture(SDL_Renderer* renderer)
{
    load_texture(renderer, "assets/sprites/Multi_ball_item.png", multi_item_texture);
}
void MultiItems::set_multi_start_pos(const int& start_pos_x, const int& start_pos_y)
{
    set_start_pos(start_pos_x, start_pos_y, multi_item_x, multi_item_y);
}
void MultiItems::multi_item_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height)
{
    start_falling(multi_item_x, multi_item_y, paddle_x, paddle_y, paddle_width, paddle_height);
}
void MultiItems::render_multi_items(SDL_Renderer* renderer)
{
    render_items(renderer, multi_item_texture, multi_item_x, multi_item_y);
}


LongItems::LongItems()
{
    set_is_activated(false);
    set_is_appeared(false);
    long_item_x = 0;
    long_item_y = 0;
}
LongItems::~LongItems()
{
    SDL_DestroyTexture(long_item_texture);
    long_item_texture = NULL;
}
void LongItems::load_long_items_texture(SDL_Renderer* renderer)
{
    load_texture(renderer, "assets/sprites/Long_item.png", long_item_texture);
}
void LongItems::set_long_start_pos(const int& start_pos_x, const int& start_pos_y)
{
    set_start_pos(start_pos_x, start_pos_y, long_item_x, long_item_y);
}
void LongItems::long_item_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height)
{
    start_falling(long_item_x, long_item_y, paddle_x, paddle_y, paddle_width, paddle_height);
}
void LongItems::render_long_items(SDL_Renderer* renderer)
{
    render_items(renderer, long_item_texture, long_item_x, long_item_y);
}


ShortItems::ShortItems()
{
    set_is_activated(false);
    set_is_appeared(false);
    short_item_x = 0;
    short_item_y = 0;
}
ShortItems::~ShortItems()
{
    SDL_DestroyTexture(short_item_texture);
    short_item_texture = NULL;
}
void ShortItems::load_short_items_texture(SDL_Renderer* renderer)
{
    load_texture(renderer, "assets/sprites/Short_item.png", short_item_texture);
}
void ShortItems::set_short_start_pos(const int& start_pos_x, const int& start_pos_y)
{
    set_start_pos(start_pos_x, start_pos_y, short_item_x, short_item_y);
}
void ShortItems::short_item_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height)
{
    start_falling(short_item_x, short_item_y, paddle_x, paddle_y, paddle_width, paddle_height);
}
void ShortItems::render_short_items(SDL_Renderer* renderer)
{
    render_items(renderer, short_item_texture, short_item_x, short_item_y);
}


SpeedUpItems::SpeedUpItems()
{
    set_is_activated(false);
    set_is_appeared(false);
    speed_up_item_x = 0;
    speed_up_item_y = 0;
}
SpeedUpItems::~SpeedUpItems()
{
    SDL_DestroyTexture(speed_up_item_texture);
    speed_up_item_texture = NULL;
}
void SpeedUpItems::load_speed_up_items_texture(SDL_Renderer* renderer)
{
    load_texture(renderer, "assets/sprites/Speed_up_item.png", speed_up_item_texture);
}
void SpeedUpItems::set_speed_up_start_pos(const int& start_pos_x, const int& start_pos_y)
{
    set_start_pos(start_pos_x, start_pos_y, speed_up_item_x, speed_up_item_y);
}
void SpeedUpItems::speed_up_item_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height)
{
    start_falling(speed_up_item_x, speed_up_item_y, paddle_x, paddle_y, paddle_width, paddle_height);
}
void SpeedUpItems::render_speed_up_items(SDL_Renderer* renderer)
{
    render_items(renderer, speed_up_item_texture, speed_up_item_x, speed_up_item_y);
}