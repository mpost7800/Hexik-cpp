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

ArmPos HexIK::TranslateIK(int x, int y, int z) {
    ArmPos arm;
    
    arm.coxa = 0;
    arm.femur = 0;
    arm.tibia = 0;
    
    double gamma = this->getGamma(x, z);
    double l = this->getL(y);
    double alpha = this->getAlpha(l);
    double beta = this->getBeta(l);
    
    cout << "gamma " << gamma << endl;
    cout << "alpha " << alpha << endl;
    cout << "beta " << beta << endl;
    
    return arm;
}

void HexIK::SetArmLengths(ArmLengths armLengthsArg) {
    armLengths = armLengthsArg;
}

double HexIK::getGamma (int x, int z) {
    return this->toDegrees(atan(x / z));
}

double HexIK::toDegrees (double radius) {
    return radius  * 180 / M_PI;
}

double HexIK::getL(int y) {
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