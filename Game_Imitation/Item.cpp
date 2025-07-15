#include "stdafx.h"
#include "Item.h"

Item::Item(const std::string& name, const std::string& textureId)
    : GameObject(name), textureId(textureId)
{
}

void Item::Init()
{
    texture = &TEXTURE_MGR.Get(textureId);
    sprite.setTexture(*texture);

    sf::Vector2f slotSize(140.f, 140.f);

    sf::Vector2f textureSize(
        static_cast<float>(texture->getSize().x),
        static_cast<float>(texture->getSize().y));

    float scaleX = slotSize.x / textureSize.x;
    float scaleY = slotSize.y / textureSize.y;

    float scaleFactor = std::min(scaleX, scaleY);

    SetScale({ scaleFactor, scaleFactor });

    SetOrigin(originPreset); 
}

void Item::Release() {}

void Item::Reset() {}

void Item::Update(float dt) {}

void Item::Draw(sf::RenderWindow& window)
{
    if (!active) return;

    sprite.setPosition(position);
    sprite.setRotation(rotation);
    sprite.setScale(scale);
    sprite.setOrigin(origin);
    window.draw(sprite);
}

void Item::SetPosition(const sf::Vector2f& pos)
{
    position = pos;
    sprite.setPosition(pos);
}

void Item::SetScale(const sf::Vector2f& s)
{
    scale = s;
    sprite.setScale(s);
}

void Item::SetTexture(const std::string& texId)
{
    textureId = texId;
    texture = &TEXTURE_MGR.Get(texId);
    sprite.setTexture(*texture);
}

sf::FloatRect Item::GetGlobalBounds() const
{
    return sprite.getGlobalBounds();
}
