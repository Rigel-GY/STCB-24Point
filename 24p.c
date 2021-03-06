//作者  陈光月 201808010309


#include <STC15F2K60S2.h>
#include <stdlib.h> //使用随机函数 
#include <intrins.h>      //_nop_();
//#include <time.h>

#define uint unsigned int
#define uchar unsigned char

/*---------宏定义---------*/  //导航按键
#define cstAdcPower 0X80     /*ADC电源开关*/
#define cstAdcFlag 0X10      /*当A/D转换完成后，cstAdcFlag要软件清零*/
#define cstAdcStart 0X08     /*当A/D转换完成后，cstAdcStart会自动清零，所以要开始下一次转换，则需要置位*/
#define cstAdcSpeed90 0X60   /*ADC转换速度 90个时钟周期转换一次*/
#define cstAdcChs17 0X07     /*选择P1.7作为A/D输入*/

sbit sbtKey1 = P3 ^ 2;  //K1
sbit sbtKey2 = P3 ^ 3; //K2
//sbit sbtKey3 = P1 ^ 7;

sbit led_sel = P2^3;//P2^3----E3

uchar duanxuan[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77,0x7c, 0x39, 0x5e, 0x79, 0x71, 0x40, 0x00}; //段选，显示0-f
uchar weixuan[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}; //位选,选择是0-7中的一个数码管
uchar fuhao[] = {0x46,0x40,0x76,0x52,0x4e,0x48,0x7e,0x5a,0x3f,0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77}; //+ - x / 带括号的加减乘除 0 1 2 3 4 符号

uchar fuhao1[]= {0xc6,0xc0,0xf6,0xd2,0xce,0xc8,0xfe,0xda,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0xf7}; //带小数点

uint dati[]= {8,1,8,1,8,1,8}; //显示0-0-0-0
bit sign=1;
//uchar fankui[]={0x6e,0x79,0x6d,0x54,0x5c,0x86}; //  y e s n o !
//uchar yes[]={0x6e,0x79,0x6d,0x86};
//uchar no[]={0x54,0x5c,0x86};
//uchar P_data[][]={
uint i=0;
uint t1[4]= {0};
uint t2=0;
bit flag=0;
uchar led;

uint total_score=0;//答对数
uint total_score1=0;//答错次数
uint total_score2=0;//算对次数
void Delay(int n) {			//延时函数
	while(n--);
}

void Delay200ms() {	//@11.0592MHz
	unsigned char i, j, k;
	//_nop_();
	//_nop_();
	i = 9;
	j = 104;
	k = 139;
	do {
		do {
			while (--k);
		} while (--j);
	} while (--i);
}

void product_data() {	//生成随机4个非0数字
	for(i=0; i<4; i++) {
		t2=rand()%11;//1--10
		if(t2!=0) {
			t1[i]=t2;
		} else {
			i-=1;
		}
	}
}


void Calculate ( float x, float y, float z, float w) { //
	if (x+y+z+w==24) flag=1;
	else if (x+y+z-w==24) flag=1;
	else if ((x+y)*(z+w)==24) flag=1;
	else if ((x-y)*(z+w)==24) flag=1;
	else if ((x-y)*(z-w)==24) flag=1;
	else if ((x+y+z)*w==24) flag=1;
	else if ((x-y-z)*w==24) flag=1;
	else if ((x+y-z)*w==24) flag=1;
	else if ((x*y*z)/w==24) flag=1;
	else if ((x*y)*(z+w)==24) flag=1;
	else if ((x*y)*(z-w)==24) flag=1;
	else if ((x*y)*z-w==24) flag=1;
	else if ((x*y)*z+w==24) flag=1;
	else if (x*y*z*w==24) flag=1;
	else if ((x+y)+(z/w)==24) flag=1;
	else if ((x+y)*(z/w)==24) flag=1;
	else if ((x*y)+z+w==24) flag=1;
	else if ((x*y)+z-w==24) flag=1;
	else if ((x*y)-(z/w)==24) flag=1;
	else if ((x*y)+(z/w)==24) flag=1;
	else if ((x*y)-z-w ==24) flag=1;
	else if ((x*y)+(z*w)==24) flag=1;
	else if ((x*y)-(z*w)==24) flag=1;
	else if ((x*y)/(z*w)==24) flag=1;
	else if ((x*y)/(z-w)==24) flag=1;
	else if ((x*y)/(z+w)==24) flag=1;
	else flag=0;
}

