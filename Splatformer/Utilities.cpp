#include "Utilities.h"
#include "player.h"
#include "Platform.h"
#include "Coin.h"
#include "Ball.h"
#include "RespawnPlatform.h"

float deltaTime = 0.0f;

int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;

unsigned int SELECTED_LEVEL = 0;
int controllersAtStartOfGame = 0;

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
	if ((fixtureAData->type == PLR || fixtureAData->type == PLT) && (fixtureBData->type == PLR || fixtureBData->type == PLT)) {

		Vector2 position;
		float32 top, halfHeight;
		Player* player;
		Platform* platform;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);

			platform = static_cast<Platform*>(fixtureBData->data);
		}
		else {
			player = static_cast<Player*>(fixtureBData->data);

			platform = static_cast<Platform*>(fixtureAData->data);
		}

		position = player->GetPosition();
		halfHeight = (player->GetDimensions() * 0.5f).y;

		Vector2 platPos = platform->GetPosition();
		platPos -= (platform->GetDimensions() * 0.5f);

		top = platPos.y;

		//Top of platform plus player box dimension.y is lower than player box 
		if (position.y + halfHeight > top + 0.15f) {
			contact->SetEnabled(false);
		}
		else {
			player->SetCanJump(true);
		}
	}else if ((fixtureAData->type == PLR || fixtureAData->type == RESPAWN) && (fixtureBData->type == PLR || fixtureBData->type == RESPAWN)) {

		Vector2 position;
		float32 top, halfHeight;
		Player* player;
		Platform* platform;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);

			platform = static_cast<RespawnPlatform*>(fixtureBData->data);
		} else {
			player = static_cast<Player*>(fixtureBData->data);

			platform = static_cast<RespawnPlatform*>(fixtureAData->data);
		}

		position = player->GetPosition();
		halfHeight = (player->GetDimensions() * 0.5f).y;

		Vector2 platPos = platform->GetPosition();
		platPos -= (platform->GetDimensions() * 0.5f);

		top = platPos.y;

		//Top of platform plus player box dimension.y is lower than player box 
		if (position.y + halfHeight > top + 0.15f) {
			contact->SetEnabled(false);
		} else {
			player->SetCanJump(true);
		}
	} else if ((fixtureAData->type == PLT || fixtureAData->type == CBALL) && (fixtureBData->type == PLT || fixtureBData->type == CBALL)) {

		b2Vec2 position;
		float32 top, halfHeight;
		Ball* ball;
		Platform* platform;

		if (fixtureAData->type == PLT) {
			platform = static_cast<Platform*>(fixtureAData->data);

			ball = static_cast<Ball*>(fixtureBData->data);
		}
		else {
			platform = static_cast<Platform*>(fixtureBData->data);

			ball = static_cast<Ball*>(fixtureAData->data);
		}

		position = ball->GetPosition().AsBox2D();
		halfHeight = (ball->GetDimensions() * 0.5f).AsBox2D().y;

		b2Vec2 platPos = platform->GetPosition().AsBox2D();
		platPos -= (platform->GetDimensions() * 0.5f).AsBox2D();

		top = platPos.y;

		if (position.y + halfHeight > top + 0.15f) {
			contact->SetEnabled(false);
		}
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
	else if ((fixtureAData->type == PLR || fixtureAData->type == CBALL) && (fixtureBData->type == PLR || fixtureBData->type == CBALL)) {
		b2Vec2 position;
		float32 top, halfHeight;
		Player* player;
		Ball* ball;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);
			ball = static_cast<Ball*>(fixtureBData->data);
		}
		else {
			player = static_cast<Player*>(fixtureBData->data);
			ball = static_cast<Ball*>(fixtureAData->data);
		}

		if (!ball->IsThrown() && !ball->isCollected()) {

			ball->Collect();
			player->GainBall(ball);
		}

		return;

	} else if ((fixtureAData->type == PLR || fixtureAData->type == RESPAWN) && (fixtureBData->type == PLR || fixtureBData->type == RESPAWN)) {
		Player* player;
		RespawnPlatform* respawnPlatform;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);

			respawnPlatform = static_cast<RespawnPlatform*>(fixtureBData->data);
		} else {
			player = static_cast<Player*>(fixtureBData->data);

			respawnPlatform = static_cast<RespawnPlatform*>(fixtureAData->data);
		}

		if ((player->GetPosition().y + player->GetDimensions().y / 2) < (respawnPlatform->GetPosition().y - respawnPlatform->GetDimensions().y / 2) && !respawnPlatform->GetActive()) {
			respawnPlatform->Activate();
			player->addCoins(5);
		}


		return;
	}

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

	if ((fixtureAData->type == PLR || fixtureAData->type == RESPAWN) && (fixtureBData->type == PLR || fixtureBData->type == RESPAWN)) {

		b2Vec2 position;
		float32 top, halfHeight;
		Player* player;
		Platform* platform;

		if (fixtureAData->type == PLR) {
			player = static_cast<Player*>(fixtureAData->data);

			platform = static_cast<RespawnPlatform*>(fixtureBData->data);
		} else {
			player = static_cast<Player*>(fixtureBData->data);

			platform = static_cast<RespawnPlatform*>(fixtureAData->data);
		}

		player->SetCanJump(false);
		return;
	}

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


float mapTo(float _x, float _min, float _max, float _outMin, float _outMax) {
	return _outMin + (_x - _min) * (_outMax - _outMin) / (_max - _min);
}