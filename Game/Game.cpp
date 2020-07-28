
#include "Game.h"
#include "Audio/AudioSystem.h"
#include "Actors/Locator.h"

void Game::Startup()
{
	g_audioSystem.Startup();
	g_particleSystem.Startup();
	m_scene.Startup();
	m_scene.SetGame(this);

	g_audioSystem.AddAudio("Laser", "Laser_Shoot.wav");
	g_audioSystem.AddAudio("Explosion", "Explosion.wav");
}

void Game::Shutdown()
{
	m_scene.Shutdown();
	g_audioSystem.Shutdown();
	g_particleSystem.Shutdown();
}

bool Game::Update(float dt)
{
	m_frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::START_GAME;
			m_score = 0;
			m_lives = 3;
		}
		break;
	case Game::eState::START_GAME:
	{
		gk::Player* player = new gk::Player;
		player->Load("player.txt");

		gk::Locator* locator = new gk::Locator;
		locator->GetTransform().position = gk::Vector2{ 0, 4 };
		player->SetChild(locator);

		m_scene.AddActor(player);

		for (int i = 0; i < 3; i++)
		{
			gk::Enemy* enemy = new gk::Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(player);
			enemy->GetTransform().position = gk::Vector2{ gk::Random(0, 800), gk::Random(0, 600) };
			enemy->SetThrust(gk::Random(50, 150));
			m_scene.AddActor(enemy);
		}
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
	{
		m_spawntimer += dt;
		if (m_spawntimer >= 3.0f)
		{
			m_spawntimer = 0.0f;

			//Add Enemy to Scene
			gk::Enemy* enemy = new gk::Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<gk::Player>());
			enemy->GetTransform().position = gk::Vector2{ gk::Random(0, 800), gk::Random(0, 600) };
			enemy->SetThrust(gk::Random(50, 150));
			m_scene.AddActor(enemy);
		}
	}
		break;
	case Game::eState::PLAYER_DEAD:
	{
		m_lives--;
		if (m_lives <= 0)
		{
			m_state = eState::GAME_OVER;
		}
		else
		{
			m_state = eState::GAME_WAIT;
		}
		m_statetimer = 3.0f;
	}
		break;
	case Game::eState::GAME_WAIT:
		m_statetimer -= dt;
		if (m_statetimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::GAME_OVER:
		m_statetimer -= dt;
		if (m_statetimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
		}
		break;
	default:
		break;
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		gk::Color colors[] = { gk::Color::white, gk::Color::red, gk::Color::green, gk::Color::blue, gk::Color::yellow };

		for (size_t i = 0; i < 30; i++)
		{
			gk::Color color = colors[(int)gk::Random(0, 4)];
			g_particleSystem.Create(gk::Vector2{ x, y }, 0, 180, 2, color, 1, 100, 200);
		}
		g_audioSystem.PlayAudio("Explosion");
	}

	m_scene.Update(dt);
	g_particleSystem.Update(dt);
	g_audioSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frametime).c_str());

	m_scene.Draw(graphics);
	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(gk::Color::green);
		graphics.DrawString(400, 300, "Asteroids");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(gk::Color::green);
		graphics.DrawString(400, 300, "Game Over");
		break;
	default:
		break;
	}

	graphics.SetColor(gk::Color::white);
	graphics.DrawString(700, 10, ("Score: " + std::to_string(m_score)).c_str());
	graphics.DrawString(700, 20, ("Lives: " + std::to_string(m_lives)).c_str());
}
