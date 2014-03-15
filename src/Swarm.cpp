#include "Swarm.h"

// This 'Swarm' object demonstrates a simple particle system
//  with 'simple harmonic motion'

Swarm::Swarm(){
	light.setAmbientColor(ofColor(0, 0, 0));
}

void Swarm::init(int nParticles, float positionDispersion, float velocityDispersion){

	// Check if we've already initialised
	if(particles.size() != 0){
		// clear out old data
		ofLogWarning("Swarm") <<  "Swarm: Already initialised";

		particles.clear();
	}

	ofSeedRandom();
	//
	ofVec3f position, velocity;
	ofColor color;
	for(int i = 0; i < nParticles; i++){
		position.x = (ofRandom(1.0f) - 0.5f)  * positionDispersion;
		position.y = (ofRandom(1.0f) - 0.5f)  * positionDispersion;
		position.z = (ofRandom(1.0f) - 0.5f)  * positionDispersion;

		velocity.x = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;
		velocity.y = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;
		velocity.z = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;

		color.r = ofRandom(255.0f);
		color.g = ofRandom(255.0f);
		color.b = 150.0f;
		color.a = 255.0f;

		particle newParticle;
		newParticle.position = position;
		newParticle.velocity = velocity;
		newParticle.color = color;

		// add our new particle to the vector
		particles.push_back(newParticle);
	}

}

void Swarm::customDraw(){
	//--
	// Draw particles

	// We use the position of the first
	//  particle as the position of the
	//  light.
	ofPushStyle();
	light.enable();
	light.setPosition(particles[0].position);

	for(unsigned int i = 0; i < particles.size(); i++){
		ofPushStyle();
		ofSetColor(particles[i].color);

		ofDrawSphere(particles[i].position, 1.0);

		ofPopStyle();
	}

	light.disable();
	ofDisableLighting();

	ofPopStyle();
}

void Swarm::update(){

	// Calculate time past per frame
	float dt = ofGetLastFrameTime();

	// Update positions, velocities
	for(unsigned int i = 0; i < particles.size(); i++){

		// -----------
		//
		//	MOTION MATHS
		//
		//		'Simple Harmonic Motion' + a little extra
		// ----
		//

		// [1] apply velocity to postion
		//  (i.e. integrate velocity)
		//
		//  v = dx / dt (*)
		//  x = x + dx [every frame]
		//
		// therefore
		//  x = x + v * dt (*)
		//

		// (velcotity is taken from previous frame)
		particles[i].position += particles[i].velocity * dt;



		// [2] apply spring force to velocity
		//  (i.e. integrate acceleration)
		//
		//  a = -k * x (this is the shm restoring force, aka spring force)
		//  a = dv / dt
		//
		// therefore from (*)s above
		//  (v = v + dv)
		//
		//  v = v + (dt * a)
		//  v = v + (dt * -k * x)
		//
		particles[i].velocity += -SPRING_CONSTANT * particles[i].position * dt;


		// [3] to get a super simple kind of 'flocking' behaviour
		//  we add a second spring force to velocity relative
		//  to the position of the light
		// NOTICE: THIS ISN'T REAL FLOCKING!
		particles[i].velocity += -SPRING_CONSTANT * (particles[i].position - light.getPosition()) * dt;


		// [4] Force a maximum velocity
		if(particles[i].velocity.length() > MAX_VELOCITY){
			particles[i].velocity /= particles[i].velocity.length() * MAX_VELOCITY;
		}

		//
		// -----------

	}
}
