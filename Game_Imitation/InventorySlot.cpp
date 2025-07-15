#include "stdafx.h"
#include "InventorySlot.h"

InventorySlot::InventorySlot(const sf::Vector2f& position, const sf::Vector2f& size)
{
    slotShape.setSize(size);
    slotShape.setPosition(position);
    slotShape.setFillColor(sf::Color(255, 195, 90));
    slotShape.setOutlineColor(sf::Color::Black);
    slotShape.setOutlineThickness(5.f);
}

void InventorySlot::Draw(sf::RenderWindow& window)
{
    if (selected)
        slotShape.setOutlineColor(sf::Color::White); //can change the color later
    else
        slotShape.setOutlineColor(sf::Color::Black);

    window.draw(slotShape);

    if (item)
    {
        item->SetPosition(slotShape.getPosition() + sf::Vector2f(10.f, 50.f));
        item->Draw(window);
    }
}

bool InventorySlot::Contains(const sf::Vector2f& point) const
{
    return slotShape.getGlobalBounds().contains(point);
}

void InventorySlot::SetItem(Item* newItem)
{
    item = newItem;
}

Item* InventorySlot::GetItem() const
{
    return item;
}

bool InventorySlot::IsEmpty() const
{
    return item == nullptr;
}

void InventorySlot::SetSelected(bool s)
{
    selected = s;
}

bool InventorySlot::IsSelected() const
{
    return selected;
}