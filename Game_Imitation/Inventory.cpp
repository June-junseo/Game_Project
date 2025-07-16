#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory()
{
    Init();
}

void Inventory::Init()
{
    slots.clear();
    sf::Vector2f size(150.f, 150.f);
    sf::Vector2f startPos(FRAMEWORK.GetWindowSizeF().x - size.x - 120.f, 160.f);

    for (int i = 0; i < 5; ++i)
    {
        InventorySlot slot(startPos + sf::Vector2f(0, i * (size.y + 10.f)), size);
        slots.push_back(slot);
    }
}

void Inventory::AddItem(Item* item)
{
    for (auto& slot : slots)
    {
        if (slot.IsEmpty())
        {
            slot.SetItem(item);
            return;
        }
    }
    std::cout << "Inventory full\n";
}

void Inventory::Update(const sf::Vector2f& mousePos, bool isClick)
{
    for (auto& slot : slots)
    {
        if (slot.Contains(mousePos))
        {
            if (isClick)
            {
                if (selectedSlot)
                    selectedSlot->SetSelected(false);

                selectedSlot = &slot;
                selectedSlot->SetSelected(true);
            }
        }
    }
}

bool Inventory::HasItem(const std::string& itemName)
{
    for (auto& slot : slots)
    {
        if (!slot.IsEmpty() && slot.GetItem()->GetName() == itemName)
        {
            return true;
        }
    }
    return false;
}

void Inventory::Draw(sf::RenderWindow& window)
{
    for (auto& slot : slots)
        slot.Draw(window);
}

Item* Inventory::GetSelectedItem()
{
    if (selectedSlot)
        return selectedSlot->GetItem();
    return nullptr;
}

void Inventory::RemoveSelectedItem()
{
    if (selectedSlot && !selectedSlot->IsEmpty())
    {
        Item* item = selectedSlot->GetItem();
        selectedSlot->SetItem(nullptr);                    
        selectedSlot->SetSelected(false);
        selectedSlot = nullptr;
    }
}

void Inventory::HandleClick(const sf::Vector2f& mousePos)
{
    Update(mousePos, true);
}
