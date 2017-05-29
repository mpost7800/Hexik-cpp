//
//  main.cpp
//  HexIK
//
//  Created by Jimmy on 20/06/16.
//  Copyright (c) 2016 Jimmy. All rights reserved.
//

#include <iostream>
#include "HexIK.h"
#include "ArmPos.h"
#include "ArmLengths.h"

using namespace std;

int main(int argc, const char * argv[]) {
    HexIK arm;
    
    ArmLengths armConf;
    armConf.coxa = 1;
    armConf.femur = 1;
    armConf.tibia = 1;
    armConf.zOffset = 1;
    
    arm.SetArmLengths(armConf);
    
    ArmAngles armAngles = arm.TranslateIK(0, 2, 0); // xyz
//    ArmAngles armAngles;
    
//    armAngles.alpha = 125.801;
//    armAngles.beta = 112.78;
//    armAngles.gamma = -10;
    
//    ArmPos pos = arm.TranslateFK(armAngles);
    
    return 0;
}
