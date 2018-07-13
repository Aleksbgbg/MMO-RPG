#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <json.hpp>

#include <unordered_map>

#include "Graphics.h"
#include "InventoryItem.h"
#include "HudWindow.h"

class Inventory : public HudWindow
{
public:
	Inventory();

public:
	void Draw(const Graphics& gfx);

	void MouseClicked(const sf::Vector2f position);

private:
	void Equip(const int itemIndex);
	void Dequip(const InventoryItem::EquipmentType type);

	int CreateAndStore(const InventoryItem::Equipment type);

private:
	sf::Sprite background;

	nlohmann::json itemsInfo;

	std::unordered_map<InventoryItem::EquipmentType, std::unique_ptr<InventoryItem>> equippedItems;

	std::vector<std::unique_ptr<InventoryItem>> storedItems;
};