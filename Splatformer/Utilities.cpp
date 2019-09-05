#include "Utilities.h"
#include "player.h"
#include "Platform.h"

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

	position = player->GetPosition().AsBox2D();
	halfHeight = (player->GetDimensions() * 0.5f).AsBox2D().y;

	b2Vec2 platPos = platform->GetPosition().AsBox2D();
	platPos -= (platform->GetDimensions() * 0.5f).AsBox2D();

	top = platPos.y;

	//Top of platform plus player box dimension.y is lower than player box 
	if (position.y + halfHeight > top + 0.15f) {
		contact->SetEnabled(false);
	} else {
		player->SetCanJump(true);
	}

	//std::cout << "A: " << position.y - halfHeight << " |B: "<< (top - 3.0f * b2_linearSlop) << std::endl;
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