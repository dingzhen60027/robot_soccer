#include "Geometry.h"
AngleParameter m_AngleParameter;
MoveParameter m_MoveParameter;
double max(double a,double b)
{
	if (a>=b)
	{
		return a;
	}
	else
	{
		return b;
	}
	
}
double min(double a,double b)
{
	if (a<=b)
	{
		return a;
	}
	else
	{
		return b;
	}
	
}
int StdLineForm(Point P1, Point P2, LINEFORMULATION& line)
{//---------aX + bY + c = 0, b = x1-x2,a=y2-y1,c=x2*y1-x1*y2
	line.a = P2.y - P1.y;
	line.b = P1.x - P2.x;
	line.c = P2.x*P1.y - P1.x*P2.y;
	return 0;
}

int StdLineForm(Point P1, Point P2, LINEFORMULATION *FormuParam)
{//---------aX + bY + c = 0, b = x1-x2,a=y2-y1,c=x2*y1-x1*y2
	FormuParam->a = double(P2.y) - double(P1.y);
	FormuParam->b = double(P1.x) - double(P2.x);
	FormuParam->c = double(P2.x)*double(P1.y) - double(P1.x)*double(P2.y);
	return 0;
}

int StdLineForm(Point P1, BallPoint P2, LINEFORMULATION *FormuParam)
{//---------aX + bY + c = 0, b = x1-x2,a=y2-y1,c=x2*y1-x1*y2
	FormuParam->a = double(P2.y) - double(P1.y);
	FormuParam->b = double(P1.x) - double(P2.x);
	FormuParam->c = double(P2.x)*double(P1.y) - double(P1.x)*double(P2.y);
	return 0;
}

int StdLineForm(Point point, double angle, LINEFORMULATION *Result)
{
	double cn_pi = acos(-1.0);
	if((angle - cn_pi/2) == 0)
	{
		Result->a = 1;
		Result->b = 0;
		Result->c = -point.x;
	}
	else
	{
		Result->a = -tan(angle);
		Result->b = 1;
		Result->c = tan(angle)*point.x - point.y;
	}
	return 1;
}

int StdLineForm(BallPoint point, double angle, LINEFORMULATION *Result)
{
	double cn_pi = acos(-1.0);
	if((angle - cn_pi/2) == 0)
	{
		Result->a = 1;
		Result->b = 0;
		Result->c = -point.x;
	}
	else
	{
		Result->a = -tan(angle);
		Result->b = 1;
		Result->c = tan(angle)*point.x - point.y;
	}
	return 1;
}

double cal_2BallPointsDist(BallPoint A, BallPoint B)
{
	return sqrt((B.y-A.y)*(B.y-A.y) + (B.x-A.x)*(B.x-A.x));
}

double cal_LineAngle(Point A, Point B)
{// Calculate the angle of line AB and the x-axis, the result is between 0-2*Pi
// and the line's direction is from A to B.
	double cn_pi = acos(-1.0);
	double angle=atan2(B.y-A.y, B.x-A.x);
	if(angle<0)
		angle += 2*cn_pi;
	return angle;
}

double cal_LineAngle(LINEFORMULATION *pLine)
{
	double theta = atan2(pLine->a, -pLine->b);
	return cal_AngleTrimPI(theta);
}

double cal_AngleTrimPI(double theta)
{//trim theta to the angle between 0 and Pi
	double cn_pi = acos(-1);
	theta = cal_AngleTrim2PI(theta);
	if(theta>cn_pi)
		theta -= cn_pi;
	return theta;
}

double cal_AngleTrim2PI(double theta)
{////trim theta to between 0 and 2pi
	double cn_pi = acos(-1);
	if(theta<-100000000000 || theta >1000000)
		theta = 0;
	while(theta>=2*cn_pi)
		theta -= 2*Pi;
	while(theta<0)
		theta += 2*Pi;
	return theta;
}

int cal_2LinesCrossPoint(LINEFORMULATION *Line1, LINEFORMULATION *Line2, Point *Result)
{//get Line1 and Line2's cross point, return -1 if no cross point, otherwise return 1.
	double dt = Line1->a*Line2->b - Line2->a*Line1->b;
	if( dt == 0)
		return -1;
	if(Result!=NULL)
	{
		Result->x = (Line1->b*Line2->c - Line2->b*Line1->c)/dt;
		Result->y = (Line1->c*Line2->a - Line2->c*Line1->a)/dt;
	}
	return 1;
}

