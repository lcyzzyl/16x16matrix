
/************************************************************************************/
/*     程序名：16x16点阵试验程序          							                */
/*                                                                                  */
/*     CPU型号：AT89S52/STC89C51RC    晶振：12.0 M                                  */
/*                                                                                  */                                             
/*                                                                                  */
/*     功能描述： 控制16x16LED点阵显示图形字母汉字等                                */
/*     行  扫    ： 74ls138x2 CPU P1口前四位 A P1^0	 B  P1^1  C  P1^2   D  P1^3	   	*/
/*     列扫（数据）：SCK P0^0 RCK P0^1 SER P0^2                                     */
/*     取模方式：    阴码 逐行式  顺向（高位在前）                                        								    */
/*																				    */
/*                                                      精英团队 版权所有           */                                 
/*                                                            2008-06-20            */
/************************************************************************************/ 

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int 
 

 
sbit  P_HC595_SCK  =  P0^0;        // CPU  pin 1        SCK        数据输入时钟
sbit  P_HC595_RCK  =  P0^1;        // CPU  pin 2        RCK        数据输出时钟
sbit  P_HC595_SER  =  P0^2;        // CPU  pin 3        SER       数据输入


int speed = 2;

uchar code table[]=
{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};


uchar code hanzi1[] = {		 //阴码 顺向 


0x00,0x80,0x20,0x40,0x17,0xFE,0x12,0x08,0x81,0x10,0x40,0xA0,0x40,0x40,0x11,0xB0,
0x16,0x0E,0x21,0x10,0xE1,0x10,0x21,0x10,0x21,0x10,0x22,0x10,0x22,0x10,0x04,0x10,/*"济",0*/
/* (16 X 16 , 宋体 )*/

}; 


uchar code hanzi2[] = {		 //阴码 顺向 


0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x7F,0xFC,0x48,0x24,0x44,0x44,
0x4F,0xE4,0x41,0x04,0x41,0x04,0x5F,0xF4,0x41,0x04,0x41,0x04,0x41,0x14,0x40,0x08,/*"南",1*/
/* (16 X 16 , 宋体 )*/


}; 

uchar code hanzi3[] = {		 //阴码 顺向 

0x00,0x00,0x3F,0xFE,0x20,0x00,0x20,0x80,0x20,0x80,0x20,0x80,0x2F,0xFC,0x20,0x84,
0x20,0x84,0x21,0x04,0x21,0x04,0x22,0x04,0x22,0x04,0x44,0x04,0x48,0x28,0x90,0x10,/*"历",2*/
/* (16 X 16 , 宋体 )*/
 };
 

uchar code hanzi4[] = {		 //阴码 顺向 


0x20,0x28,0x20,0x24,0x20,0x20,0x27,0xFE,0x24,0x20,0xFC,0x20,0x24,0x24,0x27,0xA4,
0x24,0xA4,0x24,0xA8,0x24,0xA8,0x3C,0x90,0xE6,0x92,0x49,0x2A,0x08,0x46,0x10,0x82,/*"城",3*/
/* (16 X 16 , 宋体 )*/

}; 


uchar code hanzi5[] = {		 //阴码 顺向 


0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"一",4*/
/* (16 X 16 , 宋体 )*/


}; 

uchar code hanzi6[] = {		 //阴码 顺向 

0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,
0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,/*"中",5*/

/* (16 X 16 , 宋体 )*/
 };


uchar code hanzi11[] =


{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,
0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/* 1.bmp",0*/

} ;


uchar code hanzi12[]=


{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x02,0x40,
0x02,0x40,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\1562_副本.bmp",0*/

};


uchar code hanzi13[] =


{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,0x04,0x20,0x05,0xA0,
0x05,0xA0,0x04,0x20,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\1562_副本.bmp",0*/


};


uchar code hanzi14[] =


{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF0,0x08,0x10,0x0B,0xD0,0x0A,0x50,
0x0A,0x50,0x0B,0xD0,0x08,0x10,0x0F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\1562_副本.bmp",0*/

} ;


 uchar code hanzi15[] =


{
0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xF8,0x10,0x08,0x17,0xE8,0x14,0x28,0x15,0xA8,
0x15,0xA8,0x14,0x28,0x17,0xE8,0x10,0x08,0x1F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\1562_副本.bmp",0*/
}  ;


uchar code hanzi16[]=


{
0x00,0x00,0x00,0x00,0x3F,0xFC,0x20,0x04,0x2F,0xF4,0x28,0x14,0x2B,0xD4,0x2A,0x54,
0x2A,0x54,0x2B,0xD4,0x28,0x14,0x2F,0xF4,0x20,0x04,0x3F,0xFC,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\1562_副本.bmp",0*/

};



 

