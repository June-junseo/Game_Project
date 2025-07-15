#pragma once
#include "stdafx.h"
#include <functional>

class ArrowButton : public GameObject, public sf::Drawable {
private:

    sf::ConvexShape shape;
    std::function<void()> onClick;

    ArrowDirection direction;

    sf::Color defaultColor = sf::Color::Black;
    sf::Color hoverColor = sf::Color::White;
    bool isHovered = false;

public:
    ArrowButton(ArrowDirection direction, const sf::Vector2f& position, const sf::Vector2f& size);

    void SetCallBack(std::function<void()> callback);
    void Update(float dt) override;
    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window) override;

    void UpdateHoverState(const sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window) override;

    void Init() override {}
    void Release() override {}
    void Reset() override {}

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