int cal_2LinesCrossPoint(Point A1, Point A2, Point B1, Point B2, Point *Result)
{
	LINEFORMULATION lineA, lineB;
	StdLineForm(A1, A2, lineA);
	StdLineForm(B1, B2, lineB);
	return cal_2LinesCrossPoint(&lineA, &lineB, Result);
}

int cal_PointPerpendLine(Point Point1, LINEFORMULATION *pLine, LINEFORMULATION *pResult, Point *pPointC)
{
	double angle = cal_LineAngle(pLine);
	angle += Pi/2;
	StdLineForm(Point1, angle, pResult);
	cal_2LinesCrossPoint(pLine, pResult, pPointC);
	return 1;
}

int cal_PointPerpendLine(BallPoint Point1, LINEFORMULATION *pLine, LINEFORMULATION *pResult, Point *pPointC)
{
	double angle = cal_LineAngle(pLine);
	angle += Pi/2;
	StdLineForm(Point1, angle, pResult);
	cal_2LinesCrossPoint(pLine, pResult, pPointC);
	return 1;
}

int predictBall_14_(const BallPoint *oldBallPtv,FORCASTBALL *pBall)
{
	double	aver_x = 0,  aver_y = 0;
	double  aver_xy = 0, aver_xx = 0, aver_yy = 0;
    Point point1,point2;
	LINEFORMULATION formu1,formu2;
	
	for(int i=0; i<14; i++)
	{
		aver_x	+= oldBallPtv[i].x;
		aver_y	+= oldBallPtv[i].y;
		aver_xy += oldBallPtv[i].x * oldBallPtv[i].y;
		aver_xx += oldBallPtv[i].x * oldBallPtv[i].x;
		aver_yy += oldBallPtv[i].y * oldBallPtv[i].y;
	}
    
	aver_x = aver_x / 14;    aver_y = aver_y / 14;
	aver_xy = aver_xy / 14;	aver_xx = aver_xx / 14;   aver_yy = aver_yy / 14;
	
	double tempx, tempy;
	tempx = aver_xx - aver_x * aver_x;
	tempy = aver_yy - aver_y * aver_y;

	
								/*   
									 pBall->velocity = (double(82.0)/double(51.0))*(cn_2PointsDist(oldBallPtv[4],oldBallPtv[6])+
									 cn_2PointsDist(oldBallPtv[3],oldBallPtv[5])+
									 cn_2PointsDist(oldBallPtv[2],oldBallPtv[4])+
									 cn_2PointsDist(oldBallPtv[1],oldBallPtv[3])+
									 cn_2PointsDist(oldBallPtv[5],oldBallPtv[7])+
									 cn_2PointsDist(oldBallPtv[7],oldBallPtv[9])+
									 cn_2PointsDist(oldBallPtv[9],oldBallPtv[11])+
									 cn_2PointsDist(oldBallPtv[11],oldBallPtv[13])+
									 cn_2PointsDist(oldBallPtv[6],oldBallPtv[8])+
									 cn_2PointsDist(oldBallPtv[8],oldBallPtv[10])+
									 cn_2PointsDist(oldBallPtv[10],oldBallPtv[12]))/22;   
								*/
	
	pBall->velocity = (cal_2BallPointsDist(oldBallPtv[4],oldBallPtv[6])+
					   cal_2BallPointsDist(oldBallPtv[3],oldBallPtv[5])+
					   cal_2BallPointsDist(oldBallPtv[2],oldBallPtv[4])+
				   	   cal_2BallPointsDist(oldBallPtv[1],oldBallPtv[3])+
					   cal_2BallPointsDist(oldBallPtv[5],oldBallPtv[7])+
					   cal_2BallPointsDist(oldBallPtv[7],oldBallPtv[9])+
					   cal_2BallPointsDist(oldBallPtv[9],oldBallPtv[11])+
					   cal_2BallPointsDist(oldBallPtv[11],oldBallPtv[13])+
					   cal_2BallPointsDist(oldBallPtv[6],oldBallPtv[8])+
					   cal_2BallPointsDist(oldBallPtv[8],oldBallPtv[10])+
					   cal_2BallPointsDist(oldBallPtv[10],oldBallPtv[12]))/22;
	
	
	//vv=pBall->velocity;
	if(tempx == 0 && tempy == 0) 
	{
		pBall->Formu.a = 0.0;
		pBall->Formu.b = 0.0;
		pBall->Formu.c = 0.0;
		return 1;
	}
	else if (tempx == 0 && tempy != 0)
	{
		pBall->Formu.a = -1;
		pBall->Formu.b = 0;
		pBall->Formu.c = oldBallPtv[13].x;
	}
	else    
	{
		pBall->Formu.b = -1;
		pBall->Formu.a = (aver_xy - aver_x * aver_y) / tempx;//���Իع�ϵ��b
		pBall->Formu.c = aver_y - pBall->Formu.a * aver_x;   //���Իع�ϵ��a
	}

	cal_PointPerpendLine(oldBallPtv[13], &(pBall->Formu),&formu1,&point1);

	cal_PointPerpendLine(oldBallPtv[0], &(pBall->Formu),&formu2,&point2);
    pBall->angle = cal_LineAngle(point2, point1);
	

	double dx = oldBallPtv[13].x - oldBallPtv[0].x;  //oldBallPt[13].x - oldBallPt[0].x
	double dy = oldBallPtv[13].y - oldBallPtv[0].y;  //oldBallPt[13].y - oldBallPt[0].y
	pBall->proBall.x = oldBallPtv[13].x + dx;
	pBall->proBall.y = oldBallPtv[13].y + dy;
	//pBall->proBall = getValLine('x', pBall->proBall.x, &pBall->Formu);
	//pBall->proBall = getValLine('y', pBall->proBall.y, &pBall->Formu);

    return 1;

}


