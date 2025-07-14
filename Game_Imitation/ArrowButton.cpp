#include "stdafx.h"
#include "ArrowButton.h"

ArrowButton::ArrowButton(ArrowDirection direction, sf::Vector2f position, sf::Vector2f size)
{
	shape.setPointCount(3);

    if (direction == ArrowDirection::Left) {
        shape.setPoint(0, { size.x, 0 });
        shape.setPoint(1, { 0, size.y / 2 });
        shape.setPoint(2, { size.x, size.y });
    }
    else {
        shape.setPoint(0, { 0, 0 });
        shape.setPoint(1, { size.x, size.y / 2 });
        shape.setPoint(2, { 0, size.y });
    }

    shape.setFillColor(sf::Color::Black);
    shape.setPosition(position);
}

void ArrowButton::Update()
{
    sf::Vector2f mousePos = (sf::Vector2f)InputMgr::GetMousePosition();

    if (shape.getGlobalBounds().contains(mousePos))
    {
        if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
        {
            if (onClick) onClick();
        }
    }
}

void ArrowButton::SetCallBack(std::function<void()> callback)
{
    onClick = callback;
}

void ArrowButton::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    sf::Vector2f mousePos = (sf::Vector2f)InputMgr::GetMousePosition();

    if (shape.getGlobalBounds().contains(mousePos))
    {
        if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
        {
            if (onClick) onClick();
        }
    }
}

void ArrowButton::UpdateHoverState(const sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool hovered = shape.getGlobalBounds().contains(mousePos);

    if (hovered != isHovered) {
        isHovered = hovered;
        shape.setFillColor(isHovered ? hoverColor : defaultColor);
    }
}

void ArrowButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}
