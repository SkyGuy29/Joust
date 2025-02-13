#pragma once
#include "globals.hpp"


//simple data class for use with the spriteData array.
struct SpriteData
{
    SpriteData(sf::IntRect bounds, int frameCount) { a = bounds; b = frameCount; }
    sf::IntRect a;
    int b;
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
    BOUNDER_BIRD_WALK,
    BOUNDER_BIRD_FLY,
    BOUNDER_BIRD_SKID,
    HUNTER_WALK,
    HUNTER_FLY,
    HUNTER_BIRD_WALK,
    HUNTER_BIRD_FLY,
    HUNTER_BIRD_SKID,
    SHADOW_WALK,
    SHADOW_FLY,
    SHADOW_BIRD_WALK,
    SHADOW_BIRD_FLY,
    SHADOW_BIRD_SKID,
    DATA_COUNT //this helps make sure array size matches enum count
};


//container for all sprite data. please use the DataNames enum with this.
static const SpriteData spriteData[AnimationNames::DATA_COUNT] =
{
    //all data follows this pattern:
    //(startPixelX, startPixelY, spriteWidth, spriteHeight), frameCount
    {sf::IntRect(247, 64, 15, 18), 4},  //P1_GROUND
    {sf::IntRect(248, 84, 13, 16), 1},  //P1_SKID
    {sf::IntRect(247, 102, 15, 12), 2}, //P1_FLY
    {sf::IntRect(248, 136, 13, 18), 4}, //P1_BIRD_GROUND
    {sf::IntRect(247, 156, 15, 12), 2}, //P1_BIRD_FLY
    {sf::IntRect(247, 173, 13, 13), 3}, //DEATH
    {sf::IntRect(248, 286, 7, 6), 3},   //EGG_FALL
    {sf::IntRect(247, 64, 15, 18), 4},  //EGG_HATCH *   //this one is super weird
    {sf::IntRect(247, 194, 15, 18), 4}, //BOUNDER_WALK
    {sf::IntRect(247, 214, 15, 12), 2}, //BOUNDER_FLY
    {sf::IntRect(247, 228, 14, 13), 4}, //BOUNDER_BIRD_WALK
    {sf::IntRect(247, 243, 15, 12), 2}, //BOUNDER_BIRD_FLY
    {sf::IntRect(247, 257, 15, 12), 1}, //BOUNDER_BIRD_SKID
    {sf::IntRect(247, 64, 15, 18), 4},  //HUNTER_WALK *
    {sf::IntRect(247, 64, 15, 18), 4},  //HUNTER_FLY *
    {sf::IntRect(247, 64, 15, 18), 4},  //HUNTER_BIRD_WALK *
    {sf::IntRect(247, 64, 15, 18), 4},  //HUNTER_BIRD_FLY *
    {sf::IntRect(247, 64, 15, 18), 4},  //HUNTER_BIRD_SKID *
    {sf::IntRect(247, 64, 15, 18), 4},  //SHADOW_WALK *
    {sf::IntRect(247, 64, 15, 18), 4},  //SHADOW_FLY *
    {sf::IntRect(247, 64, 15, 18), 4},  //SHADOW_BIRD_WALK *
    {sf::IntRect(247, 64, 15, 18), 4},  //SHADOW_BIRD_FLY *
    {sf::IntRect(247, 64, 15, 18), 4},  //SHADOW_BIRD_SKID *
    //* INDICATES UNFINISHED DO NOT USE
};