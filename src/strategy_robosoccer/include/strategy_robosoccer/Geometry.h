/*
 * Geomotry.h
 *
 *  Created on: 09.01.2025
 *      Author: Wang Jiguo
 */

#include <cmath>
#include "strategy.h"

typedef struct tagLineFormulation{
	double a;
	double b;
	double c;
}LINEFORMULATION; //定义直线一般式ax+by+c=0的系数

typedef struct tagCircleFormulation{
	double x;
	double y;
	double r;
}CircleFormulation, CIRCLEFORMULATION;//定义圆的信息，圆心坐标及半径

typedef struct _FORCASTBALL
{
	LINEFORMULATION Formu;//轨迹
	double angle;//角度
	double velocity;//速度
	Point proBall;//位置
} FORCASTBALL;
typedef struct _AccessParameter{
	Point obstPt;
	Point targetPt;
	int   x;
	int   y;
	int  boundNo;
	RobotPose  charRobot;	
}AccessParameter;
typedef struct _DecisionParamter
{
	int					numPara;	
	int					StartSW;
	int                 CharNo;
	int                 RobotNo;
	char				Command[3][3];//setCommand����д�����͵�����
	bool				nReset;//�Ƿ��λ,FALSE
	BallPoint	ball;
	BallPoint		oldball;
	BallPoint		oldBallPt[7];
	RobotPose			Robot[7];
	FORCASTBALL			pBall;
}DecisionParamter;

double max(double a,double b);
double min(double a,double b);
int StdLineForm(Point P1, Point P2, LINEFORMULATION& line); //标准直线方程
int StdLineForm(Point P1, Point P2, LINEFORMULATION *FormuParam);//直线方程（重载）
int StdLineForm(Point point, double angle, LINEFORMULATION *Result);//直线方程（重载）
int StdLineForm(BallPoint point, double angle, LINEFORMULATION *Result);//直线方程（重载）
int StdLineForm(Point P1, BallPoint P2, LINEFORMULATION *FormuParam);
double cn_LineAngle(Point A, Point B);
double cal_2BallPointsDist(BallPoint A, BallPoint B);//计算不同帧球两点间距离
int cn_LineCircleCross(LINEFORMULATION *pLine, CIRCLEFORMULATION *pCircle, Point *Point1, Point *Point2);
int cn_LineCircleCross(Point A, Point B, CIRCLEFORMULATION *pCircle, Point *Point1, Point *Point2);
double cal_LineAngle(Point A, Point B);
double cn_PointLineDist(BallPoint Point, LINEFORMULATION *Line);
double cn_PointLineDist(Point P, Point A, Point B);
double cn_PointLineDist(Point P, Point A, Point B);
double cal_LineAngle(LINEFORMULATION *pLine);
double cn_LineAngle(Point A, BallPoint B);
double cal_AngleTrimPI(double theta);
double cal_AngleTrim2PI(double theta);
double Getpt2ptAngle(Point pt1, Point pt2);
double Getpt2ptAngle(BallPoint pt1, Point pt2);
double Getpt2ptAngle(Point pt1, BallPoint pt2);
double cal_2PointsDist(Point A, Point B);
double cal_2PointsDist(BallPoint A, Point B);
double distRobot2Pt(RobotPose robot,Point Point);
double distRobot2Pt(RobotPose robot,BallPoint Point);
double distRobot2Pt(RobotPose robot,RobotPose Point);
double distRobot2Pt(OppRobotPoint robot,BallPoint Point);
int cn_2LinesCrossPoint(LINEFORMULATION *Line1, LINEFORMULATION *Line2, Point *Result);
int cn_2LinesCrossPoint(Point A1, Point A2, Point B1, Point B2, Point *Result);

double distRobot2Pt(RobotPose robot,Point point);
void AdaptAngle (RobotPose *pRobotInford,Velocity *pSpeed, int angleFlag);
int TurnToAnglePD(RobotPose *pRobot,double dbAngle,int clock,Velocity *pSpeed);

double cn_AngleTrim2PI(double theta);
double cn_AngleTrimPI(double theta);
int cn_PointPerpendLine(Point Point, LINEFORMULATION *pLine, LINEFORMULATION *pResult, struct Point *pPointC);
int cn_PointPerpendLine(Point Point, struct Point A, struct Point B, LINEFORMULATION *pResult, struct Point *pPointCross);
double cn_LineAngle(LINEFORMULATION *pLine);
int cal_PointPerpendLine(BallPoint Point1, LINEFORMULATION *pLine, LINEFORMULATION *pResult, Point *pPointC);//Point1 是为了防止与结构体Point冲突
int cal_PointPerpendLine(Point Point1, LINEFORMULATION *pLine, LINEFORMULATION *pResult, Point *pPointC);
int cal_2LinesCrossPoint(LINEFORMULATION *Line1, LINEFORMULATION *Line2, Point *Result);
int cal_2LinesCrossPoint(Point A1, Point A2, Point B1, Point B2, Point *Result);


int predictBall_14_(const BallPoint *oldBallPtv,FORCASTBALL *pBall); //球预测函数

//extern FORCASTBALL         ballCharacter;
