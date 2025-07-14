#pragma once
class ZoomUI
{
private:
    sf::Sprite sprite;
    sf::FloatRect clickableArea;
    bool isVisible = false;  
    bool isOpened = false;

public:
    void Init(const sf::Texture& texture, const sf::Vector2f& windowCenter);
    void SetClickableArea(const sf::FloatRect& rect);

    bool CheckClick(const sf::Vector2f& point);

    void Show() { isVisible = true; }
    void Hide() { isVisible = false; }
    bool IsVisible() const { return isVisible; }

    void Draw(sf::RenderWindow& window, const sf::RectangleShape* extraOverlay = nullptr);
    void ChangeTexture(const sf::Texture& newTexture);
    void SetOpened(bool open) { isOpened = open; }
    bool IsOpened() const { return isOpened; }
};