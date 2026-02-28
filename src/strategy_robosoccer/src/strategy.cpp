#include "rclcpp/rclcpp.hpp"
#include "message_interface_robosoccer/msg/pose_robots.hpp"
#include "message_interface_robosoccer/msg/velocity_robots.hpp"
#include "message_interface_robosoccer/msg/decision_var.hpp"

#include <cmath>
#include <memory>
#include <algorithm>  // 包含算法库
using namespace std;

#include "strategy.h"
#include "Geometry.h"
#include "defines.h"
#define TO_BALL(pt)   (BallPoint{ (pt).x, (pt).y })
#define TO_POINT(bpt) (Point{ (bpt).x, (bpt).y })

class Strategy : public rclcpp::Node
{
public:
    Strategy(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s已创建!", name.c_str());
        
        
		isAttack = true;
        isRightArea = false;
        StartMode = NormalStart;
        isBackInitPose = true;
        isReInit = true;
        isStartGame = false;
		RingFlag = true;
        
        distError = 4.0; //2.0
        m_Front = 0.0;
		ban_counter = 0, ban_counter2 = 0, ban_counter3 = 0;
		ban_warning_flag = 100;
		ban_warning_flag2 = 100;
		changeCharacter = 0;
		EndProcessFlag = 0;
		charrobot=0;
		endprocessV = 0;
		End_vxishu = 1.1;
		qiusubi = 42.0; 
		endprocessrobot.x = 0;endprocessrobot.y = 0;
		anglexishuA=0.000871;//0.0017;
		anglexishuC=0.75;//0.6465;0.772
		timelimit = 48;
        shootsign3=0;
        m_AngleParameter.Kp = 4; // 18  超调 改这个
	    m_AngleParameter.Kd = 13.0;  //2
	    m_AngleParameter.AngleError = 8.0 / 180.0 * Pi; //5.0    8.0
	    m_AngleParameter.MaxAngleSpeed = 80.0 / 2.0; 
	    m_AngleParameter.MaxAngle = 75.0 * Pi / 180.0;
	    moca = 0.0025;
		v_xishu=1.2;
		yanchi=0;
		vx=385;

		zhichong[1]=0;
		zhichong[2]=0;
		zhichong[3]=0.042082;
		zhichong[4]=0.042082;
		zhichong[5]=0.084163;
		zhichong[6]=0.084163;
		zhichong[7]=0.269753;
		zhichong[8]=0.497298;
		zhichong[9]=0.912934;
		zhichong[10]=1.249995;
		zhichong[11]=1.710257;
		zhichong[12]=2.259753;
		zhichong[13]=2.813427;
		zhichong[14]=3.478908;
		zhichong[15]=4.028876;
		zhichong[16]=4.791662;
		zhichong[17]=5.554403;
		zhichong[18]=6.220986;
		zhichong[19]=6.976735;
		zhichong[20]=7.806225;
		zhichong[21]=8.699473;
		zhichong[22]=9.544229;
		zhichong[23]=10.70727;
		zhichong[24]=11.78994;
		zhichong[25]=12.96350;
		zhichong[26]=14.21360;
		zhichong[27]=15.51326;
		zhichong[28]=16.97170;
		zhichong[29]=18.42579;
		zhichong[30]=19.92817;
		zhichong[31]=21.64443;
		zhichong[32]=23.31292;
		zhichong[33]=25.02341;
		zhichong[34]=26.90341;
		zhichong[35]=28.78175;
		zhichong[36]=30.74726;
		zhichong[37]=32.67629;
		zhichong[38]=34.98494;
		zhichong[39]=37.36318;
		zhichong[40]=39.50234;
		zhichong[41]=41.81746;
		zhichong[42]=44.25980;
		zhichong[43]=46.61902;
		zhichong[44]=49.07044;
		zhichong[45]=51.52772;
		zhichong[46]=54.36601;
		zhichong[47]=56.66586;
		zhichong[48]=59.35234;
		zhichong[49]=62.21757;
		dizeng=2.865236;
		g_GoalKeeper =0;
		showtarget=0;
    	showtarget1=0;
    	showtarget2=0;
		showtarget2=0;
		g_timeflag =0;
	    m_MoveParameter.V_MAX = 70.0;
        m_MoveParameter.V_max = 70.0;
        m_MoveParameter.max_distance = 40.0;
        m_MoveParameter.kp4pospd = 12;	//12
        m_MoveParameter.kd4pospd =  2;// 0.50;
        m_MoveParameter.max_distanceG = 25.0;
        m_MoveParameter.kp4pospdG =18.5;//18.50;//15.5
        m_MoveParameter.kd4pospdG =0;// 1.90;
		readyflag=1;
		defendflag=0;
		
		charPerformancescore00[0]=14;
		charPerformancescore00[1]=14;
		charPerformancescore00[2]=15;
		charPerformancescore00[3]=16;
		charPerformancescore00[4]=17;
		charPerformancescore00[5]=18;
		charPerformancescore00[6]=19;
		charPerformancescore00[7]=20;
		charPerformancescore00[8]=21;
		charPerformancescore00[9]=22;
		charPerformancescore00[10]=23;
		charPerformancescore00[11]=24;
		charPerformancescore00[12]=25;
		charPerformancescore00[13]=26;
		charPerformancescore00[14]=27;
		charPerformancescore00[15]=28;
		charPerformancescore00[16]=28.6;
		charPerformancescore00[17]=29.2;
		charPerformancescore00[18]=29.8;
		charPerformancescore00[19]=30.4;
		charPerformancescore00[20]=31;
		charPerformancescore00[21]=31.6;
		charPerformancescore00[22]=32.2;
		charPerformancescore00[23]=32.8;
		charPerformancescore00[24]=33.4;
		charPerformancescore00[25]=34;
		charPerformancescore00[26]=35;
		charPerformancescore00[27]=36;
		charPerformancescore00[28]=37;
		charPerformancescore00[29]=38;
		charPerformancescore00[30]=39;
		charPerformancescore00[31]=40;
		charPerformancescore00[32]=41;
		charPerformancescore00[33]=42;
		charPerformancescore00[34]=43;
		charPerformancescore00[35]=43;
		charPerformancescore00[36]=43.8;
		charPerformancescore00[37]=44.6;
		charPerformancescore00[38]=45.4;
		charPerformancescore00[39]=46.2;
		charPerformancescore00[40]=47;
		charPerformancescore00[41]=47.8;
		charPerformancescore00[42]=48.6;
		charPerformancescore00[43]=49.4;
		charPerformancescore00[44]=50.2;
		charPerformancescore00[45]=51;
		charPerformancescore00[46]=51.5;
		charPerformancescore00[47]=52;
		charPerformancescore00[48]=52.5;
		charPerformancescore00[49]=53;
		charPerformancescore00[50]=53.5;
		charPerformancescore00[51]=54;
		charPerformancescore00[52]=54.5;
		charPerformancescore00[53]=55;
		charPerformancescore00[54]=55.5;
		charPerformancescore00[55]=56;
		charPerformancescore00[56]=56.8;
		charPerformancescore00[57]=57.6;
		charPerformancescore00[58]=58.4;
		charPerformancescore00[59]=59.2;
		charPerformancescore00[60]=60;
		charPerformancescore00[61]=60.8;
		charPerformancescore00[62]=61.6;
		charPerformancescore00[63]=62.4;
		charPerformancescore00[64]=63.2;
		charPerformancescore00[65]=64;
		charPerformancescore00[66]=64.5;
		charPerformancescore00[67]=65;
		charPerformancescore00[68]=65.5;
		charPerformancescore00[69]=66;
		charPerformancescore00[70]=66.6;
		charPerformancescore00[71]=67;
		charPerformancescore00[72]=67.5;
		charPerformancescore00[73]=68;
		charPerformancescore00[74]=68.5;
		charPerformancescore00[75]=69;
		charPerformancescore00[76]=69.5;
		charPerformancescore00[77]=70;
		charPerformancescore00[78]=70.5;
		charPerformancescore00[79]=71;
		charPerformancescore00[80]=71.5;
		charPerformancescore00[81]=72;
		charPerformancescore00[82]=72.5;
		charPerformancescore00[83]=73;
		charPerformancescore00[84]=73.5;
		charPerformancescore00[85]=74;
		pfmj=75;
		for(pfmi=86;pfmi<=284;pfmi++)//285
		{
			charPerformancescore00[pfmi]=pfmj;
			pfmj++;
		}
		//0/10
		charPerformancescore010[0]=14;
		charPerformancescore010[1]=15;
		charPerformancescore010[2]=16;
		charPerformancescore010[3]=17;
		charPerformancescore010[4]=18;
		charPerformancescore010[5]=19;
		charPerformancescore010[6]=20;
		charPerformancescore010[7]=21;
		charPerformancescore010[8]=22;
		charPerformancescore010[9]=23;
		charPerformancescore010[10]=24;
		charPerformancescore010[11]=25;
		charPerformancescore010[12]=26;
		charPerformancescore010[13]=27;
		charPerformancescore010[14]=28;
		charPerformancescore010[15]=28;
		charPerformancescore010[16]=28.9;
		charPerformancescore010[17]=29.8;
		charPerformancescore010[18]=30.7;
		charPerformancescore010[19]=31.6;
		charPerformancescore010[20]=32.5;
		charPerformancescore010[21]=33.4;
		charPerformancescore010[22]=34.3;
		charPerformancescore010[23]=35.2;
		charPerformancescore010[24]=36.1;
		charPerformancescore010[25]=37;
		charPerformancescore010[26]=37.8;
		charPerformancescore010[27]=38.6;
		charPerformancescore010[28]=39.4;
		charPerformancescore010[29]=40.2;
		charPerformancescore010[30]=41;
		charPerformancescore010[31]=41.8;
		charPerformancescore010[32]=42.6;
		charPerformancescore010[33]=43.4;
		charPerformancescore010[34]=44.2;
		charPerformancescore010[35]=45;
		charPerformancescore010[36]=45.9;
		charPerformancescore010[37]=46.8;
		charPerformancescore010[38]=47.7;
		charPerformancescore010[39]=48.6;
		charPerformancescore010[40]=49.5;
		charPerformancescore010[41]=50.4;
		charPerformancescore010[42]=51.3;
		charPerformancescore010[43]=52.2;
		charPerformancescore010[44]=53.1;
		charPerformancescore010[45]=54;
		charPerformancescore010[46]=54.4;
		charPerformancescore010[47]=54.8;
		charPerformancescore010[48]=55.2;
		charPerformancescore010[49]=55.6;
		charPerformancescore010[50]=56;
		charPerformancescore010[51]=56.4;
		charPerformancescore010[52]=56.8;
		charPerformancescore010[53]=57.2;
		charPerformancescore010[54]=57.6;
		charPerformancescore010[55]=58;
		charPerformancescore010[56]=58.9;
		charPerformancescore010[57]=59.8;
		charPerformancescore010[58]=60.7;
		charPerformancescore010[59]=61.6;
		charPerformancescore010[60]=62.5;
		charPerformancescore010[61]=63.4;
		charPerformancescore010[62]=64.3;
		charPerformancescore010[63]=65.2;
		charPerformancescore010[64]=66.1;
		charPerformancescore010[65]=67;
		charPerformancescore010[66]=67.5;
		charPerformancescore010[67]=68;
		charPerformancescore010[68]=68.5;
		charPerformancescore010[69]=69;
		charPerformancescore010[70]=69.5;
		charPerformancescore010[71]=70;
		charPerformancescore010[72]=70.5;
		charPerformancescore010[73]=71;
		charPerformancescore010[74]=71.5;
		charPerformancescore010[75]=72;
		charPerformancescore010[76]=72.5;
		charPerformancescore010[77]=73;
		charPerformancescore010[78]=73.5;
		charPerformancescore010[79]=74;
		charPerformancescore010[80]=74.5;
		charPerformancescore010[81]=75;
		charPerformancescore010[82]=75.5;
		charPerformancescore010[83]=76;
		charPerformancescore010[84]=76.5;
		charPerformancescore010[85]=77;
		pfmj=78;
		for(pfmi=86;pfmi<=284;pfmi++)//285
		{
			charPerformancescore010[pfmi]=pfmj;
			pfmj++;
		}
		//0/20
		pfmj=24;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=39;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=53;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=46;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=58;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=67;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=72;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=76;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=84;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore020[pfmi]=pfmj;
			pfmj++;
		}
		//0/30
		pfmj=26;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=41;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=54;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=60;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=64;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=77;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=80;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=83;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=94;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore030[pfmi]=pfmj;
			pfmj++;
		}
		//0/40
		pfmj=27;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=42;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=56;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=72;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj=pfmj+5.1;
		}
		pfmj=123;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=130;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj=pfmj-4.7;
		}
		pfmj=83;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=91;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=97;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore040[pfmi]=pfmj;
			pfmj++;
		}
		//0/50
		pfmj=29;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=44;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=62;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=74;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj=pfmj+6;
		}
		pfmj=134;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=140;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj=pfmj-4.9;
		}
		pfmj=91;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=102;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=104;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore050[pfmi]=pfmj;
			pfmj++;
		}
		//0/60
		pfmj=30;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=45;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=63;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=75;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj=pfmj+6.8;
		}
		pfmj=143;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=150;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj=pfmj-5.2;
		}
		pfmj=98;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=104;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=110;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore060[pfmi]=pfmj;
			pfmj++;
		}
		//0/70
		pfmj=31;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=46;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=64;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=78;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj=pfmj+7.4;
		}
		pfmj=152;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=160;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj=pfmj-5.6;
		}
		pfmj=104;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=109;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=114;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore070[pfmi]=pfmj;
			pfmj++;
		}
		//0/80
		pfmj=32;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=47;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=65;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=82;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj=pfmj+7.9;
		}
		pfmj=161;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=170;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj=pfmj-3.5;
		}
		pfmj=135;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=145;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=156;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore080[pfmi]=pfmj;
			pfmj++;
		}
		//0/90
		pfmj=34;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=49;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=68;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=88;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj=pfmj+8.3;
		}
		pfmj=171;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=180;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj=pfmj-3.8;
		}
		pfmj=142;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=153;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=164;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore090[pfmi]=pfmj;
			pfmj++;
		}
		//10/0
		pfmj=13;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=28;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=35;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=43;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=53;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=58;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=65;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=67;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=74;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore100[pfmi]=pfmj;
			pfmj++;
		}
		//10/10
		pfmj=13;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=28;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=35;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=45;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=55;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=60;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=65;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=71;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=79;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1010[pfmi]=pfmj;
			pfmj++;
		}
		//10/20
		pfmj=21;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=36;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=47;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=49;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=59;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=60;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=76;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=81;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=92;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1020[pfmi]=pfmj;
			pfmj++;
		}
		//10/30
		pfmj=26;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=41;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=50;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=53;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=65;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=70;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=78;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=86;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=97;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1030[pfmi]=pfmj;
			pfmj++;
		}
		//10/40
		pfmj=29;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=44;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=58;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=68;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=73;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=85;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=88;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=89;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=102;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1040[pfmi]=pfmj;
			pfmj++;
		}
		//10/50
		pfmj=31;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=46;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=62;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=78;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj=pfmj+4.8;
		}
		pfmj=126;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=132;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj=pfmj-4;
		}
		pfmj=92;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=96;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=105;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1050[pfmi]=pfmj;
			pfmj++;
		}
		//10/60
		pfmj=34;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=49;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=65;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=80;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj=pfmj+5.8;
		}
		pfmj=138;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=143;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj=pfmj-4.5;
		}
		pfmj=98;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=106;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=109;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1060[pfmi]=pfmj;
			pfmj++;
		}
		//10/70
		pfmj=36;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=51;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=65;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=82;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj=pfmj+6.7;
		}
		pfmj=149;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=155;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj=pfmj-3.9;
		}
		pfmj=116;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=111;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=114;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1070[pfmi]=pfmj;
			pfmj++;
		}
		//10/80
		pfmj=38;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=53;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=66;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=85;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj=pfmj+7.5;
		}
		pfmj=160;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=166;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj=pfmj-4;
		}
		pfmj=126;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj=pfmj-1.2;
		}
		pfmj=114;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=117;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1080[pfmi]=pfmj;
			pfmj++;
		}
		//10/90
		pfmj=40;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=55;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=69;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=90;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj=pfmj+8;
		}
		pfmj=170;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=180;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj=pfmj-4.6;
		}
		pfmj=134;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj=pfmj-1.4;
		}
		pfmj=120;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=124;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1090[pfmi]=pfmj;
			pfmj++;
		}
		//20/0
		pfmj=14;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=29;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=35;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=44;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=54;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=58;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=63;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=74;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=83;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore200[pfmi]=pfmj;
			pfmj++;
		}
		//20/10
		pfmj=15;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=30;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=35;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=45;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=55;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=59;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=64;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=76;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=85;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2010[pfmi]=pfmj;
			pfmj++;
		}
		//20/20
		pfmj=19;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=34;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=39;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=48;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=58;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=62;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=69;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=77;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=88;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2020[pfmi]=pfmj;
			pfmj++;
		}
		//20/30
		pfmj=33;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=48;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=55;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=51;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=61;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=65;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=78;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=85;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=94;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2030[pfmi]=pfmj;
			pfmj++;
		}
		//20/40
		pfmj=35;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=50;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=59;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=56;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=70;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=73;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=81;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=86;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=97;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2040[pfmi]=pfmj;
			pfmj++;
		}
		//20/50
		pfmj=37;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=52;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=60;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=78;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=83;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=87;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=88;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=92;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=100;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2050[pfmi]=pfmj;
			pfmj++;
		}
		//20/60
		pfmj=39;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=54;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=66;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=82;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj=pfmj+4.3;
		}
		pfmj=125;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=131;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj=pfmj-3.4;
		}
		pfmj=97;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=97;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=108;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2060[pfmi]=pfmj;
			pfmj++;
		}
		//20/70
		pfmj=42;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=57;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=67;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=85;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj=pfmj+5.5;
		}
		pfmj=140;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=145;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj=pfmj-4;
		}
		pfmj=105;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=103;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=113;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2070[pfmi]=pfmj;
			pfmj++;
		}
		//20/80
		pfmj=45;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=60;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=70;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=88;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj=pfmj+6.3;
		}
		pfmj=151;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=161;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj=pfmj-5.2;
		}
		pfmj=109;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=109;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=119;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2080[pfmi]=pfmj;
			pfmj++;
		}
		//20/90
		pfmj=47;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=62;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=73;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=92;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj=pfmj+7;
		}
		pfmj=162;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=170;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj=pfmj-5.9;
		}
		pfmj=111;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=113;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=123;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore2090[pfmi]=pfmj;
			pfmj++;
		}
		//30/0
		pfmj=40;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=55;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj=pfmj-0.8;
		}
		pfmj=47;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=50;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=58;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=61;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=69;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=77;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=78;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore300[pfmi]=pfmj;
			pfmj++;
		}
		//30/10
		pfmj=40;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=55;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj=pfmj-1.3;
		}
		pfmj=42;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=45;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=52;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=57;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=62;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=70;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=78;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3010[pfmi]=pfmj;
			pfmj++;
		}
		//30/20
		pfmj=36;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=51;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=60;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=58;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=64;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=69;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=76;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=86;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=94;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3020[pfmi]=pfmj;
			pfmj++;
		}
		//30/30
		pfmj=36;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=51;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=65;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=62;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=66;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=72;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=80;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=88;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=97;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3030[pfmi]=pfmj;
			pfmj++;
		}
		//30/40
		pfmj=40;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=55;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=65;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj=pfmj-0.1;
		}
		pfmj=64;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=68;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=74;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=84;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=91;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=100;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3040[pfmi]=pfmj;
			pfmj++;
		}
		//30/50
		pfmj=43;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=58;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=65;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=66;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=73;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=80;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=86;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=95;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=103;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3050[pfmi]=pfmj;
			pfmj++;
		}
		//30/60
		pfmj=43;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=58;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=65;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=77;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=87;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=89;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=92;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=99;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=107;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3060[pfmi]=pfmj;
			pfmj++;
		}
		//30/70
		pfmj=45;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=60;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=73;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=82;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=112;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=130;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj=pfmj-3.4;
		}
		pfmj=96;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=103;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=111;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3070[pfmi]=pfmj;
			pfmj++;
		}
		//30/80
		pfmj=48;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=63;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=77;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=88;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj=pfmj+3.8;
		}
		pfmj=126;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=141;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj=pfmj-3.9;
		}
		pfmj=102;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=105;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=115;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3080[pfmi]=pfmj;
			pfmj++;
		}
		//30/90
		pfmj=50;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=65;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=82;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=95;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj=pfmj+4.8;
		}
		pfmj=143;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=153;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj=pfmj-4.7;
		}
		pfmj=106;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=111;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=121;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore3090[pfmi]=pfmj;
			pfmj++;
		}
		//40/0
		pfmj=50;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=65;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=68;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=74;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=78;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=83;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=92;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=105;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=115;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore400[pfmi]=pfmj;
			pfmj++;
		}
		//40/10
		pfmj=50;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=65;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=67;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=73;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=77;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=80;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=89;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=98;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=108;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4010[pfmi]=pfmj;
			pfmj++;
		}
		//40/20
		pfmj=45;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=60;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=66;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=72;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=73;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=75;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=81;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=87;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=98;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4020[pfmi]=pfmj;
			pfmj++;
		}
		//40/30
		pfmj=42;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=57;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=64;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=68;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=70;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=72;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=78;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=83;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=96;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4030[pfmi]=pfmj;
			pfmj++;
		}
		//40/40
		pfmj=38;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=53;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=67;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=70;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=72;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=76;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=83;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=90;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=103;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4040[pfmi]=pfmj;
			pfmj++;
		}
		//40/50
		pfmj=45;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=60;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=68;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=82;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=77;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=80;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=85;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=94;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=107;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4050[pfmi]=pfmj;
			pfmj++;
		}
		//40/60
		pfmj=48;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=63;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=69;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=85;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=88;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=90;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=98;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=104;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=114;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4060[pfmi]=pfmj;
			pfmj++;
		}
		//40/70
		pfmj=52;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=67;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=71;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=90;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj=pfmj+4.1;
		}
		pfmj=131;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj=pfmj-3.3;
		}
		pfmj=98;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=102;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=109;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=117;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4070[pfmi]=pfmj;
			pfmj++;
		}
		//40/80
		pfmj=56;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=71;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=75;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=94;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj=pfmj+3.3;
		}
		pfmj=127;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj=pfmj-2.3;
		}
		pfmj=104;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=108;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=115;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=123;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4080[pfmi]=pfmj;
			pfmj++;
		}
		//40/90
		pfmj=61;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=76;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=80;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=99;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj=pfmj+3.6;
		}
		pfmj=135;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj=pfmj-2.4;
		}
		pfmj=111;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=114;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=123;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=130;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore4090[pfmi]=pfmj;
			pfmj++;
		}
		//50/0
		pfmj=56;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=71;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=76;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=85;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=98;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=105;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=102;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=107;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=112;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore500[pfmi]=pfmj;
			pfmj++;
		}
		//50/10
		pfmj=53;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=68;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=75;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=83;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=88;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=94;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=96;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=99;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=106;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5010[pfmi]=pfmj;
			pfmj++;
		}
		//50/20
		pfmj=50;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=65;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=74;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=78;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=81;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=85;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=92;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=98;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=105;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5020[pfmi]=pfmj;
			pfmj++;
		}
		//50/30
		pfmj=50;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=65;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=71;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=76;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj=pfmj-0.8;
		}
		pfmj=68;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=76;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=85;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=92;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=96;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5030[pfmi]=pfmj;
			pfmj++;
		}
		//50/40
		pfmj=53;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=68;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=74;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=78;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj=pfmj-0.7;
		}
		pfmj=71;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=78;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=88;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=96;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=104;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5040[pfmi]=pfmj;
			pfmj++;
		}
		//50/50
		pfmj=54;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=69;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=80;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=86;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=109;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj=pfmj-2.9;
		}
		pfmj=80;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=89;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=100;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=110;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5050[pfmi]=pfmj;
			pfmj++;
		}
		//50/60
		pfmj=57;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=72;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=91;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=97;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=117;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj=pfmj-3;
		}
		pfmj=87;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=99;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=108;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=117;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5060[pfmi]=pfmj;
			pfmj++;
		}
		//50/70
		pfmj=60;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=75;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=93;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=101;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=110;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj=pfmj-1.7;
		}
		pfmj=93;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=104;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=113;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=125;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5070[pfmi]=pfmj;
			pfmj++;
		}
		//50/80
		pfmj=64;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=79;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=94;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=105;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=116;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj=pfmj-1.5;
		}
		pfmj=101;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=107;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=117;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=128;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5080[pfmi]=pfmj;
			pfmj++;
		}
		//50/90
		pfmj=68;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=83;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=96;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=111;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=122;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj=pfmj-1.2;
		}
		pfmj=110;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=112;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=123;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=134;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore5090[pfmi]=pfmj;
			pfmj++;
		}
		//60/0
		pfmj=78;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=93;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=89;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=92;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=98;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=100;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=110;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=114;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=125;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore600[pfmi]=pfmj;
			pfmj++;
		}
		//60/10
		pfmj=74;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=89;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=87;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=88;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=92;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=97;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=103;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=105;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=116;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6010[pfmi]=pfmj;
			pfmj++;
		}
		//60/20
		pfmj=70;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=85;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=85;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=85;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=87;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=93;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=98;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=102;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=113;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6020[pfmi]=pfmj;
			pfmj++;
		}
		//60/30
		pfmj=63;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=78;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=85;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=81;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=86;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=92;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=96;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=101;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=111;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6030[pfmi]=pfmj;
			pfmj++;
		}
		//60/40
		pfmj=63;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=78;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=85;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=82;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=88;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=96;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=103;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=108;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=118;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6040[pfmi]=pfmj;
			pfmj++;
		}
		//60/50
		pfmj=63;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=78;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=85;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=83;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=91;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=100;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=109;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=116;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=124;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6050[pfmi]=pfmj;
			pfmj++;
		}
		//60/60
		pfmj=68;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=82;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=91;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj=pfmj-0.8;
		}
		pfmj=83;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=96;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=105;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=117;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=122;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=129;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6060[pfmi]=pfmj;
			pfmj++;
		}
		//60/70
		pfmj=70;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=85;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=105;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=107;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=105;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=111;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=123;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=125;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=133;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6070[pfmi]=pfmj;
			pfmj++;
		}
		//60/80
		pfmj=75;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=90;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=107;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=115;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=110;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=114;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=125;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=128;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=137;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6080[pfmi]=pfmj;
			pfmj++;
		}
		//60/90
		pfmj=79;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=94;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=109;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=123;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=118;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=120;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=128;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=131;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=140;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore6090[pfmi]=pfmj;
			pfmj++;
		}
		//70/0
		pfmj=72;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=87;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=83;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj=pfmj+3.5;
		}
		pfmj=118;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj=pfmj-1;
		}
		pfmj=108;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=122;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=130;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=147;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=164;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore700[pfmi]=pfmj;
			pfmj++;
		}
		//70/10
		pfmj=69;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=84;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=82;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=103;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=107;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=120;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=129;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=146;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=164;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7010[pfmi]=pfmj;
			pfmj++;
		}
		//70/20
		pfmj=65;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=80;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=81;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=103;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=107;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=118;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=129;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=145;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=164;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7020[pfmi]=pfmj;
			pfmj++;
		}
		//70/30
		pfmj=60;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=75;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=88;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=103;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=106;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=117;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=127;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=144;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=164;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7030[pfmi]=pfmj;
			pfmj++;
		}
		//70/40
		pfmj=65;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=80;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=98;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=103;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=105;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=116;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=127;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=143;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=164;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7040[pfmi]=pfmj;
			pfmj++;
		}
		//70/50
		pfmj=65;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=80;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=97;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=93;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=97;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=101;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=111;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=120;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=134;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7050[pfmi]=pfmj;
			pfmj++;
		}
		//70/60
		pfmj=69;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=84;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=97;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=94;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=100;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=106;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=117;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=125;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=139;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7060[pfmi]=pfmj;
			pfmj++;
		}
		//70/70
		pfmj=69;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=84;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=110;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=129;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj=pfmj-2.3;
		}
		pfmj=106;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=114;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=122;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=128;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=141;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7070[pfmi]=pfmj;
			pfmj++;
		}
		//70/80
		pfmj=72;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=87;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=113;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=139;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj=pfmj-2.8;
		}
		pfmj=111;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=119;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=128;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=133;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=143;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7080[pfmi]=pfmj;
			pfmj++;
		}
		//70/90
		pfmj=75;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=90;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj=pfmj+2.5;
		}
		pfmj=115;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj=pfmj+3.4;
		}
		pfmj=149;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj=pfmj-3.1;
		}
		pfmj=118;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=125;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=133;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=138;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=146;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore7090[pfmi]=pfmj;
			pfmj++;
		}
		//80/0
		pfmj=78;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=93;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj=pfmj+4.5;
		}
		pfmj=138;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj=pfmj-2;
		}
		pfmj=118;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=137;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=139;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=151;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=163;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj=pfmj+2.5;
		}
		pfmj=188;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore800[pfmi]=pfmj;
			pfmj++;
		}
		//80/10
		pfmj=78;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=93;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=109;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=130;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=137;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=139;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=151;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=163;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=187;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8010[pfmi]=pfmj;
			pfmj++;
		}
		//80/20
		pfmj=78;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=93;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=109;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=130;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=137;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=137;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=148;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=163;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=186;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8020[pfmi]=pfmj;
			pfmj++;
		}
		//80/30
		pfmj=65;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=80;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj=pfmj+2.9;
		}
		pfmj=109;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=130;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=137;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=135;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=148;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=162;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=185;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8030[pfmi]=pfmj;
			pfmj++;
		}
		//80/40
		pfmj=67;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=82;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=109;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=130;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=136;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=134;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=147;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=161;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=184;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8040[pfmi]=pfmj;
			pfmj++;
		}
		//80/50
		pfmj=73;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=88;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=108;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=123;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj=pfmj-0.7;
		}
		pfmj=116;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=119;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=128;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=139;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=146;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8050[pfmi]=pfmj;
			pfmj++;
		}
		//80/60
		pfmj=74;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=89;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=105;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=112;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=110;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=116;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=121;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=131;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=139;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8060[pfmi]=pfmj;
			pfmj++;
		}
		//80/70
		pfmj=74;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=89;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj=pfmj+2.9;
		}
		pfmj=118;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=123;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=123;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=126;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=124;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=131;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=142;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8070[pfmi]=pfmj;
			pfmj++;
		}
		//80/80
		pfmj=75;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=90;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj=pfmj+3.3;
		}
		pfmj=123;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=131;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=129;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=134;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj=pfmj-0.6;
		}
		pfmj=128;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=135;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=144;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8080[pfmi]=pfmj;
			pfmj++;
		}
		//80/90
		pfmj=78;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=93;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj=pfmj+3.3;
		}
		pfmj=126;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=138;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=136;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=144;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj=pfmj-1.3;
		}
		pfmj=131;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=139;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=148;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore8090[pfmi]=pfmj;
			pfmj++;
		}
		//90/0
		pfmj=105;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=120;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj=pfmj+2.5;
		}
		pfmj=145;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj=pfmj-2.9;
		}
		pfmj=116;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj=pfmj+4.4;
		}
		pfmj=160;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=174;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=178;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=186;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=200;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore900[pfmi]=pfmj;
			pfmj++;
		}
		//90/10
		pfmj=105;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=120;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=115;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=134;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=160;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=172;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=176;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=182;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=199;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9010[pfmi]=pfmj;
			pfmj++;
		}
		//90/20
		pfmj=66;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=81;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj=pfmj+3.4;
		}
		pfmj=115;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=134;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=155;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=166;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=172;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=180;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=198;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9020[pfmi]=pfmj;
			pfmj++;
		}
		//90/30
		pfmj=66;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=81;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj=pfmj+3.4;
		}
		pfmj=115;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=134;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=154;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=163;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=168;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=180;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=197;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9030[pfmi]=pfmj;
			pfmj++;
		}
		//90/40
		pfmj=83;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=98;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=115;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=134;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=153;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=161;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=165;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=178;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=196;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9040[pfmi]=pfmj;
			pfmj++;
		}
		//90/50
		pfmj=81;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=96;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=115;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=130;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=145;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj=pfmj-1.9;
		}
		pfmj=126;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=130;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=140;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=155;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9050[pfmi]=pfmj;
			pfmj++;
		}
		//90/60
		pfmj=79;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=94;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=115;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=125;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=132;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj=pfmj-0.6;
		}
		pfmj=126;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj=pfmj-0.1;
		}
		pfmj=125;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=136;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=151;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9060[pfmi]=pfmj;
			pfmj++;
		}
		//90/70
		pfmj=81;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=96;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=118;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=130;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=133;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj=pfmj-0.6;
		}
		pfmj=127;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=132;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=141;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=156;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9070[pfmi]=pfmj;
			pfmj++;
		}
		//90/80
		pfmj=83;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=98;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=125;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=136;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=134;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj=pfmj-0.6;
		}
		pfmj=128;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=132;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=140;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=157;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9080[pfmi]=pfmj;
			pfmj++;
		}
		//90/90
		pfmj=85;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=100;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj=pfmj+3.1;
		}
		pfmj=131;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=143;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj=pfmj-0.7;
		}
		pfmj=136;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj=pfmj-0.7;
		}
		pfmj=129;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=133;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=141;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=157;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore9090[pfmi]=pfmj;
			pfmj++;
		}
		//100/0
		pfmj=115;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=130;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=157;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj=pfmj-1.5;
		}
		pfmj=142;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=162;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=188;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=202;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=226;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=242;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1000[pfmi]=pfmj;
			pfmj++;
		}
		//100/10
		pfmj=115;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=130;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=126;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=142;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=162;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=186;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=199;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=222;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=239;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10010[pfmi]=pfmj;
			pfmj++;
		}
		//100/20
		pfmj=110;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=125;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=126;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=142;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=160;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=184;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=198;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=218;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=235;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10020[pfmi]=pfmj;
			pfmj++;
		}
		//100/30
		pfmj=87;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=102;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=125;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=142;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=160;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=184;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=198;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=211;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=228;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10030[pfmi]=pfmj;
			pfmj++;
		}
		//100/40
		pfmj=87;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=102;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=142;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=160;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=182;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=192;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=200;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=216;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10040[pfmi]=pfmj;
			pfmj++;
		}
		//100/50
		pfmj=87;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=102;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=135;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=130;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=142;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=145;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=153;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=179;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10050[pfmi]=pfmj;
			pfmj++;
		}
		//100/60
		pfmj=87;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=102;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=119;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=123;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=130;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=136;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=140;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=148;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=175;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10060[pfmi]=pfmj;
			pfmj++;
		}
		//100/70
		pfmj=83;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=98;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=114;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=121;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=121;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=128;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=136;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=146;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=173;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10070[pfmi]=pfmj;
			pfmj++;
		}
		//100/80
		pfmj=84;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=99;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=114;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=125;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=125;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=134;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=139;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=150;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=178;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10080[pfmi]=pfmj;
			pfmj++;
		}
		//100/90
		pfmj=87;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=102;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=120;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=129;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=129;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=138;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=144;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=154;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=182;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore10090[pfmi]=pfmj;
			pfmj++;
		}
		//110/0
		pfmj=125;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=140;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=145;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=147;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=170;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=186;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=204;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=218;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj=pfmj+2.9;
		}
		pfmj=247;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1100[pfmi]=pfmj;
			pfmj++;
		}
		//110/10
		pfmj=125;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=140;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj=pfmj-1.5;
		}
		pfmj=125;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=144;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj=pfmj+2.5;
		}
		pfmj=169;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=186;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=202;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=217;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=244;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11010[pfmi]=pfmj;
			pfmj++;
		}
		//110/20
		pfmj=90;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=105;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=143;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj=pfmj+2.5;
		}
		pfmj=168;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=184;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=202;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=221;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=242;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11020[pfmi]=pfmj;
			pfmj++;
		}
		//110/30
		pfmj=93;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=108;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=143;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=167;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=183;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=201;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=219;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=236;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11030[pfmi]=pfmj;
			pfmj++;
		}
		//110/40
		pfmj=93;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=108;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=143;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=162;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=171;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=176;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=200;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=208;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11040[pfmi]=pfmj;
			pfmj++;
		}
		//110/50
		pfmj=92;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=107;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=132;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=140;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=149;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=155;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=172;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=196;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11050[pfmi]=pfmj;
			pfmj++;
		}
		//110/60
		pfmj=92;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=107;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=125;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj=pfmj-0.1;
		}
		pfmj=124;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=134;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=139;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=144;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=165;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=195;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11060[pfmi]=pfmj;
			pfmj++;
		}
		//110/70
		pfmj=92;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=107;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=126;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=136;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=136;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=141;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=145;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=167;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=195;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11070[pfmi]=pfmj;
			pfmj++;
		}
		//110/80
		pfmj=92;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=107;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj=pfmj+2.5;
		}
		pfmj=132;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=138;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=138;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=145;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=149;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=172;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=202;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11080[pfmi]=pfmj;
			pfmj++;
		}
		//110/90
		pfmj=94;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=109;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj=pfmj+2.9;
		}
		pfmj=138;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=142;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj=pfmj-0.1;
		}
		pfmj=141;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=148;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=152;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=175;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=205;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore11090[pfmi]=pfmj;
			pfmj++;
		}
		//120/0
		pfmj=109;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=124;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=126;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=141;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=146;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj=pfmj+3.2;
		}
		pfmj=178;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=201;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=223;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=247;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1200[pfmi]=pfmj;
			pfmj++;
		}
		//120/10
		pfmj=109;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=124;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=125;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=143;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=144;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj=pfmj+2.9;
		}
		pfmj=173;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=197;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=218;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=244;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12010[pfmi]=pfmj;
			pfmj++;
		}
		//120/20
		pfmj=107;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=122;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=125;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=143;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=166;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj=pfmj+3.2;
		}
		pfmj=198;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=214;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=236;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=266;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12020[pfmi]=pfmj;
			pfmj++;
		}
		//120/30
		pfmj=107;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=122;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=125;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=147;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=163;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=190;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=206;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=222;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj=pfmj+3.8;
		}
		pfmj=260;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12030[pfmi]=pfmj;
			pfmj++;
		}
		//120/40
		pfmj=96;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=111;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=125;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=138;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=154;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=180;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=197;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=215;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=245;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12040[pfmi]=pfmj;
			pfmj++;
		}
		//120/50
		pfmj=95;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=110;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=135;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=145;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=171;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=190;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=200;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=228;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12050[pfmi]=pfmj;
			pfmj++;
		}
		//120/60
		pfmj=94;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=109;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=139;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=139;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=150;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=167;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=185;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj=pfmj+3.3;
		}
		pfmj=218;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12060[pfmi]=pfmj;
			pfmj++;
		}
		//120/70
		pfmj=106;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=121;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=124;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=143;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj=pfmj-0.9;
		}
		pfmj=134;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=142;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=161;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=180;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=207;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12070[pfmi]=pfmj;
			pfmj++;
		}
		//120/80
		pfmj=111;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=126;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=142;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=148;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=143;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=152;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=165;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=183;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=213;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12080[pfmi]=pfmj;
			pfmj++;
		}
		//120/90
		pfmj=116;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=131;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=147;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=152;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=147;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=155;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=169;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=188;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj=pfmj+3.2;
		}
		pfmj=220;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore12090[pfmi]=pfmj;
			pfmj++;
		}
		//130/0
		pfmj=124;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=139;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj=pfmj-1.2;
		}
		pfmj=127;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=128;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=133;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=153;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=158;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=164;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj=pfmj+12.2;
		}
		pfmj=286;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1300[pfmi]=pfmj;
			pfmj++;
		}
		//130/10
		pfmj=124;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=139;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj=pfmj-1.2;
		}
		pfmj=127;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=125;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=128;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=129;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=134;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=144;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj=pfmj+13.2;
		}
		pfmj=276;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13010[pfmi]=pfmj;
			pfmj++;
		}
		//130/20
		pfmj=124;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=139;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj=pfmj-1.2;
		}
		pfmj=127;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=131;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=136;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=154;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=158;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=167;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj=pfmj+19.9;
		}
		pfmj=266;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13020[pfmi]=pfmj;
			pfmj++;
		}
		//130/30
		pfmj=125;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=140;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj=pfmj-1.3;
		}
		pfmj=127;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=140;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=158;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=180;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=199;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=219;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=242;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13030[pfmi]=pfmj;
			pfmj++;
		}
		//130/40
		pfmj=126;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=141;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj=pfmj-1.4;
		}
		pfmj=127;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=138;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=155;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=175;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=196;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=215;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj=pfmj+2.5;
		}
		pfmj=240;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13040[pfmi]=pfmj;
			pfmj++;
		}
		//130/50
		pfmj=122;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=137;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj=pfmj-0.7;
		}
		pfmj=130;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=138;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=154;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=174;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=197;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=213;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj=pfmj+2.6;
		}
		pfmj=239;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13050[pfmi]=pfmj;
			pfmj++;
		}
		//130/60
		pfmj=122;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=137;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj=pfmj-0.7;
		}
		pfmj=130;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=135;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=149;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=168;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj=pfmj+2.5;
		}
		pfmj=193;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=210;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj=pfmj+2.9;
		}
		pfmj=239;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13060[pfmi]=pfmj;
			pfmj++;
		}
		//130/70
		pfmj=125;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=140;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=138;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=135;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=146;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=155;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=179;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=202;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj=pfmj+3.7;
		}
		pfmj=239;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13070[pfmi]=pfmj;
			pfmj++;
		}
		//130/80
		pfmj=129;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=144;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=144;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=155;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=151;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=157;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=185;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=207;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj=pfmj+4;
		}
		pfmj=247;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13080[pfmi]=pfmj;
			pfmj++;
		}
		//130/90
		pfmj=134;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=149;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=151;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=161;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj=pfmj-0.7;
		}
		pfmj=154;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=158;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=188;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=210;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj=pfmj+4.1;
		}
		pfmj=251;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore13090[pfmi]=pfmj;
			pfmj++;
		}
		//140/0
		pfmj=142;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=157;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=159;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=155;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj=pfmj-2.3;
		}
		pfmj=132;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=135;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj=pfmj+3.5;
		}
		pfmj=170;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=176;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj=pfmj+8;
		}
		pfmj=256;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1400[pfmi]=pfmj;
			pfmj++;
		}
		//140/10
		pfmj=142;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=157;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj=pfmj-1.3;
		}
		pfmj=144;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj=pfmj-1.4;
		}
		pfmj=130;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=127;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=130;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj=pfmj+3.2;
		}
		pfmj=162;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=168;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj=pfmj+8.8;
		}
		pfmj=156;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14010[pfmi]=pfmj;
			pfmj++;
		}
		//140/20
		pfmj=140;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=155;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj=pfmj-1.1;
		}
		pfmj=144;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=145;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj=pfmj-1;
		}
		pfmj=135;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=139;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=148;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=154;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj=pfmj+10.2;
		}
		pfmj=256;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14020[pfmi]=pfmj;
			pfmj++;
		}
		//140/30
		pfmj=131;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=146;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=143;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=146;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=148;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=178;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=189;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=198;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj=pfmj+4.9;
		}
		pfmj=247;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14030[pfmi]=pfmj;
			pfmj++;
		}
		//140/40
		pfmj=131;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=146;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=142;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=148;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=153;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=181;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=190;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=202;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj=pfmj+4.6;
		}
		pfmj=248;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14040[pfmi]=pfmj;
			pfmj++;
		}
		//140/50
		pfmj=131;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=146;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=141;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=148;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=155;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=183;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=197;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=212;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj=pfmj+3.8;
		}
		pfmj=250;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14050[pfmi]=pfmj;
			pfmj++;
		}
		//140/60
		pfmj=131;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=146;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj=pfmj-0.6;
		}
		pfmj=140;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=153;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=155;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj=pfmj+2.9;
		}
		pfmj=184;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=204;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=215;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj=pfmj+3.7;
		}
		pfmj=252;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14060[pfmi]=pfmj;
			pfmj++;
		}
		//140/70
		pfmj=131;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=146;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj=pfmj-0.9;
		}
		pfmj=137;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=153;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=157;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=185;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=208;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=221;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj=pfmj+4.4;
		}
		pfmj=265;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14070[pfmi]=pfmj;
			pfmj++;
		}
		//140/80
		pfmj=131;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=146;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj=pfmj-0.9;
		}
		pfmj=137;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=155;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=158;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=185;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=212;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj=pfmj+2.2;
		}
		pfmj=234;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj=pfmj+3.8;
		}
		pfmj=272;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14080[pfmi]=pfmj;
			pfmj++;
		}
		//140/90
		pfmj=131;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=146;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=141;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=159;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj=pfmj-0.1;
		}
		pfmj=158;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=186;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj=pfmj+3;
		}
		pfmj=216;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=236;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj=pfmj+3.8;
		}
		pfmj=274;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore14090[pfmi]=pfmj;
			pfmj++;
		}
		//150/0
		pfmj=150;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=165;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj=pfmj-1.7;
		}
		pfmj=148;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj=pfmj-1.9;
		}
		pfmj=129;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj=pfmj+3.7;
		}
		pfmj=166;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj=pfmj-2.6;
		}
		pfmj=140;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=151;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=158;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=172;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1500[pfmi]=pfmj;
			pfmj++;
		}
		//150/10
		pfmj=130;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=145;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=142;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj=pfmj-1.5;
		}
		pfmj=127;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=128;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=133;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=142;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=144;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=162;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15010[pfmi]=pfmj;
			pfmj++;
		}
		//150/20
		pfmj=130;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=145;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=142;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj=pfmj-1.5;
		}
		pfmj=127;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=136;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=141;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=156;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=166;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=176;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15020[pfmi]=pfmj;
			pfmj++;
		}
		//150/30
		pfmj=124;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=139;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=142;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj=pfmj-0.2;
		}
		pfmj=140;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=150;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=173;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=184;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=188;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=193;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15030[pfmi]=pfmj;
			pfmj++;
		}
		//150/40
		pfmj=124;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=139;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=141;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=145;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=156;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=175;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=190;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=195;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=200;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15040[pfmi]=pfmj;
			pfmj++;
		}
		//150/50
		pfmj=165;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=180;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj=pfmj-3.9;
		}
		pfmj=141;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=148;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=158;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj=pfmj+2;
		}
		pfmj=178;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=196;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=199;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=206;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15050[pfmi]=pfmj;
			pfmj++;
		}
		//150/60
		pfmj=170;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=185;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj=pfmj-4.5;
		}
		pfmj=140;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=153;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=160;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj=pfmj+2.4;
		}
		pfmj=184;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=202;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=206;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=211;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15060[pfmi]=pfmj;
			pfmj++;
		}
		//150/70
		pfmj=133;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=148;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=145;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=156;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=162;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj=pfmj+3.1;
		}
		pfmj=193;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=210;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=222;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=232;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15070[pfmi]=pfmj;
			pfmj++;
		}
		//150/80
		pfmj=133;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=148;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=150;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=160;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=167;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj=pfmj+3.2;
		}
		pfmj=199;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=218;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=231;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=244;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15080[pfmi]=pfmj;
			pfmj++;
		}
		//150/90
		pfmj=134;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=149;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=156;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=163;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=172;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj=pfmj+3.4;
		}
		pfmj=206;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=224;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=238;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=248;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore15090[pfmi]=pfmj;
			pfmj++;
		}
		//160/0
		pfmj=166;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=181;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj=pfmj-0.1;
		}
		pfmj=180;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj=pfmj-2.8;
		}
		pfmj=152;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=158;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj=pfmj-1.2;
		}
		pfmj=146;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=155;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=166;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=175;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1600[pfmi]=pfmj;
			pfmj++;
		}
		//160/10
		pfmj=129;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=144;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=150;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj=pfmj-2.7;
		}
		pfmj=123;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=132;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=127;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=134;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=147;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=162;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16010[pfmi]=pfmj;
			pfmj++;
		}
		//160/20
		pfmj=129;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=144;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=150;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj=pfmj-1;
		}
		pfmj=140;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=152;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=147;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=158;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=170;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=177;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16020[pfmi]=pfmj;
			pfmj++;
		}
		//160/30
		pfmj=128;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=143;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=144;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=148;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj=pfmj+1.7;
		}
		pfmj=165;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj=pfmj-0.1;
		}
		pfmj=164;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=174;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=183;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=188;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16030[pfmi]=pfmj;
			pfmj++;
		}
		//160/40
		pfmj=123;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=138;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=144;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=152;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=166;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=170;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=179;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=190;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=193;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16040[pfmi]=pfmj;
			pfmj++;
		}
		//160/50
		pfmj=175;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=190;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj=pfmj-4.5;
		}
		pfmj=145;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=152;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=166;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=177;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=182;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=196;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=200;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16050[pfmi]=pfmj;
			pfmj++;
		}
		//160/60
		pfmj=130;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=145;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=146;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=152;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=167;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj=pfmj+2.3;
		}
		pfmj=190;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=199;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=206;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=210;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16060[pfmi]=pfmj;
			pfmj++;
		}
		//160/70
		pfmj=124;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=139;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=155;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=152;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=170;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj=pfmj+3.1;
		}
		pfmj=201;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=208;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=216;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=222;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16070[pfmi]=pfmj;
			pfmj++;
		}
		//160/80
		pfmj=124;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=139;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=166;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj=pfmj-0.8;
		}
		pfmj=158;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj=pfmj+1.8;
		}
		pfmj=176;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj=pfmj+2.8;
		}
		pfmj=204;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=213;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=226;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=232;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16080[pfmi]=pfmj;
			pfmj++;
		}
		//160/90
		pfmj=127;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=142;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj=pfmj+2.9;
		}
		pfmj=171;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj=pfmj-1;
		}
		pfmj=161;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj=pfmj+2.1;
		}
		pfmj=182;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj=pfmj+2.7;
		}
		pfmj=209;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=220;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=231;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=238;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore16090[pfmi]=pfmj;
			pfmj++;
		}
		//170/0
		pfmj=153;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=168;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=164;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=173;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj=pfmj-3.4;
		}
		pfmj=139;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=142;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=151;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=157;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=171;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore1700[pfmi]=pfmj;
			pfmj++;
		}
		//170/10
		pfmj=153;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=168;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj=pfmj-3.4;
		}
		pfmj=134;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj=pfmj-0.4;
		}
		pfmj=130;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj=pfmj+0.2;
		}
		pfmj=132;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=136;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=142;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=146;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj=pfmj+1.6;
		}
		pfmj=162;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17010[pfmi]=pfmj;
			pfmj++;
		}
		//170/20
		pfmj=124;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=139;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj=pfmj-0.5;
		}
		pfmj=134;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=143;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj=pfmj-0.1;
		}
		pfmj=142;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=143;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=151;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=156;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=171;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17020[pfmi]=pfmj;
			pfmj++;
		}
		//170/30
		pfmj=123;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=138;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=135;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=150;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=164;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj=pfmj-0.8;
		}
		pfmj=156;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=168;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=174;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=186;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17030[pfmi]=pfmj;
			pfmj++;
		}
		//170/40
		pfmj=185;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=200;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj=pfmj-5.9;
		}
		pfmj=141;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=151;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=166;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj=pfmj-0.3;
		}
		pfmj=163;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=172;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=183;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=190;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17040[pfmi]=pfmj;
			pfmj++;
		}
		//170/50
		pfmj=195;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=210;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj=pfmj-6.3;
		}
		pfmj=147;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=152;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=167;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=168;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=175;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=183;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=193;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17050[pfmi]=pfmj;
			pfmj++;
		}
		//170/60
		pfmj=195;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=210;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj=pfmj-5.8;
		}
		pfmj=152;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj=pfmj+0.3;
		}
		pfmj=155;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=169;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj=pfmj+0.5;
		}
		pfmj=174;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=182;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=188;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=199;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17060[pfmi]=pfmj;
			pfmj++;
		}
		//170/70
		pfmj=133;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=148;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=159;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=165;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj=pfmj+1.1;
		}
		pfmj=176;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj=pfmj+0.4;
		}
		pfmj=180;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj=pfmj+0.8;
		}
		pfmj=188;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=195;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=205;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17070[pfmi]=pfmj;
			pfmj++;
		}
		//170/80
		pfmj=135;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=150;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=162;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=168;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj=pfmj+1.5;
		}
		pfmj=183;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj=pfmj+0.9;
		}
		pfmj=192;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj=pfmj+1.3;
		}
		pfmj=205;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj=pfmj+0;
		}
		pfmj=205;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj=pfmj+0.7;
		}
		pfmj=212;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17080[pfmi]=pfmj;
			pfmj++;
		}
		//170/90
		pfmj=138;
		for(pfmi=0;pfmi<=14;pfmi++)
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj++;
		}
		pfmj=153;
		for(pfmi=15;pfmi<=24;pfmi++)
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj=pfmj+1.2;
		}
		pfmj=165;
		for(pfmi=25;pfmi<=34;pfmi++)
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=171;
		for(pfmi=35;pfmi<=44;pfmi++)
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj=pfmj+1.9;
		}
		pfmj=190;
		for(pfmi=45;pfmi<=54;pfmi++)
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj=pfmj+1;
		}
		pfmj=200;
		for(pfmi=55;pfmi<=64;pfmi++)
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj=pfmj+1.4;
		}
		pfmj=214;
		for(pfmi=65;pfmi<=74;pfmi++)
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj=pfmj+0.1;
		}
		pfmj=215;
		for(pfmi=75;pfmi<=84;pfmi++)
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj=pfmj+0.6;
		}
		pfmj=221;
		for(pfmi=85;pfmi<=284;pfmi++)//285
		{
			charPerformancescore17090[pfmi]=pfmj;
			pfmj++;
		}
	









	    /********************case变量********************/
	    //case1
	    isShootPoint_Arrived = false;
	    /************************************************/
		zhuangqiangshijian=0;
        
        subscription_pose_ = this->create_subscription<message_interface_robosoccer::msg::PoseRobots>("robots_pose", 1, std::bind(&Strategy::pose_sub_callback, this, std::placeholders::_1));
        publish_velocity_ = this->create_publisher<message_interface_robosoccer::msg::VelocityRobots>("robots_velocity",1);
//        timer_ = this->create_wall_timer(std::chrono::milliseconds(20),                  //轮速发布 暂定20ms
//                                          std::bind(&Strategy::timer_callback,this));

        subscription_decisionvar_ = this->create_subscription<message_interface_robosoccer::msg::DecisionVar>("decision_var", 1, std::bind(&Strategy::var_sub_callback, this, std::placeholders::_1));
    }

private:
    rclcpp::Subscription<message_interface_robosoccer::msg::PoseRobots>::SharedPtr subscription_pose_;
    rclcpp::Publisher<message_interface_robosoccer::msg::VelocityRobots>::SharedPtr publish_velocity_;
//    rclcpp::TimerBase::SharedPtr timer_;

    rclcpp::Subscription<message_interface_robosoccer::msg::DecisionVar>::SharedPtr subscription_decisionvar_;
    
    message_interface_robosoccer::msg::PoseRobots robots_pose;
    message_interface_robosoccer::msg::PoseRobots robots_pose_old;
    message_interface_robosoccer::msg::VelocityRobots robots_velocity;
    /***************机器人位姿 var **************/
    RobotPose my_robot_pose[ROBOTNUM+1]; //我方机器人位姿
    RobotPose old_robot_pose[ROBOTNUM+1]; // 上一帧机器人位姿 
    OppRobotPoint opp_robot_point[ROBOTNUM+1]; //敌方机器人位姿
	OppRobotPoint OpponentGoalKeeper; //敌方守门员位置
    /***************球位置 var **************/
    BallPoint ball_point;//当前球位置
    BallPoint old_ball_pts[7];//存储最近7帧球的位置
    BallPoint old_ball_pts_dense[14];//更密集的轨迹记录（14帧）
	FORCASTBALL BallPredictCharacter;//根据14帧历史数据预测的球的相关属性
    Velocity rbV[ROBOTNUM+1];//速度发布 var
	Point endprocessrobot;
    
    int formNo;
	int currentResult[6],oldResult[6];
	int currentForm[6], oldForm[6];
    int currentOrder[6], oldOrder[6];
	double perfRecord[6],oldperfRecord[6];
	int ban_counter, ban_counter2, ban_counter3; //禁区内机器人数量
	int defend_counter; //防守机器人数量
	int ban_warning_flag, ban_warning_flag2; //禁区超时警告标志
	int	ForbinCount;
	int changeCharacter; // 角色转换
	int EndProcessFlag;
	int charrobot;
	int timelimit;
    
    bool isAttack;//GUI设置变量：己方进攻/敌方进攻
    bool isRightArea;//GUI设置变量：右半场/左半场
    int StartMode;//GUI设置变量：比赛模式
    bool isBackInitPose;//GUI设置变量：是否归位
    bool isReInit;//GUI设置变量：是否初始化
    bool isStartGame;//GUI设置变量：开始比赛/停止比赛
	bool RingFlag;//比赛模式转换标志 例如：以点球模式开始，运行一段时间后（这段时间采用点球的队形），就与正常开球无异则转为正常开球模式
    
    double distError;
    double m_Front;
	double End_vxishu;
	double endprocessV;
	double qiusubi; 
	double anglexishuA;
	double anglexishuC; 
	float secondpt1;
	AngleParameter m_AngleParameter;
	MoveParameter m_MoveParameter;
	

	FORCASTBALL         ballCharacter;

	/******************评分变量******************/
	double               charPerformancescore00[285];//
	double               charPerformancescore010[285];//
	double               charPerformancescore020[285];//
	double               charPerformancescore030[285];//
	double               charPerformancescore040[285];//
	double               charPerformancescore050[285];//
	double               charPerformancescore060[285];//
	double               charPerformancescore070[285];//
	double               charPerformancescore080[285];//
	double               charPerformancescore090[285];//
	double               charPerformancescore100[285];//
	double               charPerformancescore1010[285];//
	double               charPerformancescore1020[285];//
	double               charPerformancescore1030[285];//
	double               charPerformancescore1040[285];//
	double               charPerformancescore1050[285];//
	double               charPerformancescore1060[285];//
	double               charPerformancescore1070[285];//
	double               charPerformancescore1080[285];//
	double               charPerformancescore1090[285];//
	double               charPerformancescore200[285];//
	double               charPerformancescore2010[285];//
	double               charPerformancescore2020[285];//
	double               charPerformancescore2030[285];//
	double               charPerformancescore2040[285];//
	double               charPerformancescore2050[285];//
	double               charPerformancescore2060[285];//
	double               charPerformancescore2070[285];//
	double               charPerformancescore2080[285];//
	double               charPerformancescore2090[285];//
	double               charPerformancescore300[285];//
	double               charPerformancescore3010[285];//
	double               charPerformancescore3020[285];//
	double               charPerformancescore3030[285];//
	double               charPerformancescore3040[285];//
	double               charPerformancescore3050[285];//
	double               charPerformancescore3060[285];//
	double               charPerformancescore3070[285];//
	double               charPerformancescore3080[285];//
	double               charPerformancescore3090[285];//
	double               charPerformancescore400[285];//
	double               charPerformancescore4010[285];//
	double               charPerformancescore4020[285];//
	double               charPerformancescore4030[285];//
	double               charPerformancescore4040[285];//
	double               charPerformancescore4050[285];//
	double               charPerformancescore4060[285];//
	double               charPerformancescore4070[285];//
	double               charPerformancescore4080[285];//
	double               charPerformancescore4090[285];//
	double               charPerformancescore500[285];//
	double               charPerformancescore5010[285];//
	double               charPerformancescore5020[285];//
	double               charPerformancescore5030[285];//
	double               charPerformancescore5040[285];//
	double               charPerformancescore5050[285];//
	double               charPerformancescore5060[285];//
	double               charPerformancescore5070[285];//
	double               charPerformancescore5080[285];//
	double               charPerformancescore5090[285];//
	double               charPerformancescore600[285];//
	double               charPerformancescore6010[285];//
	double               charPerformancescore6020[285];//
	double               charPerformancescore6030[285];//
	double               charPerformancescore6040[285];//
	double               charPerformancescore6050[285];//
	double               charPerformancescore6060[285];//
	double               charPerformancescore6070[285];//
	double               charPerformancescore6080[285];//
	double               charPerformancescore6090[285];//
	double               charPerformancescore700[285];//
	double               charPerformancescore7010[285];//
	double               charPerformancescore7020[285];//
	double               charPerformancescore7030[285];//
	double               charPerformancescore7040[285];//
	double               charPerformancescore7050[285];//
	double               charPerformancescore7060[285];//
	double               charPerformancescore7070[285];//
	double               charPerformancescore7080[285];//
	double               charPerformancescore7090[285];//
	double               charPerformancescore800[285];//
	double               charPerformancescore8010[285];//
	double               charPerformancescore8020[285];//
	double               charPerformancescore8030[285];//
	double               charPerformancescore8040[285];//
	double               charPerformancescore8050[285];//
	double               charPerformancescore8060[285];//
	double               charPerformancescore8070[285];//
	double               charPerformancescore8080[285];//
	double               charPerformancescore8090[285];//
	double               charPerformancescore900[285];//
	double               charPerformancescore9010[285];//
	double               charPerformancescore9020[285];//
	double               charPerformancescore9030[285];//
	double               charPerformancescore9040[285];//
	double               charPerformancescore9050[285];//
	double               charPerformancescore9060[285];//
	double               charPerformancescore9070[285];//
	double               charPerformancescore9080[285];//
	double               charPerformancescore9090[285];//
	double               charPerformancescore1000[285];//
	double               charPerformancescore10010[285];//
	double               charPerformancescore10020[285];//
	double               charPerformancescore10030[285];//
	double               charPerformancescore10040[285];//
	double               charPerformancescore10050[285];//
	double               charPerformancescore10060[285];//
	double               charPerformancescore10070[285];//
	double               charPerformancescore10080[285];//
	double               charPerformancescore10090[285];//
	double               charPerformancescore1100[285];//
	double               charPerformancescore11010[285];//
	double               charPerformancescore11020[285];//
	double               charPerformancescore11030[285];//
	double               charPerformancescore11040[285];//
	double               charPerformancescore11050[285];//
	double               charPerformancescore11060[285];//
	double               charPerformancescore11070[285];//
	double               charPerformancescore11080[285];//
	double               charPerformancescore11090[285];//
	double               charPerformancescore1200[285];//
	double               charPerformancescore12010[285];//
	double               charPerformancescore12020[285];//
	double               charPerformancescore12030[285];//
	double               charPerformancescore12040[285];//
	double               charPerformancescore12050[285];//
	double               charPerformancescore12060[285];//
	double               charPerformancescore12070[285];//
	double               charPerformancescore12080[285];//
	double               charPerformancescore12090[285];//
	double               charPerformancescore1300[285];//
	double               charPerformancescore13010[285];//
	double               charPerformancescore13020[285];//
	double               charPerformancescore13030[285];//
	double               charPerformancescore13040[285];//
	double               charPerformancescore13050[285];//
	double               charPerformancescore13060[285];//
	double               charPerformancescore13070[285];//
	double               charPerformancescore13080[285];//
	double               charPerformancescore13090[285];//
	double               charPerformancescore1400[285];//
	double               charPerformancescore14010[285];//
	double               charPerformancescore14020[285];//
	double               charPerformancescore14030[285];//
	double               charPerformancescore14040[285];//
	double               charPerformancescore14050[285];//
	double               charPerformancescore14060[285];//
	double               charPerformancescore14070[285];//
	double               charPerformancescore14080[285];//
	double               charPerformancescore14090[285];//
	double               charPerformancescore1500[285];//
	double               charPerformancescore15010[285];//
	double               charPerformancescore15020[285];//
	double               charPerformancescore15030[285];//
	double               charPerformancescore15040[285];//
	double               charPerformancescore15050[285];//
	double               charPerformancescore15060[285];//
	double               charPerformancescore15070[285];//
	double               charPerformancescore15080[285];//
	double               charPerformancescore15090[285];//
	double               charPerformancescore1600[285];//
	double               charPerformancescore16010[285];//
	double               charPerformancescore16020[285];//
	double               charPerformancescore16030[285];//
	double               charPerformancescore16040[285];//
	double               charPerformancescore16050[285];//
	double               charPerformancescore16060[285];//
	double               charPerformancescore16070[285];//
	double               charPerformancescore16080[285];//
	double               charPerformancescore16090[285];//
	double               charPerformancescore1700[285];//
	double               charPerformancescore17010[285];//
	double               charPerformancescore17020[285];//
	double               charPerformancescore17030[285];//
	double               charPerformancescore17040[285];//
	double               charPerformancescore17050[285];//
	double               charPerformancescore17060[285];//
	double               charPerformancescore17070[285];//
	double               charPerformancescore17080[285];//
	double               charPerformancescore17090[285];//


	int  yanchi;
int	vx;
BallPoint		oldBallPt[7];
BallPoint		oldBallPtv[14];
RobotPose		Robot[12];

int shootsign3;
int zhuangqiangshijian ;
double              moca,moca1;
double               pfmj;
int                  pfmi;
int					readyflag;
double  dizeng;
double				zhichong[50];
int step;
int					zsg_time;
int					timer;

int g_GoalKeeper;
int					g_timeflag;
//int showtarget2;
int					defendflag;
float robotY2;
float               robotY1;
float             secondpt;
float               showtarget;
float               showtarget1;
float               showtarget2;
float v_xishu;




	/******************综合运动变量******************/
	//case1
	bool isShootPoint_Arrived;
	/************************************************/

	//接收QT端发布的决策变量
    void var_sub_callback(const message_interface_robosoccer::msg::DecisionVar::SharedPtr msg)
    {
        isAttack = msg->decisionvar[0];
        isRightArea = msg->decisionvar[1];
        StartMode = msg->decisionvar[2];
        isBackInitPose = msg->decisionvar[3];
        isReInit = msg->decisionvar[4];
        isStartGame = msg->decisionvar[5];
        
        if(isReInit == true)
        {
            //需要初始化的变量
            isShootPoint_Arrived = false;
        }
        
        RCLCPP_INFO(this->get_logger(), "成功接收策略变量!");
    }
    //订阅经过vision_processing处理得到的位姿 初步处理位姿 完成坐标转换 
    void pose_sub_callback(const message_interface_robosoccer::msg::PoseRobots::SharedPtr msg)
    {
        /********************坐标转换********************/
        for (int i=0; i<11; i++)
        {
            robots_pose_old.pose[i].x = robots_pose.pose[i].x;
            robots_pose_old.pose[i].y = robots_pose.pose[i].y;
            robots_pose_old.pose[i].theta = robots_pose.pose[i].theta;
            
            robots_pose.pose[i].x = msg->pose[i].x;
            robots_pose.pose[i].y = GROUND_HEIGHT-msg->pose[i].y;
            robots_pose.pose[i].theta = msg->pose[i].theta*Pi/180;
            
            if (robots_pose.pose[i].x==wallleft || robots_pose.pose[i].x==wallright || robots_pose.pose[i].y==wallbottom || robots_pose.pose[i].y==walltop)
            {
                robots_pose.pose[i].x = robots_pose_old.pose[i].x;
                robots_pose.pose[i].y = robots_pose_old.pose[i].y;
                robots_pose.pose[i].theta = robots_pose_old.pose[i].theta;
            }
			
        }
        if (isRightArea)
        {
            for (int i=0; i<11; i++)
            {
                robots_pose.pose[i].x = GROUND_WIDTH-robots_pose.pose[i].x;
                robots_pose.pose[i].y = GROUND_HEIGHT-robots_pose.pose[i].y;
                robots_pose.pose[i].theta = Pi+robots_pose.pose[i].theta;
                if (robots_pose.pose[i].theta > 2 * Pi) 
                    robots_pose.pose[i].theta -= 2 * Pi;
            }
        }
        
        for (int i=1; i<=ROBOTNUM; i++)
        {
            my_robot_pose[i].x = robots_pose.pose[i-1].x;
            my_robot_pose[i].y = robots_pose.pose[i-1].y;
            my_robot_pose[i].theta = robots_pose.pose[i-1].theta;
            
            opp_robot_point[i].x = robots_pose.pose[i+4].x;
            opp_robot_point[i].y = robots_pose.pose[i+4].y;

			if (my_robot_pose[i].x < 30 && my_robot_pose[i].y < 125 && my_robot_pose[i].y > 55)  //判断是否在禁区内
				ban_counter++;
			if (my_robot_pose[i].x < 15 && my_robot_pose[i].y < 115 && my_robot_pose[i].y > 65)
				ban_counter2++;
			if(my_robot_pose[i].x < 30 && my_robot_pose[i].x > 10 && my_robot_pose[i].y < 125 && my_robot_pose[i].y > 55)
				ban_counter3++;
			
			if (opp_robot_point[i].x > 205 && opp_robot_point[i].x < 255 && opp_robot_point[i].y < 115 && opp_robot_point[i].y > 65)
			{
				OpponentGoalKeeper.x = opp_robot_point[i].x;
				OpponentGoalKeeper.y = opp_robot_point[i].y;
			}
			
        }
        ball_point.x = robots_pose.pose[10].x;
        ball_point.y = robots_pose.pose[10].y;

		/********************************/
		if (ban_counter > 3) defend_counter = 2;
		else if (ban_counter > 2) defend_counter = 1;
		else defend_counter = 0;
		


		if (defend_counter == 2)
		{
			ban_warning_flag--;
			if (ban_warning_flag < 0) ban_warning_flag = 0;
		}
		else ban_warning_flag = 100;
		

		if (ban_counter2 > 3) ForbinCount = 2;
		else if (ban_counter2 > 2) ForbinCount = 1;
		else ForbinCount = 0;

		if (ForbinCount == 1)
		{
			ban_warning_flag2--;
			if (ban_warning_flag2 < 0) ban_warning_flag2 = 0;
		}
		else ban_warning_flag2 = 100;

		if(ban_counter3 < 2) charrobot=0;
		else charrobot=1;

        /************************************************/
		
		if (isBackInitPose)
	        RobotReturn2InitPt();//归位
        else
        {
	        MiroSot_DecisionMaking();//比赛
		}
		
		//发布轮速
		for (int i=0; i<ROBOTNUM; i++)
        {
            robots_velocity.velocity[i].left_wheel = rbV[i+1].LeftValue;
            robots_velocity.velocity[i].right_wheel = rbV[i+1].RightValue;
        }
        publish_velocity_->publish(robots_velocity);
        // RCLCPP_INFO(this->get_logger(), "| 1号车速度设定: L:%f R:%f|", 
        //             robots_velocity.velocity[0].left_wheel, robots_velocity.velocity[0].right_wheel);
    }
    
//    void timer_callback()
//    {
//        for (int i=0; i<ROBOTNUM; i++)
//        {
//            robots_velocity.velocity[i].left_wheel = rbV[i+1].LeftValue;
//            robots_velocity.velocity[i].right_wheel = rbV[i+1].RightValue;
//        }
//        
//        publish_velocity_->publish(robots_velocity);
//    }
    
    
    void RobotReturn2InitPt()
    {
	    RobotPose Robot_pt[6];
	    switch(StartMode)
	    {
	    case NormalStart://普通
		    {
			    if(isAttack)//我方开球
			    {
				    Robot_pt[1].x = CENTER_X;
				    Robot_pt[1].y = CENTER_Y + 4.0;
				    Robot_pt[1].theta = 5.4;
				    
				    Robot_pt[2].x = CENTER_X - 14.0;
				    Robot_pt[2].y = CENTER_Y - 5.0;
				    Robot_pt[2].theta = 0;
				    
				    Robot_pt[3].x = 21;
				    Robot_pt[3].y = CENTER_Y + 10.0;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 21;
				    Robot_pt[4].y = CENTER_Y - 10.0;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }	
			    else//对方开球
			    {
				    Robot_pt[1].x = 80;
				    Robot_pt[1].y = CENTER_Y;
				    Robot_pt[1].theta = 0;
				    
				    Robot_pt[2].x = 50;
				    Robot_pt[2].y = CENTER_Y ;
				    Robot_pt[2].theta = 0;
				    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = CENTER_Y + 10.0;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = CENTER_Y - 10.0;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
		    }
		    break;
	    case PenaltyKick://点球
		    {
			    if(!isAttack)//对方点球
			    {
				    Robot_pt[1].x = 114;
				    Robot_pt[1].y = 50;
				    Robot_pt[1].theta = Pi;
				    
				    Robot_pt[2].x = 114;
				    Robot_pt[2].y = 80;
				    Robot_pt[2].theta = Pi;
				    
				    Robot_pt[3].x = 114;
				    Robot_pt[3].y = 100;
				    Robot_pt[3].theta = Pi;
				    
				    Robot_pt[4].x = 114;
				    Robot_pt[4].y = 130;
				    Robot_pt[4].theta = Pi;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
			    else//我方点球
			    {
				    Robot_pt[1].x = 175;
				    Robot_pt[1].y = 90;
				    Robot_pt[1].theta = 0;
				    
				    Robot_pt[2].x = 100;
				    Robot_pt[2].y = 65;
				    Robot_pt[2].theta = 0;
				    
				    Robot_pt[3].x = 100;
				    Robot_pt[3].y = 115;
				    Robot_pt[3].theta = 0;
				    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = 85;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y + 5.0;
				    Robot_pt[5].theta = Pi/2;
			    }
		    }
		    break;
	    case GoalKick://门球
		    {
			    if(!isAttack)//对方发球
			    {
				    Robot_pt[1].x = 100;
				    Robot_pt[1].y = 140;
				    Robot_pt[1].theta = 0;
				    
				    Robot_pt[2].x = 100;
				    Robot_pt[2].y = 40;
				    Robot_pt[2].theta = 0;
				    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = 98;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = 82;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
			    else//我方发球
			    {
				    Robot_pt[1].x = 10;
				    Robot_pt[1].y = 110;
				    Robot_pt[1].theta =Pi/12;
				    
				    Robot_pt[2].x = 10;
				    Robot_pt[2].y = 150;
				    Robot_pt[2].theta = 0;
				    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = 70;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 60;
				    Robot_pt[4].y = 75;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = 60;
				    Robot_pt[5].theta = Pi/2;
			    }
		    }
		    break;
	    case FreeKick://任意球
		    {
			    //对方开任意球
			    if(!isAttack)
			    {
				    Robot_pt[1].x = ball_point.x - 22;
				    Robot_pt[1].y = ball_point.y;
				    Robot_pt[1].theta = 0;
				    
				    Robot_pt[2].x = ball_point.x - 22;
				    if(ball_point.y>90)
					    Robot_pt[2].y = ball_point.y - 12;
				    else 
					    Robot_pt[2].y= ball_point.y + 12;
				    Robot_pt[2].theta = 0;
				    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = 100;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = 80;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
			    //我方开任意球
			    else
			    {
				    Robot_pt[1].x = ball_point.x - 15;
				    Robot_pt[1].y = ball_point.y;
				    Robot_pt[1].theta = 0;
				    
				    Robot_pt[2].x = ball_point.x - 22;
				    if(ball_point.y>90)
					    Robot_pt[2].y = ball_point.y - 12;
				    else
					    Robot_pt[2].y = ball_point.y + 12;
				    
				    Robot_pt[2].theta = 0;
				    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = 100;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = 80;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
		    }
		    break;
	    case TackleBall://争球
		    {
			    if(ball_point.x<CENTER_X && ball_point.y<CENTER_Y)
			    {
				    Robot_pt[1].x = 30;
				    Robot_pt[1].y = 30;
				    Robot_pt[1].theta = 0;
								    
				    Robot_pt[2].x = 45;
				    Robot_pt[2].y = CENTER_Y;
				    Robot_pt[2].theta = 3*Pi/2;
				    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = CENTER_Y;
				    Robot_pt[3].theta = Pi/2;
								    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = CENTER_Y + 12.0;
				    Robot_pt[4].theta = Pi/2;

				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
			    else if(ball_point.x<CENTER_X && ball_point.y>CENTER_Y)
			    {
				    Robot_pt[1].x = 30;
				    Robot_pt[1].y = 150;
				    Robot_pt[1].theta = 0;
					    
				    Robot_pt[2].x = 45;
				    Robot_pt[2].y = CENTER_Y;
				    Robot_pt[2].theta = 3*Pi/2;
				    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = CENTER_Y - 12.0;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = CENTER_Y;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
			    else if(ball_point.x>CENTER_X && ball_point.y<CENTER_Y)
			    {
				    Robot_pt[1].x = 140;
				    Robot_pt[1].y = 30;
				    Robot_pt[1].theta = 0;
				    
				    Robot_pt[2].x = 100;
				    Robot_pt[2].y = CENTER_Y - 30.0;
				    Robot_pt[2].theta = 0;
					    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = 75;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = 85;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
			    else
			    {
				    Robot_pt[1].x = 140;
				    Robot_pt[1].y = 150;
				    Robot_pt[1].theta = 0;
				    
				    Robot_pt[2].x = 100;
				    Robot_pt[2].y = CENTER_Y + 30.0;
				    Robot_pt[2].theta = 0;
					    
				    Robot_pt[3].x = 20;
				    Robot_pt[3].y = 95;
				    Robot_pt[3].theta = Pi/2;
				    
				    Robot_pt[4].x = 20;
				    Robot_pt[4].y = 105;
				    Robot_pt[4].theta = Pi/2;
				    
				    Robot_pt[5].x = 5;
				    Robot_pt[5].y = CENTER_Y;
				    Robot_pt[5].theta = Pi/2;
			    }
		    }
		    break;
	    case RetractCar://收车
		    {
                if(!isAttack)
			    {
                    for(int i=1;i<=5;i++)
				    {
					    Robot_pt[i].x = 210;
					    Robot_pt[i].y = 110.0 + 12.0*i;
					    Robot_pt[i].theta = 0;
				    }
			    }
			    else
			    {
                    for(int i=1;i<=5;i++)
				    {
					    Robot_pt[i].x = 10;
					    Robot_pt[i].y = 110.0 + 12.0*i;
					    Robot_pt[i].theta = 0;
				    }
			    }
		    }
		    break;
	    default:
		    break;
	    }
	    //--比赛用代码段--
	    if(isStartGame)
		{
	        for(int i=1;i<=ROBOTNUM;i++)
	        {
		        Point pt[ROBOTNUM+1];
		        pt[i].x = Robot_pt[i].x;
		        pt[i].y = Robot_pt[i].y;
		        if(distRobot2Pt(my_robot_pose[i],pt[i])>distError)
		        {
			        ToPositionN(&my_robot_pose[i],pt[i],40, &rbV[i]);
		        }
		        else
			        s_TurnToAnglePD(&my_robot_pose[i],Robot_pt[i].theta,&rbV[i]);	
	        }
	    }
	    else
	    {
	        for(int i=1;i<=ROBOTNUM;i++)
	        {
		        rbV[i].LeftValue = 0;
		        rbV[i].RightValue = 0;	
	        }
	    }
	    //---------------
	    //--测试用代码段--
//	    Point pt;
//	    pt.x = 20;
//	    pt.y = 90;
//      double angle;
//      angle = 0;
//	    if(distRobot2Pt(my_robot_pose[1],pt)>distError)
//	    {
//		    ToPositionN(&my_robot_pose[1],pt,60, 0, &rbV[1]);
//	    }
//	    else
//		    s_TurnToAnglePD(&my_robot_pose[1],angle,&rbV[1]);	
	    //---------------
	    return;
    }
    void MiroSot_DecisionMaking()
    {
	    preProcess();//信息预处理，记录机器人小车和球的轨迹(最近几帧的位置，可用于预测)
	    
	    int areaNo;
	    areaNo = GetAreaNo(ball_point);//场地分区，得到球所在的区域号码(看球落在哪个区块上，采用先粗分后细分的方法)[1-32]
	    
	    taskDecompose(areaNo);//队形制定，根据球所在的区号确定机器人队形号码dmformNo(同时还能根据开球状态看使用哪种队形模式)   例如：6
	    formInterpret();//队形解释，根据队形号得到其所对应的角色号，结果按重要性排序存到数组currentForm中，按角色重要性排序而不是车号   例如：32、33、1、68
	    
	    charAllot();//角色分配(任务分配)，依据所需角色的重要性依次得到完成队形应该所需要的车号数组currentOrder   例如：3、4、1、2
	    robotManager();//机器人管理，将车号与角色号对应起来得到数组currentResult   例如：1、68、32、33
	    bestManager();//优化分配，优化机器人管理(固化后卫)，即守门角色车号固定(例如：角色12固定5号车)
	    
	    actProcess();//动作执行，更新小车轮速值
	    
	    return;
    }
    
    /********************比赛函数********************/

    void preProcess()
    {
		short i; //循环用

        // 防止视觉数据错误（丢车）
        for(int i=1; i<=ROBOTNUM; i++)
        {
            if(my_robot_pose[i].x == 0 && my_robot_pose[i].y == 180)
                my_robot_pose[i] = old_robot_pose[i];
        }
        
        // 更新历史轨迹（保留最近7/14帧）
        static int frame_count = 0;
        frame_count = (frame_count + 1) % 7;
        
		if (frame_count == 1) // 第一次进入函数 将历史帧全部设为当前帧
		{
			for (i = 0; i < 7; i++)
			{
				old_ball_pts[i] = ball_point;
			}
			
			for (i = 0; i < 14; i++)
			{
				old_ball_pts_dense[i] = ball_point;
			}
		}
		else // 循环更新历史数据，保持该数组存储最新的 7/14 帧数据
		{
			for (i = 0; i < 6; i++)
			{
				old_ball_pts[i] = old_ball_pts[i+1];
			}
			old_ball_pts[6] = ball_point;

			for ( i = 0; i < 13; i++)
			{
				old_ball_pts_dense[i] = old_ball_pts_dense[i+1];
			}
			old_ball_pts_dense[13] = ball_point;
			
		}
		
		
        // 预测球速轨迹等 此处使用历史14帧
        predictBall_14_(old_ball_pts_dense,&BallPredictCharacter);
        
        // 保存当前机器人位姿
        for(int i=1; i<=ROBOTNUM; i++)
            old_robot_pose[i] = my_robot_pose[i];
    }

    int GetAreaNo(BallPoint ball)
    {
        int areaNo;
		Point Point1, Point2;
		LINEFORMULATION line;
		
		//先粗分 后细分

		// 粗分部分
		if (ball.x <= 60)
		{
			if (ball.y >= 90 && ball.y <= 180) 
			{
				areaNo = 1;
			}
			else
			{
				areaNo = 8;
			}
		}
		else if (ball.x >= 60 && ball.x <= 175)
		{
			if (ball.y >= 155)
			{
				areaNo = 18;
			}
			else if (ball.y >= 25 && ball.y <= 155)
			{
				areaNo = 19;
			}
			else
			{
				areaNo = 20;
			}						
		}
		else if (ball.x >= 175 && ball.x <= 220)
		{
			areaNo = 23;
		}
		
		// 细分部分
		switch (areaNo)
		{
		case 1:
			if (ball.x <= 15)
			{
				if (ball.y <= 115)
				{
					areaNo = 4;
				}
				else if (ball.y >= 115 && ball.y <= 135)
				{
					areaNo = 3;
				}
				else if (ball.y >= 135 && ball.y <= 160)
				{
					areaNo = 2;
				}
				else	
				{
					areaNo = 1;
				}
			}
			else
			{
				if (ball.y >= 160 && ball.y <= 180)
				{
					if (ball.x >= 15 && ball.x <= 20)
					{
						Point1.x = 15;
						Point1.y = 160;
						Point2.x = 20;
						Point2.y = 165;
						StdLineForm(Point1, Point2, line);
						if (ball.y <= (line.a*ball.x + line.c) / (-line.b))
						{
							areaNo = 10;
						}
						else areaNo = 1;
					}
					else
					{
						if (ball.y >= 165 && ball.y <= 180)
						{
							areaNo = 9;
						}
						else
						{
							areaNo = 10;
						}
					}
				}
				else
				{
					Point1.x = 15; Point1.y = 115; Point2.x = 60; Point2.y = 160;
					StdLineForm(Point1, Point2, line);
					if (ball.y >= (line.a*ball.x + line.c) / (-line.b))
					{
						areaNo = 10;
					}
					else
					{
						if (ball.x >= 15 && ball.x <= 35)
						{
							areaNo = 11;
						}
						else areaNo = 15;
					}	
				}
			}
			break;
		
		case 8:
			if (ball.x <= 15)
			{
				if (ball.y >= 65)
				{
					areaNo = 5;
				}
				else if (ball.y >= 45 && ball.y <= 65)
				{
					areaNo = 6;
				}
				else if (ball.y >= 20 && ball.y <= 45)
				{
					areaNo = 7;
				}
				else	
				{
					areaNo = 8;
				}
			}
			else
			{
				if (ball.y >= 0 && ball.y <= 20)
				{
					if (ball.x >= 15 && ball.x <= 20)
					{
						Point1.x = 20;Point1.y = 15;Point2.x = 15;Point2.y = 20;
						StdLineForm(Point1, Point2, line);
						if (ball.y <= (line.a*ball.x + line.c) / (-line.b))
						{
							areaNo = 8;
						}
						else areaNo = 13;
					}
					else
					{
						if (ball.y >= 0 && ball.y <= 15)
						{
							areaNo = 14;
						}
						else
						{
							areaNo = 13;
						}
					}
				}
				else
				{
					Point1.x = 60; Point1.y = 20; Point2.x = 15; Point2.y = 65;
					StdLineForm(Point1, Point2, line);
					if (ball.y <= (line.a*ball.x + line.c) / (-line.b))
					{
						areaNo = 13;
					}
					else
					{
						if (ball.x >= 15 && ball.x <= 35)
						{
							areaNo = 12;
						}
						else areaNo = 16;
					}	
				}
			}
			break;
		
		case 18:
			if (ball.y >= 165)
			{
				if (ball.x <= 110)
				{
					areaNo = 17;
				}
				else areaNo = 31;
			}
			break;
		
		case 19:
			areaNo = 19;
			break;
		case 20:
			if (ball.y <= 15)
			{
				if (ball.x <= 110)
				{
					areaNo = 21;
				}
				else areaNo = 32;
			}
			break;

		case 23:
			if (ball.x >= 205)
			{
				if (ball.y >= 160)
				{
					areaNo = 26;
				}
				else if (ball.y >= 115 && ball.y <= 160)
				{
					areaNo = 27;
				}
				else if (ball.y >= 65 && ball.y <= 115)
				{
					areaNo = 28;
				}
				else if (ball.y >= 20 && ball.y <= 65)
				{
					areaNo = 29;
				}
				else
				{
					areaNo = 30;
				}
			}
			else
			{
				if (ball.y >= 165)  //此处与标准分区没有严格相同 
				{
					if (ball.x <= 200)
					{
						areaNo = 31;
					}
					else areaNo = 26;
				}
				else if (ball.y >= 115 && ball.y <= 165)
				{
					Point1.x = 175; Point1.y = 165; Point2.x = 205; Point2.y = 115;
					StdLineForm(Point1, Point2, line);
					if (ball.y >= (line.a*ball.x + line.c) / (-line.b)) 
					{
						areaNo = 22;
					}
					else areaNo = 23;
				}
				else if (ball.y >= 90 && ball.y <= 115)
				{
					areaNo = 23;
				}
				else if (ball.y >= 65 && ball.y <= 90)
				{
					areaNo = 24;
				}
				else if (ball.y >= 15 && ball.y <= 65)
				{
					Point1.x = 205; Point1.y = 65; Point2.x = 175; Point2.y = 15;
					StdLineForm(Point1, Point2, line);
					if (ball.y >= (line.a*ball.x + line.c) / (-line.b))
					{
						areaNo = 24;
					}
					else areaNo = 25;
				}
				else
				{
					if (ball.x <= 200)
					{
						areaNo = 32;
					}
					else areaNo = 30;
					
				}
			}
			break;	
		default:
			areaNo = 0;
			break;
		}
		//RCLCPP_INFO(this->get_logger(),"""areaNo = %d""",areaNo);  //分区测试 
        return areaNo;
    }
	
    int taskDecompose(int areaNo)
    {
        formNo = areaNo;
        
		static int timer_ = 0;
		int timelimit = 0;
		if (!RingFlag)
		{
			StartMode = NormalStart;
			return 1;
		}
		else
		{
			timer_++;
		}
		if(StartMode == NormalStart)
			{
				timelimit = 40;	//30 未经测试
			}
		else if (StartMode == PenaltyKick && isAttack == false)
			timelimit = 30;
		else if(StartMode==PenaltyKick)
			timelimit = 35;//25
		else if(StartMode==GoalKick)//
			timelimit = 40;//80
		else
			timelimit = 80;//20//30
		
		if(timer_ >= timelimit)
		{
			timer_ = 0;
			RingFlag = false;
			return 1;
		}

		switch(StartMode)
			{
			case NormalStart:
				{
					if(isAttack)
						formNo = 100;
					else
						formNo = 101;
				}
				break; 
			case PenaltyKick:
				{
					if(isAttack)
						if (timer_>11)//10
							formNo = 102;
						else
							formNo = 108;
				}
				break;
			case FreeKick:
				{
					if(isAttack)
						formNo = 104;
					else
						formNo = 105;
				}
				break;
			case TackleBall:
				formNo = 106;
				break;
			case GoalKick:
				formNo = 107;
				break;
			default:
				formNo = 101;
				break;
			}
			
		return 1;
    }
	
    void formInterpret()
    {
        bool flag = false;
		short down = 0;
		int tempForm[6];
		if (old_ball_pts[0].x > old_ball_pts[3].x && old_ball_pts[3].x > old_ball_pts[6].x)
		{
			flag = true;
		}
		if (old_ball_pts[0].y > old_ball_pts[3].y && old_ball_pts[0].y > old_ball_pts[6].y)
		{
			down = 1;
		}
		else if (old_ball_pts[0].y < old_ball_pts[3].y && old_ball_pts[0].y < old_ball_pts[6].y)
		{
			down = -1;
		}
		
		switch(formNo)
		{
		case 1:
			{
	
				if(ban_warning_flag==0)
				{
					tempForm[1] = 1;
					tempForm[2] = 27;
					tempForm[3] = 20;
					tempForm[4] = 7;//8
				}
				else
				{
					tempForm[1] = 20;
					tempForm[2] = 7;
					tempForm[4] = 27;
					tempForm[3] = 1;
				}
			}
			break;	
		case 2:
			{
				if(ban_warning_flag==0)
				{   
					tempForm[1] = 27;
					if(ball_point.y>144)
						tempForm[2] = 1;
					else
						tempForm[2] = 29;
					tempForm[3] = 20;
					tempForm[4] = 7;
				}
				else
				{
					tempForm[1] = 20;
					tempForm[2] = 7;//8
					tempForm[3] = 27;
					if(ball_point.y>144)
						tempForm[4] = 1;
					else
						tempForm[4] = 29;	
					
					
				}
			}
			break;
		case 3:
			{ 
				if(ban_warning_flag==0)
				{
					tempForm[1] = 27;
					tempForm[2] = 15;
					tempForm[3] = 20;
					tempForm[4] = 7;
				}
				else
				{
					tempForm[1] = 20;
					tempForm[2] = 7;//8
					tempForm[3] = 27;
					tempForm[4] = 15;
				}
			}
			break;
		case 4:
			{
				if(down == 1)
				{
					tempForm[1] = 8;
					tempForm[2] = 7;
					tempForm[3] = 16;
					tempForm[4] = 15;			
				}
				else
				{
					tempForm[1] = 7;
					tempForm[2] = 8;
					tempForm[3] = 15;
					tempForm[4] = 16;
				}
			}
			break;
		case 5:
			{
				if(down == 1)
				{
					tempForm[1] = 8;
					tempForm[2] = 7;
					tempForm[3] = 16;
					tempForm[4] = 15;			
				}
				else
				{
					tempForm[1] = 7;
					tempForm[2] = 8;
					tempForm[3] = 15;
					tempForm[4] = 16;
				}
			}
			break;
		case 6:
			{
				if(ban_warning_flag==0)
				{		
					tempForm[1] = 16;
					tempForm[2] = 22;
					tempForm[3] = 21;
					tempForm[4] = 8;//7
				}
				else
				{
					tempForm[1] = 21;
					tempForm[2] = 8;//7
					tempForm[3] = 16;
					tempForm[4] = 22;
				}
			}
			break;
		case 7:
			{
				if(ban_warning_flag==0)
				{
					tempForm[1] = 22;
					if(ball_point.y<36)
						tempForm[2] = 1;
					else
						tempForm[2] = 28;
					tempForm[3] = 21;
					tempForm[4] = 8;//7
				}
				else
				{
					tempForm[1] = 21;
					tempForm[2] = 8;//7
					tempForm[3] = 22;
					if(ball_point.y<36)
						tempForm[4] = 1;
					else
						tempForm[4] = 28;	
					
				}
			}
			break;
		case 8:
			{      
				if(ban_warning_flag==0)
				{		
					tempForm[1] = 1;
					tempForm[2] = 22;
					tempForm[3] = 21;		
					tempForm[4] = 8;//7
				}
				else
				{
					tempForm[1] = 21;			
					tempForm[2] = 8;//7
					tempForm[3] = 1;
					tempForm[4] = 22;
				}
			}
			break;
		case 9:
			{
				if(ban_warning_flag==0)
				{			
					tempForm[1] = 1;
					tempForm[2] = 27;
					tempForm[3] = 20;
					tempForm[4] = 8;
				}
				else
				{
					tempForm[1] = 20;
					tempForm[2] = 8;
					tempForm[3] = 1;
					tempForm[4] = 27;
				}
			}
			break;
		case 10:
			{
				if(ban_warning_flag==0)
				{				
					if(ball_point.y>=145)
					{
						tempForm[1] = 3;
						tempForm[2] = 27;
					}
					else
					{
						if(down==1)
						{
							tempForm[1] = 15;
							tempForm[2] = 27;
						}
						else
						{
							tempForm[1] = 27;
							tempForm[2] = 15;
						}
					}
					tempForm[3] = 20;
					tempForm[4] = 8;
				}
				else//ban_warning_flag!=0
				{
					tempForm[1] = 20;
					tempForm[2] = 8;
					if(ball_point.y>=145)
					{
						tempForm[3] = 3;
						tempForm[4] = 27;
					}
					else
					{
						if(down==1)
						{
							tempForm[3] = 15;
							tempForm[4] = 27;
						}
						else
						{
							tempForm[3] = 27;
							tempForm[4] = 15;
						}
					}
				}
			}
			break;
		case 11:
			{
				if(ban_warning_flag==0)
				{		
					if(down == 1)
					{
						tempForm[1] = 16;
						tempForm[2] = 15;		
						tempForm[3] = 32;	
						tempForm[4] = 33;
					}
					else
					{
						tempForm[1] = 15;
						tempForm[2] = 16;				
						tempForm[3] = 32;	
						tempForm[4] = 33;			
					}
				}
				else//ban_warning_flag!=0
				{
					if(down == 1)
					{				
						tempForm[1] = 32;	
						tempForm[2] = 33;
						tempForm[3] = 16;
						tempForm[4] = 15;
					}
					else
					{
						tempForm[1] = 32;	
						tempForm[2] = 33;
						tempForm[3] = 15;
						tempForm[4] = 16;			
					}
				}
			}
			break;
		case 12:
			{
				if(ban_warning_flag==0)
				{				
					if(down == 1)
					{
						tempForm[1] = 16;
						tempForm[2] = 15;
						tempForm[3] = 32;	
						tempForm[4] = 33;
					}
					else
					{
						tempForm[1] = 15;
						tempForm[2] = 16;		
						tempForm[3] = 32;	
						tempForm[4] = 33;	
					}
				}
				else//ban_warning_flag!=0
				{
					if(down == 1)
					{					
						tempForm[1] = 32;	
						tempForm[2] = 33;					
						tempForm[3] = 16;
						tempForm[4] = 15;
					}
					else
					{			
						tempForm[1] = 32;	
						tempForm[2] = 33;
						tempForm[3] = 15;
						tempForm[4] = 16;
					}
				}
			}
			break;
		case 13:
			{
				if(ban_warning_flag==0)
				{		
					if(ball_point.y<35)
					{
						tempForm[1] = 3;
						tempForm[2] = 22;
					}
					else
					{
						if(down==-1)
						{
							tempForm[1] = 16;
							tempForm[2] = 22;
						}
						else
						{
							tempForm[1] = 22;
							tempForm[2] = 16;
						}
					}
					tempForm[3] = 21;
					tempForm[4] = 7;
				}
				else//ban_warning_flag!=0
				{
					tempForm[1] = 21;
					tempForm[2] = 7;
					if(ball_point.y<35)
					{
						tempForm[3] = 3;
						tempForm[4] = 22;
					}
					else
					{
						if(down==-1)
						{
							tempForm[3] = 16;
							tempForm[4] = 22;
						}
						else
						{
							tempForm[3] = 22;
							tempForm[4] = 16;
						}
					}
				}
			}
			break;
		case 14:
			{
				if(ban_warning_flag==0)
				{
					tempForm[1] = 1;
					tempForm[2] = 22;
					tempForm[3] = 21;
					tempForm[4] = 7;
				}
				else
				{
					tempForm[1] = 21;
					tempForm[2] = 7;
					tempForm[3] = 1;
					tempForm[4] = 22;
				}
			}
			break;
		case 15:
			{
				if(ball_point.y>=140)
				{
					tempForm[1] = 20;
					tempForm[2] = 8;            
					tempForm[3] = 3;
					tempForm[4] = 5;
				}
				else
				{
					tempForm[1] = 32;
					tempForm[2] = 33;				
					/*if(ball.x<53)//////
					{
					if(down==1)
					{
					tempForm[3] = 16;
					tempForm[4] = 15;
					}
					else
					{
					tempForm[3] = 15;
					tempForm[4] = 16;
					}
					}
					else
					{
					tempForm[3] = 3;
					tempForm[4] = 68;//60;
					}
					*/
					if(down==1)
					{
						tempForm[3] = 16;
						tempForm[4] = 15;
					}
					else
					{
						tempForm[3] = 15;
						tempForm[4] = 16;
					}
				}
			}
			break;
		case 16:
			{	
				if(ball_point.y <= 40)
				{
					tempForm[1] = 21;
					tempForm[2] = 7;		
					tempForm[3] = 3;
					tempForm[4] = 6;//(40,45)45
				}
				else
				{
					tempForm[1] = 32;
					tempForm[2] = 33;				
					/*if(ball.x<53)
					{
					if(down==-1)
					{
					tempForm[3] = 15;
					tempForm[4] = 16;
					}
					else
					{
					tempForm[3] = 16;
					tempForm[4] = 15;
					}
					}
					else
					{
					tempForm[3] = 3;
					tempForm[4] = 68;//60;
					}
					*/
					if(down==-1)
					{
						tempForm[3] = 15;
						tempForm[4] = 16;
					}
					else
					{
						tempForm[3] = 16;
						tempForm[4] = 15;
					}
				}
			}
			break;
		case 17:
			{		
				tempForm[1] = 32;	
				tempForm[2] = 33;
				tempForm[3] = 1;
				tempForm[4] = 68;
			}
			break;
		case 19:
			{
				if(ball_point.x<110)
				{
					tempForm[1] = 32;	
					tempForm[2] = 33;
					tempForm[3] = 2;
					tempForm[4] = 68;
					if(ball_point.x<90)
					{
						tempForm[1] = 32;	
						tempForm[2] = 33;
						tempForm[3] = 2;
						if(down==1)
						{
							tempForm[4] = 16;
						}
						else
						{
							tempForm[4] = 15;
						}
						
					}
				}
				else if(ball_point.x<140)
				{
					if(flag == true)
					{
						tempForm[1] = 32;
						tempForm[2] = 2;
						tempForm[3] = 33;
						tempForm[4] = 68;
					}
					else
					{
						tempForm[1] = 2;
						tempForm[2] = 32;
						tempForm[3] = 68;//68
						tempForm[4] = 33;
					}
				}
				else //>140
				{
					tempForm[1] = 32;				
					tempForm[2] = 2;
					tempForm[3] =68 ;
					tempForm[4] = 33;
				}
			}
			break;
		case 21:
			{
				tempForm[1] = 32;	
				tempForm[2] = 33;
				tempForm[3] = 1;
				tempForm[4] = 68;
			}
			break;
		case 22:
			{
				tempForm[1] = 2;
				tempForm[2] = 68;
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 23:
			{	
				tempForm[1] = 2;
				tempForm[2] = 68;
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 24:
			{				
				tempForm[1] = 2;
				tempForm[2] = 68;
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 25:
			{
				tempForm[1] = 2;
				tempForm[2] = 68;//68
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 26:
			{
				tempForm[1] = 1;
				tempForm[2] = 68;//68
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 27:
			{
				tempForm[1] = 1;
				tempForm[2] = 68;//68
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 28:
			{
				tempForm[1] = 2;
				tempForm[2] = 68;
				tempForm[3] = 32;
				tempForm[4] = 33;			
			}
			break;
		case 29:
			{			
				tempForm[1] = 1;
				tempForm[2] = 68;//68
				tempForm[3] = 32;		
				tempForm[4] = 33;
			}
			break;
		case 30:
			{
				tempForm[1] = 1;
				tempForm[2] = 68;//68
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 31:
			{	
				tempForm[1] = 32;
				tempForm[2] = 1;		
				tempForm[3] = 68;//68					
				tempForm[4] = 33;						
			}
			break;
		case 32:
			{
				tempForm[1] = 32;
				tempForm[2] = 1;							
				tempForm[3] = 68;//68				
				tempForm[4] = 33;		
			}
			break;
		case 100:
			{
			/*	tempForm[1] = 39;
			tempForm[2] = 40;
			tempForm[3] = 46;
				tempForm[4] = 32;*/
				tempForm[1] = 39;
				tempForm[2] = 40;
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 101:
			{
			/*	tempForm[1] = 2;
			tempForm[2] = 40;
			tempForm[3] = 46;
				tempForm[4] = 32;*/
				tempForm[1] = 2;
				tempForm[2] = 68;
				tempForm[3] = 32;
				tempForm[4] = 33;
			}
			break;
		case 102:
			{
				tempForm[1] = 41;
				tempForm[2] = 2;
				tempForm[3] = 11;
				tempForm[4] = 32;
			}
			break;
		case 103:
			{
				tempForm[1] = 8;
				tempForm[2] = 7;
				tempForm[3] = 47;
				tempForm[4] = 48;
			}
			break;
		case 104:
			{
				tempForm[1] = 2;
				tempForm[2] = 64;
				tempForm[3] = 4;
				tempForm[4] = 23;
			}
			break;
		case 105:
			{
				tempForm[1] = 4;
				tempForm[2] = 64;
				tempForm[3] = 4;
				tempForm[4] = 23;
			}
			break;
		case 106:
			{
				
				tempForm[1] = 65;
				tempForm[2] = 32;
				if(ball_point.x>90)
					tempForm[3] = 68;
				else
					tempForm[3] = 33;
				tempForm[4] = 0;
			}
			break;
		case 107:
			{
				if(isAttack)
				{
					tempForm[1] = 46;
					tempForm[2] = 4;
					tempForm[3] = 60;
					tempForm[4] = 0;
				}
				else
				{
					tempForm[1] = 2;
					tempForm[2] = 2;
					tempForm[3] = 32;
					tempForm[4] = 33;
				}
			}
			break;
		case 108:
			{
				tempForm[1] = 43;
				tempForm[2] = 4;
				tempForm[3] = 60;
				tempForm[4] = 11;
			}
			break;
		case 109:
			{
				tempForm[1] = 44;
				tempForm[2] = 4;
				tempForm[3] = 60;
				tempForm[4] = 11;
			}
			break;
		default:
			{
				tempForm[1] = 2;
				tempForm[2] = 4;
				tempForm[3] = 15;
				tempForm[4] = 16;
			}
			break;
		}
		tempForm[ROBOTNUM] = 12;
		int i = 0;
		for ( i = 1; i < 6; i++)
		{
			if (tempForm[i] == 30 || tempForm[i] == 31)
			{
				if (tempForm[i] == 30)
				{
					if (ball_point.y > 125)
						tempForm[i] = 31;
				}
				else
				{
					if (ball_point.y < 55)
						tempForm[i] = 30;
				}
				break;
			}
			
		}	
        
		for ( i = 1; i < ROBOTNUM; i++)
		{
			currentForm[i] = tempForm[i];
		}
		
    }

    void charAllot()
    {
        double temp[6] = {0};
		for (short i = 1; i < ROBOTNUM; i++)
		{
			currentOrder[i] = 0;
		}

		for (short tempj = 1; tempj < ROBOTNUM; tempj++)
		{
			for (short tempi = 1; tempi < ROBOTNUM; tempi++)
			{
				temp[tempi] = charPerformance(currentForm[tempj], &my_robot_pose[tempi], tempi);
			}
			for (short i = 1; i <= tempj; i++)
			{
				currentOrder[tempj] = GetBestRobot(temp, currentForm[tempj]);
			}
		}
		
		currentOrder[ROBOTNUM] = 5;
    }
    void robotManager()
    {
		for(int tempi=1;tempi<=ROBOTNUM;tempi++)
		{
			currentResult[currentOrder[tempi]]=currentForm[tempi];
		}

	for(int tempi=1;tempi<=ROBOTNUM;tempi++)
	{
		oldForm[tempi] = currentForm[tempi];
		oldResult[tempi] = currentResult[tempi];
		oldOrder[tempi] = currentOrder[tempi];
		oldperfRecord[tempi] = perfRecord[tempi];
	}
    }
    void bestManager()
    {
		static  int ii=0,i27=0,i22=0;
		static  int  robotchar32=0,robotchar33=0,robotchar27=0,robotchar22=0;
		int i,k,count,count27,count22;
		int  bestResult[5];
		for(i=0;i<ROBOTNUM;i++)
		{
			bestResult[i]=0;
		}
		for(i=1;i<ROBOTNUM;i++)
		{
			bestResult[i]=currentResult[i];
		}
		count=0;
		for(i=1;i<ROBOTNUM;i++)
		{
			if(currentForm[i]==32)
				count++;
			if(currentForm[i]==33)
				count++;
		}
		
		////////////////////////////////////////////////////////
		
		if(charrobot==1&&count==2&&ForbinCount==0)
		{   
			if(ii==0)
			{
				for(k=1;k<ROBOTNUM;k++)
				{
					if(bestResult[k]==32)
					{
						robotchar32=k;
					}
					if(bestResult[k]==33)
					{
						robotchar33=k;
					}
				}
				ii++;          
			}
			else
			{ 
				for(i=1;i<ROBOTNUM;i++)
				{
					if(i==robotchar32)
						continue;
					else 
					{
						if(bestResult[i]==32)
						{
							bestResult[i]=bestResult[robotchar32];
							bestResult[robotchar32]=32;
						}
					}
				}
				for(i=1;i<ROBOTNUM;i++)
				{
					if(i==robotchar33)
						continue;
					else 
					{
						if(bestResult[i]==33)
						{
							bestResult[i]=bestResult[robotchar33];
							bestResult[robotchar33]=33;
						}	
					}
				}
				ii++; 
			}
			bestResult[robotchar32]=32;
			bestResult[robotchar33]=33;
			for(i=1;i<ROBOTNUM;i++)
			{
				currentResult[i]=bestResult[i];
			}	
		}
		else
		{   
			robotchar32=0;
			robotchar33=0;  
			ii=0;
			for(i=0;i<ROBOTNUM;i++)
				currentResult[i]=bestResult[i];  
		}
		
		for(i=0;i<ROBOTNUM;i++)
		{
			bestResult[i]=0;
		}
		for(i=1;i<ROBOTNUM;i++)
		{
			bestResult[i]=currentResult[i];
		}
		count27=0;
		
		for(i=1;i<ROBOTNUM;i++)
		{
			if(currentForm[i]==27)
				count27++;
		}
		int j=0;
		for(i=1;i<ROBOTNUM;i++)
		{
			if(130<my_robot_pose[i].y && my_robot_pose[i].y < 140 && my_robot_pose[i].x < 40)
			{
				j=1;
			}
		}
		if(count27==1&&j==1&&ForbinCount==0)//
		{
			if(i27==0)
			{
				for(k=1;k<ROBOTNUM;k++)
				{
					if(bestResult[k]==27)
					{
						robotchar27=k;
					}
					
				}
				i27++;          
			}
			else
			{
				for(i=1;i<ROBOTNUM;i++)
				{
					if(i==robotchar27)
						continue;
					else 
					{
						if(bestResult[i]==27)
						{
							bestResult[i]=bestResult[robotchar27];
							bestResult[robotchar27]=27;
						}
					}
				}
				i27++;
			}
			bestResult[robotchar27]=27;
			for(i=1;i<ROBOTNUM;i++)
			{
				currentResult[i]=bestResult[i];
			}
		}
		else
		{
			robotchar27=0;  
			i27=0;
			for(i=0;i<ROBOTNUM;i++)
				currentResult[i]=bestResult[i];  
		}

		for(i=0;i<ROBOTNUM;i++)
		{
			bestResult[i]=0;
		}
		for(i=1;i<ROBOTNUM;i++)
		{
			bestResult[i]=currentResult[i];
		}
		count22=0;
		
		for(i=1;i<ROBOTNUM;i++)
		{
			if(currentForm[i]==22)
				count22++;
		}
		int m=0;
		for(i=1;i<ROBOTNUM;i++)
		{
			if(40<my_robot_pose[i].y&&my_robot_pose[i].y<50&&my_robot_pose[i].x<40)
			{
				m=1;
			}
		}
		if(count22==1&&m==1&&ForbinCount==0)
		{
			if(i22==0)
			{
				for(k=1;k<ROBOTNUM;k++)
				{
					if(bestResult[k]==22)
					{
						robotchar22=k;
					}	
				}
				i22++;          
			}
			else
			{
				for(i=1;i<ROBOTNUM;i++)
				{
					if(i==robotchar22)
						continue;
					else 
					{
						if(bestResult[i]==22)
						{
							bestResult[i]=bestResult[robotchar22];
							bestResult[robotchar22]=22;
						}
					}
				}
				i22++;
			}
			bestResult[robotchar22]=22;
			for(i=1;i<ROBOTNUM;i++)
			{
				currentResult[i]=bestResult[i];
			}
		}
		else
		{
			robotchar22=0;  
			i22=0;
			for(i=0;i<ROBOTNUM;i++)
				currentResult[i]=bestResult[i];  
		}
    }
    void actProcess()
    {
		for(int i=1; i<=ROBOTNUM; i++)
		{
			rbV[i].LeftValue = 0;
			rbV[i].RightValue = 0;
		}
		currentResult[5] = 12;
		if(isStartGame)
		{
			for(int i=1; i<=ROBOTNUM; i++)
			{
				charInterpret(i, currentResult[i], &rbV[i]);
			}
		}
        
        return;
    }
int ClearBall(RobotPose *pRobot,
								BallPoint ball ,
								Velocity *pSpeed)
{
	Point goal;
	goal.x = wallright;
	goal.y = walltop/2;
		
	CS_ToPositionNew(pRobot,ball,goal,2,pSpeed);
		
	if(pRobot->x>ball.x)
	{
		Point pt;
		double det;
		det = 30;
		pt.x =ball.x +100;
			
		pt.y = 2*ball.y-pRobot->y;
		if(pt.y>ball.y)
			pt.y = ball.y + 5;
		else
			pt.y = ball.y - 5;
		if(ball.y<det)
			pt.y = ball.y - 5;
		else if(ball.y>walltop-det)
			pt.y = ball.y + 5;
			
		CS_ToPositionNew(pRobot,ball,pt,0,pSpeed);	
	}
	return 1;
}
double TNpara(int i,RobotPose myrobot,Point ball,Point goal,double dist,double angle)
{
	double tempp;
	tempp = 0;
	
	double distlimit1,distlimit2,ktheta,thetat2b,thetab2r,deltheta,anglelimit1,anglelimit2;
	Point rpt;
	rpt.x = myrobot.x;
	rpt.y = myrobot.y;
	anglelimit1 = Pi*0.6;
	
	anglelimit2 = Pi*0.06;
	
	distlimit1 = 50;
	distlimit2 = 10;
	
	thetat2b = Getpt2ptAngle(goal,ball);
	thetab2r = Getpt2ptAngle(ball,rpt);
	deltheta = cn_AngleTrim2PI(thetat2b-thetab2r);
	if(deltheta>Pi)
		deltheta -=2*Pi;
	ktheta =(distlimit1-distRobot2Pt(myrobot,ball))/(distlimit1-distlimit2);
	if(ktheta>1)
		ktheta = 1;
	if(ktheta<0)
		ktheta = 0;
	
	if(dist<=distlimit1)
	{
		tempp = (angle - anglelimit2)/(anglelimit1 - anglelimit2)*Pi/2;
		if(tempp>Pi/2)
			tempp = Pi/2;
		if(tempp <0)
			tempp = 0;
		tempp =ktheta*tempp;
	}
	return	tempp;
}
double TNpara(int i,RobotPose myrobot,BallPoint ball,Point goal,double dist,double angle)
{
	double tempp;
	tempp = 0;
	
	double distlimit1,distlimit2,ktheta,thetat2b,thetab2r,deltheta,anglelimit1,anglelimit2;
	Point rpt;
	rpt.x = myrobot.x;
	rpt.y = myrobot.y;
	anglelimit1 = Pi*0.6;
	
	anglelimit2 = Pi*0.06;
	
	distlimit1 = 50;
	distlimit2 = 10;
	
	thetat2b = Getpt2ptAngle(goal,ball);
	thetab2r = Getpt2ptAngle(ball,rpt);
	deltheta = cn_AngleTrim2PI(thetat2b-thetab2r);
	if(deltheta>Pi)
		deltheta -=2*Pi;
	ktheta =(distlimit1-distRobot2Pt(myrobot,ball))/(distlimit1-distlimit2);
	if(ktheta>1)
		ktheta = 1;
	if(ktheta<0)
		ktheta = 0;
	
	if(dist<=distlimit1)
	{
		tempp = (angle - anglelimit2)/(anglelimit1 - anglelimit2)*Pi/2;
		if(tempp>Pi/2)
			tempp = Pi/2;
		if(tempp <0)
			tempp = 0;
		tempp =ktheta*tempp;
	}
	return	tempp;
}
int ToPositionNew(RobotPose* robot, Point ball,Point directionpt, double samespeed, 
									int IfEndprocess,Velocity* pSpeed)
{
	//-----------------------------------------
	if (samespeed>=75)//65
	{
		samespeed=75;
	}
	//-----------------------------------------
	int vemax;
	vemax = 120;
	double dist;
	double Dx,Dy;
	double Anglerb2ball;
	
	double delta,angletemp;
	double kp4new = 15.0;
	delta = 6.5;
	
	angletemp = Getpt2ptAngle(ball,directionpt);
	//ball.x = ball.x - delta*sin(angletemp);
	//ball.y = ball.y + delta*cos(angletemp);
	
	
	ball.y = 180 - ball.y;
	directionpt.y = 180 - directionpt.y;
	robot->y = 180 - robot->y;
	robot->theta = 2*Pi - robot->theta;
	robot->theta = cn_AngleTrim2PI(robot->theta);
	

	Dx = ball.x - robot->x;
	Dy = ball.y - robot->y;
	dist = sqrt(Dx*Dx+Dy*Dy);
	Anglerb2ball = atan2(Dy ,Dx);
	Anglerb2ball = cn_AngleTrim2PI(Anglerb2ball);
	

	double Angleball2dpt;
	Dx = directionpt.x - ball.x;
	Dy = directionpt.y - ball.y;
	Angleball2dpt = atan2(Dy ,Dx);
	Angleball2dpt = cn_AngleTrim2PI(Angleball2dpt);
	

	double angle;
	angle = Angleball2dpt - Anglerb2ball;
	angle = cn_AngleTrim2PI(angle);
	if(angle >Pi)//(-Pi~Pi)
		angle -=2*Pi;
	double sign;
	if(angle>0)
		sign =1;
	else 
		sign =-1;
	

	double disiredAngle;
	disiredAngle = Anglerb2ball - sign*TNpara(IfEndprocess,*robot,ball,directionpt,distRobot2Pt(*robot,ball),fabs(angle));
	disiredAngle = cn_AngleTrim2PI(disiredAngle);
	

	double Angle_e;
	Angle_e = disiredAngle - robot->theta;
	Angle_e = cn_AngleTrim2PI(Angle_e);
	

	double ka,la;
	la = Pi*0.5;
	if(robot->x<7||robot->x>wallright-7.0||robot->y<7||robot->y>walltop-7.0)
		la = Pi*0.27;
	
	ka=samespeed;
	

	if(ballCharacter.velocity>0.5)
	{
		double d_BallVelAngle;
		d_BallVelAngle = cn_AngleTrim2PI(ballCharacter.angle);
		double k1,k2;
		k1 = ballCharacter.velocity*24*cos(d_BallVelAngle)+ka*cos(disiredAngle);
		k2 = ballCharacter.velocity*24*sin(d_BallVelAngle)+ka*sin(disiredAngle);
		disiredAngle = atan2(k2,k1);
		disiredAngle = cn_AngleTrim2PI(disiredAngle);
		ka = sqrt(k1*k1+k2*k2);
		if(ka>90) ka = 90;
	}
}

int ToPositionNew(RobotPose* robot, BallPoint ball,Point directionpt, double samespeed, 
									int IfEndprocess,Velocity* pSpeed)
{
	//-----------------------------------------
	if (samespeed>=75)//65
	{
		samespeed=75;
	}
	//-----------------------------------------
	int vemax;
	vemax = 120;
	double dist;
	double Dx,Dy;
	double Anglerb2ball;
	
	double delta,angletemp;
	double kp4new = 15.0;
	delta = 6.5;
	
	angletemp = Getpt2ptAngle(ball,directionpt);
	//ball.x = ball.x - delta*sin(angletemp);
	//ball.y = ball.y + delta*cos(angletemp);
	
	
	ball.y = 180 - ball.y;
	directionpt.y = 180 - directionpt.y;
	robot->y = 180 - robot->y;
	robot->theta = 2*Pi - robot->theta;
	robot->theta = cn_AngleTrim2PI(robot->theta);
	

	Dx = ball.x - robot->x;
	Dy = ball.y - robot->y;
	dist = sqrt(Dx*Dx+Dy*Dy);
	Anglerb2ball = atan2(Dy ,Dx);
	Anglerb2ball = cn_AngleTrim2PI(Anglerb2ball);
	

	double Angleball2dpt;
	Dx = directionpt.x - ball.x;
	Dy = directionpt.y - ball.y;
	Angleball2dpt = atan2(Dy ,Dx);
	Angleball2dpt = cn_AngleTrim2PI(Angleball2dpt);
	

	double angle;
	angle = Angleball2dpt - Anglerb2ball;
	angle = cn_AngleTrim2PI(angle);
	if(angle >Pi)//(-Pi~Pi)
		angle -=2*Pi;
	double sign;
	if(angle>0)
		sign =1;
	else 
		sign =-1;
	

	double disiredAngle;
	disiredAngle = Anglerb2ball - sign*TNpara(IfEndprocess,*robot,ball,directionpt,distRobot2Pt(*robot,ball),fabs(angle));
	disiredAngle = cn_AngleTrim2PI(disiredAngle);
	

	double Angle_e;
	Angle_e = disiredAngle - robot->theta;
	Angle_e = cn_AngleTrim2PI(Angle_e);
	

	double ka,la;
	la = Pi*0.5;
	if(robot->x<7||robot->x>wallright-7.0||robot->y<7||robot->y>walltop-7.0)
		la = Pi*0.27;
	
	ka=samespeed;
	

	if(ballCharacter.velocity>0.5)
	{
		double d_BallVelAngle;
		d_BallVelAngle = cn_AngleTrim2PI(ballCharacter.angle);
		double k1,k2;
		k1 = ballCharacter.velocity*24*cos(d_BallVelAngle)+ka*cos(disiredAngle);
		k2 = ballCharacter.velocity*24*sin(d_BallVelAngle)+ka*sin(disiredAngle);
		disiredAngle = atan2(k2,k1);
		disiredAngle = cn_AngleTrim2PI(disiredAngle);
		ka = sqrt(k1*k1+k2*k2);
		if(ka>90) ka = 90;
	}
}

int OutOfForbbidenZone(RobotPose robot, Point &pt)
{
	double dJiontPt_y;//,dJiontPt_x;
	dJiontPt_y = (35-pt.x)*(robot.y-pt.y)/(robot.x-pt.x)+pt.y;
	//	dJiontPt_x = (130-pt.y)*(robot.x-pt.x)/(robot.y-pt.y)+pt.x;
	if(dJiontPt_y>50&&dJiontPt_y<130&&(robot.x-35)*(pt.x-35)<0)
	{
		if(robot.x<35)
		{
			if(robot.y>130)
			{
				pt.x = 40;
				pt.y = 135;
			}
			else if(robot.y<50)
			{
				pt.x = 40;
				pt.y = 45;
			}
		}
		else //robot.x>=35
		{
			if(pt.y>130)
			{
				pt.x = 40;
				pt.y = 135;
			}
			else if(pt.y<50)
			{
				pt.x = 40;
				pt.y = 45;
			}
		}
	}
	if(robot.x<35&&pt.x<35)
	{
		if(pt.y>130&&(pt.y-130)*(robot.y-130)<0)
		{
			pt.x = 40;
			pt.y = 135;
		}
		else if(pt.y<50&&(pt.y-50)*(robot.y-50)<0)
		{
			pt.x = 40;
			pt.y = 45;
		}
	}
	return 1;
}

int AvoidSelfBump(RobotPose *robot,Point	directionpt,int	flag, Velocity	*pSpeed)
{
	int i,samespeed;
	if(flag!=0)
		samespeed = 0;
	else
		samespeed = 15;
	
	robot->theta = cn_AngleTrim2PI(robot->theta);
	for(i=1;i<=ROBOTNUM;i++)
	{
		double dx1,dy1,dx,dy;
		dx1 = Robot[i].x - robot->x;
		dy1 = Robot[i].y - robot->y;
		if(dx1==0&&dy1==0)
			continue;
		dx = dx1*cos(robot->theta - Pi/2) + dy1*sin(robot->theta - Pi/2);
		dy = -dx1*sin(robot->theta - Pi/2) + dy1*cos(robot->theta - Pi/2);
		if(fabs(dy)<8&&fabs(dx)<7)
		{
			if(pSpeed->LeftValue+pSpeed->RightValue>5)
			{
				if(dx<0&&dy>0)
				{
					pSpeed->LeftValue = samespeed;
					pSpeed->RightValue = -samespeed;
				}
				else if(dx>0&&dy>0)
				{
					pSpeed->LeftValue = -samespeed;
					pSpeed->RightValue = samespeed;
				}
			}
			else if(pSpeed->LeftValue+pSpeed->RightValue<-5)
			{
				if(dx>0&&dy<0)
				{
					pSpeed->LeftValue = samespeed;
					pSpeed->RightValue = -samespeed;
				}
				else if(dx>0&&dy>0)
				{
					pSpeed->LeftValue = -samespeed;
					pSpeed->RightValue = samespeed;
				}
			}
			break;
		}
	}
	return 1;
}
int ToPositionNPTC(RobotPose* robot,Point directionpt, double samespeed, Velocity* pSpeed)
{
	//--------------------------------------------------------
    if (samespeed >= 75)
	{
		samespeed=75;
	}
	//--------------------------------------------------------
	int vemax;
	vemax = 110;
	double dist;
	double Dx,Dy;
	double Anglerb2target;
	
	robot->y = 180 - robot->y;
	robot->theta = 2*Pi - robot->theta;
	directionpt.y = 180 - directionpt.y;
	robot->theta = cn_AngleTrim2PI(robot->theta);
	
	Dx = directionpt.x - robot->x;Dy = directionpt.y - robot->y;
	dist = sqrt(Dx*Dx+Dy*Dy);
	
	if(distRobot2Pt(*robot,directionpt)<30)
		samespeed = 60*distRobot2Pt(*robot,directionpt)/30;
	//   samespeed = 40+distRobot2Pt(*robot,directionpt)/2;
	
	double kp4new;
	
	
	kp4new = 10.0;//15.0
	
	Anglerb2target = atan2(Dy ,Dx);
	Anglerb2target = cn_AngleTrim2PI(Anglerb2target);
	
	double disiredAngle;
	disiredAngle = Anglerb2target;
	disiredAngle = cn_AngleTrim2PI(disiredAngle);
	//����Ƕ�ƫ��
	double Angle_e;
	Angle_e = disiredAngle - robot->theta;
	Angle_e = cn_AngleTrim2PI(Angle_e);

	
	double ka,limitation,a;
	a = Pi*0.3;//0.4
	limitation = 100;
	ka=samespeed;
	double speed_e;
	if(Angle_e <= Pi/2)//�Ƕ�ƫ���ڵ�һ����
	{
		speed_e = kp4new*Angle_e;
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Angle_e)>0)
			samespeed = ka*(a-fabs(Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
	}
	else if(Angle_e <= Pi)
	{
		speed_e = kp4new*(Pi - Angle_e);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Pi-Angle_e)>0)
			samespeed = ka*(a-fabs(Pi-Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}
	else if(Angle_e<3*Pi/2)
	{
		speed_e = kp4new*(Angle_e - Pi);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Angle_e - Pi)>0)
			samespeed = ka*(a-fabs(Angle_e - Pi))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}
	else
	{
		speed_e = kp4new*(2*Pi - Angle_e);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(2*Pi - Angle_e)>0)
			samespeed = ka*(a-fabs(2*Pi - Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
	}
	
	if(pSpeed->LeftValue>vemax)
	{
		pSpeed->LeftValue = vemax;
		pSpeed->RightValue = pSpeed->LeftValue - fabs(speed_e);
	}
	if(pSpeed->LeftValue<-vemax)
	{
		pSpeed->LeftValue = -vemax;
		pSpeed->RightValue = pSpeed->LeftValue + fabs(speed_e);
	}
	if(pSpeed->RightValue<-vemax)
	{
		pSpeed->RightValue = -vemax;
		pSpeed->LeftValue = pSpeed->RightValue + fabs(speed_e);
	}
	if(pSpeed->RightValue>vemax)
	{
		pSpeed->RightValue = vemax;
		pSpeed->LeftValue = pSpeed->RightValue - fabs(speed_e);
	}
	//����ԭ����
	robot->y = 180 - robot->y;
	robot->theta = 2*Pi - robot->theta;
	directionpt.y = 180 - directionpt.y;
	robot->theta = cn_AngleTrim2PI(robot->theta);
	return 1;
}
int AvoidALLRobotsM(RobotPose *robot, Point directionpt, double samespeed, double endspeed, Velocity *pSpeed)
{
    if (samespeed >= 100)
	{
		samespeed=100;	//55
	}
	
	//�ϰ��ﻮ��
	Point Obstacle[24]{};
	int i;
	for(i=1;i<=ROBOTNUM;i++)
	{
		Obstacle[i].x = opp_robot_point[i].x;
		Obstacle[i].y = opp_robot_point[i].y;
	}
	for(int j=1;j<=ROBOTNUM;j++)
	{
		if(Robot[j].x==robot->x&&Robot[j].y == robot->y)
			continue;
		else
		{
			Obstacle[i].x = Robot[j].x;
			Obstacle[i].y = Robot[j].y;
			i++;
		}
	}
	int count=0,flag[10] = {0};
	double d_Dist;
	for(i=1;i<9;i++)
	{
		for(int j=i+1;j<=9;j++)
		{
			//���ϰ�������
			d_Dist = sqrt((Obstacle[i].x-Obstacle[j].x)*(Obstacle[i].x-Obstacle[j].x)
				+(Obstacle[i].y-Obstacle[j].y)*(Obstacle[i].y-Obstacle[j].y));
			if(d_Dist<16)
			{
				//���������һ����ϰ���
				if(flag[i]==0&&flag[j]==0)
				{
					flag[i] = flag[j] = count+1;
					count++;
				}
				else if(flag[i]!=0&&flag[j]!=0)
				{
					if(flag[i]>flag[j])
						flag[i] = flag[j];
					else
						flag[j] = flag[i];
				}
				else
				{
					if(flag[i]==0)
						flag[i] = flag[j];
					else
						flag[j] = flag[i];
				}
			}
		}
	}
	
	//����������ϰ�������а뾶����ֵ������radius[i]��
	double radius[6] = {15,15,15,15,15,15};//Ϊ11��11���ã�5V5ֻ��3��	12
	Point CenterPt[6] = {};
	int i_Count[6] = {0},i_ORobotInformation[6] = {0};
	for(i=1;i<=9;i++)
	{
		switch (flag[i])
		{
			//Ĭ��ֵΪ0
			//5:5�����ֻ��2�飬11:11���������5�飬����case��5
		case 1:
			{
				CenterPt[1].x += Obstacle[i].x;
				CenterPt[1].y += Obstacle[i].y;
				i_Count[1]++;
				i_ORobotInformation[1] = i;
			}
			break;
		case 2:
			{
				CenterPt[2].x += Obstacle[i].x;
				CenterPt[2].y += Obstacle[i].y;
				i_Count[2]++;
				i_ORobotInformation[2] = i;
			}
			break;
		case 3:
			{
				CenterPt[3].x += Obstacle[i].x;
				CenterPt[3].y += Obstacle[i].y;
				i_Count[3]++;
				i_ORobotInformation[3] = i;
			}
			break;
		case 4:
			{
				CenterPt[4].x += Obstacle[i].x;
				CenterPt[4].y += Obstacle[i].y;
				i_Count[4]++;
				i_ORobotInformation[4] = i;
			}
			break;
		default:
			break;
		}
	}
	//5:5�����ֻ��2�飬11:11���������5�飬����case��5
	//i��ѭ���յ㼴Ϊ�����ϰ���������2��ȡ����ֵ
	for(i=1;i<=4;i++)
	{
		CenterPt[i].x = CenterPt[i].x/i_Count[i];
		CenterPt[i].y = CenterPt[i].y/i_Count[i];
		radius[i] = 0;
		for(int j=1;j<=9;j++)
		{
			if(flag[j]==i && radius[i]<cn_2PointsDist(Obstacle[j],CenterPt[i]))
			{
				radius[i] = cn_2PointsDist(Obstacle[j],CenterPt[i]);
			}
		}
		radius[i] = radius[i]+12;
	}
	//�ƿ��ϰ���
	double trantheta,dx,dy,temp=200;
	int k = 100;	//������¼�ϰ���
	Point Robot,ORobot[11];
	
	Robot.x = robot->x;
	Robot.y = robot->y;
	trantheta = atan2(directionpt.y-robot->y,directionpt.x-robot->x);
	trantheta = cn_AngleTrim2PI(trantheta);
	trantheta = trantheta - Pi/2;
	trantheta = cn_AngleTrim2PI(trantheta);
	for(i=1;i<=9;i++)
	{
		if(flag[i]!=0)
		{
			dx = CenterPt[flag[i]].x - robot->x;
			dy = CenterPt[flag[i]].y - robot->y;
		}
		else
		{
			dx = Obstacle[i].x - robot->x;
			dy = Obstacle[i].y - robot->y;
		}
		ORobot[i].x = dx*cos(trantheta) + dy*sin(trantheta);
		ORobot[i].y = -dx*sin(trantheta) + dy*cos(trantheta);
		if(fabs(ORobot[i].x)< radius[flag[i]]&&ORobot[i].y>0&&ORobot[i].y<temp)
		{
			temp = ORobot[i].y;
			k = i;
		}
	}
	/////////////////////////���ϰ취//////////////////////////////////////////
	if(k<=9&&temp>0&&temp+5<distRobot2Pt(*robot,directionpt))
	{
		Point pt1,pt2,tranPt1,tranPt2,TargetPt;
		bool bWhitchPt;
		pt1.x = ORobot[k].x - radius[flag[k]];
		pt2.x = ORobot[k].x + radius[flag[k]];
		pt1.y = pt2.y = ORobot[k].y;
		tranPt1.x = pt1.x*cos(trantheta) - pt1.y*sin(trantheta) + robot->x;
		tranPt1.y = pt1.x*sin(trantheta) + pt1.y*cos(trantheta) + robot->y;
		tranPt2.x = pt2.x*cos(trantheta) - pt2.y*sin(trantheta) + robot->x;
		tranPt2.y = pt2.x*sin(trantheta) + pt2.y*cos(trantheta) + robot->y;
		if(ORobot[k].x>=0)
		{
			TargetPt.x = tranPt1.x;
			TargetPt.y = tranPt1.y;
			bWhitchPt = 1;
		}
		else
		{
			TargetPt.x = tranPt2.x;
			TargetPt.y = tranPt2.y;	
			bWhitchPt = 0;
		}
		//���߽紦��
		if( TargetPt.x<8 || TargetPt.x>212 || TargetPt.y<8 || TargetPt.y>172)
		{
			if(bWhitchPt)
			{
				TargetPt.x = tranPt2.x;
				TargetPt.y = tranPt2.y;
				bWhitchPt = 0;
			}
			else
			{
				TargetPt.x = tranPt1.x;
				TargetPt.y = tranPt1.y;
				bWhitchPt = 1;
			}
		}
		if(ORobot[k].y<20)
		{
			//���㷨
			Point TempPt1,TempPt2,TranTempPt1,TranTempPt2;
			if(bWhitchPt)
			{
				TempPt1.x = pt1.x;
				TempPt1.y = pt1.y - radius[flag[k]]/2;
				TempPt2.x = pt1.x;
				TempPt2.y = pt1.y + radius[flag[k]]/2;
				TranTempPt1.x = TempPt1.x*cos(trantheta) - TempPt1.y*sin(trantheta) + robot->x;
				TranTempPt1.y = TempPt1.x*sin(trantheta) + TempPt1.y*cos(trantheta) + robot->y;
				TranTempPt2.x = TempPt2.x*cos(trantheta) - TempPt2.y*sin(trantheta) + robot->x;
				TranTempPt2.y = TempPt2.x*sin(trantheta) + TempPt2.y*cos(trantheta) + robot->y;
			}
			else
			{
				TempPt1.x = pt2.x;
				TempPt1.y = pt2.y - radius[flag[k]]/2;
				TempPt2.x = pt2.x;
				TempPt2.y = pt2.y + radius[flag[k]]/2;
				TranTempPt1.x = TempPt1.x*cos(trantheta) - TempPt1.y*sin(trantheta) + robot->x;
				TranTempPt1.y = TempPt1.x*sin(trantheta) + TempPt1.y*cos(trantheta) + robot->y;
				TranTempPt2.x = TempPt2.x*cos(trantheta) - TempPt2.y*sin(trantheta) + robot->x;
				TranTempPt2.y = TempPt2.x*sin(trantheta) + TempPt2.y*cos(trantheta) + robot->y;
			}
			
			
			if(distRobot2Pt(*robot,TranTempPt1)<20)	//10
				//	ToPositionPD(robot,TranTempPt2,samespeed,30,pSpeed);
                ToPositionPD(robot,TranTempPt2,70,30,pSpeed);
			else
				//	ToPositionPD(robot,TranTempPt1,samespeed,30,pSpeed);
				ToPositionPD(robot,TranTempPt2,70,30,pSpeed);
			return 1;
		}
		else//���㷨
		{
			//	ToPositionPD(robot,TargetPt,samespeed,30,pSpeed);
            ToPositionPD(robot,TargetPt,70,30,pSpeed);
		}
	}
	else
		ToPositionPD(robot,directionpt,samespeed+20,endspeed,pSpeed);
	//ToPositionN(robot,directionpt,50,pSpeed);
	   return 0;
	   return 1;
}

int ToPositionPDchampion(RobotPose* pROBOTPOSTURE,Point Target,double RobotV, double end_speed,Velocity* pLRWheelVelocity)
{                                                                             //vBase��ʹС�����ﶨ��ʱ����һ�����ٶ�
    //if (same_speed > 120)	//70 
		//same_speed = 120;


	double same_speed;
	double samespeed;
	int clock_sign,move_sign;
	double theta,theta_e1;			//e1Ϊ��ǰ�Ƕ����
	double dx,dy,dx1,dy1,distance;
	double speed;
	double Kp;

	//����任����С������Ϊԭ�㣬С������Ϊy��
	dx1=Target.x-pROBOTPOSTURE->x;
	dy1=Target.y-pROBOTPOSTURE->y;
	dx=dx1*cos(pROBOTPOSTURE->theta-Pi/2)+dy1*sin(pROBOTPOSTURE->theta-Pi/2);
	dy=-dx1*sin(pROBOTPOSTURE->theta-Pi/2)+dy1*cos(pROBOTPOSTURE->theta-Pi/2);
	theta=atan2(dy,dx);				//Ŀ���ķ����


	distance = sqrt(dx*dx+dy*dy);
	if(distance>=170)
	{
		samespeed=100;
	}
	else if(distance>=130)
	{
        samespeed = 0.16*distance+69.2;
	}
	else
	{
        samespeed = 0.576*distance+15.12;
	}
	if(RobotV<=samespeed)
	{
		same_speed = samespeed;
	}
	else
	{
		same_speed = RobotV;
	}
	double distancelimit;
	if(RobotV<=60)
	{
		distancelimit = 0.332675*RobotV-1.13025;
		if(RobotV<10)
			distancelimit = 2;
	}
	else
	{
        distancelimit = RobotV - 45;
	}

    //if(end_speed>same_speed)
	   //end_speed=same_speed;
	//if(distance > m_MoveParameter.max_distance)	//	75.0*Pi/180.0
	if(distance>distancelimit)
		speed = same_speed;		
	else //�������Լ���
		//speed = distance/m_MoveParameter.max_distance*same_speed;
		speed = RobotV*(4/5)*distance/distancelimit;
	
	//���ٲ���
	if(RobotV < end_speed) 
		speed = end_speed;
		
	/////////////////////////////////////

    
    if(distance>25)
	{
	
			if(fabs(fabs(theta)-Pi/2)<0.15*Pi)
			{
				theta = cn_AngleTrim2PI(theta);
				if(theta <= Pi/2)//��һ����
				{
					move_sign = 1;
					clock_sign = 1;
					theta_e1 = Pi/2 - theta;
				}
				else if(theta <= Pi)//�ڶ�����
				{
					move_sign = 1;
					clock_sign = -1;
					theta_e1 = theta - Pi/2;
				}
				else if(theta <= 3*Pi/2)//��������
				{
					move_sign = -1;
					clock_sign = 1;
					theta_e1 = 3*Pi/2 - theta;
				}
				else//��������
				{
					move_sign = -1;
					clock_sign = -1;
					theta_e1 = theta - 3*Pi/2;
				}
				Kp=(45/Pi)*theta_e1+5.5;

				//pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e1));
				//pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e1));
				pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(Kp*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e1));
				pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(Kp*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e1));
                
				//���汾���ڽǶ�����һ������΢����	
				theta_e1=theta_e1;
				
			}
			else
			{
				double sp=45;
				double angle_e=fabs(fabs(theta)-Pi/2);
				double r=30/angle_e;
				double d=7.5;
				theta = cn_AngleTrim2PI(theta-Pi/2);
				if(theta<Pi/2)
				{
					pLRWheelVelocity->LeftValue = sp*(r-d/2)/r;
	     			pLRWheelVelocity->RightValue = sp*(r+d/2)/r;
				}
				else if(theta<Pi)
				{
					pLRWheelVelocity->LeftValue = -sp*(r-d/2)/r;
	     			pLRWheelVelocity->RightValue = -sp*(r+d/2)/r;
				}
				else if(theta<Pi*1.5)
				{
					pLRWheelVelocity->LeftValue = -sp*(r+d/2)/r;
	     			pLRWheelVelocity->RightValue = -sp*(r-d/2)/r;
				}
				else
				{
					pLRWheelVelocity->LeftValue = sp*(r+d/2)/r;
	     			pLRWheelVelocity->RightValue = sp*(r-d/2)/r;
				}
				
			}
		
	}
	else
	{
		if(fabs(fabs(theta)-Pi/2)>m_AngleParameter.MaxAngle)
		{
		    TurnToPointPD(pROBOTPOSTURE,Target,NOCLOCK,pLRWheelVelocity);
		    pLRWheelVelocity->LeftValue /= 2.2;		//2
		    pLRWheelVelocity->RightValue /= 2.2;
			
		  return 0;
		}
             theta = cn_AngleTrim2PI(theta);
				if(theta <= Pi/2)//��һ����
				{
					move_sign = 1;
					clock_sign = 1;
					theta_e1 = Pi/2 - theta;
				}
				else if(theta <= Pi)//�ڶ�����
				{
					move_sign = 1;
					clock_sign = -1;
					theta_e1 = theta - Pi/2;
				}
				else if(theta <= 3*Pi/2)//��������
				{
					move_sign = -1;
					clock_sign = 1;
					theta_e1 = 3*Pi/2 - theta;
				}
				else//��������
				{
					move_sign = -1;
					clock_sign = -1;
					theta_e1 = theta - 3*Pi/2;
				}
                Kp=(45/Pi)*theta_e1+5.5;
				//pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e1));
				//pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e1));
                pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(Kp*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e1));
				pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(Kp*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e1));
				
				//���汾���ڽǶ�����һ������΢����	
				theta_e1=theta_e1;			
	}
  return 0;
}
int EndProcess_Forhit_mid(int i, RobotPose *pRobot, Point shoot_target, BallPoint ballPt, Velocity *pSpeed)
{
	static int time = 0;
	   static int endtimes=15;
	   double	r,dist,distE,anglerb2ball,anglerb2target,angle1,angle2,angle3,angleball2target,maxe,maxd,maxspeed;
	   Point rbPt,EGoal;
	   maxspeed = 160;//120
	   EGoal.x = wallright + 3.0;
	   EGoal.y = walltop/2;
	   
	   maxd = 11;//12
	   maxe = 3.8;	//2.8;3.2
	   r = 3.4;
	   dist = distRobot2Pt(*pRobot,ballPt);//������С���ľ���
	   rbPt.x = pRobot->x;
	   rbPt.y = pRobot->y;
	   anglerb2ball = Getpt2ptAngle(rbPt,ballPt);//С��ָ����ķ���
	   anglerb2target = Getpt2ptAngle(rbPt,shoot_target);//С��ָ��Ŀ��ķ���
	   angleball2target = Getpt2ptAngle(ballPt,shoot_target);//��Ŀ�귽��
	   
	   angle1 = cn_AngleTrim2PI(anglerb2ball - anglerb2target);
	   
	   if(angle1>Pi&&angle1<=2*Pi)
		   angle1 =angle1 - 2*Pi;
	   
	   angle2 = cn_AngleTrim2PI(pRobot->theta);
	   angle3 = cn_AngleTrim2PI(angle2 - anglerb2ball);
	   ///////////////////////////////////////////
	   
	   EndProcessFlag = 0;
	   double kp=16;
	   
	   distE = fabs(dist*sin(angle3));

	   if(i==1 &&((dist<=maxd && distE<=maxe)||(endtimes<10)))//&&i>0
	   {
		   
		   double anglelimit,anglet1,anglet2,anglet3,kk;
		   //kk=0.75+time*0.01;
           // kk=0.92; 
		   kk=1;
		   //if(kk>1)
		   //	kk=1;
           // if(time>10)
		   //	anglelimit = (280-pRobot->x )/280*Pi*.15 + Pi*.18+(time-10)*0.015*Pi;
		   //	else
		   anglelimit = (200-pRobot->x )/200*Pi*.1 + Pi*.18+time*0.006*Pi;
		   if(anglelimit>Pi*.5)
			   anglelimit = Pi*.5;
		   Point pt1,pt2;
		   pt1.x = pt2.x = wallright;
		   
		   if(OpponentGoalKeeper.y!=0)
		   {
			   if(OpponentGoalKeeper.y>90)
			   {
				   pt1.y = CENTER_Y;
				   pt2.y = CENTER_Y-20.0;
			   }
			   else
			   {
				   pt1.y = CENTER_Y+20.0;
				   pt2.y = CENTER_Y;
			   }
		   }
		   else
		   {
			   pt1.y = CENTER_Y+20.0;
			   pt2.y = CENTER_Y-20.0;
		   }
		   
		   //��������
		   if(angle3<Pi*0.2&&angle3>=0||angle3>Pi*1.8&&angle3<2*Pi)
		   {
			   if(time<25)
				   time++;
			   double anglek;
			   anglek = cn_AngleTrim2PI(pRobot->theta - anglerb2target);
			   //xue
			   anglet1 = cn_AngleTrim2PI(pRobot->theta - Getpt2ptAngle(rbPt,pt1));
			   if(anglet1>Pi)
				   anglet1 -=2*Pi;
			   anglet2 = cn_AngleTrim2PI(pRobot->theta - Getpt2ptAngle(rbPt,pt2));
			   if(anglet2>Pi)
				   anglet2 -=2*Pi;
			   if(fabs(anglet1)>fabs(anglet2))
				   anglet3 = fabs(anglet2);
			   else
				   anglet3 = fabs(anglet1);
			   if(anglek>Pi)
				   anglek -=2*Pi;
			   
			   if(anglet3<anglelimit||anglet1*anglet2<0)
			   {
				   if(anglek>0)
				   {
					   if(anglek<Pi/2)
                           pSpeed->LeftValue =4.0*time+60.0;
					   
					   else
						   pSpeed->LeftValue = 100;
					   
					   pSpeed->RightValue = pSpeed->LeftValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
				   }
				   else 
				   {
					   if(anglek<Pi/2)
						   pSpeed->RightValue =4.0*time+60.0;
					   else
						   pSpeed->RightValue = 100;
					   pSpeed->LeftValue = pSpeed->RightValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
				   }
				   EndProcessFlag = 1;	
			   }
		   }
		   //��������
		   else if(angle3>0.8*Pi&&angle3<1.2*Pi)//&&i>0
		   {
			   if(time<25)
				   time++;
			   double anglek;
			   anglek = cn_AngleTrim2PI(pRobot->theta - anglerb2target+Pi);
			   //xue
			   anglet1 = cn_AngleTrim2PI(pRobot->theta - Getpt2ptAngle(rbPt,pt1)+Pi);
			   if(anglet1>Pi)
				   anglet1 -=2*Pi;
			   anglet2 = cn_AngleTrim2PI(pRobot->theta - Getpt2ptAngle(rbPt,pt2)+Pi);
			   if(anglet2>Pi)
				   anglet2 -=2*Pi;
			   if(fabs(anglet1)>fabs(anglet2))
				   anglet3 = fabs(anglet2);
              	else
					anglet3 = fabs(anglet1);	
               	if(anglek>Pi)
					anglek -=2*Pi;
				if(anglet3<anglelimit||(anglet1*anglet2<0))
				{
					if(anglek>0)
					{
						if(anglek<Pi/2)
                            pSpeed->RightValue =4.0*time+60.0;
						else
							pSpeed->RightValue = 100;//+time*0.6;
						
						pSpeed->RightValue = -pSpeed->RightValue;
                        pSpeed->LeftValue = pSpeed->RightValue*(Pi/2-kk*fabs(anglek))/(Pi/2);
					}
					else
					{
						if(anglek<Pi/2)
							pSpeed->LeftValue =4.0*time+60.0;
						else
							pSpeed->LeftValue = 100;
						pSpeed->LeftValue = -pSpeed->LeftValue;
                        pSpeed->RightValue = pSpeed->LeftValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
						
					} 
					EndProcessFlag = 1;	
				}
		   }
		   
		   if(i>0 && dist<=maxd && distE<=maxe) endtimes=0;
		   if(endtimes<10) endtimes++;
		   step=5;
		   
		}
		else
		{		
			if(endtimes==10&&(ball_point.x>115||ball_point.x<105))
				time=0;
			
		}	
		
        if(i==2&&(( dist<=maxd && distE<=maxe)||(endtimes<10)))//&&i>0
		{
			
			double anglelimit,kk;
			kk=1;
			anglelimit = (200-pRobot->x )/200*Pi*.1 + Pi*.18+time*0.006*Pi;
			if(anglelimit>Pi*.5)
				anglelimit = Pi*.5;
			
			//��������
			if(angle3<Pi*0.2&&angle3>=0||angle3>Pi*1.8&&angle3<2*Pi)
			{
				if(time<30)
					time++;
				double anglek;
				anglek = cn_AngleTrim2PI(pRobot->theta - anglerb2target);
				//xue
				if(anglek>Pi)
					anglek -=2*Pi;
				
				if(anglek<anglelimit)
				{
					if(anglek>0)
					{
						if(anglek<Pi/2)
							pSpeed->LeftValue =3.0*time+20.0;
						
						else
							pSpeed->LeftValue = 100;
						
						pSpeed->RightValue = pSpeed->LeftValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
					}
					else 
					{
						if(anglek<Pi/2)
							pSpeed->RightValue =3.0*time+20.0;
						else
							pSpeed->RightValue = 100;
						pSpeed->LeftValue = pSpeed->RightValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
					}
					EndProcessFlag = 1;	
				}
			}
			//��������
			else if(angle3>0.8*Pi&&angle3<1.2*Pi)//&&i>0
			{
				if(time<30)
					time++;
				double anglek;
				anglek = cn_AngleTrim2PI(pRobot->theta - anglerb2target+Pi);
				if(anglek>Pi)
					anglek -=2*Pi;
				if(anglek<anglelimit)
				{
					if(anglek>0)
					{
						if(anglek<Pi/2)
                            pSpeed->RightValue =3.0*time+20.0;
						else
							pSpeed->RightValue = 100;//+time*0.6;
						
						pSpeed->RightValue = -pSpeed->RightValue;
                        pSpeed->LeftValue = pSpeed->RightValue*(Pi/2-kk*fabs(anglek))/(Pi/2);
					}
					else
					{
						if(anglek<Pi/2)
							pSpeed->LeftValue =3.0*time+20.0;
						else
							pSpeed->LeftValue = 100;
						pSpeed->LeftValue = -pSpeed->LeftValue;
                        pSpeed->RightValue = pSpeed->LeftValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
						
					} 
					EndProcessFlag = 1;	
				}
			}
			
			if(i>0 && dist<=maxd && distE<=maxe) endtimes=0;
			if(endtimes<10) endtimes++;
			step=5;
			
		}
		else
		{		
			if(endtimes==10&&(ball_point.x>115||ball_point.x<105))
				time=0;
			
		}	
		
		
		//�Ƕ��ر�õĴ���
		//��������(ball.x<100||ball.x>140)&&
		
		if((angle3<Pi*0.2&&angle3>=0||angle3>Pi*1.8&&angle3<2*Pi)&&fabs(angle1)<Pi*0.45&&
			distE<=maxe&& dist<=maxd &&(angle2>=0&&angle2<=Pi*0.45||angle2>=Pi*1.55&&angle2<=2*Pi))
		{
			double temp;
			temp = pRobot->y+(wallright-pRobot->x)*tan(angle2);
			if(OpponentGoalKeeper.y!=0)
			{
				if((OpponentGoalKeeper.y>140 && temp>=110.0+4 && temp<=OpponentGoalKeeper.y-8)||
					(OpponentGoalKeeper.y<=140 && temp>=OpponentGoalKeeper.y+8&&temp<=170.0-4))
				{
					if(ball_point.x>280)
						pSpeed->LeftValue = pSpeed->RightValue = maxspeed;
					else
					{
                        pSpeed->LeftValue = pSpeed->RightValue = (120 - (154-ball_point.x)*0.5);
					}
				}
			}
			else
			{
				if(temp>=113&&temp<=176)
				{
					pSpeed->LeftValue = pSpeed->RightValue = maxspeed;
				}
			}
			EndProcessFlag = 1;
		}
		//��������(ball.x<100||ball.x>140)&&
		else if((angle3>Pi - Pi*0.2&&angle3<Pi+Pi*0.2)&&fabs(angle1)<Pi*0.45&&
			distE<=maxe&& dist<=maxd &&(angle2>=0&&angle2<=Pi*0.45||angle2>=Pi*1.55&&angle2<=2*Pi))
		{
			
		/* pSpeed->LeftValue = 0;
		pSpeed->RightValue =0;
			return 1;*/
			double temp;
			temp = pRobot->y+(wallright-pRobot->x)*tan(angle2);
			if(OpponentGoalKeeper.y!=0)
			{
				if((OpponentGoalKeeper.y>140 && temp>=110.0+4&&temp<=OpponentGoalKeeper.y-8)||
					(OpponentGoalKeeper.y<=140 && temp>=OpponentGoalKeeper.y+8&&temp<=170.0-4))
				{
					if(ball_point.x>280)
						pSpeed->LeftValue = pSpeed->RightValue = -maxspeed;
					else
					{
						pSpeed->LeftValue = pSpeed->RightValue = -(120 - (280-ball_point.x)*0.5);
						//	if(fabs(pSpeed->LeftValue)<=100)
						//	pSpeed->LeftValue = pSpeed->RightValue = -80;
					}
					//	if(time<2)
					//		pSpeed->LeftValue = pSpeed->RightValue = -(time/2*(fabs(pSpeed->LeftValue)-50)+50);
				}	
			}
			else
			{
				if(temp>=113 && temp<=167)
				{
					pSpeed->LeftValue = pSpeed->RightValue = -maxspeed;
				}
			}
			EndProcessFlag = 1;
		}
		zsg_time=time;	
		return 1;
}
double GetCrossPtWithGLLine()
{
	double detaX,target_y;
	/*	if(ball.x < 30 /*&& (ball.y < DN_LINE || ball.y > UP_LINE)*//*)
																	{
																	target_y = ball.y;
																	return target_y;
}*/
	if(fabs(ballCharacter.Formu.a/ballCharacter.Formu.b) > tan(75.0/180.0*Pi))
	{
		detaX = 7;
		//		target_y = ball.y;
		//		return target_y;
	}
    else if(fabs(ballCharacter.Formu.a/ballCharacter.Formu.b) > tan(50.0/180.0*Pi))
		detaX = 6;
	else if(fabs(ballCharacter.Formu.a/ballCharacter.Formu.b) > tan(35.0/180.0*Pi))
		detaX = 4;
	else if(fabs(ballCharacter.Formu.a/ballCharacter.Formu.b) > tan(20.0/180.0*Pi))
		detaX = 3;
	else
		detaX = 2;
	target_y = -(ballCharacter.Formu.a * (G_OFFSET + detaX) + ballCharacter.Formu.c)/ballCharacter.Formu.b;
	return target_y; 	
}
int GoalieAction(RobotPose* pRobotInford, 
								   BallPoint ball,
								   Velocity *pSpeed)
{
	int		gtError = 4;	
	Point	target,joinPt;
	Point	homePt;
	double	dx,dy,k_ball,SM_offset;
	int		goToken=0;	
	bool    IsGate = 0;//���Ƿ�������
	bool    IsFore = 0;//���Ƿ����������˶�
	bool    BallStop = 0;
	double speed =  60;//60.0;//����ٶ�
	SM_offset = 3.0;	
    homePt.x =  6.5;//3.5;		//6.5;
	homePt.y = CENTER_Y;//90
	
	target = homePt;
	pRobotInford->theta = cn_AngleTrim2PI(pRobotInford->theta);


	if(ball.x > CENTER_X)//110
	{
		target.y = (ball.y-90)*target.x/ball.x+90;	
		dx = pRobotInford->x - target.x;
		dy = pRobotInford->y - target.y;
		
		if(dx*dx + dy*dy >4)
		{
			ToPositionPDGoal(pRobotInford,target,speed,0.0,pSpeed);	
		}
		else
		{
			if(pRobotInford->theta < Pi)
				TurnToAnglePD(pRobotInford,Pi/2,NOCLOCK,pSpeed);
			else
				TurnToAnglePD(pRobotInford,3*Pi/2,NOCLOCK,pSpeed);
		}
	}

	else
	{
		//ȷ��Ŀ���
		if((oldBallPt[0].x > oldBallPt[3].x && oldBallPt[3].x > oldBallPt[6].x) && ballCharacter.velocity > 0)				 // GG new add
		{																//���Բ��ÿ���ballCharacter.velocity?
			IsFore = 1;//�������˶�
			target.y = GetCrossPtWithGLLine( );//-5//x = 0        �루G_OFFSET -5������X=0�Ľ���
			joinPt.y = GetCrossPtWithGLLine();//X=8.0 ��X=8�Ľ��� 
		}
		else
			target.y = ball.y;
		
		if(target.y <= GATE_UP_LINE+1 && target.y >= GATE_DN_LINE-1.0 ) 
			IsGate = 1;

		if (ballCharacter.Formu.b != 0.0)
		{
			k_ball = -ballCharacter.Formu.a/ballCharacter.Formu.b;
			BallStop = 0;
		}
		else
			BallStop = 1;

		if (ball.x < 15)
		{
			if(IsGate)//�������ſ���
			{
				goToken = 3;
				if (IsFore == 1)
					target.y = joinPt.y;
				else target.y = ball.y; 
				if(ball.x < pRobotInford->x+4)		
				{
					if (ball.y < 65 && pRobotInford->y > (ball.y+5))
					{
						goToken = 0;
					}
					else if (ball.y>115 && pRobotInford->y < (ball.y-5))
					{
						goToken = 0;
					}
					else
					{
						//??????
						if(pRobotInford->x>ball.x+2&&fabs(pRobotInford->y - ball.y)<7&&distRobot2Pt(*pRobotInford,ball) < 15)
						{

							pSpeed->LeftValue = pSpeed->RightValue = 0;

							return 1;
						}
						else
							//	goToken = 0;//ToPositionNew
							goToken = 5;
					}
				}
				else
				{
					goToken = 3;
					//speed = gVMAX;
					//speed =60;
				}
			}
			else
				goToken = 3;
			{
				if(ball.y < 55) 
				{
					target.y = 68;//GOALS_DN_LINE - glError 61
					goToken = 2;//goToken = 1; 
				}
				else if(ball.y > 125) 
				{
					target.y = 112;//GOALS_UP_LINE + glError 119
					goToken = 2;//goToken = 1;
				}
				else if(ball.y >=112)
				{
					target.y = ball.y;
					if (ball.x < pRobotInford->x+4)
					{
						if (BallStop == 1)
						{
							if (ball.y > pRobotInford->y+4)
								goToken = 4;//goToken = 4;//goToken = 0;
							else
							{
								goToken = 5;
							}
						}
						else if (k_ball>1)
						{
							if (ball.y > pRobotInford->y+4)
								goToken = 4;//goToken = 4;//goToken = 0;
							else
								goToken=5;////////////////////////////����
						}
						else
						{
							target.y = 112;
							goToken = 2;//goToken = 1;
						}
					}
					else
					{
						target.y = 112;
						goToken = 1;
					}
				}
				else if(ball.y <=68)
				{
					target.y = ball.y;
					if(ball.x < pRobotInford->x+4)
					{
						if (BallStop == 1)
						{
							if (ball.y < pRobotInford->y-4)
								goToken = 4;//	goToken = 4;//goToken = 0;
							else
							{
								goToken = 5;
							}
						}
						else if (k_ball<-1)
						{
							if (ball.y < pRobotInford->y-4)
								goToken = 4;//	goToken = 4;//goToken = 0;
							else
								goToken = 5;
						}
						else
						{
							target.y = 68;
							goToken = 2;//goToken = 1;
						}
					}
					else
					{
						target.y = 68;
						goToken = 1;
					}
				}
				else
				{
					target.y = ball.y;
					if(ball.x < pRobotInford->x+4)
					{
						if (ball.y < 70 && ball.y < pRobotInford->y-4) 
							goToken = 4;//goToken = 0;
						else
							goToken = 5;
						if (ball.y > 110 && ball.y > pRobotInford->y+4)
							goToken = 4;//goToken = 0;
						else
							goToken = 5;
					}
					else
						goToken = 3;
				}
			}
		}
		else if(ball.x < 30)//����<30����
		{
			if(IsGate)
			{
				goToken = 3;//move
				if (IsFore == 1)
					target.y = joinPt.y;
				else 
				{
					target.y = ball.y;
					if(target.y < double(GATE_DN_LINE) + gtError+3.0)
						target.y = double(GATE_DN_LINE) + gtError+0.0;//+3;
					
					if(target.y>GATE_UP_LINE - gtError-3.0)
						target.y=target.y = GATE_UP_LINE-gtError;//-3
				} 
			}
			else
			{
				goToken = 3;
				if(ball.y < 66)//GOALS_DN_LINE65
				{
					if(oldBallPt[3].x > oldBallPt[6].x && oldBallPt[3].y < oldBallPt[6].y)
						target.y = GATE_DN_LINE ;//- gtError;
					else
						target.y = GATE_DN_LINE ;//+ gtError+3;///////////
				}
				else if(ball.y > 114) //GOALS_UP_LINE115
				{
					if(oldBallPt[3].x > oldBallPt[6].x && oldBallPt[3].y > oldBallPt[6].y)
						target.y = GATE_UP_LINE ;//+ gtError;
					else
						target.y = GATE_UP_LINE ;//- gtError-3;
				}
				else
				{
					target.y = ball.y;
					if(target.y>GATE_UP_LINE- gtError-3)
						target.y =GATE_UP_LINE- gtError-3;
					if(target.y<GATE_DN_LINE + gtError+3.0)
						target.y=GATE_DN_LINE + gtError+3.0;
					
					goToken = 3;
				}
			}
		}
		else if(ball.x < homePt.x + 50)//����<55����
		{
			if(IsGate)
			{
				goToken = 3;
				if (IsFore == 1)
					target.y = joinPt.y;
				else 
				{
					target.y=ball.y;
					
					if(target.y <= GATE_DN_LINE + 8.0)
						target.y = GATE_DN_LINE + 4.0;//8
					
					if(target.y >= GATE_UP_LINE - 8.0)
						target.y = GATE_UP_LINE - 4.0;//8
				}
			}
			else
			{
				if(ball.y < GATE_DN_LINE) 
					target.y = GATE_DN_LINE + 4.0;//8
				else if(ball.y > GATE_UP_LINE) 
					target.y = GATE_UP_LINE - 4.0;//8
				else target.y = ball.y;
				goToken = 2;
			}
		}
		else if(ball.x < homePt.x + 70.0)//����<75����
		{				
			if(IsGate)
			{
				goToken = 2;
				if(target.y<GATE_DN_LINE + 12.0)
					target.y=GATE_DN_LINE + 6.0;//12
				if(target.y>GATE_UP_LINE - 12.0)
					target.y=GATE_UP_LINE - 6.0;//12
			}
			else
			{
				if(ball.y < GATE_DN_LINE) 
					target.y = GATE_DN_LINE + 6.0;//12	
				else if(ball.y > GATE_UP_LINE) 
					target.y = GATE_UP_LINE - 6.0;//12
				else target.y = ball.y;
				goToken = 2;
			}
		}
		else if(ball.x < homePt.x + 80)//����<85���� 
		{
			if(IsGate)
			{
				if(IsFore == 1)
				{
					if(target.y < CENTER_Y-10)
						target.y = GATE_DN_LINE + 10.0;//16
					else if(target.y > CENTER_Y+10.0)
						target.y = GATE_UP_LINE - 10.0;//16
					else target.y = ball.y;
				}
				else
				{
					target.y = CENTER_Y;
				}
			}
			else
			{
				target.y = ball.y;
				if(target.y < GATE_DN_LINE) 
					target.y = GATE_DN_LINE + 12.0;	
				if(target.y > GATE_UP_LINE) 
					target.y = GATE_UP_LINE - 12.0;
			}
			goToken = 2;
		}
		else //����<110����
		{
			if(IsGate)
				target.y = CENTER_Y;//90
			else
				target.y = ball.y;
			if(target.y < GATE_DN_LINE) //70
				target.y = GATE_DN_LINE + 12.0;//15	
			if(target.y > GATE_UP_LINE) 
				target.y = GATE_UP_LINE - 12.0;//15
			goToken = 2;
		}

		//����
		//点球
		//目前接受信息里面不包含点球方向信息，先不做这快
		/*if ((StartMode == PenaltyKick) && (isAttack != 1) && (timer>0) && (timer<25))
		{          
			if (dmDEG.DEDQSMDirect == 0)
			{
				target.y = 74;
				goToken = 1;
			}
			else if (dmDEG.DEDQSMDirect == 2) 
			{
				target.y = 106;
				goToken = 1;
			}
		}*/
		
		dx = pRobotInford->x - target.x;
		dy = pRobotInford->y - target.y;
		
		switch(goToken)
		{
		case 0:  // ����
			{
			Point tempPt;
			tempPt.x = homePt.x;
			//tempPt.x = G_OFFSET;//homePt.x + 5.0;
			if(ball.y < pRobotInford->y)
				tempPt.y = 60;//�ɷ�С
			else
				tempPt.y = 120;
			ToPositionNew(pRobotInford,target,tempPt, 60,0,pSpeed);//60
			break;

			}
		case 1: //��Ŀ���
			{if(defend_counter==0)
			{
				target.y = target.y-3;
			}
			if(dx*dx + dy*dy <2.0*2.0)
				ToPositionPDGoal(pRobotInford, target,speed,0.0,pSpeed);
			else
				ToPositionPDGoal(pRobotInford, target,speed,10.0,pSpeed);//20.0
			break;}

		case 2: //��Ŀ���
			ToPositionPDGoal(pRobotInford, target,speed,0.0,pSpeed);
			break;

		case 3://���ڳ�ǰ��x < 30��   ��Ŀ���
			if(dx*dx + dy*dy <2.0*2.0)//ֵ�ɷ�С5��5
				ToPositionPDGoal(pRobotInford, target,speed,0.0,pSpeed);
			else
			{
				dx = pRobotInford->x - ball.x;
				dy = pRobotInford->y - ball.y;
				if(sqrt(dx*dx + dy*dy) > 60)
				{
					if(ballCharacter.velocity < 8) 
						speed = gVMAX - 10.0;
					else 
						speed = gVMAX - 15.0;
					
					dx = pRobotInford->x - target.x;
					dy = pRobotInford->y - target.y;
					if(sqrt(dx*dx + dy*dy) > 20)
						speed = gVMAX - 10.0;
					//else speed = gVMAX - 30;
				}
				else
				{	
					dx = pRobotInford->x - target.x;
					dy = pRobotInford->y - target.y;
					if(ballCharacter.velocity > 12.5 || sqrt(dx*dx + dy*dy) > 13) 
						speed = gVMAX;
					else speed = gVMAX - 10;
				}
				if(ballCharacter.velocity > 15 && IsGate == 1) 
					speed = gVMAX ;
				if(ball.x < 10 && IsGate == 1)
					speed = gVMAX ;
				ToPositionPDGoal(pRobotInford, target,speed,20,pSpeed);
			}
			break;

		case 4:
			{Point tempBall,tempPt;
			tempPt.x = homePt.x;
			tempBall.x = homePt.x;
			if(ball.y < pRobotInford->y)
				tempBall.y = pRobotInford->y-2;
			else
				tempBall.y = pRobotInford->y+2;
			//tempPt.x = G_OFFSET;//homePt.x + 5.0;
			if(ball.y < pRobotInford->y)
				tempPt.y = 60;//�ɷ�С//60
			else
				tempPt.y = 120;
			//ToPositionNew(pRobotInford,target,tempPt,55.0,0,pSpeed);
			if (tempBall.y<60)
			{
				target.y = 68;
				ToPositionPDGoal(pRobotInford, target,speed,0.0,pSpeed);
			}
			else if (tempBall.y>120)
			{
				target.y = 112;
				ToPositionPDGoal(pRobotInford, target,speed,0.0,pSpeed);
			}
			else
				ToPositionNew(pRobotInford,tempBall,tempPt, 60,0,pSpeed);	//60
			break;}

		case 5://����������
			{Point tempPt1;
			//tempPt1.x = 25;//homePt.x + 5.0;
			tempPt1.x = homePt.x;
			if(ball.y < pRobotInford->y)
				tempPt1.y = 60;//�ɷ�С
			else
				tempPt1.y = 120;
			ToPositionNew(pRobotInford,target,tempPt1, 60,0,pSpeed);//60
			break;}

		case   6://���߲�����
            {Point tempPt2;
            tempPt2.x = homePt.x-1;
			double dx,dy;
			if(ball.y < pRobotInford->y)
			{
				tempPt2.y = 67;
			}
			else
			{
				tempPt2.y = 113;
			}
            dx = pRobotInford->x - tempPt2.x;
			dy = pRobotInford->y - tempPt2.y;
            if(fabs(dx*dx+dy*dy)<1*1)
			{
                ToPositionPDGoal(pRobotInford, tempPt2,speed,0.0,pSpeed);
			}
			else
			{
				TurnToAnglePD(pRobotInford,Pi/2,NOCLOCK,pSpeed);
			}
			
			break;}

        default:
			{break;}
		}
		
		dx = pRobotInford->x - target.x;
		dy = pRobotInford->y - target.y;
		if(dx*dx + dy*dy < 2.0*2.0)
			if(pRobotInford->theta < Pi)
				TurnToAnglePD(pRobotInford,Pi/2,NOCLOCK,pSpeed);
			else
				TurnToAnglePD(pRobotInford,3*Pi/2,NOCLOCK,pSpeed);
			////////////////     ײǽ����     /////////////////////////////
			if(pRobotInford->y > GATE_UP_LINE || pRobotInford->y < GATE_DN_LINE)
			{
				double theta = cn_AngleTrim2PI(pRobotInford->theta);
				if(theta < Pi/4 || (theta > Pi && theta - Pi < Pi/4))
					TurnToAnglePD(pRobotInford,Pi/2,ANTICLOCK,pSpeed);
				else if((2*Pi - theta) < Pi/4 || (theta < Pi && Pi - theta < Pi/4))
					TurnToAnglePD(pRobotInford,Pi/2,CLOCKWISE,pSpeed);
			}
			///////////////////////////////////////////////////////////////////////////////////
			if(ballCharacter.velocity<0.3&&ball.x>10&&ball.x<15&&ball.y>65&&ball.y<115)
				g_GoalKeeper++;
			else
				g_GoalKeeper = 0;
			if(g_GoalKeeper>200)
				g_timeflag = 15;
			if(g_timeflag>0)
			{
				Point tempPt;
				tempPt.x = ball.x;
				if(ball.y>pRobotInford->y)
				{
					pSpeed->LeftValue = -30;
					pSpeed->RightValue = 30;
				}
				else
				{
					pSpeed->LeftValue = 30;
					pSpeed->RightValue = -30;
				}
				g_timeflag--;
			}
	}
	return 1;
}

int Outofforbiddenzonezq(Point robotpt,ROSrect rect,int i,int sign,Point target,int *j,Point *pt)
{
    double a,b,c,d;
	int m;
	m=*j;
    //��������Χ
    a = double(rect.left)-i;//-8
	b = double(rect.bottom)-i;//40
	c = double(rect.right)+i;//45
	d = double(rect.top)+i;//140
	//ȷ���ӳ���
    Point  targetteam[4];
	targetteam[0].x=rect.right;//37
	targetteam[0].y=d+i;//148
    targetteam[1].x=rect.right;//37
	targetteam[1].y=b-i;//32
	targetteam[2].x=c+i;//53
	targetteam[2].y=d-i;//132
    targetteam[3].x=c+i;//53
	targetteam[3].y=b+i;//48
    
	if(sign==0)
	{
		*pt=target;
	}
	//�ܾ���ԭʼ�ܵ�������Ǹ���
	else
	{
		Point  targetpt;
		targetpt=targetteam[0];
		for(int i=1;i<4;i++)
		{
			if(cn_2PointsDist(*pt, targetpt)>cn_2PointsDist(*pt, targetteam[i])) 
			{
				targetpt=targetteam[i];
			}
		}
		*pt=targetpt;
		//�ܳ�ԭ���ľ��ε���߿��ټ�8���¾��ο����ɹ��ܳ�
		if(robotpt.x<c&&robotpt.y<d&&robotpt.y>b)
		{
			m=1;
		}
		else
		{
			m=0;
		}
	}
    *j=m;
	//����Ƿ��Ѿ�������
    
    return 1;
}

int AvoidBall(RobotPose *robot, BallPoint ball, Point pt, Velocity *pSpeed)
{
	//�ܿ���
	Point pt1;
	int det1,det2,det3,det4;
	det1 = 20;
	det2 = 40;
	det3 = 25;
	det4 = 30;
	if(fabs(robot->y - ball.y)<det1&&robot->x>ball.x&&robot->x<ball.x+det2&&pt.x<ball.x)
	{
		if(ball.y<det3)
		{
			pt1.x = ball.x-3;
			pt1.y = ball.y+det4;
			if(pt.y<pt1.y)
				ToPositionN(robot,pt1,80,pSpeed);
		}
		else if(ball.y>walltop-det3)
		{
			pt1.x = ball.x-3;
			pt1.y = ball.y-det4;
			if(pt.y>pt1.y)
				ToPositionN(robot,pt1,80,pSpeed);
		}
		else if(robot->y >= ball.y)
		{
			pt1.x = ball.x - 3;
			pt1.y = ball.y + det4;
			if(pt.y<pt1.y)
				ToPositionN(robot,pt1,80,pSpeed);
		}
		else 
		{
			pt1.x = ball.x - 3;
			pt1.y = ball.y - det4;
			if(pt.y>pt1.y)
				ToPositionN(robot,pt1,80,pSpeed);
		}
	}
	return 1;
}


int CS_ToPositionN1(RobotPose *robot, Point directionpt, BallPoint Obstacle, int TurnFlag, double TurnRadius, double samespeed,Velocity *pSpeed)
{
	if (samespeed >= 65)
	{
		samespeed=65;
	}
	//--------------------------------------------------------
	
	int vemax;
	vemax = 110;
	double dist;
	double Dx,Dy;
	double Anglerb2target;
	
	//��������˵�Ŀ���ĽǶ�
	Dx = directionpt.x - robot->x;
	Dy = directionpt.y - robot->y;
	dist = sqrt(Dx*Dx+Dy*Dy);
	
	if(distRobot2Pt(*robot,directionpt)<40)
		samespeed = 50*distRobot2Pt(*robot,directionpt)/40;
	
	double kp4new;
	
	kp4new = 10.0;
	
	//����targetpt��directionpt�ĽǶ�
	Anglerb2target = atan2(Dy ,Dx);
	Anglerb2target = cn_AngleTrim2PI(Anglerb2target);
	
	//�����¸����ڵ�Ŀ��Ƕ�
	double disiredAngle;
	disiredAngle = Anglerb2target;
	disiredAngle = cn_AngleTrim2PI(disiredAngle);
	
	//����Ƕ�ƫ��
	double Angle_e;
	Angle_e = disiredAngle - robot->theta;
	Angle_e = cn_AngleTrim2PI(Angle_e);
	//�����������ٶȲ������������ٶ�
	
	//�ƿ��ϰ���
	double trantheta,dx,dy,temp=200;
	int k = 10;
	Point Obpoint;
	
	trantheta = atan2(directionpt.y-robot->y,directionpt.x-robot->x);
	trantheta = cn_AngleTrim2PI(trantheta);
	dx = Obstacle.x - robot->x;
	dy = Obstacle.y - robot->y;
	Obpoint.x = dx*cos(trantheta - Pi/2) + dy*sin(trantheta - Pi/2);
	Obpoint.y = -dx*sin(trantheta - Pi/2) + dy*cos(trantheta - Pi/2);
	//if(fabs(ORobot.x)<15&&ORobot.y>0&&sqrt(ORobot.x*ORobot.x+ORobot.y*ORobot.y)<35)
	if(fabs(Obpoint.x)<TurnRadius&&Obpoint.y>0&&Obpoint.y<TurnRadius+10)
	{
		samespeed = 55;
		if(TurnFlag==1)//��ת
		{
			disiredAngle = atan2(Obpoint.x,-Obpoint.y);
			if(disiredAngle<0)
				disiredAngle += Pi;
			if(disiredAngle>Pi/2)
				disiredAngle = 0;
		}
		else if(TurnFlag==-1)//��ת
		{
			disiredAngle = atan2(Obpoint.x,-Obpoint.y);
			if(disiredAngle<0)
				disiredAngle += Pi;
			if(disiredAngle<Pi/2)
				disiredAngle = Pi;
		}
		else//�ͽ�ת
		{		
			disiredAngle = atan2(Obpoint.x,-Obpoint.y);
			/*	if(ORobot.x<0)
			disiredAngle = atan(-40/((ORobot.x+15)*Pi*sin(ORobot.y*Pi/20)));
			else 
			disiredAngle = atan(40/((15-ORobot.x)*Pi*sin(ORobot.y*Pi/20)));*/
			if(disiredAngle<0)
				disiredAngle += Pi;
		}
		robot->theta = cn_AngleTrim2PI(robot->theta)-trantheta+Pi/2;
		Angle_e = disiredAngle - cn_AngleTrim2PI(robot->theta);
		Angle_e = cn_AngleTrim2PI(Angle_e);
		if(Angle_e<= 0.5*Pi)
		{
			if(Angle_e>0.25*Pi)
				Angle_e =0.25*Pi; 
		}
		else if(Angle_e <= Pi)
		{
			if(Angle_e<0.75*Pi)
				Angle_e = 0.75*Pi;
		}
		else if(Angle_e <= 1.5*Pi)
		{
			if(Angle_e>1.25*Pi)
				Angle_e = 1.25*Pi;
		}	
		else
		{
			if(Angle_e<1.75*Pi)
				Angle_e = 1.75*Pi;
		}
	}
	
	
	
	double ka,limitation,a;
	a = Pi*0.4;
	limitation = 100;
	ka=samespeed;
	double speed_e;
	if(Angle_e <= Pi/2)//�Ƕ�ƫ���ڵ�һ����
	{
		speed_e = kp4new*Angle_e;
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Angle_e) > 0)
			samespeed = ka*(a-fabs(Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
	}
	else if(Angle_e <= Pi)
	{
		speed_e = kp4new*(Pi - Angle_e);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Pi-Angle_e)>0)
			samespeed = ka*(a-fabs(Pi-Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}
	else if(Angle_e<3*Pi/2)
	{
		speed_e = kp4new*(Angle_e - Pi);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Angle_e - Pi)>0)
			samespeed = ka*(a-fabs(Angle_e - Pi))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}
	else
	{
		speed_e = kp4new*(2*Pi - Angle_e);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(2*Pi - Angle_e)>0)
			samespeed = ka*(a-fabs(2*Pi - Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
	}
	
	if(pSpeed->LeftValue>vemax)
	{
		pSpeed->LeftValue = vemax;
		pSpeed->RightValue = pSpeed->LeftValue - fabs(speed_e);
	}
	if(pSpeed->LeftValue<-vemax)
	{
		pSpeed->LeftValue = -vemax;
		pSpeed->RightValue = pSpeed->LeftValue + fabs(speed_e);
	}
	if(pSpeed->RightValue<-vemax)
	{
		pSpeed->RightValue = -vemax;
		pSpeed->LeftValue = pSpeed->RightValue + fabs(speed_e);
	}
	if(pSpeed->RightValue>vemax)
	{
		pSpeed->RightValue = vemax;
		pSpeed->LeftValue = pSpeed->RightValue - fabs(speed_e);
	}
	
	return 1;
}

int AoidenterbiddenzoneLC(Point robotpt, ROSrect rect, int i, Point *pt)
{
	double a,b,c,d;
    //��������Χ
    a = rect.left;
	b = rect.bottom;
	c = rect.right;
	d = rect.top;
    Point pt1;
	pt1=*pt;
	//��������˺��ܵ㶼�ھ���ͬһ���ߵ���࣬��ֱ���˳�
	if((robotpt.x>c&&pt1.x>c)||(robotpt.x<a&&pt1.x<a)||(robotpt.y>d&&pt1.y>d)||(robotpt.y<b&&pt1.y<b))
	{
		
	}
	else
	{
		//ȷ����������Ŀ�������ߺ͸�������Ľ���
		LINEFORMULATION Line[4],robot2target;
		///////////////////////////////////////////
		StdLineForm(robotpt, pt1, &robot2target);
		///////////////////////////////////////////
		Line[0].a=0,Line[0].b=1,Line[0].c=-rect.top;
		Line[1].a=0,Line[1].b=1,Line[1].c=-rect.bottom;
		Line[2].a=1,Line[2].b=0,Line[2].c=-rect.left;
		Line[3].a=1,Line[3].b=0,Line[3].c=-rect.right;
		//////////////////////////////////////////////////
		//ȷ��������������α߿�����ֱ�ߵĽ���
		int j=0,k=0; 
		Point allcrosspt[4];
		for(k=0;k<4;k++)
		{
			allcrosspt[k].x=0;
			allcrosspt[k].y=0;
		}
		for(k=0;k<4;k++)
		{   
			Point target;
			if(cn_2LinesCrossPoint(&Line[k], &robot2target, &target)==1)
			{
				allcrosspt[j]=target;
				j++;
			}
		}
		//ȷ���ڽ����ڵ�Σ�ս���
		Point crosspt[4];
		int sign=0;
		for(k=0;k<2;k++)
		{
			crosspt[k].x=0;
			crosspt[k].y=0;
		}
		for(k=0;k<4;k++)
		{
			if((rect.left-1.0)<=allcrosspt[k].x&&(rect.right+1.0)>=allcrosspt[k].x
				&&(rect.bottom-1.0)<=allcrosspt[k].y&&(rect.top+1.0)>=allcrosspt[k].y)
			{
				crosspt[sign]=allcrosspt[k];
				sign++;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////
		//ȷ���ӳ���
		Point  targetteam[4];
		targetteam[0].x=c;
		targetteam[0].y=d+i;
		targetteam[1].x=c;
		targetteam[1].y=b-i;
		targetteam[2].x=c+i;
		targetteam[2].y=d+i;
		targetteam[3].x=c+i;
		targetteam[3].y=b-i;
		if(sign>1)/////////
		{
			Point  targetpt;
			targetpt=targetteam[0];
			for(k=1;k<4;k++)
			{
				if(cn_2PointsDist(pt1, targetpt)>cn_2PointsDist(pt1, targetteam[k])) 
				{
					targetpt=targetteam[k];
				}
			}
			if (pt1.x<c&&robotpt.x>c)
			{
				pt1.x=targetpt.x;	
			}
			//pt1.x=targetpt.x;
			if (pt1.x>c&&robotpt.x<c)
			{
				if (robotpt.y<=90)
				{
					pt1=targetteam[3];
				}
				else if(robotpt.y>90)
				{
					pt1=targetteam[2];
				}
			}
			if((crosspt[0].x-rect.right)*(crosspt[1].x-rect.right)>0)
			{
				if(targetpt.y>90)
				{
					//pt1.y=b-i; 
					pt1=targetteam[3];
				}
				else
				{
					//pt1.y=d+i;
					pt1=targetteam[2];
				}
			}
			//pt1.x=targetpt.x;	
		}	
		*pt=pt1;		
	}
	//Aoidenterbiddenzone(robotpt,rect,5,pt);
	return 1;

}



int AvoidSelfRobotsM(RobotPose *robot, Point directionpt, double samespeed, Velocity *pSpeed)
{
	if (samespeed >= 60)
	{
		samespeed=60;
	}
	//�ϰ��ﻮ��
	Point Obstacle[24]{};
	int i=1;
	for(int j=1;j<=ROBOTNUM;j++)
	{
		if(Robot[j].x==robot->x&&Robot[j].y == robot->y)
			continue;
		else
		{
			Obstacle[i].x = Robot[j].x;
			Obstacle[i].y = Robot[j].y;
			i++;
		}
	}
	int count=0,flag[6] = {0};
	double d_Dist;
	for(i=1;i<4;i++)
	{
		for(int j=i+1;j<=4;j++)
		{
			//���ϰ�������
			d_Dist = sqrt((Obstacle[i].x-Obstacle[j].x)*(Obstacle[i].x-Obstacle[j].x)
				+(Obstacle[i].y-Obstacle[j].y)*(Obstacle[i].y-Obstacle[j].y));
			if(d_Dist<16)
			{
				//���������һ����ϰ���
				if(flag[i]==0&&flag[j]==0)
				{
					flag[i] = flag[j] = count+1;
					count++;
				}
				else if(flag[i]!=0&&flag[j]!=0)
				{
					if(flag[i]>flag[j])
						flag[i] = flag[j];
					else
						flag[j] = flag[i];
				}
				else
				{
					if(flag[i]==0)
						flag[i] = flag[j];
					else
						flag[j] = flag[i];
				}
			}
		}
	}
	
	//����������ϰ�������а뾶����ֵ������radius[i]��
	double radius[6] = {12,12,12,12,12,12};//Ϊ11��11���ã�5V5ֻ��3��
	Point CenterPt[6] = {};
	int i_Count[6] = {0},i_ORobotInformation[6] = {0};
	for(i=1;i<=4;i++)
	{
		switch (flag[i])
		{
			//Ĭ��ֵΪ0
			//5:5�����ֻ��2�飬11:11���������5�飬����case��5
		case 1:
			{
				CenterPt[1].x += Obstacle[i].x;
				CenterPt[1].y += Obstacle[i].y;
				i_Count[1]++;
				i_ORobotInformation[1] = i;
			}
			break;
		case 2:
			{
				CenterPt[2].x += Obstacle[i].x;
				CenterPt[2].y += Obstacle[i].y;
				i_Count[2]++;
				i_ORobotInformation[2] = i;
			}
			break;
		default:
			break;
		}
	}
	//5:5�����ֻ��2�飬11:11���������5�飬����case��5
	for(i=1;i<=2;i++)
	{
		CenterPt[i].x = CenterPt[i].x/i_Count[i];
		CenterPt[i].y = CenterPt[i].y/i_Count[i];
		radius[i] = 0;
		for(int j=1;j<=5;j++)
		{
			if(flag[j]==i&&radius[i]<cn_2PointsDist(Obstacle[j],CenterPt[i]))
			{
				radius[i] = cn_2PointsDist(Obstacle[j],CenterPt[i]);
			}
		}
		radius[i] = radius[i]+12;
	}
	//�ƿ��ϰ���
	double trantheta,dx,dy,temp=200;
	int k = 10;
	Point Robot,ORobot[11];
	
	Robot.x = robot->x;
	Robot.y = robot->y;
	trantheta = atan2(directionpt.y-robot->y,directionpt.x-robot->x);
	trantheta = cn_AngleTrim2PI(trantheta);
	trantheta = trantheta - Pi/2;
	trantheta = cn_AngleTrim2PI(trantheta);
	for(i=1;i<5;i++)
	{
		if(flag[i]!=0)
		{
			dx = CenterPt[flag[i]].x - robot->x;
			dy = CenterPt[flag[i]].y - robot->y;
		}
		else
		{
			dx = Obstacle[i].x - robot->x;
			dy = Obstacle[i].y - robot->y;
		}
		ORobot[i].x = dx*cos(trantheta) + dy*sin(trantheta);
		ORobot[i].y = -dx*sin(trantheta) + dy*cos(trantheta);
		if(fabs(ORobot[i].x)<radius[flag[i]]&&ORobot[i].y>0&&ORobot[i].y<temp)
		{
			temp = ORobot[i].y;
			k = i;
		}
	}
	
	if(k<=5&&temp>0&&temp+5<distRobot2Pt(*robot,directionpt))
	{
		Point pt1,pt2,tranPt1,tranPt2,TargetPt;
		bool bWhitchPt;
		pt1.x = ORobot[k].x - radius[flag[k]];
		pt2.x = ORobot[k].x + radius[flag[k]];
		pt1.y = pt2.y = ORobot[k].y;
		tranPt1.x = pt1.x*cos(trantheta) - pt1.y*sin(trantheta) + robot->x;
		tranPt1.y = pt1.x*sin(trantheta) + pt1.y*cos(trantheta) + robot->y;
		tranPt2.x = pt2.x*cos(trantheta) - pt2.y*sin(trantheta) + robot->x;
		tranPt2.y = pt2.x*sin(trantheta) + pt2.y*cos(trantheta) + robot->y;
		if(ORobot[k].x>=0)
		{
			TargetPt.x = tranPt1.x;
			TargetPt.y = tranPt1.y;
			bWhitchPt = 1;
		}
		else
		{
			TargetPt.x = tranPt2.x;
			TargetPt.y = tranPt2.y;	
			bWhitchPt = 0;
		}
		
		//���߽紦��
		if( TargetPt.x<8 || TargetPt.x>212 || TargetPt.y<8 || TargetPt.y>172)
		{
			if(bWhitchPt)
			{
				TargetPt.x = tranPt2.x;
				TargetPt.y = tranPt2.y;
				bWhitchPt = 0;
			}
			else
			{
				TargetPt.x = tranPt1.x;
				TargetPt.y = tranPt1.y;
				bWhitchPt = 1;
			}
		}
		if(ORobot[k].y<30)
		{
			//���㷨
			Point TempPt1,TempPt2,TranTempPt1,TranTempPt2;
			if(bWhitchPt)
			{
				TempPt1.x = pt1.x;
				TempPt1.y = pt1.y - radius[flag[k]]/2;
				TempPt2.x = pt1.x;
				TempPt2.y = pt1.y + radius[flag[k]]/2;
				TranTempPt1.x = TempPt1.x*cos(trantheta) - TempPt1.y*sin(trantheta) + robot->x;
				TranTempPt1.y = TempPt1.x*sin(trantheta) + TempPt1.y*cos(trantheta) + robot->y;
				TranTempPt2.x = TempPt2.x*cos(trantheta) - TempPt2.y*sin(trantheta) + robot->x;
				TranTempPt2.y = TempPt2.x*sin(trantheta) + TempPt2.y*cos(trantheta) + robot->y;
			}
			else
			{
				TempPt1.x = pt2.x;
				TempPt1.y = pt2.y - radius[flag[k]]/2;
				TempPt2.x = pt2.x;
				TempPt2.y = pt2.y + radius[flag[k]]/2;
				TranTempPt1.x = TempPt1.x*cos(trantheta) - TempPt1.y*sin(trantheta) + robot->x;
				TranTempPt1.y = TempPt1.x*sin(trantheta) + TempPt1.y*cos(trantheta) + robot->y;
				TranTempPt2.x = TempPt2.x*cos(trantheta) - TempPt2.y*sin(trantheta) + robot->x;
				TranTempPt2.y = TempPt2.x*sin(trantheta) + TempPt2.y*cos(trantheta) + robot->y;
			}
			if(TempPt1.y<1)///distRobot2Pt(*robot,TranTempPt1)<10
				ToPositionPD(robot,TranTempPt2,samespeed,35,pSpeed);
			else
				ToPositionPD(robot,TranTempPt1,samespeed,35,pSpeed);
			return 1;
		}
		else//���㷨
		{
			ToPositionPD(robot,TargetPt,samespeed,35,pSpeed);
		}
		//		
	}
	else
		ToPositionPD(robot,directionpt,50,0,pSpeed);
	   return 0;
	   return 1;
}


int CS_ClearBall(RobotPose *pRobot, BallPoint ball, Velocity *pSpeed)
{
	Point goal;// ����λ����ΪĿ���
	goal.x = wallright;
	goal.y = walltop/2;
	
	if(ball.x<40)
	{
		Point pt;
		pt.x = 40;
		pt.y = ball.y;
		if(distRobot2Pt(*pRobot,pt)>3)
			ToPositionN(pRobot,pt,55,pSpeed);
		else
			TurnToAnglePD(pRobot,Pi/2,0,pSpeed);
		if(distRobot2Pt(*pRobot,ball)<8&&ball.x<pRobot->x)
		{
			if(ball.y>pRobot->y)
			{
				pSpeed->LeftValue = 15;
				pSpeed->RightValue = -15;
			}
			else
			{
				pSpeed->LeftValue = -15;
				pSpeed->RightValue = 15;
			}
		}
	}
	else if(ball.x<55&&ball.y<130&&ball.y>50)
	{
		Point pt;
		double det;
		det = 30;
		pt.x =40;
		if(pRobot->y>ball.y)//+5
		{	pt.y = 40;
		ToPositionNew(pRobot,ball,pt,55,0,pSpeed);
		}
		else //if(pRobot->y<ball.y-5)
		{
			pt.y = 140;
			ToPositionNew(pRobot,ball,pt,55,0,pSpeed);	
		}
		
	}
	else
		ToPositionNew(pRobot,ball,goal,70,2,pSpeed);
	return 1;
}

int ToPositionM(RobotPose* robot,Point directionpt, 
								  double samespeed, Velocity* pSpeed)
{
	//--------------------------------------------------------
    if (samespeed >= 90)//70
	{
		samespeed=90;
	}
	//--------------------------------------------------------
	
	int vemax;
	vemax = 110;
	double dist;
	double Dx,Dy;
	double Anglerb2target;
	
	robot->y = 180 - robot->y;
	robot->theta = 2*Pi - robot->theta;
	directionpt.y = 180 - directionpt.y;
	robot->theta = cn_AngleTrim2PI(robot->theta);
	//��������˵�Ŀ���ĽǶ�
	Dx = directionpt.x - robot->x;Dy = directionpt.y - robot->y;
	dist = sqrt(Dx*Dx+Dy*Dy);
	
	if(distRobot2Pt(*robot,directionpt)<30)
		samespeed = samespeed*distRobot2Pt(*robot,directionpt)/30;
	
	if(samespeed<ballCharacter.velocity*qiusubi+10)
		samespeed=ballCharacter.velocity*qiusubi+10;
	
	double kp4new;
	
	kp4new = 15.0;
	
	//����targetpt��directionpt�ĽǶ�
	Anglerb2target = atan2(Dy ,Dx);
	Anglerb2target = cn_AngleTrim2PI(Anglerb2target);
	
	//�����¸����ڵ�Ŀ��Ƕ�
	double disiredAngle;
	disiredAngle = Anglerb2target;
	disiredAngle = cn_AngleTrim2PI(disiredAngle);
	//����Ƕ�ƫ��
	double Angle_e;
	Angle_e = disiredAngle - robot->theta;
	Angle_e = cn_AngleTrim2PI(Angle_e);
	//�����������ٶȲ������������ٶ�
	
	double ka,limitation,a;
	a = Pi*0.4;
	limitation = 100;
	ka=samespeed;
	double speed_e;
	if(Angle_e <= Pi/2)//�Ƕ�ƫ���ڵ�һ����
	{
		speed_e = kp4new*Angle_e;
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Angle_e)>0)
			samespeed = ka*(a-fabs(Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
	}
	else if(Angle_e <= Pi)
	{
		speed_e = kp4new*(Pi - Angle_e);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Pi-Angle_e)>0)
			samespeed = ka*(a-fabs(Pi-Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}
	else if(Angle_e<3*Pi/2)
	{
		speed_e = kp4new*(Angle_e - Pi);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(Angle_e - Pi)>0)
			samespeed = ka*(a-fabs(Angle_e - Pi))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}
	else
	{
		speed_e = kp4new*(2*Pi - Angle_e);
		speed_e = Limit(speed_e,limitation);
		if(a-fabs(2*Pi - Angle_e)>0)
			samespeed = ka*(a-fabs(2*Pi - Angle_e))/a;
		else samespeed = 0;
		
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
	}
	
	if(pSpeed->LeftValue>vemax)
	{
		pSpeed->LeftValue = vemax;
		pSpeed->RightValue = pSpeed->LeftValue - fabs(speed_e);
	}
	if(pSpeed->LeftValue<-vemax)
	{
		pSpeed->LeftValue = -vemax;
		pSpeed->RightValue = pSpeed->LeftValue + fabs(speed_e);
	}
	if(pSpeed->RightValue<-vemax)
	{
		pSpeed->RightValue = -vemax;
		pSpeed->LeftValue = pSpeed->RightValue + fabs(speed_e);
	}
	if(pSpeed->RightValue>vemax)
	{
		pSpeed->RightValue = vemax;
		pSpeed->LeftValue = pSpeed->RightValue - fabs(speed_e);
	}
	robot->y = 180 - robot->y;
	robot->theta = 2*Pi - robot->theta;
	directionpt.y = 180 - directionpt.y;
	robot->theta = cn_AngleTrim2PI(robot->theta);
	return 1;
}

int Aoidenterbiddenzone(Point robotpt, ROSrect rect, int i, Point* pt)
{
	double a = 0, b = 0, c = 0, d = 0;
	//��������Χ
	a = rect.left;
	b = rect.bottom;
	c = rect.right;
	d = rect.top;
	Point pt1 = { 0,0 };
	pt1 = *pt;
	//��������˺��ܵ㶼�ھ���ͬһ���ߵ���࣬��ֱ���˳�
	if((robotpt.x>c&&pt1.x>c)||(robotpt.x<a&&pt1.x<a)||(robotpt.y>d&&pt1.y>d)||(robotpt.y<b&&pt1.y<b))
	{
		
	}
	else
	{
		//ȷ����������Ŀ�������ߺ͸�������Ľ���
		LINEFORMULATION Line[4],robot2target;
		///////////////////////////////////////////
		StdLineForm(robotpt, pt1, &robot2target);
		///////////////////////////////////////////
		Line[0].a=0,Line[0].b=1,Line[0].c=-rect.top;
		Line[1].a=0,Line[1].b=1,Line[1].c=-rect.bottom;
		Line[2].a=1,Line[2].b=0,Line[2].c=-rect.left;
		Line[3].a=1,Line[3].b=0,Line[3].c=-rect.right;
		//////////////////////////////////////////////////
		//ȷ��������������α߿�����ֱ�ߵĽ���
		int j=0,k=0; 
		Point allcrosspt[4];
		for(k=0;k<4;k++)
		{
			allcrosspt[k].x=0;
			allcrosspt[k].y=0;
		}
		for(k=0;k<4;k++)
		{   
			Point target;
			if(cn_2LinesCrossPoint(&Line[k], &robot2target, &target)==1)
			{
				allcrosspt[j]=target;
				j++;
			}
		}
		//ȷ���ڽ����ڵ�Σ�ս���
		Point crosspt[2];
		int sign=0;
		for(k=0;k<2;k++)
		{
			crosspt[k].x=0;
			crosspt[k].y=0;
		}
		for(k=0;k<4;k++)
		{
			if((rect.left-1.0)<=allcrosspt[k].x&&(rect.right+1.0)>=allcrosspt[k].x
				&&(rect.bottom-1.0)<=allcrosspt[k].y&&(rect.top+1.0)>=allcrosspt[k].y)
			{
				crosspt[sign]=allcrosspt[k];
				sign++;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////
		//ȷ���ӳ���
		Point  targetteam[4];
		targetteam[0].x=c;
		targetteam[0].y=d+i;
		targetteam[1].x=c;
		targetteam[1].y=b-i;
		targetteam[2].x=c+i;
		targetteam[2].y=d+i;
		targetteam[3].x=c+i;
		targetteam[3].y=b-i;
		if(sign>=2)
		{
			Point  targetpt;
			targetpt=targetteam[0];
			for(k=1;k<4;k++)
			{
				if(cn_2PointsDist(pt1, targetpt)>cn_2PointsDist(pt1, targetteam[k])) 
				{
					targetpt=targetteam[k];
				}
			}
			pt1.x=targetpt.x;	
			//
			if((crosspt[0].x-rect.right)*(crosspt[1].x-rect.right)>0)
			{
				if(targetpt.y>90)
				{
					//pt1.y=b-i; 
					pt1=targetteam[3];
				}
				else
				{
					//pt1.y=d+i;
					pt1=targetteam[2];
				}
			}
			//pt1.x=targetpt.x;	
		}	
		*pt=pt1;		
	}
	//Aoidenterbiddenzone(robotpt,rect,5,pt);
	return 1;
}


int AvoidALLRobots(RobotPose*robot, Point directionpt, double samespeed, Velocity *pSpeed)
{
	if (samespeed >= 60)
	{
		samespeed=60;
	}
	//�ϰ��ﻮ��
	Point Obstacle[24]{};
	int i;
	for(i=1;i<=ROBOTNUM;i++)
	{
		Obstacle[i].x = opp_robot_point[i].x;
		Obstacle[i].y = opp_robot_point[i].y;
	}
	for(int j=1;j<=ROBOTNUM;j++)
	{
		if(Robot[j].x==robot->x&&Robot[j].y == robot->y)
			continue;
		else
		{
			Obstacle[i].x = Robot[j].x;
			Obstacle[i].y = Robot[j].y;
			i++;
		}
	}
	int count=0,flag[10] = {0};
	double d_Dist;
	for(i=1;i<9;i++)
	{
		for(int j=i+1;j<=9;j++)
		{
			//���ϰ�������
			d_Dist = sqrt((Obstacle[i].x-Obstacle[j].x)*(Obstacle[i].x-Obstacle[j].x)
				+(Obstacle[i].y-Obstacle[j].y)*(Obstacle[i].y-Obstacle[j].y));
			if(d_Dist<16)
			{
				//���������һ����ϰ���
				if(flag[i]==0&&flag[j]==0)
				{
					flag[i] = flag[j] = count+1;
					count++;
				}
				else if(flag[i]!=0&&flag[j]!=0)
				{
					if(flag[i]>flag[j])
						flag[i] = flag[j];
					else
						flag[j] = flag[i];
				}
				else
				{
					if(flag[i]==0)
						flag[i] = flag[j];
					else
						flag[j] = flag[i];
				}
			}
		}
	}
	
	//����������ϰ�������а뾶����ֵ������radius[i]��
	double radius[6] = {12,12,12,12,12,12};//Ϊ11��11���ã�5V5ֻ��3��
	Point CenterPt[6] = {};
	int i_Count[6] = {0},i_ORobotInformation[6] = {0};
	for(i=1;i<=9;i++)
	{
		switch (flag[i])
		{
			//Ĭ��ֵΪ0
			//5:5�����ֻ��2�飬11:11���������5�飬����case��5
		case 1:
			{
				CenterPt[1].x += Obstacle[i].x;
				CenterPt[1].y += Obstacle[i].y;
				i_Count[1]++;
				i_ORobotInformation[1] = i;
			}
			break;
		case 2:
			{
				CenterPt[2].x += Obstacle[i].x;
				CenterPt[2].y += Obstacle[i].y;
				i_Count[2]++;
				i_ORobotInformation[2] = i;
			}
			break;
		case 3:
			{
				CenterPt[3].x += Obstacle[i].x;
				CenterPt[3].y += Obstacle[i].y;
				i_Count[3]++;
				i_ORobotInformation[3] = i;
			}
			break;
		case 4:
			{
				CenterPt[4].x += Obstacle[i].x;
				CenterPt[4].y += Obstacle[i].y;
				i_Count[4]++;
				i_ORobotInformation[4] = i;
			}
			break;
		default:
			break;
		}
	}
	//5:5�����ֻ��2�飬11:11���������5�飬����case��5
	//i��ѭ���յ㼴Ϊ�����ϰ���������2��ȡ����ֵ
	for(i=1;i<=4;i++)
	{
		CenterPt[i].x = CenterPt[i].x/i_Count[i];
		CenterPt[i].y = CenterPt[i].y/i_Count[i];
		radius[i] = 0;
		for(int j=1;j<=9;j++)
		{
			if(flag[j]==i&&radius[i]<cn_2PointsDist(Obstacle[j],CenterPt[i]))
			{
				radius[i] = cn_2PointsDist(Obstacle[j],CenterPt[i]);
			}
		}
		radius[i] = radius[i]+12;
	}
	//�ƿ��ϰ���
	double trantheta,dx,dy,temp=200;
	int k = 100;//������¼�ϰ���
	Point Robot,ORobot[11];
	
	Robot.x = robot->x;
	Robot.y = robot->y;
	trantheta = atan2(directionpt.y-robot->y,directionpt.x-robot->x);
	trantheta = cn_AngleTrim2PI(trantheta);
	trantheta = trantheta - Pi/2;
	trantheta = cn_AngleTrim2PI(trantheta);
	for(i=1;i<=9;i++)
	{
		if(flag[i]!=0)
		{
			dx = CenterPt[flag[i]].x - robot->x;
			dy = CenterPt[flag[i]].y - robot->y;
		}
		else
		{
			dx = Obstacle[i].x - robot->x;
			dy = Obstacle[i].y - robot->y;
		}
		ORobot[i].x = dx*cos(trantheta) + dy*sin(trantheta);
		ORobot[i].y = -dx*sin(trantheta) + dy*cos(trantheta);
		if(fabs(ORobot[i].x)< radius[flag[i]]&&ORobot[i].y>0&&ORobot[i].y<temp)
		{
			temp = ORobot[i].y;
			k = i;
		}
	}
	/////////////////////////���ϰ취//////////////////////////////////////////
	if(k<=9&&temp>0&&temp+5<distRobot2Pt(*robot,directionpt))
	{
		Point pt1,pt2,tranPt1,tranPt2,TargetPt;
		bool bWhitchPt;
		pt1.x = ORobot[k].x - radius[flag[k]];
		pt2.x = ORobot[k].x + radius[flag[k]];
		pt1.y = pt2.y = ORobot[k].y;
		tranPt1.x = pt1.x*cos(trantheta) - pt1.y*sin(trantheta) + robot->x;
		tranPt1.y = pt1.x*sin(trantheta) + pt1.y*cos(trantheta) + robot->y;
		tranPt2.x = pt2.x*cos(trantheta) - pt2.y*sin(trantheta) + robot->x;
		tranPt2.y = pt2.x*sin(trantheta) + pt2.y*cos(trantheta) + robot->y;
		if(ORobot[k].x>=0)
		{
			TargetPt.x = tranPt1.x;
			TargetPt.y = tranPt1.y;
			bWhitchPt = 1;
		}
		else
		{
			TargetPt.x = tranPt2.x;
			TargetPt.y = tranPt2.y;	
			bWhitchPt = 0;
		}
		//���߽紦��
		if( TargetPt.x<8 || TargetPt.x>212 || TargetPt.y<8 || TargetPt.y>172)
		{
			if(bWhitchPt)
			{
				TargetPt.x = tranPt2.x;
				TargetPt.y = tranPt2.y;
				bWhitchPt = 0;
			}
			else
			{
				TargetPt.x = tranPt1.x;
				TargetPt.y = tranPt1.y;
				bWhitchPt = 1;
			}
		}
		if(ORobot[k].y<30)
		{
			//���㷨
			Point TempPt1,TempPt2,TranTempPt1,TranTempPt2;
			if(bWhitchPt)
			{
				TempPt1.x = pt1.x;
				TempPt1.y = pt1.y - radius[flag[k]]/2;
				TempPt2.x = pt1.x;
				TempPt2.y = pt1.y + radius[flag[k]]/2;
				TranTempPt1.x = TempPt1.x*cos(trantheta) - TempPt1.y*sin(trantheta) + robot->x;
				TranTempPt1.y = TempPt1.x*sin(trantheta) + TempPt1.y*cos(trantheta) + robot->y;
				TranTempPt2.x = TempPt2.x*cos(trantheta) - TempPt2.y*sin(trantheta) + robot->x;
				TranTempPt2.y = TempPt2.x*sin(trantheta) + TempPt2.y*cos(trantheta) + robot->y;
			}
			else
			{
				TempPt1.x = pt2.x;
				TempPt1.y = pt2.y - radius[flag[k]]/2;
				TempPt2.x = pt2.x;
				TempPt2.y = pt2.y + radius[flag[k]]/2;
				TranTempPt1.x = TempPt1.x*cos(trantheta) - TempPt1.y*sin(trantheta) + robot->x;
				TranTempPt1.y = TempPt1.x*sin(trantheta) + TempPt1.y*cos(trantheta) + robot->y;
				TranTempPt2.x = TempPt2.x*cos(trantheta) - TempPt2.y*sin(trantheta) + robot->x;
				TranTempPt2.y = TempPt2.x*sin(trantheta) + TempPt2.y*cos(trantheta) + robot->y;
			}
			if(distRobot2Pt(*robot,TranTempPt1)<10)
				ToPositionPD(robot,TranTempPt2,samespeed,35,pSpeed);
			else
				ToPositionPD(robot,TranTempPt1,samespeed,35,pSpeed);
			return 1;
		}
		else//���㷨
		{
			ToPositionPD(robot,TargetPt,samespeed,35,pSpeed);
		}
	}
	else
		//ToPositionPD(robot,directionpt,50,0,pSpeed);
		return 0;
	return 1;
}

int ToPositionPDchampionnew(RobotPose* pROBOTPOSTURE,Point Target,double end_speed,
											  Velocity* pLRWheelVelocity)
{                                                                    
	double samespeed;
	int clock_sign,move_sign;
	double theta,theta_e1;			//e1Ϊ��ǰ�Ƕ����
	static double theta_e2 = 0;		//e2Ϊ��һ���ڽǶ����
	double dx,dy,dx1,dy1,distance;
	double speed;
	double Kp;
	
	//����任����С������Ϊԭ�㣬С������Ϊy��
	dx1=Target.x-pROBOTPOSTURE->x;
	dy1=Target.y-pROBOTPOSTURE->y;
	dx=dx1*cos(pROBOTPOSTURE->theta-Pi/2)+dy1*sin(pROBOTPOSTURE->theta-Pi/2);
	dy=-dx1*sin(pROBOTPOSTURE->theta-Pi/2)+dy1*cos(pROBOTPOSTURE->theta-Pi/2);
	theta=atan2(dy,dx);				//Ŀ���ķ����
	
	///////////////////////
	/////////�ٶȵ���//////////
	distance = sqrt(dx*dx+dy*dy);
	if(distance>=170)
	{
		samespeed=100;
	}
	else if(distance>=130)
	{
        samespeed = 0.16*distance+69.2;
	}
	else
	{
        samespeed = 0.576*distance+15.12;
	}
	
	//Զ�̸���
	//Ϊ��ʹ������ʱ����һ�����ٶ�,���������ķ���
	
	//if(distance > m_MoveParameter.max_distance)	//	75.0*Pi/180.0
	if(distance>15)
		speed = samespeed;		
	else //�������Լ���
		//speed = distance/m_MoveParameter.max_distance*same_speed;
		speed = samespeed*distance/15;
	
	//���ٲ���
	if(speed<end_speed)
	{
		speed=end_speed;
	}	
	
    if(distance>25)
	{	
		if(fabs(fabs(theta)-Pi/2)<0.15*Pi)
		{
			theta = cn_AngleTrim2PI(theta);
			if(theta <= Pi/2)//��һ����
			{
				move_sign = 1;
				clock_sign = 1;
				theta_e1 = Pi/2 - theta;
			}
			else if(theta <= Pi)//�ڶ�����
			{
				move_sign = 1;
				clock_sign = -1;
				theta_e1 = theta - Pi/2;
			}
			else if(theta <= 3*Pi/2)//��������
			{
				move_sign = -1;
				clock_sign = 1;
				theta_e1 = 3*Pi/2 - theta;
			}
			else//��������
			{
				move_sign = -1;
				clock_sign = -1;
				theta_e1 = theta - 3*Pi/2;
			}
			Kp=(45/Pi)*theta_e1+5.5;
			if(12>=Kp)
			{
				Kp=Kp;
			}
			else
			{
				Kp=12;
			}
			
			//pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e2));
			//pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e2));
			
			//��ֹ��
			if(Kp*theta_e1>vx/speed)
			{
				pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(vx/speed);
				pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(vx/speed);
			}
			else
			{
				pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(Kp*theta_e1);
				pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(Kp*theta_e1);
			}
			//���汾���ڽǶ�����һ������΢����	
			theta_e2=theta_e1;
		}

		else
		{
			double sp=45;
			double angle_e=fabs(fabs(theta)-Pi/2);
			double r=30/angle_e;
			double d=7.5;
			theta = cn_AngleTrim2PI(theta-Pi/2);
			if(theta<Pi/2)
			{
				pLRWheelVelocity->LeftValue = sp*(r-d/2)/r;
				pLRWheelVelocity->RightValue = sp*(r+d/2)/r;
			}
			else if(theta<Pi)
			{
				pLRWheelVelocity->LeftValue = -sp*(r-d/2)/r;
				pLRWheelVelocity->RightValue = -sp*(r+d/2)/r;
			}
			else if(theta<Pi*1.5)
			{
				pLRWheelVelocity->LeftValue = -sp*(r+d/2)/r;
				pLRWheelVelocity->RightValue = -sp*(r-d/2)/r;
			}
			else
			{
				pLRWheelVelocity->LeftValue = sp*(r+d/2)/r;
				pLRWheelVelocity->RightValue = sp*(r-d/2)/r;
			}	
		}	
	}

	else
	{
		if(fabs(fabs(theta)-Pi/2)>m_AngleParameter.MaxAngle)
		{
			TurnToPointPD(pROBOTPOSTURE,Target,NOCLOCK,pLRWheelVelocity);
			pLRWheelVelocity->LeftValue /= 2.2;		//2
			pLRWheelVelocity->RightValue /= 2.2;
			
			return 0;
		}
		theta = cn_AngleTrim2PI(theta);
		if(theta <= Pi/2)//��һ����
		{
			move_sign = 1;
			clock_sign = 1;
			theta_e1 = Pi/2 - theta;
		}
		else if(theta <= Pi)//�ڶ�����
		{
			move_sign = 1;
			clock_sign = -1;
			theta_e1 = theta - Pi/2;
		}
		else if(theta <= 3*Pi/2)//��������
		{
			move_sign = -1;
			clock_sign = 1;
			theta_e1 = 3*Pi/2 - theta;
		}
		else//��������
		{
			move_sign = -1;
			clock_sign = -1;
			theta_e1 = theta - 3*Pi/2;
		}
		Kp=(45/Pi)*theta_e1+5.5;
		if(12>=Kp)
			{
				Kp=Kp;
			}
			else
			{
				Kp=12;
			}
		//Kp=min(12,Kp);
		//pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e2));
		//pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e2));
		if(Kp*theta_e1>vx/speed)
		{
			pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(vx/speed);
			pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(vx/speed);
		}
		else
		{
			pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(Kp*theta_e1);
			pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(Kp*theta_e1);
		}
		//���汾���ڽǶ�����һ������΢����	
		theta_e2=theta_e1;
	}
	return 0;
}
void MidActAndDefend (RobotPose *pRobotInford,BallPoint ball,Velocity *pSpeed)
{
	Point  targetPt,crossPt;
	   Point  homePt;
	   double   speed=60;
	   double   detx=0,dety=0;
	   //  dbPOINT  ballPt;
	   bool     isUp=true,isBack=true,isStop=false; //������˶����ж�
	   homePt.x=125;
	   homePt.y=90;   //����Ȧ
	   
	   if(ball.y>90) 
		   isUp=true;
	   else 
		   isUp=false;
	   if(oldBallPt[0].x >oldBallPt[3].x && oldBallPt[3].x > oldBallPt[6].x ) 
		   isBack=true;
	   else   
		   isBack=false;
	   if (ballCharacter.Formu.b==0.0) 
		   isStop=true;
	   else
		   isStop=false;
	   
	   pRobotInford->theta =cn_AngleTrim2PI(pRobotInford->theta );
	   targetPt=homePt;
	   crossPt=homePt;
	   if (ball.x >125)
	   {
		   
		   if(isBack) //run to the target pt;
		   { 
			   crossPt.y =GetCrossPtWithGLLine();
			   targetPt.y =ball.y ;
			   if(!isStop) 
				   targetPt.y =crossPt.y ;
			   if(isUp) //just defend the upside;
			   {
				   if(targetPt.y>175)
					   targetPt.y =175;
				   else if(targetPt.y<90) 
					   targetPt.y =90;
			   }
			   else //just defend  the downside;
			   {
				   if(targetPt.y>90)
					   targetPt.y =90;
				   else if(targetPt.y<5) 
					   targetPt.y =5;
			   }
			   
			   
		   }
		   else //following the ball.y
		   {
			   targetPt.y =ball.y;
		   }
		   
		   ToPositionPDGoal(pRobotInford,targetPt,speed,ballCharacter.velocity,pSpeed);
		   
		   detx=targetPt.x-pRobotInford->x;
		   dety=targetPt.y-pRobotInford->y;
		   if((detx*detx+dety*dety)<=3.0*3.0)
		   {
			   if(pRobotInford->theta <Pi)
				   TurnToAnglePD(pRobotInford,Pi/2,NOCLOCK,pSpeed);
			   else
				   TurnToAnglePD(pRobotInford,3*Pi/2,NOCLOCK,pSpeed);
		   }
	   }
}
int ToPositionForShoot(RobotPose *robot, BallPoint directionpt, int Flag, 
										 double samespeed, Velocity *pSpeed)
{
	//--------------------------------------------------------
    if (samespeed >= 100)//90
	{
		samespeed= 100;
	}
	//--------------------------------------------------------
	int vemax;
	vemax = 110;
	double dist;
	double Dx,Dy;
	double Anglerb2target;
	robot->y = 180 - robot->y;
	robot->theta = 2*Pi - robot->theta;
	directionpt.y = 180 - directionpt.y;
	robot->theta = cn_AngleTrim2PI(robot->theta);
	//��������˵�Ŀ���ĽǶ�
	Dx = directionpt.x - robot->x;
	Dy = directionpt.y - robot->y;
	dist = sqrt(Dx*Dx+Dy*Dy);
	
	if(distRobot2Pt(*robot,directionpt)<20)
		//Flag==1�����ظ�
		if(Flag==1&&oldBallPt[0].x>oldBallPt[3].x&&oldBallPt[3].x>oldBallPt[6].x)
		{
			samespeed = samespeed*distRobot2Pt(*robot,directionpt)/20;
			if(samespeed<30+ballCharacter.velocity*qiusubi)
				samespeed=30+ballCharacter.velocity*qiusubi;
		}	
		else if(Flag==0&&oldBallPt[0].x<oldBallPt[3].x&&oldBallPt[3].x<oldBallPt[6].x)
		{
			samespeed = samespeed*distRobot2Pt(*robot,directionpt)/20+ballCharacter.velocity*qiusubi;
			//if(samespeed<45+ballCharacter.velocity*qiusubi)
			//	samespeed=45+ballCharacter.velocity*qiusubi;
		}
		else
		{
			samespeed = samespeed*distRobot2Pt(*robot,directionpt)/20;
			if(samespeed<35)
				samespeed = 35;
		}

		double kp4new;
		kp4new = 15.0;//15.0
		
		//����targetpt��directionpt�ĽǶ�
		Anglerb2target = atan2(Dy ,Dx);
		Anglerb2target = cn_AngleTrim2PI(Anglerb2target);
		
		//�����¸����ڵ�Ŀ��Ƕ�
		double disiredAngle;
		disiredAngle = Anglerb2target;
		disiredAngle = cn_AngleTrim2PI(disiredAngle);
		//����Ƕ�ƫ��
		double Angle_e;
		Angle_e = disiredAngle - robot->theta;
		Angle_e = cn_AngleTrim2PI(Angle_e);
		//�����������ٶȲ������������ٶ�
		
		double ka,limitation,a;
		a = Pi*0.4;//0.4
		limitation = 100;
		ka=samespeed;
		double speed_e;
		if(Angle_e <= Pi/2)//�Ƕ�ƫ���ڵ�һ����
		{
			speed_e = kp4new*Angle_e;
			speed_e = Limit(speed_e,limitation);
			if(a-fabs(Angle_e)>0)
				samespeed = ka*(a-fabs(Angle_e))/a;
			else samespeed = 0;
			
			pSpeed->LeftValue = samespeed + speed_e/2;
			pSpeed->RightValue = samespeed - speed_e/2;
		}
		else if(Angle_e <= Pi)
		{
			speed_e = kp4new*(Pi - Angle_e);
			speed_e = Limit(speed_e,limitation);
			if(a-fabs(Pi-Angle_e)>0)
				samespeed = ka*(a-fabs(Pi-Angle_e))/a;
			else samespeed = 0;
			
			pSpeed->LeftValue = samespeed + speed_e/2;
			pSpeed->RightValue = samespeed - speed_e/2;
			pSpeed->LeftValue =- pSpeed->LeftValue;
			pSpeed->RightValue =- pSpeed->RightValue;
		}
		else if(Angle_e<3*Pi/2)
		{
			speed_e = kp4new*(Angle_e - Pi);
			speed_e = Limit(speed_e,limitation);
			if(a-fabs(Angle_e - Pi)>0)
				samespeed = ka*(a-fabs(Angle_e - Pi))/a;
			else samespeed = 0;
			
			pSpeed->LeftValue = samespeed - speed_e/2;
			pSpeed->RightValue = samespeed + speed_e/2;
			pSpeed->LeftValue =- pSpeed->LeftValue;
			pSpeed->RightValue =- pSpeed->RightValue;
		}
		else
		{
			speed_e = kp4new*(2*Pi - Angle_e);
			speed_e = Limit(speed_e,limitation);
			if(a-fabs(2*Pi - Angle_e)>0)
				samespeed = ka*(a-fabs(2*Pi - Angle_e))/a;
			else samespeed = 0;
			
			pSpeed->LeftValue = samespeed - speed_e/2;
			pSpeed->RightValue = samespeed + speed_e/2;
		}
		
		if(pSpeed->LeftValue>vemax)
		{
			pSpeed->LeftValue = vemax;
			pSpeed->RightValue = pSpeed->LeftValue - fabs(speed_e);
		}
		if(pSpeed->LeftValue<-vemax)
		{
			pSpeed->LeftValue = -vemax;
			pSpeed->RightValue = pSpeed->LeftValue + fabs(speed_e);
		}
		if(pSpeed->RightValue<-vemax)
		{
			pSpeed->RightValue = -vemax;
			pSpeed->LeftValue = pSpeed->RightValue + fabs(speed_e);
		}
		if(pSpeed->RightValue>vemax)
		{
			pSpeed->RightValue = vemax;
			pSpeed->LeftValue = pSpeed->RightValue - fabs(speed_e);
		}
		robot->y = 180 - robot->y;
		robot->theta = 2*Pi - robot->theta;
		directionpt.y = 180 - directionpt.y;
		robot->theta = cn_AngleTrim2PI(robot->theta);
		
		return 1;
}

int CS_ToPosition68(RobotPose *robot, BallPoint ball, Point directionpt, 
									  double samespeed, int IfEndprocess, Velocity *pSpeed)
{
	if (samespeed>=80)//70
	{
		samespeed=80;//70
	}
	
	Point cs_tempt,cs_pt1,cs_pt2;
	CIRCLEFORMULATION cs_circle1;
	LINEFORMULATION line_b2d,line_b2c;
	StdLineForm(directionpt,ball,&line_b2d);
	Point midpt;
	midpt.x=(directionpt.x+ball.x)/2;
	midpt.y=(directionpt.y+ball.y)/2;
	cn_PointPerpendLine(midpt,&line_b2d,&line_b2c,&cs_tempt);
	
	cs_circle1.x = midpt.x;
	cs_circle1.y = midpt.y;
	cs_circle1.r = 20;
	cn_LineCircleCross(&line_b2c,&cs_circle1,&cs_pt1,&cs_pt2);
	////////////////////���Լ�С���а뾶////////////////////////
	double theta,dx,dy,dx1,dy1;
	theta = atan2(directionpt.y-ball.y,directionpt.x-ball.x);
	theta = cn_AngleTrim2PI(theta);
	dx = robot->x-midpt.x;
	dy = robot->y-midpt.y;
	dx1 = dx*cos(theta - Pi/2) + dy*sin(theta - Pi/2);
	dy1 = -dx*sin(theta - Pi/2) + dy*cos(theta - Pi/2);
	//һ����
	if(dy1<=0.57735*dx1&&dy1<=-0.57735*dx1)
		//	if(robot->x > 5+(-line_b2c.b*robot->y-line_b2c.c)/line_b2c.a)//)
	{
		if(robot->y < (-line_b2d.a*robot->x-line_b2d.c)/line_b2d.b)
		{
			if(cs_pt1.y<cs_pt2.y)
			{
				//ToPositionPD(robot,cs_pt1,90,15+qiusubi*ballCharacter.velocity,pSpeed);
				//ToPositionN(robot,cs_pt1,65,pSpeed);
				//ToPositionForShoot(robot,cs_pt1,1,70,pSpeed);
				ToPositionPDchampionnew(robot,cs_pt1,60,pSpeed);
				AvoidBall(robot,ball,cs_pt1,pSpeed);
			}
			else 
			{
				//ToPositionPD(robot,cs_pt2,90,15+qiusubi*ballCharacter.velocity,pSpeed);
				ToPositionPDchampionnew(robot,cs_pt2,60,pSpeed);
				AvoidBall(robot,ball,cs_pt2,pSpeed);
				//ToPositionN(robot,cs_pt2,65,pSpeed);
				//ToPositionForShoot(robot,cs_pt2,1,70,pSpeed);
			}
		}
		else
		{
			if(cs_pt1.y > cs_pt2.y)
			{
				//ToPositionPD(robot,cs_pt1,90,15+qiusubi*ballCharacter.velocity,pSpeed);
				//ToPositionForShoot(robot,cs_pt1,1,70,pSpeed);
                ToPositionPDchampionnew(robot,cs_pt1,60,pSpeed);
				AvoidBall(robot,ball,cs_pt1,pSpeed);
			}
			else
			{
				//ToPositionPD(robot,cs_pt2,90,15+qiusubi*ballCharacter.velocity,pSpeed);
				//ToPositionForShoot(robot,cs_pt2,1,70,pSpeed);
				ToPositionPDchampionnew(robot,cs_pt2,60,pSpeed);
				AvoidBall(robot,ball,cs_pt1,pSpeed);
			}
		}
	}
	else
	{	
		ToPositionPD(robot,directionpt,70,0,pSpeed);
		//ToPositionForShoot(robot,cs_pt1,1,70,pSpeed);	
	}
	//else//���ڳ���Է�����֮��	
	return 1;
}




    void charInterpret(int robotNo,int charNo,Velocity *rbV)
	{
	int flag_1=0 , down=0;
	Point ballPt(ball_point.x, ball_point.y);
	if(old_ball_pts[0].y > old_ball_pts[3].y && old_ball_pts[3].y > old_ball_pts[6].y)
		down = 1;
	else if(old_ball_pts[0].y < old_ball_pts[3].y && old_ball_pts[3].y < old_ball_pts[6].y)
		down = -1;
	if(old_ball_pts[0].x > old_ball_pts[3].x && old_ball_pts[3].x > old_ball_pts[6].x)
		flag_1 = 1;

	switch (charNo)  
	{
	case 0:
		{
			rbV->LeftValue = rbV->RightValue = 0;
		}
		break;
	case 1:
		{
			double dJiontPt_y;
			Point pt;
			dJiontPt_y = (35-ball_point.x)*(my_robot_pose[robotNo].y-ball_point.y)/(my_robot_pose[robotNo].x-ball_point.x)+ball_point.y;
			
			if(dJiontPt_y>50&&dJiontPt_y<130&&(ball_point.x-35)*(my_robot_pose[robotNo].x-35)<0)
			{
				if(my_robot_pose[robotNo].x<35&&my_robot_pose[robotNo].y<130&&my_robot_pose[robotNo].y>50)
				{
					pt.x = 40;
					if(ball_point.y>90)
						pt.y = 135;
					else
						pt.y = 45;
					
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
						ToPositionPD(&my_robot_pose[robotNo],pt,80,35,rbV);
					else
						TurnToPointPD(&my_robot_pose[robotNo],ball_point,0,rbV);
				}
				else
				{
					if(dJiontPt_y>90)
					{
						pt.x = 40;
						pt.y = 135;
					}
					else
					{
						pt.x = 40;
						pt.y = 45;
					}
					
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
						ToPositionPD(&my_robot_pose[robotNo],pt,80,35,rbV);
					else
						TurnToPointPD(&my_robot_pose[robotNo],ball_point,0,rbV);
				}
			}
			else
			{
				BoundPushBall(my_robot_pose[robotNo],ballPt,*rbV);
				AvoidSelfRobots(&my_robot_pose[robotNo],ball_point,65,rbV);
			}
		}
		break;
	case 2:
		{
			double dx,dy,angle;
			dx = my_robot_pose[robotNo].x-ball_point.x;
			dy = my_robot_pose[robotNo].y-ball_point.y;
			angle=atan2(dy,dx);
			Vect_MidShoot1(my_robot_pose[robotNo],ball_point,rbV);
			if ((my_robot_pose[robotNo].x<wallleft+6.5)||(my_robot_pose[robotNo].x>wallright-6.5)||(my_robot_pose[robotNo].y>walltop-6.5)||(my_robot_pose[robotNo].y<wallbottom+6.5))
			{
		 			zhuangqiangshijian++;
		 			if (zhuangqiangshijian>40)
						{
							BoundPushBall(my_robot_pose[robotNo],ballPt,*rbV);
							AvoidSelfRobots(&my_robot_pose[robotNo],ball_point,65,rbV);	
						}
		  			if (zhuangqiangshijian>40+40)//zhuangqiangshijian>40+decisiondata[2][3]
						{
							zhuangqiangshijian=0;
		 				}									 	
			}
		}
		break;
	case 3:
		{	
			double dJiontPt_y;
			Point pt;
			dJiontPt_y = (35-ball_point.x)*(my_robot_pose[robotNo].y-ball_point.y)/(my_robot_pose[robotNo].x-ball_point.x)+ball_point.y;
			
			if(dJiontPt_y>50&&dJiontPt_y<130&&(ball_point.x-35)*(my_robot_pose[robotNo].x-35)<0)
			{
				if(my_robot_pose[robotNo].x<35&&my_robot_pose[robotNo].y<130&&my_robot_pose[robotNo].y>50)
				{
					pt.x = 40;
					if(ball_point.y>130)
					{
						pt.y = 135;
						if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
							ToPositionPD(&my_robot_pose[robotNo],pt,80,35,rbV);
						else
							TurnToPointPD(&my_robot_pose[robotNo],ball_point,0,rbV);
					}
					else if(ball_point.y<50)
					{
						pt.y = 45;
						if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
							ToPositionPD(&my_robot_pose[robotNo],pt,80,35,rbV);
						else
							TurnToPointPD(&my_robot_pose[robotNo],ball_point,0,rbV);
					}
					else
						ClearBall(&my_robot_pose[robotNo],ball_point,rbV);
				}
				else//
				{
					if(dJiontPt_y>90)
					{
						pt.x = 40;
						pt.y = 135;
					}
					else
					{
						pt.x = 40;
						pt.y = 45;
					}
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
						ToPositionPD(&my_robot_pose[robotNo],pt,80,35,rbV);
					else
						TurnToPointPD(&my_robot_pose[robotNo],ball_point,0,rbV);
				}
			}
			else
			{
				ClearBall(&my_robot_pose[robotNo],ball_point,rbV);
				AvoidSelfRobots(&my_robot_pose[robotNo],ball_point,65,rbV);
			}
		}
		break;
	case 4://רְ����
		{
			Point target,pt;
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<8&&ball_point.x<30&&ball_point.x>15)
			{	
				if(ball_point.y>my_robot_pose[robotNo].y)
				{
					rbV->LeftValue = 25;
					rbV->RightValue = -25;
				}
				else
				{
					rbV->LeftValue = -25;
					rbV->RightValue = 25;
				}
			}
			else
			{
				target.x = 20;
				if(ball_point.x<35)
				{
					target.y = ball_point.y;
				}
				else if(ball_point.x<60 && flag_1==1)
				{
					Point goal;
					LINEFORMULATION formu;
					formu.a = 1;
					formu.b = 0;
					formu.c = 0;
					if(cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1&&goal.y<115&&goal.y>65)
					{
						formu.c = -23;
						cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);
						target.y = goal.y;
						////////////////
						
						if(defend_counter == 0)
						{
							target.y = target.y+3;
						}
					}
					else
					{
						target.y = (ball_point.y-90)*target.x/ball_point.x+90;
					}
				}
				else
				{
					target.y = (ball_point.y-90)*target.x/ball_point.x+90;
				}
				if(target.y<60)
					target.y = 60;
				if(target.y>120)
					target.y = 120;
				
				if(distRobot2Pt(my_robot_pose[robotNo],target) > distError)
					ToPositionPDGoal(&my_robot_pose[robotNo],target,60,0,rbV);
				else
				{
					if(my_robot_pose[robotNo].theta < Pi)
						TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,NOCLOCK,rbV);
					else
						TurnToAnglePD(&my_robot_pose[robotNo],3*Pi/2,NOCLOCK,rbV);
				}
				

				if(target.y>90 && ball_point.y>my_robot_pose[robotNo].y&&ball_point.y<125&&ball_point.x<24&&ball_point.x>16)
				{
					pt.x = 25;
					pt.y = 140;
					ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,70,2,rbV);
				}
				else if(target.y<90&&ball_point.y<my_robot_pose[robotNo].y&&ball_point.y>55&&ball_point.x<24&&ball_point.x>16)
				{
					pt.x = 25;
					pt.y = 40;
					ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,70,2,rbV);
				}

			}
			

			Point car5,cari;
			car5.x=my_robot_pose[5].x;			car5.y=my_robot_pose[5].y;
			cari.x=my_robot_pose[robotNo].x;	cari.y=my_robot_pose[robotNo].y;
			
			if(my_robot_pose[robotNo].y>65 && my_robot_pose[robotNo].y<115 && my_robot_pose[robotNo].x<15)
			{
				double angle,angle_e;
				angle=my_robot_pose[robotNo].theta;
				angle=cal_AngleTrimPI(angle);
				if(angle>Pi/2)
					angle_e=Pi-angle;
				else
					angle_e=angle;
				
				if(angle_e>0.2)
					TurnToAnglePD(&my_robot_pose[robotNo],0,0,rbV);
			}
			
			if(ban_warning_flag2==100 && my_robot_pose[robotNo].y>65 && my_robot_pose[robotNo].y<115 && my_robot_pose[robotNo].x<15
				&& cal_2PointsDist(cari,car5)<12)
			{
				position(&my_robot_pose[robotNo],target,rbV);
				
			}

		}
		break;
	case 5:
		{
			Point pt,goal;
			pt.y = 135;
			LINEFORMULATION formu;
			formu.a = 0;
			formu.b = 1;
			formu.c = -135;
			if(cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1&&goal.x<40&&goal.x>5)
				pt.x = goal.x;
			else
			{
				pt.x = ball_point.x*45/fabs(ball_point.y-90);
				if(pt.x>40)
					pt.x = 40;
				if(pt.x<5)
					pt.x = 5;
			}
			if(ball_point.y<135)
				pt.x = 20;
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				if(my_robot_pose[robotNo].x<35&&my_robot_pose[robotNo].y<130)
				{
					pt.x = 35;
					pt.y = 140;
					ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				}
				else
					ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				//ToPositionN(&my_robot_pose[robotNo],pt,70,rbV);
			}
			else	
				AdaptAngle(&my_robot_pose[robotNo],rbV,1);
			
			AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
			

			if(ball_point.x<my_robot_pose[robotNo].x+2&&distRobot2Pt(my_robot_pose[robotNo],ball_point)<8)
			{
				rbV->LeftValue = 30;
				rbV->RightValue = -30;
			}
		}
		break;
	case 6:
		{
			Point pt,goal;
			pt.y = 45;
			LINEFORMULATION formu;
			formu.a = 0;
			formu.b = 1;
			formu.c = -45;
			if(cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1&&goal.x<40&&goal.x>5)
				pt.x = goal.x;
			else
			{
				pt.x = ball_point.x*45/fabs(90-ball_point.y);
				if(pt.x>40)
					pt.x = 40;
				if(pt.x<5)
					pt.x = 5;
			}
			if(ball_point.y>45)
				pt.x = 20;
			
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				if(my_robot_pose[robotNo].x<35&&my_robot_pose[robotNo].y>50)
				{
					pt.x = 35;
					pt.y = 40;
				}
				ToPositionN(&my_robot_pose[robotNo],pt,70,rbV);
				//ToPositionN(&my_robot_pose[robotNo],pt,70,rbV);
			}
			else
				AdaptAngle(&my_robot_pose[robotNo],rbV,1);
			
			AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
			
			/////////////////////////////˦����////////////////////////////
			if(ball_point.x<my_robot_pose[robotNo].x+2&&distRobot2Pt(my_robot_pose[robotNo],ball_point)<8)
			{
				rbV->LeftValue = -30;
				rbV->RightValue = 30;
			}
		}
		break;
	case 7:
		{
			if(ball_point.x>XIAOJINGQU&&ball_point.x<=XIAOJINGQU+5.0&&ball_point.y<130&&ball_point.y>my_robot_pose[robotNo].y+3)
			{
				Point pt;
				pt.x = 20;//20
				pt.y = 140 /*130*/;
				ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,80,2,rbV);
			}
			else if(ball_point.x>XIAOJINGQU-5.0&&ball_point.x<=XIAOJINGQU&&ball_point.y<130&&ball_point.y>my_robot_pose[robotNo].y+3)
			{
				Point pt;
				pt.x = 20;//20
				pt.y = 140 /*130*/;
				ToPositionPD(&my_robot_pose[robotNo],pt,80,2,rbV);
			}
			else if(ball_point.x>XIAOJINGQU-5.0/*&&ball_point.x<=26*/&&distRobot2Pt(my_robot_pose[robotNo],ball_point)< 15 &&ball_point.y<my_robot_pose[robotNo].y)
			{
				rbV->LeftValue = -25;
				rbV->RightValue = 25;
			}
			else
			{
				Point pt;
				pt.x = 20;//20
				if(ball_point.x<XIAOJINGQU+7.0)//25
					pt.y = ball_point.y;
				else
				{
					pt.y = pt.x*(ball_point.y -90)/ball_point.x + 90 + 5;
				}
				//////////////////////////////////////////////
				if(ball_point.x<XIAOJINGQU-5.0&&ball_point.y<=115&&ball_point.y>65)
					pt.y=ball_point.y+4+0.5;
				if(pt.y>118)
					pt.y = 118;//120
				if(pt.y<72)
					pt.y = 72;//72

				if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
					ToPositionPDGoal(&my_robot_pose[robotNo],pt,60,0,rbV);
				else
					AdaptAngle(&my_robot_pose[robotNo],rbV,0);//0��ʾת��ֱ
			}
		}
		break;
	case 8:
		{
			if(ball_point.x>XIAOJINGQU && ball_point.x<=XIAOJINGQU+5.0 && ball_point.y>50 && ball_point.y<my_robot_pose[robotNo].y+3)
			{
				Point pt;
				pt.x = 20;//20
				pt.y = 40/*50*/;
				ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,80,2,rbV);
			}
			else if(ball_point.x>XIAOJINGQU-5.0&&ball_point.x<=XIAOJINGQU&&ball_point.y>50&&ball_point.y<my_robot_pose[robotNo].y+3)
			{
				Point pt;
				pt.x = 20;//20
				pt.y = 40;
				ToPositionPD(&my_robot_pose[robotNo],pt,80,2,rbV);
			}

			else if(ball_point.x>XIAOJINGQU-5.0/*&&ball_point.x<=26*/&&distRobot2Pt(my_robot_pose[robotNo],ball_point)<5&&ball_point.y>my_robot_pose[robotNo].y)
			{
				rbV->LeftValue = 25;
				rbV->RightValue = -25;
			}
			else
			{
				Point pt;
				pt.x = 20;//20
				if(ball_point.x<XIAOJINGQU+7.0)
					pt.y = ball_point.y;
				else
				{
					pt.y = pt.x*(ball_point.y -90)/ball_point.x + 90 - 5 ;//5
				}
				//////////////////////////////////////////////
				if(ball_point.x<XIAOJINGQU/*14*/&&ball_point.y<=115/*105*/&&ball_point.y>65)
					pt.y=ball_point.y-4-0.5;
				if(pt.y>108)
					pt.y = 108;//108
				if(pt.y<63)
					pt.y = 63;//60
				
				if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
					ToPositionPDGoal(&my_robot_pose[robotNo],pt,60,0,rbV);
				else
					AdaptAngle(&my_robot_pose[robotNo],rbV,0);
			}
		}
		break;
	case 9:
		{
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<8&&ball_point.x<my_robot_pose[robotNo].x+3)	
			{
				rbV->LeftValue = 30;
				rbV->RightValue = -30;
			}
			else
			{
				Point pt;
				if(my_robot_pose[robotNo].x<16&&my_robot_pose[robotNo].y>64&&my_robot_pose[robotNo].y<116)
				{
					pt.x = 20;
					pt.y = 120;
				}
				else
				{
					double cs_y;
					cs_y = my_robot_pose[ROBOTNUM].y;
					if(cs_y>125) cs_y = 125;
					if(cs_y<110) cs_y = 110;
					pt.y = 120;
					pt.x = ball_point.x*30/fabs(ball_point.y-90);
					if(pt.x<9)
						pt.x = 9;
					pt.x = pt.x+(cs_y-110);
					if(pt.x>15)
						pt.x = 15;
				}
				if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
				{
					ToPositionNPTC(&my_robot_pose[robotNo],pt,80,rbV);		
				}
				else
					AdaptAngle(&my_robot_pose[robotNo],rbV,1);
				//TurnToAnglePD(&my_robot_pose[robotNo],0,0,rbV);
				AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
			}
		}
		break;
	case 10://С�����´�ֱ����
		{
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<8&&ball_point.x<my_robot_pose[robotNo].x+3)	
			{
				rbV->LeftValue = -30;
				rbV->RightValue = 30;
			}
			else
			{
				Point pt;
				if(my_robot_pose[robotNo].x<16&&my_robot_pose[robotNo].y>64&&my_robot_pose[robotNo].y<116)
				{
					pt.x = 20;
					pt.y = 60;
				}
				else
				{
					double cs_y;
					cs_y = my_robot_pose[ROBOTNUM].y;
					if(cs_y>70) cs_y = 70;
					if(cs_y<55) cs_y = 55;
					pt.y = 60;
					pt.x = ball_point.x*30/fabs(90-ball_point.y);
					pt.x = ball_point.x;
					if(pt.x<9)
						pt.x = 9;
					pt.x = pt.x+(70-cs_y);
					if(pt.x>15)
						pt.x = 15;
				}
				if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
				{
					ToPositionNPTC(&my_robot_pose[robotNo],pt,80,rbV);//ToPositionPD(&my_robot_pose[robotNo],pt,70,0,rbV);
				}
				else
					AdaptAngle(&my_robot_pose[robotNo],rbV,1);
				AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
			}
		}
		break;
	case 11://ֱ������
		{
			Point pt,goal,directionpt;
			double timeshoot;
			directionpt.x=220;//400;
			directionpt.y=90;//140;

			static Point factpt={140, 90};//{140,90};

			int x = shootsign3;
			
			int chongflag=0;//ֱ���־



			pt.x =130;//140
			pt.y =90;//90
			LINEFORMULATION formu;
			formu.a = 0;
			formu.b = 1;
			formu.c = -90;//-140;//y=140

			if(BallPredictCharacter.Formu.b!=0)//Ԥ���߲���ֱ��X��
				cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);//���Ԥ��켣��y=140�Ľ���Ϊgoal
			else 
			{
				goal.x = ball_point.x;
				goal.y =90;// 140;
			}
			double 	t;
			double s1,s2;
			s1=cal_2PointsDist(ball_point,goal);//���Ŀ���ľ���
			double Vt;
			Vt=moca*s1;//��Ŀ������ٵļ����� 
			double ybv;
			ybv=cn_LineAngle(&BallPredictCharacter.Formu);//��Ԥ���ߵļн�
			ybv=cn_AngleTrimPI(ybv);
			ybv=fabs(BallPredictCharacter.velocity*sin(ybv));
			if(ybv<0.35&&ball_point.y<factpt.y+4.5&&ball_point.y>factpt.y-4.5)//��y���ٶȵ���0.35����y�ӽ�140
			{
				s1=0;
				chongflag=1;//��ֱ���־
			}
			t=fabs(s1/((2*BallPredictCharacter.velocity-Vt)/2));//·�̳���ƽ���ٶȣ���Ŀ���Ĵ���ʱ�䣩
			if(BallPredictCharacter.velocity<0.18&&ball_point.y<factpt.y+4.5&&ball_point.y>factpt.y-4.5)//���ٵ���0.18,������y�ӽ�140
			{
				goal.x = ball_point.x;
				goal.y =90;// 140;
			}
			if(readyflag==1)//��ֵΪ1
			{
				double robottheta;
				robottheta=cn_AngleTrim2PI(my_robot_pose[robotNo].theta);//����н�
				if(distRobot2Pt(my_robot_pose[robotNo],pt)<=2&&(robottheta<=(4.0/180.0)*Pi||
					fabs(robottheta-Pi)<=(4.0/180.0)*Pi||2*Pi-robottheta<=(4.0/180.0)*Pi))
					//С���������ƽ����X�ᣬС��λ���ڣ�290��140������
				{
					readyflag = 0;
					factpt.x=my_robot_pose[robotNo].x;
					factpt.y=my_robot_pose[robotNo].y;
					timeshoot=0;
				}
			}
			int tt;
			tt=t;//��Ŀ���Ĵ���ʱ��
			if(t<=49)
			{
				s2=zhichong[tt];//ttʱ�̳��루290��140���ľ���
			}
			else//t>49
			{
				s2=zhichong[49]+dizeng*(t-49);//����290,140���ľ���
			}
			double distlimit,balltime,rbttime;
			balltime=1.875/BallPredictCharacter.velocity;//Ϊʲô��1.875,����1/4
			double dist,V;
			dist=my_robot_pose[robotNo].x-factpt.x;//������290��140���ľ���
			if(dist<2.5)
			{
				V=25;
			}
			else if(dist<3)
			{
				V=25+15*(dist-2.5);
				//V=100;
			}
			else 
			{
				V=32.5+30*(dist-3);
			}
			
			if(V>100)
			{
				V=100;
			}
			
			V=V/qiusubi;//�������ٶ�ת��Ϊ������ͬһ��λ ��ǰ��25
			rbttime=4/V;//4Ϊ����һ�룬�߳���һ�복�����ʱ��
			if(balltime<rbttime)
			{       
				distlimit=balltime*V;//���߳���һ���ʱ�䳵�ߵľ���
			}
			else
			{
				distlimit=4;
			}

			if(BallPredictCharacter.velocity>0.2)//���˶�
			{
				double fuhao;
				fuhao=cn_AngleTrim2PI(BallPredictCharacter.angle);
				{
					if((fuhao>=3*Pi/2+Pi/6&&fuhao<=2*Pi)||fuhao<=Pi/3+Pi/18)//��Ԥ������X��ļнǣ�-60,70�㣩
					{
						distlimit=-distlimit;
					}
				}
			}
			
			if(goal.x<220 && goal.x>142 &&

				(    (ball_point.y<95&&ball_point.y>85)   ||
				(ball_point.y<150&&ball_point.y>80 && down==1||ball_point.y>30&&ball_point.y<100&&down==-1)
				&&cal_2PointsDist(pt,goal)>s2-distlimit  &&   readyflag==0
				&&my_robot_pose[robotNo].y<95    &&   my_robot_pose[robotNo].y>85))//ֱ�������
			{
				goal.x = 230;//500;
				double dist,V;
				dist=my_robot_pose[robotNo].x-factpt.x;
				if(dist<2.5)
				{
					V=25;
				}
				else if(dist<3)
				{
					V=25+15*(dist-2.5);
					//V=100;
				}
				else 
				{
					V=32.5+30*(dist-3);
				}
				
				if(V>100)
				{
					V=100;
				}
				ToPositionPD(&my_robot_pose[robotNo],goal,V,0,rbV);
				shootsign3 = 5;
			}
			else//������ֱ�������
			{   
				if(shootsign3!=0)//5֡���ж�ʱ��
				{
					goal.x =230;// 500;
					double dist,V;
					dist=my_robot_pose[robotNo].x-factpt.x;
					if(dist<2.5)
					{
						V=25;
						
					}
					else if(dist<3)
					{
						V=25+15*(dist-2.5);
						//V=100;
					}
					else 
					{
						V=32.5+30*(dist-3);
					}
					
					if(V>100)
					{
						V=100;
					}
					ToPositionPD(&my_robot_pose[robotNo],goal,V,0,rbV);
					shootsign3--;
				}
				else//if(shootsign3=0)  
				{
					//AvoidShooter(&my_robot_pose[robotNo],&pt);
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>3)
					{
						readyflag=1;
						if(distRobot2Pt(my_robot_pose[robotNo],pt)>25)
					       AvoidALLRobotsM(&my_robot_pose[robotNo],pt,70,0,rbV);
						else//3<distRobot2Pt(my_robot_pose[robotNo],pt)<25
						   ToPositionPDchampion(&my_robot_pose[robotNo],pt,0,0,rbV);
					}	
					else
						TurnToAnglePD(&my_robot_pose[robotNo],0,0,rbV);
				}
			}
			EndProcess_Forhit_mid(1,&my_robot_pose[robotNo],directionpt,ball_point,rbV);
		}
		break;
	
	case 12://��ɫ12����
		{
			GoalieAction(&my_robot_pose[robotNo],ball_point,rbV);
			showtarget2=(float)my_robot_pose[robotNo].y;
		}
		break;
	case 13://�߽���Э��
		{
			Point	pt;
			pt.x = ball_point.x - 30;
			pt.y = ball_point.y + 30;
			if(pt.x<45)
				pt.x = 45;
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				if(ball_point.x<my_robot_pose[robotNo].x)
					CS_ToPositionN1(&my_robot_pose[robotNo],pt,ball_point,0,20,80,rbV);
				else
					ToPositionN(&my_robot_pose[robotNo],pt,90,rbV);
				AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
			}
			else
				TurnToPointPD(&my_robot_pose[robotNo],ball_point,0,rbV);
		}
		break;
	case 14://�߽���Э��
		{
			Point	pt;
			pt.x = ball_point.x - 30;
			pt.y = ball_point.y - 30;
			if(pt.x<45)
				pt.x = 45;
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{	
				if(ball_point.x<my_robot_pose[robotNo].x)
					CS_ToPositionN1(&my_robot_pose[robotNo],pt,ball_point,0,20,80,rbV);
				else
					ToPositionN(&my_robot_pose[robotNo],pt,90,rbV);
				AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
			}
			else
				TurnToPointPD(&my_robot_pose[robotNo],ball_point,0,rbV);
		}
		break;
	case 15://������ϻ���
		{
			Point	pt;
			if(ball_point.x<DAJINGQU+10.0&&ball_point.x>DAJINGQU&&ball_point.y>my_robot_pose[robotNo].y+3&&ball_point.y<145)
			{
				pt.x =  45;//DAJINGQU-3;//45
				pt.y = 165;
				ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,70,0,rbV);
			}
			else if(ball_point.x<DAJINGQU&&ball_point.x>DAJINGQU-5.0&&ball_point.y>my_robot_pose[robotNo].y&&ball_point.y<145)
			{
				pt.x = 40;//DAJINGQU-3;//40
				pt.y = 165;
				ToPositionPD(&my_robot_pose[robotNo],pt,70,0,rbV);
			}
			else
			{
				if(ball_point.y<my_robot_pose[robotNo].y/*+3*/&&ball_point.x>DAJINGQU-5.0/*40*/&&distRobot2Pt(my_robot_pose[robotNo],ball_point)<3)//decisiondata[0][0]
				{
					rbV->LeftValue = -30;
					rbV->RightValue = 30;
				}
				else
				{
					pt.x = 40;//DAJINGQU-3;//40
					pt.y = ball_point.y+3;//3
					if(pt.y<= 94)//94
						pt.y = 94;// 94;
					else if(pt.y >= 130)///////////////////////130
						pt.y = 130;//130;					
					
					Point robotpt;
					robotpt.x=my_robot_pose[robotNo].x;
					robotpt.y=my_robot_pose[robotNo].y;
					static int j=0;
					ROSrect rect(0,130,35,50);
					if(my_robot_pose[robotNo].x<35&&my_robot_pose[robotNo].y>50&&my_robot_pose[robotNo].y<130)//�����
					{
						j=1;	
					}
					if(j==1)
						Outofforbiddenzonezq(robotpt,rect,8,1,pt,&j,&pt);
					else
						AoidenterbiddenzoneLC(robotpt,rect,5,&pt);
					////////////////////////////////////////////////////////////////////////////
					// OutOfForbbidenZone(my_robot_pose[robotNo],pt);
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
					{
						//ToPositionN(&my_robot_pose[robotNo],pt,70,rbV);
                        ToPositionPD(&my_robot_pose[robotNo],pt,70,0,rbV);
						AvoidSelfRobots(&my_robot_pose[robotNo],pt,70,rbV);
						AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
					}
					else
						TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,0,rbV);
					//	AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
				}
			}
		}
		break;
	case 16://������»���
		{
			Point	pt;
			if(ball_point.x<DAJINGQU+10.0&&ball_point.x>DAJINGQU&&ball_point.y<my_robot_pose[robotNo].y-3&&ball_point.y>35)
			{
				pt.x = 45;//DAJINGQU+5;//45
				pt.y = 15;
				ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,70,0,rbV);
			}
			else if(ball_point.x<DAJINGQU&&ball_point.x>DAJINGQU-5.0&&ball_point.y<my_robot_pose[robotNo].y&&ball_point.y>35)
			{
				pt.x = 40;//DAJINGQU;//40
				pt.y = 15;
				ToPositionPD(&my_robot_pose[robotNo],pt,70,0,rbV);
			}
			else
			{
				if(ball_point.y>my_robot_pose[robotNo].y&&ball_point.x>35&&distRobot2Pt(my_robot_pose[robotNo],ball_point)<3)//decisiondata[0][0]
				{
					rbV->LeftValue = 30;
					rbV->RightValue = -30;
				}
				else
				{
					pt.x =40;// DAJINGQU;//40//decisiondata[16][0]
					pt.y = ball_point.y-3;//3//decisiondata[15][3]
					if(pt.y>=86)//86//decisiondata[16][1]
						pt.y =86;// 86;//decisiondata[16][1]
					else if(pt.y<=55)//55//decisiondata[16][2]
						pt.y = 55;//55;//decisiondata[16][2]
					/////��������/////////////////////////////////////////////////////////////////////					
					
					Point robotpt;
					robotpt.x=my_robot_pose[robotNo].x;
					robotpt.y=my_robot_pose[robotNo].y;
					static int j=0;
					ROSrect rect(0,130,35,50);
					if(my_robot_pose[robotNo].x<35&&my_robot_pose[robotNo].y>50&&my_robot_pose[robotNo].y<130)//�����
					{
						j=1;	
					}
					
					if(j==1)
						Outofforbiddenzonezq(robotpt,rect,8,1,pt,&j,&pt);
					else
						AoidenterbiddenzoneLC(robotpt,rect,5,&pt);
					/////////////////////////////////////////////////////////////////////////////////
					OutOfForbbidenZone(my_robot_pose[robotNo],pt);
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
					{
						//ToPositionN(&my_robot_pose[robotNo],pt,70,rbV);
						
                        ToPositionPD(&my_robot_pose[robotNo],pt,70,0,rbV);
						AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,70,rbV);
						AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
					}
					else
						TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,0,rbV);
					//	AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
				}
			}
		}
		break;
	case 17://(30,140)������
		{
			Point	pt;
			pt.x = 30;
			pt.y = 140;
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				//ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,80,rbV);
				
				AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);		
			}
			else
				AdaptAngle(&my_robot_pose[robotNo],rbV,1);			
		}
		break;
	case 18://(45,90)90����
		{
			Point	pt;
			pt.x = 45;
			pt.y = 90;
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{	
				//ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				
				AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,80,rbV);
				AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
			}
			else
				AdaptAngle(&my_robot_pose[robotNo],rbV,1);
		}
		break;
	case 19://(30,40)������
		{
			Point	pt;
			pt.x = 30;
			pt.y = 40;
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);			
			}
			else
				AdaptAngle(&my_robot_pose[robotNo],rbV,0);
			//TurnToPointPD(&my_robot_pose[robotNo],ball_point,0,rbV);
			//TurnToAnglePD(&my_robot_pose[robotNo],Pi/4,0,rbV);
		}
		break;
	case 20://С�����ϴ�ֱ����
		{
			///////////////////���ʱ��ת/////////////////////////////////////////////
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<5&&ball_point.x<my_robot_pose[robotNo].x+3)	//decisiondata[0][0]
			{
				rbV->LeftValue = 30;
				rbV->RightValue = -30;
			}
			else
			{
				Point pt;
				if(my_robot_pose[robotNo].x<15/*16*/&&my_robot_pose[robotNo].y>65/*64*/&&my_robot_pose[robotNo].y<115/*116*/)
				{
					pt.x = 20;
					pt.y = 120;//120;
				}
				else
				{
					pt.y = 120;//120;
					pt.x = (ball_point.x-wallleft)*(pt.y-90)/fabs(ball_point.y-90);
					if(pt.x<5)
						pt.x = 3;//3;
 					if(pt.x>20)
 						pt.x = 20;
				}
				if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
				{	
					ToPositionPD(&my_robot_pose[robotNo],pt,80,0,rbV);
				}
				else
				{
					if(pt.x<18)
						AdaptAngle(&my_robot_pose[robotNo],rbV,1);
					else 
                        AdaptAngle(&my_robot_pose[robotNo],rbV,0);
				}
				AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
			}    
		}
		break;
	case 21://С�����´�ֱ����
		{
			///////////////////���ʱ��ת/////////////////////////////////////////////
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<5&&ball_point.x<my_robot_pose[robotNo].x+3)	//decisiondata[0][0]
			{
				rbV->LeftValue = -30;
				rbV->RightValue = 30;
			}
			else
			{
				Point pt;
				if(my_robot_pose[robotNo].x<15&&my_robot_pose[robotNo].y>65&&my_robot_pose[robotNo].y<115)
				{
					pt.x = 20;
					pt.y = 160;//60;
				}
				else
				{
					pt.y = 60;//60;
					pt.x = (ball_point.x-wallleft)*fabs((pt.y-90)/(ball_point.y-90));
					if(pt.x<5)
						pt.x = 3;//3;
					if(pt.x>20)
						pt.x = 20;

				}
				if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
				{
					ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);			
				}
				else
				{
					if(pt.x<18)
						AdaptAngle(&my_robot_pose[robotNo],rbV,1);
					else 
                        AdaptAngle(&my_robot_pose[robotNo],rbV,0);
				}
				AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
			}    
		}
		break;
	case 22://������´�ֱ����
		{
            ///////////////////���ʱ��ת/////////////////////////////////////////////
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<8&&ball_point.x<my_robot_pose[robotNo].x+3&&ball_point.y<=my_robot_pose[robotNo].y+3)	
			{
				rbV->LeftValue = -30;
				rbV->RightValue = 30;
			}
            ///////////////////////////////////////////////////////////////////////
            else if(ball_point.y>42 && ball_point.y<=48&& ball_point.x>my_robot_pose[robotNo].x+3&&ball_point.x<60)
			{
				Point pt;
				pt.x = 50;
				pt.y = 45;//45;
				ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,80,2,rbV);
			}
			else
			{
				Point pt,target;
				/*	if(my_robot_pose[robotNo].x<36&&my_robot_pose[robotNo].y>49&&my_robot_pose[robotNo].y<131)
				{
				pt.x = 35;
				pt.y = 45;
				}
				else
				{*/	
				int k=45;
				if(ball_point.x<20)
					k=35;
				else
					k=45;
				pt.y =45;// 45;
				////////////////////////////
				pt.x=k*ball_point.x/fabs(90-ball_point.y);
				////////////////////////////
				if(ball_point.y>35&&ball_point.y<55)
					pt.x = ball_point.x-3;
				
				target.x=pt.x;
				
				//////////////////////////////////////////////////////////////////////
				int count1=0;
				for(int i=1;i<=4;i++)
				{
					if(i==robotNo)
						continue;
					else if(/*my_robot_pose[i].y<=(my_robot_pose[robotNo].y+10)*/my_robot_pose[i].y<45&&my_robot_pose[i].y>ball_point.y&&ball_point.y>=25&&
						ball_point.x<=(my_robot_pose[i].x+4)&&ball_point.x>=(my_robot_pose[i].x-4)&&ball_point.x<=10&&my_robot_pose[i].y>30
						/*&&my_robot_pose[robotNo].x<=(my_robot_pose[i].x+4)&&my_robot_pose[robotNo].x>=(my_robot_pose[i].x-4)*/
						)
					{
						count1=1; 
					}
				}
				////////////////////////////////////////////////////////////
				if(target.x<=7)
					pt.x=3.5;//2;//3.5
				else if(target.x>=35)//35
					pt.x=35;//35
				else
					pt.x=target.x;
				
				if(ball_point.y>48&&ball_point.x<15)
					pt.x=9;
				else if(ball_point.y>48&&ball_point.x>35)//35
					
					pt.x=35;//35
				if(count1==1)
					pt.x=12;
				/////////////��������///////////////////////////////////////				
				
				Point robotpt;
				robotpt.x=my_robot_pose[robotNo].x;
				robotpt.y=my_robot_pose[robotNo].y;
				/* CRect rect(0,130,35,50);
				Aoidenterbiddenzone(robotpt,rect,1,&pt);
				/////////////////////////////////////////////////////////*/
				static int j=0;
				ROSrect rect(0,131,36,49);
				if(my_robot_pose[robotNo].x<35&&my_robot_pose[robotNo].y>50&&my_robot_pose[robotNo].y<130)
				{
					j=1;	
				}
				
				if(j==1)
					Outofforbiddenzonezq(robotpt,rect,8,1,pt,&j,&pt);
				else
					Aoidenterbiddenzone(robotpt,rect,3,&pt);
				///////////////////////////////////////////////////////////					
				//}
				if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
				{
                    
					//ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
					if(my_robot_pose[robotNo].x>70||my_robot_pose[robotNo].x<35) 
						ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
					else
					{ 
						ToPositionN(&my_robot_pose[robotNo],pt,60,rbV); 
					}
				}
				else
				{
					AdaptAngle(&my_robot_pose[robotNo],rbV,1);
				}
				AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
			}    
		}
		break;
    case 23://С��������רְ����
	    {
		   Point target;
		   target.x = 20;
		   if(ball_point.x<35)
		   {
			   target.y = ball_point.y;
		   }
		   else if(ball_point.x<60&&flag_1==1)
		   {
			   Point goal;
			   LINEFORMULATION formu;
			   formu.a = 1;
			   formu.b = 0;
			   formu.c = 0;
			   if(cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1&&goal.y<115&&goal.y>65)//������С������
			   {
				   formu.c = -23;
				   cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);
				   target.y = goal.y;
			   }
			   else//������������޽��� �� ��������������
			   {
				   target.y = (ball_point.y-90)*target.x/ball_point.x+90;
			   }		
		   }
		   else//ball_point.x>60||��ͣ����ȥ
		   {
			   target.y = (ball_point.y-90)*target.x/ball_point.x+90;			
		   }
		   if(target.y<60)
			   target.y = 60;
		   if(target.y>120)
			   target.y = 120;
		   if(target.y>90)
		   {
			   target.y = target.y - 11;	//12
			   defendflag = 1;
		   }
		   else
		   {
			   target.y = target.y + 11;	//12
			   defendflag = 0;
		   }
		   
		   if(distRobot2Pt(my_robot_pose[robotNo],target) > distError)
			   ToPositionPDGoal(&my_robot_pose[robotNo],target,60,0,rbV);
		   //ToPositionN(&my_robot_pose[robotNo],target,50,rbV);
		   //ToPositionNPTC(&my_robot_pose[robotNo],target,70,rbV);
		   else
		   {
			   if(my_robot_pose[robotNo].theta < Pi)
				   TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,NOCLOCK,rbV);
			   else
				   TurnToAnglePD(&my_robot_pose[robotNo],3*Pi/2,NOCLOCK,rbV);
		   }
		   AvoidSelfBump(&my_robot_pose[robotNo],target,1,rbV);
		   if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<8&&ball_point.x<27&&ball_point.x>15)
		   {	
			   if(ball_point.y>my_robot_pose[robotNo].y)
			   {
				   rbV->LeftValue = 25;
				   rbV->RightValue = -25;
			   }
			   else
			   {	
				   rbV->LeftValue = -25;
				   rbV->RightValue = 25;
			   }
		   }
		   
		   
		   Point car5,cari;
		   car5.x=my_robot_pose[5].x;			car5.y=my_robot_pose[5].y;
		   cari.x=my_robot_pose[robotNo].x;	cari.y=my_robot_pose[robotNo].y;
		   
		   if(my_robot_pose[robotNo].y>65 && my_robot_pose[robotNo].y<115 && my_robot_pose[robotNo].x<15)
		   {
			   double angle,angle_e;
			   angle=my_robot_pose[robotNo].theta;
			   angle=cn_AngleTrimPI(angle);
			   if(angle>Pi/2)
				   angle_e=Pi-angle;
			   else
				   angle_e=angle;
			   
			   if(angle_e>0.2)
				   TurnToAnglePD(&my_robot_pose[robotNo],0,0,rbV);
		   }
		   
		   if(ban_warning_flag2==100 && my_robot_pose[robotNo].y>65 && my_robot_pose[robotNo].y<115 && my_robot_pose[robotNo].x<15
			   && cal_2PointsDist(cari,car5)<12)
		   {
			   position(&my_robot_pose[robotNo],target,rbV);
			   
		   }
		}
		break;
	case 24:
		{
			Point pt;
			pt.x = 20;
			pt.y = (ball_point.y-90)*pt.x/ball_point.x+90;
			if(pt.y<70)
				pt.y = 70;
			if(pt.y>110)
				pt.y = 110;
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
				//ToPositionN(&my_robot_pose[robotNo],pt,55,rbV);
				ToPositionNPTC(&my_robot_pose[robotNo],pt,80,rbV);
			else
				AdaptAngle(&my_robot_pose[robotNo],rbV,0);
			//	AvoidSelfBump(&my_robot_pose[robotNo],pt,1,rbV);
		}
		break;
	case 25:
		{
			Point pt;
			pt.x = 50;
			pt.y = 90;
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);		
			}
			else
				AdaptAngle(&my_robot_pose[robotNo],rbV,1);
		}
		break;
	case 26:
		{
			CS_ClearBall(&my_robot_pose[robotNo],ball_point,rbV);
		}
		break;
	case 27:
		{
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<8&&ball_point.x<my_robot_pose[robotNo].x/*+3*/&&ball_point.y>=my_robot_pose[robotNo].y-3)	
			{
				rbV->LeftValue = 30;
				rbV->RightValue =-30;
				
			}
            else if(ball_point.y>132 && ball_point.y<=138&& ball_point.x>my_robot_pose[robotNo].x+3&&ball_point.x<50/*60*/)
			{
				Point pt;
				pt.x = 60/*50*/;
				pt.y = 135;//140/*135*/;
				ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,80,2,rbV);
			}
			else
			{
				Point pt,target;


				pt.y = 135;// 135;


				pt.x=(135.0-90.0)*ball_point.x/(ball_point.y-90);
				if(ball_point.y<145&&ball_point.y>125)
					pt.x = ball_point.x-3;
				//	pt.x = ball_point.x;
				target.x=pt.x;

				if(target.x<=7)
					pt.x = 3.5;//3.5;
				else if(target.x>=35)//35
					pt.x=35;//35
				else 
					pt.x=target.x;

				if(ball_point.y<132&&ball_point.x<12)
					pt.x=6;//9
				else if(ball_point.y<132&&ball_point.x>35)//35
					pt.x=35;//35
				int count=0;
				for(int i=1;i<=4;i++)
				{
					if(i==robotNo)
						continue;
					else if(/*my_robot_pose[i].y<=(my_robot_pose[robotNo].y+10)*/my_robot_pose[i].y>135&&my_robot_pose[i].y<ball_point.y&&ball_point.y<=155&&
						ball_point.x<=(my_robot_pose[i].x+4)&&ball_point.x>=(my_robot_pose[i].x-4)&&ball_point.x<=10&&my_robot_pose[i].y<150)
						/*&&my_robot_pose[robotNo].x<=(my_robot_pose[i].x+4)&&my_robot_pose[robotNo].x>=(my_robot_pose[i].x-4)*/
					{
						count=1; 
					}
				}	
				if(count==1)
					pt.x=12;
				
				
				
				Point robotpt;
				robotpt.x=my_robot_pose[robotNo].x;
				robotpt.y=my_robot_pose[robotNo].y;
				static int j=0;
				ROSrect rect(0,130,35,50);
				if(my_robot_pose[robotNo].x<35&&my_robot_pose[robotNo].y>50&&my_robot_pose[robotNo].y<130)
				{
					j=1;	
				}
				
				if(j==1)
					Outofforbiddenzonezq(robotpt,rect,8,1,pt,&j,&pt);
				else
					AoidenterbiddenzoneLC(robotpt,rect,5/*3*/,&pt);
				//Outofforbiddenzonezq(RobotInford robot, CRect rect, int i, int sign, Point target, int &j, Point &pt)
				/////////////////////////////////////////////////////////
				if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
				{
                    if(my_robot_pose[robotNo].x>70||my_robot_pose[robotNo].x<35) 
						ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
					else
					{ 
						ToPositionN(&my_robot_pose[robotNo],pt,60,rbV); 
					}
				}
				else
				{
					AdaptAngle(&my_robot_pose[robotNo],rbV,1);
				}
				AvoidSelfBump(&my_robot_pose[robotNo],pt,0,rbV);
			}    
		}
		break;
	case 28:
		{
			Point pt;
			pt.x = 40;
			pt.y = 50;
			
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
				ToPositionPD(&my_robot_pose[robotNo],pt,65,0,rbV);
			else
				//AdaptAngle(&my_robot_pose[robotNo],rbV,1);
				TurnToAnglePD(&my_robot_pose[robotNo],0.1*Pi,0,rbV);	
			AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
		}
		break;
	case 29:
		{
			Point pt;
			pt.x = 40;
			pt.y = 130;
			
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)		
				ToPositionPD(&my_robot_pose[robotNo],pt,55,0,rbV);
			else
				//AdaptAngle(&my_robot_pose[robotNo],rbV,1);//0��
				TurnToAnglePD(&my_robot_pose[robotNo],0.9*Pi,0,rbV);
			AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
		}
		break;
	case 30:
		{
			Point pt,goal;
			static int shootsign1 = 0;
			
			pt.x = 150;		//160
			pt.y = 120;		//
			
			LINEFORMULATION formu;
			formu.a = 1;
			formu.b = 3;
			formu.c = -520;
			
			if(BallPredictCharacter.Formu.b!=0)
				cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);
			else
			{
				goal.x = ball_point.x;
				goal.y = (520 - ball_point.x)/3;
			}
			
			double cs_k;
			cs_k = (goal.x-pt.x)/60+0.78;//0.9
			
			if(ball_point.x+3 * ball_point.y<520.0+15.0 && ball_point.x+3*ball_point.y>520.0-15.0 && ball_point.x>145		|| 
				(goal.x<220 && goal.x>170 && cal_2PointsDist(ball_point,goal)<BallPredictCharacter.velocity*fabs(goal.x- pt.x)/cs_k
				&& old_ball_pts[0].y<old_ball_pts[3].y && old_ball_pts[3].y<old_ball_pts[6].y)
				)
			{
				goal.x = 300;
				goal.y = 73.3;	//shootsign!=0
				ToPositionM(&my_robot_pose[robotNo],goal,80,rbV);
				shootsign1 = 3;
			}
			else
			{
				if(shootsign1!=0)
				{
					goal.x = 300;
					goal.y = 73.3;
					ToPositionM(&my_robot_pose[robotNo],goal,80,rbV);
					shootsign1--;
				}
				else
				{
					if(ball_point.x<my_robot_pose[robotNo].x && distRobot2Pt(my_robot_pose[robotNo],ball_point)<25)
					{
						if(old_ball_pts[0].y<old_ball_pts[3].y&&old_ball_pts[3].y<old_ball_pts[6].y)
							pt.y = 135;
						else
							pt.y = 95;
						ToPositionM(&my_robot_pose[robotNo],pt,80,rbV);
					}
					else
					{
						if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
						{
							ToPositionN(&my_robot_pose[robotNo],pt,70,rbV);//	ToPositionPD(&my_robot_pose[robotNo],pt,70,0,rbV);
							AvoidALLRobots(&my_robot_pose[robotNo],pt,60,rbV);
						}
						else
							TurnToAnglePD(&my_robot_pose[robotNo],-0.32175,0,rbV);	
					}
				}
			}
		}
		break;
	case 31:
		{
			Point pt,goal;
			static int shootsign2 = 0;
			pt.x = 150;	//160
			pt.y = 60;
			
			LINEFORMULATION formu;
			formu.a = 1;
			formu.b = -3;
			formu.c = 20;
			if(BallPredictCharacter.Formu.b!=0)
				cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);
			else
			{
				goal.x = ball_point.x;
				goal.y = (ball_point.x + 20)/3;
			}
			double cs_k;
			cs_k = cal_2PointsDist(pt,goal)/60+0.78;	//0.9
			
			if(ball_point.x-3*ball_point.y<20.0+15.0&&ball_point.x-3*ball_point.y>20.0-15.0 && ball_point.x>145 || (goal.x<220&&goal.x>170 &&
				cal_2PointsDist(ball_point,goal)<BallPredictCharacter.velocity*cal_2PointsDist(pt,goal)/cs_k
				&&old_ball_pts[0].y>old_ball_pts[3].y&&old_ball_pts[3].y>old_ball_pts[6].y))
			{
				goal.x = 300;
				goal.y = 166.667;
				ToPositionM(&my_robot_pose[robotNo],goal,80,rbV);
				shootsign2 = 3;
			}
			else
			{
				if(shootsign2!=0)
				{
					goal.x = 300;
					goal.y = 166.667;
					ToPositionM(&my_robot_pose[robotNo],goal,80,rbV);
					shootsign2--;
				}
				else
				{
					if(ball_point.x<my_robot_pose[robotNo].x&&distRobot2Pt(my_robot_pose[robotNo],ball_point)<25)
					{
						if(old_ball_pts[0].y>old_ball_pts[3].y&&old_ball_pts[3].y>old_ball_pts[6].y)
							pt.y = 45;
						else
							pt.y = 85;
						ToPositionM(&my_robot_pose[robotNo],pt,80,rbV);
					}
					else
					{
						if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
						{
							ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);//	ToPositionPD(&my_robot_pose[robotNo],pt,70,0,rbV);
							AvoidALLRobots(&my_robot_pose[robotNo],pt,60,rbV);
						}
						else
							TurnToAnglePD(&my_robot_pose[robotNo],0.4636476,0,rbV);	
					}
				}
			}
		}
		break;
	case 32:
		{
			Point target,pt; 
			target.x = 0;
			target.y = 0;
			double dist,distother;
			int OppNO=1;
			dist=distRobot2Pt(opp_robot_point[1],ball_point);
			int oppi;
			int dangerousflag=0;
			for(oppi=2;oppi<=5;oppi++)
			{
                distother=distRobot2Pt(opp_robot_point[oppi],ball_point);
				if(distother<dist)
				{
					dist=distother;
					OppNO=oppi;
				}
			}
			if(dist<=10)
			{
				dangerousflag=1;
			}
			
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<8&&ball_point.x<30&&ball_point.x>15)
			{
				if(ball_point.y>my_robot_pose[robotNo].y)
				{
					rbV->LeftValue = 25;
					rbV->RightValue = -25;
				}
				else
				{
					rbV->LeftValue = -25;
					rbV->RightValue = 25;
				}
			}
			/////////////////////////////////////////////////////////////////////////
			else
			{
				target.x = 20;// XIAOJINGQU;//20
				if(ball_point.x<35)
				{
					if(ball_point.x>=XIAOJINGQU + 5.0 && dangerousflag==1)
					{
                        LINEFORMULATION lineoppball;
						Point ballpt;
						ballpt.x=ball_point.x;
						ballpt.y=ball_point.y;
						Point opprbpt;
						opprbpt.x=opp_robot_point[OppNO].x;
						opprbpt.y=opp_robot_point[OppNO].y;
						StdLineForm(opprbpt,ballpt,&lineoppball);
						LINEFORMULATION formu;
						formu.a=1;
						formu.b=0;
						formu.c=-XIAOJINGQU-3.0;//23
						Point goal;
						if(cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1)
						{
							if(fabs(ball_point.y-goal.y)>4)
							{
								if(goal.y>ball_point.y)
								{
									if(goal.y-ball_point.y>8)
									{
										target.y=ball_point.y+6;
									}
									else if(goal.y-ball_point.y>6)
									{
										target.y=ball_point.y+4;
									}
									else
									{
										target.y=ball_point.y+2;
									}							
								}
								else
								{
									if(ball_point.y-target.y>8)
									{
										target.y=ball_point.y-6;
									}
									else if(ball_point.y-target.y>6)
									{
										target.y=ball_point.y-4;
									}
									else
									{
										target.y=ball_point.y-2;
									}							
								}	
							}
							else
							{
								target.y = ball_point.y;
							}
						}
						else
						{
							if(opprbpt.y>ball_point.y)
							{
								target.y=ball_point.y-6;
							}
							else
							{
								target.y=ball_point.y+6;
							}
						}	
					}
					else
					{
                        target.y = ball_point.y;
					}
				}
				else if(ball_point.x<60 && flag_1==1)//back
				{
					Point goal;
					LINEFORMULATION formu;
					formu.a = 1;
					formu.b = 0;
					formu.c = 0;
					if(cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1 && goal.y<115 && goal.y>65)
					{
						formu.c = -XIAOJINGQU-3.0;//23
						cn_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);
						target.y = goal.y;
						if(goal.y>90)
							target.y = target.y+2;
						if(goal.y<90)
							target.y = target.y-2;//?????
						//
						if(dangerousflag==1)
						{
							LINEFORMULATION lineoppball;
							Point ballpt;
							ballpt.x=ball_point.x;
							ballpt.y=ball_point.y;
							Point opprbpt;
							opprbpt.x=opp_robot_point[OppNO].x;
							opprbpt.y=opp_robot_point[OppNO].y;
							StdLineForm(opprbpt,ballpt,&lineoppball);
							Point goal2;
							if(cn_2LinesCrossPoint(&lineoppball,&formu,&goal2)!=-1)
							{
								if(fabs(goal2.y-target.y)>4)
								{
									if(goal2.y>target.y)
									{
										if(goal2.y-target.y>8)
										{
											target.y=target.y+4;
										}
										else if(goal2.y-target.y>6)
										{
											target.y=target.y+3;
										}
										else
										{
											target.y=target.y+2;
										}
									}
									else
									{
										if(target.y-goal2.y>8)
										{
											target.y=target.y-4;
										}
										else if(target.y-goal2.y>6)
										{
											target.y=target.y-3;
										}
										else
										{
											target.y=target.y-2;
										}
									}
								}	
							}
							else
							{
								if(opprbpt.y>ball_point.y)
								{
                                    target.y=target.y-4;
								}
								else
								{
									target.y=target.y+4;
								}	
							}
						}//

						if(defend_counter==0&&goal.y>90)
						{
							target.y = target.y-2;
						}
						if(defend_counter==0&&goal.y<90)
						{
							target.y = target.y+2;
						}
					}
					else
					{
						target.y = (ball_point.y-90)*target.x/ball_point.x+90;
					}
				}
				else //��ͣ����ȥ||ball_point.x>60
				{
					target.y = (ball_point.y-90)*target.x/ball_point.x+90;
				}
				/////////////////////////////////////////////////////////////////////////

                double Yvalue;
				float robotY;
                robotY=(float)my_robot_pose[robotNo].y;
				robotY2=(float)my_robot_pose[robotNo].y;
               	if(charrobot==1)
				{
					if(robotY>robotY1)
					{
						if(target.y>=90)
						{
							Yvalue=target.y+3;                   
						}
						else
						{
							Yvalue=target.y+7;//8                          
						}
						if(Yvalue>120)
							Yvalue= 120;
						if(Yvalue<70)
							Yvalue= 70;
						secondpt=(float)Yvalue - 9;// 10 9
					}
					else
					{
						if(target.y<=90)
						{
							Yvalue=target.y-3; 
						}
						else
						{
							Yvalue=target.y-7;//8
						}
						if(Yvalue<60)
							Yvalue= 60;
						if(Yvalue>110)
							Yvalue=110;
						secondpt=(float)Yvalue+ 9 ;//10 9	 
					}
				}
                else
                {
					Yvalue=target.y;
					if(target.y>90)
					{
						Yvalue=target.y;						   
					}
					else 
					{   
						Yvalue=target.y;							
					}
					if(Yvalue<60)
						Yvalue = 60;
					if(Yvalue>120)
						Yvalue= 120;
					if(target.y>90)
					{
						secondpt=(float)Yvalue-10-3;//11ȷ���ع�㣬�ɷŴ�
					}
					if(target.y<=90)
					{
						secondpt=(float)Yvalue+10+3;//11ȷ���ع�㣬�ɷŴ�
					}
				}
                target.y=Yvalue;
				///////////////////////////////////////////////////////////////////////////
                showtarget=(float)target.y;		
				showtarget1=secondpt;
                ///secondpt0= secondpt;
				if(distRobot2Pt(my_robot_pose[robotNo],target) > distError)
					 ToPositionN(&my_robot_pose[robotNo],target,80,rbV);	//70
				
				else
				{
					if(my_robot_pose[robotNo].theta < Pi)
						TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,NOCLOCK,rbV);
					else
						TurnToAnglePD(&my_robot_pose[robotNo],3*Pi/2,NOCLOCK,rbV);
				}
				
				//////////////////////////����������////////////////////
				if(target.y>90 && ball_point.y>my_robot_pose[robotNo].y && ball_point.y<132 && ball_point.x<XIAOJINGQU+4.0 && ball_point.x>XIAOJINGQU-4.0 && (robotY>robotY1||defend_counter==0))
				{
					pt.x = XIAOJINGQU+5.0;//25
					pt.y = 140;
					ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,70,2,rbV);
				}
				else if(target.y<90&&ball_point.y<my_robot_pose[robotNo].y&&ball_point.y>48 && ball_point.x<XIAOJINGQU+4.0 && ball_point.x>XIAOJINGQU-4.0 && (robotY<robotY1||defend_counter==0))
				{
					pt.x = XIAOJINGQU+5.0;//25
					pt.y = 40;
					ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,70,2,rbV);
				}
				////////////////////////////////////////////////////////////
				//	AvoidSelfBump(&my_robot_pose[robotNo],target,1,rbV);
			}
			
			///////////////////////////////////////////////////////////
			//����
			Point car5,cari;
			car5.x=my_robot_pose[5].x;			car5.y=my_robot_pose[5].y;
			cari.x=my_robot_pose[robotNo].x;	cari.y=my_robot_pose[robotNo].y;
			
			if(my_robot_pose[robotNo].y>65 && my_robot_pose[robotNo].y<115 && my_robot_pose[robotNo].x<15)
			{
				double angle,angle_e;
				angle=my_robot_pose[robotNo].theta;
				angle=cal_AngleTrimPI(angle);
				if (angle>Pi)
					angle_e=2*Pi-angle;
				if(angle>Pi/2)
					angle_e=Pi-angle;
				else
					angle_e=angle;
				if(angle_e>0.2)
					TurnToAnglePD(&my_robot_pose[robotNo],0,0,rbV);
			}

            if(ban_warning_flag2==100&&my_robot_pose[robotNo].y>65&&my_robot_pose[robotNo].y<115&&my_robot_pose[robotNo].x<15&&cal_2PointsDist(cari,car5)<12)
			{
				position(&my_robot_pose[robotNo],target,rbV);	
			} 
		}
		break;
	case 33://��������
		{      
			Point target,pt;

			robotY1=(float)my_robot_pose[robotNo].y;

			target.x=20;//22;//20
			target.y=secondpt;
			/*if(target.y<60)
			target.y=60;
			if(target.y>120)
			target.y=120;*/
			if(distRobot2Pt(my_robot_pose[robotNo],target) > distError)
				ToPositionN(&my_robot_pose[robotNo],target,80,rbV);//60
			else
			{
				if(my_robot_pose[robotNo].theta < Pi)
					TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,NOCLOCK,rbV);
				else
					TurnToAnglePD(&my_robot_pose[robotNo],3*Pi/2,NOCLOCK,rbV);
			}
			AvoidSelfBump(&my_robot_pose[robotNo],target,1,rbV);
			//////////////////////////����������////////////////////
			if(target.y>90 && ball_point.y>my_robot_pose[robotNo].y&&ball_point.y<132&&ball_point.x<XIAOJINGQU+4.0&&ball_point.x>XIAOJINGQU-4.0&&robotY1>robotY2)
			{
				pt.x = XIAOJINGQU+5;//25
				pt.y = 140;
				ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,70,2,rbV);
			}
			else if(target.y<90&&ball_point.y<my_robot_pose[robotNo].y&&ball_point.y>48&&ball_point.x<XIAOJINGQU+4.0&&ball_point.x>XIAOJINGQU-4.0&&robotY1<robotY2)
			{
				pt.x = XIAOJINGQU+5;//25
				pt.y = 40;
				ToPositionNew(&my_robot_pose[robotNo],ball_point,pt,70,2,rbV);
			}
			////////////////////////////////////////////////////////////
			////////////////////���ʱ��ת////////////////////////
			if(distRobot2Pt(my_robot_pose[robotNo],ball_point)<8&&ball_point.x<27&&ball_point.x>15)
			{	
				if(ball_point.y>my_robot_pose[robotNo].y)
				{
					rbV->LeftValue = 25;
					rbV->RightValue = -25;
				}
				else
				{	
					rbV->LeftValue = -25;
					rbV->RightValue = 25;
				}
			}
			
			///////////////////////////////////////////////////////////
			//����
			Point car5,cari;
			car5.x=my_robot_pose[5].x;			car5.y=my_robot_pose[5].y;
			cari.x=my_robot_pose[robotNo].x;	cari.y=my_robot_pose[robotNo].y;
			
			if(my_robot_pose[robotNo].y>65 && my_robot_pose[robotNo].y<115 && my_robot_pose[robotNo].x<15)
			{
				double angle,angle_e;
				angle=my_robot_pose[robotNo].theta;
				angle=cn_AngleTrimPI(angle);
				if(angle>Pi/2)
					angle_e=Pi-angle;
				else
					angle_e=angle;
				
				if(angle_e>0.2)
					TurnToAnglePD(&my_robot_pose[robotNo],0,0,rbV);
			}
			
			if(ban_warning_flag2==100 && my_robot_pose[robotNo].y>65 && my_robot_pose[robotNo].y<115 && my_robot_pose[robotNo].x<15
				&& cal_2PointsDist(cari,car5)<12)
			{
				position(&my_robot_pose[robotNo],target,rbV);	
			}	
		}
		break;
	case 38://�м����(used)
		{
			Point pt;
			pt.x = ball_point.x - 70;
			if(pt.x<50)
				pt.x = 50;
			pt.y = 90;
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				AvoidSelfRobots(&my_robot_pose[robotNo],pt,70,rbV);
				//AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
				//				AvoidSelfBump(&my_robot_pose[robotNo],rbV);		
			}
			else
				TurnToAnglePD(&my_robot_pose[robotNo],0,0,rbV);			
		}
		break;
	case 39://����ش�
		{
		/*if(timer<STARTTIME)
		{
		rbV->LeftValue = rbV->RightValue = 20;
		}
		else
		{
		rbV->LeftValue = -100;
		rbV->RightValue =-60;
		}*/
			
            if(timer<STARTTIME)
			{
				rbV->LeftValue = 40;
				rbV->RightValue =-40;
			}
			else
			{
				rbV->LeftValue = 0;
				rbV->RightValue =0;
			}
			/*if(dmDEG.DESKickLR ==0)
			{
			rbV->LeftValue = -40;
			rbV->RightValue =40;
			}
			else
			{
			rbV->LeftValue = 40;
			rbV->RightValue =-40;
		}*/
		}
		break;
	case 40://��������
		{
			if(timer<STARTTIME)//+5
			{
				rbV->LeftValue = rbV->RightValue = 0;
			}
			else 
			{
				rbV->LeftValue = 120;//60+(timer-STARTTIME)*5;
				rbV->RightValue = 120;//60+(timer-STARTTIME)*5;
			}
			/*if(timer<STARTTIME+8)
			{
			rbV->LeftValue =120; 
			rbV->RightValue = -120;
			}
			else 
			{
			rbV->LeftValue = 0;//60+(timer-STARTTIME)*5;
			rbV->RightValue = 0;//60+(timer-STARTTIME)*5;
		}*/
		}
		break;
	case 41://����ֱ��
		{
			rbV->LeftValue = 90;
			rbV->RightValue = 90;
		}
		break;
	case 42://���ٻ���
		{	//Vect_MidShoot(my_robot_pose[robotNo],ball_point,rbV);	
			//if(timer<STARTTIME+8)
			if(timer<2)
			{
				if(my_robot_pose[robotNo].y>90)
				{
				//	rbV->LeftValue = 10+timer*14;//90
				//	rbV->RightValue = 10+timer*8;//90
					TurnToAnglePD(&my_robot_pose[robotNo],Pi/15,0,rbV);
				}
				else
				{
				//	rbV->LeftValue = 10+timer*8;//90
			    //    rbV->RightValue = 10+timer*14;//90
					TurnToAnglePD(&my_robot_pose[robotNo],Pi/15,0,rbV);
				}
			}
			else
				/*
			{  	           
	            rbV->LeftValue = 80;//60+(timer-STARTTIME)*5;
				rbV->RightValue = 80;//60+(timer-STARTTIME)*5;
			}
			*/
			{
			Point goal;
			goal.x = 220;
			goal.y = 90;
			CS_ToPositionNew(&my_robot_pose[robotNo],ball_point,goal,1,rbV);
			}
		}
		break;
	case 43://�ҹ��仡��
		{
			
			rbV->LeftValue = 16;
			rbV->RightValue = 10;
		}
		break;
	case 44://����仡��
		{
			rbV->LeftValue = 10;//20
			rbV->RightValue = 16;//50;
		}
		break;
	case 46://����ֱ��
		{
			if(timer<STARTTIME-3)//+5
			{
				rbV->LeftValue = rbV->RightValue = 0;
			}
			else 
			{
				rbV->LeftValue = 70;//60+(timer-STARTTIME)*5;
				rbV->RightValue = 70;//60+(timer-STARTTIME)*5;
			}
		}
		break;
	case 47://������ϸ���x=40
		{
			if(ball_point.x<46&&ball_point.x>=35)
			{
				Point temp;
				if(ball_point.y>my_robot_pose[robotNo].y)
				{	
					temp.x = 50;
					temp.y = 140;
					if(ball_point.y<90)
					{
						temp.x = 50;
						temp.y = 120;
					}
				}
				else
				{
					temp.x = 50;
					temp.y = 40;
					if(ball_point.y>90)
					{
						temp.x = 50;
						temp.y = 60;
					}
				}
				ToPositionNew(&my_robot_pose[robotNo],ball_point,temp,65,2,rbV);
			}	
			else
			{
				if(ball_point.x>38&&distRobot2Pt(my_robot_pose[robotNo],ball_point)<8)
				{
					if(ball_point.y>90)
					{
						rbV->LeftValue = -25;
						rbV->RightValue = 25;
					}
					else
					{
						rbV->LeftValue = 25;
						rbV->RightValue = -25;
					}
				}
				else
				{
					Point pt;
					pt.x = 40;
					pt.y = ball_point.y;
					if(pt.y>120)
						pt.y = 135;
					if(pt.y<60)
						pt.y = 45;
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
					{
						ToPositionPD(&my_robot_pose[robotNo],pt,60,BallPredictCharacter.velocity,rbV);
						//					AvoidSelfBump(&my_robot_pose[robotNo],rbV);
					}
					else
					{
						if(ball_point.y<120&&ball_point.y>60)
							TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,0,rbV);
						else
							TurnToAnglePD(&my_robot_pose[robotNo],-Pi,0,rbV);
					}		
				}
			}
		}
		break;
	case 48://������ϸ���x=55
		{
			if(ball_point.x<60&&ball_point.x>49)
			{
				Point temp;
				if(ball_point.y>my_robot_pose[robotNo].y)
				{	
					temp.x = 60;
					temp.y = 140;
				}
				else
				{
					temp.x = 60;
					temp.y = 40;
				}
				ToPositionNew(&my_robot_pose[robotNo],ball_point,temp,60,2,rbV);
			}
			else
			{
				if(ball_point.x>38&&distRobot2Pt(my_robot_pose[robotNo],ball_point)<8)
				{
					if(ball_point.y>90)
					{
						rbV->LeftValue = -25;
						rbV->RightValue = 25;
					}
					else
					{
						rbV->LeftValue = 25;
						rbV->RightValue = -25;
					}
				}
				else
				{
					Point pt;
					pt.x = 55;
					pt.y = ball_point.y;
					if(ball_point.y>135)
						pt.y = 135;
					if(ball_point.y<45)
						pt.y = 45;
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
					{
						ToPositionPD(&my_robot_pose[robotNo],pt,60,BallPredictCharacter.velocity,rbV);
						//					AvoidSelfBump(&my_robot_pose[robotNo],rbV);
					}
					else
					{
						if(ball_point.y<120&&ball_point.y>60)
							TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,0,rbV);
						else
							TurnToAnglePD(&my_robot_pose[robotNo],-Pi,0,rbV);
						//TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,0,rbV);
					}
				}
			}
		}
		break;
	case 50:
		{
			Point pt={200,90};
			if(ball_point.x>197&& ball_point.y<80)
			{
				pt.x=197;
				pt.y=70;
			}
			if(ball_point.x>197&& ball_point.y>100)
			{
				pt.x=197;
				pt.y=110;
			}
			
			
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				ToPositionPD(&my_robot_pose[robotNo],pt,80,BallPredictCharacter.velocity,rbV);
			}
			else
			{
				if(ball_point.y<120&&ball_point.y>60)
					TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,0,rbV);
				else
					TurnToAnglePD(&my_robot_pose[robotNo],-Pi,0,rbV);
			}
			
			
			
			if(ball_point.x>190 && distRobot2Pt(my_robot_pose[robotNo],ball_point)<10)
			{
				if(ball_point.y>my_robot_pose[robotNo].y)
				{
					rbV->LeftValue = 50;
					rbV->RightValue = -50;
				}
				else
				{
					rbV->LeftValue = -50;
					rbV->RightValue = 50;
				}
			}
		}
		break;
	case 60://ȫ��Э��
		{
			Point pt;
			//����
			if(flag_1==1)
				pt.x = ball_point.x-30-BallPredictCharacter.velocity*10;
			else
				pt.x = ball_point.x-30;
			
			if(ball_point.x>110)
				pt.x = ball_point.x - 40;
			
			if(pt.x<0)
				pt.x=0;
			
			pt.y = 90+(ball_point.y-90)*pt.x/ball_point.x;
			
			if(pt.x>120)
			{
				if(pt.y>90 && pt.y<105)
					pt.y = 105;
				else if(pt.y<90 && pt.y>75)
					pt.y = 75;
			}
			if(pt.x<50)
				pt.x = 50;
			//����
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				ToPositionN(&my_robot_pose[robotNo],pt,90,rbV);
				AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,60,rbV);
			}
			else
			{
				if(ball_point.x<190)
					AdaptAngle(&my_robot_pose[robotNo],rbV,1);
				else
				{
					Point pt;
					pt.x = 220;
					pt.y = 90;
					TurnToPointPD(&my_robot_pose[robotNo],pt,0,rbV);
					AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,60,rbV);
				}
			}
		}
		break;
	case 61://��ǰ��(5-5);
		{
			MidActAndDefend(&my_robot_pose[robotNo],ball_point,rbV); 
		}
		break;
	case 62://��Э��  
		{
			Point	pt;
			pt.x = ball_point.x - NUMBERLAX;
			pt.y = ball_point.y + NUMBERLAY;
			if(pt.x<45)
				pt.x = 45;
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				
				/*if(distRobot2Pt(my_robot_pose[robotNo],pt)>20)
				{
				if(my_robot_pose[robotNo].x < pt.x)
				AvoidALLRobots(&my_robot_pose[robotNo],pt,70,rbV);
				else
				AvoidSelfRobots(&my_robot_pose[robotNo],pt,70,rbV);
			}*/
				AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,60,rbV);////////////
				
				AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
			}
			else
				AdaptAngle(&my_robot_pose[robotNo],rbV,1);
			//TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,0,rbV);	
		}
		break;
	case 63://��Э��
		{
			Point	pt;
			pt.x = ball_point.x - NUMBERLAX;
			pt.y = ball_point.y - NUMBERLAY;
			if(pt.x<45)
				pt.x = 45;
			OutOfForbbidenZone(my_robot_pose[robotNo],pt);
			if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
			{
				ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
				/*if(distRobot2Pt(my_robot_pose[robotNo],pt)>20)
				{
				if(my_robot_pose[robotNo].x < pt.x)
				AvoidALLRobots(&my_robot_pose[robotNo],pt,70,rbV);
				else
				AvoidSelfRobots(&my_robot_pose[robotNo],pt,70,rbV);
			}*/
				
				AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,70,rbV);/////////////
				AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
			}
			else
				//TurnToAnglePD(&my_robot_pose[robotNo],Pi/2,0,rbV);
				AdaptAngle(&my_robot_pose[robotNo],rbV,1);
		}
		break;
	case 64:
		{
			rbV->LeftValue = 90;
			rbV->RightValue = 90;
		}
		break;
	case 65:
		{
			if (timer<30)
			{
				timer++;
			}
			rbV->LeftValue = 100;//timer*2.3+50;//90
			rbV->RightValue = 100;//timer*2.3+50;//90
		}
		break;
	case 66://��Э��ֱ������
		{   
			static int shootsign=0,sign=0;
			Point	pt,homept,robotpt;
			homept.x=220;
			homept.y=90;
            //Point joint;
			/* double  Anglerb2R, Anglerpt2R,theta1;*/
			double theta,/*dx,dy,*/dx1,dy1,dx2,dy2,ds,ds1;
            LINEFORMULATION line_b2d;
            pt.x = ball_point.x -30;// 30;//NUMBERLAX
			pt.y = ball_point.y +25;// 25;//NUMBERLAY
			if(pt.x<45)
				pt.x = 45;
			//����Ҫת�ĽǶ�
			dx2=homept.x-my_robot_pose[robotNo].x;
			dy2=homept.y-my_robot_pose[robotNo].y;
			theta=atan2(dy2,dx2);
			theta = cn_AngleTrim2PI(theta);
            my_robot_pose[robotNo].theta= cn_AngleTrim2PI(my_robot_pose[robotNo].theta);
            robotpt.x=my_robot_pose[robotNo].x;robotpt.y=my_robot_pose[robotNo].y;
            StdLineForm(homept,robotpt,&line_b2d);
            ds=cn_PointLineDist(ball_point,&line_b2d);
            dx1 = ball_point.x - my_robot_pose[robotNo].x;
            dy1 = ball_point.y - my_robot_pose[robotNo].y;
			ds1=sqrt(dx1*dx1+dy1*dy1);
            if(ds1<40&&my_robot_pose[robotNo].y>(ball_point.y+5)&&my_robot_pose[robotNo].x<(ball_point.x-5)&&(fabs(ds)<10)&&
				(theta<Pi/12||theta<23*Pi/12||(11*Pi/12<theta&&theta<13*Pi/12))
				)
			{     
				ToPositionForShoot(&my_robot_pose[robotNo],ball_point,0,100,rbV);
				if(BallPredictCharacter.velocity<0.7)
					shootsign = 8;
				else
					shootsign = 3;
				
			}
			else
			{
				if(shootsign!=0)
				{   
                    ToPositionForShoot(&my_robot_pose[robotNo],ball_point,0,100,rbV);
                    shootsign--;
				}
				else
				{
					if(ball_point.x>185&&65<ball_point.y&&ball_point.y<115)
					{
						pt.x=160;
						pt.y=120;///////
                        theta=-0.147*Pi;//11*Pi/12;
					}
					if(pt.y>175)
                        pt.y=175;
					OutOfForbbidenZone(my_robot_pose[robotNo],pt);
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
					{
						ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
						AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,60,rbV);
						AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
					}
					else
					{
						TurnToAnglePD(&my_robot_pose[robotNo],theta,0,rbV);
                        if(theta<Pi/14||theta<27*Pi/14||(13*Pi/14<theta&&theta<15*Pi/14))
                            sign=1;
					}
					
				}	
			}
		}
		break;
	case 67://��Э��ֱ������
		{   
			static int shootsign=0,sign=0;
			Point	pt,homept,robotpt;
			homept.x=220;
			homept.y=90;
            //Point joint;
			//  double  /*Anglerb2R, Anglerpt2R,*/theta1;
			double theta,dx1,dy1,dx2,dy2,ds,ds1;
            LINEFORMULATION line_b2d;
            pt.x = ball_point.x -30;//30; //NUMBERLAX;
			pt.y = ball_point.y -25;//25; //NUMBERLAY;
			if(pt.x<45)
				pt.x = 45;
			//����Ҫת�ĽǶ�
			dx2=homept.x-my_robot_pose[robotNo].x;
			dy2=homept.y-my_robot_pose[robotNo].y;
			theta=atan2(dy2,dx2);
			theta = cn_AngleTrim2PI(theta);
			//joint.y=(ball_point.y-my_robot_pose[robotNo].y)*(220-my_robot_pose[robotNo].x)/(ball_point.x-my_robot_pose[robotNo].x)+90;
            my_robot_pose[robotNo].theta= cn_AngleTrim2PI(my_robot_pose[robotNo].theta);
            robotpt.x=my_robot_pose[robotNo].x;robotpt.y=my_robot_pose[robotNo].y;
            StdLineForm(homept,robotpt,&line_b2d);
            ds=cn_PointLineDist(ball_point,&line_b2d);
            dx1 = ball_point.x - my_robot_pose[robotNo].x;
            dy1 = ball_point.y - my_robot_pose[robotNo].y;
			ds1=sqrt(dx1*dx1+dy1*dy1);

            if(ds1<40&&sign==1&&my_robot_pose[robotNo].y<(ball_point.y-5)&&
				my_robot_pose[robotNo].x<(ball_point.x-5)&&(fabs(ds)<10)&&
				(theta<Pi/12||theta<23*Pi/12||(11*Pi/12<theta&&theta<13*Pi/12))
				)
			{     
				ToPositionForShoot(&my_robot_pose[robotNo],ball_point,0,100,rbV);
				if(BallPredictCharacter.velocity<0.7)
					shootsign = 8;
				else
					shootsign = 3;
				
			}
			else
			{
				if(shootsign!=0)
				{   
					//CS_ToPositionNew(&my_robot_pose[robotNo],ball_point,homept,0,rbV);
					ToPositionForShoot(&my_robot_pose[robotNo],ball_point,0,100,rbV);
                    shootsign--;
				}
				else
				{
					if(ball_point.x>185&&65<ball_point.y&&ball_point.y<115)
					{
						pt.x=160;
						pt.y=60;
                        theta=0.147*Pi;//Pi/12;
					}
					if(pt.y<7)
                        pt.y=7;
					OutOfForbbidenZone(my_robot_pose[robotNo],pt);
					if(distRobot2Pt(my_robot_pose[robotNo],pt)>distError)
					{
						ToPositionN(&my_robot_pose[robotNo],pt,80,rbV);
						AvoidSelfRobotsM(&my_robot_pose[robotNo],pt,60,rbV);
						AvoidBall(&my_robot_pose[robotNo],ball_point,pt,rbV);
					}
					else
					{
						// AdaptAngle(&my_robot_pose[robotNo],rbV,1);
						TurnToAnglePD(&my_robot_pose[robotNo],theta,0,rbV);
                        if(theta<Pi/14||theta<27*Pi/14||(13*Pi/14<theta&&theta<15*Pi/14))
							sign=1;
					}
				}	
			}
		}
		break;
	case 68://ȫ��Э������//����X>60�������ʹ��
		{
			int ptflag=0;
			Point Target,homept,homept1,targetball,pt,homept2;
			int iii=0;
			double theta,s,endtheta;
			s=35;
            homept.x=223;
			homept.y=90;
            pt.x=220;
			pt.y=90;
			if(ball_point.y>100)
				homept.y=100;
            if(ball_point.y<80)
				homept.y=80;
            homept1.x=0;
            homept1.y=90;
			if(ball_point.y>=110)
				homept1.y=105;
            if(ball_point.y<=70)
				homept1.y=75;
			if(ball_point.y>150)
			{
				homept2.x=35;
				homept2.y=130;
			}
			else if(ball_point.y>115)
			{
				homept2.x=15;
				homept2.y=115;
			}
			else if(ball_point.y>65)
			{
				homept2.x=0;
				homept2.y=90;
			}
			else if(ball_point.y>30)
			{
				homept2.x=15;
				homept2.y=65;
			}
			else
			{
				homept2.x=35;
				homept2.y=50;
			}
			
			/////////////////////////////ȷ��Э����/////////////////////////////////
			double yanchi68;
			yanchi68=0;
			double bvangle;
			bvangle=cn_AngleTrim2PI(BallPredictCharacter.angle);
			targetball.x=BallPredictCharacter.velocity*cos(bvangle)*yanchi68+ball_point.x;
            targetball.y=BallPredictCharacter.velocity*sin(bvangle)*yanchi68+ball_point.y;
			if(targetball.x>215)//200
			{   
				iii=1;
				theta=cn_LineAngle(homept2, targetball);
                Target.x=targetball.x-40;///50
                Target.y=targetball.y-tan(theta)*40;//
				
				
				
			}
			
			else if(targetball.x>140)
			{
				theta=cn_LineAngle(homept2, targetball);
                Target.x=targetball.x-40;///50
                Target.y=targetball.y-tan(theta)*40;//
			}
			else if(targetball.x>110)
			{    
				pt.x=targetball.x;
				pt.y=targetball.y;
				theta=cn_LineAngle(homept2, targetball);
                Target.x=targetball.x-40;///
                Target.y=targetball.y-tan(theta)*40;
				if(Target.x<45)
					Target.x=55;
				
                
				
			}
			else
			{ 
				ptflag=1;
				pt.x=targetball.x;
				pt.y=targetball.y;
				///if() 
				theta=cn_LineAngle(homept1, targetball);
				//Target.x=targetball.x-32;
				//Target.y=targetball.y-tan(theta)*32;
				Target.x=targetball.x-32;
				Target.y=targetball.y-tan(theta)*32;
				if(Target.x<=45)
				{ 
					Target.x=55; 
					if(targetball.y>135)
					{
						Target.x=targetball.x-15;
						Target.y=targetball.y-15;
						if(Target.y<135)
							Target.y=135;
					}
					if(targetball.y<45)
					{
						Target.x=targetball.x-15;
						Target.y=targetball.y+15;
						if(Target.y>45)
							Target.y=45;
					}
				}
				
				
			}
			
			if(Target.y<7)
				Target.y=7;
			if(Target.y>173)
				Target.y=173;
            //ȷ����������
            static int shootsign=0,sign=0,robotNum;
            OutOfForbbidenZone(my_robot_pose[robotNo],Target);
            if(distRobot2Pt(my_robot_pose[robotNo],Target)>distError)
			{
				////ToPositionN(&my_robot_pose[robotNo],Target,80,rbV);
				//CS_ToPositiontoAngle(&my_robot_pose[robotNo],Target,homept,90,rbV);
				//CS_ToPositiontoAngle(&my_robot_pose[robotNo],Target,homept,90,rbV);
				//AvoidSelfRobotsM(&my_robot_pose[robotNo],Target,60,rbV);
				CS_ToPosition68(&my_robot_pose[robotNo],ball_point,Target,60,EndProcessFlag,rbV);
				//AvoidBall(&my_robot_pose[robotNo],ball_point,Target,rbV);
				//AvoidSelfDeal(&my_robot_pose[robotNo], 30, rbV);
			}
            else
			{
				TurnToAnglePD(&my_robot_pose[robotNo],0,0,rbV);
				if(ptflag==1)
				{
					pt=TO_POINT(ball_point);
					TurnToPointPD(&my_robot_pose[robotNo],pt,0,rbV);
				}
				
				//AdaptAngle(&my_robot_pose[robotNo],rbV,1);
				
				//TurnToAnglePD(&my_robot_pose[robotNo],theta,0,rbV);
			}
			robotNum=robotNo;//��¼�����˵ĺ��룬���ڽ�ɫת��
		}
		break;

	default:
		{
			rbV->LeftValue = 0;
			rbV->RightValue = 0;
		}
		break;
	}
}
	
	
	double charPerformance(int charNo, RobotPose* pRobot,int robotNO)
	{
		float	result;
		int flag_1=0 , down=0;
		if(old_ball_pts[0].y > old_ball_pts[3].y && old_ball_pts[3].y > old_ball_pts[6].y)
			down = 1;
		if(old_ball_pts[0].x > old_ball_pts[3].x && old_ball_pts[3].x > old_ball_pts[6].x)
			flag_1 = 1;
		//static float secondpt11;
		switch(charNo)
		{
		case 1:
			{
				int boundAreaNo,errord;
				Point ballPt,tempPt;
				errord = 5;
				ballPt.x = ball_point.x;
				ballPt.y = ball_point.y;

				if(ballPt.x<errord)
					ballPt.x = errord;
				if(ballPt.y<errord)
					ballPt.y = errord;
				if(ballPt.x >wallright - errord)
					ballPt.x = wallright - errord;
				if(ballPt.y >walltop - errord)
					ballPt.y = walltop - errord;
	
				boundAreaNo = GetBoundAreaNo(ballPt);
				/*
					-------------------------------------------
					|   |                2                    |
					| 1 |--------------------------------------
					|   |               7                 | 3 |
					|   |                                 |   |
					-------------------------------------------
					|   |                                 |   |
					| 4 |               8                 | 6 |
					|   |--------------------------------------
					|   |                5                    |
					-------------------------------------------
				*/
				switch(boundAreaNo)
				{
				case	1:
					{
						tempPt.x = NUMBER2;
						tempPt.y = walltop - NUMBER2;
					}
					break;
				case	2:
					{
						tempPt.x = wallright;
						tempPt.y = walltop - NUMBER2;
					}
					break;
				case	3:
					{
						tempPt.x = wallright;
						tempPt.y = walltop/2;
					}
					break;
				case	4:
					{
						tempPt.x = NUMBER2;
						tempPt.y = NUMBER2;
					}
					break;
				case	5:
					{
						tempPt.x = wallright;
						tempPt.y = NUMBER2;
					}
					break;
				case	6:
					{
						tempPt.x = wallright;
						tempPt.y = walltop/2;
					}
					break;
				default:
					{
						tempPt.x = wallright;
						tempPt.y = walltop/2;
					}
					break;
				}
				result = float(GetCharPerformance(1,*pRobot,ballPt,tempPt));
				if(oldResult[robotNO]==1||oldResult[robotNO]==2)
				{
					result=result*0.92;//0.95
					if(EndProcessFlag==1)//�������ĩ�˺���
					{
						result=result*0.5;
					}
				}
			}
			break;
		case 2://����
			{
				Point dpt;
				dpt.x = wallright + 3;
				dpt.y = walltop/2;
				Point ballPt;

				ballPt.x=ball_point.x;
				ballPt.y=ball_point.y;

				int k,dist1,dist;
				// 			double deltax;
				//			deltax = 5;
				result = (float)GetCharPerformance(2,*pRobot,ballPt,dpt);
				if(oldResult[robotNO]==1|| oldResult[robotNO] == 2)
				{
					result = result * 0.92;//0.95
					if(EndProcessFlag == 1)
					{
						result = result * 0.5;
					}
				}					
			}
			break;
		case 3://
			{
				Point ballPt;

				ballPt.x = ball_point.x;
				ballPt.y = ball_point.y;
				result = float(distRobot2Pt(*pRobot,ballPt));
				if(oldResult[robotNO]==3)
				{
					result = result * 0.92;//0.95
				}
			}
			break;
		case 4:
			{
				Point target;
				target.x = 20;
				if(ball_point.x<35)
				{
					target.y = ball_point.y;
				}
				else if(ball_point.x < 60 && flag_1 == 1)
				{				
					Point goal;
					LINEFORMULATION formu;
					formu.a = 1;
					formu.b = 0;
					formu.c = 0;
					if(cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1&&goal.y<115&&goal.y>65)
					{
						formu.c = -23;
						cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);
						target.y = goal.y;
					}
					else
					{
						target.y = (ball_point.y-90)*target.x/ball_point.x+90;
					}
				}
				else
				{
					//target.y = 90;	
					target.y = (ball_point.y-90) * target.x / ball_point.x + 90;
				}
				if(target.y < 60)
					target.y = 60;
				if(target.y>120)
					target.y = 120;
				result = float(distRobot2Pt(*pRobot,target));
				if(oldResult[robotNO] == 4)
				{
					result = float(result*0.9);
				}
			}
			break;
		case 5:
			{
				Point pt,goal;
				pt.y = 135;
				LINEFORMULATION formu;
				formu.a = 0;
				formu.b = 1;
				formu.c = -135;
				if(cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal) != -1 && goal.x < 40 && goal.x > 5)
					pt.x = goal.x;
				else
				{
					pt.x = ball_point.x * 45 / fabs(ball_point.y-90);
					if(pt.x > 40)
						pt.x = 40;
					if(pt.x < 5)
						pt.x = 5;
				}
				if(ball_point.y < 135)
					pt.x = 20;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 5)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 6:
			{
				Point pt,goal;
				pt.y = 45;
				LINEFORMULATION formu;
				formu.a = 0;
				formu.b = 1;
				formu.c = -45;
				if(cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1&&goal.x<40&&goal.x>5)
					pt.x = goal.x;
				else
				{
					pt.x = ball_point.x * 45 / fabs(90-ball_point.y);
					if(pt.x > 40)
						pt.x = 40;
					if(pt.x < 5)
						pt.x = 5;
				}
				if(ball_point.y > 45)
					pt.x = 20;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 6)
				{
					result=float(result*0.9);
				}
				
			}
			break;
		case 7:
			{
				Point pt;
				pt.x = 20;
				if(ball_point.x<25)
					pt.y = ball_point.y;
				else
				{
					pt.y = 20*(ball_point.y -90)/ball_point.x + 90 + 5  ;
				}
				if(ball_point.x < 13 && ball_point.y <= 105 && ball_point.y > 65)
					pt.y = ball_point.y + 4;
				if(pt.y>120)
					pt.y = 120;
				if(pt.y<72)
					pt.y = 72;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 7)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 8:
			{
				Point pt;
				pt.x = 20;
				if(ball_point.x<25)
					pt.y = ball_point.y;
				else
				{
					pt.y = 20*(ball_point.y -90)/ball_point.x + 90 - 5  ;
				}
				if(ball_point.x < 13 && ball_point.y <= 105 && ball_point.y > 65)
					pt.y=ball_point.y-4;
				if(pt.y>108)
					pt.y = 108;
				if(pt.y<60)
					pt.y = 60;
				
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 8)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 9:
			{
				Point pt;
				pt.y = 120;
				pt.x = ball_point.x * 30 / fabs(ball_point.y - 90);
				if(pt.x < 9)
					pt.x = 9;
				if(pt.x > 15)
					pt.x = 15;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 9)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 10:
			{
				Point pt;
				pt.y = 60;
				pt.x = ball_point.x * 30 / fabs(90 - ball_point.y);
				if(pt.x < 9)
					pt.x = 9;
				if(pt.x > 20)
					pt.x = 15;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 10)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 11:
			{
				Point pt;
				pt.x = 130;
				pt.y = 90;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 11)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 12:
			{
				result = 100;
			}
			break;
		case 13:
			{
				Point pt;
				pt.x = ball_point.x - 30;
				pt.y = ball_point.y + 30;
				if(pt.x < 40)
					pt.x = 40;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 13)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 14:
			{
				Point pt;
				pt.x = ball_point.x - 30;
				pt.y = ball_point.y - 30;
				if(pt.x<40)
					pt.x = 40;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 14)
				{
					result = (float)result * 0.9;
				}
			}
			break;
		case 15:
			{
				Point pt;
				pt.x = 40;//45
				pt.y = ball_point.y + 4;
				if(pt.y < 95)
					pt.y = 95;
				else if(pt.y > 125)
					pt.y = 125;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==15)
				{
					result=result*0.9;
				}
			}
			break;
		case 16:
			{
				Point pt;
				pt.x = 40;//45
				pt.y = ball_point.y - 4;
				if(pt.y > 85)
					pt.y = 85;
				else if(pt.y < 55)
					pt.y = 55;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 16)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 17:
			{
				Point pt;
				pt.x = 30;
				pt.y = 140;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 17)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 18:
			{
				Point pt;	
				pt.x = 45;
				pt.y = 90;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==18)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 19:
			{
				Point pt;
				pt.x = 30;
				pt.y = 40;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 19)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 20:
			{
				Point pt,target;
				pt.y = 120;
				pt.x = ball_point.x*30/fabs(ball_point.y-90);
				target.x=pt.x;
				///////////////////////////////////////////////////////////
				if(target.x >= 15&&target.x <= 24)
					pt.x = 20;
					/*	if(target.x>24)
					{
					pt.y=20*(ball_point.y -90)/ball_point.x + 90;
					pt.x=20;
					}
				*/
				///////////////////////////////////////////////////////////
				if(pt.x < 4)
					pt.x = 4;
				if(pt.x >= 20)
					pt.x = 20;
				
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 20)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 21:	
			{
				Point pt,target;
				pt.y = 60;
				pt.x = ball_point.x*30/fabs(ball_point.y-90);
				target.x = pt.x;
				///////////////////////////////////////////////////////////
				if(target.x >= 15 && target.x <= 24)
					pt.x = 20;
					/*if(target.x>24)
					{
					pt.y=20*(ball_point.y -90)/ball_point.x + 90;
					pt.x=20;
			}*/
				///////////////////////////////////////////////////////////
				if(pt.x < 4)
					pt.x = 4;
				if(pt.x >= 20)
					pt.x = 20;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 21)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 22:
			{
				Point pt,target;
				pt.y = 45;
				
				pt.x = ball_point.x * 35 / fabs(ball_point.y-80);
				target.x = pt.x;
				if(target.x <= 9)
					pt.x = 5.5;
				else if(target.x >= 35)
					pt.x = 35;
				if(ball_point.y > 48)
					pt.x = 30;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 22)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 23:
			{	
				Point target;
				target.x = 20;
				if(ball_point.x<35)
				{
					target.y = ball_point.y;
				}
				else if(ball_point.x < 60 && flag_1 == 1)
				{
					Point goal;
					LINEFORMULATION formu;
					formu.a = 1;
					formu.b = 0;
					formu.c = 0;
					if(cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal) != -1 && goal.y < 115 && goal.y > 65)
					{
						formu.c = -23;
						cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);
						target.y = goal.y;
					}
					else
					{
						target.y = (ball_point.y-90) * target.x / ball_point.x + 90;
					}
				}
				else
				{
					//target.y = 90;	
					target.y = (ball_point.y-90) * target.x / ball_point.x + 90;			
				}
				if(target.y < 60)
					target.y = 60;
				if(target.y > 120)
					target.y = 120;
				if(target.y > 90)
					target.y = target.y - 13;
				else
					target.y = target.y + 13;
				result = float(distRobot2Pt(*pRobot,target));
				if(oldResult[robotNO] == 23)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 24:
			{
				Point pt;
				pt.x = 20;
				pt.y = (ball_point.y-90)*pt.x / ball_point.x + 90;
				if(pt.y < 70)
					pt.y = 70;
				if(pt.y > 110)
					pt.y = 110;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 24)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 25:
			{
				Point pt;
				pt.x = 50;
				pt.y = 90;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 25)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 26:
			{
				Point ballPt;
				ballPt.x = ball_point.x;
				ballPt.y = ball_point.y;
				result = float(distRobot2Pt(*pRobot,ballPt));
			}
			break;
		case 27:
			{
				Point pt,target;
				
				pt.y = 135;
				pt.x = ball_point.x * 35 / fabs(ball_point.y - 100);
				target.x = pt.x;
				if(target.x <= 9)
					pt.x = 5.5;
				else if(target.x >= 35)
					pt.x = 35;
				if(ball_point.y < 132)
					pt.x=30;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 27)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 28:
			{
				Point pt;
				pt.x = 40;
				pt.y = 50;
				result = float(distRobot2Pt(*pRobot,pt));
			}
			break;
		case 29:
			{
				Point pt;
				pt.x = 40;
				pt.y = 130;
				result = float(distRobot2Pt(*pRobot,pt));
			}
			break;
		case 30:
			{
				Point pt;
				pt.x = 150;
				pt.y = 120;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==30)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 31:
			{
				Point pt;
				pt.x = 150;
				pt.y = 60;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 31)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 32:
			{
				
				Point target, ball_point;
				RobotPose opp_robot[6];
				ball_point.x = ball_point.x;
				ball_point.y = ball_point.y;
				opp_robot[1].x = opp_robot_point[1].x;
				opp_robot[1].y = opp_robot_point[1].y;
				opp_robot[1].theta = 0;
				target.x = 0;
				target.y = 0;
				target.x = 20;
				double dist,distother;
				int OppNO = 1;
				dist=distRobot2Pt(opp_robot[1],ball_point);
				int oppi;
				int dangerousflag=0;
				for(oppi=2;oppi<=5;oppi++)
				{
					distother=distRobot2Pt(opp_robot[oppi],ball_point);
					if(distother<dist)
					{
						dist=distother;
						OppNO=oppi;
					}
				}
				if(dist<=10)
				{
					dangerousflag=1;
				}
				if(ball_point.x<35)
				{
					if(ball_point.x>=25&&dangerousflag==1)
					{
						LINEFORMULATION lineoppball;
						Point ballpt;
						ballpt.x=ball_point.x;
						ballpt.y=ball_point.y;
						Point opprbpt;
						opprbpt.x=opp_robot_point[OppNO].x;
						opprbpt.y=opp_robot_point[OppNO].y;
						StdLineForm(opprbpt,ballpt,&lineoppball);
						LINEFORMULATION formu;
						formu.a=1;
						formu.b=0;
						formu.c=-23;
						Point goal;
						if(cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1)
						{
							if(fabs(ball_point.y-goal.y)>4)
							{
								if(goal.y>ball_point.y)
								{
									if(goal.y-ball_point.y>8)
									{
										target.y=ball_point.y+6;
									}
									else if(goal.y-ball_point.y>6)
									{
										target.y=ball_point.y+4;
									}
									else
									{
										target.y=ball_point.y+2;
									}
									
								}
								else
								{
									if(ball_point.y-target.y>8)
									{
										target.y=ball_point.y-6;
									}
									else if(ball_point.y-target.y>6)
									{
										target.y=ball_point.y-4;
									}
									else
									{
										target.y=ball_point.y-2;
									}
									
								}
								
							}
							else
							{
								target.y = ball_point.y;
							}
						}
						else
						{
							if(opprbpt.y>ball_point.y)
							{
								target.y=ball_point.y-6;
							}
							else
							{
								target.y=ball_point.y+6;
							}
						}
						
					}
					else
					{
						target.y = ball_point.y;
					}
				}
				else if(ball_point.x<60 && flag_1==1)//back
				{
					Point goal;
					LINEFORMULATION formu;
					formu.a = 1;
					formu.b = 0;
					formu.c = 0;
					if(cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal)!=-1&&goal.y<115&&goal.y>65)
					{
						formu.c = -23;
						cal_2LinesCrossPoint(&BallPredictCharacter.Formu,&formu,&goal);
						target.y = goal.y;
						if(goal.y>90)
							target.y = target.y+2;
						if(goal.y<90)
							target.y = target.y-2;
						if(dangerousflag==1)
						{
							LINEFORMULATION lineoppball;
							Point ballpt;
							ballpt.x=ball_point.x;
							ballpt.y=ball_point.y;
							Point opprbpt;
							opprbpt.x=opp_robot_point[OppNO].x;
							opprbpt.y=opp_robot_point[OppNO].y;
							StdLineForm(opprbpt,ballpt,&lineoppball);
							Point goal2;
							if(cal_2LinesCrossPoint(&lineoppball,&formu,&goal2)!=-1)
							{
								if(fabs(goal2.y-target.y)>4)
								{
									if(goal2.y>target.y)
									{
										if(goal2.y-target.y>8)
										{
											target.y=target.y+4;
										}
										else if(goal2.y-target.y>6)
										{
											target.y=target.y+3;
										}
										else
										{
											target.y=target.y+2;
										}
									}
									else
									{
										if(target.y-goal2.y>8)
										{
											target.y=target.y-4;
										}
										else if(target.y-goal2.y>6)
										{
											target.y=target.y-3;
										}
										else
										{
											target.y=target.y-2;
										}
									}
								}
								
							}
							else
							{
								if(opprbpt.y>ball_point.y)
								{
									target.y=target.y-4;
								}
								else
								{
									target.y=target.y+4;
								}
								
							}
							
							
						}
						if(defend_counter == 0&&goal.y>90)
						{
							target.y = target.y-2;
						}
						if(defend_counter == 0&&goal.y<90)
						{
							target.y = target.y+2;
						}
						
					}
					else
					{
						target.y = (ball_point.y-90)*target.x/ball_point.x+90;
					}
				}
				else
				{
					target.y = (ball_point.y-90)*target.x/ball_point.x+90;
				}
				
				if(target.y<60)
					target.y = 60;
				if(target.y>120)
					target.y = 120;
				if(target.y>=90)
					secondpt1=(float)target.y-13;
				else 
					secondpt1=(float)target.y+13;
				//	bool DONE=TRUE;
				// secondpt11=secondpt1;
				result = float(distRobot2Pt(*pRobot,target));
				if(oldResult[robotNO]==32)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 33://
			{	
				Point target;
				target.x = 20;
				target.y=secondpt1;
				result = float(distRobot2Pt(*pRobot,target));
				if(oldResult[robotNO]==33)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 38:
			{
				Point pt;
				pt.x = ball_point.x - 70;
				if(pt.x<50)
					pt.x = 50;
				pt.y = 90;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==38)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 39://
			{	
				if(pRobot->x == my_robot_pose[1].x && pRobot->y == my_robot_pose[1].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 40://
			{
				if(pRobot->x == my_robot_pose[2].x && pRobot->y == my_robot_pose[2].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 41://
			{
				if(pRobot->x == my_robot_pose[1].x && pRobot->y == my_robot_pose[1].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 42://
			{
				if(pRobot->x == my_robot_pose[1].x && pRobot->y == my_robot_pose[1].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 43://
			{
				if(pRobot->x == my_robot_pose[1].x && pRobot->y == my_robot_pose[1].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 44://
			{
				if(pRobot->x == my_robot_pose[1].x && pRobot->y == my_robot_pose[1].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 45:
			{
				Point pt;
				if (ball_point.y >= 160)
				{
					pt.x = int(wallright*.75);
					pt.y = int(walltop*.75);
				}
				else if (ball_point.y >= 130 && ball_point.y < 160)
				{
					pt.x = 180;
					pt.y = 90;
				}
				else if (ball_point.y >= 110 && ball_point.y < 130)
				{
					pt.x = 185;
					pt.y = 90;
				}
				else
				{
					pt.x = 190;
					pt.y = 90;
				}
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==45)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 46://
			{
				if(pRobot->x == my_robot_pose[1].x && pRobot->y == my_robot_pose[1].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 47:
			{
				Point pt;
				pt.x = 40;
				pt.y = ball_point.y;
				if(ball_point.y > 120)
					pt.y = 135;
				if(ball_point.y < 60)
					pt.y = 45;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 47)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 48:
			{
				Point pt;
				pt.x = 55;
				pt.y = ball_point.y;
				if(ball_point.y>135)
					pt.y = 155;
				if(ball_point.y<45)
					pt.y = 45;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==48)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 50:
			{
				Point pt={200,90};
				
				result = float(distRobot2Pt(*pRobot,pt));
			}
			break;
		case 60:
			{
				Point pt;
				if(flag_1==1)
					pt.x = ball_point.x - 30 - BallPredictCharacter.velocity*7;
				else
					pt.x = ball_point.x - 30;
				if(ball_point.x > 200)
					pt.x = ball_point.x - 40;
				if(pt.x < 0)
					pt.x = 0;
				pt.y = 90 + (ball_point.y-90) * pt.x / ball_point.x;
				if(pt.x > 120)
				{
					if(pt.y > 90 && pt.y < 105)
						pt.y = 105;
					else if(pt.y < 90 && pt.y > 75)
						pt.y = 75;
				}
				if(pt.x < 50)
					pt.x = 50;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==60)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 61:
			{
				Point pt;
				pt.x = 125;
				pt.y = ball_point.y;
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==61)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 62:
			{
				Point	pt;
				pt.x = ball_point.x - NUMBERLAX;
				pt.y = ball_point.y + NUMBERLAY;
				
				if(pt.x<40&&pt.y>45)
				{
					pt.x = 40;
					pt.y = 45;
				}
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==62)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 63:
			{
				Point	pt;
				pt.x = ball_point.x - NUMBERLAX;
				pt.y = ball_point.y - NUMBERLAY;
				//		if(pRobot->y<ball_point.y+10)
				//			pt.x = ball_point.x;
				if(pt.x < 40 && ball_point.y < 135)
				{
					pt.x = 40;
					pt.y = 135;
				}
				if(pt.y < 5)
					pt.y = 5;
				
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 63)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 64:
			{
				if(pRobot->x == my_robot_pose[2].x && pRobot->y == my_robot_pose[2].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 65:
			{
				if(pRobot -> x == my_robot_pose[1].x && pRobot -> y == my_robot_pose[1].y)
					result = 0;
				else
					result = 10000;
			}
			break;
		case 66:
			{
				Point	pt;
				pt.x = ball_point.x - NUMBERLAX;
				pt.y = ball_point.y + NUMBERLAY;
				
				if(pt.x < 40 && pt.y > 45)
				{
					pt.x = 40;
					pt.y = 45;
				}
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO] == 66)
				{
					result=float(result * 0.9);
				}
			}
			break;
		case 67:
			{
				Point	pt;
				pt.x = ball_point.x - NUMBERLAX;
				pt.y = ball_point.y - NUMBERLAY;
				//		if(pRobot->y<ball_point.y+10)
				//			pt.x = ball_point.x;
				if(pt.x<40 && ball_point.y < 135)
				{
					pt.x = 40;
					pt.y = 135;
				}
				if(pt.y<5)
					pt.y = 5;
				
				result = float(distRobot2Pt(*pRobot,pt));
				if(oldResult[robotNO]==67)
				{
					result=float(result*0.9);
				}
			}
			break;
		case 68:
			{
				
				Point Target,homept,homept1,targetball,homept2;//,pt
				double theta;
				homept.x=223;
				homept.y=90;
				if(ball_point.y>100)
					homept.y=100;
				if(ball_point.y<80)
					homept.y=80;
				homept1.x=0;
				homept1.y=90;
				if(ball_point.y>=110)
					homept1.y=105;
				if(ball_point.y<=70)
					homept1.y=75;
				if(ball_point.y>150)
				{
					homept2.x=35;
					homept2.y=130;
				}
				else if(ball_point.y>115)
				{
					homept2.x=15;
					homept2.y=115;
				}
				else if(ball_point.y>65)
				{
					homept2.x=0;
					homept2.y=90;
				}
				else if(ball_point.y>30)
				{
					homept2.x=15;
					homept2.y=65;
				}
				else
				{
					homept2.x=35;
					homept2.y=50;
				}
				double yanchi68;
				yanchi68 = 0;
				double bvangle;
				bvangle = cal_AngleTrim2PI(BallPredictCharacter.angle);
				targetball.x = BallPredictCharacter.velocity*cos(bvangle)*yanchi68+ball_point.x;
				targetball.y = BallPredictCharacter.velocity*sin(bvangle)*yanchi68+ball_point.y;
				if(targetball.x>215)
				{   
					theta=cal_LineAngle(homept2, targetball);
					Target.x=targetball.x-50;
					Target.y=targetball.y-tan(theta)*50;
					
				}
				
				else if(targetball.x>140)
				{
					theta=cal_LineAngle(homept2, targetball);
					Target.x=targetball.x-50;
					Target.y=targetball.y-tan(theta)*50;
					
					
				}
				else if(targetball.x>110)
				{    
					
					theta=cal_LineAngle(homept2, targetball);
					Target.x=targetball.x-50;
					Target.y=targetball.y-tan(theta)*50;
					if(Target.x<45)
						Target.x=55;
				}
				else
				{ 
					
					theta=cal_LineAngle(homept1, targetball);
					//Target.x=targetball.x-32;
					//Target.y=targetball.y-tan(theta)*32;
					Target.x=targetball.x-50;
					Target.y=targetball.y-tan(theta)*50;
					if(Target.x<=45)
					{ 
						Target.x=55; 
						if(targetball.y>135)
						{
							Target.x=targetball.x-15;
							Target.y=targetball.y-15;
							if(Target.y<135)
								Target.y=135;
						}
						if(targetball.y<45)
						{
							Target.x=targetball.x-15;
							Target.y=targetball.y+15;
							if(Target.y<45)
								Target.y=45;
						}
					}
					
				}
				/*if(ball_point.x>185&&65<ball_point.y&&ball_point.y<=90)     
				{   
				
				  Target.x=160;
				  Target.y=65;
				  
					}
					if(ball_point.x>185&&90<=ball_point.y&&ball_point.y<=115)
					{   
					
					  Target.x=160;
					  Target.y=115;
					  
						}
				*/
				if(Target.y<7)
					Target.y=7;
				if(Target.y>173)
					Target.y=173;
				result = float(distRobot2Pt(*pRobot,Target));
				if(oldResult[robotNO]==68)
				{
					result=result*0.9;
				}
			}
			break;
		default:
			Point ball_point;
			ball_point.x = ball_point.x;
			ball_point.y = ball_point.y;
			result = float(distRobot2Pt(*pRobot,ball_point));
			break;
		}
		
		return result;
	}
	int GetBoundAreaNo(Point pt)
/*
	-------------------------------------------
	|   |                2                    |
	| 1 |--------------------------------------
	|   |               7                 | 3 |
	|   |                                 |   |
	-------------------------------------------
	|   |                                 |   |
	| 4 |               8                 | 6 |
	|   |--------------------------------------
	|   |                5                    |
	-------------------------------------------
*/
	{
		int	boundAreaNO1;
		if(pt.y>walltop/2)
		{
			if(pt.x<15)//pt.y<walltop-7&&
				boundAreaNO1 = 1;
			else if(pt.y>walltop-15)
				boundAreaNO1 = 2;
			else if(pt.x>wallright-15)
				boundAreaNO1=3;
			else
				boundAreaNO1=7;
		}
		else
		{
			if(pt.x<15)//pt.y>7&&
				boundAreaNO1 = 4;
			else if(pt.y<15)//
				boundAreaNO1 = 5;
			else if(pt.x>wallright-15)
				boundAreaNO1=6;
			else
				boundAreaNO1=8;
		}
		return boundAreaNO1;
	}

	double GetCharPerformance(int no, RobotPose myRobot, Point ball_point, Point dpt)
	{
		double	k,angle1,angle,angle2,result,k1,ddist;
		Point rpt;
		int dist;
		int angleforpi,angle2forpi;

		angle2 = cn_AngleTrim2PI(myRobot.theta);
		rpt.x = myRobot.x;
		rpt.y = myRobot.y;


		angle = Getpt2ptAngle(ball_point,dpt);
		angle1 = Getpt2ptAngle(rpt,ball_point);
		angle = angle - angle1;
		angle2 = angle1 - angle2;
		angle2 = cal_AngleTrim2PI(angle2);//trim theta to between 0 and 2pi

		if(angle2>Pi)//(0~Pi)
		angle2 = 2*Pi  -  angle2;
		if(angle2>Pi/2)//(0~Pi/2)
		angle2 = Pi - angle2;

		angle = cal_AngleTrim2PI(angle);

		if(angle>Pi)//(0~Pi)
		angle = 2*Pi - angle;

		ddist = distRobot2Pt(myRobot,ball_point);
		dist = ddist;
		if(angle<(Pi/18))//10
		{
		angleforpi = 0;
		}
		else if(angle<(Pi/9))//20
		{
		angleforpi = 10;
		}
		else if(angle<(Pi/6))//30
		{
		angleforpi = 20;
		}
		else if(angle<(2*Pi/9))//40
		{
		angleforpi = 30;
		}
		else if(angle<(5*Pi/18))//50
		{
		angleforpi = 40;
		}
		else if(angle<(6*Pi/18))//60
		{
		angleforpi = 50;
		}
		else if(angle<(7*Pi/18))//70
		{
		angleforpi = 60;
		}
		else if(angle<(8*Pi/18))//80
		{
		angleforpi = 70;
		}
		else if(angle<(9*Pi/18))//90
		{
		angleforpi = 80;
		}
		else if(angle<(10*Pi/18))//100
		{
		angleforpi = 90;
		}
		else if(angle<(11*Pi/18))//110
		{
		angleforpi = 100;
		}
		else if(angle<(12*Pi/18))//120
		{
		angleforpi = 110;
		}
		else if(angle<(13*Pi/18))//130
		{
		angleforpi = 120;
		}
		else if(angle<(14*Pi/18))//140
		{
		angleforpi = 130;
		}
		else if(angle<(15*Pi/18))//150
		{
		angleforpi = 140;
		}
		else if(angle<(16*Pi/18))//160
		{
		angleforpi = 150;
		}
		else if(angle<(17*Pi/18))//170
		{
		angleforpi = 160;
		}
		else
		{
		angleforpi = 170;
		}



		if(angle2<(Pi/18))//10
		{
		angle2forpi = 0;
		}
		else if(angle2<(Pi/9))//20
		{
		angle2forpi = 10;
		}
		else if(angle2<(Pi/6))//30
		{
		angle2forpi = 20;
		}
		else if(angle2<(2*Pi/9))//40
		{
		angle2forpi = 30;
		}
		else if(angle2<(5*Pi/18))//50
		{
		angle2forpi = 40;
		}
		else if(angle2<(6*Pi/18))//60
		{
		angle2forpi = 50;
		}
		else if(angle2<(7*Pi/18))//70
		{
		angle2forpi = 60;
		}
		else if(angle2<(8*Pi/18))//80
		{
		angle2forpi = 70;
		}
		else if(angle2<(9*Pi/18))//90
		{
		angle2forpi = 80;
		}
		else
		{
		angle2forpi = 90;
		}


		if(angleforpi==0&&angle2forpi==0)
		{
		result = charPerformancescore00[dist];
		}
		if(angleforpi==0&&angle2forpi==10)
		{
		result = charPerformancescore010[dist];
		}
		if(angleforpi==0&&angle2forpi==20)
		{
		result = charPerformancescore020[dist];
		}
		if(angleforpi==0&&angle2forpi==30)
		{
		result = charPerformancescore030[dist];
		}
		if(angleforpi==0&&angle2forpi==40)
		{
		result = charPerformancescore040[dist];
		}
		if(angleforpi==0&&angle2forpi==50)
		{
		result = charPerformancescore050[dist];
		}
		if(angleforpi==0&&angle2forpi==60)
		{
		result = charPerformancescore060[dist];
		}
		if(angleforpi==0&&angle2forpi==70)
		{
		result = charPerformancescore070[dist];
		}
		if(angleforpi==0&&angle2forpi==80)
		{
		result = charPerformancescore080[dist];
		}
		if(angleforpi==0&&angle2forpi==90)
		{
		result = charPerformancescore090[dist];
		}
		if(angleforpi==10&&angle2forpi==0)
		{
		result = charPerformancescore100[dist];
		}
		if(angleforpi==10&&angle2forpi==10)
		{
		result = charPerformancescore1010[dist];
		}
		if(angleforpi==10&&angle2forpi==20)
		{
		result = charPerformancescore1020[dist];
		}
		if(angleforpi==10&&angle2forpi==30)
		{
		result = charPerformancescore1030[dist];
		}
		if(angleforpi==10&&angle2forpi==40)
		{
		result = charPerformancescore1040[dist];
		}
		if(angleforpi==10&&angle2forpi==50)
		{
		result = charPerformancescore1050[dist];
		}
		if(angleforpi==10&&angle2forpi==60)
		{
		result = charPerformancescore1060[dist];
		}
		if(angleforpi==10&&angle2forpi==70)
		{
		result = charPerformancescore1070[dist];
		}
		if(angleforpi==10&&angle2forpi==80)
		{
		result = charPerformancescore1080[dist];
		}
		if(angleforpi==10&&angle2forpi==90)
		{
		result = charPerformancescore1090[dist];
		}
		if(angleforpi==20&&angle2forpi==0)
		{
		result = charPerformancescore200[dist];
		}
		if(angleforpi==20&&angle2forpi==10)
		{
		result = charPerformancescore2010[dist];
		}
		if(angleforpi==20&&angle2forpi==20)
		{
		result = charPerformancescore2020[dist];
		}
		if(angleforpi==20&&angle2forpi==30)
		{
		result = charPerformancescore2030[dist];
		}
		if(angleforpi==20&&angle2forpi==40)
		{
		result = charPerformancescore2040[dist];
		}
		if(angleforpi==20&&angle2forpi==50)
		{
		result = charPerformancescore2050[dist];
		}
		if(angleforpi==20&&angle2forpi==60)
		{
		result = charPerformancescore2060[dist];
		}
		if(angleforpi==20&&angle2forpi==70)
		{
		result = charPerformancescore2070[dist];
		}
		if(angleforpi==20&&angle2forpi==80)
		{
		result = charPerformancescore2080[dist];
		}
		if(angleforpi==20&&angle2forpi==90)
		{
		result = charPerformancescore2090[dist];
		}
		if(angleforpi==30&&angle2forpi==0)
		{
		result = charPerformancescore300[dist];
		}
		if(angleforpi==30&&angle2forpi==10)
		{
		result = charPerformancescore3010[dist];
		}
		if(angleforpi==30&&angle2forpi==20)
		{
		result = charPerformancescore3020[dist];
		}
		if(angleforpi==30&&angle2forpi==30)
		{
		result = charPerformancescore3030[dist];
		}
		if(angleforpi==30&&angle2forpi==40)
		{
		result = charPerformancescore3040[dist];
		}
		if(angleforpi==30&&angle2forpi==50)
		{
		result = charPerformancescore3050[dist];
		}
		if(angleforpi==30&&angle2forpi==60)
		{
		result = charPerformancescore3060[dist];
		}
		if(angleforpi==30&&angle2forpi==70)
		{
		result = charPerformancescore3070[dist];
		}
		if(angleforpi==30&&angle2forpi==80)
		{
		result = charPerformancescore3080[dist];
		}
		if(angleforpi==30&&angle2forpi==90)
		{
		result = charPerformancescore3090[dist];
		}
		if(angleforpi==40&&angle2forpi==0)
		{
		result = charPerformancescore400[dist];
		}
		if(angleforpi==40&&angle2forpi==10)
		{
		result = charPerformancescore4010[dist];
		}
		if(angleforpi==40&&angle2forpi==20)
		{
		result = charPerformancescore4020[dist];
		}
		if(angleforpi==40&&angle2forpi==30)
		{
		result = charPerformancescore4030[dist];
		}
		if(angleforpi==40&&angle2forpi==40)
		{
		result = charPerformancescore4040[dist];
		}
		if(angleforpi==40&&angle2forpi==50)
		{
		result = charPerformancescore4050[dist];
		}
		if(angleforpi==40&&angle2forpi==60)
		{
		result = charPerformancescore4060[dist];
		}
		if(angleforpi==40&&angle2forpi==70)
		{
		result = charPerformancescore4070[dist];
		}
		if(angleforpi==40&&angle2forpi==80)
		{
		result = charPerformancescore4080[dist];
		}
		if(angleforpi==40&&angle2forpi==90)
		{
		result = charPerformancescore4090[dist];
		}
		if(angleforpi==50&&angle2forpi==0)
		{
		result = charPerformancescore500[dist];
		}
		if(angleforpi==50&&angle2forpi==10)
		{
		result = charPerformancescore5010[dist];
		}
		if(angleforpi==50&&angle2forpi==20)
		{
		result = charPerformancescore5020[dist];
		}
		if(angleforpi==50&&angle2forpi==30)
		{
		result = charPerformancescore5030[dist];
		}
		if(angleforpi==50&&angle2forpi==40)
		{
		result = charPerformancescore5040[dist];
		}
		if(angleforpi==50&&angle2forpi==50)
		{
		result = charPerformancescore5050[dist];
		}
		if(angleforpi==50&&angle2forpi==60)
		{
		result = charPerformancescore5060[dist];
		}
		if(angleforpi==50&&angle2forpi==70)
		{
		result = charPerformancescore5070[dist];
		}
		if(angleforpi==50&&angle2forpi==80)
		{
		result = charPerformancescore5080[dist];
		}
		if(angleforpi==50&&angle2forpi==90)
		{
		result = charPerformancescore5090[dist];
		}
		if(angleforpi==60&&angle2forpi==0)
		{
		result = charPerformancescore600[dist];
		}
		if(angleforpi==60&&angle2forpi==10)
		{
		result = charPerformancescore6010[dist];
		}
		if(angleforpi==60&&angle2forpi==20)
		{
		result = charPerformancescore6020[dist];
		}
		if(angleforpi==60&&angle2forpi==30)
		{
		result = charPerformancescore6030[dist];
		}
		if(angleforpi==60&&angle2forpi==40)
		{
		result = charPerformancescore6040[dist];
		}
		if(angleforpi==60&&angle2forpi==50)
		{
		result = charPerformancescore6050[dist];
		}
		if(angleforpi==60&&angle2forpi==60)
		{
		result = charPerformancescore6060[dist];
		}
		if(angleforpi==60&&angle2forpi==70)
		{
		result = charPerformancescore6070[dist];
		}
		if(angleforpi==60&&angle2forpi==80)
		{
		result = charPerformancescore6080[dist];
		}
		if(angleforpi==60&&angle2forpi==90)
		{
		result = charPerformancescore6090[dist];
		}
		if(angleforpi==70&&angle2forpi==0)
		{
		result = charPerformancescore700[dist];
		}
		if(angleforpi==70&&angle2forpi==10)
		{
		result = charPerformancescore7010[dist];
		}
		if(angleforpi==70&&angle2forpi==20)
		{
		result = charPerformancescore7020[dist];
		}
		if(angleforpi==70&&angle2forpi==30)
		{
		result = charPerformancescore7030[dist];
		}
		if(angleforpi==70&&angle2forpi==40)
		{
		result = charPerformancescore7040[dist];
		}
		if(angleforpi==70&&angle2forpi==50)
		{
		result = charPerformancescore7050[dist];
		}
		if(angleforpi==70&&angle2forpi==60)
		{
		result = charPerformancescore7060[dist];
		}
		if(angleforpi==70&&angle2forpi==70)
		{
		result = charPerformancescore7070[dist];
		}
		if(angleforpi==70&&angle2forpi==80)
		{
		result = charPerformancescore7080[dist];
		}
		if(angleforpi==70&&angle2forpi==90)
		{
		result = charPerformancescore7090[dist];
		}
		if(angleforpi==80&&angle2forpi==0)
		{
		result = charPerformancescore800[dist];
		}
		if(angleforpi==80&&angle2forpi==10)
		{
		result = charPerformancescore8010[dist];
		}
		if(angleforpi==80&&angle2forpi==20)
		{
		result = charPerformancescore8020[dist];
		}
		if(angleforpi==80&&angle2forpi==30)
		{
		result = charPerformancescore8030[dist];
		}
		if(angleforpi==80&&angle2forpi==40)
		{
		result = charPerformancescore8040[dist];
		}
		if(angleforpi==80&&angle2forpi==50)
		{
		result = charPerformancescore8050[dist];
		}
		if(angleforpi==80&&angle2forpi==60)
		{
		result = charPerformancescore8060[dist];
		}
		if(angleforpi==80&&angle2forpi==70)
		{
		result = charPerformancescore8070[dist];
		}
		if(angleforpi==80&&angle2forpi==80)
		{
		result = charPerformancescore8080[dist];
		}
		if(angleforpi==80&&angle2forpi==90)
		{
		result = charPerformancescore8090[dist];
		}
		if(angleforpi==90&&angle2forpi==0)
		{
		result = charPerformancescore900[dist];
		}
		if(angleforpi==90&&angle2forpi==10)
		{
		result = charPerformancescore9010[dist];
		}
		if(angleforpi==90&&angle2forpi==20)
		{
		result = charPerformancescore9020[dist];
		}
		if(angleforpi==90&&angle2forpi==30)
		{
		result = charPerformancescore9030[dist];
		}
		if(angleforpi==90&&angle2forpi==40)
		{
		result = charPerformancescore9040[dist];
		}
		if(angleforpi==90&&angle2forpi==50)
		{
		result = charPerformancescore9050[dist];
		}
		if(angleforpi==90&&angle2forpi==60)
		{
		result = charPerformancescore9060[dist];
		}
		if(angleforpi==90&&angle2forpi==70)
		{
		result = charPerformancescore9070[dist];
		}
		if(angleforpi==90&&angle2forpi==80)
		{
		result = charPerformancescore9080[dist];
		}
		if(angleforpi==90&&angle2forpi==90)
		{
		result = charPerformancescore9090[dist];
		}
		if(angleforpi==100&&angle2forpi==0)
		{
		result = charPerformancescore1000[dist];
		}
		if(angleforpi==100&&angle2forpi==10)
		{
		result = charPerformancescore10010[dist];
		}
		if(angleforpi==100&&angle2forpi==20)
		{
		result = charPerformancescore10020[dist];
		}
		if(angleforpi==100&&angle2forpi==30)
		{
		result = charPerformancescore10030[dist];
		}
		if(angleforpi==100&&angle2forpi==40)
		{
		result = charPerformancescore10040[dist];
		}
		if(angleforpi==100&&angle2forpi==50)
		{
		result = charPerformancescore10050[dist];
		}
		if(angleforpi==100&&angle2forpi==60)
		{
		result = charPerformancescore10060[dist];
		}
		if(angleforpi==100&&angle2forpi==70)
		{
		result = charPerformancescore10070[dist];
		}
		if(angleforpi==100&&angle2forpi==80)
		{
		result = charPerformancescore10080[dist];
		}
		if(angleforpi==100&&angle2forpi==90)
		{
		result = charPerformancescore10090[dist];
		}
		if(angleforpi==110&&angle2forpi==0)
		{
		result = charPerformancescore1100[dist];
		}
		if(angleforpi==110&&angle2forpi==10)
		{
		result = charPerformancescore11010[dist];
		}
		if(angleforpi==110&&angle2forpi==20)
		{
		result = charPerformancescore11020[dist];
		}
		if(angleforpi==110&&angle2forpi==30)
		{
		result = charPerformancescore11030[dist];
		}
		if(angleforpi==110&&angle2forpi==40)
		{
		result = charPerformancescore11040[dist];
		}
		if(angleforpi==110&&angle2forpi==50)
		{
		result = charPerformancescore11050[dist];
		}
		if(angleforpi==110&&angle2forpi==60)
		{
		result = charPerformancescore11060[dist];
		}
		if(angleforpi==110&&angle2forpi==70)
		{
		result = charPerformancescore11070[dist];
		}
		if(angleforpi==110&&angle2forpi==80)
		{
		result = charPerformancescore11080[dist];
		}
		if(angleforpi==110&&angle2forpi==90)
		{
		result = charPerformancescore11090[dist];
		}
		if(angleforpi==120&&angle2forpi==0)
		{
		result = charPerformancescore1200[dist];
		}
		if(angleforpi==120&&angle2forpi==10)
		{
		result = charPerformancescore12010[dist];
		}
		if(angleforpi==120&&angle2forpi==20)
		{
		result = charPerformancescore12020[dist];
		}
		if(angleforpi==120&&angle2forpi==30)
		{
		result = charPerformancescore12030[dist];
		}
		if(angleforpi==120&&angle2forpi==40)
		{
		result = charPerformancescore12040[dist];
		}
		if(angleforpi==120&&angle2forpi==50)
		{
		result = charPerformancescore12050[dist];
		}
		if(angleforpi==120&&angle2forpi==60)
		{
		result = charPerformancescore12060[dist];
		}
		if(angleforpi==120&&angle2forpi==70)
		{
		result = charPerformancescore12070[dist];
		}
		if(angleforpi==120&&angle2forpi==80)
		{
		result = charPerformancescore12080[dist];
		}
		if(angleforpi==120&&angle2forpi==90)
		{
		result = charPerformancescore12090[dist];
		}
		if(angleforpi==130&&angle2forpi==0)
		{
		result = charPerformancescore1300[dist];
		}
		if(angleforpi==130&&angle2forpi==10)
		{
		result = charPerformancescore13010[dist];
		}
		if(angleforpi==130&&angle2forpi==20)
		{
		result = charPerformancescore13020[dist];
		}
		if(angleforpi==130&&angle2forpi==30)
		{
		result = charPerformancescore13030[dist];
		}
		if(angleforpi==130&&angle2forpi==40)
		{
		result = charPerformancescore13040[dist];
		}
		if(angleforpi==130&&angle2forpi==50)
		{
		result = charPerformancescore13050[dist];
		}
		if(angleforpi==130&&angle2forpi==60)
		{
		result = charPerformancescore13060[dist];
		}
		if(angleforpi==130&&angle2forpi==70)
		{
		result = charPerformancescore13070[dist];
		}
		if(angleforpi==130&&angle2forpi==80)
		{
		result = charPerformancescore13080[dist];
		}
		if(angleforpi==130&&angle2forpi==90)
		{
		result = charPerformancescore13090[dist];
		}
		if(angleforpi==140&&angle2forpi==0)
		{
		result = charPerformancescore1400[dist];
		}
		if(angleforpi==140&&angle2forpi==10)
		{
		result = charPerformancescore14010[dist];
		}
		if(angleforpi==140&&angle2forpi==20)
		{
		result = charPerformancescore14020[dist];
		}
		if(angleforpi==140&&angle2forpi==30)
		{
		result = charPerformancescore14030[dist];
		}
		if(angleforpi==140&&angle2forpi==40)
		{
		result = charPerformancescore14040[dist];
		}
		if(angleforpi==140&&angle2forpi==50)
		{
		result = charPerformancescore14050[dist];
		}
		if(angleforpi==140&&angle2forpi==60)
		{
		result = charPerformancescore14060[dist];
		}
		if(angleforpi==140&&angle2forpi==70)
		{
		result = charPerformancescore14070[dist];
		}
		if(angleforpi==140&&angle2forpi==80)
		{
		result = charPerformancescore14080[dist];
		}
		if(angleforpi==140&&angle2forpi==90)
		{
		result = charPerformancescore14090[dist];
		}
		if(angleforpi==150&&angle2forpi==0)
		{
		result = charPerformancescore1500[dist];
		}
		if(angleforpi==150&&angle2forpi==10)
		{
		result = charPerformancescore15010[dist];
		}
		if(angleforpi==150&&angle2forpi==20)
		{
		result = charPerformancescore15020[dist];
		}
		if(angleforpi==150&&angle2forpi==30)
		{
		result = charPerformancescore15030[dist];
		}
		if(angleforpi==150&&angle2forpi==40)
		{
		result = charPerformancescore15040[dist];
		}
		if(angleforpi==150&&angle2forpi==50)
		{
		result = charPerformancescore15050[dist];
		}
		if(angleforpi==150&&angle2forpi==60)
		{
		result = charPerformancescore15060[dist];
		}
		if(angleforpi==150&&angle2forpi==70)
		{
		result = charPerformancescore15070[dist];
		}
		if(angleforpi==150&&angle2forpi==80)
		{
		result = charPerformancescore15080[dist];
		}
		if(angleforpi==150&&angle2forpi==90)
		{
		result = charPerformancescore15090[dist];
		}
		if(angleforpi==160&&angle2forpi==0)
		{
		result = charPerformancescore1600[dist];
		}
		if(angleforpi==160&&angle2forpi==10)
		{
		result = charPerformancescore16010[dist];
		}
		if(angleforpi==160&&angle2forpi==20)
		{
		result = charPerformancescore16020[dist];
		}
		if(angleforpi==160&&angle2forpi==30)
		{
		result = charPerformancescore16030[dist];
		}
		if(angleforpi==160&&angle2forpi==40)
		{
		result = charPerformancescore16040[dist];
		}
		if(angleforpi==160&&angle2forpi==50)
		{
		result = charPerformancescore16050[dist];
		}
		if(angleforpi==160&&angle2forpi==60)
		{
		result = charPerformancescore16060[dist];
		}
		if(angleforpi==160&&angle2forpi==70)
		{
		result = charPerformancescore16070[dist];
		}
		if(angleforpi==160&&angle2forpi==80)
		{
		result = charPerformancescore16080[dist];
		}
		if(angleforpi==160&&angle2forpi==90)
		{
		result = charPerformancescore16090[dist];
		}
		if(angleforpi==170&&angle2forpi==0)
		{
		result = charPerformancescore1700[dist];
		}
		if(angleforpi==170&&angle2forpi==10)
		{
		result = charPerformancescore17010[dist];
		}
		if(angleforpi==170&&angle2forpi==20)
		{
		result = charPerformancescore17020[dist];
		}
		if(angleforpi==170&&angle2forpi==30)
		{
		result = charPerformancescore17030[dist];
		}
		if(angleforpi==170&&angle2forpi==40)
		{
		result = charPerformancescore17040[dist];
		}
		if(angleforpi==170&&angle2forpi==50)
		{
		result = charPerformancescore17050[dist];
		}
		if(angleforpi==170&&angle2forpi==60)
		{
		result = charPerformancescore17060[dist];
		}
		if(angleforpi==170&&angle2forpi==70)
		{
		result = charPerformancescore17070[dist];
		}
		if(angleforpi==170&&angle2forpi==80)
		{
		result = charPerformancescore17080[dist];
		}
		if(angleforpi==170&&angle2forpi==90)
		{
		result = charPerformancescore17090[dist];
		}
		return result;
	}
	double GetCharPerformance(int no, RobotPose myRobot, BallPoint ball_point, Point dpt)
	{
		double	k,angle1,angle,angle2,result,k1,ddist;
		Point rpt;
		int dist;
		int angleforpi,angle2forpi;

		angle2 = cn_AngleTrim2PI(myRobot.theta);
		rpt.x = myRobot.x;
		rpt.y = myRobot.y;


		angle = Getpt2ptAngle(ball_point,dpt);
		angle1 = Getpt2ptAngle(rpt,ball_point);
		angle = angle - angle1;
		angle2 = angle1 - angle2;
		angle2 = cal_AngleTrim2PI(angle2);//trim theta to between 0 and 2pi

		if(angle2>Pi)//(0~Pi)
		angle2 = 2*Pi  -  angle2;
		if(angle2>Pi/2)//(0~Pi/2)
		angle2 = Pi - angle2;

		angle = cal_AngleTrim2PI(angle);

		if(angle>Pi)//(0~Pi)
		angle = 2*Pi - angle;

		ddist = distRobot2Pt(myRobot,ball_point);
		dist = ddist;
		if(angle<(Pi/18))//10
		{
		angleforpi = 0;
		}
		else if(angle<(Pi/9))//20
		{
		angleforpi = 10;
		}
		else if(angle<(Pi/6))//30
		{
		angleforpi = 20;
		}
		else if(angle<(2*Pi/9))//40
		{
		angleforpi = 30;
		}
		else if(angle<(5*Pi/18))//50
		{
		angleforpi = 40;
		}
		else if(angle<(6*Pi/18))//60
		{
		angleforpi = 50;
		}
		else if(angle<(7*Pi/18))//70
		{
		angleforpi = 60;
		}
		else if(angle<(8*Pi/18))//80
		{
		angleforpi = 70;
		}
		else if(angle<(9*Pi/18))//90
		{
		angleforpi = 80;
		}
		else if(angle<(10*Pi/18))//100
		{
		angleforpi = 90;
		}
		else if(angle<(11*Pi/18))//110
		{
		angleforpi = 100;
		}
		else if(angle<(12*Pi/18))//120
		{
		angleforpi = 110;
		}
		else if(angle<(13*Pi/18))//130
		{
		angleforpi = 120;
		}
		else if(angle<(14*Pi/18))//140
		{
		angleforpi = 130;
		}
		else if(angle<(15*Pi/18))//150
		{
		angleforpi = 140;
		}
		else if(angle<(16*Pi/18))//160
		{
		angleforpi = 150;
		}
		else if(angle<(17*Pi/18))//170
		{
		angleforpi = 160;
		}
		else
		{
		angleforpi = 170;
		}



		if(angle2<(Pi/18))//10
		{
		angle2forpi = 0;
		}
		else if(angle2<(Pi/9))//20
		{
		angle2forpi = 10;
		}
		else if(angle2<(Pi/6))//30
		{
		angle2forpi = 20;
		}
		else if(angle2<(2*Pi/9))//40
		{
		angle2forpi = 30;
		}
		else if(angle2<(5*Pi/18))//50
		{
		angle2forpi = 40;
		}
		else if(angle2<(6*Pi/18))//60
		{
		angle2forpi = 50;
		}
		else if(angle2<(7*Pi/18))//70
		{
		angle2forpi = 60;
		}
		else if(angle2<(8*Pi/18))//80
		{
		angle2forpi = 70;
		}
		else if(angle2<(9*Pi/18))//90
		{
		angle2forpi = 80;
		}
		else
		{
		angle2forpi = 90;
		}


		if(angleforpi==0&&angle2forpi==0)
		{
		result = charPerformancescore00[dist];
		}
		if(angleforpi==0&&angle2forpi==10)
		{
		result = charPerformancescore010[dist];
		}
		if(angleforpi==0&&angle2forpi==20)
		{
		result = charPerformancescore020[dist];
		}
		if(angleforpi==0&&angle2forpi==30)
		{
		result = charPerformancescore030[dist];
		}
		if(angleforpi==0&&angle2forpi==40)
		{
		result = charPerformancescore040[dist];
		}
		if(angleforpi==0&&angle2forpi==50)
		{
		result = charPerformancescore050[dist];
		}
		if(angleforpi==0&&angle2forpi==60)
		{
		result = charPerformancescore060[dist];
		}
		if(angleforpi==0&&angle2forpi==70)
		{
		result = charPerformancescore070[dist];
		}
		if(angleforpi==0&&angle2forpi==80)
		{
		result = charPerformancescore080[dist];
		}
		if(angleforpi==0&&angle2forpi==90)
		{
		result = charPerformancescore090[dist];
		}
		if(angleforpi==10&&angle2forpi==0)
		{
		result = charPerformancescore100[dist];
		}
		if(angleforpi==10&&angle2forpi==10)
		{
		result = charPerformancescore1010[dist];
		}
		if(angleforpi==10&&angle2forpi==20)
		{
		result = charPerformancescore1020[dist];
		}
		if(angleforpi==10&&angle2forpi==30)
		{
		result = charPerformancescore1030[dist];
		}
		if(angleforpi==10&&angle2forpi==40)
		{
		result = charPerformancescore1040[dist];
		}
		if(angleforpi==10&&angle2forpi==50)
		{
		result = charPerformancescore1050[dist];
		}
		if(angleforpi==10&&angle2forpi==60)
		{
		result = charPerformancescore1060[dist];
		}
		if(angleforpi==10&&angle2forpi==70)
		{
		result = charPerformancescore1070[dist];
		}
		if(angleforpi==10&&angle2forpi==80)
		{
		result = charPerformancescore1080[dist];
		}
		if(angleforpi==10&&angle2forpi==90)
		{
		result = charPerformancescore1090[dist];
		}
		if(angleforpi==20&&angle2forpi==0)
		{
		result = charPerformancescore200[dist];
		}
		if(angleforpi==20&&angle2forpi==10)
		{
		result = charPerformancescore2010[dist];
		}
		if(angleforpi==20&&angle2forpi==20)
		{
		result = charPerformancescore2020[dist];
		}
		if(angleforpi==20&&angle2forpi==30)
		{
		result = charPerformancescore2030[dist];
		}
		if(angleforpi==20&&angle2forpi==40)
		{
		result = charPerformancescore2040[dist];
		}
		if(angleforpi==20&&angle2forpi==50)
		{
		result = charPerformancescore2050[dist];
		}
		if(angleforpi==20&&angle2forpi==60)
		{
		result = charPerformancescore2060[dist];
		}
		if(angleforpi==20&&angle2forpi==70)
		{
		result = charPerformancescore2070[dist];
		}
		if(angleforpi==20&&angle2forpi==80)
		{
		result = charPerformancescore2080[dist];
		}
		if(angleforpi==20&&angle2forpi==90)
		{
		result = charPerformancescore2090[dist];
		}
		if(angleforpi==30&&angle2forpi==0)
		{
		result = charPerformancescore300[dist];
		}
		if(angleforpi==30&&angle2forpi==10)
		{
		result = charPerformancescore3010[dist];
		}
		if(angleforpi==30&&angle2forpi==20)
		{
		result = charPerformancescore3020[dist];
		}
		if(angleforpi==30&&angle2forpi==30)
		{
		result = charPerformancescore3030[dist];
		}
		if(angleforpi==30&&angle2forpi==40)
		{
		result = charPerformancescore3040[dist];
		}
		if(angleforpi==30&&angle2forpi==50)
		{
		result = charPerformancescore3050[dist];
		}
		if(angleforpi==30&&angle2forpi==60)
		{
		result = charPerformancescore3060[dist];
		}
		if(angleforpi==30&&angle2forpi==70)
		{
		result = charPerformancescore3070[dist];
		}
		if(angleforpi==30&&angle2forpi==80)
		{
		result = charPerformancescore3080[dist];
		}
		if(angleforpi==30&&angle2forpi==90)
		{
		result = charPerformancescore3090[dist];
		}
		if(angleforpi==40&&angle2forpi==0)
		{
		result = charPerformancescore400[dist];
		}
		if(angleforpi==40&&angle2forpi==10)
		{
		result = charPerformancescore4010[dist];
		}
		if(angleforpi==40&&angle2forpi==20)
		{
		result = charPerformancescore4020[dist];
		}
		if(angleforpi==40&&angle2forpi==30)
		{
		result = charPerformancescore4030[dist];
		}
		if(angleforpi==40&&angle2forpi==40)
		{
		result = charPerformancescore4040[dist];
		}
		if(angleforpi==40&&angle2forpi==50)
		{
		result = charPerformancescore4050[dist];
		}
		if(angleforpi==40&&angle2forpi==60)
		{
		result = charPerformancescore4060[dist];
		}
		if(angleforpi==40&&angle2forpi==70)
		{
		result = charPerformancescore4070[dist];
		}
		if(angleforpi==40&&angle2forpi==80)
		{
		result = charPerformancescore4080[dist];
		}
		if(angleforpi==40&&angle2forpi==90)
		{
		result = charPerformancescore4090[dist];
		}
		if(angleforpi==50&&angle2forpi==0)
		{
		result = charPerformancescore500[dist];
		}
		if(angleforpi==50&&angle2forpi==10)
		{
		result = charPerformancescore5010[dist];
		}
		if(angleforpi==50&&angle2forpi==20)
		{
		result = charPerformancescore5020[dist];
		}
		if(angleforpi==50&&angle2forpi==30)
		{
		result = charPerformancescore5030[dist];
		}
		if(angleforpi==50&&angle2forpi==40)
		{
		result = charPerformancescore5040[dist];
		}
		if(angleforpi==50&&angle2forpi==50)
		{
		result = charPerformancescore5050[dist];
		}
		if(angleforpi==50&&angle2forpi==60)
		{
		result = charPerformancescore5060[dist];
		}
		if(angleforpi==50&&angle2forpi==70)
		{
		result = charPerformancescore5070[dist];
		}
		if(angleforpi==50&&angle2forpi==80)
		{
		result = charPerformancescore5080[dist];
		}
		if(angleforpi==50&&angle2forpi==90)
		{
		result = charPerformancescore5090[dist];
		}
		if(angleforpi==60&&angle2forpi==0)
		{
		result = charPerformancescore600[dist];
		}
		if(angleforpi==60&&angle2forpi==10)
		{
		result = charPerformancescore6010[dist];
		}
		if(angleforpi==60&&angle2forpi==20)
		{
		result = charPerformancescore6020[dist];
		}
		if(angleforpi==60&&angle2forpi==30)
		{
		result = charPerformancescore6030[dist];
		}
		if(angleforpi==60&&angle2forpi==40)
		{
		result = charPerformancescore6040[dist];
		}
		if(angleforpi==60&&angle2forpi==50)
		{
		result = charPerformancescore6050[dist];
		}
		if(angleforpi==60&&angle2forpi==60)
		{
		result = charPerformancescore6060[dist];
		}
		if(angleforpi==60&&angle2forpi==70)
		{
		result = charPerformancescore6070[dist];
		}
		if(angleforpi==60&&angle2forpi==80)
		{
		result = charPerformancescore6080[dist];
		}
		if(angleforpi==60&&angle2forpi==90)
		{
		result = charPerformancescore6090[dist];
		}
		if(angleforpi==70&&angle2forpi==0)
		{
		result = charPerformancescore700[dist];
		}
		if(angleforpi==70&&angle2forpi==10)
		{
		result = charPerformancescore7010[dist];
		}
		if(angleforpi==70&&angle2forpi==20)
		{
		result = charPerformancescore7020[dist];
		}
		if(angleforpi==70&&angle2forpi==30)
		{
		result = charPerformancescore7030[dist];
		}
		if(angleforpi==70&&angle2forpi==40)
		{
		result = charPerformancescore7040[dist];
		}
		if(angleforpi==70&&angle2forpi==50)
		{
		result = charPerformancescore7050[dist];
		}
		if(angleforpi==70&&angle2forpi==60)
		{
		result = charPerformancescore7060[dist];
		}
		if(angleforpi==70&&angle2forpi==70)
		{
		result = charPerformancescore7070[dist];
		}
		if(angleforpi==70&&angle2forpi==80)
		{
		result = charPerformancescore7080[dist];
		}
		if(angleforpi==70&&angle2forpi==90)
		{
		result = charPerformancescore7090[dist];
		}
		if(angleforpi==80&&angle2forpi==0)
		{
		result = charPerformancescore800[dist];
		}
		if(angleforpi==80&&angle2forpi==10)
		{
		result = charPerformancescore8010[dist];
		}
		if(angleforpi==80&&angle2forpi==20)
		{
		result = charPerformancescore8020[dist];
		}
		if(angleforpi==80&&angle2forpi==30)
		{
		result = charPerformancescore8030[dist];
		}
		if(angleforpi==80&&angle2forpi==40)
		{
		result = charPerformancescore8040[dist];
		}
		if(angleforpi==80&&angle2forpi==50)
		{
		result = charPerformancescore8050[dist];
		}
		if(angleforpi==80&&angle2forpi==60)
		{
		result = charPerformancescore8060[dist];
		}
		if(angleforpi==80&&angle2forpi==70)
		{
		result = charPerformancescore8070[dist];
		}
		if(angleforpi==80&&angle2forpi==80)
		{
		result = charPerformancescore8080[dist];
		}
		if(angleforpi==80&&angle2forpi==90)
		{
		result = charPerformancescore8090[dist];
		}
		if(angleforpi==90&&angle2forpi==0)
		{
		result = charPerformancescore900[dist];
		}
		if(angleforpi==90&&angle2forpi==10)
		{
		result = charPerformancescore9010[dist];
		}
		if(angleforpi==90&&angle2forpi==20)
		{
		result = charPerformancescore9020[dist];
		}
		if(angleforpi==90&&angle2forpi==30)
		{
		result = charPerformancescore9030[dist];
		}
		if(angleforpi==90&&angle2forpi==40)
		{
		result = charPerformancescore9040[dist];
		}
		if(angleforpi==90&&angle2forpi==50)
		{
		result = charPerformancescore9050[dist];
		}
		if(angleforpi==90&&angle2forpi==60)
		{
		result = charPerformancescore9060[dist];
		}
		if(angleforpi==90&&angle2forpi==70)
		{
		result = charPerformancescore9070[dist];
		}
		if(angleforpi==90&&angle2forpi==80)
		{
		result = charPerformancescore9080[dist];
		}
		if(angleforpi==90&&angle2forpi==90)
		{
		result = charPerformancescore9090[dist];
		}
		if(angleforpi==100&&angle2forpi==0)
		{
		result = charPerformancescore1000[dist];
		}
		if(angleforpi==100&&angle2forpi==10)
		{
		result = charPerformancescore10010[dist];
		}
		if(angleforpi==100&&angle2forpi==20)
		{
		result = charPerformancescore10020[dist];
		}
		if(angleforpi==100&&angle2forpi==30)
		{
		result = charPerformancescore10030[dist];
		}
		if(angleforpi==100&&angle2forpi==40)
		{
		result = charPerformancescore10040[dist];
		}
		if(angleforpi==100&&angle2forpi==50)
		{
		result = charPerformancescore10050[dist];
		}
		if(angleforpi==100&&angle2forpi==60)
		{
		result = charPerformancescore10060[dist];
		}
		if(angleforpi==100&&angle2forpi==70)
		{
		result = charPerformancescore10070[dist];
		}
		if(angleforpi==100&&angle2forpi==80)
		{
		result = charPerformancescore10080[dist];
		}
		if(angleforpi==100&&angle2forpi==90)
		{
		result = charPerformancescore10090[dist];
		}
		if(angleforpi==110&&angle2forpi==0)
		{
		result = charPerformancescore1100[dist];
		}
		if(angleforpi==110&&angle2forpi==10)
		{
		result = charPerformancescore11010[dist];
		}
		if(angleforpi==110&&angle2forpi==20)
		{
		result = charPerformancescore11020[dist];
		}
		if(angleforpi==110&&angle2forpi==30)
		{
		result = charPerformancescore11030[dist];
		}
		if(angleforpi==110&&angle2forpi==40)
		{
		result = charPerformancescore11040[dist];
		}
		if(angleforpi==110&&angle2forpi==50)
		{
		result = charPerformancescore11050[dist];
		}
		if(angleforpi==110&&angle2forpi==60)
		{
		result = charPerformancescore11060[dist];
		}
		if(angleforpi==110&&angle2forpi==70)
		{
		result = charPerformancescore11070[dist];
		}
		if(angleforpi==110&&angle2forpi==80)
		{
		result = charPerformancescore11080[dist];
		}
		if(angleforpi==110&&angle2forpi==90)
		{
		result = charPerformancescore11090[dist];
		}
		if(angleforpi==120&&angle2forpi==0)
		{
		result = charPerformancescore1200[dist];
		}
		if(angleforpi==120&&angle2forpi==10)
		{
		result = charPerformancescore12010[dist];
		}
		if(angleforpi==120&&angle2forpi==20)
		{
		result = charPerformancescore12020[dist];
		}
		if(angleforpi==120&&angle2forpi==30)
		{
		result = charPerformancescore12030[dist];
		}
		if(angleforpi==120&&angle2forpi==40)
		{
		result = charPerformancescore12040[dist];
		}
		if(angleforpi==120&&angle2forpi==50)
		{
		result = charPerformancescore12050[dist];
		}
		if(angleforpi==120&&angle2forpi==60)
		{
		result = charPerformancescore12060[dist];
		}
		if(angleforpi==120&&angle2forpi==70)
		{
		result = charPerformancescore12070[dist];
		}
		if(angleforpi==120&&angle2forpi==80)
		{
		result = charPerformancescore12080[dist];
		}
		if(angleforpi==120&&angle2forpi==90)
		{
		result = charPerformancescore12090[dist];
		}
		if(angleforpi==130&&angle2forpi==0)
		{
		result = charPerformancescore1300[dist];
		}
		if(angleforpi==130&&angle2forpi==10)
		{
		result = charPerformancescore13010[dist];
		}
		if(angleforpi==130&&angle2forpi==20)
		{
		result = charPerformancescore13020[dist];
		}
		if(angleforpi==130&&angle2forpi==30)
		{
		result = charPerformancescore13030[dist];
		}
		if(angleforpi==130&&angle2forpi==40)
		{
		result = charPerformancescore13040[dist];
		}
		if(angleforpi==130&&angle2forpi==50)
		{
		result = charPerformancescore13050[dist];
		}
		if(angleforpi==130&&angle2forpi==60)
		{
		result = charPerformancescore13060[dist];
		}
		if(angleforpi==130&&angle2forpi==70)
		{
		result = charPerformancescore13070[dist];
		}
		if(angleforpi==130&&angle2forpi==80)
		{
		result = charPerformancescore13080[dist];
		}
		if(angleforpi==130&&angle2forpi==90)
		{
		result = charPerformancescore13090[dist];
		}
		if(angleforpi==140&&angle2forpi==0)
		{
		result = charPerformancescore1400[dist];
		}
		if(angleforpi==140&&angle2forpi==10)
		{
		result = charPerformancescore14010[dist];
		}
		if(angleforpi==140&&angle2forpi==20)
		{
		result = charPerformancescore14020[dist];
		}
		if(angleforpi==140&&angle2forpi==30)
		{
		result = charPerformancescore14030[dist];
		}
		if(angleforpi==140&&angle2forpi==40)
		{
		result = charPerformancescore14040[dist];
		}
		if(angleforpi==140&&angle2forpi==50)
		{
		result = charPerformancescore14050[dist];
		}
		if(angleforpi==140&&angle2forpi==60)
		{
		result = charPerformancescore14060[dist];
		}
		if(angleforpi==140&&angle2forpi==70)
		{
		result = charPerformancescore14070[dist];
		}
		if(angleforpi==140&&angle2forpi==80)
		{
		result = charPerformancescore14080[dist];
		}
		if(angleforpi==140&&angle2forpi==90)
		{
		result = charPerformancescore14090[dist];
		}
		if(angleforpi==150&&angle2forpi==0)
		{
		result = charPerformancescore1500[dist];
		}
		if(angleforpi==150&&angle2forpi==10)
		{
		result = charPerformancescore15010[dist];
		}
		if(angleforpi==150&&angle2forpi==20)
		{
		result = charPerformancescore15020[dist];
		}
		if(angleforpi==150&&angle2forpi==30)
		{
		result = charPerformancescore15030[dist];
		}
		if(angleforpi==150&&angle2forpi==40)
		{
		result = charPerformancescore15040[dist];
		}
		if(angleforpi==150&&angle2forpi==50)
		{
		result = charPerformancescore15050[dist];
		}
		if(angleforpi==150&&angle2forpi==60)
		{
		result = charPerformancescore15060[dist];
		}
		if(angleforpi==150&&angle2forpi==70)
		{
		result = charPerformancescore15070[dist];
		}
		if(angleforpi==150&&angle2forpi==80)
		{
		result = charPerformancescore15080[dist];
		}
		if(angleforpi==150&&angle2forpi==90)
		{
		result = charPerformancescore15090[dist];
		}
		if(angleforpi==160&&angle2forpi==0)
		{
		result = charPerformancescore1600[dist];
		}
		if(angleforpi==160&&angle2forpi==10)
		{
		result = charPerformancescore16010[dist];
		}
		if(angleforpi==160&&angle2forpi==20)
		{
		result = charPerformancescore16020[dist];
		}
		if(angleforpi==160&&angle2forpi==30)
		{
		result = charPerformancescore16030[dist];
		}
		if(angleforpi==160&&angle2forpi==40)
		{
		result = charPerformancescore16040[dist];
		}
		if(angleforpi==160&&angle2forpi==50)
		{
		result = charPerformancescore16050[dist];
		}
		if(angleforpi==160&&angle2forpi==60)
		{
		result = charPerformancescore16060[dist];
		}
		if(angleforpi==160&&angle2forpi==70)
		{
		result = charPerformancescore16070[dist];
		}
		if(angleforpi==160&&angle2forpi==80)
		{
		result = charPerformancescore16080[dist];
		}
		if(angleforpi==160&&angle2forpi==90)
		{
		result = charPerformancescore16090[dist];
		}
		if(angleforpi==170&&angle2forpi==0)
		{
		result = charPerformancescore1700[dist];
		}
		if(angleforpi==170&&angle2forpi==10)
		{
		result = charPerformancescore17010[dist];
		}
		if(angleforpi==170&&angle2forpi==20)
		{
		result = charPerformancescore17020[dist];
		}
		if(angleforpi==170&&angle2forpi==30)
		{
		result = charPerformancescore17030[dist];
		}
		if(angleforpi==170&&angle2forpi==40)
		{
		result = charPerformancescore17040[dist];
		}
		if(angleforpi==170&&angle2forpi==50)
		{
		result = charPerformancescore17050[dist];
		}
		if(angleforpi==170&&angle2forpi==60)
		{
		result = charPerformancescore17060[dist];
		}
		if(angleforpi==170&&angle2forpi==70)
		{
		result = charPerformancescore17070[dist];
		}
		if(angleforpi==170&&angle2forpi==80)
		{
		result = charPerformancescore17080[dist];
		}
		if(angleforpi==170&&angle2forpi==90)
		{
		result = charPerformancescore17090[dist];
		}
		return result;
	}

	int GetBestRobot(double Performance[12], int charNo)
	{

		double	temp;
		temp = 100000;
		int BestRobotNo;
		BestRobotNo = 0; 

		for(int tempi=1;tempi<ROBOTNUM;tempi++)
		{
			if(temp>Performance[tempi])
			{
				temp = Performance[tempi];
				BestRobotNo = tempi;
			}
		}
		perfRecord[BestRobotNo] = Performance[BestRobotNo];
		return BestRobotNo;
	}
	
int ToPositionPDlimit(RobotPose* pROBOTPOSTURE,Point Target,double same_speed,
										double end_speed,Velocity* pLRWheelVelocity)
{
    if (same_speed > 120)	//70 
		same_speed = 120;
	
	int clock_sign,move_sign;
	double theta,theta_e1;			//e1Ϊ��ǰ�Ƕ����
	static double theta_e2 = 0;		//e2Ϊ��һ���ڽǶ����
	double dx,dy,dx1,dy1,distance;
	double speed;
	
	//����任����С������Ϊԭ�㣬С������Ϊy��
	dx1=Target.x-pROBOTPOSTURE->x;
	dy1=Target.y-pROBOTPOSTURE->y;
	dx=dx1*cos(pROBOTPOSTURE->theta-Pi/2)+dy1*sin(pROBOTPOSTURE->theta-Pi/2);
	dy=-dx1*sin(pROBOTPOSTURE->theta-Pi/2)+dy1*cos(pROBOTPOSTURE->theta-Pi/2);
	theta=atan2(dy,dx);				//Ŀ���ķ����
	
	/////////�ٶȵ���
	distance = sqrt(dx*dx+dy*dy);
	//Զ�̸���
	//Ϊ��ʹ������ʱ����һ�����ٶ�,���������ķ���
    if(end_speed>same_speed)
		end_speed=same_speed;
	if(distance > m_MoveParameter.max_distance)//75.0*Pi/180.0
		speed = same_speed;
	else //�������Լ���
		speed = distance/m_MoveParameter.max_distance*same_speed;
	
	//���ٲ���
	if(speed < end_speed)
		speed = end_speed;
	
    if(distance>25)
	{
		if(fabs(fabs(theta)-Pi/2)<0.15*Pi)
		{
			theta = cn_AngleTrim2PI(theta);
			if(theta <= Pi/2)//��һ����
			{
				move_sign = 1;
				clock_sign = 1;
				theta_e1 = Pi/2 - theta;
			}
			else if(theta <= Pi)//�ڶ�����
			{
				move_sign = 1;
				clock_sign = -1;
				theta_e1 = theta - Pi/2;
			}
			else if(theta <= 3*Pi/2)//��������
			{
				move_sign = -1;
				clock_sign = 1;
				theta_e1 = 3*Pi/2 - theta;
			}
			else//��������
			{
				move_sign = -1;
				clock_sign = -1;
				theta_e1 = theta - 3*Pi/2;
			}
			
			//pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e2));
			//pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e2));
		
			//��ֹ�򻬣���CS_Curveshootfball��ķ�ֹ������
			if(m_MoveParameter.kp4pospd*theta_e1>vx/speed)
			{
				pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(vx/speed);
				pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(vx/speed);
			}
			else
			{
				pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1);
				pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1);
			}
			//���汾���ڽǶ�����һ������΢����	
			theta_e2=theta_e1;	
		}
		
		else
		{
			double sp=45;
			double angle_e=fabs(fabs(theta)-Pi/2);
			double r=30/angle_e;
			double d=7.5;
			theta = cn_AngleTrim2PI(theta-Pi/2);
			if(theta<Pi/2)
			{
				pLRWheelVelocity->LeftValue = sp*(r-d/2)/r;
				pLRWheelVelocity->RightValue = sp*(r+d/2)/r;
			}
			else if(theta<Pi)
			{
				pLRWheelVelocity->LeftValue = -sp*(r-d/2)/r;
				pLRWheelVelocity->RightValue = -sp*(r+d/2)/r;
			}
			else if(theta<Pi*1.5)
			{
				pLRWheelVelocity->LeftValue = -sp*(r+d/2)/r;
				pLRWheelVelocity->RightValue = -sp*(r-d/2)/r;
			}
			else
			{
				pLRWheelVelocity->LeftValue = sp*(r+d/2)/r;
				pLRWheelVelocity->RightValue = sp*(r-d/2)/r;
			}
			
		}	
	}
	else
	{
		if(fabs(fabs(theta)-Pi/2)>m_AngleParameter.MaxAngle)
		{
			TurnToPointPD(pROBOTPOSTURE,Target,NOCLOCK,pLRWheelVelocity);
			pLRWheelVelocity->LeftValue /= 2.2;		//2
			pLRWheelVelocity->RightValue /= 2.2;
			return 0;
		}
		theta = cn_AngleTrim2PI(theta);
		if(theta <= Pi/2)//��һ����
		{
			move_sign = 1;
			clock_sign = 1;
			theta_e1 = Pi/2 - theta;
		}
		else if(theta <= Pi)//�ڶ�����
		{
			move_sign = 1;
			clock_sign = -1;
			theta_e1 = theta - Pi/2;
		}
		else if(theta <= 3*Pi/2)//��������
		{
			move_sign = -1;
			clock_sign = 1;
			theta_e1 = 3*Pi/2 - theta;
		}
		else//��������
		{
			move_sign = -1;
			clock_sign = -1;
			theta_e1 = theta - 3*Pi/2;
		}
		
		//pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e2));
		//pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1 + m_MoveParameter.kd4pospd*(theta_e1-theta_e2));
		if(m_MoveParameter.kp4pospd*theta_e1>vx/speed)
		{
			pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(vx/speed);
			pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(vx/speed);
		}
		else
		{
			pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1);
			pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1);
		}
		//���汾���ڽǶ�����һ������΢����	
		theta_e2=theta_e1;
		
	}
	return 0;
}





	
	int BoundPushBall(RobotPose charRobot,Point ballPt,Velocity &rbV)
	{
		int		boundAreaNo;
		double	errord,errord1;
		double  dx,dy,dist;
		double  TurnV;
		double  distT,d1,d2;
		
		errord = 10;
		errord1 = 0;
		
		boundAreaNo = GetBoundAreaNo(ballPt);
		charRobot.theta = cal_AngleTrim2PI(charRobot.theta);
		Point tempPt,target;
		if(ballPt.x<errord1)
			ballPt.x = errord1;
		if(ballPt.y<errord1)
			ballPt.y = errord1;
		if(ballPt.x >wallright - errord1)
			ballPt.x = wallright - errord1;
		if(ballPt.y >walltop - errord1)
			ballPt.y = walltop - errord1;
		if(ball_point.x<35)
		{
			TurnV=40;//50
		}
		else
		{
			TurnV = 60;//60;//70
		}
		
		distT = 7;//7;
		d1 = 6;
		d2 = 8;//8;
		
		Point cs_robot,goal;
		cs_robot.x = charRobot.x;
		cs_robot.y = charRobot.y;
		goal.x = 220.0+3.0;
		goal.y = 90;
		
		New_EndProcess(1,&charRobot,goal,ball_point,&rbV);
		
		switch(boundAreaNo)
		{
		case 1:
			{  
				tempPt.x = NUMBER2;//3
				tempPt.y = walltop + NUMBER2;
				
				if(ballPt.y<145&&charRobot.x>ballPt.x&&(ballPt.y-charRobot.y)/(ballPt.x-charRobot.x)>-3/4)
				{
					target.x = ballPt.x + d1;
					target.y = ballPt.y - d2;
					
					dx = charRobot.x - target.x;
					dy = charRobot.y - target.y;
					dist = sqrt(dx*dx + dy*dy);
					if(dist>2)
					{
						ToPositionN(&charRobot,target,55,&rbV);
					}
					else
					{
						TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}
					return 1;
				}
				
				if(charRobot.x<errord&&charRobot.y>=ballPt.y)
				{
					target.x = ballPt.x + d1;
					target.y = ballPt.y - d2;
					
					dx = charRobot.x - target.x;
					dy = charRobot.y - target.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>2)
					{
						ToPositionN(&charRobot,target,70,&rbV);
					}
					else
					{
						TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}
					return 1;
				}
				
				if(charRobot.x<errord&&(charRobot.theta>=0&&charRobot.theta<.4*Pi||charRobot.theta>0.6*Pi&&charRobot.theta<1.4*Pi||charRobot.theta>1.6*Pi&&charRobot.theta<2*Pi))
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					Point rbPt;
					rbPt.x = charRobot.x;
					rbPt.y = charRobot.y;
					double Error_theta = Getpt2ptAngle(rbPt,ballPt) - charRobot.theta;
					if(Error_theta<0)
						Error_theta = -Error_theta;
					if(Error_theta>Pi)
						Error_theta -= Pi;
					if(Error_theta>Pi/2)
						Error_theta = Pi - Error_theta;
					if(dist>distT)//7
					{
						if(Error_theta<0.15*Pi)
							ToPositionN(&charRobot,ballPt,50,&rbV);
						else
						{
							static int IsBoundFlag = 0;
							if(charRobot.x <= 5) 
								IsBoundFlag++;	
							else 
								IsBoundFlag = 0;
							if(IsBoundFlag > 20)
							{
								Point pt;
								pt.y = charRobot.y;
								pt.x = 8;
								ToPositionN(&charRobot,pt,60,&rbV);
							}
							else
								TurnToPointPD(&charRobot,ballPt,0,&rbV);
						}
					}
					else
					{
						rbV.LeftValue = TurnV;
						rbV.RightValue = -TurnV;
					}
					return	1;
				}
				if(ballPt.x<8&&ballPt.y>walltop-8)
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>distT)
					{
						ToPositionN(&charRobot,ballPt,70,&rbV);
					}
					else
					{
						rbV.LeftValue = TurnV;
						rbV.RightValue = -TurnV;
					}
					return	1;
				}
			}
			break;
		case	2:
			{
				tempPt.x = wallright;
				tempPt.y = walltop - NUMBER2-3;
				dx = charRobot.x - ballPt.x;
				dy = charRobot.y - ballPt.y;
				dist = sqrt(dx*dx + dy*dy);
				if(ball_point.x>=CENTER_X && dx<0 && dist<=10 && ((charRobot.theta>Pi*5/6&&charRobot.theta<=Pi)||(charRobot.theta>Pi*11/6&&charRobot.theta<=2*Pi)))
				{
					tempPt.x = wallright + 5;
					tempPt.y = walltop/2;
				}
				
				Point mycar[12];
				int carnum;
				ROSrect rect((int)ball_point.x,(int)ball_point.y+7,(int)ball_point.x+20,(int)ball_point.y-7);
				GetWarInformation(rect,mycar,carnum,true);
				
				if((ball_point.x>=160||carnum!=0) && dx<0 && dist<7.5)
				{
					rbV.LeftValue = TurnV;
					rbV.RightValue = -TurnV;
					return 1;
				}
				
				if(charRobot.y>walltop-errord && charRobot.x>=ballPt.x)
				{
					target.x = ballPt.x - d2;
					target.y = ballPt.y - d1;
					
					dx = charRobot.x - target.x;
					dy = charRobot.y - target.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>2)
					{
						ToPositionN(&charRobot,target,70,&rbV);
					}
					else
					{
						TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}

					if (distRobot2Pt(charRobot,ball_point)<7 && charRobot.y>ball_point.y&&charRobot.x-3.5>ball_point.x)
					{
						rbV.LeftValue=-TurnV;
						rbV.RightValue=TurnV;
					}
					else if (distRobot2Pt(charRobot,ball_point)<7 && charRobot.y<ball_point.y&&charRobot.x-3.5>ball_point.x)
					{
						rbV.LeftValue=TurnV;
						rbV.RightValue=-TurnV;
					}
					return 1;
				}
				if(charRobot.y>walltop - errord&&(charRobot.theta>.2*Pi&&charRobot.theta<.8*Pi||charRobot.theta>1.2*Pi&&charRobot.theta<1.8*Pi))
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					Point rbPt;
					rbPt.x = charRobot.x;
					rbPt.y = charRobot.y;
					double Error_theta = Getpt2ptAngle(rbPt,ballPt) - charRobot.theta;
					if(Error_theta<0)
						Error_theta = -Error_theta;
					if(Error_theta>Pi)
						Error_theta -= Pi;
					if(Error_theta>Pi/2)
						Error_theta = Pi - Error_theta;
					
					if(dist>distT)
					{
						if(Error_theta<0.15*Pi)
							ToPositionN(&charRobot,ballPt,50,&rbV);
						else
						{
							static int IsBoundFlag = 0;
							if(charRobot.y > 176) 
								IsBoundFlag++;	
							else 
								IsBoundFlag = 0;
							if(IsBoundFlag > 20)
							{
								Point pt;
								pt.x = charRobot.x;
								pt.y = 170;//173
								ToPositionN(&charRobot,pt,60,&rbV);//
							}
							else
								TurnToPointPD(&charRobot,ballPt,0,&rbV);
						}
					}
					else
					{
						rbV.LeftValue = TurnV;//
						rbV.RightValue = -TurnV;//
					}
					return	1;
				}
				
				if(ballPt.x>wallright-8&&ballPt.y>walltop-8)
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>distT)//6
					{
						ToPositionN(&charRobot,ballPt,70,&rbV);
					}
					else
					{
						rbV.LeftValue = TurnV;
						rbV.RightValue = -TurnV;
					}
					return	1;
				}

				if(EndProcessFlag == 1)
				{
					New_EndProcess(1,&charRobot,goal,ball_point,&rbV);	
					return 1;
				}
				else if(dist<7.0&&cs_robot.y>170&&cs_robot.x<ball_point.x&&ball_point.y>170)
				{
					rbV.LeftValue =TurnV ;//
					rbV.RightValue =-TurnV;//
					return 1;
				}
				else
				{
					CS_ToPositionNew(&charRobot,TO_BALL(ballPt),tempPt,1,&rbV);
				}			
				return 1;		
			}
			break;
		case	3:
			{
				tempPt.x = wallright;
				tempPt.y = walltop/2 - 5;
				
				dx = charRobot.x - ballPt.x;
				dy = charRobot.y - ballPt.y;
				dist = sqrt(dx*dx + dy*dy);
				
				ROSrect rect((int)ball_point.x-6,(int)ball_point.y,(int)ball_point.x+6,(int)ball_point.y-10);
				int num;
				GetWarInformation(rect,NULL,num,false);
				if(EndProcessFlag==0&&num==0 && dy>0 && dist<8)
				{
					rbV.LeftValue =TurnV ;//
					rbV.RightValue =-TurnV;//
					return 1;
				}
				if(charRobot.x>wallright-errord&&charRobot.y<=ballPt.y)
				{
					target.x = ballPt.x - d1;
					target.y = ballPt.y + d2;
					
					dx = charRobot.x - target.x;
					dy = charRobot.y - target.y;
					dist = sqrt(dx*dx + dy*dy);   
					
					if(dist>2)
					{
						ToPositionN(&charRobot,target,70,&rbV);
					}
					else
					{
						TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}
					return 1;
				}
				if(charRobot.x>wallright - errord&&(charRobot.theta>=0&&charRobot.theta<.4*Pi||charRobot.theta>.6*Pi&&charRobot.theta<1.4*Pi||charRobot.theta>1.6*Pi&&charRobot.theta<2*Pi))
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					Point rbPt;
					rbPt.x = charRobot.x;
					rbPt.y = charRobot.y;
					double Error_theta = Getpt2ptAngle(rbPt,ballPt) - charRobot.theta;
					if(Error_theta<0)
						Error_theta = -Error_theta;
					if(Error_theta>Pi)
						Error_theta -= Pi;
					if(Error_theta>Pi/2)
						Error_theta = Pi - Error_theta;
					if(dist>distT)
					{
						if(Error_theta<0.1*Pi)
							ToPositionN(&charRobot,ballPt,50,&rbV);
						else
							TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}
					else
					{
						rbV.LeftValue = TurnV;
						rbV.RightValue = -TurnV;
					}
					return	1;
				}
				
				static int count=0;
				if(num!=0 && charRobot.y>ball_point.y && charRobot.y<ball_point.y+10 && 
					distRobot2Pt(charRobot,ballPt)<10)
					count++;
				else
					count = 0;
				if(count>20)
				{   
					if(charRobot.x<=wallright-5)
					{
						rbV.LeftValue = TurnV;
						rbV.RightValue = -TurnV;
					}
					else
					{
						Point tempPt;
						tempPt.x = charRobot.x - 5;
						tempPt.y = charRobot.y + 10;
						ToPositionN(&charRobot,tempPt,60,&rbV);
					}
					return 1;
				}
			}
			break;
		case	4:
			{
				tempPt.x = NUMBER2;
				tempPt.y = NUMBER2;
				if(ballPt.y>35&&charRobot.x>ballPt.x&&(ballPt.y-charRobot.y)/(ballPt.x-charRobot.x)<3/4)
				{
					target.x = ballPt.x + d1;
					target.y = ballPt.y + d2;
					
					dx = charRobot.x - target.x;
					dy = charRobot.y - target.y;
					dist = sqrt(dx*dx + dy*dy);
					if(dist>2)
					{
						ToPositionN(&charRobot,target,55,&rbV);
					}
					else
					{
						TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}
					return 1;
				}
				if(charRobot.x<errord&&charRobot.y<=ballPt.y)
				{
					target.x = ballPt.x + d1;
					target.y = ballPt.y + d2;
					
					dx = charRobot.x - target.x;
					dy = charRobot.y - target.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>2)
					{
						ToPositionN(&charRobot,target,70,&rbV);
					}
					else
					{
						TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}
					return 1;
				}
				if(charRobot.x<errord&&(charRobot.theta>=0&&charRobot.theta<.4*Pi||charRobot.theta>.6*Pi&&charRobot.theta<1.4*Pi||charRobot.theta>1.6*Pi&&charRobot.theta<2*Pi))
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					Point rbPt;
					rbPt.x = charRobot.x;
					rbPt.y = charRobot.y;
					double Error_theta = Getpt2ptAngle(rbPt,ballPt) - charRobot.theta;
					if(Error_theta<0)
						Error_theta = -Error_theta;
					if(Error_theta>Pi)
						Error_theta -= Pi;
					if(Error_theta>Pi/2)
						Error_theta = Pi - Error_theta;
					if(dist>distT)
					{
						if(Error_theta<0.1*Pi)
							ToPositionN(&charRobot,ballPt,50,&rbV);
						else
						{
							static int IsBoundFlag = 0;
							if(charRobot.x < 4) 
								IsBoundFlag++;	
							else 
								IsBoundFlag = 0;
							if(IsBoundFlag > 20)
							{
								Point pt;
								pt.y = charRobot.y;
								pt.x = 7;
								ToPositionN(&charRobot,pt,60,&rbV);
							}
							else
								TurnToPointPD(&charRobot,ballPt,0,&rbV);
						}
					}
					else
					{
						rbV.LeftValue = -TurnV;
						rbV.RightValue = TurnV;
					}
					return	1;
				}
				if(ballPt.x<8&&ballPt.y<8)
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>6)
					{
						ToPositionN(&charRobot,ballPt,70,&rbV);
					}
					else
					{
						rbV.LeftValue = -TurnV;
						rbV.RightValue = TurnV;
					}
					return	1;
				}
			}
			break;
		case	5:
			{
				tempPt.x = wallright;
				tempPt.y = NUMBER2+3.0;
				dx = charRobot.x - ballPt.x;
				dy = charRobot.y - ballPt.y;
				dist = sqrt(dx*dx + dy*dy);
				if(ball_point.x>=CENTER_X && dx<0 && dist<=10 && ((charRobot.theta>Pi*5/6&&charRobot.theta<=Pi)||(charRobot.theta>Pi*11/6&&charRobot.theta<=2*Pi)))
				{
					tempPt.x = wallright + 5;
					tempPt.y = walltop/2;
				}
				
				Point mycar[12];
				int carnum;
				ROSrect rect((int)ball_point.x,(int)ball_point.y+7,(int)ball_point.x+20,(int)ball_point.y-7);
				GetWarInformation(rect,mycar,carnum,true);
				
				if((ball_point.x>=160||carnum!=0) && dx<0 && dist<7.5)
				{
					rbV.LeftValue = -TurnV;
					rbV.RightValue = TurnV;
					return 1;
				}
				if(charRobot.y<errord&&charRobot.x>=ballPt.x)
				{
					target.x = ballPt.x - d2;
					target.y = ballPt.y + d1;
					
					dx = charRobot.x - target.x;
					dy = charRobot.y - target.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>2)
					{
						ToPositionN(&charRobot,target,70,&rbV);
					}
					else
					{
						TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}

					if (distRobot2Pt(charRobot,ball_point)<7 && charRobot.y>ball_point.y&&charRobot.x-3.5>ball_point.x)
					{
						rbV.LeftValue=-TurnV;
						rbV.RightValue=TurnV;
					}
					else if (distRobot2Pt(charRobot,ball_point)<7 && charRobot.y<ball_point.y&&charRobot.x-3.5>ball_point.x)
					{
						rbV.LeftValue=TurnV;
						rbV.RightValue=-TurnV;
					}

					return 1;
				}
				if(charRobot.y<errord&&(charRobot.theta>.1*Pi&&charRobot.theta<.9*Pi||charRobot.theta>1.1*Pi&&charRobot.theta<1.9*Pi))
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					Point rbPt;
					rbPt.x = charRobot.x;
					rbPt.y = charRobot.y;
					double Error_theta = Getpt2ptAngle(rbPt,ballPt) - charRobot.theta;
					if(Error_theta<0)
						Error_theta = -Error_theta;
					if(Error_theta>Pi)
						Error_theta -= Pi;
					if(Error_theta>Pi/2)
						Error_theta = Pi - Error_theta;
					if(dist>distT)
					{
						if(Error_theta<0.15*Pi)
							ToPositionN(&charRobot,ballPt,50,&rbV);
						else
						{
							static int IsBoundFlag = 0;
							if(charRobot.y < 4) 
								IsBoundFlag++;	
							else 
								IsBoundFlag = 0;
							if(IsBoundFlag > 20)
							{
								Point pt;
								pt.x = charRobot.x;
								pt.y = 7;
								ToPositionN(&charRobot,pt,60,&rbV);
							}
							else
								TurnToPointPD(&charRobot,ballPt,0,&rbV);
						}
					}
					else
					{
						rbV.LeftValue = -TurnV;
						rbV.RightValue = TurnV;
					}
					return	1;
				}
				if(ballPt.x>wallright-8&&ballPt.y<8)
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>6)
					{
						ToPositionN(&charRobot,ballPt,70,&rbV);
					}
					else
					{
						rbV.LeftValue = -TurnV;
						rbV.RightValue = TurnV;
					}
					return	1;
				}
				if(EndProcessFlag == 1)
				{
					
					New_EndProcess(1,&charRobot,goal,ball_point,&rbV);	
					return 1;
				}
				else if(dist<7.0&&cs_robot.y<10&&cs_robot.x<ball_point.x&&ball_point.y<10)
				{
					rbV.LeftValue =-TurnV ;//
					rbV.RightValue =+TurnV;//
					return 1;
				}
				else
				{
					CS_ToPositionNew(&charRobot,TO_BALL(ballPt),tempPt,1,&rbV);
				}
				
				return 1;
			}
			break;
		case 6:
			{
				tempPt.x = wallright;
				tempPt.y = walltop/2 + 5;
				//crossing near the bottom line
				dx = charRobot.x - ballPt.x;
				dy = charRobot.y - ballPt.y;
				dist = sqrt(dx*dx + dy*dy);
				
				ROSrect rect((int)ball_point.x-6,(int)ball_point.y+10,(int)ball_point.x+6,(int)ball_point.y);
				int num;
				GetWarInformation(rect,NULL,num,false);
				if(EndProcessFlag==0&&num==0 && dy<0 && dist<8)
				{
					rbV.LeftValue = -TurnV;
					rbV.RightValue = TurnV;
					return 1;
				}
				if(charRobot.x>wallright-errord&&charRobot.y>=ballPt.y)
				{
					target.x = ballPt.x - d1;
					target.y = ballPt.y - d2;
					
					dx = charRobot.x - target.x;
					dy = charRobot.y - target.y;
					dist = sqrt(dx*dx + dy*dy);
					
					if(dist>2)
					{
						ToPositionN(&charRobot,target,70,&rbV);
					}
					else
					{
						TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}
					return 1;
				}
				if(charRobot.x>wallright - errord&&(charRobot.theta>=0&&charRobot.theta<.4*Pi||charRobot.theta>.6*Pi&&charRobot.theta<1.4*Pi||charRobot.theta>1.6*Pi&&charRobot.theta<2*Pi))
				{
					dx = charRobot.x - ballPt.x;
					dy = charRobot.y - ballPt.y;
					dist = sqrt(dx*dx + dy*dy);
					Point rbPt;
					rbPt.x = charRobot.x;
					rbPt.y = charRobot.y;
					double Error_theta = Getpt2ptAngle(rbPt,ballPt) - charRobot.theta;
					if(Error_theta<0)
						Error_theta = -Error_theta;
					if(Error_theta>Pi)
						Error_theta -= Pi;
					if(Error_theta>Pi/2)
						Error_theta = Pi - Error_theta;
					if(dist>distT)
					{
						if(Error_theta<0.1*Pi)
							ToPositionN(&charRobot,ballPt,50,&rbV);
						else
							TurnToPointPD(&charRobot,ballPt,0,&rbV);
					}
					else
					{
						rbV.LeftValue = -TurnV;
						rbV.RightValue = TurnV;
					}
					return	1;
				}
				
				static int count=0;
				if(num!=0 && charRobot.y>ball_point.y-10 && charRobot.y<ball_point.y && 
					distRobot2Pt(charRobot,ballPt)<10)
					count++;
				else
					count = 0;
				if(count>20)
				{
					if(charRobot.x<=wallright-5)
					{
						rbV.LeftValue = -TurnV;
						rbV.RightValue = TurnV;
					}
					else
					{
						Point tempPt;
						tempPt.x = charRobot.x - 5;
						tempPt.y = charRobot.y - 10;
						ToPositionN(&charRobot,tempPt,60,&rbV);
					}
					
					return 1;
				}
			}
			break;
		case 7:
		case 8:
			{
				CS_ToPositionNew(&charRobot,TO_BALL(ballPt),goal,1,&rbV);
			}
		default:
			break;
		}
		
		CS_ToPositionNew(&charRobot,TO_BALL(ballPt),goal,1,&rbV);
		if(EndProcessFlag==0 && charRobot.x>205 && distRobot2Pt(charRobot,ballPt)<7.5 && charRobot.x<ball_point.x)
		{
			if(ball_point.y<90 && ball_point.y>70)
			{
				if(ball_point.y>charRobot.y)
				{
					rbV.LeftValue = 60;
					rbV.RightValue = -60;
				}
				else
				{
					rbV.LeftValue = -60;
					rbV.RightValue = 60;
				}
			}
			else if(ball_point.y>90 && ball_point.y<115)
			{
				if(ball_point.y<charRobot.y)
				{
					rbV.LeftValue = -60;
					rbV.RightValue = 60;
				}
				else
				{
					rbV.LeftValue = 60;
					rbV.RightValue = -60;
				}
			}
			else
			{
				if(ball_point.y<90)
				{
					rbV.LeftValue = -60;
					rbV.RightValue = 60;
				}
				else if(ball_point.y>90)
				{
					rbV.LeftValue = 60;
					rbV.RightValue = -60;
				}
			}
		}
		
		return	1;
		
		
	}
int choosebestpt(RobotPose pRobotInford, BallPoint &ball, Point *pt)
{  
	//OpponentGoalKeeper
	//opp_robot_point[i]
	int i;
	Point robotpt,targetpt,targetpt1,targetpt2,directpt;
	robotpt.x=pRobotInford.x;//��Ӧ����С���ĳ������帡��λ����Ϣ
	robotpt.y=pRobotInford.y;
	targetpt.x=220;//�����м�
	targetpt.y=90;
	targetpt1.x=220;//�����ϱ߽�
	targetpt1.y=110;
	targetpt2.x=220;//�����±߽�
	targetpt2.y=70;
	LINEFORMULATION line,line1,line2;//����ֱ��
	////////////////////////////////////////////////////////////
	StdLineForm(robotpt, targetpt,&line);//����Ŀ������ߣ����������м�
	StdLineForm(robotpt, targetpt1,&line1);//���������ϱ߽��
	StdLineForm(robotpt, targetpt2,&line2);//���������±߽��
	///////////////////////////////////////////////////////////
	int sign1=0,sign2=0;//�з�������
	for(i=1;i<=5;i++)//������0��180��Χ��ĵз�С��
	{
		if(opp_robot_point[i].x<180)
			continue;
		else//�ж����������ڵз���������,����1������2�Ϸ�
		{
			if(((line1.a*opp_robot_point[i].x+line1.b*opp_robot_point[i].y)<-line1.c)&&
				((line.a*opp_robot_point[i].x+line.b*opp_robot_point[i].y)>=-line.c))	
			{//����1�����������ϱ߽��������£����������м����������
                sign1++;//�ег�����1
			}
			if(((line2.a*opp_robot_point[i].x+line2.b*opp_robot_point[i].y)>-line2.c)&&
				((line.a*opp_robot_point[i].x+line.b*opp_robot_point[i].y)<=-line.c))
			{//����2�����������±߽��������ϣ����м���������¡�
                sign2++;
			}
		}
	}
	/////////////////////////////////////////////////////////////
	//ѡ��Ŀ���
	directpt.x=224;
	if(sign1<sign2)//��2�еĵз�����
	{ 
		directpt.y=100;
	}
	else if(sign1>sign2)//��1�еĵط�����
	{
		directpt.y=80;
	}
	else//�������з���һ����
	{
		if(OpponentGoalKeeper.y>=90)//�ӵз�����Աλ�����ж������ù���Ŀ���
			directpt.y=80;
		else
			directpt.y=100;
	}
	*pt=directpt;//�����趨�õ�Ŀ���
	return 1;
}

int ToCatchBall(RobotPose *robot, BallPoint ball, int IfEndprocess, 
								  Velocity *pSpeed)
{
    Point target,shoot_target;//�����
	shoot_target.x = 225;//����Ŀ�����Ϊ��������λ��
	shoot_target.y = 90;	
	
	Point fball;
	fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*0.5+ball.x;
	fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*0.5+ball.y;//Ԥ����λ��
	target.x = (robot->x+ball.x)/2;
	target.y = (robot->y+ball.y)/2;//����Ŀ���
	if(ballCharacter.velocity>0.5)
		ToPositionPD(robot,target,80,30+qiusubi*ballCharacter.velocity,pSpeed);
	else
        ToPositionPD(robot,target,80,30+qiusubi*ballCharacter.velocity,pSpeed);
	//	AvoidALLRobots(robot,target,70,pSpeed);
	if(IfEndprocess == 1)
	{
		New_EndProcess(1,robot,shoot_target,ball,pSpeed);
	}
	return 1;
}

int New_QuickCurve(RobotPose *robot, BallPoint ball, Velocity *pSpeed)
{
    double dx,dy,dx1,dy1,dist,dbv;
	dbv=cn_AngleTrim2PI(ballCharacter.angle);
	BallPoint fball;
	fball.x=ballCharacter.velocity*cos(dbv)*0+ball.x;
	fball.y=ballCharacter.velocity*sin(dbv)*0+ball.y;
	//ת������ϵ����С��ָ��Ϊy��
	dx1 = fball.x - robot->x;
	dy1 = fball.y - robot->y;
	dx = dx1*cos(robot->theta - Pi/2) + dy1*sin(robot->theta - Pi/2);
	dy = -dx1*sin(robot->theta - Pi/2) + dy1*cos(robot->theta - Pi/2);
	dist = distRobot2Pt(*robot,fball);
	double R,V,V1,V2,V3,t,t1,angle;
	R = 3.75*3.0;//
	
	if(ballCharacter.velocity<=0.8)
		//V = qiusubi*ballCharacter.velocity + 4;//
		V=40;
	else
		//V = qiusubi*ballCharacter.velocity * 1.1;
		V=40;
	V1 = 15+qiusubi*ballCharacter.velocity;//20
    V2 = 0;//
	V3 = qiusubi*ballCharacter.velocity +10;
	//	t = 0.5;
	//	t1 = 0.5;
	angle = cn_AngleTrim2PI(ballCharacter.angle);
	
	int clock=1;
	Point directionpt;
	directionpt.x = 220;
	directionpt.y = 90;
	double angle1,angle2,angle3;
	angle1=cn_LineAngle(directionpt,oldBallPt[0]);
    angle2=cn_LineAngle(directionpt,oldBallPt[3]);
    angle3=cn_LineAngle(directionpt,oldBallPt[6]);
    if(angle3>angle2&&angle2>angle1)
		clock = 1;
	else if(angle1>angle2&&angle2>angle3)
		clock = -1;//�����������ϵ��˳ʱ��
	
    if(dist<10&&fabs(dx)<(3.75+2+4)&&fabs(dy)<3.75+8&&ballCharacter.velocity<2.0&&ballCharacter.velocity>0.6)
	{
		if(dist<9&&fabs(dx)<8.0&&fabs(dy)<3.75+2&&ballCharacter.velocity<2.0&&ballCharacter.velocity>0.6)
		{
			if(dist<9&&fabs(dx)>3.75+1.5&&fabs(dx)<8.0&&fabs(dy)<3.75+1&&ballCharacter.velocity>0.6)//�ɵ�
			{
				//if(angle>=Pi/2&&angle<=Pi)
				if(clock==-1)
				{
					if(dx>0)
					{
						pSpeed->LeftValue = V/R*(R + 3.75);
						pSpeed->RightValue = V/R*(R - 3.75);
					}
					else 
					{
						pSpeed->LeftValue = -V/R*(R - 3.75);
						pSpeed->RightValue = -V/R*(R + 3.75);
					}
				}
				//	if(angle>Pi&&angle<=3*Pi/2)
				if(clock==1)
				{
					if(dx>0)
					{
						pSpeed->LeftValue = -V/R*(R + 3.75);
						pSpeed->RightValue = -V/R*(R - 3.75);
					}
					else 
					{
						pSpeed->LeftValue = V/R*(R - 3.75);
						pSpeed->RightValue = V/R*(R + 3.75);
					}
				}
			}
			else if(fabs(dx)>3.75+1&&fabs(dx)<7.2&&fabs(dy)<=3.75+1&&ballCharacter.velocity>0.4&&
				ballCharacter.velocity<=0.6)
			{
				if(dx>0&&dy>0)
				{
					pSpeed->LeftValue = -V3;
					pSpeed->RightValue = -V3;
				}
				else if(dx>0&&dy<0)
				{
					pSpeed->LeftValue = V3;
					pSpeed->RightValue = V3;
				}
				else if(dx<0&&dy>0)
				{
					pSpeed->LeftValue = -V3;
					pSpeed->RightValue = -V3;
				}
				else if(dx<0&&dy<0)
				{
					pSpeed->LeftValue = V3;
					pSpeed->RightValue = V3;
				}
				else
				{
					if(dx>0&&ball.y<90)
					{
						pSpeed->LeftValue = -V3;
						pSpeed->RightValue = -V3;
					}
					else if(dx>0&&ball.y>90)
					{
						pSpeed->LeftValue = V3;
						pSpeed->RightValue = V3;
					}
					else if(dx<0&&ball.y<90)
					{
						pSpeed->LeftValue = V3;
						pSpeed->RightValue = V3;
					}
					else
					{
						pSpeed->LeftValue = -V3;
						pSpeed->RightValue = -V3;
					}
				}
			}
		}
		if(dist<10&&fabs(dx)>1&&fabs(dx)<=(3.75+2+3.5)&&fabs(dy)>(3.75+1)&&fabs(dy)<(3.75+2+6)&&
			ballCharacter.velocity<0.6)
		{
            if(dx>=(1)&&dx<=(3.75+2+3.5)&&dy>=(3.75)&&dy<=(3.75+8))
			{
				pSpeed->LeftValue = V1;
				//		 pSpeed->RightValue = 0;
				pSpeed->RightValue = V2;
			}
			if(dx>=(1)&&dx<=(3.75+2+3.5)&&dy<=-(3.75)&&dy>=-(3.75+8))
			{
				pSpeed->LeftValue = -V1;
				//		 pSpeed->RightValue = 0;
				pSpeed->RightValue = -V2;
			}
			if(dx<=-(1)&&dx>=-(3.75+2+3.5)&&dy>=(3.75)&&dy<=(3.75+8))
			{
				pSpeed->LeftValue = V2;
				//		 pSpeed->LeftValue = 0;
				pSpeed->RightValue = V1;
			}
			if(dx>=(1)&&dx<=(3.75+2+3.5)&&dy<=-(3.75)&&dy>=-(3.75+8))
			{
				pSpeed->LeftValue = -V2;
				//		pSpeed->LeftValue = 0;
				pSpeed->RightValue = -V1;
			}
		}
	}
	return 1;
}


int hitwallCS_CurveShoot(int IfEndprocess, RobotPose *robot, BallPoint ball, 
										   Point fball,Point directionpt,Point realdirectionpt, 
										   Velocity	*pSpeed,int hitwall)
{
	Point	cs_robot,cs_middlePt,cs_circlePt,cs_tempt;//,cs_ball,cs_ball1,cs_ball2;
	double kp4new,vemax,samespeed;//k1,k2,
	double Angle_e,disiredAngle,robotangle;
    double dist;
	double bangle;
	bangle=cn_AngleTrim2PI(ballCharacter.angle);
	fball.x=ball.x;
	fball.y=ball.y;
	dist=distRobot2Pt(*robot,fball);
	
	if(dist<=35)
	{
		samespeed=68;
		//fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*0.2+ball.x;
		//fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*0.2+ball.y;
	}
	else
	{
		samespeed=0.5*dist+50.5;
		//fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*1+ball.x;
		//fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*1+ball.y;
	}
	kp4new = 15.0;//
	vemax = 140;
	
	
	cs_robot.x = robot->x;
	cs_robot.y = robot->y;
	
	cs_middlePt.x = (cs_robot.x+fball.x)/2;
	cs_middlePt.y = (cs_robot.y+fball.y)/2;
	
	LINEFORMULATION  line_b2d,line_b2r,line_m2c;
	StdLineForm(fball,directionpt,&line_b2d);
	StdLineForm(fball,cs_robot,&line_b2r);
	
	cn_PointPerpendLine(cs_middlePt,&line_b2r,&line_m2c,&cs_tempt);
	cn_2LinesCrossPoint(&line_m2c,&line_b2d,&cs_circlePt);
	
	disiredAngle = atan2(cs_circlePt.y-robot->y,cs_circlePt.x-robot->x);
	
    double d1=distRobot2Pt(*robot,fball);
	double d2=fabs(distRobot2Pt(*robot,fball)*sin(robot->theta-cn_LineAngle(cs_robot,fball)));
	double angle_limit=0.2*Pi;
	double angle;
	angle=cn_AngleTrim2PI(robot->theta-cn_LineAngle(cs_robot,directionpt));
	if(angle>Pi)
		angle=Pi*2-angle;
	if(angle<angle_limit)
	{
		if(d1<12 && d2<3.5)//���ʵ�����  15  4.5
			disiredAngle=cn_LineAngle(cs_robot,TO_POINT(fball));
	}
	
	double speed_e,la,ka;
	la = 0.5*Pi;
    ka = samespeed;
	
	//////////////�����ʱ������////////////////////
	if(IfEndprocess>=0)
	{	
		///////////////////////////////////////////////////////////////////////////////
		if(distRobot2Pt(*robot,fball)<35)//
		{	
            ka = ka*(distRobot2Pt(*robot,fball)/40)+10;
			ka=max(35,ka);	
        }
		else
		{
			ka=samespeed;
		}
		
		if(ka<ballCharacter.velocity*qiusubi+10&&distRobot2Pt(*robot,fball)<10)
		{
			ka=ballCharacter.velocity*qiusubi+10;
			ka=min(35,ka);
		}		
	}
	///////////////////���϶����˶������Ԥ��///////////////////////////////
    if(ballCharacter.velocity>0.1)
	{
		double d_BallVelAngle;
		d_BallVelAngle = cn_AngleTrim2PI(ballCharacter.angle);
		
		double k1,k2;
		k1 = ballCharacter.velocity*qiusubi*cos(d_BallVelAngle)+ka*cos(disiredAngle);//24
		k2 = ballCharacter.velocity*qiusubi*sin(d_BallVelAngle)+ka*sin(disiredAngle);
		disiredAngle = atan2(k2,k1);
		
		disiredAngle = cn_AngleTrim2PI(disiredAngle);//��Ŀ��Ƕ�
				
        ka=sqrt(k1*k1+k2*k2);
		if(ka>70) 
			ka = 70;
	}
	
	////////////////////////////////////////////////////////////////////////////////
	robotangle = cn_AngleTrim2PI(robot->theta);
	//����Ƕ�ƫ��
	Angle_e = robotangle-disiredAngle;
	Angle_e = cn_AngleTrim2PI(Angle_e);
	//�����������ٶȲ������������ٶ�
    
    if(Angle_e <= Pi/2)
	{
        if(fabs(Angle_e)<Pi/6)
		{
			kp4new=(90/Pi)*fabs(Angle_e);
			kp4new=max(10,kp4new);
		}
	}
	else if(Angle_e <= Pi)
	{
		if(fabs(Pi-Angle_e)<Pi/6)
		{
			kp4new=(90/Pi)*fabs(Pi-Angle_e);
			kp4new=max(10,kp4new);
		}	
	}
    else if(Angle_e<3*Pi/2)
	{
        if(fabs(Angle_e-Pi)<Pi/6)
		{
			kp4new=(90/Pi)*fabs(Angle_e-Pi);
			kp4new=max(10,kp4new);
		}
	}
    else
	{
        if(fabs(2*Pi-Angle_e)<Pi/6)
		{
			kp4new=(90/Pi)*fabs(2*Pi-Angle_e);
			kp4new=max(10,kp4new);
		}
	}

	//����������
	if(Angle_e <= Pi/2)//�Ƕ�ƫ���ڵ�һ����
	{
		speed_e = kp4new*Angle_e;
		if(fabs(Angle_e)>la)
			samespeed = 0;
		else
			samespeed = ka*(la-fabs(Angle_e))/la;
			/*if(samespeed*speed_e/2>vx)
			{
			speed_e=(vx/samespeed)*2;
			}
		*/
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
		
	}
	else if(Angle_e <= Pi)
	{
		speed_e = kp4new*(Pi - Angle_e);
		if(fabs(Pi - Angle_e)>la)
			samespeed = 0;
		else
			samespeed = ka*(la-fabs(Pi-Angle_e))/la;
			/*if(samespeed*speed_e/2>vx)
			{
			speed_e=(vx/samespeed)*2;
			}
		*/
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}
	else if(Angle_e<3*Pi/2)
	{
		speed_e = kp4new*(Angle_e - Pi);
		if(fabs(Angle_e - Pi)>la)
			samespeed = 0;
		else
			samespeed = ka*(la-fabs(Angle_e - Pi))/la;
			/*if(samespeed*speed_e/2>vx)
			{
			speed_e=(vx/samespeed)*2;
			}
		*/
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}
	else
	{
		speed_e = kp4new*(2*Pi - Angle_e);
		if(fabs(2*Pi - Angle_e)>la)
			samespeed = 0;
		else
			samespeed = ka*(la-fabs(2*Pi - Angle_e))/la;
			/*if(samespeed*speed_e/2>vx)
			{
			speed_e=(vx/samespeed)*2;
			}
		*/
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
	}
	//ֱ������
	//   hold_ball(IfEndprocess,robot,ball,directionpt,80,pSpeed);
	New_QuickCurve(robot,ball,pSpeed);
	if(IfEndprocess!=0)
	{
		directionpt=realdirectionpt;
		New_EndProcess(IfEndprocess,robot,directionpt,ball,pSpeed);
	}
	
	return 1;
}



int CS_CurveShootfball(int IfEndprocess, RobotPose *robot, BallPoint ball, Point fball,
										 Point directionpt, Velocity*pSpeed,int hitwall)
{
	Point	cs_robot,cs_middlePt,cs_circlePt,cs_tempt;//,cs_ball,cs_ball1,cs_ball2;
	double kp4new,vemax,samespeed;//k1,k2,
	double Angle_e,disiredAngle,robotangle;
    double dist;
	dist=distRobot2Pt(*robot,fball);
	double bangle;
	bangle=cn_AngleTrim2PI(ballCharacter.angle);
	if(dist<=35)
	{
		samespeed=68;
		//fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*0.2+ball.x;
		//fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*0.2+ball.y;
	}
	else
	{
		samespeed=0.5*dist+50.5;
		//fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*1+ball.x;
		//fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*1+ball.y;
	}
	samespeed=samespeed*v_xishu;
	
    kp4new = 15;//15
	vemax = 140;
	
	cs_robot.x = robot->x;
	cs_robot.y = robot->y;
	
	cs_middlePt.x = (cs_robot.x+ball.x)/2;
	cs_middlePt.y = (cs_robot.y+ball.y)/2;
	
	LINEFORMULATION  line_b2d,line_b2r,line_m2c;
	StdLineForm(TO_POINT(ball),directionpt,&line_b2d);
	StdLineForm(TO_POINT(ball),cs_robot,&line_b2r);
	
	cn_PointPerpendLine(cs_middlePt,&line_b2r,&line_m2c,&cs_tempt);
	cn_2LinesCrossPoint(&line_m2c,&line_b2d,&cs_circlePt);
	
	disiredAngle = atan2(cs_circlePt.y-robot->y,cs_circlePt.x-robot->x);
	
    double d1=distRobot2Pt(*robot,ball);
	double d2=fabs(d1*sin(robot->theta-cn_LineAngle(cs_robot,TO_POINT(ball))));
	double angle_limit=0.2*Pi;
	double angle;
	angle=cn_AngleTrim2PI(robot->theta-cn_LineAngle(cs_robot,directionpt));
	if(angle>Pi)//(0~Pi)
		angle=Pi*2-angle;
	if(angle<angle_limit)
	{
	/*if(d1<15&&d2<4.5)
	disiredAngle=cn_LineAngle(cs_robot,ball);
		*/
		if(d1<12&&d2<3.5)//11,3.2
			disiredAngle=cn_LineAngle(cs_robot,directionpt);	
	}
	
	double speed_e,la,ka;
	la = 0.5*Pi;
    ka = samespeed;
	
	//////////////�����ʱ������////////////////////
	if(IfEndprocess>=0)
	{	
		///////////////////////////////////////////////////////////////////////////////
		if(distRobot2Pt(*robot,fball)<35)
		{		
            ka = ka*(distRobot2Pt(*robot,fball)/40)+10;
			ka=max(38,ka);//��С35
		}
		else
		{
			ka=samespeed;
		}
		if(ka<ballCharacter.velocity*qiusubi+10 && distRobot2Pt(*robot,fball)<10)
		{
			ka=ballCharacter.velocity *qiusubi+10;
			ka=min(38,ka);//���35   ���Ƴ��ӽ���ʱ���ٶȣ���ֹ����̫����ײ��
		}
	}
		
	///////////////////���϶����˶������Ԥ��///////////////////////////////
    if(ballCharacter.velocity>0.1)
	{
		double d_BallVelAngle;
		d_BallVelAngle = cn_AngleTrim2PI(ballCharacter.angle);
		
		double k1,k2;
		k1 = ballCharacter.velocity*25*cos(d_BallVelAngle)+ka*cos(disiredAngle);//24
		k2 = ballCharacter.velocity*25*sin(d_BallVelAngle)+ka*sin(disiredAngle);
		disiredAngle = atan2(k2,k1);
		disiredAngle = cn_AngleTrim2PI(disiredAngle);//��Ŀ��Ƕ�

        ka=sqrt(k1*k1+k2*k2);
		if(ka>72) 
			ka = 72;
	}
	
	////////////////////////////////////////////////////////////////////////////////
	
	robotangle = cn_AngleTrim2PI(robot->theta);
	//����Ƕ�ƫ��
	Angle_e = robotangle-disiredAngle;
	Angle_e = cn_AngleTrim2PI(Angle_e);
	
	//�����������ٶȲ������������ٶ�
    
    if(Angle_e <= Pi/2)
	{
        if(fabs(Angle_e)<Pi/6)
		{
			kp4new=(90/Pi)*fabs(Angle_e);
			kp4new=max(10,kp4new);//10~15
		}
	}
	else if(Angle_e <= Pi)
	{
		if(fabs(Pi-Angle_e)<Pi/6)
		{
			kp4new=(90/Pi)*fabs(Pi-Angle_e);
			kp4new=max(10,kp4new);
		}
		
	}
    else if(Angle_e<3*Pi/2)
	{
        if(fabs(Angle_e-Pi)<Pi/6)
		{
			kp4new=(90/Pi)*fabs(Angle_e-Pi);
			kp4new=max(10,kp4new);
		}
	}
    else
	{
        if(fabs(2*Pi-Angle_e)<Pi/6)
		{
			kp4new=(90/Pi)*fabs(2*Pi-Angle_e);
			kp4new=max(10,kp4new);
		}
	}
	
	//����������
	if(Angle_e <= Pi/2)//�Ƕ�ƫ���ڵ�һ����
	{
		speed_e = kp4new*Angle_e;
		if(fabs(Angle_e)>la)
			samespeed = 0;
		else
			samespeed = ka*(la-fabs(Angle_e))/la;
		//��ֹ��
		if(samespeed*speed_e/2>vx)
		{
			speed_e=(vx/samespeed)*2;
		}
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
	}

	else if(Angle_e <= Pi)
	{
		speed_e = kp4new*(Pi - Angle_e);
		if(fabs(Pi - Angle_e)>la)
			samespeed = 0;
		else
			samespeed = ka*(la-fabs(Pi-Angle_e))/la;
        if(samespeed*speed_e/2>vx)
		{
			speed_e=(vx/samespeed)*2;
		}
		pSpeed->LeftValue = samespeed + speed_e/2;
		pSpeed->RightValue = samespeed - speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}

	else if(Angle_e<3*Pi/2)
	{
		speed_e = kp4new*(Angle_e - Pi);
		if(fabs(Angle_e - Pi)>la)
			samespeed = 0;
		else
			samespeed = ka*(la-fabs(Angle_e - Pi))/la;
        if(samespeed*speed_e/2>vx)
		{
			speed_e=(vx/samespeed)*2;
		}
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
		pSpeed->LeftValue =- pSpeed->LeftValue;
		pSpeed->RightValue =- pSpeed->RightValue;
	}

	else
	{
		speed_e = kp4new*(2*Pi - Angle_e);
		if(fabs(2*Pi - Angle_e)>la)
			samespeed = 0;
		else
			samespeed = ka*(la-fabs(2*Pi - Angle_e))/la;
        if(samespeed*speed_e/2>vx)
		{
			speed_e=(vx/samespeed)*2;
		}
		pSpeed->LeftValue = samespeed - speed_e/2;
		pSpeed->RightValue = samespeed + speed_e/2;
	}
	//ֱ������
	//   hold_ball(IfEndprocess,robot,ball,directionpt,80,pSpeed);
	New_QuickCurve(robot,ball,pSpeed);
	if(IfEndprocess!=0)
	{		
		New_EndProcess(IfEndprocess,robot,directionpt,ball,pSpeed);
	}
	return 1;
}


int CS_ToPositionNewfyp(RobotPose *robot, BallPoint ball, Point directionpt, //*robot��Ӧ����С���ĳ������帡��λ����Ϣ  //ball������λ����Ϣ //directionpt����Ŀ��������λ����Ϣ
										   int IfEndprocess, Velocity *pSpeed)                     //IfEndprocessĩ�˴�����־λ //*pSpeed�Ƕ�Ӧ���ŵ�С����������
{
	
	int flag_1=0 , down=0;
	double minspeed = 0.0;
	if(oldBallPt[0].y > oldBallPt[3].y && oldBallPt[3].y > oldBallPt[6].y)//�������˶�
		down = 1;
	else if(oldBallPt[0].y < oldBallPt[3].y && oldBallPt[3].y < oldBallPt[6].y)//�������˶�
		down = -1;
	if(oldBallPt[0].x > oldBallPt[3].x && oldBallPt[3].x > oldBallPt[6].x)//�����ҷ����ŷ����˶�
		flag_1 = 1;
// 	if (samespeed>=120)//85
// 	{
//        samespeed=120;//85
// 	}
	int minrflag,midrflag,maxrflag;
	minrflag=0;
	midrflag=0;
	maxrflag=0;
	double	dist6,distE,angle7,angle8,maxe,angle4,anglerb2ball;//����һЩ�Ƕȡ��������
	Point robotpt;//���岢��ֵС��λ��������Ϣ
	robotpt.x=robot->x;
	robotpt.y=robot->y;
	maxe = 7;
	anglerb2ball = Getpt2ptAngle(robotpt,ball);//����������ֱ����x��������нǣ�����robotptΪԭ�㣩
	dist6 = distRobot2Pt(*robot,ball);//������С���ľ���
	angle7 = cn_AngleTrim2PI(robot->theta);//trim theta to between 0 and 2pi
	angle8 = cn_AngleTrim2PI(angle7 - anglerb2ball);//trim theta to between 0 and 2pi
	if(angle8>Pi)
		angle8 = 2*Pi  -  angle8;
	if(angle8>Pi/2)	
		angle8 = Pi - angle8;
	distE = fabs(dist6*sin(angle8));

	int hitwall=0;
	double bvangle;
	bvangle=cn_AngleTrim2PI(ballCharacter.angle);//�������½�ԭ��������x��������нǽǶ�
	Point fball;
	fball.x=ballCharacter.velocity*cos(bvangle)*yanchi+ball.x;//Ԥ����λ��
	fball.y=ballCharacter.velocity*sin(bvangle)*yanchi+ball.y;
	Point realdirectionpt;     //�����
	realdirectionpt=directionpt;//directionpt����Ŀ��������λ����Ϣ
	Point cs_tempt,cs_pt1,cs_pt2,cs_pt;//�����
	CIRCLEFORMULATION cs_circle1;//����Բ����Ϣ��Բ�����꼰�뾶��
	LINEFORMULATION line_b2d,line_b2c;//����ֱ�ߣ�ʵ�ʶ������ֱ��һ��ʽ��ϵ��a,b,c��
	StdLineForm(fball,directionpt,&line_b2d);//��֪Ԥ����λ�õ��Ŀ��㣬���������ȷ����ֱ��line_b2d��һ��ʽ��ϵ����
	
	double shoottime;
	int robotno=0;
	///ȷ�����ţ�ȷ���봫����С��λ����Ϣһ�µ�С������
	if(Robot[1].x==robot->x&&Robot[1].y==robot->y)
	{
		robotno=1;
	}
	if(Robot[2].x==robot->x&&Robot[2].y==robot->y)
	{
		robotno=2;
	}
	if(Robot[3].x==robot->x&&Robot[3].y==robot->y)
	{
		robotno=3;
	}
	if(Robot[4].x==robot->x&&Robot[4].y==robot->y)
	{
		robotno=4;
	}
	/////ȷ���������ʱ��
	shoottime=GetCharPerformance(robotno,*robot,TO_POINT(ball),directionpt);
	if(ballCharacter.velocity>0.2)
	{
		if(oldBallPt[0].x > oldBallPt[3].x && oldBallPt[3].x > oldBallPt[6].x)//back
		{
			shoottime=shoottime*(1+ballCharacter.velocity);
		}
		else
		{
			shoottime=shoottime*0.8;
		}
	}
	/////	
	fball.x=ballCharacter.velocity*cos(bvangle)*shoottime+ball.x+ballCharacter.velocity*cos(bvangle)*yanchi;//Ԥ����λ��
	fball.y=ballCharacter.velocity*sin(bvangle)*shoottime+ball.y+ballCharacter.velocity*sin(bvangle)*yanchi;
	if(ballCharacter.velocity>0.2)
	{
		if(fball.y>165&&ball.x>35&&ball.x<185)
		{
			Point pt;
			pt.x=ball.x;
			pt.y=ball.y-8;
			if(distRobot2Pt(*robot,ball)>=20)//������ľ���
			{
				pt.y=ball.y-10;
			}
			directionpt.x=223;
			directionpt.y=pt.y;
			StdLineForm(pt,directionpt,&line_b2d);//��֪���㣬���������ȷ����ֱ��
			hitwall=1;
		}
		if(fball.y<15&&ball.x>35&&ball.x<185)
		{
			
			Point pt;
			pt.x=ball.x;
			pt.y=ball.y+8;
			if(distRobot2Pt(*robot,ball)>=20)//������ľ���
			{
				pt.y=ball.y+10;
			}
			directionpt.x=223;
			directionpt.y=pt.y;
			StdLineForm(pt,directionpt,&line_b2d);//��֪���㣬���������ȷ����ֱ��
			hitwall=1;
		}
	}
	else
	{
		if(ball.y>165&&ball.x>35&&ball.x<185)
		{
		
			Point pt;
			pt.x=ball.x;
			pt.y=ball.y-8;
			if(distRobot2Pt(*robot,ball)>=20)//������ľ���
			{
				pt.y=ball.y-10;
			}
			directionpt.x=223;
			directionpt.y=pt.y;
			StdLineForm(pt,directionpt,&line_b2d);//��֪���㣬���������ȷ����ֱ��
			hitwall=1;
		}
		if(ball.y<15&&ball.x>35&&ball.x<185)
		{
			Point pt;
			pt.x=ball.x;
			pt.y=ball.y+8;
			if(distRobot2Pt(*robot,ball)>=20)//������ľ���
			{
				pt.y=ball.y+10;
			}
			directionpt.x=223;
			directionpt.y=pt.y;
			StdLineForm(pt,directionpt,&line_b2d);//��֪���㣬���������ȷ����ֱ��
			hitwall=1;
		}
	}
	////����Ϊѡ��directionpt���꣬���ڱ߽���ͬʱ��ֵײǽ��־
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	fball.x=ball.x+ballCharacter.velocity*cos(bvangle)*yanchi;/////Ԥ������λ��
	fball.y=ball.y+ballCharacter.velocity*sin(bvangle)*yanchi;
	cn_PointPerpendLine(fball,&line_b2d,&line_b2c,&cs_tempt);//��һ������ֱ�ߴ�ֱ��ֱ�߷��̺ͽ���
	cs_circle1.x = fball.x;///Ԥ������λ��ΪԲ����Բ
	cs_circle1.y = fball.y;
	double ball_vy;
	double ballangle1;
	ballangle1=ballCharacter.angle;
	ballangle1=cn_AngleTrim2PI(ballangle1);
	if (ballangle1>Pi)
	{
		ballangle1=ballangle1-2*Pi;
	}
	ballangle1=fabs(ballangle1);
	ball_vy=ballCharacter.velocity*sin(ballangle1);////��ÿ֡�仯�ľ���
	if (ball_vy<0.2)/////////////////////////////**************************************
	{
		cs_circle1.r =40;//12
		minrflag = 1;
	}
	if (ball_vy<0.6&&ball_vy>=0.2)
	{
		cs_circle1.r = 14;//14
		midrflag =1;
	}
	if (ball_vy>=0.6&&ball_vy<1)
	{
		cs_circle1.r = 16;//16
		maxrflag = 1;
	}
	if (ball_vy>=1)
	{
		cs_circle1.r = 18;//18
		maxrflag = 1;
	}
//////���ϲ�������Ҫ����cs_circle1.r           ballCharacter.velocity
/////////////////////////////////////////////////////////////
	cn_LineCircleCross(&line_b2c,&cs_circle1,&cs_pt1,&cs_pt2);//��ֱ�ߺ�Բ�Ľ��㣬&cs_pt1,&cs_pt2���Ӧ���صĽ��㣬���û���򷵻�-1��ֻ��һ���򷵻�0���������򷵻�1��
	Point cs_pt3;	
	//��Բ�Ľ��㣬��cs_pt1Ϊ�Ͻ��㣬cs_pt2Ϊ�½���
	if (cs_pt1.y<cs_pt2.y)
	{
		cs_pt3=cs_pt1;
		cs_pt1=cs_pt2;
		cs_pt2=cs_pt3;
	}
////////////////////////////////////////////////////////////////
	double theta,dx,dy,dx1,dy1;
	theta = atan2(ball.y-directionpt.y,ball.x-directionpt.x);//����Ŀ���������x��������н�
	theta = cn_AngleTrim2PI(theta);//trim theta to between 0 and 2pi
	///////ת������ϵ,����Ϊԭ�㣬��Ŀ���ָ����ķ���Ϊy��
	dx = robot->x-fball.x;
	dy = robot->y-fball.y;
	dx1 = dx*cos(theta - Pi/2) + dy*sin(theta - Pi/2);//(����ת������ת)
	dy1 = -dx*sin(theta - Pi/2) + dy*cos(theta - Pi/2);
//////////////////////////////////////////////////////////////

	//һ����
	if(dy1<=0.57735*dx1&&dy1<=-0.57735*dx1) 
//	if(robot->x > 5+(-line_b2c.b*robot->y-line_b2c.c)/line_b2c.a)//)
	{
        double	angle1,pt1angle2,pt2angle2,result,ddist,pt1angle,pt2angle,angle2;
		Point rpt;
		int dist;
		int angleforpi,angle2forpi;
		angle2 = cn_AngleTrim2PI(robot->theta);
		rpt.x = robot->x;//С��λ������
		rpt.y = robot->y;
		pt1angle = Getpt2ptAngle(rpt,cs_pt1);//��������ֱ����x��������нǣ�����rptΪԭ�㣩
		pt2angle = Getpt2ptAngle(rpt,cs_pt2);//��������ֱ����x��������нǣ�����rptΪԭ�㣩
		pt1angle2 = pt1angle - angle2;//���ĳ����복��cs_pt1�����ߣ�֮��ļн�
		pt2angle2 = pt2angle - angle2;//���ĳ����복��cs_pt2�����ߣ�֮��ļн�
		pt1angle2 = cn_AngleTrim2PI(pt1angle2);
		pt2angle2 = cn_AngleTrim2PI(pt2angle2);
		
		if(pt1angle2>Pi)
			pt1angle2 = 2*Pi  -  pt1angle2;
		if(pt1angle2>Pi/2)
			pt1angle2 = Pi - pt1angle2;                                                                  
		if(pt2angle2>Pi)
			pt2angle2 = 2*Pi  -  pt2angle2;
		if(pt2angle2>Pi/2)
			pt2angle2 = Pi - pt2angle2;
        ddist = distRobot2Pt(*robot,ball);//������ľ���
		dist = ddist;//������ľ���
		///////////////////////////////////////////////////////////////
		int pt1score,pt2score;
		/////����pt1angle2��pt2angle2��dist��ballCharacter.velocity�����٣��Ĵ�С��Χ������˶�����������������֡���ֵ��pt1score,pt2score��ͬ����������
		//pt1
		if(pt1angle2<Pi/18)//10
		{
            pt1score = charPerformancescore00[dist];
		}
		else if(pt1angle2<Pi/9)//20
		{
			pt1score = charPerformancescore010[dist];
		}
		else if(pt1angle2<Pi/6)//30
		{
            pt1score = charPerformancescore020[dist];
		}
		else if(pt1angle2<2*Pi/9)//40
		{
			pt1score = charPerformancescore030[dist];
		}
		else if(pt1angle2<5*Pi/18)//50
		{
			pt1score = charPerformancescore040[dist];
		}
		else if(pt1angle2<Pi/3)//60
		{
			pt1score = charPerformancescore050[dist];
		}
		else if(pt1angle2<7*Pi/18)//70
		{
			pt1score = charPerformancescore060[dist];
		}
		else if(pt1angle2<8*Pi/18)//80
		{
			pt1score = charPerformancescore070[dist];
		}
		else if(pt1angle2<Pi/2)//90
		{
			pt1score = charPerformancescore080[dist];
		}
		else
		{ 
			pt1score = charPerformancescore090[dist];
		}
		//pt2
		if(pt2angle2<Pi/18)//10
		{
            pt2score = charPerformancescore00[dist];
		}
		else if(pt2angle2<Pi/9)//20
		{
			pt2score = charPerformancescore010[dist];
		}
		else if(pt2angle2<Pi/6)//30
		{
            pt2score = charPerformancescore020[dist];
		}
		else if(pt2angle2<2*Pi/9)//40
		{
			pt2score = charPerformancescore030[dist];
		}
		else if(pt2angle2<5*Pi/18)//50
		{
			pt2score = charPerformancescore040[dist];
		}
		else if(pt2angle2<Pi/3)//60
		{
			pt2score = charPerformancescore050[dist];
		}
		else if(pt2angle2<7*Pi/18)//70
		{
			pt2score = charPerformancescore060[dist];
		}
		else if(pt2angle2<8*Pi/18)//80
		{
			pt2score = charPerformancescore070[dist];
		}
		else if(pt2angle2<Pi/2)//90
		{
			pt2score = charPerformancescore080[dist];
		}
		else
		{ 
			pt2score = charPerformancescore090[dist];
		}
		if(dist<15)/////�������
		{
			if(dist<8)
			{
				pt1score=0;
				pt2score=0;
			}
			else
			{
				pt1score=pt1score+(15-dist);
				pt2score=pt2score+(15-dist);
				pt1score=pt1score*(dist-8)/7;
				pt2score=pt2score*(dist-8)/7;
			}
		}
		if(ballCharacter.velocity>0.2)
		{
             if(oldBallPt[0].x > oldBallPt[3].x && oldBallPt[3].x > oldBallPt[6].x)//back
			 {
				 pt1score=pt1score*(1+ballCharacter.velocity);
				 pt2score=pt2score*(1+ballCharacter.velocity);
			 }
			 else
			 {
				 pt1score=pt1score*0.8;
				 pt2score=pt2score*0.8;
			 }
		}
////////////////////////////////////////////////////////////		
		Point fpt1ball,fpt2ball;
		fpt1ball.x = ballCharacter.velocity*cos(bvangle)*pt1score+ball.x;//Ԥ�����ܵ�λ�ã��ϣ�
		fpt1ball.y = ballCharacter.velocity*sin(bvangle)*pt1score+ball.y;//Ԥ�����ܵ�λ��
		fpt2ball.x = ballCharacter.velocity*cos(bvangle)*pt2score+ball.x;//Ԥ�����ܵ�λ�ã��£�
		fpt2ball.y = ballCharacter.velocity*sin(bvangle)*pt2score+ball.y;//Ԥ�����ܵ�λ��
		LINEFORMULATION pt1b2d,pt2b2d,pt1b2c,pt2b2c;
		StdLineForm(fpt1ball,directionpt,&pt1b2d);//��֪���㣬���������ȷ����ֱ��
		StdLineForm(fpt2ball,directionpt,&pt2b2d);//��֪���㣬���������ȷ����ֱ��
		Point cpt;
		cn_PointPerpendLine(fpt1ball,&pt1b2d,&pt1b2c,&cpt);//��һ����ô�ֱ��һ��ֱ�ߵķ��̺ͽ���
		cn_PointPerpendLine(fpt2ball,&pt2b2d,&pt2b2c,&cpt);//��һ����ô�ֱ��һ��ֱ�ߵķ��̺ͽ���
		CIRCLEFORMULATION fcirclept1,fcirclept2;
		fcirclept1.x=fpt1ball.x;
		fcirclept1.y=fpt1ball.y;
		fcirclept1.r=cs_circle1.r;//25260��ǰ��Ԥ����Ϊ���ģ��Բ���ball_vy����ÿ֡�仯�ľ��룩Ϊ�ж���׼���������İ뾶cs_circle1.r
		//////���Ͻ����Ԥ��Բ
		fcirclept2.x=fpt2ball.x;
		fcirclept2.y=fpt2ball.y;
		fcirclept2.r=cs_circle1.r;
		//////���½����Ԥ��Բ

		Point ffpt1pt1,ffpt1pt2,ffpt1pt3,ffpt2pt1,ffpt2pt2,ffpt2pt3,fpt1,fpt2;
		cn_LineCircleCross(&pt1b2c,&fcirclept1,&ffpt1pt1,&ffpt1pt2);//��ֱ�ߺ�Բ�Ľ��㣬ffpt1pt1, ffpt1pt2�����������Ӧ���صĽ��㣨���û���򷵻�-1��ֻ��һ���򷵻�0���������򷵻�1��
		///���Ͻ������ffpt1pt1
		if (ffpt1pt1.y<ffpt1pt2.y)
		{
			ffpt1pt3=ffpt1pt1;
			ffpt1pt1=ffpt1pt2;
			ffpt1pt2=ffpt1pt3;
		}
		if(cs_pt1.y>cs_pt2.y&&ffpt1pt1.y>ffpt1pt2.y)
		{
			fpt1=ffpt1pt1;//�Ͻ���
		}
		else if(cs_pt1.y<cs_pt2.y&&ffpt1pt1.y<ffpt1pt2.y)
		{
			fpt1=ffpt1pt1;
		}
		else
		{
            fpt1=ffpt1pt2;
		}
		
		cn_LineCircleCross(&pt2b2c,&fcirclept2,&ffpt2pt1,&ffpt2pt2);
		if (ffpt2pt1.y<ffpt2pt2.y)
		{
			ffpt2pt3=ffpt2pt1;
			ffpt2pt1=ffpt2pt2;
			ffpt2pt2=ffpt2pt3;
		}
		if(cs_pt1.y>cs_pt2.y&&ffpt2pt1.y>ffpt2pt2.y)
		{
			fpt2=ffpt2pt2;
		}
		else if(cs_pt1.y<cs_pt2.y&&ffpt2pt1.y<ffpt2pt2.y)
		{
			fpt2=ffpt2pt2;
		}
		else
		{
			fpt2=ffpt2pt1;
		}
//////////////////////////////////////////�õ�Ԥ����ܵ�

///////////////////////////////////////////////////////////////////////		
		int notcspt1,notcspt2,allout;
		notcspt1=0;
		notcspt2=0;
		allout=0;
		if(fpt1.y>165||fpt1.y<15)//�ӽ����±߽�
		{
			notcspt1=1;
		}
		if(fpt2.y>165||fpt2.y<15)//���±߽�����
		{
			notcspt2=1;
		}
		if(cs_pt1.y>165||cs_pt1.y<15)
		{
			notcspt1=1;
		}
		if(cs_pt2.y>165||cs_pt2.y<15)
		{
			notcspt2=1;
		}
		if(notcspt1==1&&notcspt2==1)
		{
			allout=1;
		}

//////�ж�1��2�ܵ��Ƿ�ϸ�
//////////////////////////////////////////////////////////
		double V2=10;
		/////���������߽����ƶ�ʱ��Ҫ��������
        if(fabs(ballCharacter.velocity)>0.4&&(notcspt1==1||notcspt2==1)&&ball.y<=150&&ball.y>=30)
		{
             if(allout==1)
			 {
                  double distfpt1,distfpt2;
				  if(down==-1)//�������˶�
				  {
					  distfpt1=cs_pt1.y-165;
				  }
				  else//�������˶�
				  {
					  distfpt1=15-cs_pt1.y;
				  }
				  if(down==-1)//�������˶�
				  {
					  distfpt2=cs_pt2.y-165;
				  }
				  else//�������˶�
				  {
					  distfpt2=15-cs_pt2.y;
				  }
				  
				  if(distfpt1<=distfpt2)//////////////����(���?)�ٶ�(���������ٶȣ�)
				  {
					    if (distRobot2Pt(*robot,cs_pt1)>50)
						{
							minspeed=100;//�����ܵ����ϴ�ʱ�����ýϸߵ�(���?)�ٶ�(���������ٶȣ�)
						}
						if (distRobot2Pt(*robot,cs_pt1)<=50)//�����ܵ���벻̫��ʱ
						{
							if (distE>maxe||distRobot2Pt(*robot,cs_pt1)>=10)//distE����С������ֱ�ߵĴ�ֱ����  //maxe��(=7)
							{
								if (distRobot2Pt(*robot,cs_pt1)>=30)
								{
										minspeed=90;
								}
								else
								{
									minspeed=65+distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
									if (minspeed>=90)
									{
										minspeed=90;
									}
									if(minspeed<80)
									{
										minspeed=80;
									}
								}
							}
							else
							{
								minspeed=distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
							}
						}
					  ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);//(���?)�ٶ�(���������ٶȣ�)������ɺ�ִ���ܵ㺯��
					  cs_pt.x=cs_pt1.x;
					  cs_pt.y=cs_pt1.y;
				  }
				  else//(distfpt1>distfpt2)
				  { 
					  if (distRobot2Pt(*robot,cs_pt2)>50)
						{
							minspeed=100;
						}
						if (distRobot2Pt(*robot,cs_pt2)<=50)
						{
							if (distE>maxe||distRobot2Pt(*robot,cs_pt2)>=10)
							{
								if (distRobot2Pt(*robot,cs_pt2)>=30)
								{
										minspeed=90;
								}
								else
								{
									minspeed=65+distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
									if (minspeed>=90)
									{
										minspeed=90;
									}
									if(minspeed<80)
									{
										minspeed=80;

									}
								}
							}
							else
							{
							
								minspeed=distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
							}
						}
					ToPositionPDchampionnew(robot,cs_pt2,minspeed*v_xishu,pSpeed);
					  cs_pt.x=cs_pt2.x;
					  cs_pt.y=cs_pt2.y;
				  }
			 }
			 else//(allout != 1)
			 {
				 if(notcspt1==1)
				 {
					 if (distRobot2Pt(*robot,cs_pt2)>50)
					{
						minspeed=100;
					}
					if (distRobot2Pt(*robot,cs_pt2)<=50)
					{
						if (distE>maxe||distRobot2Pt(*robot,cs_pt2)>=10)
						{
							if (distRobot2Pt(*robot,cs_pt2)>=30)
							{
									minspeed=90;
							}
							else
							{
								minspeed=65+distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
								if (minspeed>=90)
								{
									minspeed=90;
								}
								if(minspeed<80)
								{
									minspeed=80;
								}
							}
						}
						else
						{
							minspeed=distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
						}
					}  
				   ToPositionPDchampionnew(robot,cs_pt2,minspeed*v_xishu,pSpeed);			 
				   cs_pt.x=cs_pt2.x;
				   cs_pt.y=cs_pt2.y;
				 }
				 if(notcspt2==1)
				 {
					 if (distRobot2Pt(*robot,cs_pt1)>50)
						{
							minspeed=100;
						}
						if (distRobot2Pt(*robot,cs_pt1)<=50)
						{
							if (distE>maxe||distRobot2Pt(*robot,cs_pt1)>=10)
							{
								if (distRobot2Pt(*robot,cs_pt1)>=30)
								{
										minspeed=90;
								}
								else
								{
									minspeed=65+distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
									if (minspeed>=90)
									{
										minspeed=90;
									}
									if(minspeed<80)
									{
										minspeed=80;
									}
								}
							}
							else
							{
								minspeed=distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
							}
						}
					ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);	 
					cs_pt.x=cs_pt1.x;
					cs_pt.y=cs_pt1.y;
				 }
			 }
		}
/////////////////////////////////////////////////////////////////////////////
		else//����ģʽ
		{
			notcspt1=0;
			notcspt2=0;
			allout=0;
            if(cs_pt1.y>165||cs_pt1.y<15)
			{
				notcspt1=1;
			}
			if(cs_pt2.y>165||cs_pt2.y<15)
			{
				notcspt2=1;
			}
			if(notcspt1==1&&notcspt2==1)
			{
				allout=1;
			}
			if(allout==1)//�����ܵ�����ϸ�
			{
				double distcspt1,distcspt2;
				if(cs_pt1.y>90)
				{
					distcspt1=fpt1.y-165;
				}
				else
				{
					distcspt1=15-fpt1.y;
				}
				if(cs_pt2.y>90)
				{
					distcspt2=fpt2.y-165;
				}
				else
				{
					distcspt2=15-fpt2.y;
				}
				if(distcspt1<distcspt2)
				{
					if (distRobot2Pt(*robot,cs_pt1)>50)
					{
						minspeed=100;//110
					}
					if (distRobot2Pt(*robot,cs_pt1)<=50)
					{
						if (distE>maxe||distRobot2Pt(*robot,cs_pt1)>=10)
						{
							if (distRobot2Pt(*robot,cs_pt1)>=30)
							{
									minspeed=90;
							}
							else
							{
								minspeed=65+distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
								if (minspeed>=90)
									{
										minspeed=90;
									}
									if(minspeed<80)
									{
										minspeed=80;
									}
							}
						}
						else
						{
							minspeed=distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
						}
					}	
					ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);	  
					cs_pt.x=cs_pt1.x;
					cs_pt.y=cs_pt1.y;
				}
				else
				{
					if (distRobot2Pt(*robot,cs_pt2)>50)
					{
						minspeed=100;
					}
					if (distRobot2Pt(*robot,cs_pt2)<=50)
					{
						if (distE>maxe||distRobot2Pt(*robot,cs_pt2)>=10)
						{
							if (distRobot2Pt(*robot,cs_pt2)>=30)
							{
									minspeed=90;
							}
							else
							{
								minspeed=65+distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
									if (minspeed>=90)
									{
										minspeed=90;
									}
									if(minspeed<80)
									{
										minspeed=80;

									}
							}
						}
						else
						{
							minspeed=distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
						}
					}
				    ToPositionPDchampionnew(robot,cs_pt2,minspeed*v_xishu,pSpeed);	  
					cs_pt.x=cs_pt2.x;
					cs_pt.y=cs_pt2.y;
				}
			}
			else//���������ܵ㲻�ϸ�(allout!=1)
			{
				if(robot->y < (-line_b2d.a*robot->x-line_b2d.c)/line_b2d.b)//ֱ����
				{
					if(cs_pt1.y<cs_pt2.y)
					{
						if(notcspt1==1)
						{
							if (distRobot2Pt(*robot,cs_pt2)>50)
							{
								minspeed=100;
							}
							if (distRobot2Pt(*robot,cs_pt2)<=50)
							{
								if (distE>maxe||distRobot2Pt(*robot,cs_pt2)>=10)
								{
									if (distRobot2Pt(*robot,cs_pt2)>=30)
									{
											minspeed=90;
									}
									else
									{
										minspeed=65+distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
											if (minspeed>=90)
											{
												minspeed=90;
											}
											if(minspeed<80)
											{
												minspeed=80;
											}
									}
								}
								else
								{
									minspeed=distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
								}
							}
						    ToPositionPDchampionnew(robot,cs_pt2,minspeed*v_xishu,pSpeed);
							cs_pt.x=cs_pt2.x;
							cs_pt.y=cs_pt2.y;
							
						}
						else
						{
							if (distRobot2Pt(*robot,cs_pt1)>50)
							{
								minspeed=100;
							}
							if (distRobot2Pt(*robot,cs_pt1)<=50)
							{
								if (distE>maxe||distRobot2Pt(*robot,cs_pt1)>=10)
								{
									if (distRobot2Pt(*robot,cs_pt1)>=30)
									{
											minspeed=90;
									}
									else
									{
										minspeed=65+distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
											if (minspeed>=90)
											{
												minspeed=90;
											}
											if(minspeed<80)
											{
												minspeed=80;
											}
									}
								}
								else
								{
									minspeed=distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
								}
							}
							ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);  
							cs_pt.x=cs_pt1.x;
						    cs_pt.y=cs_pt1.y;
						}
					}
					else //cs-pt1���Ϸ��������·�
					{
						if(notcspt2==1)
						{
							if (distRobot2Pt(*robot,cs_pt1)>50)
							{
								minspeed=100;
							}
							if (distRobot2Pt(*robot,cs_pt1)<=50)
							{
								if (distE>maxe||distRobot2Pt(*robot,cs_pt1)>=10)
								{
									if (distRobot2Pt(*robot,cs_pt1)>=30)
									{
											minspeed=90;
									}
									else
									{
										minspeed=65+distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
											if (minspeed>=90)
											{
												minspeed=90;
											}
											if(minspeed<80)
											{
												minspeed=80;

											}
									}
								
								}
								else
								{
									minspeed=distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
								}
							}	
						  ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);
							cs_pt.x=cs_pt1.x;
							cs_pt.y=cs_pt1.y;

						}
						else
						{
							if (distRobot2Pt(*robot,cs_pt2)>50)
							{
								minspeed=100;
							}
							if (distRobot2Pt(*robot,cs_pt2)<=50)
							{
								if (distE>maxe||distRobot2Pt(*robot,cs_pt2)>=10)
								{
									if (distRobot2Pt(*robot,cs_pt2)>=30)
									{
											minspeed=90;
									}
									else
									{
										minspeed=65+distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
											if (minspeed>=90)
											{
												minspeed=90;
											}
											if(minspeed<80)
											{
												minspeed=80;

											}
									}
								
								}
								else
								{
									minspeed=distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
								}
							}
						
						 ToPositionPDchampionnew(robot,cs_pt2,minspeed*v_xishu,pSpeed);
							
							cs_pt.x=cs_pt2.x;
							cs_pt.y=cs_pt2.y;
						}
						
					}
					
				/*	if (ballCharacter.velocity>0.4&&down==-1&&notcspt1==0&&dist>30)
					{
						ToPositionPDchampionnew(robot,cs_pt1,minspeed,pSpeed);
							
							cs_pt.x=cs_pt1.x;
							cs_pt.y=cs_pt1.y;

					}*/
					
				}
				else//ֱ����
				{
					if(cs_pt1.y > cs_pt2.y)
					{
						if(notcspt1==1)
						{
							if (distRobot2Pt(*robot,cs_pt2)>50)
							{
								minspeed=100;
							}
							if (distRobot2Pt(*robot,cs_pt2)<=50)
							{
								if (distE>maxe||distRobot2Pt(*robot,cs_pt2)>=10)
								{
									if (distRobot2Pt(*robot,cs_pt2)>=30)
									{
											minspeed=100;
									}
									else
									{
										minspeed=65+distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
											if (minspeed>=90)
											{
												minspeed=90;
											}
											if(minspeed<80)
											{
												minspeed=80;

											}
									}
								
								}
								else
								{
								
									minspeed=distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
								}
							}
									
							ToPositionPDchampionnew(robot,cs_pt2,minspeed*v_xishu,pSpeed);
							 cs_pt.x=cs_pt2.x;
							 cs_pt.y=cs_pt2.y;
						}
						else
						{
							if (distRobot2Pt(*robot,cs_pt1)>50)
							{
								minspeed=100;
							}
							if (distRobot2Pt(*robot,cs_pt1)<=50)
							{
								if (distE>maxe||distRobot2Pt(*robot,cs_pt1)>=10)
								{
									if (distRobot2Pt(*robot,cs_pt1)>=30)
									{
											minspeed=90;
									}
									else
									{
										minspeed=65+distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
											if (minspeed>=90)
											{
												minspeed=90;
											}
											if(minspeed<80)
											{
												minspeed=80;

											}
									}
								
								}
								else
								{
								
									minspeed=distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
								}
							}							
							ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);
							cs_pt.x=cs_pt1.x;
							cs_pt.y=cs_pt1.y;
						}
						
					}
					else
					{
						if(notcspt2==1)
						{	
							ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);
							cs_pt.x=cs_pt1.x;
							cs_pt.y=cs_pt1.y;
						}
						else
						{
							if (distRobot2Pt(*robot,cs_pt2)>50)
							{
								minspeed=100;
							}
							if (distRobot2Pt(*robot,cs_pt2)<=50)
							{
								if (distE>maxe||distRobot2Pt(*robot,cs_pt2)>=10)
								{
									if (distRobot2Pt(*robot,cs_pt2)>=30)
									{
											minspeed=90;
									}
									else
									{
										minspeed=65+distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
											if (minspeed>=90)
											{
												minspeed=90;
											}
											if(minspeed<80)
											{
												minspeed=80;
											}
									}
								
								}
								else
								{
								
									minspeed=distRobot2Pt(*robot,cs_pt2)+qiusubi*ballCharacter.velocity;
								}
							}
							
							ToPositionPDchampionnew(robot,cs_pt2,minspeed*v_xishu,pSpeed);
							cs_pt.x=cs_pt2.x;
							cs_pt.y=cs_pt2.y;
						}						
					}
				/*	if (ballCharacter.velocity>0.4&&down==1&&notcspt2==0&&dist>30)
					{
						ToPositionPDchampionnew(robot,cs_pt2,minspeed,pSpeed);
							
							cs_pt.x=cs_pt2.x;
							cs_pt.y=cs_pt2.y;

					}*/
				}
			}	
		}
		//	   hold_ball(IfEndprocess,robot,ball,directionpt,80,pSpeed);	
			 //onezonehitballfyp(robot,ball,pSpeed,cs_pt); 
	}
//////////////////////////////////////////////////////////////////
	//������
	else if(dy1<0.57735*dx1||dy1<-0.57735*dx1)	
	{	////������복���Ǻܽ������ٺ�Сʱ��ִ����Χ�ܵ�
		////�����ٴ���0.6��С��������ܽ�ʱ��ִ��newquickcurve
	
	//	pSpeed->LeftValue=pSpeed->RightValue=0;
	
		if(dy1<0||distRobot2Pt(*robot,fball)>15)
		{
			//fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*yanchi+ball.x;
	        //fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*yanchi+ball.y;
			cs_circle1.x = fball.x;
			cs_circle1.y = fball.y;
	
			if (oldBallPt[6].x<oldBallPt[3].x&&oldBallPt[3].x<oldBallPt[0].x)
			{
				double ball_vx;
				double ballangle;
				ballangle=ballCharacter.angle;
				ballangle=cn_AngleTrim2PI(ballangle);
				if (ballangle>Pi)
				{
					ballangle=ballangle-2*Pi;
				}
				ballangle=fabs(ballangle);
				ballangle=Pi-ballangle;
				ball_vx=ballCharacter.velocity*cos(ballangle);
				if (ball_vx<=0.2)
				{
					cs_circle1.r=14;
				}
				if (ball_vx>0.2&&ball_vx<=0.6)
				{
					cs_circle1.r=20;
				}
				if (ball_vx>0.6&&ball_vx<=1.5)
				{
					cs_circle1.r=24;
				}
				if (ball_vx>1.5&&ball_vx<=2)
				{
					cs_circle1.r = 26;
				}
				if (ball_vx>2)
				{
					cs_circle1.r = 26;
				}
			}
		
			cn_LineCircleCross(&line_b2d,&cs_circle1,&cs_pt1,&cs_pt2);//��ֱ�ߺ�Բ�Ľ��㣬cs_pt1, cs_pt2�����������ӦҪ���صĽ��㡣���û���򷵻�-1��ֻ��һ���򷵻�0���������򷵻�1��
			//���cs-pt1
			if (cs_pt1.x>cs_pt2.x)
			{
				cs_pt3=cs_pt1;
				cs_pt1=cs_pt2;
				cs_pt2=cs_pt3;
			}
			if (distRobot2Pt(*robot,cs_pt1)>50)
			{
				minspeed=100;
			}
			if (distRobot2Pt(*robot,cs_pt1)<=50)
			{
				
					if (distRobot2Pt(*robot,cs_pt1)>=30)
					{
							minspeed=80;
					}
					else
					{
						minspeed=20+0.3*distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
						if (minspeed<=65)
						{
							minspeed=65;
						}
						if (minspeed>=80)
						{
							minspeed=80;
						}
					}
			}
			ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);	
		}
		else //�����ϰ벿���Ҿ���ܽ�
		{
			//fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*yanchi+ball.x;
	        //fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*yanchi+ball.y;
			cs_circle1.x = fball.x;
			cs_circle1.y = fball.y;
			if (oldBallPt[6].x<oldBallPt[3].x&&oldBallPt[3].x<oldBallPt[0].x)//���򼺷��ƶ�
			{
				double ball_vx;
				double ballangle;
				ballangle=ballCharacter.angle;
				ballangle=cn_AngleTrim2PI(ballangle);
				if (ballangle>Pi)
				{
					ballangle=ballangle-2*Pi;
				}
				ballangle=fabs(ballangle);
				ballangle=Pi-ballangle;
				ball_vx=ballCharacter.velocity*cos(ballangle);
				if (ball_vx<=0.2)
				{
					cs_circle1.r=11;
				}
				if (ball_vx>0.2&&ball_vx<=0.6)
				{
					cs_circle1.r=13;
				}
				if (ball_vx>0.6&&ball_vx<=1.5)
				{
					cs_circle1.r=18;
				}
				if (ball_vx>1.5&&ball_vx<=2)
				{
					cs_circle1.r = 20;
				}
				if (ball_vx>2)
				{
					cs_circle1.r = 21;
				}
			}
			cn_LineCircleCross(&line_b2d,&cs_circle1,&cs_pt1,&cs_pt2);//��ֱ�ߺ�Բ�Ľ��㣬cs_pt1, cs_pt2�����������ӦҪ���صĽ��㡣���û���򷵻�-1��ֻ��һ���򷵻�0���������򷵻�1��
			//���cs-pt1
			if (cs_pt1.x>cs_pt2.x)
			{
				cs_pt3=cs_pt1;
				cs_pt1=cs_pt2;
				cs_pt2=cs_pt3;
			}
			if (distRobot2Pt(*robot,cs_pt1)>50)
			{
				minspeed=100;
			}
			if (distRobot2Pt(*robot,cs_pt1)<=50)
			{
			
					if (distRobot2Pt(*robot,cs_pt1)>=30)
					{
							minspeed=80;
					}
					else
					{
						minspeed=20+0.3*distRobot2Pt(*robot,cs_pt1)+qiusubi*ballCharacter.velocity;
						if (minspeed<=65)
						{
							minspeed=65;
						}
						if (minspeed>=80)
						{
							minspeed=80;
						}
					}
			}
			//ToPositionPD(robot,cs_pt1,85,15+qiusubi*ballCharacter.velocity,pSpeed);	//100
			ToPositionPDchampionnew(robot,cs_pt1,minspeed*v_xishu,pSpeed);	
		}
        New_QuickCurve(robot,ball,pSpeed); 
//		    hold_ball(IfEndprocess,robot,ball,directionpt,80,pSpeed);
		New_EndProcess(1,robot,realdirectionpt,ball,pSpeed); 
	}
///////////////////////////////////////////////////////////////////////
	//������
	else
	{
		Point cs_robot;
		cs_robot.x = robot->x;
		cs_robot.y = robot->y;
        fball.x=ball.x;
		fball.y=ball.y;
		Point midpt,cs_tempt;
		LINEFORMULATION line1,line2;
		midpt.x=(cs_robot.x+ball.x)/2;
		midpt.y=(cs_robot.y+ball.y)/2;
		StdLineForm(TO_POINT(ball),cs_robot,&line1);
        cn_PointPerpendLine(midpt,&line1,&line2,&cs_tempt);
        StdLineForm(TO_POINT(ball),directionpt,&line1);
        cn_2LinesCrossPoint(&line1,&line2,&cs_tempt);
		cs_tempt.x=(cs_tempt.x+ball.x)/2;
        cs_tempt.y=(cs_tempt.y+ball.y)/2;
         
		if(ballCharacter.velocity>0.4)
		{
			if(cn_2PointsDist(fball,cs_robot)>60)
			{
				if(oldBallPt[0].x<oldBallPt[3].x&&oldBallPt[3].x<oldBallPt[6].x)
				{
					double v,d;
					d=cn_2PointsDist(fball,cs_robot);
					v=0.576*(d-60)+95;
					if(v>=120)
					{
						v=120;
					}
					ToPositionPDlimit(robot,cs_tempt,v*v_xishu,(20+qiusubi*ballCharacter.velocity)*v_xishu,pSpeed);
				}
				else
					ToPositionPDlimit(robot,cs_tempt,88*v_xishu,(20+qiusubi*ballCharacter.velocity)*v_xishu,pSpeed);
			}
			else
			{
				if(hitwall==1)
				{
                     hitwallCS_CurveShoot(IfEndprocess,robot,ball,fball,directionpt,realdirectionpt,pSpeed,hitwall);
				}
				else
				{
                     CS_CurveShootfball(IfEndprocess,robot,ball,fball,directionpt,pSpeed,hitwall);
				}				
			}
		}
        else
		{
            if(cn_2PointsDist(fball,cs_robot)>60)
			{
				if(oldBallPt[0].x<oldBallPt[3].x&&oldBallPt[3].x<oldBallPt[6].x)
				{
					double v,d;
					d=cn_2PointsDist(fball,cs_robot);
					v=0.576*(d-60)+95;
					if(v>=120)
					{
						v=120;
					}
					ToPositionPDlimit(robot,cs_tempt,v*v_xishu,(20+qiusubi*ballCharacter.velocity)*v_xishu,pSpeed);
				}
				else
					ToPositionPDlimit(robot,cs_tempt,88*v_xishu,(20+qiusubi*ballCharacter.velocity)*v_xishu,pSpeed);
			}
			else
			{
				if(hitwall==1)
				{
                     hitwallCS_CurveShoot(IfEndprocess,robot,ball,fball,directionpt,realdirectionpt,pSpeed,hitwall);
				}
				else
				{
                     CS_CurveShootfball(IfEndprocess,robot,ball,fball,directionpt,pSpeed,hitwall);
				}				
			}
		}
	}
	return 1;
}



	int Vect_MidShoot1(RobotPose pRobotInford, BallPoint &ball,Velocity *pSpeed)
	{	
		Point	goal,ballPt;//
		static int k=0;
		static int hitwalltime=0;
		double delta,angletemp;
		delta = 10;
		ballPt = TO_POINT(ball);
		
		
		goal.x = 223;
		goal.y = 95;
		
		if(ball.x>185)
			k=1;
		else
			k=k+1;
		if(k>50||ball.x<=185)
			k=0;
		if(k==1)
			choosebestpt(pRobotInford, ball, &goal);
		
		angletemp = Getpt2ptAngle(ballPt,goal);
		double deltax;
		deltax = 10;
		
		for(int t=1;t<=5;t++)
		{
			
			if(distRobot2Pt(opp_robot_point[t],TO_BALL(ballPt))<9 && oldBallPt[0].x>oldBallPt[3].x &&
				oldBallPt[3].x>oldBallPt[6].x&& ballCharacter.velocity>1.5)
			{
				ToCatchBall(&pRobotInford,TO_BALL(ballPt),1,pSpeed);
				break;
			}
			else
				CS_ToPositionNewfyp(&pRobotInford,TO_BALL(ballPt),goal,2,pSpeed);	
	}
	
	
	if(EndProcessFlag==0 && pRobotInford.x>185 && distRobot2Pt(pRobotInford,ballPt)<5 && pRobotInford.x<ball.x)//decisiondata[0][0]
	{
		if(ball.y<90 && ball.y>72)
		{
			if(ball.y>pRobotInford.y)
			{
				pSpeed->LeftValue = 70;
				pSpeed->RightValue = -70;
			}
			else
			{
				pSpeed->LeftValue = -70;
				pSpeed->RightValue = 70;
			}
		}
		else if(ball.y>90 && ball.y<108)
		{
			if(ball.y<pRobotInford.y)
			{
				pSpeed->LeftValue = -70;
				pSpeed->RightValue = 70;
			}
			else
			{
				pSpeed->LeftValue = 70;
				pSpeed->RightValue = -70;
			}
		}
		else
		{
			if(ball.y<90)
			{
				pSpeed->LeftValue = -70;
				pSpeed->RightValue = 70;
			}
			else if(ball.y>90)
			{
				pSpeed->LeftValue = 70;
				pSpeed->RightValue = -70;
			}
		}
	}	
	
	return 1;
	}
	int GetWarInformation(ROSrect rect, Point *car, int &num, bool kind)
	{
		Point oppcar[12],mycar[12],testcar[12];
		double a,b,c,d;
		
		for(int i=1 ;i<6;i++)
		{
			oppcar[i].x = 0.0;
			oppcar[i].y = 0.0;
			mycar[i].x = 0.0;
			mycar[i].y = 0.0;
			testcar[i].x = my_robot_pose[i].x;
			testcar[i].y = my_robot_pose[i].y;
			a = rect.left;
			b = rect.bottom;
			c = rect.right;
			d = rect.top;
			
		}
		
		num =1;
		
		for(int i=1;i<6;i++)
		{
			if(!kind)//false
			{
				if(opp_robot_point[i].x > rect.left && opp_robot_point[i].y > rect.bottom && 
					opp_robot_point[i].x < rect.right && opp_robot_point[i].y < rect.top)
				{
					oppcar[num].x = opp_robot_point[i].x;
					oppcar[num].y = opp_robot_point[i].y;
					num++;
				}
			}
			else
			{
				if(my_robot_pose[i].x > rect.left && my_robot_pose[i].y > rect.bottom &&
					my_robot_pose[i].x < rect.right && my_robot_pose[i].y < rect.top)
				{
					mycar[num].x = my_robot_pose[i].x;
					mycar[num].y = my_robot_pose[i].y;
					num++;
				}
			}
		}
		num--;
		
		for(int i=1;i<=num;i++)
		{
			Point tempcar;
			tempcar.x =0.0;
			tempcar.y =0.0;
			int j=0;
			if(!kind)//�Է���
			{
				for(j=2;j<= num;j++)
				{
					if(oppcar[j].x < oppcar[i].x)
					{
						tempcar.x = oppcar[i].x;
						tempcar.y = oppcar[i].y;
						
						oppcar[i].x = oppcar[j].x;
						oppcar[i].y = oppcar[j].y;
						
						oppcar[j].x = tempcar.x;
						oppcar[j].y = tempcar.y;
					}
				}
			}
			else
			{
				for(j =2;j<= num;j++)
				{
					if(mycar[j].x < mycar[i].x)
					{
						tempcar.x = mycar[i].x;
						tempcar.y = mycar[i].y;
						
						mycar[i].x = mycar[j].x;
						mycar[i].y = mycar[i].y;
						
						mycar[j].x = tempcar.x;
						mycar[j].y = tempcar.y;	
					}
				}
			}	
		}
		if(!car)
			return num;
		else
		{
			if(kind)
			{
				for(int i =1;i<=num;i++)
				{
					car[i].x = mycar[i].x;
					car[i].y = mycar[i].y;
				}
			}
			else
			{
				for(int i = 1;i<num;i++)
				{
					car[i].x = oppcar[i].x;
					car[i].y = oppcar[i].y;
				}
			}
			return num;
		}
	}

	
	int New_EndProcess(int i,RobotPose *pRobot, Point shoot_target, BallPoint ballPt,Velocity *pSpeed)
	{
		double s_speed=120*End_vxishu;
		static int time = 0;
		static int endtimes=10;
		double weitiaoyuliang;
		weitiaoyuliang=0.017;//0.018
		int vxup=80;
		double	r,dist,distE,anglerb2ball,anglerb2target,angle1,angle2,angle3,angleball2target,maxe,maxd,maxspeed;
		Point rbPt,EGoal;
		BallPoint ball = ballPt;
		maxspeed = 180*End_vxishu;//180
		EGoal.x = wallright + 3;
		EGoal.y = walltop/2;
		
		maxd = 10;//10;//10;// 12
		maxe = 3;//3;	//2.8;3.2
		//	if(Flag_run == 1)//���⴦��
		//		maxd = 50;
		r = 3.7;
		dist = distRobot2Pt(*pRobot,ballPt);
		rbPt.x = pRobot->x;
		rbPt.y = pRobot->y;
		anglerb2ball = Getpt2ptAngle(rbPt,ballPt);
		anglerb2target = Getpt2ptAngle(rbPt,EGoal);
		angleball2target = Getpt2ptAngle(ballPt,shoot_target);
		
		angle1 = cal_AngleTrim2PI(anglerb2ball - anglerb2target);
		
		if(angle1>Pi)
			angle1 =angle1 - 2*Pi;
		
		angle2 = cal_AngleTrim2PI(pRobot->theta);
		angle3 = cal_AngleTrim2PI(angle2 - anglerb2ball);
		
		EndProcessFlag = 0;
		
		distE = fabs(dist*sin(angle3));


		if((i>0 && dist<=maxd && distE<=maxe)||(endtimes<10))//&&i>0
		{
			double anglelimit,anglet1,anglet2,anglet3,kk;
			

			kk=1.00;
			anglelimit = (150-pRobot->x )/150*Pi*.15 + Pi*.2+time*0.006*Pi;
			if(anglelimit>Pi*0.4)
				anglelimit = Pi*0.4;

			Point pt1,pt2;
			pt1.x = pt2.x = wallright;
			
			if(OpponentGoalKeeper.y!=0)
			{
				if(OpponentGoalKeeper.y>90)
				{
					pt1.y = CENTER_Y;
					pt2.y = CENTER_Y-20;
				}
				else
				{
					pt1.y = CENTER_Y+20;
					pt2.y = CENTER_Y;
				}
			}
			else
			{
				pt1.y = CENTER_Y+20;
				pt2.y = CENTER_Y-20;
			}

			double anglexishu;
			if(time==0)
			{
				endprocessV=fabs(qiusubi*BallPredictCharacter.velocity);
				endprocessrobot.x=pRobot->x;
				endprocessrobot.y=pRobot->y;
			}
			if (cal_2PointsDist(shoot_target,endprocessrobot)>110)
			{
				anglexishuA=0.000871;//0.0017;
				anglexishuC=0.75;//0.6465;0.772
			}
			else
			{
				anglexishuA=0.000871;//0.0017;
				anglexishuC=0.77;//0.6465;0.772
			}

			anglexishu=(anglexishuA*cal_2PointsDist(shoot_target,endprocessrobot)+anglexishuC)-weitiaoyuliang;

			if(anglexishu>=1)
			{
				anglexishu=1;
			}
			if(angle3<Pi*0.2&&angle3>=0||angle3>Pi*1.8&&angle3<2*Pi)
			{
				if(time<timelimit)
					time++;
				double anglek;
				anglek = cn_AngleTrim2PI(pRobot->theta - anglerb2target);
				anglet1 = cn_AngleTrim2PI(pRobot->theta - Getpt2ptAngle(rbPt,pt1));
				if(anglet1>Pi)//(-Pi~Pi)
					anglet1 -=2*Pi;
				anglet2 = cn_AngleTrim2PI(pRobot->theta - Getpt2ptAngle(rbPt,pt2));
				if(anglet2>Pi)//(-Pi~Pi)
					anglet2 -=2*Pi;
				if(fabs(anglet1)>fabs(anglet2))
					anglet3 = fabs(anglet2);
				else
					anglet3 = fabs(anglet1);
				
				if(anglek>Pi)//(-Pi~Pi)
					anglek -=2*Pi;
				
				if(anglet3<anglelimit||anglet1*anglet2<0)
				{
					if(anglek>0)//�ҹգ�
					{
						if(anglek<Pi/2)
						{
							if (endprocessV>50*End_vxishu)
							{
								pSpeed->LeftValue =(90.0/timelimit)*time+endprocessV;
							}
							else
								pSpeed->LeftValue =(90.0/timelimit)*time+50*End_vxishu;//endprocessV;//
							if(pSpeed->LeftValue>s_speed)
								pSpeed->LeftValue=s_speed;
						}
						else
						{
							pSpeed->LeftValue = 100;
						}

						pSpeed->RightValue = pSpeed->LeftValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
						if(pSpeed->RightValue < pSpeed->LeftValue*anglexishu)
						{
							pSpeed->RightValue=pSpeed->LeftValue*anglexishu;
						}

						//if((endprocessrobot.x>=185&&endprocessrobot.y>=50&&endprocessrobot.y<=130)||anglek>=Pi/2)
						if(fabs(pSpeed->LeftValue-pSpeed->RightValue)/2>(vx+vxup)/((fabs(pSpeed->LeftValue)+fabs(pSpeed->RightValue))/2))
						{
							pSpeed->RightValue = sqrt(pSpeed->LeftValue*pSpeed->LeftValue-4*(vx+vxup));
						}
						if(ball.x>=175&&ball.y>40&&ball.y<140)
						{
							pSpeed->RightValue = pSpeed->LeftValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
						}
					}

					else 
					{
						if(anglek>-Pi/2)
							//if(anglek<Pi/2)
						{	
							if (endprocessV>50*End_vxishu)
							{
								pSpeed->RightValue =(90.0/timelimit)*time+endprocessV;
							}
							else
								pSpeed->RightValue =(90.0/timelimit)*time+50*End_vxishu;
							if(pSpeed->RightValue>s_speed)
								pSpeed->RightValue=s_speed;
						}
						else
						{
							pSpeed->RightValue = 100;
						}

						pSpeed->LeftValue = pSpeed->RightValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
						if(pSpeed->LeftValue<pSpeed->RightValue*anglexishu)
						{
							pSpeed->LeftValue=pSpeed->RightValue*anglexishu;
						}
						//if((endprocessrobot.x>=185&&endprocessrobot.y>=50&&endprocessrobot.y<=130)||anglek<=-Pi/2)
						if(fabs(pSpeed->RightValue-pSpeed->LeftValue)/2>(vx+vxup)/((fabs(pSpeed->LeftValue)+fabs(pSpeed->RightValue))/2))
						{
							pSpeed->LeftValue = sqrt(pSpeed->RightValue*pSpeed->RightValue-4*(vx+vxup));
						}
						if(ball.x>=175&&ball.y>40&&ball.y<140)
						{
							pSpeed->LeftValue = pSpeed->RightValue*(Pi/2-kk*fabs(anglek))/(Pi/2);
						}	 
					}
					EndProcessFlag = 1;
				}
			}
			
			else if(angle3>0.8*Pi&&angle3<1.2*Pi)//&&i>0
			{
				
				if(time<timelimit)
					time++;
				double anglek;
				anglek = cn_AngleTrim2PI(pRobot->theta - anglerb2target+Pi);
				//xue
				anglet1 = cn_AngleTrim2PI(pRobot->theta - Getpt2ptAngle(rbPt,pt1)+Pi);
				if(anglet1>Pi)
					anglet1 -=2*Pi;
				anglet2 = cn_AngleTrim2PI(pRobot->theta - Getpt2ptAngle(rbPt,pt2)+Pi);
				if(anglet2>Pi)
					anglet2 -=2*Pi;
				if(fabs(anglet1)>fabs(anglet2))
					anglet3 = fabs(anglet2);
				else
					anglet3 = fabs(anglet1);	
				if(anglek>Pi)
					anglek -=2*Pi;
				if(anglet3<anglelimit||(anglet1*anglet2<0))
				{
					if(anglek>0)
					{
						if(anglek<Pi/2)
						{
							if (endprocessV>50*End_vxishu)
							{
								pSpeed->RightValue =(90.0/timelimit)*time+endprocessV;
							}
							else
								pSpeed->RightValue =(90.0/timelimit)*time+50*End_vxishu;
							if(pSpeed->RightValue>s_speed)
								pSpeed->RightValue=s_speed;
						}
						else
						{
							pSpeed->RightValue = 100;//+time*0.6;
						}
			
						pSpeed->RightValue = -pSpeed->RightValue;
						pSpeed->LeftValue = pSpeed->RightValue*(Pi/2-kk*fabs(anglek))/(Pi/2);
						if(fabs(pSpeed->LeftValue)<fabs(pSpeed->RightValue)*anglexishu)
						{
							pSpeed->LeftValue=pSpeed->RightValue*anglexishu;
						}
						//if((endprocessrobot.x>=185&&endprocessrobot.y>=50&&endprocessrobot.y<=130)||anglek>=Pi/2)
						
						if(fabs((pSpeed->RightValue*pSpeed->RightValue) - (pSpeed->LeftValue*pSpeed->LeftValue)) > 4*(vx+vxup))
						{
							pSpeed->LeftValue = -sqrt(pSpeed->RightValue*pSpeed->RightValue-4*(vx+vxup));
						}
						if(ball.x>=175&&ball.y>40&&ball.y<140)
						{
							pSpeed->LeftValue = pSpeed->RightValue*(Pi/2-kk*fabs(anglek))/(Pi/2);	
						}	
					}
					else
					{
						if(anglek>-Pi/2)
							//if(anglek<Pi/2)
						{
							if (endprocessV>50*End_vxishu)
							{
								pSpeed->LeftValue =(90.0/timelimit)*time+endprocessV;
							}
							else
								pSpeed->LeftValue =(90.0/timelimit)*time+50*End_vxishu;
							if(pSpeed->LeftValue>s_speed)
								pSpeed->LeftValue=s_speed;
						}
						
						else
						{
							pSpeed->LeftValue = 100;
						}

						pSpeed->LeftValue = -pSpeed->LeftValue;
						pSpeed->RightValue = pSpeed->LeftValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
						if(fabs(pSpeed->RightValue)<fabs(pSpeed->LeftValue)*anglexishu)
						{
							pSpeed->RightValue= pSpeed->LeftValue*anglexishu;
						}
						//if((endprocessrobot.x>=185&&endprocessrobot.y>=50&&endprocessrobot.y<=130)||anglek<=-Pi/2)
						if(fabs((pSpeed->RightValue*pSpeed->RightValue) - (pSpeed->LeftValue*pSpeed->LeftValue)) > 4*(vx+vxup))
						{
							pSpeed->RightValue = -sqrt(pSpeed->LeftValue*pSpeed->LeftValue-4*(vx+vxup));
						}
						if(ball.x>=175&&ball.y>40&&ball.y<140)
						{
							pSpeed->RightValue = pSpeed->LeftValue*(Pi/2-kk*fabs(anglek))/(Pi/2);//*fabs(cos(anglek))*kk;
							
						}
					}
					EndProcessFlag = 1;	
				}
			}
			if(i>0 && dist<=maxd && distE<=maxe)
				endtimes=0;
			if(endtimes<10) endtimes++;
			
		}
		/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////
		else
		{	       
			if(endtimes==10)
				time=0;	 
		}	
		
		
		if((angle3<Pi*0.2 && angle3>=0||angle3>Pi*1.8 && angle3<2*Pi) && fabs(angle1)<Pi*0.45 && distE<=maxe &&
			dist<=maxd && (angle2>=0 && angle2<=Pi*0.45||angle2>=Pi*1.55 && angle2<=2*Pi))
		{
			double temp;
			temp = pRobot->y+(wallright-pRobot->x)*tan(angle2);
			
			if(OpponentGoalKeeper.y!=0)
			{
				if((OpponentGoalKeeper.y>90&&temp>=70.0+4.0&&temp<=OpponentGoalKeeper.y-8)||(OpponentGoalKeeper.y<=90 && temp>=OpponentGoalKeeper.y+8&&temp<=110.0-4.0))
				{
					if(ball.x>150)
						pSpeed->LeftValue = pSpeed->RightValue = maxspeed;
					else
					{
						//pSpeed->LeftValue = pSpeed->RightValue = 180-(150-ball.x)*0.6;
						pSpeed->LeftValue = pSpeed->RightValue = 180-(150-ball.x)*0.5;
					}
					EndProcessFlag = 1;	
				}
			}
			else
			{
				if(temp>=74&&temp<=106)
				{
					pSpeed->LeftValue = pSpeed->RightValue = maxspeed;
					EndProcessFlag = 1;	
				}             
			}
		}
		
		else if((angle3>Pi - Pi*0.2&&angle3<Pi+Pi*0.2)&&fabs(angle1)<Pi*0.45&&distE<=maxe&& dist<=maxd &&
			(angle2>=0.55*Pi&&angle2<=Pi*1.45))
		{
			double temp;
			temp = pRobot->y+(wallright-pRobot->x)*tan(angle2);
			if(OpponentGoalKeeper.y!=0)
			{
				if((OpponentGoalKeeper.y>90 && temp>=70.0+4.0&&temp<=OpponentGoalKeeper.y-8)||
					(OpponentGoalKeeper.y<=90 && temp>=OpponentGoalKeeper.y+8&&temp<=110.0-4.0))
				{
					if(ball.x>150)
						pSpeed->LeftValue = pSpeed->RightValue = -maxspeed;
					else
					{
						//pSpeed->LeftValue = pSpeed->RightValue = -(180 - (150-ball.x)*0.6);
						pSpeed->LeftValue = pSpeed->RightValue = -(180 - (150-ball.x)*0.5);
						
					}
					EndProcessFlag = 1;	
				}	
			}
			else
			{
				if(temp>=74 && temp<=106)
				{
					pSpeed->LeftValue = pSpeed->RightValue = -maxspeed;
					EndProcessFlag = 1;	
				}             
			}
		}
		return 1;
	}
	double cn_2PointsDist(Point A, Point B)
	{
	return sqrt((double(B.y)-double(A.y))*(double(B.y)-double(A.y)) + (double(B.x)-double(A.x))*(double(B.x)-double(A.x)));
	}
	/************************************************/
    /********************综合运动********************/
    
	
	
	//本函数用于比赛过程中根据队形确定的小车运动执行
    /*void charInterpret(int robotNo, int charNo, Velocity *rbV)//robotNo-小车车号,charNo-角色号,rbV-对应小车车号的左右轮速
    {
	    switch (charNo)
	    {
	    case 1://前锋
		    {   
			    Point shootGoal;
			    Point shootPoint;
			    
			    shootGoal.x = 220.0;
			    shootGoal.y = 90.0;
			    
			    double shootDist;
			    

		        if (ball_point.x>110 && ball_point.x<205 && ball_point.y>15 && ball_point.y<165)//一定区域内触发
			    {
			        double dx1,dy1,angle1;
			        dx1 = shootGoal.x-ball_point.x;
			        dy1 = shootGoal.y-ball_point.y;
			        angle1 = atan2(dy1,dx1);
			        angle1 = cn_AngleTrim2PI(angle1);
			        double dx2,dy2,angle2;
			        dx2 = my_robot_pose[robotNo].x-ball_point.x;
			        dy2 = my_robot_pose[robotNo].y-ball_point.y;
			        angle2 = atan2(dy2,dx2);
			        angle2 = cn_AngleTrim2PI(angle2);
			        double Angle;
			        Angle = angle2-angle1;
			        Angle = cn_AngleTrim2PI(Angle);
			        double Theta;
			        Theta = Pi - Angle;
			        
			        Point ball_point;
			        ball_point.x = ball_point.x;
			        ball_point.y = ball_point.y;
			        
			        if (cos(Theta) == 0)
			        {
		                shootDist = 0;
			        }
			        else
			        {
			            shootDist = fabs((distRobot2Pt(my_robot_pose[robotNo], ball_point) / 2) / cos(Theta));
			        }
			        
			        shootPoint.x = ball_point.x-shootDist*cos(angle1);
			        shootPoint.y = ball_point.y-shootDist*sin(angle1);
			        
			        if (shootPoint.x < 5)
		            {
		                shootPoint.x = 5;
		            }
		            if (shootPoint.x > 215)
		            {
		                shootPoint.x = 215;
		            }
		            if (shootPoint.y < 5)
		            {
		                shootPoint.y = 5;
		            }
		            if (shootPoint.y > 175)
		            {
		                shootPoint.y = 175;
		            }
			        
			        ToPositionN(&my_robot_pose[robotNo], shootPoint, 50, rbV); //60
			        //ToPositionPD(&my_robot_pose[robotNo],shootPoint, 30, 30, rbV);
			        if (ball_point.x > 205)
	                {
	                    rbV->LeftValue = 0;
		                rbV->RightValue = 0;
	                }
			    }
			    else
			    {
			        rbV->LeftValue = 0;
		            rbV->RightValue = 0;
		            
		            //ToPositionN(&my_robot_pose[robotNo], ball_point, 60, 30, rbV);
			    }
		        
		    
		    }
		    break;
		case 2://中锋
		    {
                rbV->LeftValue = 0;
			    rbV->RightValue = 0;
		    }
		    break;
		case 3://左后卫
		    {
			    rbV->LeftValue = 0;
			    rbV->RightValue = 0;
		    }
		    break;
		case 4://右后卫
		    {
			    rbV->LeftValue = 0;
			    rbV->RightValue = 0;
		    }
		    break;
		case 5://守门员
		    {
			    rbV->LeftValue = 0;
			    rbV->RightValue = 0;
		    }
		    break;
		default:
		    {
			    rbV->LeftValue = 0;
			    rbV->RightValue = 0;
		    }
		    break;
	    }
	    
	    return;
    }*/
	int position (RobotPose *pRobot,Point Target,Velocity *pSpeed)
{
	int kind=0;
	Point pt;
	pt.x=pRobot->x;
	pt.y=pRobot->y;
	
	if(pRobot->y > pRobot[5].y)
	{	
		kind=1;
		pt.y=pt.y+8;
	}
	else
	{ 
		kind=2;
		pt.y=pt.y-8;
	}
	
	Point car5,cari;
	car5.x=pRobot[5].x;	car5.y=pRobot[5].y;
	cari.x=pRobot->x;	cari.y=pRobot->y;
	
	if(distRobot2Pt(*pRobot,pt)>3 && cn_2PointsDist(car5,cari)<20)
		ToPositionN(pRobot,pt,50,pSpeed);
	else
		ToPositionN(pRobot,Target,50,pSpeed);
	return 1;
}
int ToPositionPDGoal(RobotPose* pROBOTPOSTURE,Point Target,double startspeed,double endspeed,Velocity* pLRWheelVelocity)
{
	int clock_sign,move_sign;
	double theta,theta_e1;
	static double theta_e2 = 0;
	double dx,dy,dx1,dy1,distance;
	double same_speed;
	
	dx1 = Target.x - pROBOTPOSTURE->x;
	dy1 = Target.y - pROBOTPOSTURE->y;
	dx = dx1*cos(pROBOTPOSTURE->theta - Pi/2) + dy1*sin(pROBOTPOSTURE->theta - Pi/2);
	dy = -dx1*sin(pROBOTPOSTURE->theta - Pi/2) + dy1*cos(pROBOTPOSTURE->theta - Pi/2);
	distance = sqrt(dx*dx + dy*dy);
	theta = atan2(dy,dx);
	
	if(distance > m_MoveParameter.max_distanceG)//m_MoveParameter.max_distanceG = 25.0
		same_speed = startspeed;
	else
		same_speed =  distance/m_MoveParameter.max_distanceG*startspeed;
	if(same_speed < endspeed) 
		same_speed = endspeed;
	
	if(fabs(fabs(theta) - Pi/2) > m_AngleParameter.MaxAngle)//m_AngleParameter.MaxAngle = 75.0*Pi/180.0;
	{
		TurnToPointPD(pROBOTPOSTURE,Target,NOCLOCK,pLRWheelVelocity);
		pLRWheelVelocity->LeftValue /= 3;
		pLRWheelVelocity->RightValue /= 3;
		return 0;
	}
	
	theta = cn_AngleTrim2PI(theta);
	if(theta <= Pi/2)
	{
		move_sign = 1;
		clock_sign = 1;
		theta_e1 = Pi/2 - theta;
	}
	else if(theta <= Pi)
	{
		move_sign = 1;
		clock_sign = -1;
		theta_e1 = theta - Pi/2;
	}
	else if(theta <= 3*Pi/2)
	{
		move_sign = -1;
		clock_sign = 1;
		theta_e1 = 3*Pi/2 - theta;
	}
	else
	{
		move_sign = -1;
		clock_sign = -1;
		theta_e1 = theta - 3*Pi/2;
	}
	
	//	if(theta_e1 > 20.0/180.0*Pi)
	same_speed = same_speed*(1-theta_e1/(Pi/2));
	double kp,kd;
	kp = m_MoveParameter.kp4pospdG;
	kd = m_MoveParameter.kd4pospdG;
	if(distance < 20 && fabs(theta_e1) < Pi/6)
	{
		kp *= 0.3;
		kd *= 0.3;
	}
	pLRWheelVelocity->LeftValue = same_speed*move_sign + clock_sign*(kp*theta_e1);
	pLRWheelVelocity->RightValue = same_speed*move_sign - clock_sign*(kp*theta_e1);
	
	
	theta_e2 = theta_e1;
	return 0;
}
    /************************************************/
    /********************组合运动********************/
    
    /************************************************/
    /********************运动基元********************/
    //本函数用于使小车到达指定点
    void ToPositionN(RobotPose* robot, Point directionpt, double samespeed, Velocity* pSpeed,double samespeed_end=5)
    {
        //--------------------------------------------------------
        if (samespeed >= 90)
	    {
		    samespeed=90;
	    }
	    if (samespeed_end >= 90)
	    {
		    samespeed=90;
	    }
        //--------------------------------------------------------
	    int vemax;
	    vemax = 110;
	    
	    double Dx,Dy;
	    double Anglerb2target;
	    
	    //坐标系变换
	    robot->y = 180.0 - robot->y;
	    robot->theta = 2*Pi - robot->theta;
	    directionpt.y =180.0 - directionpt.y;
	    robot->theta = cn_AngleTrim2PI(robot->theta);

	    Dx = directionpt.x - robot->x;
	    Dy = directionpt.y - robot->y;

	    if(distRobot2Pt(*robot,directionpt)<30)
		    samespeed = 32*distRobot2Pt(*robot,directionpt)/30 + samespeed_end;
		    //samespeed = samespeed*distRobot2Pt(*robot,directionpt)/20;

	    double kp4new;
	    kp4new = 11.0;  // 角度偏差到速度差的转换系数，值越大转向越灵敏

	    //计算targetpt<robotpt>到directionpt的角度
	    Anglerb2target = atan2(Dy ,Dx);
	    Anglerb2target = cn_AngleTrim2PI(Anglerb2target);

	    //计算下一帧的目标角度
	    double disiredAngle;
	    disiredAngle = Anglerb2target;
	    disiredAngle = cn_AngleTrim2PI(disiredAngle);
	    
	    //计算角度偏差<需要转动的角度>
	    double Angle_e;
	    Angle_e = disiredAngle - robot->theta;
	    Angle_e = cn_AngleTrim2PI(Angle_e);
	    
	    //计算左右轮速度差并计算出左右轮速度
	    double ka,limitation,a;
	    a = Pi*0.4;//72度
	    limitation = 100;
	    ka=samespeed;
	    double speed_e;
	    if(Angle_e <= Pi/2)//角度偏差在第一象限
	    {
		    speed_e = kp4new*Angle_e;
		    speed_e = Limit(speed_e,limitation);
		    if(a-fabs(Angle_e)>0)
			    samespeed = ka*(a-fabs(Angle_e))/a;
		    else samespeed = 0;
		    
		    pSpeed->LeftValue = samespeed + speed_e/2;
		    pSpeed->RightValue = samespeed - speed_e/2;
	    }
	    else if(Angle_e <= Pi)//角度偏差在第二象限
	    {
		    speed_e = kp4new*(Pi - Angle_e);
		    speed_e = Limit(speed_e,limitation);
		    if(a-fabs(Pi-Angle_e)>0)
			    samespeed = ka*(a-fabs(Pi-Angle_e))/a;
		    else samespeed = 0;

		    pSpeed->LeftValue = samespeed + speed_e/2;
		    pSpeed->RightValue = samespeed - speed_e/2;
		    pSpeed->LeftValue =- pSpeed->LeftValue;
		    pSpeed->RightValue =- pSpeed->RightValue;
	    }
	    else if(Angle_e<3*Pi/2)//角度偏差在第三象限
	    {
		    speed_e = kp4new*(Angle_e - Pi);
		    speed_e = Limit(speed_e,limitation);
		    if(a-fabs(Angle_e - Pi)>0)
			    samespeed = ka*(a-fabs(Angle_e - Pi))/a;
		    else samespeed = 0;

		    pSpeed->LeftValue = samespeed - speed_e/2;
		    pSpeed->RightValue = samespeed + speed_e/2;
		    pSpeed->LeftValue =- pSpeed->LeftValue;
		    pSpeed->RightValue =- pSpeed->RightValue;
	    }
	    else//角度偏差在第四象限
	    {
		    speed_e = kp4new*(2*Pi - Angle_e);
		    speed_e = Limit(speed_e,limitation);
		    if(a-fabs(2*Pi - Angle_e)>0)
			    samespeed = ka*(a-fabs(2*Pi - Angle_e))/a;
		    else samespeed = 0;

		    pSpeed->LeftValue = samespeed - speed_e/2;
		    pSpeed->RightValue = samespeed + speed_e/2;
	    }
	    
	    if(pSpeed->LeftValue>vemax)
	    {
		    pSpeed->LeftValue = vemax;
		    pSpeed->RightValue = pSpeed->LeftValue - fabs(speed_e);
	    }
	    if(pSpeed->RightValue>vemax)
	    {
		    pSpeed->RightValue = vemax;
		    pSpeed->LeftValue = pSpeed->RightValue - fabs(speed_e);
	    }
	    if(pSpeed->LeftValue<-vemax)
	    {
		    pSpeed->LeftValue = -vemax;
		    pSpeed->RightValue = pSpeed->LeftValue + fabs(speed_e);
	    }
	    if(pSpeed->RightValue<-vemax)
	    {
		    pSpeed->RightValue = -vemax;
		    pSpeed->LeftValue = pSpeed->RightValue + fabs(speed_e);
	    }
	    
	    //变回原坐标
	    robot->y = 180.0 - robot->y;
	    robot->theta = 2*Pi - robot->theta;
	    directionpt.y = 180.0 - directionpt.y;
	    robot->theta = cn_AngleTrim2PI(robot->theta);
	    
	    return;
    }
    
    int AvoidSelfRobots(RobotPose *robot, const BallPoint &directionpt, double samespeed, Velocity *pSpeed)
    {
        Point target(directionpt.x, directionpt.y);
        return AvoidSelfRobots(robot, target, samespeed, pSpeed);
    }
	int ToPositionPD(RobotPose* pROBOTPOSTURE,Point Target,double same_speed,double end_speed,Velocity* pLRWheelVelocity)
    {
        if (same_speed > 120)	//70
            same_speed = 120;

        //vBase 是使小车到达定点时保持一定的速度
        int clock_sign,move_sign;
        double theta,theta_e1;			//e1为当前角度误差
        //static double theta_e2 = 0;		//e2为上一周期角度误差
        double dx,dy,dx1,dy1,distance;
        double speed;

        //坐标变换，以小车中心为原点，小车朝向为y轴   （原理：矩阵的旋转变换）
        dx1=Target.x-pROBOTPOSTURE->x;
        dy1=Target.y-pROBOTPOSTURE->y;
        dx=dx1*cos(pROBOTPOSTURE->theta-Pi/2)+dy1*sin(pROBOTPOSTURE->theta-Pi/2);
        dy=-dx1*sin(pROBOTPOSTURE->theta-Pi/2)+dy1*cos(pROBOTPOSTURE->theta-Pi/2);
        theta=atan2(dy,dx);				//目标点的方向角（-Pi~Pi）
        distance = sqrt(dx*dx+dy*dy);

        /////////速度调节
        //远程高速
        //为了使到定点时保持一定的速度,用增大距离的方法
        if(end_speed>same_speed)
            end_speed=same_speed;
        if(distance > m_MoveParameter.max_distance)	//75.0*Pi/180.0  m_MoveParameter.max_distance=40
            speed = same_speed;
        else //近程线性减速
            speed = distance/m_MoveParameter.max_distance*same_speed;
        if(speed < end_speed) //低速不低
            speed = end_speed;
        /////////////////////////////////////

        if(distance>25)
        {
            if(fabs(fabs(theta)-Pi/2)<0.15*Pi)
            {
                theta = cn_AngleTrim2PI(theta);
                if(theta <= Pi/2)//第一象限
                {
                    move_sign = 1;
                    clock_sign = 1;
                    theta_e1 = Pi/2 - theta;
                }
                else if(theta <= Pi)//第二象限
                {
                    move_sign = 1;
                    clock_sign = -1;
                    theta_e1 = theta - Pi/2;
                }
                else if(theta <= 3*Pi/2)//第三象限
                {
                    move_sign = -1;
                    clock_sign = 1;
                    theta_e1 = 3*Pi/2 - theta;
                }
                else//第四象限
                {
                    move_sign = -1;
                    clock_sign = -1;
                    theta_e1 = theta - 3*Pi/2;
                }

                pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1);//m_MoveParameter.kp4pospd=12
                pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1);
                //保存本周期角度误差，下一周期作微分用
                //theta_e2=theta_e1;//直接赋值可能调用会出错，会用到其他车号的数据
            }

            else//>0.15*Pi
            {
                double sp=45;
                double angle_e=fabs(fabs(theta)-Pi/2);
                double r=30/angle_e;//为什么这么赋值???
                double d=7.5;
                theta = cn_AngleTrim2PI(theta-Pi/2);
                if(theta<Pi/2)//第一项限
                {
                    pLRWheelVelocity->LeftValue = sp*(r-d/2)/r;
                    pLRWheelVelocity->RightValue = sp*(r+d/2)/r;
                }
                else if(theta<Pi)//第二项限
                {
                    pLRWheelVelocity->LeftValue = -sp*(r-d/2)/r;
                    pLRWheelVelocity->RightValue = -sp*(r+d/2)/r;
                }
                else if(theta<Pi*1.5)//第三项限
                {
                    pLRWheelVelocity->LeftValue = -sp*(r+d/2)/r;
                    pLRWheelVelocity->RightValue = -sp*(r-d/2)/r;
                }
                else//第四项限
                {
                    pLRWheelVelocity->LeftValue = sp*(r+d/2)/r;
                    pLRWheelVelocity->RightValue = sp*(r-d/2)/r;
                }
            }
        }

        else//distance<=25
        {
            if(fabs(fabs(theta)-Pi/2)>m_AngleParameter.MaxAngle)  //m_AngleParameter.MaxAngle = 75.0*Pi/180.0;
            {
                TurnToPointPD(pROBOTPOSTURE,Target,NOCLOCK,pLRWheelVelocity);
                pLRWheelVelocity->LeftValue /= 2.2;		//2
                pLRWheelVelocity->RightValue /= 2.2;
                return 0;
            }

            theta = cn_AngleTrim2PI(theta);
            if(theta <= Pi/2)//第一象限
            {
                move_sign = 1;
                clock_sign = 1;
                theta_e1 = Pi/2 - theta;
            }
            else if(theta <= Pi)//第二象限
            {
                move_sign = 1;
                clock_sign = -1;
                theta_e1 = theta - Pi/2;
            }
            else if(theta <= 3*Pi/2)//第三象限
            {
                move_sign = -1;
                clock_sign = 1;
                theta_e1 = 3*Pi/2 - theta;
            }
            else//第四象限
            {
                move_sign = -1;
                clock_sign = -1;
                theta_e1 = theta - 3*Pi/2;
            }

            pLRWheelVelocity->LeftValue = speed*move_sign + clock_sign*(m_MoveParameter.kp4pospd*theta_e1);
            pLRWheelVelocity->RightValue = speed*move_sign - clock_sign*(m_MoveParameter.kp4pospd*theta_e1);
            //保存本周期角度误差，下一周期作微分用
            //theta_e2=theta_e1;
        }
        return 0;
    }
    int AvoidSelfRobots(RobotPose *robot, const Point &directionpt, double samespeed, Velocity *pSpeed)
    {
        if (robot == nullptr || pSpeed == nullptr)
            return 0;

        if (samespeed >= 60)
        {
            samespeed = 60;
        }

        Point obstacle[ROBOTNUM + 1];
        int obstacleCount = 1;
        for (int j = 1; j <= ROBOTNUM; j++)
        {
            if (&my_robot_pose[j] == robot)
                continue;
            if (obstacleCount > ROBOTNUM)
                break;
            obstacle[obstacleCount].x = my_robot_pose[j].x;
            obstacle[obstacleCount].y = my_robot_pose[j].y;
            obstacleCount++;
        }
        int teammateCount = obstacleCount - 1;

        int flag[ROBOTNUM + 1] = {0};
        int groupId = 0;
        for (int i = 1; i <= teammateCount; i++)
        {
            for (int j = i + 1; j <= teammateCount; j++)
            {
                double dist = cal_2PointsDist(obstacle[i], obstacle[j]);
                if (dist < 16)
                {
                    if (flag[i] == 0 && flag[j] == 0)
                    {
                        groupId++;
                        flag[i] = flag[j] = groupId;
                    }
                    else if (flag[i] != 0 && flag[j] != 0)
                    {
                        if (flag[i] > flag[j])
                            flag[i] = flag[j];
                        else
                            flag[j] = flag[i];
                    }
                    else
                    {
                        if (flag[i] == 0)
                            flag[i] = flag[j];
                        else
                            flag[j] = flag[i];
                    }
                }
            }
        }

        double radius[ROBOTNUM + 1];
        for (int i = 0; i <= ROBOTNUM; i++)
        {
            radius[i] = 12.0;
        }
        Point center[ROBOTNUM + 1];
        for (int i = 0; i <= ROBOTNUM; i++)
        {
            center[i].x = 0.0;
            center[i].y = 0.0;
        }
        int memberCount[ROBOTNUM + 1] = {0};

        for (int i = 1; i <= teammateCount; i++)
        {
            int group = flag[i];
            if (group > 0 && group <= ROBOTNUM)
            {
                center[group].x += obstacle[i].x;
                center[group].y += obstacle[i].y;
                memberCount[group]++;
            }
        }
        for (int g = 1; g <= ROBOTNUM; g++)
        {
            if (memberCount[g] == 0)
                continue;
            center[g].x /= memberCount[g];
            center[g].y /= memberCount[g];
            radius[g] = 0.0;
            for (int j = 1; j <= teammateCount; j++)
            {
                if (flag[j] == g)
                {
                    double dist = cal_2PointsDist(obstacle[j], center[g]);
                    if (dist > radius[g])
                        radius[g] = dist;
                }
            }
            radius[g] += 12.0;
        }

        double trantheta = atan2(directionpt.y - robot->y, directionpt.x - robot->x);
        trantheta = cal_AngleTrim2PI(trantheta);
        trantheta -= Pi / 2;
        trantheta = cal_AngleTrim2PI(trantheta);

        Point transformed[ROBOTNUM + 1];
        double nearest = 200.0;
        int blockIdx = ROBOTNUM + 5;
        for (int i = 1; i <= teammateCount; i++)
        {
            double dx, dy;
            if (flag[i] != 0)
            {
                dx = center[flag[i]].x - robot->x;
                dy = center[flag[i]].y - robot->y;
            }
            else
            {
                dx = obstacle[i].x - robot->x;
                dy = obstacle[i].y - robot->y;
            }
            transformed[i].x = dx * cos(trantheta) + dy * sin(trantheta);
            transformed[i].y = -dx * sin(trantheta) + dy * cos(trantheta);

            double effectiveRadius = radius[flag[i]];
            if (flag[i] == 0)
                effectiveRadius = radius[0];

            if (fabs(transformed[i].x) < effectiveRadius &&
                transformed[i].y > 0 && transformed[i].y < nearest)
            {
                nearest = transformed[i].y;
                blockIdx = i;
            }
        }

        double targetDist = distRobot2Pt(*robot, directionpt);
        if (blockIdx <= teammateCount && nearest > 0 && nearest + 5 < targetDist)
        {
            double effectiveRadius = radius[flag[blockIdx]];
            if (flag[blockIdx] == 0)
                effectiveRadius = radius[0];

            Point pt1, pt2, tranPt1, tranPt2, targetPt;
            bool useFirst;
            pt1.x = transformed[blockIdx].x - effectiveRadius;
            pt2.x = transformed[blockIdx].x + effectiveRadius;
            pt1.y = pt2.y = transformed[blockIdx].y;

            tranPt1.x = pt1.x * cos(trantheta) - pt1.y * sin(trantheta) + robot->x;
            tranPt1.y = pt1.x * sin(trantheta) + pt1.y * cos(trantheta) + robot->y;
            tranPt2.x = pt2.x * cos(trantheta) - pt2.y * sin(trantheta) + robot->x;
            tranPt2.y = pt2.x * sin(trantheta) + pt2.y * cos(trantheta) + robot->y;

            if (transformed[blockIdx].x >= 0)
            {
                targetPt = tranPt1;
                useFirst = true;
            }
            else
            {
                targetPt = tranPt2;
                useFirst = false;
            }

            if (targetPt.x < 8 || targetPt.x > 212 || targetPt.y < 8 || targetPt.y > 172)
            {
                if (useFirst)
                {
                    targetPt = tranPt2;
                    useFirst = false;
                }
                else
                {
                    targetPt = tranPt1;
                    useFirst = true;
                }
            }

            if (transformed[blockIdx].y < 30)
            {
                Point tempPt1, tempPt2, tranTempPt1, tranTempPt2;
                if (useFirst)
                {
                    tempPt1.x = pt1.x;
                    tempPt1.y = pt1.y - effectiveRadius / 2;
                    tempPt2.x = pt1.x;
                    tempPt2.y = pt1.y + effectiveRadius / 2;
                }
                else
                {
                    tempPt1.x = pt2.x;
                    tempPt1.y = pt2.y - effectiveRadius / 2;
                    tempPt2.x = pt2.x;
                    tempPt2.y = pt2.y + effectiveRadius / 2;
                }

                tranTempPt1.x = tempPt1.x * cos(trantheta) - tempPt1.y * sin(trantheta) + robot->x;
                tranTempPt1.y = tempPt1.x * sin(trantheta) + tempPt1.y * cos(trantheta) + robot->y;
                tranTempPt2.x = tempPt2.x * cos(trantheta) - tempPt2.y * sin(trantheta) + robot->x;
                tranTempPt2.y = tempPt2.x * sin(trantheta) + tempPt2.y * cos(trantheta) + robot->y;

                if (tempPt1.y < 1)
                    ToPositionPD(robot, tranTempPt2, samespeed, 35, pSpeed);
                else
                    ToPositionPD(robot, tranTempPt1, samespeed, 35, pSpeed);
                return 1;
            }
            else
            {
                ToPositionPD(robot, targetPt, samespeed, 35, pSpeed);
            }
        }
        else
        {
            return 0;
        }
        return 1;
    }

    //本函数用于使小车撞球
    
    
    //本函数用于使小车快速转指向目标角度:先判断需要转动的角度，在误差范围内则不做任何动作，否则根据其大小确定转动速度
    //Robot为小车位置信息，dbAngle为目标角度(弧度)，pSpeed为返回的左右轮速
    //Kp、Kd为比例、微分调节参数
    void s_TurnToAnglePD(RobotPose* pRobot, double dbAngle, Velocity* pSpeed)
    {
	    double theta, theta1;
	    double SameSpeed;
	    dbAngle = cn_AngleTrim2PI(dbAngle);
	    pRobot->theta = cn_AngleTrim2PI(pRobot->theta);//车身在坐标系下的角度位姿
	    theta = pRobot->theta - dbAngle;//转向目标角度需要转动的夹角
	    if (theta < -Pi)
		    theta = 2 * Pi + theta;
	    else if (theta > Pi)
		    theta = theta - 2 * Pi;
	    theta1 = fabs(theta);
	    if (theta1 < m_AngleParameter.AngleError)//判断是否在角度误差限之内
	    {
		    pSpeed->LeftValue = 0;
		    pSpeed->RightValue = 0;
		    return;
	    }
	    //需要转动的角度在角度误差限之外
	    SameSpeed = m_AngleParameter.Kp * theta1 + m_AngleParameter.Kd * (theta1 - m_Front);
	    if (SameSpeed > m_AngleParameter.MaxAngleSpeed)
		    SameSpeed = m_AngleParameter.MaxAngleSpeed;
	    m_Front = theta1;
	    if (theta < 0)
	    {
		    pSpeed->LeftValue = -SameSpeed;
		    pSpeed->RightValue = SameSpeed;
	    }
	    else
	    {
		    pSpeed->LeftValue = SameSpeed;
		    pSpeed->RightValue = -SameSpeed;
	    }
	    return;
    }
    
    //本函数用于使小车的方向以给定的时钟方向快速转到所要求的角度方向
    //Robot为小车的位置信息，Angle为需要转向的角度，Speed为返回的左右轮速
    //pPD为比例、微分调节参数结构
    int TurnToAnglePD(RobotPose *pRobot,double dbAngle,int clock,Velocity *pSpeed)
    {
        double Difference,SameSpeed;
        int Quadrant;
        Difference=pRobot->theta-dbAngle;
        Difference = cn_AngleTrim2PI(Difference);
        if (Difference <= m_AngleParameter.AngleError)//判断是否在角度误差限之内
        {
            pSpeed->LeftValue=0.;
            pSpeed->RightValue=0.;
            return 1;
        }
        if (clock==ANTICLOCK)
            Difference=2*Pi-Difference;
        else if (clock == NOCLOCK)
        {
            if (Difference >= 0 &&  Difference < Pi/2)//判断角度差所在象限
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
        //此处进行PD调节
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
            case 1://顺时针旋转
            case 3:
                {
                    pSpeed->LeftValue=SameSpeed;
                    pSpeed->RightValue=-SameSpeed;
                    break;
                }
            case 2://逆时针旋转
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
    
    //本函数用于使小车快速转向指定点
    //Robot为小车位置信息，point为转向的点，pSpeed为返回的左右轮速
    //Kp、Kd为比例、微分调节参数
    int TurnToPointPD(RobotPose *pRobot,Point Point,int clock,Velocity *pSpeed)
    {
        double Angle;
        int Result;
        struct Point Point1;
        Point1.x=pRobot->x;
        Point1.y=pRobot->y;
        Result=PointToPointDirectionAngle(Point1,Point,&Angle);
        if (Result==0)
            return 0;
        Result=TurnToAnglePD(pRobot,Angle,clock,pSpeed);
        return (Result);
    }

int TurnToPointPD(RobotPose *pRobot,BallPoint Point,int clock,Velocity *pSpeed)   //重构
    {
        double Angle;
        int Result;
        struct Point Point1;
        Point1.x=pRobot->x;
        Point1.y=pRobot->y;
        Result=PointToPointDirectionAngle(Point1,Point,&Angle);
        if (Result==0)
            return 0;
        Result=TurnToAnglePD(pRobot,Angle,clock,pSpeed);
        return (Result);
    }
int CS_ToPositionNew(RobotPose *robot, BallPoint ball, Point directionpt, 
									    int IfEndprocess, Velocity *pSpeed)
{
	int flag_1=0 , down=0;
	if(oldBallPt[0].y > oldBallPt[3].y && oldBallPt[3].y > oldBallPt[6].y)
		down = 1;
	else if(oldBallPt[0].y < oldBallPt[3].y && oldBallPt[3].y < oldBallPt[6].y)
		down = -1;
	if(oldBallPt[0].x > oldBallPt[3].x && oldBallPt[3].x > oldBallPt[6].x)
		flag_1 = 1;//�����ҷ������˶�
// 	if (samespeed>=120)//85
// 	{
// 		samespeed=120;//85
// 	}
	//double v_xishu = 1.0;//���ڱ���ʱ���������ٶ�
	int hitwall=0;
	double bvangle;
	bvangle=cn_AngleTrim2PI(ballCharacter.angle);
	Point fball;
	fball.x=ballCharacter.velocity*cos(bvangle)*yanchi+ball.x;
	fball.y=ballCharacter.velocity*sin(bvangle)*yanchi+ball.y;
	Point realdirectionpt;
	realdirectionpt=directionpt;
	Point cs_tempt,cs_pt1,cs_pt2;
	CIRCLEFORMULATION cs_circle1;
	LINEFORMULATION line_b2d,line_b2c;
	StdLineForm(fball,directionpt,&line_b2d);
	double shoottime;
	//ȷ������
	int robotno=0;
	if(Robot[1].x==robot->x&&Robot[1].y==robot->y)
	{
		robotno=1;
	}
	if(Robot[2].x==robot->x&&Robot[2].y==robot->y)
	{
		robotno=2;
	}
	if(Robot[3].x==robot->x&&Robot[3].y==robot->y)
	{
		robotno=3;
	}
	if(Robot[4].x==robot->x&&Robot[4].y==robot->y)
	{
		robotno=4;
	}
	//ȷ���������ʱ��
	shoottime=GetCharPerformance(robotno,*robot,TO_POINT(ball),directionpt);
	if(ballCharacter.velocity>0.2)
	{
		if(oldBallPt[0].x > oldBallPt[3].x && oldBallPt[3].x > oldBallPt[6].x)//back
		{
			shoottime=shoottime*(1+ballCharacter.velocity);
		}
		else
		{
			shoottime=shoottime*0.8;
		}
	}	

	fball.x=ballCharacter.velocity*cos(bvangle)*shoottime+ball.x+ballCharacter.velocity*cos(bvangle)*yanchi;
	fball.y=ballCharacter.velocity*sin(bvangle)*shoottime+ball.y+ballCharacter.velocity*sin(bvangle)*yanchi;
	//�ж����Ƿ��ײǽ
	if(ballCharacter.velocity>0.2)
	{
		if(fball.y>165&&ball.x>35&&ball.x<185)//�����ϱ���
		{
			Point pt;
			pt.x=ball.x;
			pt.y=ball.y-8;
			if(distRobot2Pt(*robot,ball)>=20)
			{
				pt.y=ball.y-10;
			}
			directionpt.x=223;
			directionpt.y=pt.y;
			StdLineForm(pt,directionpt,&line_b2d);
			hitwall=1;
		}
		if(fball.y<15&&ball.x>35&&ball.x<185)//�±���
		{
			
			Point pt;
			pt.x=ball.x;
			pt.y=ball.y+8;
			if(distRobot2Pt(*robot,ball)>=20)
			{
				pt.y=ball.y+10;
			}
			directionpt.x=223;
			directionpt.y=pt.y;
			StdLineForm(pt,directionpt,&line_b2d);
			hitwall=1;
		}
	}
	else
	{
		if(ball.y>165&&ball.x>35&&ball.x<185)
		{
			
			Point pt;
			pt.x=ball.x;
			pt.y=ball.y-8;
			if(distRobot2Pt(*robot,ball)>=20)
			{
				pt.y=ball.y-10;
			}
			directionpt.x=223;
			directionpt.y=pt.y;
			StdLineForm(pt,directionpt,&line_b2d);
			hitwall=1;		
		}
		if(ball.y<15&&ball.x>35&&ball.x<185)
		{
			Point pt;
			pt.x=ball.x;
			pt.y=ball.y+8;
			if(distRobot2Pt(*robot,ball)>=20)
			{
				pt.y=ball.y+10;
			}
			directionpt.x=223;
			directionpt.y=pt.y;
			StdLineForm(pt,directionpt,&line_b2d);
			hitwall=1;
		}
	}
	fball.x=ball.x+ballCharacter.velocity*cos(bvangle)*yanchi;
	fball.y=ball.y+ballCharacter.velocity*sin(bvangle)*yanchi;

	//ͨ��fball��ֱ��line_b2d�õ���֮���ഹֱ����һֱ��line_b2c����ֱ�߽���cs_tempt
	cn_PointPerpendLine(fball,&line_b2d,&line_b2c,&cs_tempt);
	
	///////////////////////////////////////////////////////////////////////////////	
	
	cs_circle1.x = fball.x;
	cs_circle1.y = fball.y;
	cs_circle1.r = 15;//18	//15
	//ֱ����Բ�Ľ���
	cn_LineCircleCross(&line_b2c,&cs_circle1,&cs_pt1,&cs_pt2);
	Point cs_pt3;	
	if (cs_pt1.y<cs_pt2.y)
	{
		cs_pt3=cs_pt1;
		cs_pt1=cs_pt2;
		cs_pt2=cs_pt3;
	}


	double theta,dx,dy,dx1,dy1;
	theta = atan2(ball.y-directionpt.y,ball.x-directionpt.x);
	theta = cn_AngleTrim2PI(theta);


	dx = robot->x-fball.x;
	dy = robot->y-fball.y;
	dx1 = dx*cos(theta - Pi/2) + dy*sin(theta - Pi/2);
	dy1 = -dx*sin(theta - Pi/2) + dy*cos(theta - Pi/2);

    double ztbd,ztuptheta,ztdowntheta;
	ztbd=cn_LineAngle(&line_b2d);
	ztuptheta=ztbd-Pi/9;
	ztdowntheta=ztbd+Pi/9;
	LINEFORMULATION ztup,ztdown;
	if(cs_pt1.y>cs_pt2.y)
	{
        StdLineForm(cs_pt1,ztuptheta,&ztup);
		StdLineForm(cs_pt2,ztdowntheta,&ztdown);
	}
	else
	{
        StdLineForm(cs_pt1,ztdowntheta,&ztdown);
		StdLineForm(cs_pt2,ztuptheta,&ztup);
	}

	int ztflag=0;
	if(robot->y < (-ztup.a*robot->x-ztup.c)/ztup.b&&robot->y > (-ztdown.a*robot->x-ztdown.c)/ztdown.b)
	{
		cs_circle1.x = fball.x;
		cs_circle1.y = fball.y;
		cs_circle1.r = 12;		//15
		cn_LineCircleCross(&line_b2c,&cs_circle1,&cs_pt1,&cs_pt2);
		ztflag=1;
	}

	//һ����
	if(dy1<=0.57735*dx1&&dy1<=-0.57735*dx1) 
		//	if(robot->x > 5+(-line_b2c.b*robot->y-line_b2c.c)/line_b2c.a)//)
	{
        double	angle1,pt1angle2,pt2angle2,/*result,*/ddist,pt1angle,pt2angle,angle2;
		Point rpt;
		int dist;
		int angleforpi,angle2forpi;
		angle2 = cn_AngleTrim2PI(robot->theta);
		rpt.x = robot->x;
		rpt.y = robot->y;
		pt1angle = Getpt2ptAngle(rpt,cs_pt1);
		pt2angle = Getpt2ptAngle(rpt,cs_pt2);
		pt1angle2 = pt1angle - angle2;//С�������복��1����֮��ļн�
		pt2angle2 = pt2angle - angle2;//С�������복��2����֮��ļн�
		pt1angle2 = cn_AngleTrim2PI(pt1angle2);
		pt2angle2 = cn_AngleTrim2PI(pt2angle2);
		
		if(pt1angle2>Pi)
			pt1angle2 = 2*Pi  -  pt1angle2;
		if(pt1angle2>Pi/2)//0-Pi/2
			pt1angle2 = Pi - pt1angle2;//С�������복��1����֮��ļн�0~Pi/2
		if(pt2angle2>Pi)
			pt2angle2 = 2*Pi  -  pt2angle2;
		if(pt2angle2>Pi/2)//0-Pi/2
			pt2angle2 = Pi - pt2angle2;//С�������복��2����֮��ļн�0~Pi/2
        ddist = distRobot2Pt(*robot,ball);
		dist = ddist;
		int pt1score,pt2score;
		//pt1
		if(pt1angle2<Pi/18)//10
		{
            pt1score = charPerformancescore00[dist];
		}
		else if(pt1angle2<Pi/9)//20
		{
			pt1score = charPerformancescore010[dist];
		}
		else if(pt1angle2<Pi/6)//30
		{
            pt1score = charPerformancescore020[dist];
		}
		else if(pt1angle2<2*Pi/9)//40
		{
			pt1score = charPerformancescore030[dist];
		}
		else if(pt1angle2<5*Pi/18)//50
		{
			pt1score = charPerformancescore040[dist];
		}
		else if(pt1angle2<Pi/3)//60
		{
			pt1score = charPerformancescore050[dist];
		}
		else if(pt1angle2<7*Pi/18)//70
		{
			pt1score = charPerformancescore060[dist];
		}
		else if(pt1angle2<8*Pi/18)//80
		{
			pt1score = charPerformancescore070[dist];
		}
		else if(pt1angle2<Pi/2)//90
		{
			pt1score = charPerformancescore080[dist];
		}
		else
		{ 
			pt1score = charPerformancescore090[dist];
		}
		//pt2
		if(pt2angle2<Pi/18)//10
		{
            pt2score = charPerformancescore00[dist];
		}
		else if(pt2angle2<Pi/9)//20
		{
			pt2score = charPerformancescore010[dist];
		}
		else if(pt2angle2<Pi/6)//30
		{
            pt2score = charPerformancescore020[dist];
		}
		else if(pt2angle2<2*Pi/9)//40
		{
			pt2score = charPerformancescore030[dist];
		}
		else if(pt2angle2<5*Pi/18)//50
		{
			pt2score = charPerformancescore040[dist];
		}
		else if(pt2angle2<Pi/3)//60
		{
			pt2score = charPerformancescore050[dist];
		}
		else if(pt2angle2<7*Pi/18)//70
		{
			pt2score = charPerformancescore060[dist];
		}
		else if(pt2angle2<8*Pi/18)//80
		{
			pt2score = charPerformancescore070[dist];
		}
		else if(pt2angle2<Pi/2)//90
		{
			pt2score = charPerformancescore080[dist];
		}
		else
		{ 
			pt2score = charPerformancescore090[dist];
		}
		if(dist<15)
		{
			if(dist<8)
			{
				pt1score=0;
				pt2score=0;
			}
			else
			{
				pt1score=pt1score+(15-dist);
				pt2score=pt2score+(15-dist);
				pt1score=pt1score*(dist-8)/7;
				pt2score=pt2score*(dist-8)/7;
			}
		}
		if(ballCharacter.velocity>0.2)
		{
			if(oldBallPt[0].x > oldBallPt[3].x && oldBallPt[3].x > oldBallPt[6].x)//back
			{
				pt1score=pt1score*(1+ballCharacter.velocity);
				pt2score=pt2score*(1+ballCharacter.velocity);
			}
			else
			{
				pt1score=pt1score*0.8;
				pt2score=pt2score*0.8;
			}
		}
		
		Point fpt1ball,fpt2ball;
		fpt1ball.x = ballCharacter.velocity*cos(bvangle)*pt1score+ball.x;//Ԥ�����ܵ�λ��
		fpt1ball.y = ballCharacter.velocity*sin(bvangle)*pt1score+ball.y;//Ԥ�����ܵ�λ��
		fpt2ball.x = ballCharacter.velocity*cos(bvangle)*pt2score+ball.x;//Ԥ�����ܵ�λ��
		fpt2ball.y = ballCharacter.velocity*sin(bvangle)*pt2score+ball.y;//Ԥ�����ܵ�λ��
		LINEFORMULATION pt1b2d,pt2b2d,pt1b2c,pt2b2c;
		StdLineForm(fpt1ball,directionpt,&pt1b2d);
		StdLineForm(fpt2ball,directionpt,&pt2b2d);
		Point cpt;
		cn_PointPerpendLine(fpt1ball,&pt1b2d,&pt1b2c,&cpt);
		cn_PointPerpendLine(fpt2ball,&pt2b2d,&pt2b2c,&cpt);
		CIRCLEFORMULATION fcirclept1,fcirclept2;
		fcirclept1.x=fpt1ball.x;
		fcirclept1.y=fpt1ball.y;
		fcirclept1.r=18;
		if(ztflag==1)
		{
			fcirclept1.r=12;
		}
		fcirclept2.x=fpt2ball.x;
		fcirclept2.y=fpt2ball.y;
		fcirclept2.r=18;
		if(ztflag==1)
		{
			fcirclept2.r=12;
		}
		Point ffpt1pt1,ffpt1pt2,ffpt2pt1,ffpt2pt2,fpt1,fpt2;
		cn_LineCircleCross(&pt1b2c,&fcirclept1,&ffpt1pt1,&ffpt1pt2);
		///���Ͻ������fpt1
		if(cs_pt1.y>cs_pt2.y&&ffpt1pt1.y>ffpt1pt2.y)
		{
			fpt1=ffpt1pt1;
		}
		else if(cs_pt1.y<cs_pt2.y&&ffpt1pt1.y<ffpt1pt2.y)
		{
			fpt1=ffpt1pt1;
		}
		else
		{
            fpt1=ffpt1pt2;
		}
		
		//���Ͻ������fpt2
		cn_LineCircleCross(&pt2b2c,&fcirclept2,&ffpt2pt1,&ffpt2pt2);
		if(cs_pt1.y>cs_pt2.y&&ffpt2pt1.y>ffpt2pt2.y)
		{
			fpt2=ffpt2pt2;
		}
		else if(cs_pt1.y<cs_pt2.y&&ffpt2pt1.y<ffpt2pt2.y)
		{
			fpt2=ffpt2pt2;
		}
		else
		{
			fpt2=ffpt2pt1;
		}
		
		//�ж��ܵ��Ƿ�ϸ�
		int notcspt1,notcspt2,allout;
		notcspt1=0;
		notcspt2=0;
		allout=0;
		if(fpt1.y>157||fpt1.y<23)
		{
			notcspt1=1;
		}
		if(fpt2.y>157||fpt2.y<23)
		{
			notcspt2=1;
		}
// 		if(cs_pt1.y>157||cs_pt1.y<23)
// 		{
// 			notcspt1=1;
// 		}
// 		if(cs_pt2.y>157||cs_pt2.y<23)
// 		{
// 			notcspt2=1;
//		}
		if(notcspt1==1&&notcspt2==1)
		{
			allout=1;
		}

		double V2=10;
		/////���������߽����ƶ�ʱ
        if(fabs(ballCharacter.velocity)>0.4 && (notcspt1==1||notcspt2==1) && ball.y<=150 && ball.y>=30)
		{
			if(allout==1)//�����㶼����������������Զ��ĵ�
			{
				double distfpt1,distfpt2;
				if(down==-1)
				{
					distfpt1=cs_pt1.y-157;
					distfpt2=cs_pt2.y-157;//��ʲô����ô��
				}
				else
				{
					distfpt1=23-cs_pt1.y;
					distfpt2=23-cs_pt2.y;
				}

				if(distfpt1<=distfpt2)
				{	
					if(distRobot2Pt(*robot,cs_pt1)>20)
					{	
						//AvoidALLRobotsM(robot,cs_pt1,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);
						ToPositionPDchampionnew(robot,cs_pt1,90*v_xishu,pSpeed);
					}
					else
					{
						//ToPositionPD(robot,cs_pt1,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);	//90
						ToPositionPDchampionnew(robot,cs_pt1,80*v_xishu,pSpeed);
					}	
				}
				else
				{
					if(distRobot2Pt(*robot,cs_pt2)>20)
					{
						//AvoidALLRobotsM(robot,cs_pt2,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);//80
						ToPositionPDchampionnew(robot,cs_pt2,90*v_xishu,pSpeed);
					}
					else
					{
						//ToPositionPD(robot,cs_pt2,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);//90
						ToPositionPDchampionnew(robot,cs_pt2,80*v_xishu,pSpeed);
					} 
				}
			}
			else//��һ��������Ҫ��ĵ㣺�ܷ���Ҫ��ĵ�
			{
				if(notcspt1==1)
				{
					if(distRobot2Pt(*robot,cs_pt2)>20)
					{
						//AvoidALLRobotsM(robot,cs_pt2,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);//80
						ToPositionPDchampionnew(robot,cs_pt2,90*v_xishu,pSpeed);
					}
					else
					{
						//ToPositionPD(robot,cs_pt2,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);//90
						ToPositionPDchampionnew(robot,cs_pt2,80*v_xishu,pSpeed);
					} 	
				}
				else if(notcspt2==1)
				{	
					if(distRobot2Pt(*robot,cs_pt1)>20)
					{
						//AvoidALLRobotsM(robot,cs_pt1,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);
						ToPositionPDchampionnew(robot,cs_pt1,90*v_xishu,pSpeed);
					}
					else
					{
						//ToPositionPD(robot,cs_pt1,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);	//90
						ToPositionPDchampionnew(robot,cs_pt1,80*v_xishu,pSpeed);
					}
				}
			}
		}
		//����ģʽ����û����߽��ƶ�
		else
		{
			notcspt1=0;
			notcspt2=0;
			allout=0;
            if(cs_pt1.y>157||cs_pt1.y<23)
			{
				notcspt1=1;
			}
			if(cs_pt2.y>157||cs_pt2.y<23)
			{
				notcspt2=1;
			}
			if(notcspt1==1&&notcspt2==1)
			{
				allout=1;
			}
			if(allout==1)//�����ܵ�����ϸ�����Զ��õ�
			{
				double distcspt1,distcspt2;
				if(cs_pt1.y>90)
				{
					distcspt1=fpt1.y-165;
				}
				else
				{
					distcspt1=15-fpt1.y;
				}
				if(cs_pt2.y>90)
				{
					distcspt2=fpt2.y-165;
				}
				else
				{
					distcspt2=15-fpt2.y;
				}
				if(distcspt1<distcspt2)
				{	
                    if(distRobot2Pt(*robot,cs_pt1)>20)
					{
						//AvoidALLRobotsM(robot,cs_pt1,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);
						ToPositionPDchampionnew(robot,cs_pt1,90*v_xishu,pSpeed);
					}
					else
					{
						//ToPositionPD(robot,cs_pt1,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);	//90
						ToPositionPDchampionnew(robot,cs_pt1,80*v_xishu,pSpeed);
					}
				}
				else
				{
					
					if(distRobot2Pt(*robot,cs_pt2)>20)
					{
						//AvoidALLRobotsM(robot,cs_pt2,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);//80
						ToPositionPDchampionnew(robot,cs_pt2,90*v_xishu,pSpeed);
					}
					else
					{
						//ToPositionPD(robot,cs_pt2,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);//90
						ToPositionPDchampionnew(robot,cs_pt2,80*v_xishu,pSpeed);
					} 
				}
			}
			else//���������ܵ㲻�ϸ�
			{
				if(notcspt1==1)
				{
					
					if(distRobot2Pt(*robot,cs_pt2)>20)
					{
						//AvoidALLRobotsM(robot,cs_pt2,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);//80
						ToPositionPDchampionnew(robot,cs_pt2,90*v_xishu,pSpeed);
					}
					else
					{
						//ToPositionPD(robot,cs_pt2,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);//90
						ToPositionPDchampionnew(robot,cs_pt2,80*v_xishu,pSpeed);
					} 
					
				}
				else if(notcspt2==1)
				{
					
					if(distRobot2Pt(*robot,cs_pt1)>20)
					{
						//AvoidALLRobotsM(robot,cs_pt1,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);
						ToPositionPDchampionnew(robot,cs_pt1,90*v_xishu,pSpeed);
					}
					else
					{
						//ToPositionPD(robot,cs_pt1,100-V2,30+qiusubi*ballCharacter.velocity,pSpeed);	//90
						ToPositionPDchampionnew(robot,cs_pt1,80*v_xishu,pSpeed);
					}
				}
				else
				{
					if (pt1score<pt2score)
					{
						ToPositionPDchampionnew(robot,cs_pt1,90*v_xishu,pSpeed);
					}
					else
						ToPositionPDchampionnew(robot,cs_pt2,80*v_xishu,pSpeed);
				}
			}	
		}	
		//hold_ball(IfEndprocess,robot,ball,directionpt,80,pSpeed);
		//onezonehitball(robot,ball,pSpeed);
	}
	
	//2����
	else if(dy1<0.57735*dx1||dy1<-0.57735*dx1)
	{	
		if(dy1<0||distRobot2Pt(*robot,fball)>15)
		{
			//fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*yanchi+ball.x;
			//fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*yanchi+ball.y;
			cs_circle1.x = fball.x;
			cs_circle1.y = fball.y;
			cs_circle1.r = 30;

			cn_LineCircleCross(&line_b2d,&cs_circle1,&cs_pt1,&cs_pt2);
			
			if(ballCharacter.velocity>0.4)
			{
				if(cs_pt1.x<cs_pt2.x)
				{
					//ToPositionPD(robot,cs_pt1,85,20+qiusubi*ballCharacter.velocity,pSpeed);	//100
					ToPositionPDchampionnew(robot,cs_pt1,70*v_xishu,pSpeed);
				}
				else
				{
					//ToPositionPD(robot,cs_pt2,85,20+qiusubi*ballCharacter.velocity,pSpeed);	//100
					ToPositionPDchampionnew(robot,cs_pt2,70*v_xishu,pSpeed);
				}
			}
			else
			{
                if(cs_pt1.x<cs_pt2.x)
				{
					//ToPositionPD(robot,cs_pt1,45,20+qiusubi*ballCharacter.velocity,pSpeed);	//45
					ToPositionPDchampionnew(robot,cs_pt1,60*v_xishu,pSpeed);
				}
				else
				{
					//ToPositionPD(robot,cs_pt2,45,20+qiusubi*ballCharacter.velocity,pSpeed);	//45
					ToPositionPDchampionnew(robot,cs_pt2,60*v_xishu,pSpeed);
				}
			}
		}
		else //�����ϰ벿���Ҿ���ܽ�
		{
			//fball.x=ballCharacter.velocity*cos(ballCharacter.angle)*yanchi+ball.x;
			//fball.y=ballCharacter.velocity*sin(ballCharacter.angle)*yanchi+ball.y;
			cs_circle1.x = fball.x;
			cs_circle1.y = fball.y;
			cs_circle1.r = 15;//12
			cn_LineCircleCross(&line_b2d,&cs_circle1,&cs_pt1,&cs_pt2);
			if(ballCharacter.velocity>0.4)
			{
				if(cs_pt1.x<cs_pt2.x)
				{
					//ToPositionPD(robot,cs_pt1,85,15+qiusubi*ballCharacter.velocity,pSpeed);	//100
					ToPositionPDchampionnew(robot,cs_pt1,70*v_xishu,pSpeed);
				}
				else
				{
					//ToPositionPD(robot,cs_pt2,85,15+qiusubi*ballCharacter.velocity,pSpeed);	//100
					ToPositionPDchampionnew(robot,cs_pt2,70*v_xishu,pSpeed);
				}
			}
			else
			{
                if(cs_pt1.x<cs_pt2.x)
				{
					//ToPositionPD(robot,cs_pt1,45,15+qiusubi*ballCharacter.velocity,pSpeed);	//45
					ToPositionPDchampionnew(robot,cs_pt1,60*v_xishu,pSpeed);
				}
				else
				{
					//ToPositionPD(robot,cs_pt2,45,15+qiusubi*ballCharacter.velocity,pSpeed);	//45
					ToPositionPDchampionnew(robot,cs_pt2,60*v_xishu,pSpeed);
				}
			}
		}
        New_QuickCurve(robot,ball,pSpeed); 
		//		    hold_ball(IfEndprocess,robot,ball,directionpt,80,pSpeed);
		New_EndProcess(1,robot,realdirectionpt,ball,pSpeed); 
	}


	//3����
	else	//���ڳ���Է�����֮��			//if(dy1>0)
	{
		Point cs_robot;
		cs_robot.x = robot->x;
		cs_robot.y = robot->y;
        fball.x=ball.x;
		fball.y=ball.y;
		Point midpt,cs_tempt;
		LINEFORMULATION line1,line2;
		midpt.x=(cs_robot.x+ball.x)/2;
		midpt.y=(cs_robot.y+ball.y)/2;
		StdLineForm(TO_POINT(ball),cs_robot,&line1);
        cn_PointPerpendLine(midpt,&line1,&line2,&cs_tempt);
        StdLineForm(TO_POINT(ball),directionpt,&line1);
        cn_2LinesCrossPoint(&line1,&line2,&cs_tempt);
		cs_tempt.x=(cs_tempt.x+ball.x)/2;
        cs_tempt.y=(cs_tempt.y+ball.y)/2;

		if(ballCharacter.velocity>0.4)
		{
			if(cn_2PointsDist(fball,cs_robot)>60)
			{
				if(oldBallPt[0].x<oldBallPt[3].x&&oldBallPt[3].x<oldBallPt[6].x)//����Է������˶�
				{
					double v,d;
					d=cn_2PointsDist(fball,cs_robot);
					v=0.576*(d-60)+95;
					if(v>=120)
					{
						v=120;
					}
					ToPositionPDlimit(robot,cs_tempt,v*v_xishu,20+qiusubi*ballCharacter.velocity,pSpeed);
				}
				else
					ToPositionPDlimit(robot,cs_tempt,88*v_xishu,20+qiusubi*ballCharacter.velocity,pSpeed);
			}
			else
			{
				if(hitwall==1)
				{
					//CS_CurveShootfball(IfEndprocess,robot,ball,fball,directionpt,pSpeed,hitwall);
					//ToPositionNew(robot,ball,directionpt,samespeed,IfEndprocess,pSpeed);
					hitwallCS_CurveShoot(IfEndprocess,robot,ball,fball,directionpt,realdirectionpt,pSpeed,hitwall);
				}
				else
				{
					CS_CurveShootfball(IfEndprocess,robot,ball,fball,directionpt,pSpeed,hitwall);
				}
			}
		}
        else
		{
            if(cn_2PointsDist(fball,cs_robot)>60)
			{
				if(oldBallPt[0].x<oldBallPt[3].x&&oldBallPt[3].x<oldBallPt[6].x)
				{
					double v,d;
					d=cn_2PointsDist(fball,cs_robot);
					v=0.576*(d-60)+95;
					if(v>=120)
					{
						v=120;
					}
					ToPositionPDlimit(robot,cs_tempt,v*v_xishu,20+qiusubi*ballCharacter.velocity,pSpeed);
				}
				else
					ToPositionPDlimit(robot,cs_tempt,88*v_xishu,20+qiusubi*ballCharacter.velocity,pSpeed);
			}
			else
			{
				if(hitwall==1)
				{
					//CS_CurveShootfball(IfEndprocess,robot,ball,fball,directionpt,pSpeed,hitwall);
					//ToPositionNew(robot,ball,directionpt,samespeed,IfEndprocess,pSpeed);
					hitwallCS_CurveShoot(IfEndprocess,robot,ball,fball,directionpt,realdirectionpt,pSpeed,hitwall);
				}
				else
				{
					CS_CurveShootfball(IfEndprocess,robot,ball,fball,directionpt,pSpeed,hitwall);
				}				
			}
		}
	}
	return 1;
}
    /************************************************/
    /********************辅助函数********************/
    
    double Limit(double value, double limitation)//限制数值函数
    {
	    double tempv;
	    tempv = value;
	    if (tempv > limitation)
		    tempv = limitation;
	    if (tempv < -limitation)
		    tempv = -limitation;
	    return tempv;
    }
    //本函数用于求解从点point1到点point2的方向角，成功返回1，否则，返回0
    //求得（0—2pi)之间的弧度方向角存于Angle
    int PointToPointDirectionAngle(Point Point1,Point Point2,double *pAngle)
    {
        double x,y;
        x=Point2.x-Point1.x;
        y=Point2.y-Point1.y;
        if (x==0 && y==0)
            return 0;
        *pAngle=atan2(y,x);
        if (*pAngle<0)
            *pAngle+=2*Pi;
        return 1;
    }
	   int PointToPointDirectionAngle(Point Point1,BallPoint Point2,double *pAngle)
    {
        double x,y;
        x=Point2.x-Point1.x;
        y=Point2.y-Point1.y;
        if (x==0 && y==0)
            return 0;
        *pAngle=atan2(y,x);
        if (*pAngle<0)
            *pAngle+=2*Pi;
        return 1;
    }
	/**/
	

    /************************************************/
};












int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Strategy>("strategy");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}