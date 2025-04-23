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
	NONE, //this is used to indicate no animation
    P1_GROUND,
    P1_SKID,
    P1_FLY,
    P1_BIRD_GROUND,
    P1_BIRD_FLY,
    P1_SPAWN,
    P1_SPAWN_PLAT,
    P2_SPAWN,
    P2_SPAWN_PLAT,
    DEATH,
    EGG_FALL,
    EGG_HATCH,
    BOUNDER_GROUND,
    BOUNDER_FLY,
    ENEMY_BIRD_GROUND,
    ENEMY_BIRD_FLY,
    ENEMY_BIRD_SKID,
    ENEMY_SPAWN,
    ENEMY_SPAWN_PLAT,
    HUNTER_GROUND,
    HUNTER_FLY,
    SHADOW_GROUND,
    SHADOW_FLY,
    PLAT_TOP_CENTER_ANIM,
    PLAT_TOP_LEFT_ANIM,
    PLAT_TOP_RIGHT_ANIM,
    PLAT_CENTER_ANIM,
    PLAT_LEFT,
    PLAT_RIGHT,
	PLAT_RIGHT_SMALL,
    PLAT_GROUND,
    DATA_COUNT //this helps make sure array size matches enum count
};


//container for all sprite data. please use the DataNames enum with this.
static const SpriteData spriteData[AnimationNames::DATA_COUNT] =
{
    //all the data follows this pattern:
    //fileName, (startPixelX, startPixelY, spriteWidth, spriteHeight), frameCount
	{"res/Art/spawners.png", sf::IntRect(100, 100, 0, 0), 0},           //NONE          //this loads a blank sprite
    {"res/Art/joustSprite.png", sf::IntRect(248, 64, 13, 18), 4},       //P1_GROUND
    {"res/Art/joustSprite.png", sf::IntRect(248, 82, 13, 18), 1},       //P1_SKID
    {"res/Art/joustSprite.png", sf::IntRect(248, 102, 13, 12), 2},      //P1_FLY
    {"res/Art/joustSprite.png", sf::IntRect(248, 136, 11, 18), 4},      //P1_BIRD_GROUND
    {"res/Art/joustSprite.png", sf::IntRect(248, 156, 12, 12), 2},      //P1_BIRD_FLY
    {"res/Art/spawnAnims.png", sf::IntRect(0, 0, 13, 18), 6},           //P1_SPAWN
    {"res/Art/spawners.png", sf::IntRect(0, 0, 28, 3), 3},              //P1_SPAWN_PLAT
    {"res/Art/spawnAnims.png", sf::IntRect(78, 0, 13, 18), 6},          //P2_SPAWN
    {"res/Art/spawners.png", sf::IntRect(0, 3, 28, 3), 3},              //P2_SPAWN_PLAT
    {"res/Art/joustSprite.png", sf::IntRect(248, 173, 13, 13), 3},      //DEATH
    {"res/Art/joustSprite.png", sf::IntRect(248, 286, 7, 6), 3},        //EGG_FALL
	{"res/Art/joustSprite.png", sf::IntRect(0, 0, 0, 0), 0},            //EGG_HATCH *   //this one is super weird
    {"res/Art/joustSprite.png", sf::IntRect(247, 194, 15, 18), 4},      //BOUNDER_GROUND
    {"res/Art/joustSprite.png", sf::IntRect(247, 214, 15, 12), 2},      //BOUNDER_FLY
    {"res/Art/joustSprite.png", sf::IntRect(247, 228, 14, 13), 4},      //ENEMY_BIRD_GROUND
    {"res/Art/joustSprite.png", sf::IntRect(247, 243, 15, 12), 2},      //ENEMY_BIRD_FLY
    {"res/Art/joustSprite.png", sf::IntRect(247, 257, 15, 12), 1},      //ENEMY_BIRD_SKID
    {"res/Art/spawnAnims.png", sf::IntRect(156, 0, 13, 18), 3},         //ENEMY_SPAWN
    {"res/Art/spawners.png", sf::IntRect(0, 6, 28, 3), 3},              //ENEMY_SPAWN_PLAT
    {"res/Art/enemyAnimations.png", sf::IntRect(0, 0, 13, 18), 4},      //HUNTER_GROUND 
    {"res/Art/enemyAnimations.png", sf::IntRect(0, 18, 13, 12), 2},     //HUNTER_FLY 
    {"res/Art/enemyAnimations.png", sf::IntRect(52, 0, 13, 18), 4},     //SHADOW_GROUND 
    {"res/Art/enemyAnimations.png", sf::IntRect(52, 18, 13, 12), 2},    //SHADOW_FLY 
    {"res/Art/topCenterPlat.png", sf::IntRect(0, 0, 88, 9), 7},         //PLAT_TOP_CENTER_ANIM
    {"res/Art/topSidePlats.png", sf::IntRect(0, 8, 30, 7), 2},          //PLAT_TOP_LEFT_ANIM
    {"res/Art/topSidePlats.png", sf::IntRect(0, 0, 46, 8), 6},          //PLAT_TOP_RIGHT_ANIM
    {"res/Art/centerPlat.png", sf::IntRect(0, 0, 64, 8), 6},            //PLAT_CENTER_ANIM
	{"res/Art/leftSide.png", sf::IntRect(0, 0, 60, 8), 1},              //PLAT_LEFT
    {"res/Art/rightSide.png", sf::IntRect(0, 0, 58, 11), 1},            //PLAT_RIGHT
    {"res/Art/rightSideSmall.png", sf::IntRect(0, 0, 42, 7), 1},        //PLAT_RIGHT_SMALL
    {"res/Art/ground.png", sf::IntRect(0, 0, 186, 33), 1}               //PLAT_GROUND
    //* INDICATES UNFINISHED DO NOT USE
};