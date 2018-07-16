#include "Inventory.h"

#include <SFML/Graphics/Shader.hpp>

#include "ResourceManager.h"
#include "Json.h"
#include "Rect.h"

using nlohmann::json;

Inventory::Inventory(Player& player)
	:
	HudWindow{ sf::Keyboard::Key::I },
	background{ TextureManager::Get("Inventory\\Items Inventory") },
	player{ player }
{
	itemsInfo = read_json("Config\\Items.json");

	const sf::Vector2f equipSlotDimensions{ itemsInfo["equipSlotWidth"], itemsInfo["equipSlotHeight"] };

	const json& specialSlotPositions = itemsInfo["positions"];

	for (int index = 0; index < static_cast<int>(specialSlotPositions.size()); ++index)
	{
		const json& slotPositionJson = specialSlotPositions[index];

		const sf::Vector2f slotPosition{ slotPositionJson["x"], slotPositionJson["y"] };

		equipSlots.emplace(static_cast<InventoryItem::EquipmentType>(index), InventorySlotWithPlaceholder{ sf::FloatRect{ slotPosition, equipSlotDimensions }, ComputeTextureRectangle(slotPositionJson["placeholder"]) });
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
	const sf::Vector2f worldPosition = gfx.MapPixelToCoords(sf::Vector2i{ 0, 0 });

	background.setPosition(worldPosition);
	gfx.Draw(background);

	for (auto& pair : equipSlots)
	{
		pair.second.UpdateWorldPosition(worldPosition);
		pair.second.Draw(gfx);
	}

	for (InventorySlot& slot : inventorySlots)
	{
		slot.UpdateWorldPosition(worldPosition);
		slot.Draw(gfx);
	}

	// Pre-calculated values for the background dimensions of the central scroll
	player.DrawAt(gfx, center(sf::FloatRect{ 125.0f, 32.0f, 316.0f, 443.0f }) + worldPosition);
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

	item.value().Render(gfx, GetWorldDimensions());
}

bool Inventory::InventorySlot::IsAt(const sf::Vector2f point) const
{
	return GetWorldDimensions().contains(point);
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

sf::Vector2f Inventory::InventorySlot::GetWorldPosition() const
{
	return worldPosition;
}

sf::FloatRect Inventory::InventorySlot::GetWorldDimensions() const
{
	sf::FloatRect dimensions = this->dimensions;

	dimensions.left += worldPosition.x;
	dimensions.top += worldPosition.y;

	return dimensions;
}

Inventory::InventorySlotWithPlaceholder::InventorySlotWithPlaceholder(const sf::FloatRect dimensions, const sf::IntRect viewport)
	:
	InventorySlot{ dimensions },
	placeholderSprite{ TextureManager::Get("Inventory\\Items"), viewport }
{
	Setup();
}

Inventory::InventorySlotWithPlaceholder::InventorySlotWithPlaceholder(const InventoryItem& item, const sf::FloatRect dimensions, const sf::IntRect viewport)
	:
	InventorySlot{ item, dimensions },
	placeholderSprite{ TextureManager::Get("Inventory\\Items"), viewport }
{
	Setup();
}

void Inventory::InventorySlotWithPlaceholder::Draw(const Graphics& gfx)
{
	if (HasItem())
	{
		InventorySlot::Draw(gfx);
		return;
	}

	placeholderSprite.setPosition(center(GetWorldDimensions()));

	gfx.Draw(placeholderSprite, *grayscale);
}

void Inventory::InventorySlotWithPlaceholder::Setup()
{
	placeholderSprite.setOrigin(center(placeholderSprite.getLocalBounds()));

	grayscale = ShaderManager::Get("Transparent Grayscale", sf::Shader::Type::Fragment);
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
	const int emptySlotIndex = FindEmptySlotIndex();

	inventorySlots[emptySlotIndex].Equip(InventoryItem{ type, ComputeTextureRectangle(static_cast<int>(type)) });

	return emptySlotIndex;
}

Inventory::InventorySlot& Inventory::FindEmptySlot()
{
	return inventorySlots[FindEmptySlotIndex()];
}

int Inventory::FindEmptySlotIndex() const
{
	for (int index = 0; index < static_cast<int>(inventorySlots.size()); ++index)
	{
		if (!inventorySlots[index].HasItem())
		{
			return index;
		}
	}

	throw std::runtime_error{ "No empty slot." };
}

sf::IntRect Inventory::ComputeTextureRectangle(const int equipmentPosition) const
{
	const int itemsPerRow = itemsInfo["itemsPerRow"];

	const int row = equipmentPosition / itemsPerRow;

	const int column = equipmentPosition % itemsPerRow;

	const int itemWidth = itemsInfo["itemWidth"];
	const int itemHeight = itemsInfo["itemHeight"];

	return sf::IntRect{ column * itemWidth, row * itemHeight, itemWidth, itemHeight };
}