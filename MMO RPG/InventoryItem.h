#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "Graphics.h"

class InventoryItem
{
public:
	enum class EquipmentType
	{
		Unknown,
		Gloves,
		Ring,
		Shield,
		Weapon,
		Hat,
		Cape,
		BodyArmor,
		Trousers,
		Boots
	};

public:
	enum class Equipment
	{
		SharpSword = 1,
		LongSword,
		//ManaPotion,
		//HealthPotion,
		//UndefinedPotion,
		LightArmor = 8,
		MediumArmor,
		HeavyArmor,
		WeakCape,
		MediumCape,
		StrongCape,
		//Undefined,
		//WhiteRibbon = 16,
		//PinkRibbon,
		//DarkCyanRibbon,
		//RedRibbon,
		//LightCyanRibbon,
		//YellowRibbon,
		LightRobe = 22,
		MediumRobe,
		MultiPurposeStaff,
		//Card1,
		//Card2,
		//Card3,
		//Card4,
		//Scroll,
		HeavyRobe = 30,
		MagicStaff = 32,
		BasicStaff,
		//Book?,
		//Bottle,
		//Sphere,
		//Mushroom,
		SpeedRing = 38,
		StrengthRing,
		SlashSword = 41,
		StabSword,
		//Backpack,
		//Acorn,
		//??
		//??
		LightBow = 48,
		BasicArmor,
		Spear,
		ThreadedSpear,
		//Cape?,
		//Chest?
		HeavyBow = 56,
		RedDiamond,
		BlueDiamond,
		CyanCiamond
	};

public:
	InventoryItem(const Equipment equipment, const sf::IntRect rectangle);

public:
	void Render(const Graphics& gfx, const sf::FloatRect location);

	EquipmentType GetEquipmentType() const;

	bool IsAt(const sf::Vector2f point) const;

private:
	EquipmentType type;
	Equipment equipment;

	sf::Sprite sprite;
};