#include "Rigidbody.hh"

Rigidbody::Rigidbody(b2World*& world, b2BodyType bodyType, b2Vec2* position, 
float boxWidth, float boxHeight, float density, float friction, float restitution)
{
    bodyDef = new b2BodyDef();
    bodyDef->type = bodyType;
    bodyDef->position = *position;

    body = world->CreateBody(bodyDef);
    polygonShape = new b2PolygonShape();
    polygonShape->SetAsBox(boxWidth, boxHeight); 

    fixtureDef = new b2FixtureDef();
    fixtureDef->shape = polygonShape;
    fixtureDef->density = density; 
    fixtureDef->friction = friction;
    fixtureDef->restitution = restitution; 

    fixture = body->CreateFixture(fixtureDef);
}

Rigidbody::~Rigidbody(){}

b2Body* Rigidbody::GetBody() const
{
    return body;
}