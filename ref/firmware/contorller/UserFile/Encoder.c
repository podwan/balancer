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

u8 Encoder_Model;
u8 Encoder_Model_0,Encoder_Model_1,Encoder_Model_2;

void Check_Encoder(void)
{
	gpio_init_type gpio_init_struct;
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_init_struct);
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_7;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOD, &gpio_init_struct);

	gpio_bits_set(GPIOD,GPIO_PINS_5 | GPIO_PINS_7);
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_4; 
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOB, &gpio_init_struct);
  gpio_bits_set(GPIOB,GPIO_PINS_4); // 拉高
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_3|GPIO_PINS_5; 
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOB, &gpio_init_struct);
	
	delay_ms(5);
	
	Encoder_Model_0 = gpio_input_data_bit_read(GPIOB,GPIO_PINS_3);
	Encoder_Model_1 = gpio_input_data_bit_read(GPIOB,GPIO_PINS_4);
  Encoder_Model_2 = gpio_input_data_bit_read(GPIOB,GPIO_PINS_5);
	
	if(Encoder_Model_0 == 0 && Encoder_Model_1 == 0 && Encoder_Model_2 == 0)
	{
		Encoder_Model = 0; // MA732
		MA732_Init();
	}
	else if(Encoder_Model_0 == 0 && Encoder_Model_1 == 1 && Encoder_Model_2 == 1)
	{
		Encoder_Model = 1; // TLE5012
		TLE5012B_Init();
	}
	else if(Encoder_Model_0 == 1 && Encoder_Model_1 == 1 && Encoder_Model_2 == 1)
	{
		Encoder_Model = 2; // MT6701
		MT6701_Init();
	}
	
	// 注意：如编码器连接线接触不良会导致识别错误，请自行仿真进行排查问题
}

/*************************************************************************************************************************/

void MT6701_Init(void)
{
	gpio_init_type gpio_initstructure;
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_initstructure);		
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_5 | GPIO_PINS_7;
  gpio_initstructure.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOD, &gpio_initstructure);

	gpio_bits_set(GPIOD,GPIO_PINS_5 | GPIO_PINS_7);
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_INPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_4;
  gpio_initstructure.gpio_pull = GPIO_PULL_DOWN;
  gpio_init(GPIOB, &gpio_initstructure);
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_3;
  gpio_initstructure.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOB, &gpio_initstructure);

	gpio_bits_set(GPIOB,GPIO_PINS_3);
}

/*************************************************************************************************************************/

/*************************************************************************************************************************/

void TLE5012B_Init(void)
{
	spi_init_type spi_init_struct;
	gpio_init_type gpio_initstructure;
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_initstructure);	
	
	gpio_pin_remap_config(SPI1_GMUX_0001,TRUE);
	gpio_pin_remap_config(SWJTAG_GMUX_010,TRUE);
	
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_3 | GPIO_PINS_4 | GPIO_PINS_5;
  gpio_init(GPIOB, &gpio_initstructure);
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_5 | GPIO_PINS_7;
  gpio_initstructure.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOD, &gpio_initstructure);

	gpio_bits_set(GPIOD,GPIO_PINS_5 | GPIO_PINS_7);
	
	spi_enable(SPI1, FALSE);
	
	crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
  spi_default_para_init(&spi_init_struct);
  spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
  spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
  spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_16;
  spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
  spi_init_struct.frame_bit_num = SPI_FRAME_16BIT;
  spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW; // SPI_CLOCK_POLARITY_LOW SPI_CLOCK_POLARITY_HIGH
  spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;      // SPI_CLOCK_PHASE_1EDGE SPI_CLOCK_PHASE_2EDGE
  spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
  spi_init(SPI1, &spi_init_struct);
	
  spi_enable(SPI1, TRUE);
	delay_ms(10);
}

