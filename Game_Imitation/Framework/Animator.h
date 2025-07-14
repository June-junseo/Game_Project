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
		//�ؽ� �Լ�? 
	}
};

class Animator
{
protected:
	static const std::string emptyString;
	std::unordered_map<std::pair<std::string, int>, AnimationEvent, AnimationEventHash> events;
	//�ؽ��Լ�? �⺻ ���������� �ؽ� �Լ��� �̹� �����Ǿ����� //���� ���� ������ ������ ����Ҷ� ������ ���ڿ� ���� �Ѱ���
	std::queue<std::string> playQueue; //std::queue �����̳� (a�� ����� ������ b��� ������ c��� �Ҷ� ��� �ȵǴ� �͵� queue )

	AnimationClip* currentClip; //���� ������� �ִϸ��̼� Ŭ�� 
	sf::Sprite* sprite;

	bool isPlaying = false;
	//�������� �ٲ��ִµ� �ʿ��� ��� ���� 
	int currentFrame = 0; 
	int totalFrame = 0;
	int checkFrame = 0;

	float frameDuration = 0.f;
	float accumTime = 0.f;
	float speed = 1.f;

public:
	Animator() = default;
	~Animator() = default;

	//�ִϸ��̼� ����� �������̵带 �޴� 
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
	//�ִϸ��̼� �ӵ� ���� 
	void SetSpeed(float speed) 
	{ 
		this->speed = speed;
		checkFrame = this->speed > 0.f ? totalFrame : -1;
	}

	//�ִϸ��̼� Ŭ���� ���̵�
	void Play(const std::string& clipId, bool clearQueue = true);
	//�ִϸ��̼� ������ �޴�//����ϰ� �ִ� Ŭ���� �������� �ٲ��ִ� 
	void Play(AnimationClip* clip, bool clearQueue = true);

	//���� �����ϰ� ���� �÷���
	void PlayQueue(const std::string& clipId);

	void Stop();

	//void Pause(bool pause);

	void SetFrame(const AnimationFrame& frame);

	//���� ����ϰ� �մ� �ִϸ��̼� ������ 
	const std::string& GetCurrentClipId() const 
	{
		if (currentClip == nullptr)
			return emptyString;
		return currentClip->id;
	}
};

