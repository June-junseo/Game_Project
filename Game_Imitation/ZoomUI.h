#pragma once
#include "stdafx.h"

class ZoomUI : public GameObject
{
public:
    ZoomUI(const std::string& name = "ZoomUI");
    virtual ~ZoomUI() = default;

    void Init(const sf::Texture& texture, const sf::Vector2f& windowCenter);
    void SetClickableArea(const sf::FloatRect& rect);
    bool CheckClick(const sf::Vector2f& point);

    void ChangeTexture(const sf::Texture& newTexture);

    void Show() { SetActive(true); }
    void Hide() { SetActive(false); }
    bool IsVisible() const { return GetActive(); }

    void SetOpened(bool opened) { isOpened = opened; }
    bool IsOpened() const { return isOpened; }

    virtual void Init() override {}
    virtual void Release() override {}
    virtual void Reset() override {}

    virtual void Update(float dt) override {}
    virtual void Draw(sf::RenderWindow& window) override;
    void Draw(sf::RenderWindow& window, const sf::RectangleShape* extraOverlay);
    virtual void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override {}

    virtual sf::FloatRect GetGlobalBounds() const override { return sprite.getGlobalBounds(); }

private:
    sf::Sprite sprite;
    sf::FloatRect clickableArea;
    bool isOpened = false;
};
