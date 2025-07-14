#pragma once

enum class ArrowDirection
{
	Left,
	Right
};

class ArrowButton : public sf::Drawable
{
public: 
	ArrowButton(ArrowDirection direction, sf::Vector2f position, sf::Vector2f size);

	void Update();
	void SetCallBack(std::function<void()> callback);
	void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
	void UpdateHoverState(const sf::RenderWindow& window);

protected:
	sf::ConvexShape shape;
	std::function<void()> onClick;

	sf::Color defaultColor = sf::Color::Black;
	sf::Color hoverColor = sf::Color(100, 100, 100); // È¸»öºû ¹àÀº»ö
	bool isHovered = false;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};