u16 SPI1_ReadWriteHalfword(u16 Halfword)
{
	u16 retry=0;				 	
	while(spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) //等待SPI发送标志位空
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI1->dt = Halfword; //发送数据
	retry=0;

	while(spi_i2s_flag_get(SPI1, SPI_I2S_RDBF_FLAG) == RESET) //等待SPI接收标志位空
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI1->dt; //接收数据		
}

/*************************************************************************************************************************/

/*************************************************************************************************************************/

u8 MA732_Map_addr[]={0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0e,0x10,0x1b};
u8 MA732_Map_data[]={0x00,0x00,0xc0,0xff,0x1c,0x00,0xc0,0x00,0x88,0x00,0x00};
u8 MA732_Map_data_check1[11];
u8 MA732_Map_data_check2[11];
void MA732_Init(void)
{
	u8 i;
	spi_init_type spi_init_struct;
	gpio_init_type gpio_initstructure;
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_initstructure);	
	
	gpio_pin_remap_config(SPI1_GMUX_0001,TRUE);
	gpio_pin_remap_config(SWJTAG_GMUX_010,TRUE);
	
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_3 | GPIO_PINS_4 | GPIO_PINS_5;
  gpio_init(GPIOB, &gpio_initstructure);
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_5 | GPIO_PINS_7;
  gpio_initstructure.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOD, &gpio_initstructure);

	gpio_bits_set(GPIOD,GPIO_PINS_5 | GPIO_PINS_7);
	
	spi_enable(SPI1, FALSE);
	
	crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE); // 120M
  spi_default_para_init(&spi_init_struct);
  spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
  spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
  spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_16;
  spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
  spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
  spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH; // SPI_CLOCK_POLARITY_LOW SPI_CLOCK_POLARITY_HIGH
  spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;      // SPI_CLOCK_PHASE_1EDGE SPI_CLOCK_PHASE_2EDGE
  spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
  spi_init(SPI1, &spi_init_struct);
	
  spi_enable(SPI1, TRUE);
	delay_ms(10);
  
	for(i=0;i<11;i++)
	{
		if(MA732_Read_Reg(1,MA732_Map_addr[i],0x0) != MA732_Map_data[i])
		{
			MA732_Write_Reg(1,MA732_Map_addr[i],MA732_Map_data[i]);
		}
	}
	
//	for(i=0;i<11;i++)
//	{
//		MA732_Map_data_check1[i] = MA732_Read_Reg(1,MA732_Map_addr[i],0x0);
//	}
	
	for(i=0;i<11;i++)
	{
		if(MA732_Read_Reg(2,MA732_Map_addr[i],0x0) != MA732_Map_data[i])
		{
			MA732_Write_Reg(2,MA732_Map_addr[i],MA732_Map_data[i]);
		}
	}
	
//	for(i=0;i<11;i++)
//	{
//		MA732_Map_data_check2[i] = MA732_Read_Reg(2,MA732_Map_addr[i],0x0);
//	}
}

u16 SPI1_ReadWriteByte(u8 byte)
{
	u16 cnt=0;				 	
	while(spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) //等待SPI发送标志位空
	{
		cnt++;
		if(cnt>200)return 0;
	}			  
	SPI1->dt = byte; //发送数据
	cnt=0;

	while(spi_i2s_flag_get(SPI1, SPI_I2S_RDBF_FLAG) == RESET) //等待SPI接收标志位空
	{
		cnt++;
		if(cnt>200)return 0;
	}	  						    
	return SPI1->dt; //接收数据		
}

u16 MA732_Write_Reg(u8 Select,u8 reg,u8 value)
{
	u8 data;
  
	if(Select == 1)
	{
		SPI1_CS1_0;
		SPI1_ReadWriteByte(reg|0x80);
		SPI1_ReadWriteByte(value);
		SPI1_CS1_1;
		delay_ms(50);
		SPI1_CS1_0;
		data = SPI1_ReadWriteByte(0x00);
		SPI1_ReadWriteByte(0x00);
		SPI1_CS1_1;
	}
	else if(Select == 2)
	{
		SPI1_CS2_0;
		SPI1_ReadWriteByte(reg|0x80);
		SPI1_ReadWriteByte(value);
		SPI1_CS2_1;
		delay_ms(50);
		SPI1_CS2_0;
		data = SPI1_ReadWriteByte(0x00);
		SPI1_ReadWriteByte(0x00);
		SPI1_CS2_1;
	}
	return data;
}

