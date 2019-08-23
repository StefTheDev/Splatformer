#include "Collider.h"

Collider::Collider(Vector2 _position, Vector2 _dimensions) {
	position = _position;
	dimensions = _dimensions;
}

void Collider::InitialiseStatic(b2World* _world) {
	b2BodyDef bodyDef;

	b2Vec2 b2Position;
	b2Position.x = position.x / PPM;
	b2Position.y = position.y / PPM;

	b2Vec2 b2Dimensions;
	b2Dimensions.x = dimensions.x / PPM;
	b2Dimensions.y = dimensions.y / PPM;

	bodyDef.position = b2Position;

	body = b2BodyPtr(_world->CreateBody(&bodyDef));

	b2PolygonShape boxBody;
	boxBody.SetAsBox(b2Dimensions.x, b2Dimensions.y);

	body->CreateFixture(&boxBody, 0.0f);
}

void Collider::InitialiseDynamic(b2World* _world, float _density, float _friction, float _damping) {
	b2Vec2 b2Position;
	b2Position.x = position.x / PPM;
	b2Position.y = position.y / PPM;

	b2Vec2 b2Dimensions;
	b2Dimensions.x = dimensions.x / PPM;
	b2Dimensions.y = dimensions.y / PPM;

	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Position;
	bodyDef.linearDamping = _damping;
	bodyDef.fixedRotation = true;

	body = b2BodyPtr(_world->CreateBody(&bodyDef));

	b2PolygonShape boxBody;
	boxBody.SetAsBox(b2Dimensions.x, b2Dimensions.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxBody;
	fixtureDef.density = _density;
	fixtureDef.friction = _friction;

	body->CreateFixture(&fixtureDef);
}

void Collider::SetCollisionCategory(int _category) {
	b2Fixture* fix = body->GetFixtureList();

	b2Filter newFilter = fix->GetFilterData();

	newFilter.categoryBits = _category;

	fix->SetFilterData(newFilter);
}

void Collider::SetCollisionMask(int _mask) {
	b2Fixture* fix = body->GetFixtureList();

	b2Filter newFilter = fix->GetFilterData();

	newFilter.maskBits = _mask;

	fix->SetFilterData(newFilter);
}