void judge(float a,float b,float c,float d) {
	if(flag==0)Calculate(a,b,c,d);
	if(flag==0)Calculate(a,b,d,c);
	if(flag==0)Calculate(a,c,d,b);

	if(flag==0)Calculate(a,c,b,d);
	if(flag==0)	Calculate(a,d,b,c);
	if(flag==0)Calculate(a,d,c,b);

	if(flag==0)Calculate(b,a,c,d);
	if(flag==0)Calculate(b,a,d,c);
	if(flag==0)Calculate(b,c,a,d);

	if(flag==0)Calculate(b,c,d,a);
	if(flag==0)Calculate(b,d,c,a);
	if(flag==0)Calculate(b,d,a,c);

	if(flag==0)Calculate(c,a,b,d);
	if(flag==0)Calculate(c,a,d,b);
	if(flag==0)Calculate(c,b,d,a);

	if(flag==0)Calculate(c,b,a,d);
	if(flag==0)Calculate(c,d,a,b);
	if(flag==0)Calculate(c,d,b,a);

	if(flag==0)Calculate(d,a,b,c);
	if(flag==0)Calculate(d,a,c,b);
	if(flag==0)Calculate(d,b,c,a);

	if(flag==0)Calculate(d,b,a,c);
	if(flag==0)	Calculate(d,c,a,b);
	if(flag==0)Calculate(d,c,b,a);
}

void ledlight (uint x) {

	led_sel=1; //P2^3----E3
	led=x;
	if(x==0x01) {
		for(i=0; i<8; i++) {
			P0=led;
			Delay200ms();
			led=led<<1;
		}
	} else {
		for(i=0; i<8; i++) {
			P0=led;
			Delay200ms();
			led=led>>1;
		}
	}
	led_sel=0;
}


float son_of_pinpan(uint x,float b,float c) {

	float jieguo;
	uint a=x%4;//是否带括号无所谓 取余就可以
	switch(a) {
		case 0:
			jieguo=b+c;
			break;
		case 1:
			jieguo=b-c;
			break;
		case 2:
			jieguo=b*c;
			break;
		case 3:
			jieguo=b/c;
			break;
	}
	return jieguo;
}

int pinpan(uint  a[]) { //7ge字符
	float jieguo,tt;
	for( i=0; i<7; i+=2)a[i]-=8;

	if(a[3]>=4&&a[3]<=7) {
		jieguo=son_of_pinpan(a[3],a[2],a[4]);
		jieguo=son_of_pinpan(a[1],a[0],jieguo);
		jieguo=son_of_pinpan(a[5],jieguo,a[6]);
	} else if(a[5]>=4&&a[5]<=7) {
		jieguo=son_of_pinpan(a[5],a[4],a[6]);
		tt=son_of_pinpan(a[1],a[0],a[2]);
		jieguo=son_of_pinpan(a[3],tt,jieguo);
	} else {
		jieguo=son_of_pinpan(a[1],a[0],a[2]);
		jieguo=son_of_pinpan(a[3],jieguo,a[4]);
		jieguo=son_of_pinpan(a[5],jieguo,a[6]);
	}

	if(jieguo==24||jieguo==-24)return 1;
	else return 0;
}

/*---------获取AD值子函数--------*/
unsigned char GetADC() {
	uchar ucAdcRes;
	ADC_CONTR = cstAdcPower | cstAdcStart | cstAdcSpeed90 | cstAdcChs17;//没有将cstAdcFlag置1，用于判断A/D是否结束
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while( !( ADC_CONTR & cstAdcFlag ) ); //等待直到A/D转换结束
	ADC_CONTR &= ~cstAdcFlag;           //cstAdcFlagE软件清0
	ucAdcRes = ADC_RES;                 //获取AD的值
	return ucAdcRes;
}

/*---------获取导航按键值子函数--------*/
uchar NavKeyCheck() {
	unsigned char key;
	key = GetADC();     //获取AD的值
	if( key != 255 ) {  //有按键按下时
		Delay(600);
		key = GetADC();
		if( key != 255 ) {          //按键消抖 仍有按键按下
			key = key & 0xE0;       //获取高3位，其他位清零
			key = _cror_( key, 5 ); //循环右移5位 获取A/D转换高三位值，减小误差
			return key;
		}
	}
	return 0x07;        //没有按键按下时返回值0x07
}


