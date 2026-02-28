#pragma once
#ifndef _define  //Define the dimension of ground
#define _define





#define	XIAOJINGQU	21.0
#define DAJINGQU	41.0

#define	STARTTIME	8
#define	NUMBER4		7
#define	NUMBER3		10
#define	NUMBER2		3
#define	NUMBER10	10
#define	NUMBER15	25
#define	NUMBERdefend	7
#define	NUMBERLAX	35
#define	NUMBERLAY	35
#define	NUMBERLDX	50
#define	NUMBERLDY	15
#define	NUMBERBHX	50
#define	NUMBERAAX	20 //
#define	NUMBERAAY	25 //25 
#define	NUMBERAWX	30
#define	NUMBERAWY	30
#define	NUMBERABWX	40  //50
#define	NUMBERABWY	15  //7
#define	VERYBOUND	7

#define	CBOUND		10
/////



#define		goal_y_widthM		50
#define		goal_y_widthL		90
#define		goal_x_widthM		15
#define		goal_x_widthL		35
#define     LINE1               20
#define     LINE2               35
#define     LINE3               60
#define     LINE4               170
#define     BOUND1              15
#define     BOUND2              25
#define     CORNERANGLE         Pi/4
#define     BACKANGLE           Pi/4
#define     FORTHANGLE          Pi/3
#define     ATTACK              0
#define     NORMAL              0
#define		G_OFFSET			5//-1.5
#define		CENTER_X			110.0		
#define		CENTER_Y			90.0		
#define		GATE_UP_LINE		110.0 
#define		GATE_DN_LINE		70.0
#define		GOAL_UP_LINE		125.0 
#define		GOAL_DN_LINE		55.0
#define     gVMAX               60.0//60.0
#define		RGATE_X				220			//bound_right;	
#define		RGATE_Y				90			//(bound_top+bound_bottom)/2;
#define     UP_LINE             145
#define     DN_LINE             35
#define		GOALS_UP_LINE		115 
#define		GOALS_DN_LINE		65
#define		GOALL_UP_LINE		135 
#define		GOALL_DN_LINE		45
#define		goal_y_widthS		50
#define Tperiod 0.040
#define BoundMinDist 8
#define bound 10
#define power 1.5
#define DistDiff 1//球与车之间的最大距离偏差
#define MinDist 8//球与车之间的最小距离
//场地分区/////////////////////////////////////////////////////////////////////////////
#define UpBound 1
#define DownBound 2
#define RUpCorner 3
#define RDownCorner 4
#define LUpCorner 5
#define LDownCorner 6
#define BackField 7 
#define MidField 8
#define FrontField 9
#define LZone 10
#define RZone 11 
//     |--------------|-------------------------------------------|-------------|
//     |LUpCorner=5   |                  UpBound=1                |RUpCorner=3  |
// |---|--------------|--------------|---------------|------------|-------------|---|
// |   |LZone=10      |BackField=7   |MidField=8     |FrontField=9| RZone=11    |   |
// |   |              |              |               |            |             |   |
// |---|--------------|--------------|---------------|------------|-------------|---|
//     |LDownCorner=6 |                  DownBound=2              |RDownCorner=4|
//     |--------------|-------------------------------------------|-------------|
////////////////////////////////////////////////////////////////////////////////////////
//*****************************
//*****************************


////////////////////////////////////////
//Discrib the special point such as: penalty kick ect.
#define		RPKFK_X				112.5			
#define		RPKFK_Y				65			
#define		LUP_FB_X			37.5			
#define		LUP_FB_Y1			25		

#define		PKICK				0
#define		FKICK				1	
//UINT(/int)	DEStrategyStyle
#define	Strategy1		0
#define	Strategy2		1
#define	Strategy3		2
#define	Strategy4		3
#define	Strategy5		4
#define	Strategy6		5
#define Strategy7       6
#define Strategy8       7
//***************************************************************//
#endif