uchar code hanzi17[] = {		 //阴码 顺向 


0xFF,0xFF,0x80,0x01,0xBF,0xFD,0xA0,0x05,0xAF,0xF5,0xA8,0x15,0xAB,0xD5,0xAA,0x55,
0xAA,0x55,0xAB,0xD5,0xA8,0x15,0xAF,0xF5,0xA0,0x05,0xBF,0xFD,0x80,0x01,0xFF,0xFF,/*"C:\Users\Administrator\Desktop\4251_副本.bmp",0*/



};



uchar code hanzi18[] =


 {
0x00,0x00,0x7F,0xFE,0x40,0x02,0x5F,0xFA,0x50,0x0A,0x57,0xEA,0x54,0x2A,0x55,0xAA,
0x55,0xAA,0x54,0x2A,0x57,0xEA,0x50,0x0A,0x5F,0xFA,0x40,0x02,0x7F,0xFE,0x00,0x00,/*"C:\Users\Administrator\Desktop\1562_副本.bmp",0*/

};





void delay(uint x)                      //延时子函数
{	
	uint i,j;
	for(i=x;i>0;i--)
	   for(j=10;j>0;j--);
}






void Send_595(unsigned char dat)        //发送一个字节
{                
        unsigned char  i;
        for(i=0; i<8; i++)
        {
                if(dat & 0x01)           //如果dat和0x01与的结果是1，也就是需要led亮，就把数据位置0， 
  
//  0000 0000 0000 1000
//  0000 0000 0000 0001
//  0000 0000 0000 0000
//  需要右移
//  第一位获取的是0，由于是阴码 0 时led是不亮的，根据595的工作原理和电路原理，送的数据应该为 1 ，送到第四位时，与的结果为1，，数据送 0 。

				   P_HC595_SER = 0;	    //数据是 0 时，led 亮
               else                		
				   P_HC595_SER = 1;	   //数据是 1  时，led不亮		    
                
			// P_HC595_SER  =  dat & 0x80 ;   //取出最高位
				
				P_HC595_SCK = 0;
			
				 
                P_HC595_SCK = 1;

                dat = dat >> 1;		//右移1位

			 	 

        }

	
}




void Show_595_clear()  //清屏

{

    unsigned char j ;

	for (j=0;j<16;j++)
    {
	   P1=table[j];//查表显示数字

	   	   
	   Send_595(0x00);	  // 送一行的高位数据
	   Send_595(0x00);	  // 送一行的低位数据
	  	   				  
	   
	   P_HC595_RCK = 1;	  //数据锁存高电平

	   P_HC595_RCK = 0;	  //数据锁存低电平


	  // delay(1);		  //延时

	     
	 }

}      





 
void Show_595_bmp(unsigned char dat[])  //显示一个字汉字


{

    unsigned char j ,temp1,temp2 ;

 

  	  
         for (j=0;j<16;j++)
           {
	   
		
	       temp2 = dat[2*j+1];
	       temp1 = dat[2*j];
	   
	   
	   
	       Send_595(temp2);	  // 送一行的高位数据
	       Send_595(temp1);	  // 送一行的低位数据
	   
	   			  
	   
	        P_HC595_RCK = 1;	  //数据锁存高电平

	        P_HC595_RCK = 0;	  //数据锁存低电平


			P1 =  table[j];	      //送完列数据再送行数据


	       delay(10);
		    	   
	  

	       
	    }

	 

} 



 


void main()
{	


       while(1) { 

			  unsigned char  i;



	       /*  for(i=0;i<200;i++)

              {
 
              Show_595_bmp(hanzi1);

              
              }


			 for(i=0;i<200;i++)

              {
 
              Show_595_bmp(hanzi2);

              
              }

			    for(i=0;i<200;i++)

              {
 
              Show_595_bmp(hanzi3);

              
              }

			    for(i=0;i<200;i++)

              {
 
              Show_595_bmp(hanzi4);

              
              }

			    for(i=0;i<200;i++)

              {
 
              Show_595_bmp(hanzi5);

              
              }

			    for(i=0;i<200;i++)

              {
 
              Show_595_bmp(hanzi6);

              
              }

			  */

     		   
			 for(i=0;i<speed;i++)

              {
 
              Show_595_bmp(hanzi11);

              
              }

			  for(i=0;i<speed;i++)

              {
 
              Show_595_bmp(hanzi12);

              
              }
			 
			 
			 
			 
			  for(i=0;i<speed;i++)

              {
 
              Show_595_bmp(hanzi13);

              
              }

			  for(i=0;i<speed;i++)

              {
 
              Show_595_bmp(hanzi14);

              
              } 
			   
			   
			   
			   
			   for(i=0;i<speed;i++)

              {
 
              Show_595_bmp(hanzi15);

              
              }

			  for(i=0;i<speed;i++)

              {
 
              Show_595_bmp(hanzi16);

              
              }

		   	   for(i=0;i<speed;i++)

              {
 
              Show_595_bmp(hanzi17);

              
              }

			  for(i=0;i<speed;i++)

              {
 
              Show_595_bmp(hanzi18);

              
              }
          
		  
		  
		  
		 }	  


}


