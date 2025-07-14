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
	//바닥에 붙어있을때만 좌우 키 압력
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{//velocity?
		isGrounded = false;
		velocity.y = -250.f;
		animator.Play("animations/jump.csv");
	}
	if (!isGrounded)
	{
		velocity += gravity * dt; //이동하는 코드랑 동일
	}
	position += velocity * dt; //y 값 //아래도 가속도 (바닥에 충돌했나 충돌하지 않았나 검사 )
	if (position.y > 0.f)
	{
		velocity.y = 0.f;
		position.y = 0.f;
		isGrounded = true;
	}
	SetPosition(position); //실제 position 을 적용 

	if (h != 0.f) //h가 0이 아닌경우 
	{
		SetScale(h > 0.f ? sf::Vector2f(1.0f, 1.0) : sf::Vector2f(- 1.f, 1.0f)); //반전
	}

	// Ani
	if (animator.GetCurrentClipId() == "Idle") //좌우키가 눌리지 않았을떄
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
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded) //space바 눌러서 점프하고 바닥에 떨저졌을떄 grounded 가 되면
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv"); //아이들이나
		}
		else
		{
			animator.Play("animations/run.csv"); //run이 됨
		}
	}
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
