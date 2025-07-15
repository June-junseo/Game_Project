#pragma once
#include "GameObject.h"

class Item : public GameObject
{
protected:
    sf::Sprite sprite;
    sf::Texture* texture = nullptr;
    std::string textureId;

public:
    Item(const std::string& name, const std::string& textureId);

    void Init() override;
    void Release() override;
    void Reset() override;

    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetTexture(const std::string& texId);
    const sf::Sprite& GetSprite() const { return sprite; }

    sf::FloatRect GetGlobalBounds() const override;
};