/*---------导航按键处理子函数--------*/
void NavKey_Process() {
	uchar ucNavKeyCurrent;  //导航按键当前的状态
	uchar ucNavKeyPast;     //导航按键前一个状态
	uint  times=0;
	int  youbiao=0,youbiao1=0;
	ucNavKeyCurrent = NavKeyCheck();    //获取当前ADC值
	if( ucNavKeyCurrent != 0x07 ) {     //导航按键是否被按下 不等于0x07表示有按下
		ucNavKeyPast = ucNavKeyCurrent;
		while( ucNavKeyCurrent != 0x07 )        //等待导航按键松开
			ucNavKeyCurrent = NavKeyCheck();

		switch( ucNavKeyPast ) {
			case 0x00 :                     //K3 玩家认为无解
				if(flag==1) { //判断错误
					total_score1++;
					ledlight(0x01);			//右到左点亮
				}

				else {	//判断
					total_score+=1;
					ledlight(0x80);//左到右依次点亮
					product_data();
					judge(t1[0],t1[1],t1[2],t1[3]);
				}
				break;
x:
			case 0x03: //导航按键向里按下  玩家认为有解
				times++;
				if(flag==0) { //判断错误
					total_score1++;
					ledlight(0x01);			//右到左点亮
				} else {	// 有解 且判断正确
					total_score++;
					//ledlight(0x80);//左到右依次点亮

					youbiao=0,youbiao1=0;//游标初始化
					for(i=0; i<7; i+=2)
						dati[i]=8;
					for(i=1; i<7; i+=2)
						dati[i]=1;

					while(times%2!=0) { //导航按键按下偶数次
						for(i=0; i<7; i++) {
							if(i==youbiao&&sign==1)P0=fuhao1[dati[i]];
							else
								P0=fuhao[dati[i]];
							P2=weixuan[i];
							Delay(600);
						}
						if(	sbtKey1 == 0) {//未消抖，几率让小数点小时或出现
							Delay(5000);
							if(	sbtKey1 == 0) {
								while(sbtKey1==0) {}
								sign=!sign;
							}


						}

						ucNavKeyCurrent = NavKeyCheck();    //获取当前ADC值
						if( ucNavKeyCurrent != 0x07 ) {     //导航按键是否被按下 不等于0x07表示有按下
							ucNavKeyPast = ucNavKeyCurrent;
							while( ucNavKeyCurrent != 0x07 )        //等待导航按键松开
								ucNavKeyCurrent = NavKeyCheck();
							switch( ucNavKeyPast ) {
								case 0x00:
									Delay(1000);
									total_score--;
									//total_score--;
									goto x;//退出答题查看题目
									break;
								case 0x03:                     //再按下 推出答题或确认答题
									if( pinpan(dati)==1) {
										ledlight(0x80);//左到右依次点亮
										total_score2++;
										flag=0;  //有解标识置0
										product_data();
										judge(t1[0],t1[1],t1[2],t1[3]);
									} else {
										total_score1++;
										ledlight(0x01);//左到右依次点亮
									}

									times++;
									break;

								case 0x04: //左?

									if(youbiao==0)youbiao=6;
									else youbiao--;
									break;

								case 0x01: //右

									if(youbiao==6)youbiao=0;
									else youbiao++;
									break;

								case 0x05:  //上

									if(youbiao%2==1) { //符号
										if(youbiao1>=7)youbiao1=0;

										else youbiao1++;
										dati[youbiao]=youbiao1;
									} else {
										if(youbiao1>=12||youbiao1<9)youbiao1=9;

										else youbiao1++;

										dati[youbiao]=t1[youbiao1-9]+8; //减9 是游标 1 范围 9-12 回到 t1的数组范围， t1数组的数是题目的数
									}																//数字在表答题的段暄信号需要显示值加4
									break;

								case 0x02:  //下

									if(youbiao%2==1) { //符号
										if(youbiao1==0||youbiao1>7)youbiao1=7;

										else youbiao1--;
										dati[youbiao]=youbiao1;
									} else {
										if(youbiao1<=9||youbiao1>12)youbiao1=12;
										else youbiao1--;

										dati[youbiao]=t1[youbiao1-9]+8;
									}
									//

									break;

							}
						}
					}
				}
				break;

		}
	}
	Delay(600);
}
void init() {
	P2M0=0x08;					//设置推挽输出
	P2M1=0x00;
	P0M0=0xff;
	P0M1=0x00;

	P1ASF = 0x80;       //P1.7作为模拟功能A/D使用
	ADC_RES = 0;        //转换结果清零
	ADC_CONTR = 0x8F;   //cstAdcPower = 1
	CLK_DIV = 0X00;     //ADRJ = 0    ADC_RES存放高八位结果

	IT0 = 0;            //设置IT0上升沿触发
	IT1 = 0;
	EA = 1;             //CPU开放中断
}
void main() {

	init();

	product_data();//再次调用 重新生成数据
	judge(t1[0],t1[1],t1[2],t1[3]); 			 //判断

	while(1) {

		NavKey_Process(); //获取按键按下情况
		if(sbtKey1 == 0) { //按下k1 刷新题目
			flag=0;
			product_data();
			judge(t1[0],t1[1],t1[2],t1[3]);
		}
		if(sbtKey2==0) { //按下K2 显示参考答案  和分数 仅显示是否有解
			P2=weixuan[4];
			P0=duanxuan[total_score1%16];
			Delay(600);

			P2=weixuan[5];
			P0=duanxuan[total_score%16];
			Delay(600);

			P2=weixuan[6];
			P0=duanxuan[total_score2%16];
			Delay(600);

			P2=weixuan[7];
			P0=duanxuan[flag];
			Delay(600);
		}


		for(i=0; i<4; i++) {
			P2=weixuan[i];
			P0=duanxuan[t1[i]];
			Delay(600);
		}
	}
}



