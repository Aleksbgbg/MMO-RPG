#include "Reticle.h"

#include "ResourceManager.h"
#include "Character.h"
#include "Rect.h"

Reticle::Reticle()
	:
	sprite{ TextureManager::Get("Reticle") }
{
	sprite.setOrigin(center(sprite.getLocalBounds()));
}

void Reticle::Update(const Character& target)
{
	const float scaleFactor = target.GetOccupation().width / sprite.getLocalBounds().width;

	sprite.setScale(scaleFactor, scaleFactor);
	sprite.setPosition(target.GetPosition());
	sprite.setRotation(sprite.getRotation() + 1.0f);
}

void Reticle::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}