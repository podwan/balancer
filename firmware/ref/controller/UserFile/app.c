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

u8 seconds;

u16 RGB_Cnt = 0;
u8 RGB_Flag = 0, LowBattery = 0, BatteryFlag = 0;
u8 LD1, LD2, LD3;
u32 RGB_LD;
u8 txdata[4];
u8 TxCnt;
u16 Volt16;

void Peripherals_Init(void)
{
	LED_Init();
	W25Qxx_Init();
	Read_Cali_Data();
	Gpio_config();
	Key_Init();
	Check_Encoder();
	TIM10_Init();
	TIM7_Init();

	USART1_init(921600); // ESP32通信
	USART2_init(100000); // SUBUS通信
	USART3_init(230400); // 串口打印
	USART4_init(115200); // 串口打印
	IMU_Init();
	delay_ms(10); // delay_ms(500); delay_ms(500); delay_ms(500);
	TIM1_Init();
	TIM8_Init();
	ADC_Config();

	parameters_Init();

	delay_ms(10);
	WS2812_init();

	while (1)
	{

		if (TIM_Flag == 1)
		{
			TIM_Flag = 0;

			if (Car.Sensitivity > 25.0f)
			{
				if (Car.Rc_Mode == 1)
					B_LED(2);
				else
					B_LED(3);
			}
			else
				B_LED(0);

			Car_Cali();
			RcData();
			IMU_handle();

			if (mpu6500.Cali_Flag == 1)
			{
				G_LED(4);

				if (++Car.M1_M2_Cnt >= 300) // 等待电机初始化
				{
					Car.M1_M2_Cnt = 300;
					if (Car.Cali_flag == 1)
						MotorControl();
				}
			}
			if (Car.Print_flag == 1)
				UsartPrint();
			Key_Scan();
			Get_InputVolt();

			if (++TxCnt >= 100) // 向ESP32发送电压数据
			{
				TxCnt = 0;
				Volt16 = (u16)(Car.BatVin_filter * 100.0f);
				txdata[0] = Volt16 & 0xff;
				txdata[1] = Volt16 >> 8;
				UART1_SendDataDMA(txdata, 4);
			}
			if (fabsf(Car.BatVin_filter) < 6.8f) // 电压低于6.8V
			{
				LowBattery = 1; // 产生标志，用于报警
			}
			else
			{
				if (BatteryFlag == 1) // 否则关闭蜂鸣器
				{
					TMR10->c1dt = 0;
					LowBattery = 0;
				}
			}
			if (++seconds >= 5)
			{
				seconds = 0;

				if (Rc.ch2 == 1)
				{
					if (LD1 < 200)
					{
						LD1++;
						LD3 = LD2 = LD1;
					}
				}
				else if (Rc.ch2 == 0)
				{
					if (LD1 > 0)
					{
						LD1--;
						LD3 = LD2 = LD1;
					}
				}
			}

			if (WS2812_SendFlag == 0)
			{
				WS2812_SendFlag = 1;
				if (Rc.ch2 == 1 && LowBattery == 0)
				{
					RGB_LD = (LD3 << 16) | (LD2 << 8) | LD1;

					RGB_Data[0] = 0x161600;
					RGB_Data[1] = RGB_LD;
					RGB_Data[2] = RGB_LD;
					RGB_Data[3] = RGB_LD;
					RGB_Data[4] = RGB_LD;
					RGB_Data[5] = 0x161600;

					//					RGB_Data[6] = 0x160000;
					//					RGB_Data[7] = 0x001600;

					RGB_Data[8] = 0x323232;
					//					RGB_Data[9] = RGB_LD;
					RGB_Data[10] = 0x323232;
					RGB_Data[11] = 0x323232;
					//					RGB_Data[12] = RGB_LD;
					RGB_Data[13] = 0x323232;

					if (RGB_Cnt < 40)
					{
						if (RGB_Flag == 0)
						{
							RGB_Data[7] = RGB_Data[9] = 0x0000EE;
							RGB_Data[6] = RGB_Data[12] = 0x000000;
						}
						else if (RGB_Flag == 1)
						{
							RGB_Data[7] = RGB_Data[9] = 0x000000;
							RGB_Data[6] = RGB_Data[12] = 0xEE0000;
						}
					}
					else if (RGB_Cnt == 80)
					{
						RGB_Data[7] = RGB_Data[9] = 0x000000;
						RGB_Data[6] = RGB_Data[12] = 0x000000;
					}
					else if (RGB_Cnt == 120)
					{
						if (RGB_Flag == 0)
						{
							RGB_Data[7] = RGB_Data[9] = 0x0000EE;
							RGB_Data[6] = RGB_Data[12] = 0x000000;
						}
						else if (RGB_Flag == 1)
						{
							RGB_Data[7] = RGB_Data[9] = 0x000000;
							RGB_Data[6] = RGB_Data[12] = 0xEE0000;
						}
					}
					else if (RGB_Cnt == 160)
					{
						RGB_Data[7] = RGB_Data[9] = 0x000000;
						RGB_Data[6] = RGB_Data[12] = 0x000000;
					}
					else if (RGB_Cnt == 100)
					{
						if (RGB_Flag == 0)
						{
							RGB_Data[7] = RGB_Data[9] = 0x0000EE;
							RGB_Data[6] = RGB_Data[12] = 0x000000;
						}
						else if (RGB_Flag == 1)
						{
							RGB_Data[7] = RGB_Data[9] = 0x000000;
							RGB_Data[6] = RGB_Data[12] = 0xEE0000;
						}
					}
					else if (RGB_Cnt == 200)
					{
						RGB_Data[7] = RGB_Data[9] = 0x000000;
						RGB_Data[6] = RGB_Data[12] = 0x000000;
					}
					else if (RGB_Cnt >= 500)
					{
						RGB_Cnt = 0;
						if (RGB_Flag == 0)
							RGB_Flag = 1;
						else if (RGB_Flag == 1)
							RGB_Flag = 0;
					}
					RGB_Cnt++;
				}
				else if (Rc.ch2 == 0 && LowBattery == 0)
				{
					RGB_LD = (LD3 << 16) | (LD2 << 8) | LD1;
					RGB_Data[0] = 0;
					RGB_Data[1] = RGB_LD;
					RGB_Data[2] = RGB_LD;
					RGB_Data[3] = RGB_LD;
					RGB_Data[4] = RGB_LD;
					RGB_Data[5] = 0;
					RGB_Data[6] = 0;
					RGB_Data[7] = 0;

					RGB_Data[8] = 0;
					RGB_Data[9] = 0;
					RGB_Data[10] = 0;
					RGB_Data[11] = 0;
					RGB_Data[12] = 0;
					RGB_Data[13] = 0;
				}
				else if (LowBattery == 1)
				{
					if (++RGB_Cnt >= 250)
					{
						RGB_Cnt = 0;
						if (BatteryFlag == 0)
						{
							TMR10->c1dt = 200;
							BatteryFlag = 1;
							RGB_Data[0] = 0;
							RGB_Data[1] = 0;
							RGB_Data[2] = 0;
							RGB_Data[3] = 0;
							RGB_Data[4] = 0;
							RGB_Data[5] = 0;
							RGB_Data[6] = 0xEE0000;
							RGB_Data[7] = 0xEE0000;

							RGB_Data[8] = 0;
							RGB_Data[9] = 0xEE0000;
							RGB_Data[10] = 0;
							RGB_Data[11] = 0;
							RGB_Data[12] = 0xEE0000;
							RGB_Data[13] = 0;
						}
						else if (BatteryFlag == 1)
						{
							TMR10->c1dt = 0;
							BatteryFlag = 0;
							RGB_Data[0] = 0;
							RGB_Data[1] = 0;
							RGB_Data[2] = 0;
							RGB_Data[3] = 0;
							RGB_Data[4] = 0;
							RGB_Data[5] = 0;
							RGB_Data[6] = 0;
							RGB_Data[7] = 0;

							RGB_Data[8] = 0;
							RGB_Data[9] = 0;
							RGB_Data[10] = 0;
							RGB_Data[11] = 0;
							RGB_Data[12] = 0;
							RGB_Data[13] = 0;
						}
					}
				}

				send_Data(RGB_Data, 14);
			}
		}
	}
}
