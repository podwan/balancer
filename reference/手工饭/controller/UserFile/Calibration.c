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

CaliData_t CaliData;

uint8_t u8_Cali_Data[256];
uint8_t Protection = 0;

// 下载程序后使用串口助手按照顺序1-5进行校准即可，亦可仿真赋值进行校准

// 0xA0 0xAA 0x01 0xB1 0x66 校准陀螺零偏，必须保证小车无受到任何震动
// 0xA0 0xAA 0x02 0xB2 0x66 校准左电机，必须保证车轮能顺滑用手转动不能有干涉，串口发送指令后电机会按照设定速度转动则为正常（不转为异常）
// 0xA0 0xAA 0x03 0xB3 0x66 校准右电机，必须保证车轮能顺滑用手转动不能有干涉，串口发送指令后电机会按照设定速度转动则为正常（不转为异常）
// 0xA0 0xAA 0x04 0xB4 0x66 关闭电机
// 0xA0 0xAA 0x05 0xB5 0x66 保存数据，保存数据前请先关闭电机
// 0xA0 0xAA 0x06 0xB6 0x66 清除数据
// 0xA0 0xAA 0x07 0xB7 0x66 开启串口打印

void Car_Cali(void)
{
	uint8_t crc = 0;

	if (U3_IDLE_Flag == 1)
	{
		U3_IDLE_Flag = 0;
		if (Get_usart3_data[0] == 0xA0 && Get_usart3_data[1] == 0xAA && Get_usart3_data[4] == 0x66)
		{
			crc = Get_usart3_data[0] + Get_usart3_data[1] + Get_usart3_data[2] + Get_usart3_data[4];
			if (Get_usart3_data[3] == crc)
			{
				Get_usart3_data[4] = 0x99;			   // 改变结尾
				UART3_SendDataDMA(Get_usart3_data, 5); // 返回相同命令

				Car.Cali_mode = Get_usart3_data[2];
				switch (Car.Cali_mode)
				{
				case 1:
					Gyro_Cali();
					Car.Cali_mode = 0;
					Protection = 0;
					break;
				case 2:
					M1_Foc.Cali_flag = 2;
					Car.Cali_mode = 0;
					break;
				case 3:
					M2_Foc.Cali_flag = 2;
					Car.Cali_mode = 0;
					break;
				case 4:
					M1_Foc.Cali_flag = 0;
					M2_Foc.Cali_flag = 0;
					Car.Cali_mode = 0;
					break;
				case 5:
					if (Protection == 0)
					{
						Protection = 1;
						Car.Cali_mode = 0;
						CaliData.M1_offset = M1_Foc.ThetaOffset;
						CaliData.M2_offset = M2_Foc.ThetaOffset;

						CaliData.M1_Flag = M1_Foc.Cali_Status;
						CaliData.M2_Flag = M2_Foc.Cali_Status;

						CaliData.x[0] = mpu6500.gyro.offset.x;
						CaliData.y[0] = mpu6500.gyro.offset.y;
						CaliData.z[0] = mpu6500.gyro.offset.z;

						CaliData.IMU_Flag = mpu6500.Cali_Flag;
						Write_Cali_Data();
					}
					break;
				case 6:
					if (Protection == 0)
					{
						Protection = 1;
						Car.Cali_mode = 0;
						CaliData.M1_offset = 0;
						CaliData.M2_offset = 0;

						CaliData.M1_Flag = 0;
						CaliData.M2_Flag = 0;

						CaliData.x[0] = 0;
						CaliData.y[0] = 0;
						CaliData.z[0] = 0;

						CaliData.IMU_Flag = 0;

						M1_Foc.Cali_flag = 0;
						M2_Foc.Cali_flag = 0;
						Write_Cali_Data();
					}
					break;
				case 7:
					Car.Print_flag = 1;
					Car.Cali_mode = 0;
					break;
				}
			}
			memset(Get_usart3_data, 0, sizeof(char) * 5);
		}
	}
}

/***********************************************************************************************************
 *原型: void Gyro_Cali(void)
 *功能：陀螺仪零偏校准
 *调用：
 *输入：
 *输出：
 ************************************************************************************************************/
void Gyro_Cali(void)
{
	mpu6500.gyro.offset.x = mpu6500.gyro.filter.x;
	mpu6500.gyro.offset.y = mpu6500.gyro.filter.y;
	mpu6500.gyro.offset.z = mpu6500.gyro.filter.z;
	mpu6500.Cali_Flag = 1;
}

/***********************************************************************************************************
 *原型: void Write_Cali_Data(void)
 *功能：保存数据到Flash
 *调用：
 *输入：
 *输出：
 ************************************************************************************************************/
void Write_Cali_Data(void)
{
	uint16_t i, len = 0;
	uint8_t *CaliDataT = (uint8_t *)&CaliData;

	CaliData.sumcheck = 0;
	CaliData.addcheck = 0;
	len = sizeof(CaliData) - 2;
	for (i = 0; i < len; i++)
	{
		CaliData.sumcheck += CaliDataT[i];
		CaliData.addcheck += CaliData.sumcheck;
	}

	memcpy(u8_Cali_Data, &CaliData, sizeof(CaliData));
	W25Qxx_ErasePage(0);
	W25Qxx_WritePage(u8_Cali_Data, 0, sizeof(CaliData));
}

/***********************************************************************************************************
 *原型: void Read_Cali_Data(void)
 *功能：读取Flash数据
 *调用：
 *输入：
 *输出：
 ************************************************************************************************************/
void Read_Cali_Data(void)
{
	uint16_t i, len = 0;
	uint8_t sumcheck = 0, addcheck = 0;

	memset(&M1_Foc, 0, sizeof(M1_Foc));
	memset(&M2_Foc, 0, sizeof(M2_Foc));
	memset(&mpu6500, 0, sizeof(mpu6500));

	W25Qxx_Read(u8_Cali_Data, 0, sizeof(CaliData));

	memset(&CaliData, 0, sizeof(CaliData));

	len = sizeof(CaliData) - 2;
	for (i = 0; i < len; i++)
	{
		sumcheck += u8_Cali_Data[i];
		addcheck += sumcheck;
	}
	memcpy(&CaliData, u8_Cali_Data, sizeof(CaliData));
	//	sumcheck = 0;
	if (CaliData.sumcheck == sumcheck && CaliData.addcheck == addcheck)
	{
		if (CaliData.M1_Flag == 1 && CaliData.M2_Flag == 1 && CaliData.IMU_Flag == 1)
		{
			Car.Cali_flag = 1;

			M1_Foc.Cali_flag = 1;
			M2_Foc.Cali_flag = 1;

			if (CaliData.M1_Flag == 1)
			{
				M1_Foc.ThetaOffset = CaliData.M1_offset;
			}

			if (CaliData.M2_Flag == 1)
			{
				M2_Foc.ThetaOffset = CaliData.M2_offset;
			}

			if (CaliData.IMU_Flag == 1)
			{
				mpu6500.Cali_Flag = CaliData.IMU_Flag;
				mpu6500.gyro.offset.x = CaliData.x[0];
				mpu6500.gyro.offset.y = CaliData.y[0];
				mpu6500.gyro.offset.z = CaliData.z[0];
			}
		}
	}
	else
	{
		memset(&CaliData, 0, sizeof(CaliData));
		Car.Cali_flag = 0;
	}
}
