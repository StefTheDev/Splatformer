#include "Collider.h"

Collider::Collider(Vector2 _position, Vector2 _dimensions) {
	position = _position;
	dimensions = _dimensions;
}

void Collider::InitialiseStatic(b2World* _world, bool _isSensor) {
	b2Vec2 b2Dimensions = (dimensions/2.0f).AsBox2D();
	
	b2BodyDef bodyDef;

	bodyDef.position = position.AsBox2D();

	body = b2BodyPtr(_world->CreateBody(&bodyDef));

	//b2Vec2 points[] = {
	//	{0.0f, 0.0f},
	//	{0.0f, -dimensions.y},
	//	{-dimensions.x, -dimensions.y},
	//	{-dimensions.x, 0.0f}
	//};

	b2PolygonShape boxBody;
	boxBody.SetAsBox(b2Dimensions.x, b2Dimensions.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxBody;
	fixtureDef.isSensor = _isSensor;

	body->CreateFixture(&fixtureDef);
}

void Collider::InitialiseDynamic(b2World* _world, float _density, float _friction, float _damping, bool _isSensor) {
	b2Vec2 b2Dimensions = (dimensions / 2.0f).AsBox2D();

	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;
	bodyDef.position = position.AsBox2D();
	bodyDef.linearDamping = _damping;
	bodyDef.fixedRotation = true;

	body = b2BodyPtr(_world->CreateBody(&bodyDef));

	b2PolygonShape boxBody;
	boxBody.SetAsBox(b2Dimensions.x, b2Dimensions.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxBody;
	fixtureDef.isSensor = _isSensor;
	fixtureDef.density = _density;
	fixtureDef.friction = _friction;

	body->CreateFixture(&fixtureDef);
}

void Collider::InitialiseKinematic(b2World* _world, bool _isSensor) {
	b2Vec2 b2Dimensions = dimensions.AsBox2D();
	
	b2BodyDef bodyDef;

	bodyDef.type = b2_kinematicBody;
	bodyDef.position = position.AsBox2D();

	body = b2BodyPtr(_world->CreateBody(&bodyDef));

	b2PolygonShape boxBody;
	boxBody.SetAsBox(b2Dimensions.x, b2Dimensions.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxBody;
	fixtureDef.isSensor = _isSensor;

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

Vector2 Collider::GetPosition() {
	Vector2 offset = (dimensions / 2.0f);

	return Vector2(body->GetPosition() - offset);
}
