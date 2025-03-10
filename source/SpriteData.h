#pragma once
#include "globals.hpp"


//simple data class for use with the spriteData array.
struct SpriteData
{
    std::string fileName;
    sf::IntRect bounds;
    int frameCount;
};


//names for the data you want.
enum AnimationNames
{
    P1_GROUND,
    P1_SKID,
    P1_FLY,
    P1_BIRD_GROUND,
    P1_BIRD_FLY,
    DEATH,
    EGG_FALL,
    EGG_HATCH,
    BOUNDER_WALK,
    BOUNDER_FLY,
    ENEMY_BIRD_WALK,
    ENEMY_BIRD_FLY,
    ENEMY_BIRD_SKID,
    HUNTER_WALK,
    HUNTER_FLY,
    SHADOW_WALK,
    SHADOW_FLY,
    TEMP_BACKGROUND,
    DATA_COUNT //this helps make sure array size matches enum count
};


//container for all sprite data. please use the DataNames enum with this.
static const SpriteData spriteData[AnimationNames::DATA_COUNT] =
{
    //all data follows this pattern:
    //(startPixelX, startPixelY, spriteWidth, spriteHeight), frameCount
    {"res/Art/joustSprite.png", sf::IntRect(247, 64, 15, 18), 4},   //P1_GROUND
    {"res/Art/joustSprite.png", sf::IntRect(248, 84, 13, 16), 1},   //P1_SKID
    {"res/Art/joustSprite.png", sf::IntRect(247, 102, 15, 12), 2},  //P1_FLY
    {"res/Art/joustSprite.png", sf::IntRect(248, 136, 13, 18), 4},  //P1_BIRD_GROUND
    {"res/Art/joustSprite.png", sf::IntRect(247, 156, 15, 12), 2},  //P1_BIRD_FLY
    {"res/Art/joustSprite.png", sf::IntRect(247, 173, 13, 13), 3},  //DEATH
    {"res/Art/joustSprite.png", sf::IntRect(248, 286, 7, 6), 3},    //EGG_FALL
	{"res/Art/joustSprite.png", sf::IntRect(0, 0, 0, 0), 0},    //EGG_HATCH *   //this one is super weird
    {"res/Art/joustSprite.png", sf::IntRect(247, 194, 15, 18), 4},  //BOUNDER_WALK
    {"res/Art/joustSprite.png", sf::IntRect(247, 214, 15, 12), 2},  //BOUNDER_FLY
    {"res/Art/joustSprite.png", sf::IntRect(247, 228, 14, 13), 4},  //ENEMY_BIRD_WALK
    {"res/Art/joustSprite.png", sf::IntRect(247, 243, 15, 12), 2},  //ENEMY_BIRD_FLY
    {"res/Art/joustSprite.png", sf::IntRect(247, 257, 15, 12), 1},  //ENEMY_BIRD_SKID
    {"res/Art/enemyAnimations.png", sf::IntRect(0, 0, 13, 18), 4},  //HUNTER_WALK 
    {"res/Art/enemyAnimations.png", sf::IntRect(0, 18, 13, 12), 2}, //HUNTER_FLY 
    {"res/Art/enemyAnimations.png", sf::IntRect(52, 0, 13, 18), 4}, //SHADOW_WALK 
    {"res/Art/enemyAnimations.png", sf::IntRect(52, 18, 13, 12), 2},//SHADOW_FLY 
    {"res/Art/joustSprite.png", sf::IntRect(2, 44, 237, 195), 1}    //TEMP_BACKGROUND *
    //* INDICATES UNFINISHED DO NOT USE
};