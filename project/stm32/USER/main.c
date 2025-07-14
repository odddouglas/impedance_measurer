#include "stm32_config.h"
#include "lcd.h"
#include "AD5933.h"
#include "interface.H"

float R_Impedance, realData, imageData; // ���гֵ������ֵ��ʵ�����ݣ��鲿����
char disStr[64];
// ��interface.H���޸ĺ궨�壬�Ҹ���ģ������ñλ�ã����Ĳ�������
int main(void)
{
    MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); // �����жϷ���
    delay_init(72);                                     // ��ʼ����ʱ����
    initial_lcd();                                      // ��ʼ��LCD

    // ע�⣺
    // AD5933ģ��Ĭ���ʺϲ�������5.1K-10M���裬�������С����ʱ�����������������㣬��Ҫʹ���ⲿ�˷ŵ�·��ǿ�����������Ӷ�����С��5.1K��С����
    // �������ڻ�С��5.1K�ĵ���ʱ�������ģ��������ñλ��
    // �ӷ�1�������� ��5.1K( 5.1K-10M)����ʱ,������ñ��ģ��������P6��1��2���ӣ�P6��3,4�Ͽ���P5��1,2�Ͽ���(��interface.H�д򿪺궨��#define _DEF_RSBIGGER5K		1)
    // �ӷ�2������С��5.1K(100R-5.1K)����ʱ,������ñ��ģ��������P6��1��2�Ͽ���P6��3,4���ӣ�P5��1,2���ӣ�(��interface.H�д򿪺궨��#define _DEF_RSBIGGER5K		0)

#if _DEF_RSBIGGER5K == 1 // ��interface.H�д򿪴˺궨�壬����ע����������ñ���ɲ����ϴ����
    LCD_Show_CEStr(0, 0, (u8 *)"5K<�������<5M  ");
#elif DEF_RSBIGGER5K == 0 // ��interface.H�д򿪴˺궨�壬����ע����������ñ���ɲ�����С����
    LCD_Show_CEStr(0, 0, "100R<�������<8K");
#endif

    while (1) {
        DA5933_Get_RsRealImage(&R_Impedance, &realData, &imageData); // �������гֵ������ֵ����ʵ�����ݣ��鲿����

        FormatRsDisStr(R_Impedance, disStr); // ����ֵ��ʾ
        LCD_Show_CEStr(20, 2, (u8 *)disStr);
        sprintf(disStr, "ʵ������:%06.0f  ", realData); // ʵ��������ʾ
        LCD_Show_CEStr(0, 4, (u8 *)disStr);
        sprintf(disStr, "�鲿����:%06.0f  ", imageData); // �鲿������ʾ
        LCD_Show_CEStr(0, 6, (u8 *)disStr);
    }
}
