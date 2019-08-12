#include "player.h"

const float playerWidth = 1.0f;
const float playerHeight = 1.0f;

Player::Player(int _controller, b2World& _world) {
	if (SDL_IsGameController(_controller)) {
		controller = std::make_unique<SDL_GameController>(SDL_GameControllerOpen(_controller));
	} else {
		fprintf(stderr, "Could not open gamecontroller %i: %s\n", _controller, SDL_GetError());
	}

	dispBody = std::make_unique<SDL_Rect>();

	dispBody->w = 1.0f * PPM;
	dispBody->h = 1.0f * PPM;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	body = std::make_unique<b2Body>(_world.CreateBody(&bodyDef));

	shape = std::make_unique<b2PolygonShape>();
	shape->SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape.get();
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
}

void Player::Render() {
	
}

void Player::Update() {
}
