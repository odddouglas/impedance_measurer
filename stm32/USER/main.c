#include "stm32_config.h"
#include "lcd.h"
#include "AD5933.h"
#include "interface.H"

float R_Impedance, realData, imageData; // 所夹持电阻的阻值，实部数据，虚部数据
char disStr[64];
// 在interface.H中修改宏定义，且更改模块跳线帽位置，更改测量量程
int main(void)
{
    MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); // 设置中断分组
    delay_init(72);                                     // 初始化延时函数
    initial_lcd();                                      // 初始化LCD

    // 注意：
    // AD5933模块默认适合测量测量5.1K-10M电阻，需测量更小电阻时，自身驱动能力不足，需要使用外部运放电路增强驱动能力，从而测量小于5.1K的小电阻
    // 测量大于或小于5.1K的电阻时，需更改模块上跳线帽位置
    // 接法1，测量大 于5.1K( 5.1K-10M)电阻时,用跳线帽将模块上排针P6的1、2连接，P6的3,4断开，P5的1,2断开；(至interface.H中打开宏定义#define _DEF_RSBIGGER5K		1)
    // 接法2，测量小于5.1K(100R-5.1K)电阻时,用跳线帽将模块上排针P6的1、2断开，P6的3,4连接，P5的1,2连接；(至interface.H中打开宏定义#define _DEF_RSBIGGER5K		0)

#if _DEF_RSBIGGER5K == 1 // 至interface.H中打开此宏定义，按其注释连接跳线帽，可测量较大电阻
    LCD_Show_CEStr(0, 0, (u8 *)"5K<电阻测量<5M  ");
#elif DEF_RSBIGGER5K == 0 // 至interface.H中打开此宏定义，按其注释连接跳线帽，可测量较小电阻
    LCD_Show_CEStr(0, 0, "100R<电阻测量<8K");
#endif

    while (1) {
        DA5933_Get_RsRealImage(&R_Impedance, &realData, &imageData); // 测量所夹持电阻的阻值，及实部数据，虚部数据

        FormatRsDisStr(R_Impedance, disStr); // 电阻值显示
        LCD_Show_CEStr(20, 2, (u8 *)disStr);
        sprintf(disStr, "实部数据:%06.0f  ", realData); // 实部数据显示
        LCD_Show_CEStr(0, 4, (u8 *)disStr);
        sprintf(disStr, "虚部数据:%06.0f  ", imageData); // 虚部数据显示
        LCD_Show_CEStr(0, 6, (u8 *)disStr);
    }
}
