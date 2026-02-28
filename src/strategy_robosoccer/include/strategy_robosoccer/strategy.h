#pragma once

#define Pi 3.14159265358979323846

#define GROUND_WIDTH  220
#define GROUND_HEIGHT 180

#define		wallleft		0.0
#define		wallright		220.0
#define		wallbottom		0.0
#define		walltop			180.0

#define		CENTER_X		110.0
#define		CENTER_Y		90.0

#define ROBOTNUM 5

//比赛模式
#define NormalStart  0 //普通
#define PenaltyKick  1 //点球
#define GoalKick     2 //门球
#define FreeKick     3 //任意球
#define TackleBall   4 //争球
#define RetractCar   5 //收车

#define CLOCKWISE 1
#define ANTICLOCK -1
#define NOCLOCK  0
#define FOREWARD 1
#define BACKWARD -1


struct RobotPose
{
    RobotPose()
    {
        x = 0.0;
        y = 0.0;
        theta = 0.0;
    }
    RobotPose(double x, double y, double theta)
    {
        this->x = x;
        this->y = y;
        this->theta = theta;
    }
    double x;
    double y;
    double theta;
};

typedef struct
{
    double x = 0.0;
    double y = 0.0;
}OppRobotPoint, BallPoint;



//470;//���ٲ����ƣ����ڳ����еķ�ֹ�򻬣�ToPositionPDlimit��ToPositionPDchampionnew��CS_CurveShootfball��New_EndProcess��

struct Point  // Point 与POINT相同  不想改了 
{
    Point()
    {
        x = 0.0;
        y = 0.0;
    }
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double x;
    double y;
};
double TNpara(int i,RobotPose myrobot,Point ball,Point goal,double dist,double angle);
struct Velocity
{
    Velocity()
    {
        LeftValue = 0.0;
        RightValue = 0.0;
    }
    Velocity(double LeftValue, double RightValue)
    {
        this->LeftValue = LeftValue;
        this->RightValue = RightValue;
    }
    double LeftValue;
    double RightValue;
};


struct AngleParameter
{
	double Kp = 0.0;
	double Kd = 0.0;
	double AngleError = 0.0;//视觉所能分辨的角度
	double MaxAngleSpeed = 0.0;//小车的最大旋转边缘线速度
	double MaxAngle = 0.0;//小车能以最大角速度旋转的角度下限
};

struct MoveParameter
{
    double max_distance = 0.0;
    double max_distanceG = 0.0;
    double V_MAX = 0.0;
    double V_max = 0.0;
    double max_angle = 0.0;
    double kp4pospd = 0.0;
    double kd4pospd = 0.0;
    double kp4pospdG = 0.0;
    double kd4pospdG = 0.0;
};

struct ROSrect {
    float left;     // 左边界 x 坐标
    float top;      // 上边界 y 坐标
    float right;    // 右边界 x 坐标
    float bottom;   // 下边界 y 坐标
    
    // 构造函数
    ROSrect() : left(0), top(0), right(0), bottom(0) {}
    
    ROSrect(float l, float t, float r, float b) 
        : left(l), top(t), right(r), bottom(b) {}
    
    // 判断点是否在矩形内
    bool contains(float x, float y) const {
        return (x >= left && x <= right && y >= bottom && y <= top);
    }
    
    // 判断点是否在矩形内（使用Point结构）
    bool contains(const Point& pt) const {
        return contains(pt.x, pt.y);
    }
    
    // 获取矩形宽度
    float width() const {
        return right - left;
    }
    
    // 获取矩形高度
    float height() const {
        return top - bottom;
    }
    
    // 获取中心点
    Point center() const {
        return Point((left + right) / 2.0f, (bottom + top) / 2.0f);
    }
    
    // 扩展矩形边界
    void expand(float margin) {
        left -= margin;
        right += margin;
        bottom -= margin;
        top += margin;
    }
    
    // 规范化（确保 left <= right, bottom <= top）
    void normalize() {
        if (left > right) std::swap(left, right);
        if (bottom > top) std::swap(bottom, top);
    }
    
    // 打印矩形信息（用于调试）
   /*void print(const std::string& name = "") const {
        if (!name.empty()) {
            std::cout << name << ": ";
        }
        std::cout << "[" << left << ", " << top << ", " 
                  << right << ", " << bottom << "]" << std::endl;
    }*/ 
};




/*int  yanchi=0;
int	vx=385;
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

//机器人位姿
    RobotPose my_robot_pose[ROBOTNUM+1]; //我方机器人位姿
    RobotPose old_robot_pose[ROBOTNUM+1]; // 上一帧机器人位姿 
    OppRobotPoint opp_robot_point[ROBOTNUM+1]; //敌方机器人位姿
	OppRobotPoint OpponentGoalKeeper; //敌方守门员位置
//球位置
    BallPoint ball_point;//当前球位置
    BallPoint old_ball_pts[7];//存储最近7帧球的位置
    BallPoint old_ball_pts_dense[14];//更密集的轨迹记录（14帧）

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


RobotPose		opp_robot_point[12];
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
	double               charPerformancescore17090[285];//*/



