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

u16 Sbus_values[12];
u8 Sbus_Data[32];

s16 CH0 = 1024;//352 - 1024 - 1696
s16 CH1 = 1024;//352 - 1024 - 1696 
s16 CH2 = 0;
s16 CH3 = 0;

RC_t Rc;

u16 BLE_Cnt = 0;
uint8_t Rc_flag = 0;

void RcData(void)
{
  if(U2_IDLE_Flag == 1)
  {
    if(Sbus_Data[0] == 0x0f && Sbus_Data[25] == 0x00) // FUTABA航模SBUS接收机通道解析
		{
//			CH1=Sbus_buff[1]|((Sbus_buff[2]&0x07)<<8);
//			CH0=((Sbus_Data[3]&0x3f)<<5)|((Sbus_Data[2]&0xf8)>>3);
//			Sbus_values[2]=((Sbus_buff[5]&0x01)<<10)|Sbus_buff[4]<<2|((Sbus_buff[3]&0xc0)>>6);
//			CH1=((Sbus_Data[6]&0x0f)<<7)|((Sbus_Data[5]&0xfe)>>1);
//			CH2 = ((Sbus_Data[7]&0x7f)<<4)|((Sbus_Data[6]&0xf0)>>4);
//			Sbus_values[4]=((Sbus_buff[7]&0x7f)<<4)|((Sbus_buff[6]&0xf0)>>4);
//			Sbus_values[5]=((Sbus_buff[9]&0x03)<<9)|Sbus_buff[8]<<1|((Sbus_buff[7]&0x80)>>7);
//			Sbus_values[6]=((Sbus_buff[10]&0x1f)<<6)|((Sbus_buff[9]&0xfc)>>2);	
//			Sbus_values[7]=(Sbus_buff[11]<<3)|((Sbus_buff[10]&0xe0)>>5);	
//			Sbus_values[8]=Sbus_buff[12]|((Sbus_buff[13]&0x07)<<8);
//			Sbus_values[9]=((Sbus_buff[14]&0x3f)<<5)|((Sbus_buff[13]&0xf8)>>3);
//			Sbus_values[10]=((Sbus_buff[16]&0x01)<<10)|Sbus_buff[15]<<2|((Sbus_buff[14]&0xc0)>>6);
//			Sbus_values[11]=((Sbus_buff[17]&0x0f)<<7)|((Sbus_buff[16]&0xfe)>>1);
			Sbus_Data[0] = 0;
		}
		U2_IDLE_Flag = 0;
	}
	
	if(U4_IDLE_Flag == 1) // 接收到串口4数据
  {
		U4_IDLE_Flag = 0;
		UART4_SendDataDMA(Get_usart4_data,8); // 把收到的前8个数据发出去
	}
	
	if(U1_IDLE_Flag == 1)
  {
		U1_IDLE_Flag = 0;
		BLE_Cnt = 0;
    if(Get_usart1_data[0] == 0x20 && Get_usart1_data[1] == 0x0f && Get_usart1_data[14] == 0x02) // 游戏手柄控制数据
		{
			if(Get_usart1_data[10] > 250)
			{
				Car.Protect_flag = 1;
				Car.AutoStandUp = 0;// 终止一键起立
			}
			
			if(Get_usart1_data[11] > 250 && Rc_flag == 0)
			{
				Rc_flag = 1;
				if(Car.Rc_Mode == 0)
				{
					Car.Rc_Mode = 1; 
				}
				else if(Car.Rc_Mode == 1)
				{
					Car.Rc_Mode = 0;
				}
			}
			else if(Get_usart1_data[11] < 10)Rc_flag = 0;
				
			Rc.ch0 = (Get_usart1_data[4] - 128); // = +- 128 
	
			if(Car.Rc_Mode == 1)Rc.ch1 = (Get_usart1_data[3] - 128); 
			else Rc.ch1 = (Get_usart1_data[5] - 128);
			
			if(Get_usart1_data[8] == 2 && CH2 == 0)
			{
				CH2 = 3;
			}
      else if(Get_usart1_data[8] != 2 && CH2 == 3)
			{
				CH2 = 0;
				if(Rc.ch2 == 0)Rc.ch2 = 1; else if(Rc.ch2 == 1)Rc.ch2 = 0;
			}
			else if(Get_usart1_data[8] == 4 && CH3 == 0)  // 左 0x04 右 0x08
			{
				CH3 = 3;
			}
			else if(Get_usart1_data[8] != 4 && CH3 == 3)
			{
				CH3 = 0;
				if(Car.Sensitivity < 25.0f) 
				{
					Car.Sensitivity = 40.0f; 
//					B_LED_Status(1);
				}
				else if(Car.Sensitivity > 25.0f)
				{
					Car.Sensitivity = 20.0f;
//					B_LED_Status(0);
				}
			}
			else if(Get_usart1_data[8] == 1)
			{
				TMR10->c1dt = 200;
				if(Car.AutoStandUp == 0)Car.AutoStandUp = 1;
				
//				if(Car.Protect_flag > 0)
//				{
//					Car.Protect_flag = 0;
//					M1_Foc.Cali_Status = 0;
//					M2_Foc.Cali_Status = 0;
//				}
			}
			else TMR10->c1dt = 0;
			
			if(abs(Rc.ch0) < 8)
			{
				Rc.ch0 = 0; 
				Rc.x += (Rc.ch0 - Rc.x) * 0.1f;
				if(fabs(Rc.x) < 0.0001f)
				{
					Rc.x = 0.0f;
					Rc.x_flag = 0;
				}
			}
			else if(Rc.ch0 > 8)
			{
				Rc.ch0 -= 8;
				Rc.x += (Rc.ch0 - Rc.x) * 0.05f;
				Rc.x_flag = 1;
			}
			else if(Rc.ch0 < -8)
			{
				Rc.ch0 += 8;
				Rc.x += (Rc.ch0 - Rc.x) * 0.05f;
				Rc.x_flag = 1;
			}
			
			if(abs(Rc.ch1) < 8)
			{
				Rc.ch1 = 0; 
				Rc.z += (Rc.ch1 - Rc.z) * 0.1f;
				if(fabs(Rc.z) < 0.0001f)
				{
					Rc.z = 0.0f;
					Rc.z_flag = 0;
				}
			}
			else if(Rc.ch1 > 8)
			{
				Rc.ch1 -= 8;
				Rc.z += (Rc.ch1 - Rc.z) * 0.05f;
				Rc.z_flag = 1;
			}
			else if(Rc.ch1 < -8)
			{
				Rc.ch1 += 8;
				Rc.z += (Rc.ch1 - Rc.z) * 0.05f;
				Rc.z_flag = 1;
			}
		}
		else if(Get_usart1_data[0] == 0x20 && Get_usart1_data[1] == 0x0f && Get_usart1_data[14] == 0x66) // 小程序控制数据
		{
			Rc.ch0 = Get_usart1_data[5]; // = +- 100 
			Rc.ch1 = Get_usart1_data[4];
      Rc.ch2 = Get_usart1_data[2];
			
			if(Get_usart1_data[8] == 2 && CH2 == 0)
			{
				CH2 = 3;
			}
      else if(Get_usart1_data[8] != 2 && CH2 == 3)
			{
				CH2 = 0;
			}
			else if(Get_usart1_data[8] == 4 && CH3 == 0)
			{
				CH3 = 3;
			}
			else if(Get_usart1_data[8] != 4 && CH3 == 3)
			{
				CH3 = 0;
				if(Car.Sensitivity < 10.0f) 
				{
					Car.Sensitivity = 12.0f; 
					B_LED(1);
				}
				else if(Car.Sensitivity > 10.0f)
				{
					Car.Sensitivity = 8.0f;
					B_LED(0);
				}
			}
			else if(Get_usart1_data[8] == 1)
			{
				TMR10->c1dt = 200;
				if(Car.Protect_flag > 0)
				{
					Car.Protect_flag = 0;
					M1_Foc.Cali_Status = 0;
					M2_Foc.Cali_Status = 0;
				}
			}
			else TMR10->c1dt = 0;
			
			if(abs(Rc.ch0) < 5)
			{
				Rc.ch0 = 0; 
				Rc.x += (Rc.ch0 - Rc.x) * 0.1f;
				if(fabs(Rc.x) < 0.001f)
				{
					Rc.x = 0.0f;
					Rc.x_flag = 0;
				}
			}
			else if(Rc.ch0 > 5)
			{
				Rc.ch0 -= 5;
				Rc.x += (Rc.ch0 - Rc.x) * 0.5f;
				Rc.x_flag = 1;
			}
			else if(Rc.ch0 < -5)
			{
				Rc.ch0 += 5;
				Rc.x += (Rc.ch0 - Rc.x) * 0.5f;
				Rc.x_flag = 1;
			}
			
			if(abs(Rc.ch1) < 25)
			{
				Rc.ch1 = 0; 
				Rc.z += (Rc.ch1 - Rc.z) * 0.1f;
				if(fabs(Rc.z) < 0.001f)
				{
					Rc.z = 0.0f;
					Rc.z_flag = 0;
				}
			}
			else if(Rc.ch1 > 25)
			{
				Rc.ch1 -= 25;
				Rc.z += (Rc.ch1 - Rc.z) * 0.5f;
				Rc.z_flag = 1;
			}
			else if(Rc.ch1 < -25)
			{
				Rc.ch1 += 25;
				Rc.z += (Rc.ch1 - Rc.z) * 0.5f;
				Rc.z_flag = 1;
			}
		}
		Get_usart1_data[0] = Get_usart1_data[1] = 0;
	}
	else
	{
		if(++BLE_Cnt >= 150)
		{
			BLE_Cnt = 500;
			if(Rc.ch0 > 0)
			{
				Rc.ch0--;
			  if(Rc.ch0 < 0)Rc.ch0 = 0; 
			}
			else if(Rc.ch0 < 0)
			{
				Rc.ch0++;
			  if(Rc.ch0 > 0)Rc.ch0 = 0; 
			}
			
			Rc.x += (Rc.ch0 - Rc.x) * 0.01f;
			if(fabs(Rc.x) < 0.0001f)
			{
				Rc.x = 0.0f;
				Rc.x_flag = 0;
			}
			
			if(Rc.ch1 > 0)
			{
				Rc.ch1--;
			  if(Rc.ch0 < 0)Rc.ch1 = 0; 
			}
			else if(Rc.ch1 < 0)
			{
				Rc.ch1++;
			  if(Rc.ch1 > 0)Rc.ch1 = 0; 
			}
			Rc.z += (Rc.ch1 - Rc.z) * 0.01f;
			if(fabs(Rc.z) < 0.0001f)
			{
				Rc.z = 0.0f;
				Rc.z_flag = 0;
			}
		}
	}
}

