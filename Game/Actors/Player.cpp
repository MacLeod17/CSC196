
#include "core.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Projectile.h"
#include "Graphics/ParticleSystem.h"
#include "../Game.h"
#include "Object/Scene.h"
#include "Math/Math.h"
#include <fstream>

namespace gk
{
	bool Player::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			Actor::Load(stream);

			stream >> m_thrust;
			stream >> m_rotationRate;

			stream.close();
		}

		return success;
	}

	void Player::Update(float dt)
	{
		m_fireTimer += dt;
		
		if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
		{
			m_fireTimer = 0;
			Projectile* projectile = new Projectile;
			projectile->Load("projectile.txt");
			projectile->GetTransform().position = m_transform.position;
			projectile->GetTransform().angle = m_transform.angle;
			m_scene->AddActor(projectile);

			m_scene->GetGame()->AddScore(-5);

			g_audioSystem.PlayAudio("Laser");
		}
		
		Vector2 force{ 0, 0 };
		if (Core::Input::IsPressed('W')) { force = Vector2::forward * m_thrust; }
		force = Vector2::Rotate(force, m_transform.angle);

		m_velocity += force * dt;
		m_velocity *= 0.99f;
		m_transform.position += m_velocity * dt;

		//Rotate
		float torque{ 0.0f };

		if (Core::Input::IsPressed('A')) { torque = -gk::DegreesToRadians(m_rotationRate); }
		if (Core::Input::IsPressed('D')) { torque = gk::DegreesToRadians(m_rotationRate); }

		m_angularVelocity += torque * dt;
		m_angularVelocity *= 0.97f;
		m_transform.angle += m_angularVelocity * dt;

		if (m_transform.position.x > 800) { m_transform.position.x = 0; }
		if (m_transform.position.x < 0) { m_transform.position.x = 800; }

		if (m_transform.position.y > 600) { m_transform.position.y = 0; }
		if (m_transform.position.y < 0) { m_transform.position.y = 600; }

		if (force.Length() > 0)
		{
			Actor* locator = m_children[0];
			g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), m_transform.angle + gk::PI, 20, 1, gk::Color{ 1, 1, 1 }, 1, 100, 200);

			locator = m_children[1];
			g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), m_transform.angle + gk::PI, 20, 1, gk::Color{ 1, 1, 1 }, 1, 100, 200);

		}

		m_transform.Update();

		for (auto child : m_children)
		{
			child->Update(dt);
		}
	}

	void Player::OnCollision(Actor* actor)
	{
		if (actor->GetType() == eType::ENEMY)
		{
			m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);
			m_destroy = true;

			//Set Enemy Targets to NULL
			auto enemies = m_scene->GetActors<gk::Enemy>();
			for (auto enemy : enemies)
			{
				enemy->SetTarget(nullptr);
			}

			Color colors[] = { Color::white, Color::red, Color::green, Color::blue, Color::yellow };

			for (size_t i = 0; i < 30; i++)
			{
				Color color = colors[(int)Random(0, 4)];
				g_particleSystem.Create(m_transform.position, 0, 180, 2, color, 1, 100, 200);
			}
			g_audioSystem.PlayAudio("Explosion");
		}
	}
}