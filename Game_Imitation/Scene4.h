#pragma once
#include "stdafx.h"
#include "ZoomUI.h"
#include "SceneUiMgr.h"
#include "Inventory.h"

class Scene4 :
    public Scene
{
public: 
    Scene4();
    virtual ~Scene4() = default;

    void Init() override;
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;

private:
    void ResourceLoad();
    void SetUpViews();

    std::string texId4 = "graphics/scene4_bg.png";
    sf::Sprite background4;

    SceneUiMgr sceneUiMgr;
};

