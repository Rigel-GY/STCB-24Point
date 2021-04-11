//����  �¹��� 201808010309


#include <STC15F2K60S2.h>
#include <stdlib.h> //ʹ��������� 
#include <intrins.h>      //_nop_();
//#include <time.h>

#define uint unsigned int
#define uchar unsigned char

/*---------�궨��---------*/  //��������
#define cstAdcPower 0X80     /*ADC��Դ����*/
#define cstAdcFlag 0X10      /*��A/Dת����ɺ�cstAdcFlagҪ�������*/
#define cstAdcStart 0X08     /*��A/Dת����ɺ�cstAdcStart���Զ����㣬����Ҫ��ʼ��һ��ת��������Ҫ��λ*/
#define cstAdcSpeed90 0X60   /*ADCת���ٶ� 90��ʱ������ת��һ��*/
#define cstAdcChs17 0X07     /*ѡ��P1.7��ΪA/D����*/

sbit sbtKey1 = P3 ^ 2;  //K1
sbit sbtKey2 = P3 ^ 3; //K2
//sbit sbtKey3 = P1 ^ 7;

sbit led_sel = P2^3;//P2^3----E3

uchar duanxuan[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77,0x7c, 0x39, 0x5e, 0x79, 0x71, 0x40, 0x00}; //��ѡ����ʾ0-f
uchar weixuan[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}; //λѡ,ѡ����0-7�е�һ�������
uchar fuhao[] ={0x46,0x40,0x76,0x52,0x4e,0x48,0x7e,0x5a,0x3f,0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77};//+ - x / �����ŵļӼ��˳� 0 1 2 3 4 ����

uchar fuhao1[]={0xc6,0xc0,0xf6,0xd2,0xce,0xc8,0xfe,0xda,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0xf7};//��С����

uint dati[]={8,1,8,1,8,1,8};//��ʾ0-0-0-0
bit sign=1;
//uchar fankui[]={0x6e,0x79,0x6d,0x54,0x5c,0x86}; //  y e s n o !
//uchar yes[]={0x6e,0x79,0x6d,0x86};
//uchar no[]={0x54,0x5c,0x86};
//uchar P_data[][]={
uint i=0;
uint t1[4]={0};	
uint t2=0;
bit flag=0;
uchar led;

uint total_score=0;//�����
uint total_score1=0;//������
uint total_score2=0;//��Դ���
void Delay(int n)				//��ʱ����
{
	while(n--);
}

