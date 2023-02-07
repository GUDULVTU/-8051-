/********************************************************************************************************************************************/



/********************************************************************************************************************************************/
/*
    sectional  :Time_sub_Function.h file
		part       :second part
    Project    :Clock
*/

// head file
#include <intrins.h>                                                     //������ȷʱ�Ӻ���
#include <reg52.h>                                                       // ����C52��
#include <math.h>                                                        // ������ѧ���㺯��ԭ��
//define I/O---------------------------------------------------------------------------------------------------------
sbit left        = P3 ^ 1;                                               //�������ư���
sbit right       = P3 ^ 0;                                               //�������ư���
sbit add         = P3 ^ 2;                                               //����Ӱ���
sbit subtraction = P3 ^ 3;                                               //���������
sbit pm          = P2 ^ 5;                                               //�������������
sbit restart     = P1 ^ 2;                                               //����������ͣ����
sbit kk          = P1 ^ 7;                                               //�������ɨ��˿�
sbit end         = P1 ^ 3;                                               //�����������
//��������---------------------------------------------------------------------------------------------------------
int sum_time_1 = 0;                                                      //������ʱ��
int address    = 0;
//-------------------------------------------------------------------------------------------------
int printf_value[8], printf_value_1[8];                                  //�������ֵ1��2
int address_array[8] = {0x1c,0x18,0x14,0x10,0x0c,0x08,0x04,0x00};        //����ɨ�����ţ���������ɨ��
int value();                                                             //��ֵ����
// struct-----------------------------------------------------------------------------------------
struct date_struct {                                                    //����ʱ��ṹ��
    int hour;
    int minute;
    int second;
};
struct date_struct set_date, date, *date_change = &date, *date_change_1 = &set_date; //����ṹ�壬��ṹ��ָ��
// all sub_Function--------------------------------------------------------------------------------
void display(int location, int number);                                             //����Ӧλ����ʾ��Ӧ������
void date_struct_change();                                                          //����λ���ַֽ⺯��
void format(int sumTime);                                                           //��ʽ������
void (*function[2])();                                                              //����ָ�뺯��
void returnnumber();                                                                //�Զ�Ӧλ�ý������ֵ�16���Ƹ�ֵ
int *var_number();                                                                  // 1-9���ִ��뺯��
void delay_1();                                                                     //��ʱ����
void init();                                                                        //��ʼ������
void delay(unsigned int ms);                                                        //��ʱ����2
// delay function--------------------------------------------------------------------------------
void delay_1()                                                                      //@12.000MHz
{
    _nop_();
}
void delay(unsigned int ms)
{
    unsigned char tt;
    while (ms--) {                                                                  // ��ѭ��
        for (tt = 0; tt < 246; tt++) {}                                             // ��ѭ��,�γ�ms�ź�
    }
}

// variable number array--------------------------------------------------------------------------------
int *var_number()
{
    int array[10] = {~0xc0, ~0xf9, ~0xa4, ~0xb0, ~0x99, ~0x92, ~0x82, ~0xf8, ~0x80, ~0x90};
    int *p;
    p = array;
    return p;
}
// format sumTime value--------------------------------------------------------------------------
void format(int sumTime)
{
    date_change->second = sumTime; //���븳ֵ
}
// date_struct_change--------------------------------------------------------------------------------
void date_struct_change()																								//����ʮλ�������
{
    printf_value[0] = (date_change->hour) / 10;
    printf_value[1] = (date_change->hour) % 10;
    printf_value[3] = (date_change->minute) / 10;
    printf_value[4] = (date_change->minute) % 10;
    printf_value[6] = (date_change->second) / 10;
    printf_value[7] = (date_change->second) % 10;
}
// value------------------------------------------------------------------------------------------------
int value(int value)																									 //����valueֵ����ÿ��λ����
{
    int sub_value = 0;
    sub_value     = *(var_number() + value);
    return sub_value;
}
// returnnumber----------------------------------------------------------------------------------------------
void returnnumber()																										  //��ʾ�����鸳ֵ
{
    int i;
    for (i = 0; i < 8; ++i) {
        printf_value_1[i] = value(printf_value[i]);
        if (i == 2 || i == 5) {
            printf_value_1[i] = ~0xbf;
            continue;
        }
    }
}
// display------------------------------------------------------------------------------------------------
void display(int location, int number)															  	//��ʾ����
{
//    P0 = 0xff;
   
        P2 = address_array[location], P0 = printf_value_1[number];
   
    delay_1();
}
// init------------------------------------------------------------------------------------------------
void init()																													//��ʼ������
{
    date.second = 0;
    date.minute = 0;
    date.hour   = 0;
    date_change->second = 0;
    date_change->minute = 0;
    date_change->hour   = 0;
    date_change_1->second = 0;
    date_change_1->minute = 0;
    date_change_1->hour   = 0;
}