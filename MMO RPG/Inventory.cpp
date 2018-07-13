#include "Inventory.h"

#include "ResourceManager.h"
#include "Json.h"

using nlohmann::json;

Inventory::Inventory()
	:
	HudWindow{ sf::Keyboard::Key::I },
	background{ TextureManager::Get("Inventory\\Items Inventory") }
{
	itemsInfo = read_json("Config\\Items.json");

	const sf::Vector2f equipSlotDimensions{ itemsInfo["equipSlotWidth"], itemsInfo["equipSlotHeight"] };

	const json& specialSlotPositions = itemsInfo["positions"];

	for (int index = 0; index < specialSlotPositions.size(); ++index)
	{
		const json& slotPositionJson = specialSlotPositions[index];

		const sf::Vector2f slotPosition{ slotPositionJson["x"], slotPositionJson["y"] };

		equipSlots.emplace(static_cast<InventoryItem::EquipmentType>(index), InventorySlot{ sf::FloatRect{ slotPosition, equipSlotDimensions } });
	}

	const int itemsPerRow = itemsInfo["itemsPerRow"];
	const int rows = itemsInfo["rows"];

	const sf::Vector2f regularSlotDimensions{ itemsInfo["regularSlotWidth"], itemsInfo["regularSlotHeight"] };

	const sf::Vector2i equipAreaOffset{ itemsInfo["equipAreaHorizontalStart"], itemsInfo["equipAreaVerticalStart"] };

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < itemsPerRow; ++x)
		{
			inventorySlots.emplace_back(sf::FloatRect{ sf::Vector2f{ static_cast<float>(equipAreaOffset.x + x * regularSlotDimensions.x), static_cast<float>(equipAreaOffset.y + y * regularSlotDimensions.y) }, regularSlotDimensions });
		}
	}

	for (const InventoryItem::Equipment equipment : std::array<InventoryItem::Equipment, 3>
	{
		InventoryItem::Equipment::MagicStaff,
		InventoryItem::Equipment::StrongCape,
		InventoryItem::Equipment::HeavyArmor
	})
	{
		Equip(CreateAndStore(equipment));
	}
}

void Inventory::OnDraw(const Graphics& gfx)
{
	background.setPosition(gfx.MapPixelToCoords(sf::Vector2i{ 0, 0 }));
	gfx.Draw(background);

	for (auto& pair : equipSlots)
	{
		pair.second.Draw(gfx);
	}

	for (InventorySlot& slot : inventorySlots)
	{
		slot.Draw(gfx);
	}
}

void Inventory::OnMouseClicked(const sf::Vector2f position)
{
	for (auto& pair : equipSlots)
	{
		if (pair.second.IsAt(position) && pair.second.HasItem())
		{
			InventorySlot::Swap(pair.second, FindEmptySlot());
			return;
		}
	}

	for (InventorySlot& slot : inventorySlots)
	{
		if (slot.IsAt(position) && slot.HasItem())
		{
			InventorySlot::Swap(slot, equipSlots[slot.GetEquipmentType()]);
			return;
		}
	}
}

Inventory::InventorySlot::InventorySlot(const sf::FloatRect dimensions)
	:
	dimensions{ dimensions }
{
}

Inventory::InventorySlot::InventorySlot(InventoryItem item, const sf::FloatRect dimensions)
	:
	item{ item },
	dimensions{ dimensions }
{
}

void Inventory::InventorySlot::Equip(const InventoryItem& item)
{
	this->item = item;
}

std::optional<InventoryItem> Inventory::InventorySlot::Dequip()
{
	std::optional<InventoryItem> item = this->item;

	this->item = std::optional<InventoryItem>{ };

	return item;
}

void Inventory::InventorySlot::UpdateWorldPosition(const sf::Vector2f worldPosition)
{
	this->worldPosition = worldPosition;
}

void Inventory::InventorySlot::Draw(const Graphics& gfx)
{
	if (!HasItem()) return;

	sf::FloatRect dimensions = this->dimensions;

	dimensions.left += worldPosition.x;
	dimensions.top += worldPosition.y;

	item.value().Render(gfx, dimensions);
}

bool Inventory::InventorySlot::IsAt(const sf::Vector2f point) const
{
	return dimensions.contains(point);
}

void Inventory::InventorySlot::Swap(InventorySlot& first, InventorySlot& second)
{
	std::optional<InventoryItem> firstItem = first.Dequip();
	std::optional<InventoryItem> secondItem = second.Dequip();

	if (firstItem.has_value())
	{
		second.Equip(firstItem.value());
	}

	if (secondItem.has_value())
	{
		first.Equip(secondItem.value());
	}
}

bool Inventory::InventorySlot::HasItem() const
{
	return item.has_value();
}

InventoryItem::EquipmentType Inventory::InventorySlot::GetEquipmentType() const
{
	return item.value().GetEquipmentType();
}

void Inventory::Equip(const int itemIndex)
{
	InventoryItem item = inventorySlots[itemIndex].Dequip().value();

	equipSlots[item.GetEquipmentType()].Equip(item);
}

void Inventory::Dequip(const InventoryItem::EquipmentType type)
{
	InventorySlot::Swap(equipSlots[type], FindEmptySlot());
}

int Inventory::CreateAndStore(const InventoryItem::Equipment type)
{
	const int position = static_cast<int>(type);

	const int itemsPerRow = itemsInfo["itemsPerRow"];

	const int row = position / itemsPerRow;

	const int column = position % itemsPerRow;

	const int itemWidth = itemsInfo["itemWidth"];
	const int itemHeight = itemsInfo["itemHeight"];

	const int emptySlotIndex = FindEmptySlotIndex();

	inventorySlots[emptySlotIndex].Equip(InventoryItem{ type, sf::IntRect{ column * itemWidth, row * itemHeight, itemWidth, itemHeight } });

	return emptySlotIndex;
}

Inventory::InventorySlot& Inventory::FindEmptySlot()
{
	return inventorySlots[FindEmptySlotIndex()];
}

int Inventory::FindEmptySlotIndex() const
{
	for (int index = 0; index < inventorySlots.size(); ++index)
	{
		if (!inventorySlots[index].HasItem())
		{
			return index;
		}
	}

	throw std::runtime_error{ "No empty slot." };
}