#pragma once
#include "Singleton.h"
#include "InventorySlot.h"

class Inventory : public Singleton<Inventory>
{
    friend class Singleton<Inventory>;

private:
    std::vector<InventorySlot> slots;
    InventorySlot* selectedSlot = nullptr;

    Inventory();

public:
    void Init();
    void AddItem(Item* item);
    void Update(const sf::Vector2f& mousePos, bool isClick);
    void Draw(sf::RenderWindow& window);
    Item* GetSelectedItem();
    bool HasItem(const std::string& itemName);
    void HandleClick(const sf::Vector2f& mousePos);
};
