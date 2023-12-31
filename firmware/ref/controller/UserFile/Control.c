/*

                                                                                                
                                    ~*~~{~%~~(!!~u0~5~~~~~~!                                    
                              ~~~~~K~!~[!Nhn~!~~t~~~*~k{~~!~~~!!~~                              
                          !~C~~~~@@!~~,!~~~~        ~~~!~~S>d~>~~~~~~~                          
                        ~|De~~TE!~~~                        ;~Y~Z~~~A~~x                        
                    ~!~~~~.q!~            ]~!~3w`~L!              ~P~~~~,SZ~                    
                  ~d~~~K!~          x~Ga!>P~~!g~              ~~F~    ;#~ug~~!                  
                ~~~~~M~~          !p!~~!~~                  ~~~~~V~~M6  ~~~Z~T~~                
              f~!c?&!)        !}N~~!p~Z~                  ~M~=B~$~j3!?q.  ~\a2!~2Z              
            ~~H!k~          x~~~~~o~                    (~~y~q9~[jx~~~k~M~    ~x!}~"            
          ~~\~~~xc        ~Q~P!~\,                      ~~,~*~6~c\~~~~X~!!M!    ~~N~!]          
          !~~S0~        M~Z~K~z^            ~y0!      !l~!b1k~~~\~2!!~3~!~1[    ~~!~<-          
        ~~~A~~        ~~~.~~~!          ~!!~~$~>~!~~  ~T~~~!~~xA5i  ~@+~qW~R[3    S~cb~~        
      !~>!~~        2L(~Y~%~        ~MiK!!~!~~"x~~!~  ~?)~~!f!        !~~v~~~~      A~U~q!      
      o`~_~~      !~(DT~x~        d~~H~H~~~~~ON~!~  ~~~$~'!~            i!~Pd~!~    !j/~-~      
    ~*~:7~      ~~~~'8!~      bi~!~%w!uv~~=~~<s~~w  ~!57~p~w              ~~~~f~      i~~~!i    
    I~~(,F      #)YDq~~!    k~~qwm~f  4~~~fe~~_~J~  ~~!8~m                ?!~1~-      ~DK!!!    
    ~~~~'~    !~Q[~~~~~-    ~~~!      ~|~~A!~~~~    u~!~g!                  Tp!8~:      !R~j    
  ~~n~~~      ~!~~~~L7~~            ~~T!~~[~~W    !f~~D~                    Y~!(~~      ~~~~!l  
  ~)~!"P      @mO~~V~2~!          ~~~v!~~~!!K~    ~~E:$~                      ~@F8      G!~!p~  
  ~~~~!~      @jQ~~!M~~b~x~^!~~~~~~~~~~m~Bi+      R~~!:~~~~X!!                1~~!~!    ~4~~!9  
  !/!^~n      !~~!h~~~7!~~C-K~~!~~wT.~0!t~u~f~    ~~~~G^-~~~~j~!                (~iB    ~~~~~~  
  ~~~J        ~!~~~i~~~O~~r!~/'~~~~~~~~mG~~K~~    6|~)Q~~~+!~"~~                  V~      uA~!  
  ;;~~            =?]~~~~~  z!!~~!~~c~~~.~~~~~~~  !:~~~~<~~!_~y~~~                        ~/6~  
  ~V~~                      @!h%5~'~  y~!^{~?~~~~b~~~!!~~~~~~~~B~T                        !~$w  
  ~!~~                    V~f~H~~~    !~~~~~!~  ~~~~~$      1V~~!~~~                      S~~~  
  ~~~~~D                ~~g~~!~\      ~~z~!~.~  z~~E        ~~~U~sKu                    ~;!J~~  
  jI3~~~              C~JAv~8E        !3H!)(R!  n!!,          Pq~~0q~P                  1!!~!~  
  ~~~~~~              ~b~~~~          *0~~;~    !~~!            !!~!~!                  ~~!~~~  
  ~~4~~~            g~~rs2            {!!?~&    ~~~7            $~~x~~                  Yj!^!~  
    ~!V>~\                          6!~~~!      2.~d              ~~!~!!                ~~A!    
    >~t~~~                          ~R~#q~      ~!Vn              :!~~V~              ~b~~~~    
    D*~~-~                        ~!~~-Z        ?L                  ~!~(              Se~~~~    
      !k~~~8                    ~~J~~I          b~                  ~~~~~~          ~av+~+      
      \~~!~~                  t~'v&~            ~~                    ~~!~          !)~~~~      
        ~,^~~!              ~~!H^A              R~                    !*d@        ~~]~Y?        
          `~~c~~          !~~~h~                FL                    ~Q~f      Ke~3!Z          
          >~~~~~~~    ~=UrN+                    2^                    "~~~    ~S.~~~~R          
            A~~!~~  ~!!5                        !~                      !,    {~!~~~            
              ~~!=t~                            !A                          ~~~~~~              
                ~~>~~K:1                        ~~~~                    ~!~!~~<~                
                  ~~~~~k:9                      !ToE                  ~~~~~!~~                  
                    w~0~<h~~~~                  !~~~              ,~~~U~!I~}                    
                        1K~f</~~~:~~                        ~~~~!3~~c~<S                        
                          ~!~*K~B~]jL!!!U~~Q        t~V~8~~t~9~~~,~!~]                          
                              K~~k9~Yi~~~~!!~~L(!!~~~~@~~~~Jz~~~~~                              
                                    iv=~0`~~;X!<,~!p~~~~}~!"                                    


	本项目虽然开源，但请勿以任何形式将本项目进行打包售卖！！！
	
	硬件和结构地址：https://oshwhub.com/nokia82/super_balance

	无刷FOC平衡车性能演示视频：https://www.bilibili.com/video/BV1Ur4y1Z7RT/?spm_id_from=333.999.0.0&vd_source=bbf6a497ecef4bee87eacb92c812c613

	如果本代码对你有帮助，欢迎关注给UP点个关注，谢谢！
	If this code helps you, please follow us and give us a like. Thank you!
	
	哔哩哔哩、抖音、快手、西瓜、小红书 油管 ID：手工饭
	Bili Bili, Tiktok, Kwai, Watermelon, Little Red Book Tubing ID: 手工饭
	
	程序员最讨厌的两件事:1. 写注释,2. 别人不写注释！（有疑问可以进QQ群:125654683交流，暗号JLINK）
	The two things programmers hate most: 1. Write comments, 2. Others don't write comments！
*/

