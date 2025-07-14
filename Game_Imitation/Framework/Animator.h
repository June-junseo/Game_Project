#pragma once
#include "AnimationClip.h"

struct AnimationEvent
{
	std::string id;
	int frame = 0;

	std::vector<std::function<void()>> actions;

	bool operator==(const AnimationEvent& other) const
	{
		return (id == other.id) && (frame == other.frame);
	}
};

struct AnimationEventHash
{
	std::size_t operator()(const std::pair<std::string, int>& pair) const
	{
		std::size_t h1 = std::hash<std::string>()(pair.first);
		std::size_t h2 = std::hash<int>()(pair.second);
		return h1 ^ (h2 << 1);
		//해쉬 함수? 
	}
};

class Animator
{
protected:
	static const std::string emptyString;
	std::unordered_map<std::pair<std::string, int>, AnimationEvent, AnimationEventHash> events;
	//해쉬함수? 기본 데이터형은 해쉬 함수가 이미 구현되어있음 //내가 만든 데이터 형으로 사용할때 세번쨰 인자에 펀터 넘겨줌
	std::queue<std::string> playQueue; //std::queue 컨테이너 (a가 재생이 끝나면 b재생 끝나면 c재생 할때 재생 안되는 것들 queue )

	AnimationClip* currentClip; //현재 재생중인 애니메이션 클립 
	sf::Sprite* sprite;

	bool isPlaying = false;
	//프레임을 바꿔주는데 필요한 멤버 변수 
	int currentFrame = 0; 
	int totalFrame = 0;
	int checkFrame = 0;

	float frameDuration = 0.f;
	float accumTime = 0.f;
	float speed = 1.f;

public:
	Animator() = default;
	~Animator() = default;

	//애니메이션 적용된 스프라이드를 받는 
	void SetTarget(sf::Sprite* target) { sprite = target; }

	void AddEvent(const std::string& id, int frame, std::function<void()> action);
	void ClearEvent() { events.clear(); }

	//void AddEvent(const AnimationEvent& ev)
	//{ 
	//	if (events.find(ev) != events.end())
	//	{
	//		// Error
	//		return;
	//	}
	//	events.insert(ev);
	//}

	void Update(float dt);

	bool IsPlaying() const { return isPlaying; }
	//애니메이션 속도 조절 
	void SetSpeed(float speed) 
	{ 
		this->speed = speed;
		checkFrame = this->speed > 0.f ? totalFrame : -1;
	}

	//애니메이션 클립의 아이디
	void Play(const std::string& clipId, bool clearQueue = true);
	//애니메이션 포인터 받는//재생하고 있는 클립의 프레임을 바꿔주는 
	void Play(AnimationClip* clip, bool clearQueue = true);

	//현재 제셍하고 나서 플레이
	void PlayQueue(const std::string& clipId);

	void Stop();

	//void Pause(bool pause);

	void SetFrame(const AnimationFrame& frame);

	//현재 재생하고 잇는 애니메이션 가져옴 
	const std::string& GetCurrentClipId() const 
	{
		if (currentClip == nullptr)
			return emptyString;
		return currentClip->id;
	}
};