double Getpt2ptAngle(Point pt1, Point pt2)
{
	double angle;
	double	dx,dy;
	dx = pt2.x - pt1.x;
	dy = pt2.y - pt1.y;
	angle = atan2(dy,dx);
	angle = cal_AngleTrim2PI(angle);
	return	angle;
}
double Getpt2ptAngle(Point pt1, BallPoint pt2)
{
	double angle;
	double	dx,dy;
	dx = pt2.x - pt1.x;
	dy = pt2.y - pt1.y;
	angle = atan2(dy,dx);
	angle = cal_AngleTrim2PI(angle);
	return	angle;
}
double Getpt2ptAngle(BallPoint pt1, Point pt2)
{
	double angle;
	double	dx,dy;
	dx = pt2.x - pt1.x;
	dy = pt2.y - pt1.y;
	angle = atan2(dy,dx);
	angle = cal_AngleTrim2PI(angle);
	return	angle;
}
int cn_PointPerpendLine(Point Point, LINEFORMULATION *pLine, LINEFORMULATION *pResult, struct Point *pPointC)
{
	double angle = cn_LineAngle(pLine);
	angle += Pi/2;
	StdLineForm(Point, angle, pResult);//�õ�����pResult
	cn_2LinesCrossPoint(pLine, pResult, pPointC);//�õ�����pPoint
	return 1;
}



int cn_2LinesCrossPoint(LINEFORMULATION *Line1, LINEFORMULATION *Line2, Point *Result)
{//get Line1 and Line2's cross point, return -1 if no cross point, otherwise return 1.
	double dt = Line1->a*Line2->b - Line2->a*Line1->b;
	if( dt == 0)
		return -1;
	if(Result!=NULL)
	{
		Result->x = (Line1->b*Line2->c - Line2->b*Line1->c)/dt;
		Result->y = (Line1->c*Line2->a - Line2->c*Line1->a)/dt;
	}
	return 1;
}
int cn_2LinesCrossPoint(Point A1, Point A2, Point B1, Point B2, Point *Result)
{
	LINEFORMULATION lineA, lineB;
	StdLineForm(A1, A2, &lineA);
	StdLineForm(B1, B2, &lineB);
	return cn_2LinesCrossPoint(&lineA, &lineB, Result);
}
int cn_PointPerpendLine(Point Point, struct Point A, struct Point B, LINEFORMULATION *pResult, struct Point *pPointCross)
{
	LINEFORMULATION line;
	StdLineForm(A, B, &line);
	return cn_PointPerpendLine(Point, &line, pResult, pPointCross);
}
double cn_AngleTrimPI(double theta)
{//trim theta to the angle between 0 and Pi
	double cn_pi = acos(-1);
	theta = cn_AngleTrim2PI(theta);
	if(theta>cn_pi)
		theta -= cn_pi;
	return theta;
}
double cn_AngleTrim2PI(double theta)
	{////trim theta to between 0 and 2pi
	double cn_pi = acos(-1);
	if(theta<-100000000000 || theta >1000000)
		theta = 0;
	while(theta>=2*cn_pi)
		theta -= 2*Pi;
	while(theta<0)
		theta += 2*Pi;
	return theta;}
