/*
 * Aspect.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include <Aspect.h>
#include <Utils.h>
#include <math.h>

Aspect::Aspect (Entity381 * ent){
	this->entity = ent;
	this->aspectType = ASPECT_TYPE::NONE;

}

Aspect::~Aspect(){

}


Renderable::Renderable(Entity381 * ent): Aspect(ent){
	this->aspectType = ASPECT_TYPE::RENDERABLE;
	return;
}

Renderable::~Renderable(){

}

void Renderable::Tick(float dt){
	entity->ogreSceneNode->setPosition(entity->pos);
	entity->ogreSceneNode->setOrientation(Ogre::Quaternion::IDENTITY);
	entity->ogreSceneNode->yaw(Ogre::Radian(-entity->heading));
}

Physics::Physics(Entity381 * ent): Aspect(ent) {
	this->aspectType = ASPECT_TYPE::PHYSICS;
}

Physics::~Physics(){

}

//static float FixAngle(float radiansAngle){
//
//	while (radiansAngle > Ogre::Math::TWO_PI)
//		radiansAngle -= Ogre::Math::TWO_PI;
//	while (radiansAngle < 0)
//		radiansAngle += Ogre::Math::TWO_PI;
//
//	return radiansAngle;
//}
//static float RadToDegree = 57.2958; //180/pi

void Physics::Tick(float dt){

	if(entity->speed < entity->desiredSpeed)
		entity->speed += entity->acceleration *dt;
	if(entity->speed > entity->desiredSpeed)
		entity->speed -= entity->acceleration *dt;

	//entity->speed = std::max(entity->minSpeed, std::min(entity->speed, entity->maxSpeed)); //clamp

	if(entity->heading < entity->desiredHeading)
		entity->heading += entity->turnRate * dt;
	if(entity->heading > entity->desiredHeading)
		entity->heading -= entity->turnRate * dt;

	//entity->heading = FixAngle(entity->heading); // between -pi and pi

	entity->vel = Ogre::Vector3(cos(entity->heading) * entity->speed, 0, sin(entity->heading) * entity->speed);
	entity->pos += entity->vel * dt;

}

UnitAI::UnitAI(Entity381* ent): Aspect(ent){
	commands.clear();
	this->aspectType = ASPECT_TYPE::AI;
}

UnitAI::~UnitAI(){

}

void UnitAI::AddCommand(Command *c){
	commands.push_back(c);
}

void UnitAI::SetCommand(Command* c){
	commands.clear();
	commands.push_front(c);
}

void UnitAI::Tick(float dt){
	std::cout << commands.size() << " commands stored" << std::endl;
	if(!commands.empty()){
		commands.front()->tick(dt);
		std::cout << "Made it before done statement" << std::endl;
		if(commands.front()->done()){
			std::cout << "Made it before popping off the command" << std::endl;
			commands.clear();
			std::cout << "Made it past popping off the command" << std::endl;
		}
	}
}

void UnitAI::clear()
{
	commands.clear();
}

