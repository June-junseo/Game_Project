#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	//PingPong,
};

struct AnimationFrame
{
	std::string texId; //��Ʈ����Ʈ�� ���̵�
	sf::IntRect texCoord; //�� ��������Ʈ�� ���(����κ���) ���������� ���� 

	AnimationFrame() {}
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord) : texId(texId), texCoord(texCoord) {}
};

struct AnimationClip 
{
	std::string id; //�ִϸ��̼� Ŭ�� ������ ���̵� 
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop; //�ִϸ��̼� ������ ���� �޶����� type (idle, run�� ������, jump�� �ѹ��� ����ص� �������)
	int fps = 30; //(������ �ӵ�)

	std::vector<AnimationFrame> frames; //�ִϸ��̼� �������� ���� �� �����ӿ� ���� ���� 

	bool loadFromFile(const std::string& filePath);
};


