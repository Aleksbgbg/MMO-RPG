#include "InventoryItem.h"

#include <stdexcept>

#include "ResourceManager.h"
#include "Rect.h"

InventoryItem::InventoryItem(const Equipment equipment, const sf::IntRect rectangle)
	:
	equipment{ equipment },
	sprite{ TextureManager::Get("Inventory\\Items"), rectangle }
{
	sprite.setOrigin(center(sprite.getLocalBounds()));

	switch (equipment)
	{
	case Equipment::HeavyBow: 
	case Equipment::SharpSword: 
	case Equipment::LongSword: 
	case Equipment::Spear: 
	case Equipment::ThreadedSpear: 
	case Equipment::SlashSword: 
	case Equipment::StabSword: 
	case Equipment::LightBow: 
	case Equipment::MultiPurposeStaff: 
	case Equipment::MagicStaff: 
	case Equipment::BasicStaff:
		type = EquipmentType::Weapon;
		break;
		
	case Equipment::BasicArmor: 
	case Equipment::LightArmor: 
	case Equipment::MediumArmor: 
	case Equipment::HeavyArmor: 
	case Equipment::LightRobe: 
	case Equipment::MediumRobe: 
	case Equipment::HeavyRobe:
		type = EquipmentType::BodyArmor;
		break; 

	case Equipment::WeakCape: 
	case Equipment::MediumCape: 
	case Equipment::StrongCape: 
		type = EquipmentType::Cape;
		break;

	case Equipment::SpeedRing: 
	case Equipment::StrengthRing: 
	case Equipment::RedDiamond: 
	case Equipment::BlueDiamond: 
	case Equipment::CyanCiamond:
		type = EquipmentType::Ring;
		break;

	default:
		throw std::runtime_error{ "Invalid equipment type." };
	}
}

void InventoryItem::Render(const Graphics& gfx, const sf::FloatRect location)
{
	sprite.setPosition(center(location));

	gfx.Draw(sprite);
}

InventoryItem::EquipmentType InventoryItem::GetEquipmentType() const
{
	return type;
}