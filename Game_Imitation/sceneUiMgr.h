#pragma once
#include "stdafx.h"
#include "ArrowButton.h"
#include "Inventory.h"

class SceneUiMgr
{
public:
    void Init(sf::RenderWindow& window, sf::Vector2f windowSize);

    void CreateArrowButtons(sf::Vector2f windowSize, sf::Vector2f size = { 25.f, 30.f });

    ArrowButton* GetLeftArrow() const { return leftArrow; }
    ArrowButton* GetRightArrow() const { return rightArrow; }

    void Update(float dt);
    void HandleEvent(const sf::Event& event, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);

    void AddArrowButtons(ArrowButton* left, ArrowButton* right);
    void ClearArrows();

private:
    ArrowButton* leftArrow = nullptr;
    ArrowButton* rightArrow = nullptr;

    sf::View uiView;
};
