#include "Utilities.h"
#include "player.h"
#include "Platform.h"
#include "Coin.h"
#include "Ball.h"

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
	if ((fixtureAData->type == PLR || fixtureAData->type == PLT) && (fixtureBData->type == PLR || fixtureBData->type == PLT)) {

		b2Vec2 position;
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

		position = player->GetPosition().AsBox2D();
		halfHeight = (player->GetDimensions() * 0.5f).AsBox2D().y;

		b2Vec2 platPos = platform->GetPosition().AsBox2D();
		platPos -= (platform->GetDimensions() * 0.5f).AsBox2D();

		top = platPos.y;

		//Top of platform plus player box dimension.y is lower than player box 
		if (position.y + halfHeight > top + 0.15f) {
			contact->SetEnabled(false);
		}
		else {
			player->SetCanJump(true);
		}
	}
	if ((fixtureAData->type == PLT || fixtureAData->type == CBALL) && (fixtureBData->type == PLT || fixtureBData->type == CBALL)) {

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
	}
	//std::cout << "A: " << position.y - halfHeight << " |B: "<< (top - 3.0f * b2_linearSlop) << std::endl;
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
	if ((fixtureAData->type == PLR || fixtureAData->type == CBALL) && (fixtureBData->type == PLR || fixtureBData->type == CBALL)) {

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

		if (!ball->IsThrown()) {

			ball->Collected();
			player->GainBall(ball);
		}
		return;
	}

	std::cout << "Contact Begun\n";
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

	std::cout << "Contact ended\n";
}