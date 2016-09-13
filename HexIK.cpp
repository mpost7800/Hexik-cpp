//
//  HexIK.cpp
//  HexIK
//
//  Created by Jimmy on 20/06/16.
//  Copyright (c) 2016 Jimmy. All rights reserved.
//

#include "HexIK.h"
#include "ArmPos.h"
#include <iostream>
#include <cmath>

using namespace std;

HexIK::HexIK (void) {
    cout << "HexIK test" << endl;
}

ArmAngles HexIK::TranslateIK (int x, int y, int z) {
    ArmAngles arm;

    double l = this->getL(y);
    
    arm.gamma = this->getGamma(x, y);
    arm.alpha = this->getAlpha(l);
    arm.beta = this->getBeta(l);
    
    cout << "gamma " << arm.gamma << endl;
    cout << "alpha " << arm.alpha << endl;
    cout << "beta " << arm.beta << endl;
    
    return arm;
}

ArmPos HexIK::TranslateFK (ArmAngles angles) {
    ArmPos pos;
    
//    angles.gamma = this->toRadians(angles.gamma);
//    angles.alpha = this->toRadians(angles.alpha);
//    angles.beta = this->toRadians(angles.beta);
    // (coxa plus (femur * alpha) + (tibia * beta)) * gamma
    angles.beta = this->toRadians(angles.beta - (angles.alpha - 90));
    angles.alpha = this->toRadians(angles.alpha - 90); // Add 90 to reach 0-180 degree of servo
    angles.gamma = this->toRadians(angles.gamma);
    double l = armLengths.coxa + (cos(angles.alpha) * armLengths.femur) + (sin(angles.beta) * armLengths.tibia);
    
    cout << "L:" << l << endl;
    cout << "Angle alpha:" << this->toDegrees(angles.alpha) << endl;
    cout << "Angle beta:" << this->toDegrees(angles.beta) << endl;
    cout << "Coxa:" << armLengths.coxa << endl;
    cout << "Femur length:" << armLengths.femur << endl;
    cout << "Femur calc:" << (cos(angles.alpha) * armLengths.femur) << endl;
    cout << "Tibia length:" << armLengths.tibia << endl;
    cout << "Tibia calc:" << (sin(angles.beta) * armLengths.tibia) << endl;
    
    pos.y = cos(angles.gamma) * l;
    pos.x = sin(angles.gamma) * l;
    pos.z = armLengths.zOffset + (sin(angles.alpha) * armLengths.femur) - (sin(angles.beta) * armLengths.tibia);
    
    cout << "FK Y:" << pos.y << endl;
    cout << "FK X:" << pos.x << endl;
    cout << "FK Z:" << pos.z << endl;
    
    return pos;
}

void HexIK::SetArmLengths (ArmLengths armLengthsArg) {
    armLengths = armLengthsArg;
}

double HexIK::getGamma (int x, int y) {
    return this->toDegrees(atan(x / y));
}

double HexIK::toDegrees (double radius) {
    return radius  * 180 / M_PI;
}

double HexIK::toRadians (double degrees) {
    return degrees * M_PI / 180;
}

double HexIK::getL (int y) {
    return sqrt(pow(armLengths.zOffset, 2) + pow(y - armLengths.coxa, 2));
}

double HexIK::getAlpha (double l) {
    double alphaOne = acos(armLengths.zOffset / l);
    double alphaTwo = acos((pow(armLengths.tibia, 2) - pow(armLengths.femur, 2) - pow(l, 2)) / (-2 * armLengths.femur * l));
    
    return this->toDegrees(alphaOne + alphaTwo);
}

double HexIK::getBeta (double l) {
    return this->toDegrees(acos((pow(l, 2) - pow(armLengths.tibia, 2) - pow(armLengths.femur, 2)) / (-2 * armLengths.tibia * armLengths.femur)));
}