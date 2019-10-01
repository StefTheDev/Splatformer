#include "Utilities.h"
#include "player.h"
#include "Platform.h"
#include "Coin.h"
#include "RespawnPlatform.h"

float deltaTime = 0.0f;

void PlatformingListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	DataContainer* fixtureAData = static_cast<DataContainer*>(fixtureA->GetBody()->GetUserData());
	DataContainer* fixtureBData = static_cast<DataContainer*>(fixtureB->GetBody()->GetUserData());

	//If fixture A and B are the same type, return
	if (fixtureAData->type == fixtureBData->type) return;

	//If fixture A or B are unimportant types
	if (fixtureAData->type == OTHER || fixtureBData->type == OTHER) {
		return;
	}

	Vector2 position;
	float32 top, halfHeight;
	Player* player;
	Platform* platform;

	if (fixtureAData->type == PLR) {
		player = static_cast<Player*>(fixtureAData->data);

		platform = static_cast<Platform*>(fixtureBData->data);
	} else {
		player = static_cast<Player*>(fixtureBData->data);

		platform = static_cast<Platform*>(fixtureAData->data);
	}

	position = player->GetPosition();
	halfHeight = (player->GetDimensions() * 0.5f).y;

	Vector2 platPos = platform->GetPosition();
	platPos -= (platform->GetDimensions() * 0.5f);

	top = platPos.y;

	//Top of platform plus player box dimension.y is lower than player box 
	if (position.y + halfHeight > (top + (platform->GetDimensions() * 0.2f).y)) {
		contact->SetEnabled(false);
	} else {
		player->SetCanJump(true);
	}
}

void PlatformingListener::BeginContact(b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	DataContainer* fixtureAData = static_cast<DataContainer*>(fixtureA->GetBody()->GetUserData());
	DataContainer* fixtureBData = static_cast<DataContainer*>(fixtureB->GetBody()->GetUserData());

	//If fixture A and B are the same type, return
	if (fixtureAData->type == fixtureBData->type) return;

	//If fixture A or B are unimportant types
	if (fixtureAData->type == OTHER || fixtureBData->type == OTHER) {
		return;
	}

	if ((fixtureAData->type == PLR || fixtureAData->type == ECOIN) && (fixtureBData->type == PLR || fixtureBData->type == ECOIN)) {

		b2Vec2 position;
		float32 top, halfHeight;
		Player* player;
		Coin* coin;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);

			coin = static_cast<Coin*>(fixtureBData->data);
		}
		else {
			player = static_cast<Player*>(fixtureBData->data);

			coin = static_cast<Coin*>(fixtureAData->data);
		}

		player->addCoin();

		coin->Collected();

		return;
	}

	else if ((fixtureAData->type == PLR || fixtureAData->type == RESPAWN) && (fixtureBData->type == PLR || fixtureBData->type == RESPAWN)) 
	{
		Player* player;
		RespawnPlatform* respawnPlatform;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);

			respawnPlatform = static_cast<RespawnPlatform*>(fixtureBData->data);
		}
		else {
			player = static_cast<Player*>(fixtureBData->data);

			respawnPlatform = static_cast<RespawnPlatform*>(fixtureAData->data);
		}

		if ((player->GetPosition().y + player->GetDimensions().y / 2) < (respawnPlatform->GetPosition().y - respawnPlatform->GetDimensions().y / 2))
		{
			respawnPlatform->Activate();
		}
		//std::cout << "CONTACT: " << contact->IsEnabled();
		

		return;
	}

	std::cout << "Contact ended\n";
}

void PlatformingListener::EndContact(b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	DataContainer* fixtureAData = static_cast<DataContainer*>(fixtureA->GetBody()->GetUserData());
	DataContainer* fixtureBData = static_cast<DataContainer*>(fixtureB->GetBody()->GetUserData());

	//If fixture A and B are the same type, return
	if (fixtureAData->type == fixtureBData->type) return;

	//If fixture A or B are unimportant types
	if (fixtureAData->type == OTHER || fixtureBData->type == OTHER) {
		return;
	}

#pragma region Platform/Player De-Collisions
	if ((fixtureAData->type == PLR || fixtureAData->type == PLT) && (fixtureBData->type == PLR || fixtureBData->type == PLT)) {

		b2Vec2 position;
		float32 top, halfHeight;
		Player* player;
		Platform* platform;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);

			platform = static_cast<Platform*>(fixtureBData->data);
		} else {
			player = static_cast<Player*>(fixtureBData->data);

			platform = static_cast<Platform*>(fixtureAData->data);
		}

		player->SetCanJump(false);
		return;
	}
#pragma endregion

#pragma region Player/Camera De-Collisions
	else if ((fixtureAData->type == PLR || fixtureAData->type == CAM) && (fixtureBData->type == PLR || fixtureBData->type == CAM)) {
		Player* player;
		Camera* camera;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);
			camera = static_cast<Camera*>(fixtureBData->data);
		} else {
			player = static_cast<Player*>(fixtureBData->data);
			camera = static_cast<Camera*>(fixtureAData->data);
		}

		player->Kill();
		return;
	}
#pragma endregion
}