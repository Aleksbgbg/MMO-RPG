#include "Portal.h"

Portal::Portal(const sf::FloatRect occupation, const int targetWorldIndex, const int targetPortalIndex)
	:
	occupation{ occupation },
	targetWorldIndex{ targetWorldIndex },
	targetPortalIndex{ targetPortalIndex }
{
}