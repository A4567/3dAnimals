#pragma once

#include "ofMain.h"
//custom creature class
class creature {
public:
    
    creature();
    ~creature();
    
    void torso();
    void head(ofVec3f start);
    void arms(ofVec3f leftArm, ofVec3f rightArm);
    void legs(ofVec3f leftLeg, ofVec3f rightLeg);
    
    int height,radius,resolution;
    float limbRatioH,limbRatioR,headRatio;
    
    ofVec3f torsoPoint;
    
    ofTexture faceTex,torsoTex,armsTex,legsTex;
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    ofEasyCam cam;
    ofLight light;
    
    float rotaty;
    
    vector<creature> creatures;
    
    bool walk;
};