double cn_LineAngle(LINEFORMULATION *pLine)
{
	double theta = atan2(pLine->a, -pLine->b);
	return cn_AngleTrimPI(theta);
}
double cn_LineAngle(Point A, Point B)
{// Calculate the angle of line AB and the x-axis, the result is between 0-2*Pi
// and the line's direction is from A to B.
	double cn_pi = acos(-1.0);
	double angle=atan2(B.y-A.y, B.x-A.x);
	if(angle<0)
		angle += 2*cn_pi;
	return angle;
}
double cn_LineAngle(Point A, BallPoint B)
{// Calculate the angle of line AB and the x-axis, the result is between 0-2*Pi
// and the line's direction is from A to B.
	double cn_pi = acos(-1.0);
	double angle=atan2(B.y-A.y, B.x-A.x);
	if(angle<0)
		angle += 2*cn_pi;
	return angle;
}
double cal_2PointsDist(Point A, Point B)
{
	return sqrt((B.y-A.y)*(B.y-A.y) + (B.x-A.x)*(B.x-A.x));
}
double cal_2PointsDist(BallPoint A, Point B)
{
	return sqrt((B.y-A.y)*(B.y-A.y) + (B.x-A.x)*(B.x-A.x));
}

	double distRobot2Pt(RobotPose robot,Point Point)//车到点的距离
    {
	    return sqrt((robot.x-Point.x)*(robot.x-Point.x) + (robot.y-Point.y)*(robot.y-Point.y));
    }

	double distRobot2Pt(RobotPose robot,BallPoint Point)//车到点的距离
    {
	    return sqrt((robot.x-Point.x)*(robot.x-Point.x) + (robot.y-Point.y)*(robot.y-Point.y));
    }
	double distRobot2Pt(OppRobotPoint robot,BallPoint Point)//车到点的距离
    {
	    return sqrt((robot.x-Point.x)*(robot.x-Point.x) + (robot.y-Point.y)*(robot.y-Point.y));
    }

double cn_PointLineDist(Point P, Point A, Point B)
{//calculate the distance of point P and line AB
	double distance;
	if((A.x==B.x) && (A.y==B.y))//A,BΪͬһ��,�����������
		return sqrt((double(P.y)-double(A.y))*(double(P.y)-double(A.y)) + (double(P.x)-double(A.x))*(double(P.x)-double(A.x)));
	LINEFORMULATION lineformu;
	StdLineForm(A, B, &lineformu);
	distance = (lineformu.a*P.x + lineformu.b*P.y + lineformu.c)/
				sqrt(lineformu.a*lineformu.a + lineformu.b*lineformu.b);
	return distance;
}

double cn_PointLineDist(BallPoint Point, LINEFORMULATION *Line)
{
	return (Line->a * Point.x + Line->b * Point.y + Line->c)/
			sqrt(Line->a*Line->a + Line->b*Line->b);
}



int cn_LineCircleCross(LINEFORMULATION *pLine, CIRCLEFORMULATION *pCircle, Point *Point1, Point *Point2)//��ֱ�ߺ�Բ�Ľ��㣬���û���򷵻�-1��ֻ��һ���򷵻�0���������򷵻�1��*Point1, *Point2�����������ӦҪ���صĽ���
{//get line and circle's cross points, return -1 if no cross, 0 if there is one cross
//point, return 1 otherwise.
	double delta;
	delta = (pow(pLine->a,2) + pow(pLine->b,2))*pow(pCircle->r,2) - 
		pow(pLine->a*pCircle->x + pLine->b*pCircle->y + pLine->c, 2);
	if(delta<0)
		return -1;//no cross point
	delta = sqrt(delta);
	Point1->x = ((pow(pLine->b,2)*pCircle->x - pLine->a*pLine->b*pCircle->y - 
		pLine->a*pLine->c) + pLine->b*delta)/(pow(pLine->a,2) + pow(pLine->b,2));
	Point1->y = ((pow(pLine->a,2)*pCircle->y - pLine->a*pLine->b*pCircle->x - 
		pLine->b*pLine->c) - pLine->a*delta)/(pow(pLine->a,2) + pow(pLine->b,2));
	Point2->x = ((pow(pLine->b,2)*pCircle->x - pLine->a*pLine->b*pCircle->y - 
		pLine->a*pLine->c) - pLine->b*delta)/(pow(pLine->a,2) + pow(pLine->b,2));
	Point2->y = ((pow(pLine->a,2)*pCircle->y - pLine->a*pLine->b*pCircle->x - 
		pLine->b*pLine->c) + pLine->a*delta)/(pow(pLine->a,2) + pow(pLine->b,2));
	if(delta==0)
		return 0;
	return 1;
}