u16 MA732_Read_Reg(u8 Select,u8 reg,u8 value)
{
	u8 data;
  
	if(Select == 1)
	{
		SPI1_CS1_0;
		SPI1_ReadWriteByte(reg|0x40);
		SPI1_ReadWriteByte(value);
		SPI1_CS1_1;
		delay_ms(50);
		SPI1_CS1_0;
		data = SPI1_ReadWriteByte(0x00);
		SPI1_ReadWriteByte(0x00);
		SPI1_CS1_1;
	}
	else if(Select == 2)
	{
		SPI1_CS2_0;
		SPI1_ReadWriteByte(reg|0x40);
		SPI1_ReadWriteByte(value);
		SPI1_CS2_1;
		delay_ms(50);
		SPI1_CS2_0;
		data = SPI1_ReadWriteByte(0x00);
		SPI1_ReadWriteByte(0x00);
		SPI1_CS2_1;
	}
	return data;
}

/*************************************************************************************************************************/

/*************************************************************************************************************************/

u16 Read_M1_Encoder(void)
{
	u8 Value1,Value2,i;
	u16 data;
	
	SPI1_CS1_0; 
	switch (Encoder_Model)	
	{
		case 0: // MA732
			Value1 = SPI1_ReadWriteByte(0);
			Value2 = SPI1_ReadWriteByte(0);
			data=((Value1<<8)|Value2)>>1;
		break;
		
		case 1: // TLE5012
			SPI1_ReadWriteHalfword(0x8020);
			GPIOB->cfglr &= 0xFF4FFFFF;
			data = 32768 - (SPI1_ReadWriteHalfword(0xff)&0x7fff);
			GPIOB->cfglr |= 0x900000;
		break;
		
		case 2: // MT6701 
			GPIOB->clr = GPIO_PINS_3;
			GPIOB->scr = GPIO_PINS_3;
			for(i = 0;i < 14; i++)
			{
				GPIOB->clr = GPIO_PINS_3;
				data<<=1;
				if((GPIO_PINS_4 & GPIOB->idt) == GPIO_PINS_4)
					data++;  
				GPIOB->scr = GPIO_PINS_3;
			}
			data = data << 1;
		break;
	}
	SPI1_CS1_1;
	
	return data;
}

u16 Read_M2_Encoder(void)
{
	u8 Value1,Value2,i;
	u16 data;
	
	SPI1_CS2_0; 
	switch (Encoder_Model)	
	{
		case 0: // MA732
			Value1 = SPI1_ReadWriteByte(0);
			Value2 = SPI1_ReadWriteByte(0);
			data=((Value1<<8)|Value2)>>1;
		break;
		
		case 1: // TLE5012
			SPI1_ReadWriteHalfword(0x8020);
			GPIOB->cfglr &= 0xFF4FFFFF;
			data = 32768 - (SPI1_ReadWriteHalfword(0xff)&0x7fff);
			GPIOB->cfglr |= 0x900000;
		break;
		
		case 2: // MT6701 
		  GPIOB->clr = GPIO_PINS_3;
			GPIOB->scr = GPIO_PINS_3;
			for(i = 0;i < 14; i++)
			{
				GPIOB->clr = GPIO_PINS_3;
				data<<=1;
				if((GPIO_PINS_4 & GPIOB->idt) == GPIO_PINS_4)
					data++;  
				GPIOB->scr = GPIO_PINS_3;
			}
			data = data << 1;
		break;
	}
	SPI1_CS2_1;
	
	return data;
}

/*************************************************************************************************************************/
