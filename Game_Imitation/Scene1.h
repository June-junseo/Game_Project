#pragma once
#include "Scene.h"
#include "ZoomUI.h"
#include "NumPad.h"

class ArrowButton;
class Scene1 :
    public Scene
{
protected:

	ArrowButton* leftArrow = nullptr;
	ArrowButton* rightArrow = nullptr;

	sf::Sprite background1;
	std::string texId = "graphics/scene1_bg.png";

	sf::Sprite light;
	std::string texId1 = "graphics/scene1_light.png";

	ZoomUI shelfUi;
	ZoomUI albumUi;
	ZoomUI boxUi;
	ZoomUI boxOpenUi;

	NumPad numPad;

	sf::RectangleShape shadowBg;
	sf::RectangleShape shelfRect;
	sf::RectangleShape boxRect;
	sf::RectangleShape albumRect;

	float blinkTimer = 0.f;
	float blinkInterval = 0.1f; 

public:
	Scene1();

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void ResourceLoad();
	void SetUpViews();
	void Draw(sf::RenderWindow& window) override;
	virtual void HandleEvent(const sf::Event& event) override;
};

