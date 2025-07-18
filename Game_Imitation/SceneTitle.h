#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{ 
public:
	SceneTitle();
	virtual ~SceneTitle() = default;

    void Init() override;
    void Enter() override;
    void Exit() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

private:
    void ResourceLoad();
    void SetUpViews();

    sf::Text titleText;
    sf::Font font;

    std::string texIdTitle = "graphics/title_bg.png";
    sf::Sprite titleBg;

};

