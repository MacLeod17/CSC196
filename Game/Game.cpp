
#include "Game.h"

void Game::Startup()
{
	g_particleSystem.Startup();
	m_scene.Startup();
	m_scene.SetGame(this);
}

void Game::Shutdown()
{
	m_scene.Shutdown();
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
		}
		break;
	case Game::eState::START_GAME:
	{
		gk::Player* player = new gk::Player;
		player->Load("player.txt");
		m_scene.AddActor(player);

		for (int i = 0; i < 3; i++)
		{
			gk::Enemy* enemy = new gk::Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(player);
			enemy->GetTransform().position = gk::Vector2{ gk::random(0, 800), gk::random(0, 600) };
			enemy->SetThrust(gk::random(50, 150));
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
			enemy->GetTransform().position = gk::Vector2{ gk::random(0, 800), gk::random(0, 600) };
			enemy->SetThrust(gk::random(50, 150));
			m_scene.AddActor(enemy);
		}

		m_scene.Update(dt);
	}
		break;
	case Game::eState::GAME_OVER:
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
			gk::Color color = colors[(int)gk::random(0, 4)];
			g_particleSystem.Create(gk::Vector2{ x, y }, 0, 180, 2, color, 1, 100, 200);
		}

	}

	g_particleSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frametime).c_str());

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
		m_scene.Draw(graphics);
		graphics.SetColor(gk::Color::white);
		graphics.DrawString(700, 10, std::to_string(m_score).c_str());
		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(gk::Color::green);
		graphics.DrawString(400, 300, "Game Over");
		break;
	default:
		break;
	}
}
