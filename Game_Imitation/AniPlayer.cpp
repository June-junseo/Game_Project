#include "stdafx.h"
#include "AniPlayer.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "??" << std::endl;
		}
	);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	animator.Play("animations/idle.csv");
	SetOrigin(Origins::BC);
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);

	float h = 0.f;
	if (isGrounded)
	{
		h = InputMgr::GetAxis(Axis::Horizontal);
		velocity.x = h * speed;
	}
	//�ٴڿ� �پ��������� �¿� Ű �з�
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{//velocity?
		isGrounded = false;
		velocity.y = -250.f;
		animator.Play("animations/jump.csv");
	}
	if (!isGrounded)
	{
		velocity += gravity * dt; //�̵��ϴ� �ڵ�� ����
	}
	position += velocity * dt; //y �� //�Ʒ��� ���ӵ� (�ٴڿ� �浹�߳� �浹���� �ʾҳ� �˻� )
	if (position.y > 0.f)
	{
		velocity.y = 0.f;
		position.y = 0.f;
		isGrounded = true;
	}
	SetPosition(position); //���� position �� ���� 

	if (h != 0.f) //h�� 0�� �ƴѰ�� 
	{
		SetScale(h > 0.f ? sf::Vector2f(1.0f, 1.0) : sf::Vector2f(- 1.f, 1.0f)); //����
	}

	// Ani
	if (animator.GetCurrentClipId() == "Idle") //�¿�Ű�� ������ �ʾ�����
	{
		if (h != 0.f)
		{
			animator.Play("animations/run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv"); 
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded) //space�� ������ �����ϰ� �ٴڿ� ���������� grounded �� �Ǹ�
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv"); //���̵��̳�
		}
		else
		{
			animator.Play("animations/run.csv"); //run�� ��
		}
	}
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
