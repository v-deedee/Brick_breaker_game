#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "CommonFunc.h"

class Items : public CommonFunc
{
public:
    const int FALLING_SPEED = 5;

    const int ITEM_WIDTH = 20;
    const int ITEM_HEIGHT = 25;

    Items();
    ~Items();

    void set_start_pos(const int& start_pos_x, const int& start_pos_y, int& x, int& y);
    void start_falling(int& x, int& y, const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height);
    void render_items(SDL_Renderer* renderer, SDL_Texture* &item_texture, const int& x, const int& y);
    void set_as_default();

    bool get_is_activated() {return is_activated;};
    bool get_is_appeared() {return is_appeared;};
    bool set_is_activated(const bool& value) {is_activated = value;};
    bool set_is_appeared(const bool& value) {is_appeared = value;};

private:
    bool is_activated;
    bool is_appeared;

};


class GunItems : public Items
{
public:
    GunItems();
    ~GunItems();

    void load_gun_items_texture(SDL_Renderer* renderer);
    void set_gun_start_pos(const int& start_pos_x, const int& start_pos_y);
    void gun_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height);
    void render_gun_items(SDL_Renderer* renderer);

private:
    SDL_Texture* gun_item_texture;
    int gun_item_x, gun_item_y;
};


class MultiItems : public Items
{
public:
    MultiItems();
    ~MultiItems();

    void load_multi_items_texture(SDL_Renderer* renderer);
    void set_multi_start_pos(const int& start_pos_x, const int& start_pos_y);
    void multi_item_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height);
    void render_multi_items(SDL_Renderer* renderer);

private:
    SDL_Texture* multi_item_texture;
    int multi_item_x, multi_item_y;

};


class LongItems : public Items
{
public:
    LongItems();
    ~LongItems();

    void load_long_items_texture(SDL_Renderer* renderer);
    void set_long_start_pos(const int& start_pos_x, const int& start_pos_y);
    void long_item_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height);
    void render_long_items(SDL_Renderer* renderer);

private:
    SDL_Texture* long_item_texture;
    int long_item_x, long_item_y;

};


class ShortItems : public Items
{
public:
    ShortItems();
    ~ShortItems();

    void load_short_items_texture(SDL_Renderer* renderer);
    void set_short_start_pos(const int& start_pos_x, const int& start_pos_y);
    void short_item_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height);
    void render_short_items(SDL_Renderer* renderer);

private:
    SDL_Texture* short_item_texture;
    int short_item_x, short_item_y;
    
};


class SpeedUpItems : public Items
{
public:
    SpeedUpItems();
    ~SpeedUpItems();

    void load_speed_up_items_texture(SDL_Renderer* renderer);
    void set_speed_up_start_pos(const int& start_pos_x, const int& start_pos_y);
    void speed_up_item_start_falling(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height);
    void render_speed_up_items(SDL_Renderer* renderer);

private:
    SDL_Texture* speed_up_item_texture;
    int speed_up_item_x, speed_up_item_y;
    
};