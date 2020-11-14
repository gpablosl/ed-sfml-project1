#include "Rigidbody.hh"

#include<iostream>
Rigidbody::Rigidbody(b2World*& world, b2BodyType bodyType, b2Vec2* position, 
float boxWidth, float boxHeight, float density, float friction, float restitution)
{
    this->world = world;
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

Rigidbody::~Rigidbody()
{
    //delete fixture;
    //world->DestroyBody(body);
    fixture->SetSensor(true);
    body->SetUserData(nullptr);
    //std::cout << "delete body" << std::endl;
    /*body->DestroyFixture(fixture);
    body->SetUserData(nullptr);
    world->DestroyBody(body);*/
    /*fixture = nullptr;
    polygonShape = nullptr;
    fixtureDef = nullptr;
    bodyDef = nullptr;
    body = nullptr;*/
    //body->DestroyFixture(fixture);
    //world->DestroyBody(body);
    //delete this;
    //delete fixtureDef;
    //delete polygonShape;
    //delete bodyDef;
}

b2Body* Rigidbody::GetBody() const
{
    return body;
}

void Rigidbody::SetUserData(void* userData)
{
    body->SetUserData(userData);
}

void Rigidbody::SetSensor(bool status)
{
    fixture->SetSensor(status);
}