int cn_LineCircleCross(Point A, Point B, CIRCLEFORMULATION *pCircle, Point *Point1, Point *Point2)
{
	LINEFORMULATION line;
	StdLineForm(A, B, &line);
	return cn_LineCircleCross(&line, pCircle, Point1, Point2);
}

int TurnToAnglePD(RobotPose *pRobot,double dbAngle,int clock,Velocity *pSpeed)
{
	double Difference,SameSpeed;
	int Quadrant = 0;
	Difference=pRobot->theta-dbAngle;
    Difference = cn_AngleTrim2PI(Difference);
	if (Difference <= m_AngleParameter.AngleError)//�ж��Ƿ��ڽǶ������֮��
	{
		pSpeed->LeftValue=0.;
		pSpeed->RightValue=0.;
		return 1;
	}
	if (clock==ANTICLOCK)
		Difference=2*Pi-Difference;
	else if (clock == NOCLOCK)
	{
		if (Difference >= 0 &&  Difference < Pi/2)//�жϽǶȲ���������
			Quadrant=1;
		else if (Difference >= Pi/2 &&  Difference < Pi)
		{
			Quadrant=2;
			Difference=Pi-Difference;
		}
		else if (Difference >= Pi && Difference < 3*Pi/2) 
		{
			Quadrant=3;
			Difference=Difference-Pi;
		}
		else
		{
			Quadrant=4;
			Difference=2*Pi-Difference;
		}
	}
	//�˴�����PD����
	if(clock==0)
		m_AngleParameter.Kp = 18.5;
    SameSpeed=m_AngleParameter.Kp*Difference/*+m_AngleParameter.Kd*(Difference-m_Front)*/;
	if (SameSpeed>m_AngleParameter.MaxAngleSpeed)
		SameSpeed=m_AngleParameter.MaxAngleSpeed;
	//m_Front=Difference;
	if (clock==CLOCKWISE)
	{
		pSpeed->LeftValue=SameSpeed;
		pSpeed->RightValue=-SameSpeed;
	}
	else if (clock == ANTICLOCK)
	{
		pSpeed->LeftValue=-SameSpeed;
		pSpeed->RightValue=SameSpeed;
	}
	else 
	{
		switch(Quadrant)
		{
		case 1://˳ʱ����ת 
		case 3:
			{
				pSpeed->LeftValue=SameSpeed;
				pSpeed->RightValue=-SameSpeed;
				break;                     
			}
		case 2://��ʱ����ת
		case 4:
			{
				pSpeed->LeftValue=-SameSpeed;
				pSpeed->RightValue=SameSpeed;
				break;
			}
		}
	}	
	return 1;
}
void AdaptAngle (RobotPose *pRobotInford,
								   Velocity *pSpeed,
								   int angleFlag)
{
	
	pRobotInford->theta =cn_AngleTrim2PI(pRobotInford->theta );
	
	if(angleFlag==0)
	{
	       if(pRobotInford->theta <Pi)
			   TurnToAnglePD(pRobotInford,Pi/2,NOCLOCK,pSpeed);
		   else
			   TurnToAnglePD(pRobotInford,3*Pi/2,NOCLOCK,pSpeed);
	}
	else
	{
		if(pRobotInford->theta <3*Pi/2 && pRobotInford->theta >Pi/2)
			TurnToAnglePD(pRobotInford,Pi,NOCLOCK,pSpeed);
		else 
			TurnToAnglePD(pRobotInford,0,NOCLOCK,pSpeed);
	}	
	return;
}