/*extern int yanchi;
extern int vx;
extern BallPoint oldBallPt[7];
extern BallPoint oldBallPtv[14];
extern RobotPose Robot[12];
extern int shootsign3;
extern int zhuangqiangshijian;
extern double moca, moca1;
extern double pfmj;
extern int pfmi;
extern int readyflag;
extern double dizeng;
extern double zhichong[50];
extern int step;
extern int zsg_time;
extern int timer;
extern int g_GoalKeeper;
extern int g_timeflag;
extern int defendflag;
extern float robotY2;
extern float robotY1;
extern float secondpt;
extern float showtarget;
extern float showtarget1;
extern float showtarget2;
extern float v_xishu;
extern RobotPose my_robot_pose[ROBOTNUM + 1];
extern RobotPose old_robot_pose[ROBOTNUM + 1];
extern OppRobotPoint opp_robot_point[ROBOTNUM + 1];
extern OppRobotPoint OpponentGoalKeeper;
extern BallPoint ball_point;
extern BallPoint old_ball_pts[7];
extern BallPoint old_ball_pts_dense[14];
extern Velocity rbV[ROBOTNUM + 1];
extern Point endprocessrobot;
extern int formNo;
extern int currentResult[6], oldResult[6];
extern int currentForm[6], oldForm[6];
extern int currentOrder[6], oldOrder[6];
extern double perfRecord[6], oldperfRecord[6];
extern int ban_counter, ban_counter2, ban_counter3;
extern int defend_counter;
extern int ban_warning_flag, ban_warning_flag2;
extern int ForbinCount;
extern int changeCharacter;
extern int EndProcessFlag;
extern int charrobot;
extern int timelimit;
extern bool isAttack;
extern bool isRightArea;
extern int StartMode;
extern bool isBackInitPose;
extern bool isReInit;
extern bool isStartGame;
extern bool RingFlag;
extern double distError;
extern double m_Front;
extern double End_vxishu;
extern double endprocessV;
extern double qiusubi;
extern double anglexishuA;
extern double anglexishuC;
extern float secondpt1;
extern AngleParameter m_AngleParameter;
extern MoveParameter m_MoveParameter;
extern RobotPose opp_robot_point[12];
extern double charPerformancescore00[285];
extern double charPerformancescore010[285];
extern double charPerformancescore020[285];
extern double charPerformancescore030[285];
extern double charPerformancescore040[285];
extern double charPerformancescore050[285];
extern double charPerformancescore060[285];
extern double charPerformancescore070[285];
extern double charPerformancescore080[285];
extern double charPerformancescore090[285];
extern double charPerformancescore100[285];
extern double charPerformancescore1010[285];
extern double charPerformancescore1020[285];
extern double charPerformancescore1030[285];
extern double charPerformancescore1040[285];
extern double charPerformancescore1050[285];
extern double charPerformancescore1060[285];
extern double charPerformancescore1070[285];
extern double charPerformancescore1080[285];
extern double charPerformancescore1090[285];
extern double charPerformancescore200[285];
extern double charPerformancescore2010[285];
extern double charPerformancescore2020[285];
extern double charPerformancescore2030[285];
extern double charPerformancescore2040[285];
extern double charPerformancescore2050[285];
extern double charPerformancescore2060[285];
extern double charPerformancescore2070[285];
extern double charPerformancescore2080[285];
extern double charPerformancescore2090[285];
extern double charPerformancescore300[285];
extern double charPerformancescore3010[285];
extern double charPerformancescore3020[285];
extern double charPerformancescore3030[285];
extern double charPerformancescore3040[285];
extern double charPerformancescore3050[285];
extern double charPerformancescore3060[285];
extern double charPerformancescore3070[285];
extern double charPerformancescore3080[285];
extern double charPerformancescore3090[285];
extern double charPerformancescore400[285];
extern double charPerformancescore4010[285];
extern double charPerformancescore4020[285];
extern double charPerformancescore4030[285];
extern double charPerformancescore4040[285];
extern double charPerformancescore4050[285];
extern double charPerformancescore4060[285];
extern double charPerformancescore4070[285];
extern double charPerformancescore4080[285];
extern double charPerformancescore4090[285];
extern double charPerformancescore500[285];
extern double charPerformancescore5010[285];
extern double charPerformancescore5020[285];
extern double charPerformancescore5030[285];
extern double charPerformancescore5040[285];
extern double charPerformancescore5050[285];
extern double charPerformancescore5060[285];
extern double charPerformancescore5070[285];
extern double charPerformancescore5080[285];
extern double charPerformancescore5090[285];
extern double charPerformancescore600[285];
extern double charPerformancescore6010[285];
extern double charPerformancescore6020[285];
extern double charPerformancescore6030[285];
extern double charPerformancescore6040[285];
extern double charPerformancescore6050[285];
extern double charPerformancescore6060[285];
extern double charPerformancescore6070[285];
extern double charPerformancescore6080[285];
extern double charPerformancescore6090[285];
extern double charPerformancescore700[285];
extern double charPerformancescore7010[285];
extern double charPerformancescore7020[285];
extern double charPerformancescore7030[285];
extern double charPerformancescore7040[285];
extern double charPerformancescore7050[285];
extern double charPerformancescore7060[285];
extern double charPerformancescore7070[285];
extern double charPerformancescore7080[285];
extern double charPerformancescore7090[285];
extern double charPerformancescore800[285];
extern double charPerformancescore8010[285];
extern double charPerformancescore8020[285];
extern double charPerformancescore8030[285];
extern double charPerformancescore8040[285];
extern double charPerformancescore8050[285];
extern double charPerformancescore8060[285];
extern double charPerformancescore8070[285];
extern double charPerformancescore8080[285];
extern double charPerformancescore8090[285];
extern double charPerformancescore900[285];
extern double charPerformancescore9010[285];
extern double charPerformancescore9020[285];
extern double charPerformancescore9030[285];
extern double charPerformancescore9040[285];
extern double charPerformancescore9050[285];
extern double charPerformancescore9060[285];
extern double charPerformancescore9070[285];
extern double charPerformancescore9080[285];
extern double charPerformancescore9090[285];
extern double charPerformancescore1000[285];
extern double charPerformancescore10010[285];
extern double charPerformancescore10020[285];
extern double charPerformancescore10030[285];
extern double charPerformancescore10040[285];
extern double charPerformancescore10050[285];
extern double charPerformancescore10060[285];
extern double charPerformancescore10070[285];
extern double charPerformancescore10080[285];
extern double charPerformancescore10090[285];
extern double charPerformancescore1100[285];
extern double charPerformancescore11010[285];
extern double charPerformancescore11020[285];
extern double charPerformancescore11030[285];
extern double charPerformancescore11040[285];
extern double charPerformancescore11050[285];
extern double charPerformancescore11060[285];
extern double charPerformancescore11070[285];
extern double charPerformancescore11080[285];
extern double charPerformancescore11090[285];
extern double charPerformancescore1200[285];
extern double charPerformancescore12010[285];
extern double charPerformancescore12020[285];
extern double charPerformancescore12030[285];
extern double charPerformancescore12040[285];
extern double charPerformancescore12050[285];
extern double charPerformancescore12060[285];
extern double charPerformancescore12070[285];
extern double charPerformancescore12080[285];
extern double charPerformancescore12090[285];
extern double charPerformancescore1300[285];
extern double charPerformancescore13010[285];
extern double charPerformancescore13020[285];
extern double charPerformancescore13030[285];
extern double charPerformancescore13040[285];
extern double charPerformancescore13050[285];
extern double charPerformancescore13060[285];
extern double charPerformancescore13070[285];
extern double charPerformancescore13080[285];
extern double charPerformancescore13090[285];
extern double charPerformancescore1400[285];
extern double charPerformancescore14010[285];
extern double charPerformancescore14020[285];
extern double charPerformancescore14030[285];
extern double charPerformancescore14040[285];
extern double charPerformancescore14050[285];
extern double charPerformancescore14060[285];
extern double charPerformancescore14070[285];
extern double charPerformancescore14080[285];
extern double charPerformancescore14090[285];
extern double charPerformancescore1500[285];
extern double charPerformancescore15010[285];
extern double charPerformancescore15020[285];
extern double charPerformancescore15030[285];
extern double charPerformancescore15040[285];
extern double charPerformancescore15050[285];
extern double charPerformancescore15060[285];
extern double charPerformancescore15070[285];
extern double charPerformancescore15080[285];
extern double charPerformancescore15090[285];
extern double charPerformancescore1600[285];
extern double charPerformancescore16010[285];
extern double charPerformancescore16020[285];
extern double charPerformancescore16030[285];
extern double charPerformancescore16040[285];
extern double charPerformancescore16050[285];
extern double charPerformancescore16060[285];
extern double charPerformancescore16070[285];
extern double charPerformancescore16080[285];
extern double charPerformancescore16090[285];
extern double charPerformancescore1700[285];
extern double charPerformancescore17010[285];
extern double charPerformancescore17020[285];
extern double charPerformancescore17030[285];
extern double charPerformancescore17040[285];
extern double charPerformancescore17050[285];
extern double charPerformancescore17060[285];
extern double charPerformancescore17070[285];
extern double charPerformancescore17080[285];
extern double charPerformancescore17090[285];
*/



