#pragma once

#include "core.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Object/Actor.h"
#include "Object/Scene.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>

class Game
{
public:
	enum class eState
	{
		INIT,
		TITLE,
		START_GAME,
		PLAYER_DEAD,
		GAME_WAIT,
		GAME,
		GAME_OVER
	};

public:
	void Startup();
	void Shutdown();

	bool LoadHighScore(const std::string& filename);
	void SaveHighScore(const std::string& filename);

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	void AddScore(int points) 
	{ 
		m_score += points;
		if (m_score < 0) m_score = 0;
		if (points > 0) m_scoresincedeath += points; 
		if (m_score >= m_highscore) m_highscore = m_score;
	}
	void SetState(eState state) { m_state = state; }

protected:
	eState m_state{ eState::TITLE };

	int m_lives{ 3 };
	int m_score{ 0 };
	int m_highscore{ 0 };
	int m_scoresincedeath{ 0 };

	float m_frametime;
	float m_spawntimer{ 0 };
	float m_statetimer{ 0 };
	float m_oneuptimer{ 0 };

	gk::Scene m_scene;
};

