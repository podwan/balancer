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

mpu6500_t mpu6500;

/**************************************************************************************************/
u8 IMU_data[14];

/**************************************************************************
**************************************************************************/

u8 IMU_flag = 0;

void IMU_handle(void) // 姿态计算
{
	Get_mpu6500(IMU_data);	//获取mpu6500数据
	
	mpu6500.acc.data.x = ((IMU_data[0]<<8)|IMU_data[1]);
	mpu6500.acc.data.y = ((IMU_data[2]<<8)|IMU_data[3]);
	mpu6500.acc.data.z = ((IMU_data[4]<<8)|IMU_data[5]);

	mpu6500.gyro.data.x = ((IMU_data[8]<<8)|IMU_data[9]);
	mpu6500.gyro.data.y = ((IMU_data[10]<<8)|IMU_data[11]);
	mpu6500.gyro.data.z = ((IMU_data[12]<<8)|IMU_data[13]);
	
	if(mpu6500.Cali_Flag == 1) // 温补已经校准
	{	
		if(mpu6500.Offset_Flag == 0)
		{
			mpu6500.Offset_Flag = 1;
			mpu6500.gyro.filter.x = mpu6500.gyro.Primitive.x;
			mpu6500.gyro.filter.y = mpu6500.gyro.Primitive.y;
			mpu6500.gyro.filter.z = mpu6500.gyro.Primitive.z;
			
			mpu6500.acc.Initial.x = mpu6500.acc.data.x;
			mpu6500.acc.Initial.y = mpu6500.acc.data.y;
			mpu6500.acc.Initial.z = mpu6500.acc.data.z;
		}
		
		mpu6500.gyro.Primitive.x = (float)mpu6500.gyro.data.x/16.4f - mpu6500.gyro.offset.x; // 换算成 度/秒
		mpu6500.gyro.Primitive.y = (float)mpu6500.gyro.data.y/16.4f - mpu6500.gyro.offset.y;
		mpu6500.gyro.Primitive.z = (float)mpu6500.gyro.data.z/16.4f - mpu6500.gyro.offset.z;	
			
		mpu6500.gyro.filter.x += (mpu6500.gyro.Primitive.x - mpu6500.gyro.filter.x) * 0.5f; // 滤波
		mpu6500.gyro.filter.y += (mpu6500.gyro.Primitive.y - mpu6500.gyro.filter.y) * 0.5f;
		mpu6500.gyro.filter.z += (mpu6500.gyro.Primitive.z - mpu6500.gyro.filter.z) * 0.5f;
		
		mpu6500.acc.Primitive.x = (float)mpu6500.acc.data.x/4096.0f; // 换算成 度/秒
		mpu6500.acc.Primitive.y = (float)mpu6500.acc.data.y/4096.0f;
		mpu6500.acc.Primitive.z = (float)mpu6500.acc.data.z/4096.0f;	
			
		mpu6500.acc.filter.x += (mpu6500.acc.Primitive.x - mpu6500.acc.filter.x) * 0.01f; // 滤波
		mpu6500.acc.filter.y += (mpu6500.acc.Primitive.y - mpu6500.acc.filter.y) * 0.01f;
		mpu6500.acc.filter.z += (mpu6500.acc.Primitive.z - mpu6500.acc.filter.z) * 0.01f;
	}
	else if(mpu6500.Cali_Flag == 0) 
	{	
		if(mpu6500.Offset_Flag == 0)
		{
			mpu6500.Offset_Flag = 1;
			mpu6500.gyro.filter.x = mpu6500.gyro.Primitive.x;
			mpu6500.gyro.filter.y = mpu6500.gyro.Primitive.y;
			mpu6500.gyro.filter.z = mpu6500.gyro.Primitive.z;
			
			mpu6500.acc.Initial.x = mpu6500.acc.data.x;
			mpu6500.acc.Initial.y = mpu6500.acc.data.y;
			mpu6500.acc.Initial.z = mpu6500.acc.data.z;
		}
		
		mpu6500.gyro.Primitive.x = (float)mpu6500.gyro.data.x/16.4f; // 换算成 度/秒
		mpu6500.gyro.Primitive.y = (float)mpu6500.gyro.data.y/16.4f;
		mpu6500.gyro.Primitive.z = (float)mpu6500.gyro.data.z/16.4f;	
			
		mpu6500.gyro.filter.x += (mpu6500.gyro.Primitive.x - mpu6500.gyro.filter.x) * 0.05f; // 滤波
		mpu6500.gyro.filter.y += (mpu6500.gyro.Primitive.y - mpu6500.gyro.filter.y) * 0.05f;
		mpu6500.gyro.filter.z += (mpu6500.gyro.Primitive.z - mpu6500.gyro.filter.z) * 0.05f;
		
		mpu6500.acc.Primitive.x = (float)mpu6500.acc.data.x/4096.0f; // 换算成 度/秒
		mpu6500.acc.Primitive.y = (float)mpu6500.acc.data.y/4096.0f;
		mpu6500.acc.Primitive.z = (float)mpu6500.acc.data.z/4096.0f;	
			
		mpu6500.acc.filter.x += (mpu6500.acc.Primitive.x - mpu6500.acc.filter.x) * 0.01f; // 滤波
		mpu6500.acc.filter.y += (mpu6500.acc.Primitive.y - mpu6500.acc.filter.y) * 0.01f;
		mpu6500.acc.filter.z += (mpu6500.acc.Primitive.z - mpu6500.acc.filter.z) * 0.01f;
	}
  
	mpu6500.accAngle.y = -atan2f(mpu6500.acc.filter.x,mpu6500.acc.filter.z) * 57.2957795f;  //计算加速度倾角
	
	if(IMU_flag == 0) // 使用加速度计算的姿态角赋初值
	{
		IMU_flag = 1;
		mpu6500.gyroAngle.y = mpu6500.accAngle.y;
	}
	
	if(fabsf(mpu6500.accAngle.y) > 90.0f) 
	{
		mpu6500.gyroAngle.y = mpu6500.accAngle.y;
	}
	else
	{
		mpu6500.gyroAngle.y += mpu6500.gyro.Primitive.y * 0.001f; // 角速度积分
	  mpu6500.gyroAngle.y = mpu6500.gyroAngle.y * 0.999f + mpu6500.accAngle.y * 0.001f; // 陀螺积分角度与加速度倾角进行融合
		
		mpu6500.gyroAngle.z += mpu6500.gyro.Primitive.z * 0.001f; // 角速度积分，暂未使用
		if(mpu6500.gyroAngle.z > 180.0f)mpu6500.gyroAngle.z -= 360.0f;	
	  else if(mpu6500.gyroAngle.z < -180.0f)mpu6500.gyroAngle.z += 360.0f;	
	}
}


