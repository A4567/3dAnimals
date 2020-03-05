#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //initialise creature count and push creatures to creature vector.
    int numCreatures = 1;
    for(int i = 0; i < numCreatures; i++){
        creature newCreature;
        creatures.push_back(newCreature);
    }
    //define paramters for the light and camera
    light.setPosition(-100, 500, 500); // make a light to light our 3D scene
    light.setPointLight();
    
    cam.setPosition(0,0, 300);
    ofVec3f centre(0,0,0);
    
    cam.lookAt(creatures[0].torsoPoint);
    ofEnableDepthTest();
    // variables which allow "animation" of the creature
    walk = false;
    rotaty = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    //keeping the camera centred on the creature
    cam.setPosition(creatures[0].torsoPoint.x+creatures[0].radius,creatures[0].torsoPoint.y+creatures[0].height, creatures[0].torsoPoint.z+500);
    ofVec3f focus(creatures[0].torsoPoint);
    cam.lookAt(focus);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw the creature in the centre of the space
    if(!walk){
    cam.begin();
    light.enable();
    creatures[0].torso();
    light.disable();
    cam.end();
    }else{
        //draw the creature and allow it to move around using perlin noise. sometimes rotating if i want to uncomment that
        cam.begin();
        light.enable();
        ofDrawSphere(0,0,0, 10);
        float posX = 102.34;
        float posZ = 123.45;
        float speed = 0.1;
        creatures[0].torsoPoint.x = ((ofGetWidth()*2) * ofNoise(ofGetElapsedTimef() * speed + posX)) - ofGetWidth()/2;
        creatures[0].torsoPoint.z = ((ofGetWidth()*2) * ofNoise(ofGetElapsedTimef() * speed + posZ)) - ofGetWidth()/2;
        //creatures[0].torsoPoint.z += 1;
        //rotaty += 1;
        ofPushMatrix();
        ofRotateYDeg(rotaty);
        creatures[0].torso();
        ofPopMatrix();
        light.disable();
        cam.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //generates new creature
    if(key == 'n'){
        creatures.clear();
        creature newCreature;
        creatures.push_back(newCreature);
    }
    //toggles the walk feature
    if(key == 'w'){
        walk = !walk;
        
        
    }
}

//----------------creature class functions------------------------------------
//constructor
creature::creature(){
    //assigning initial values to radius and height determining overall size of creature
    height = ofRandom(100,300);
    radius = ofRandom(5,75);
    //setting rations for the limbs and head to follow so not all shapes are the same size
    limbRatioH = 0.8;
    limbRatioR = 0.4;
    headRatio = 0.66;
    //assigning a random resolution to the cylinders used to create the creature
    resolution = ofRandom(3,30);
    
    //setting torso origin to centre
    torsoPoint.x = 0;
    torsoPoint.y = 0;
    torsoPoint.z = 0;
}

creature::~creature(){
    
}

void creature::torso(){
    //putting a texture on the body
    ofDisableArbTex();
    string texture = "torso.png";
    ofLoadImage(torsoTex,texture);
    torsoTex.bind();
    //drawing the torso
    ofSetCylinderResolution(resolution, 8);
    ofDrawCylinder(torsoPoint, radius, height);
    
    torsoTex.unbind();
    //setting points relative to the toso for the head and drawing the head
    ofVec3f headPoint(torsoPoint.x,torsoPoint.y+height/2 + (radius*headRatio),torsoPoint.z);
    head(headPoint);
    // doing the same for the left and right arms and legs.
    ofVec3f leftArm(torsoPoint.x-radius,(height/2)-((height*limbRatioH)/2),torsoPoint.z);
    ofVec3f rightArm(torsoPoint.x+radius,(height/2)-((height*limbRatioH)/2),torsoPoint.z);
    arms(leftArm,rightArm);
    
    ofVec3f leftLeg(torsoPoint.x-radius+(limbRatioR*radius),-((height/2)+(height*limbRatioH/2)),torsoPoint.z);
    ofVec3f rightLeg(torsoPoint.x+radius-(limbRatioR*radius),-((height/2)+(height*limbRatioH/2)),torsoPoint.z);
    legs(leftLeg,rightLeg);
    
}

void creature::head(ofVec3f start){
    ofDisableArbTex();
    string texture = "face.png";
    ofLoadImage(faceTex,texture);
    faceTex.bind();
    //ofSetColor(255,0,0);
    float size = radius*headRatio;
    ofDrawSphere(start, size);
    faceTex.unbind();
}

void creature::arms(ofVec3f leftArm, ofVec3f rightArm){
    
    
    float aR = radius * limbRatioR;
    float aH = height * limbRatioH;
   // ofSetColor(0,255,0);
    //left arm
    ofDrawCylinder(leftArm, aR, aH);
    //right arm
    ofDrawCylinder(rightArm, aR, aH);

}

void creature::legs(ofVec3f leftLeg, ofVec3f rightLeg){
    float lR = radius * limbRatioR;
    float lH = height * limbRatioH;
    
    //ofSetColor(0,0,255);
    //left leg
    ofDrawCylinder(leftLeg, lR, lH);
    //right leg
    ofDrawCylinder(rightLeg, lR, lH);
}