#include "app.h"

PID_Structure_t SpeedPID;
PID_Structure TurnPID;

PID_Structure UprightPID;
PID_Structure GyroAnglePID;

PID_Structure M1SpeedPID;
PID_Structure M2SpeedPID;

PID_Structure M1CurrentIdPID;
PID_Structure M1CurrentIqPID;

PID_Structure M2CurrentIdPID;
PID_Structure M2CurrentIqPID;

Encoder_t M1_Encoder;
Encoder_t M2_Encoder;

Car_t Car;

volatile union sFaultBitTypeDef FaultBit;


#define CurrentLimit  8.0f // 电流限制为8A，不建议大于8A

#define IqId 1.0f // 最大为1.0

#define UprightLimit 6000.0f // 直立最大输出 6000 度/秒
#define TurnLimit    3000.0f // 旋转最大输出 3000 度/秒
#define SpeedLimit   5000.0f // 速度最大输出 5000 度/秒

void parameters_Init(void) //
{
/*************************************************************/		
	SpeedPID.Kp = 1.25f; 
	SpeedPID.Ki = 0.002f; 
	SpeedPID.Kd = 0.0f;
	
	SpeedPID.Ki_Out = 0.0f;
	
	SpeedPID.Kp_Min = -SpeedLimit;
	SpeedPID.Kp_Max =  SpeedLimit;
	
	SpeedPID.Kd_Min = -SpeedLimit;
	SpeedPID.Kd_Max =  SpeedLimit;
	
	SpeedPID.Ki_Min = -SpeedLimit / SpeedPID.Ki;
	SpeedPID.Ki_Max =  SpeedLimit / SpeedPID.Ki;
	
	SpeedPID.outMin = -SpeedLimit / SpeedPID.Ki;
	SpeedPID.outMax =  SpeedLimit / SpeedPID.Ki;
	
	SpeedPID.PID_Out = 0.0f;
	SpeedPID.OutLimit = SpeedLimit;
	
/*************************************************************/	

/*************************************************************/	
	TurnPID.Kp = 1.0f;
	TurnPID.Ki = 0.0f;
	TurnPID.Kd = 5.0f;
	
	TurnPID.Ki_Out = 0.0f; 
	
	TurnPID.Kp_Min = -TurnLimit;
	TurnPID.Kp_Max =  TurnLimit;
	
	TurnPID.Kd_Min = -TurnLimit;
	TurnPID.Kd_Max =  TurnLimit;
	
	TurnPID.Ki_Min = -TurnLimit; 
	TurnPID.Ki_Max =  TurnLimit;
	
	TurnPID.outMin = -TurnLimit;
	TurnPID.outMax =  TurnLimit;
	
	TurnPID.PID_Out = 0.0f;
/*************************************************************/

/*************************************************************/		
	UprightPID.Kp = 80.0f;
	UprightPID.Ki = 0.0f;   
	UprightPID.Kd = 15.0f;  
	
	UprightPID.Ki_Out = 0.0f;
	
	UprightPID.Kp_Min = -UprightLimit;
	UprightPID.Kp_Max =  UprightLimit;
	
	UprightPID.Kd_Min = -UprightLimit;
	UprightPID.Kd_Max =  UprightLimit;
	
	UprightPID.Ki_Min = -UprightLimit;
	UprightPID.Ki_Max =  UprightLimit;
	
	UprightPID.outMin = -UprightLimit;
	UprightPID.outMax =  UprightLimit;
	
	UprightPID.PID_Out = 0.0f;
/*************************************************************/	

/*************************************************************/	
	M1SpeedPID.Kp = 0.005f; 
	M1SpeedPID.Ki = M1SpeedPID.Kp / 50.0f; 
	M1SpeedPID.Kd = 0.0f;
	
	M1SpeedPID.Ki_Out = 0.0f;
	
	M1SpeedPID.Kp_Min = -CurrentLimit;
	M1SpeedPID.Kp_Max =  CurrentLimit;
	
	M1SpeedPID.Kd_Min = -CurrentLimit;
	M1SpeedPID.Kd_Max =  CurrentLimit;
	
	M1SpeedPID.Ki_Min = -CurrentLimit;
	M1SpeedPID.Ki_Max =  CurrentLimit;
	
	M1SpeedPID.outMin = -CurrentLimit;
	M1SpeedPID.outMax =  CurrentLimit;
	
	M1SpeedPID.PID_Out = 0.0f;
/*************************************************************/		
	M2SpeedPID.Kp = 0.005f; 
	M2SpeedPID.Ki = M2SpeedPID.Kp / 50.0f; 
	M2SpeedPID.Kd = 0.0f;
	
	M2SpeedPID.Ki_Out = 0.0f;
	
	M2SpeedPID.Kp_Min = -CurrentLimit;
	M2SpeedPID.Kp_Max =  CurrentLimit;
	
	M2SpeedPID.Kd_Min = -CurrentLimit;
	M2SpeedPID.Kd_Max =  CurrentLimit;
	
	M2SpeedPID.Ki_Min = -CurrentLimit; 
	M2SpeedPID.Ki_Max =  CurrentLimit;
	
	M2SpeedPID.outMin = -CurrentLimit;
	M2SpeedPID.outMax =  CurrentLimit;
	
	M2SpeedPID.PID_Out = 0.0f;
/*************************************************************/	

/*************************************************************/		
	M1CurrentIdPID.Kp = 0.005f; 
	M1CurrentIdPID.Ki = M1CurrentIdPID.Kp / 10.0f;
	M1CurrentIdPID.Kd = 0.0f;
	
	M1CurrentIdPID.Ki_Out = 0.0f; 
	
	M1CurrentIdPID.Kp_Min = -IqId/2.0f;
	M1CurrentIdPID.Kp_Max =  IqId/2.0f;
	
	M1CurrentIdPID.Kd_Min = -IqId/2.0f;
	M1CurrentIdPID.Kd_Max =  IqId/2.0f;
	
	M1CurrentIdPID.Ki_Min = -IqId/2.0f; 
	M1CurrentIdPID.Ki_Max =  IqId/2.0f;
	
	M1CurrentIdPID.outMin = -IqId/2.0f;
	M1CurrentIdPID.outMax =  IqId/2.0f;
	
	M1CurrentIdPID.PID_Out = 0.0f;
/*************************************************************/		
	M1CurrentIqPID.Kp = 0.01f; 
	M1CurrentIqPID.Ki = M1CurrentIqPID.Kp / 10.0f;
	M1CurrentIqPID.Kd = 0.0f;
	
	M1CurrentIqPID.Ki_Out = 0.0f; 
	
	M1CurrentIqPID.Kp_Min = -IqId;
	M1CurrentIqPID.Kp_Max =  IqId;
	
	M1CurrentIqPID.Kd_Min = -IqId;
	M1CurrentIqPID.Kd_Max =  IqId;
	
	M1CurrentIqPID.Ki_Min = -IqId; 
	M1CurrentIqPID.Ki_Max =  IqId;
	
	M1CurrentIqPID.outMin = -IqId;
	M1CurrentIqPID.outMax =  IqId;
	
	M1CurrentIqPID.PID_Out = 0.0f;
/*************************************************************/		

/*************************************************************/		
	M2CurrentIdPID.Kp = 0.005f; 
	M2CurrentIdPID.Ki = M2CurrentIdPID.Kp / 10.0f;
	M2CurrentIdPID.Kd = 0.0f;
	
	M2CurrentIdPID.Ki_Out = 0.0f; 
	
	M2CurrentIdPID.Kp_Min = -IqId/2.0f;
	M2CurrentIdPID.Kp_Max =  IqId/2.0f;
	
	M2CurrentIdPID.Kd_Min = -IqId/2.0f;
	M2CurrentIdPID.Kd_Max =  IqId/2.0f;
	
	M2CurrentIdPID.Ki_Min = -IqId/2.0f; 
	M2CurrentIdPID.Ki_Max =  IqId/2.0f;
	
	M2CurrentIdPID.outMin = -IqId/2.0f;
	M2CurrentIdPID.outMax =  IqId/2.0f;
	
	M2CurrentIdPID.PID_Out = 0.0f;
/*************************************************************/		
	M2CurrentIqPID.Kp = 0.01f; 
	M2CurrentIqPID.Ki = M2CurrentIqPID.Kp / 10.0f;
	M2CurrentIqPID.Kd = 0.0f;
	
	M2CurrentIqPID.Ki_Out = 0.0f;
	
	M2CurrentIqPID.Kp_Min = -IqId;
	M2CurrentIqPID.Kp_Max =  IqId;
	
	M2CurrentIqPID.Kd_Min = -IqId;
	M2CurrentIqPID.Kd_Max =  IqId;
	
	M2CurrentIqPID.Ki_Min = -IqId;
	M2CurrentIqPID.Ki_Max =  IqId;
	
	M2CurrentIqPID.outMin = -IqId;
	M2CurrentIqPID.outMax =  IqId;
	
	M2CurrentIqPID.PID_Out = 0.0f;
/*************************************************************/	

  Car.Sensitivity = 20.0f; //默认遥控手感
	Car.Protect_flag = 1;
	Car.BatVin_filter = 8.2f;
}

