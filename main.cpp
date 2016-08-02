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
    armConf.coxa = 0;
    armConf.femur = 5;
    armConf.tibia = 10;
    armConf.zOffset = 0;
    
    arm.SetArmLengths(armConf);
    
    ArmAngles armAngles = arm.TranslateIK(0, 10, 5); // xyz
    
    ArmPos pos = arm.TranslateFK(armAngles);
    
    return 0;
}
