#include "Spawner.h"


void Spawner::setPlatform(PlatformNames plat)
{
	sf::Vector2f pos;

	switch (plat)
	{
	case PlatformNames::P_TOP_MIDDLE:
		pos = sf::Vector2f(100, 74);
		break;
	case PlatformNames::P_LEFT_SIDE:
		pos = sf::Vector2f(10, 131);
		break;
	case PlatformNames::P_RIGHT_SIDE:
		pos = sf::Vector2f(218, 122);
		break;
	case PlatformNames::P_GROUND:
		pos = sf::Vector2f(114, 204);
		break;
	default:
		return;
	}

	pos.x += spriteData[AnimationNames::P1_SPAWN_PLAT].bounds.width / 2.f; //centers the spawner on the platform
	pos.x *= WINDOW_SCALE;

	pos.y += spriteData[AnimationNames::P1_SPAWN_PLAT].bounds.height / 2.f;
	pos.y *= WINDOW_SCALE;

	sprite.setPos(pos);
}


void Spawner::setSpawnAnim(AnimationNames anim)
{
	switch (anim)
	{
	case AnimationNames::P1_SPAWN_PLAT:
	case AnimationNames::P2_SPAWN_PLAT:
	case AnimationNames::ENEMY_SPAWN_PLAT:
		std::cout << "augh\n";
		std::cout << sprite.getBounds().top << " " << sprite.getBounds().left << "\n";
		sprite.setAnimation(anim);
		break;
	default:
		return;
	}

	sprite.setMode(Mode::LOOP);
}