float ControlOut_L = 0.0f,ControlOut_R = 0.0f;

u8 CarSpeedCnt = 0;

float testfloat = 45.0f;
	
void MotorControl(void) 
{
	if(fabs(mpu6500.gyroAngle.y) < testfloat)
	{
		if(Car.AutoStandUp == 1)
		{
			Car.AutoStandUp = 0;
			testfloat = 2.0f;
			Car.Protect_flag = 0;
		}
		
		Car.Protect = 1;
		
		if(Car.Protect_flag == 1) // 如果是保护模式
		{
			if(fabsf(mpu6500.gyro.filter.x) < 1.5f && fabsf(mpu6500.gyro.filter.y) < 1.5f && fabsf(mpu6500.gyro.filter.z) < 5.0f) // 检测陀螺角速度和小车姿态
			{
				if(++Car.ProtectCnt >= 100) // 等待100次
				{
					Car.ProtectCnt = 0;
					Car.Protect_flag = 0; // 进入平衡
					M1_Foc.Cali_Status = 0;
					M2_Foc.Cali_Status = 0;
				}
			}
			else Car.ProtectCnt = 0;
		}
	}
	
	if(Car.Protect_flag == 0 && Car.PowerFlag == 1) 
	{
		if(++CarSpeedCnt >= 2) // 2ms闭环一次
		{
			CarSpeedCnt = 0;	
			if(Car.Protect == 1)
			{					
				Car.Speed = (M1_Encoder.Speed_filterA - M2_Encoder.Speed_filterA); // 获小车速度
				
				if(Rc.z_flag == 0) // 增强手感
				{
					TurnPID.Kd = 10.0f; 
				}
				else if(Rc.z_flag == 1) // 默认手感
				{
					TurnPID.Kd = 5.0f; 
				}
				
				Car.ControlY = Rc.x*Car.Sensitivity; // 前后控制量
				Car.ControlZ = Rc.z*Car.Sensitivity; // 旋转控制量
				
				if(fabsf(M1_Encoder.Speed_filterA) > 3600.0f || fabsf(M2_Encoder.Speed_filterA) > 3600.0f) // 小车车轮转速达到3600度/秒
				{
					if(Rc.x_flag == 0 && Rc.z_flag == 0) // 如果遥控器没有控制
					{
						if(mpu6500.acc.filter.z > 1.01f)Car.Protect_flag = 1; // 如果检测到小车被拿起则进入保护模式
					}
				}

				PID_Adjust_S(&SpeedPID,0.0f,Car.Speed,Car.ControlY);           // 小车速度环
				PID_Adjust_T(&TurnPID,Car.ControlZ,0.0f,mpu6500.gyro.Primitive.z);  // 小车旋转环
			}
		}		
		PID_Adjust_T(&UprightPID,0.0f,-mpu6500.gyroAngle.y,mpu6500.gyro.Primitive.y);  // 小车直立环+陀螺角度
		ControlOut_L = UprightPID.PID_Out + SpeedPID.PID_Out + TurnPID.PID_Out;  // 输出电机速度控制量
		ControlOut_R = UprightPID.PID_Out + SpeedPID.PID_Out - TurnPID.PID_Out;  // 输出电机速度控制量
	}
	else if(Car.Protect_flag == 1) // 保护模式电机停转
	{
		if(Car.AutoStandUp == 1) //直接控制电机转速进行起立后闭环，需要注意的是轮胎与地面摩擦力一定要足够大，要不然会打滑并发生意想不到的情况
		{
			if(mpu6500.gyroAngle.y > 0.0f && mpu6500.gyroAngle.y < 175.0f)
			{
				ControlOut_L = 3600.0f;
				ControlOut_R = 3600.0f;
			}
			else if(mpu6500.gyroAngle.y < 0.0f && mpu6500.gyroAngle.y > -175.0f)
			{
				ControlOut_L = -3600.0f;
				ControlOut_R = -3600.0f;
			}
			else // 如果小车是倒立水平放置，则加大电机速度提高反扭力保证小车能顺利起立
			{
				ControlOut_L = 7200.0f;
				ControlOut_R = 7200.0f;
			}
			M1_Foc.Cali_Status = 0;
			M2_Foc.Cali_Status = 0;
		}
		else if(Car.AutoStandUp == 0)
		{
			ControlOut_L = 0.0f;
			ControlOut_R = 0.0f;
			
			if(fabsf(ControlOut_L) < 5.0f && fabsf(ControlOut_R) < 5.0f) // 转速小于5
			{
				M1_Foc.Cali_Status = 2; // 电机进入停止
				M2_Foc.Cali_Status = 2; // 电机进入停止
			}
			
			Car.Speed = 0.0f;
			Car.Protect = 0;

			testfloat = 10.0f;
			
			M1_Encoder.Spd_Offset_Flag = 0;
			M2_Encoder.Spd_Offset_Flag = 0;
			
			UprightPID.Ki_Out = 0.0f;
			UprightPID.PID_Out = 0.0f;
			
			SpeedPID.Ki_Out = 0.0f;
			SpeedPID.PID_Out = 0.0f;
			
			TurnPID.Ki_Out =  0.0f;
			TurnPID.PID_Out = 0.0f;
			
			M1_Encoder.Speed_filterA = 0.0f;
			M2_Encoder.Speed_filterA = 0.0f;			
		}			
	}
	
	if(FaultBit.bit.IMU == 1) // IMU错误
	{
		ControlOut_L = 0.0f;
		ControlOut_R = 0.0f;
		M1_Foc.Cali_Status = 2; // 电机进入停止
		M2_Foc.Cali_Status = 2; // 电机进入停止
	}
}

