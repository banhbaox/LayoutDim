// Copyright Kubotek Corporation, 2006-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CKSSIMCONSTRAINTOPTIONS_H_LOADED
#define CKSSIMCONSTRAINTOPTIONS_H_LOADED

// @doc EXTERNAL SDK

/////////////////////////////////////////////////////////////////////////////
// AnimationOptions

// @class The CKSSimConstraintOptions class
// The class for the options of animation constraint entities in KeyCreator.

class CKSSimConstraintOptions {
public:
	//@cmember Type of constraint, internal use
	int nType;

	//@cmember Is this a grounded constraint
	bool bWorld;

	//@cmember Can the constrained bodies collide?
	bool bCollision;

	//@cmember Angular motor settings, if applicable
	bool bMotor; double dMotorSpeed; double dMotorStrength;

	//@cmember Linear motor settings, if applicable
	bool bLinMotor; double dLinMotorSpeed; double dLinMotorStrength;

	//@cmember Angular limits, if applicable
	//One value per axis
	bool bAngLimit[2]; double dAngMin[2]; double dAngMax[2];

	//@cmember Linear limits, if applicable
	bool bLinLimit; double dLinMin; double dLinMax;

	//@cmember Has the axis been reversed
	bool bReverse;

	//@cmember Gear ratio, if applicable
	double dGearRatio;

	//@cmember Intermittent motor settings
	bool bIntermittent; g_array<double> adIntermittent;

	CKSSimConstraintOptions() 
	{
		//Set defaults
		nType = 0;
		bWorld = false;
		bCollision = false;
		bMotor = false;
		dMotorSpeed = 90;
		dMotorStrength = 1000;
		bLinMotor = false;
		dLinMotorSpeed = 10;
		dLinMotorStrength = 1000;
		bAngLimit[0] = bAngLimit[1] = false;
		dAngMin[0] = dAngMin[1] = 0;
		dAngMax[0] = dAngMax[1] = 0;
		bLinLimit = 0;
		dLinMin = 0;
		dLinMax = 0;
		bReverse = false;
		dGearRatio = 1;
		bIntermittent = false;
	}
};

#endif