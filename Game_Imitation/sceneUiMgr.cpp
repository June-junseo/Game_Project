#include "stdafx.h"
#include "SceneUiMgr.h"


void SceneUiMgr::Init(sf::RenderWindow& window, sf::Vector2f windowSize)
{
    uiView.setSize(windowSize);
    uiView.setCenter(windowSize * 0.5f);
    window.setView(uiView);
}

void SceneUiMgr::CreateArrowButtons(sf::Vector2f windowSize, sf::Vector2f size)
{
    if (leftArrow) delete leftArrow;
    if (rightArrow) delete rightArrow;

    leftArrow = new ArrowButton(ArrowDirection::Left, { 150, windowSize.y / 2 - 20 }, size);
    rightArrow = new ArrowButton(ArrowDirection::Right, { windowSize.x - 370, windowSize.y / 2 - 20 }, size);
}

void SceneUiMgr::AddArrowButtons(ArrowButton* left, ArrowButton* right)
{
    leftArrow = left;
    rightArrow = right;
}

void SceneUiMgr::ClearArrows()
{
    leftArrow = nullptr;
    rightArrow = nullptr;
}

void SceneUiMgr::Update(float dt)
{
    InputMgr::Update(dt);
    if (leftArrow) leftArrow->Update(dt);
    if (rightArrow) rightArrow->Update(dt);

    // Inventory things maybe....
}

void SceneUiMgr::HandleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    InputMgr::UpdateEvent(event);
    window.setView(uiView);

    if (leftArrow) leftArrow->HandleEvent(event, window);
    if (rightArrow) rightArrow->HandleEvent(event, window);
}

void SceneUiMgr::Draw(sf::RenderWindow& window)
{
    window.setView(uiView);

    if (leftArrow) leftArrow->Draw(window);
    if (rightArrow) rightArrow->Draw(window);

    Inventory::Instance().Draw(window);
}
