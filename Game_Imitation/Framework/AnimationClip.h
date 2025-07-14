#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	//PingPong,
};

struct AnimationFrame
{
	std::string texId; //스트라이트의 아이디
	sf::IntRect texCoord; //이 스프라이트의 어디를(어느부분을) 프레임으로 쓸지 

	AnimationFrame() {}
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord) : texId(texId), texCoord(texCoord) {}
};

struct AnimationClip 
{
	std::string id; //애니메이션 클립 마다의 아이디 
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop; //애니메이션 종류에 따라 달라지는 type (idle, run은 루프로, jump는 한번만 재생해도 상관없음)
	int fps = 30; //(프레임 속도)

	std::vector<AnimationFrame> frames; //애니메이션 프레임의 백터 한 프레임에 대한 정보 

	bool loadFromFile(const std::string& filePath);
};


