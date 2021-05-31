#pragma once
#ifndef __GAME_DEFINE__
#define __GAME_DEFINE__
namespace Define
{
    const int WINDOW_SCREEN_WIDTH = 512;
    const int WINDOW_SCREEN_HEIGHT = 448;

    const int GAME_SCREEN_WIDTH = 512;
    const int GAME_SCREEN_HEIGHT = 384;

    const int BLACK_BOARD_WIDTH = 512;
    const int BLACK_BOARD_HEIGHT = 64;

    const char* const PATH_MAP1_TMX = "Resources/map1/map1.tmx";
    const char* const PATH_BLACKBOARD = "Resources/blackboard.png";

    const char* const PATH_ANIMATION_BIG_GEAR_1 = "Resources/map1/animation_map1/BigGear1.png";
    const char* const PATH_ANIMATION_BIG_GEAR_2 = "Resources/map1/animation_map1/BigGear2.png";
    const char* const PATH_ANIMATION_BIG_GEAR_3 = "Resources/map1/animation_map1/BigGear3.png";
    const char* const PATH_ANIMATION_BIG_GEAR_4 = "Resources/map1/animation_map1/BigGear4.png";
    const char* const PATH_ANIMATION_SMALL_GEAR = "Resources/map1/animation_map1/SmallGear.png";
    const char* const PATH_ANIMATION_CHAIN_1 = "Resources/map1/animation_map1/Chain1.png";
    const char* const PATH_ANIMATION_CHAIN_2 = "Resources/map1/animation_map1/Chain2.png";
    const char* const PATH_ANIMATION_CHAIN_3 = "Resources/map1/animation_map1/Chain3.png";
    const char* const PATH_ANIMATION_CHAIN_4 = "Resources/map1/animation_map1/Chain4.png";
    const char* const PATH_ANIMATION_WATERFALL_1 = "Resources/map1/animation_map1/Waterfall1.png";
    const char* const PATH_ANIMATION_WATERFALL_2 = "Resources/map1/animation_map1/Waterfall2.png";
    const char* const PATH_ANIMATION_WATERFALL_3 = "Resources/map1/animation_map1/Waterfall3.png";
    const char* const PATH_ANIMATION_WATERFALL_4 = "Resources/map1/animation_map1/Waterfall4.png";
    const char* const PATH_ANIMATION_WATERFALL_5 = "Resources/map1/animation_map1/Waterfall5.png";
    const char* const PATH_ANIMATION_WATERFALL_6 = "Resources/map1/animation_map1/Waterfall6.png";
    const char* const PATH_ANIMATION_WATERFALL_7 = "Resources/map1/animation_map1/Waterfall7.png";
    const char* const PATH_ANIMATION_WATERFALL_8 = "Resources/map1/animation_map1/Waterfall8.png";
    const char* const PATH_ANIMATION_WATERFALL_9 = "Resources/map1/animation_map1/Waterfall9.png";
    const char* const PATH_ANIMATION_WATERFALL_10 = "Resources/map1/animation_map1/Waterfall10.png";
    const char* const PATH_ANIMATION_WATERFALL_11 = "Resources/map1/animation_map1/Waterfall11.png";
    const char* const PATH_ANIMATION_WATERFALL_12 = "Resources/map1/animation_map1/Waterfall12.png";

    enum TypeAniMap1 {
        BigGear1 = 169,
        BigGear2 = 170,
        BigGear3 = 183,
        BigGear4 = 184,
        SmallGear = 173,
        Chain1 = 225,
        Chain2 = 253,
        Chain3 = 239,
        Chain4 = 254,
        Waterfall1 = 95,
        Waterfall2 = 96,
        Waterfall3 = 109,
        Waterfall4 = 110,
        Waterfall5 = 151,
        Waterfall6 = 152,
        Waterfall7 = 165,
        Waterfall8 = 166,
        Waterfall9 = 206,
        Waterfall10 = 207,
        Waterfall11 = 220,
        Waterfall12 = 221,
    };

    const float PLAYER_MAX_JUMP_VELOCITY = -350.0f; //van toc nhay lon nhat
    const float PLAYER_MIN_JUMP_VELOCITY = 350.0f; //van toc nhay thap nhat
    const float PLAYER_MAX_RUNNING_SPEED = 150.0f; //toc do chay nhanh nhat cua player
    const float PLAYER_BOTTOM_RANGE_FALLING = 8.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
}
#endif // !__GAME_DEFINE__
