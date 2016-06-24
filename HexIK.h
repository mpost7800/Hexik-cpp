//
//  HexIK.h
//  HexIK
//
//  Created by Jimmy on 20/06/16.
//  Copyright (c) 2016 Jimmy. All rights reserved.
//

#ifndef HexIK_HexIK_h
#define HexIK_HexIK_h

#include "ArmPos.h"
#include "ArmLengths.h"

class HexIK {
    
public:
    HexIK();
    ArmPos TranslateIK(int x, int y, int z);
    void SetArmLengths(ArmLengths armLengths);
    
private:
    ArmLengths armLengths;
    double getGamma(int x, int z);
    double toDegrees(double radius);
    double getAlpha(double l);
    double getBeta(double l);
    double getL(int y);
};

#endif
