#pragma once
#include "stdafx.h"
#include "Item.h"
class InventorySlot
{
private:
    sf::RectangleShape slotShape;
    Item* item = nullptr;
    bool selected = false;

public:
    InventorySlot(const sf::Vector2f& position, const sf::Vector2f& size);

    void Draw(sf::RenderWindow& window);
    bool Contains(const sf::Vector2f& point) const;
    void SetItem(Item* newItem);
    Item* GetItem() const;
    bool IsEmpty() const;
    void SetSelected(bool s);
    bool IsSelected() const;
};