u8 M1SpeedCnt = 0;
u8 M2SpeedCnt = 0;

void M1_Control(void)
{
	if(M1_Foc.Cali_Status == 0) // 正常闭环
	{
		M1SpeedControl(-ControlOut_L);
		M1Current_ClosedLoop(M1SpeedPID.PID_Out);
	}
	else if(M1_Foc.Cali_Status == 2) // 电机停止
	{
		M1_Foc.Vd = 0.0f;	
		M1_Foc.Vq = 0.0f;	
	}
	else if(M1_Foc.Cali_Status == 1) // 电机校准后转动
	{
		M1SpeedControl(600.0f);
		M1Current_ClosedLoop(M1SpeedPID.PID_Out);
	}
	else if(M1_Foc.Cali_Status == 3) //计算速度
	{
		if(++M1SpeedCnt >= 2) 
		{
			M1SpeedCnt = 0;
			SpeedCompute(&M1_Encoder,M1_Foc.Encoder_data);
		}
	}
}

void M2_Control(void) 
{
	if(M2_Foc.Cali_Status == 0) // 正常闭环
	{
		M2SpeedControl(ControlOut_R);
		M2Current_ClosedLoop(M2SpeedPID.PID_Out);
	}
	else if(M2_Foc.Cali_Status == 2) // 电机停止
	{
		M2_Foc.Vd = 0.0f;	
		M2_Foc.Vq = 0.0f;	
	}
	else if(M2_Foc.Cali_Status == 1) // 电机校准后转动
	{
		M2SpeedControl(600.0f);
		M2Current_ClosedLoop(M2SpeedPID.PID_Out);
	}
	else if(M2_Foc.Cali_Status == 3) //计算速度
	{
		if(++M2SpeedCnt >= 2)
		{
			M2SpeedCnt = 0;
			SpeedCompute(&M2_Encoder,M2_Foc.Encoder_data);
		}
	}
}