void Delay200ms()		//@11.0592MHz
{
	unsigned char i, j, k;
	//_nop_();
	//_nop_();
	i = 9;
	j = 104;
	k = 139;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void product_data()	//�������4����0����	
{
	for(i=0;i<4;i++)
				{
					t2=rand()%11;//1--10
					if(t2!=0)
						{
							t1[i]=t2;
						}
					else{
						i-=1;
						}	
				}
}


void Calculate ( float x, float y, float z, float w) //
{
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

void judge(float a,float b,float c,float d)
{
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

void ledlight (uint x)
{

					led_sel=1; //P2^3----E3												
					led=x;
	if(x==0x01){
						for(i=0;i<8;i++){
						P0=led;
						Delay200ms(); 
						led=led<<1;
						}
					}
	else{
					for(i=0;i<8;i++){
						P0=led;
						Delay200ms(); 
						led=led>>1;
					}
			}
				led_sel=0;
}


float son_of_pinpan(uint x,float b,float c)
{
	
	float jieguo;
	uint a=x%4;//�Ƿ����������ν ȡ��Ϳ���
	switch(a)
	{	
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

int pinpan(uint  a[])//7ge�ַ�
{
	float jieguo,tt;
	for( i=0;i<7;i+=2)a[i]-=8;
	
	if(a[3]>=4&&a[3]<=7)
	{
		jieguo=son_of_pinpan(a[3],a[2],a[4]);
		jieguo=son_of_pinpan(a[1],a[0],jieguo);
		jieguo=son_of_pinpan(a[5],jieguo,a[6]);
	}
	else if(a[5]>=4&&a[5]<=7)
	{	
		jieguo=son_of_pinpan(a[5],a[4],a[6]);
		tt=son_of_pinpan(a[1],a[0],a[2]);
		jieguo=son_of_pinpan(a[3],tt,jieguo);
	}
	else{
		jieguo=son_of_pinpan(a[1],a[0],a[2]);
		jieguo=son_of_pinpan(a[3],jieguo,a[4]);
		jieguo=son_of_pinpan(a[5],jieguo,a[6]);
	}
	
	if(jieguo==24||jieguo==-24)return 1;
	else return 0;
}

/*---------��ȡADֵ�Ӻ���--------*/
unsigned char GetADC()
{
    uchar ucAdcRes;
    ADC_CONTR = cstAdcPower | cstAdcStart | cstAdcSpeed90 | cstAdcChs17;//û�н�cstAdcFlag��1�������ж�A/D�Ƿ����
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    while( !( ADC_CONTR & cstAdcFlag ) ); //�ȴ�ֱ��A/Dת������
    ADC_CONTR &= ~cstAdcFlag;           //cstAdcFlagE�����0
    ucAdcRes = ADC_RES;                 //��ȡAD��ֵ
    return ucAdcRes;
}

/*---------��ȡ��������ֵ�Ӻ���--------*/
uchar NavKeyCheck()
{
    unsigned char key;
    key = GetADC();     //��ȡAD��ֵ
    if( key != 255 )    //�а�������ʱ
    {
        Delay(600);
        key = GetADC();
        if( key != 255 )            //�������� ���а�������
        {
            key = key & 0xE0;       //��ȡ��3λ������λ����
            key = _cror_( key, 5 ); //ѭ������5λ ��ȡA/Dת������λֵ����С���
            return key;
        }
    }
    return 0x07;        //û�а�������ʱ����ֵ0x07
}


/*---------�������������Ӻ���--------*/
void NavKey_Process()
{
    uchar ucNavKeyCurrent;  //����������ǰ��״̬
    uchar ucNavKeyPast;     //��������ǰһ��״̬
		uint  times=0;
	  int  youbiao=0,youbiao1=0;
		ucNavKeyCurrent = NavKeyCheck();    //��ȡ��ǰADCֵ
		if( ucNavKeyCurrent != 0x07 )       //���������Ƿ񱻰��� ������0x07��ʾ�а���
    {
        ucNavKeyPast = ucNavKeyCurrent;
        while( ucNavKeyCurrent != 0x07 )        //�ȴ����������ɿ�
            ucNavKeyCurrent = NavKeyCheck();

        switch( ucNavKeyPast )
        {
            case 0x00 :                     //K3 �����Ϊ�޽�
                if(flag==1)//�жϴ���
											{	
												total_score1++;		
												ledlight(0x01);			//�ҵ������
											}
												
								else	//�ж�
											{
													total_score+=1;				
													ledlight(0x80);//�������ε���
													product_data();
													judge(t1[0],t1[1],t1[2],t1[3]);
											}
                break;
x:											
						 case 0x03: //�����������ﰴ��  �����Ϊ�н�
								times++;
							  if(flag==0)//�жϴ���
											{	
												total_score1++;		
												ledlight(0x01);			//�ҵ������
											}							
								else	// �н� ���ж���ȷ
											{												
													total_score++;				
													//ledlight(0x80);//�������ε���
												
													youbiao=0,youbiao1=0;//�α��ʼ��
												for(i=0;i<7;i+=2)
													dati[i]=8;
												for(i=1;i<7;i+=2)
													dati[i]=1;
												
												while(times%2!=0)//������������ż����
													{ 									
																	for(i=0;i<7;i++)	
																{
																	if(i==youbiao&&sign==1)P0=fuhao1[dati[i]];	
																	else 
																		P0=fuhao[dati[i]];	
																	P2=weixuan[i]; 									
																	Delay(600);	
																}
														if(	sbtKey1 == 0) {//δ������������С����Сʱ�����
															Delay(5000);
																if(	sbtKey1 == 0){
																	while(sbtKey1==0){}
																		sign=!sign;
																		}
															
																	
															}
														
														ucNavKeyCurrent = NavKeyCheck();    //��ȡ��ǰADCֵ
														if( ucNavKeyCurrent != 0x07 )       //���������Ƿ񱻰��� ������0x07��ʾ�а���
															{
																ucNavKeyPast = ucNavKeyCurrent;
																while( ucNavKeyCurrent != 0x07 )        //�ȴ����������ɿ�
																	ucNavKeyCurrent = NavKeyCheck();
																 switch( ucNavKeyPast )
																		{
																			case 0x00:
																					Delay(1000);
																					total_score--;
																					//total_score--;
																					goto x;//�˳�����鿴��Ŀ
																					break;
																			case 0x03:                     //�ٰ��� �Ƴ������ȷ�ϴ���
																				if( pinpan(dati)==1){
																					ledlight(0x80);//�������ε���
																					total_score2++;		
																					flag=0;  //�н��ʶ��0
																					product_data();
																					judge(t1[0],t1[1],t1[2],t1[3]);																					
																					}
																				else {
																					total_score1++;
																					ledlight(0x01);//�������ε���
																							}
										
																				times++;
																				break;
																							
																			 case 0x04: //��
																					
																					if(youbiao==0)youbiao=6;
																					else youbiao--;
																				 break;
																			 
																			 case 0x01: //��
																				
																					if(youbiao==6)youbiao=0;
																					else youbiao++;
																				 break;
																			 
																			 case 0x05:  //��
																				 
																				if(youbiao%2==1){//����
																						if(youbiao1>=7)youbiao1=0;
																			
																						else youbiao1++;
																					dati[youbiao]=youbiao1;
																				}
																				else{
																						if(youbiao1>=12||youbiao1<9)youbiao1=9;
																					
																						else youbiao1++;
																						
																				    dati[youbiao]=t1[youbiao1-9]+8; //��9 ���α� 1 ��Χ 9-12 �ص� t1�����鷶Χ�� t1�����������Ŀ����
																						}																//�����ڱ����Ķ����ź���Ҫ��ʾֵ��4
																				 break;
																						
																			 case 0x02:  //��
																				
																			 if(youbiao%2==1){//����
																						if(youbiao1==0||youbiao1>7)youbiao1=7;
																						
																						else youbiao1--;
																						dati[youbiao]=youbiao1;
																				}
																				else{
																							if(youbiao1<=9||youbiao1>12)youbiao1=12;
																							else youbiao1--;
																						
																						dati[youbiao]=t1[youbiao1-9]+8;
																						}
																			   //
																			 
																				 break;
																																
																		}
															}
													 }}
                break;
													
        }
    }		
		Delay(600);
}
void init()
{
		P2M0=0x08;					//�����������
   	P2M1=0x00;
    P0M0=0xff;
    P0M1=0x00;
			
		P1ASF = 0x80;       //P1.7��Ϊģ�⹦��A/Dʹ��
		ADC_RES = 0;        //ת���������
    ADC_CONTR = 0x8F;   //cstAdcPower = 1
	  CLK_DIV = 0X00;     //ADRJ = 0    ADC_RES��Ÿ߰�λ���
		
		IT0 = 0;            //����IT0�����ش���
    IT1 = 0;
    EA = 1;             //CPU�����ж�
}
	void main()
	{
		
			init();

				product_data();//�ٴε��� ������������
				judge(t1[0],t1[1],t1[2],t1[3]); 			 //�ж�
		
					while(1)
						{
							
							NavKey_Process(); //��ȡ�����������
							if(sbtKey1 == 0) //����k1 ˢ����Ŀ
									{
											flag=0;
											product_data();
											judge(t1[0],t1[1],t1[2],t1[3]); 
									}
									if(sbtKey2==0)//����K2 ��ʾ�ο���  �ͷ��� ����ʾ�Ƿ��н�
									{	
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
									
									
							for(i=0;i<4;i++)	
									{
											P2=weixuan[i]; 
											P0=duanxuan[t1[i]];	
											Delay(600);	
									}		
								}									
		}

		
	