void SpeedCompute(Encoder_t* Speed, uint16_t Encoder_data) // 计算速度
{
	Speed->data = Encoder_data;
	if(Speed->Spd_Offset_Flag == 0)
	{
		Speed->Spd_Offset_Flag = 1;
		Speed->UpData = Speed->data;
	}
	if(Speed->UpData > 32000 && Speed->data < 768)
	{
		Speed->DiffeData = (int32_t)(32768  + Speed->data) - Speed->UpData;
	} 
	else if(Speed->UpData < 768 && Speed->data > 32000)
	{
		Speed->DiffeData = - ((int32_t)(32768  - Speed->data) + Speed->UpData);
	}
	else
	{
		Speed->DiffeData = Speed->data - Speed->UpData;
	}
	Speed->UpData = Speed->data;
	
	Speed->Speed = (Speed->DiffeData * 0.010986328125f)/0.0002f;
	Speed->Speed_filter += (Speed->Speed - Speed->Speed_filter) * 0.25f;
	Speed->Speed_filterA += (Speed->Speed_filter - Speed->Speed_filterA) * 0.025f;
}

void M1SpeedControl(float speed) // 速度环 200us
{
	if(++M1SpeedCnt >= 2) 
	{
		M1SpeedCnt = 0;
		SpeedCompute(&M1_Encoder,M1_Foc.Encoder_data);
		PID_Adjust(&M1SpeedPID,speed,M1_Encoder.Speed_filter);	
	}
}

void M1Current_ClosedLoop(float Current) // 电流环 100us
{
	PID_Adjust(&M1CurrentIdPID,0.0f,M1_Foc.Id);
	M1_Foc.Vd = M1CurrentIdPID.PID_Out;	
	
	PID_Adjust(&M1CurrentIqPID,Current,M1_Foc.Iq);
	M1_Foc.Vq = M1CurrentIqPID.PID_Out;
}

void M2SpeedControl(float speed) // 速度环 200us
{
	if(++M2SpeedCnt >= 2) 
	{
		M2SpeedCnt = 0;
		SpeedCompute(&M2_Encoder,M2_Foc.Encoder_data);
		PID_Adjust(&M2SpeedPID,speed,M2_Encoder.Speed_filter);	
	}
}

void M2Current_ClosedLoop(float Current) // 电流环 100us
{
	PID_Adjust(&M2CurrentIdPID,0.0f,M2_Foc.Id);
	M2_Foc.Vd = M2CurrentIdPID.PID_Out;	
	
	PID_Adjust(&M2CurrentIqPID,Current,M2_Foc.Iq);
	M2_Foc.Vq = M2CurrentIqPID.PID_Out;
}

float PID_Adjust_T(PID_Structure* handle,float Given,float Feedback,float Gyro)
{
	float Error_value;

	float P_Out;
	float D_Out;
	
	Error_value = Given - Feedback;
	
	P_Out = Error_value * handle->Kp;
	handle->Ki_Out += Error_value * handle->Ki;
	D_Out = Gyro * handle->Kd; 
	
	if(P_Out < handle->Kp_Min)P_Out = handle->Kp_Min; 
	else if(P_Out > handle->Kp_Max)P_Out = handle->Kp_Max;
	
	if(handle->Ki_Out < handle->Ki_Min)handle->Ki_Out = handle->Ki_Min;
	else if(handle->Ki_Out > handle->Ki_Max)handle->Ki_Out = handle->Ki_Max;
  
	if(D_Out < handle->Kd_Min)D_Out = handle->Kd_Min; 
	else if(D_Out > handle->Kd_Max)D_Out = handle->Kd_Max;
	
	handle->PID_Out = P_Out + handle->Ki_Out + D_Out;
	
	if(handle->PID_Out > handle->outMax)
	{
    handle->PID_Out = handle->outMax;
	}
  else if(handle->PID_Out < handle->outMin)
	{
    handle->PID_Out = handle->outMin;
	}
	return handle->PID_Out;
}

float PID_Adjust(PID_Structure* handle,float Given,float Feedback)
{
	float Error_value;

	float P_Out;
	
	Error_value = Given - Feedback;
	
	P_Out = Error_value * handle->Kp;
	handle->Ki_Out += Error_value * handle->Ki;

	if(P_Out < handle->Kp_Min)P_Out = handle->Kp_Min; 
	else if(P_Out > handle->Kp_Max)P_Out = handle->Kp_Max;
	
	if(handle->Ki_Out < handle->Ki_Min)handle->Ki_Out = handle->Ki_Min;
	else if(handle->Ki_Out > handle->Ki_Max)handle->Ki_Out = handle->Ki_Max;
	
	handle->PID_Out = P_Out + handle->Ki_Out;
	
	if(handle->PID_Out > handle->outMax)
	{
    handle->PID_Out = handle->outMax;
	}
  else if(handle->PID_Out < handle->outMin)
	{
    handle->PID_Out = handle->outMin;
	}
	return handle->PID_Out;
}


