/****************************************************************************************
* 文件名：GUI_BASIC.H
* 功能：GUI基本画图函数。
* 说明：
****************************************************************************************/
#ifndef  GUI_BASIC_H
#define  GUI_BASIC_H

#include "gui_types.h"
#include "lcmdrv.h"

/* 定义坐标数据结构 */
typedef  struct
         {  uint32  x;				// x坐标变量
            uint32  y;				// y坐标变量
         } 
         PointXY;


/****************************************************************************
* 名称：GUI_Rectangle()
* 功能：画矩形。
* 入口参数： x0		矩形左上角的x坐标值
*           y0		矩形左上角的y坐标值
*           x1      矩形右下角的x坐标值
*           y1      矩形右下角的y坐标值
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern  void  GUI_Rectangle(uint32 x0, uint32 y0, uint32 x1, uint32 y1, TCOLOR color);


/****************************************************************************
* 名称：GUI_RectangleFill()
* 功能：填充矩形。画一个填充的矩形，填充色与边框色一样。
* 入口参数： x0		矩形左上角的x坐标值
*           y0		矩形左上角的y坐标值
*           x1      矩形右下角的x坐标值
*           y1      矩形右下角的y坐标值
*           color	填充颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_RectangleFill(uint32 x0, uint32 y0, uint32 x1, uint32 y1, TCOLOR color);


/****************************************************************************
* 名称：GUI_Square()
* 功能：画正方形。
* 入口参数： x0		正方形左上角的x坐标值
*           y0		正方形左上角的y坐标值
*           with    正方形的边长
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_Square(uint32 x0, uint32 y0, uint32  with, TCOLOR  color);


/****************************************************************************
* 名称：GUI_Line()
* 功能：画任意两点之间的直线。
* 入口参数： x0		直线起点的x坐标值
*           y0		直线起点的y坐标值
*           x1      直线终点的x坐标值
*           y1      直线终点的y坐标值
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_Line(uint32 x0, uint32 y0, uint32 x1, uint32 y1, TCOLOR color);


/****************************************************************************
* 名称：GUI_LineWith()
* 功能：画任意两点之间的直线，并且可设置线的宽度。
* 入口参数： x0		直线起点的x坐标值
*           y0		直线起点的y坐标值
*           x1      直线终点的x坐标值
*           y1      直线终点的y坐标值
*           with    线宽(0-50)
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_LineWith(uint32 x0, uint32 y0, uint32 x1, uint32 y1, uint8 with, TCOLOR color);


/****************************************************************************
* 名称：GUI_LineS()
* 功能：多个点之间的连续连线。从第一点连到第二点，再连到第三点...
* 入口参数： points  多个点坐标数据的指针，数据排列为(x0,y0)、(x1,y1)、(x2,y2)...
*           no      点数目，至少要大于1
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_LineS(uint32 const *points, uint8 no, TCOLOR color);


/****************************************************************************
* 名称：GUI_Circle()
* 功能：指定圆心位置及半径，画圆。
* 入口参数： x0		圆心的x坐标值
*           y0		圆心的y坐标值
*           r       圆的半径
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_Circle(uint32 x0, uint32 y0, uint32 r, TCOLOR color);


/****************************************************************************
* 名称：GUI_CircleFill()
* 功能：指定圆心位置及半径，画圆并填充，填充色与边框色一样。
* 入口参数： x0		圆心的x坐标值
*           y0		圆心的y坐标值
*           r       圆的半径
*           color	填充颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_CircleFill(uint32 x0, uint32 y0, uint32 r, TCOLOR color);


/****************************************************************************
* 名称：GUI_Ellipse()
* 功能：画正椭圆。给定椭圆的四个点的参数，最左、最右点的x轴坐标值为x0、x1，最上、最下点
*      的y轴坐标为y0、y1。
* 入口参数： x0		最左点的x坐标值
*           x1		最右点的x坐标值
*           y0		最上点的y坐标值
*           y1      最下点的y坐标值
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_Ellipse(uint32 x0, uint32 x1, uint32 y0, uint32 y1, TCOLOR color);


/****************************************************************************
* 名称：GUI_EllipseFill()
* 功能：画正椭圆，并填充。给定椭圆的四个点的参数，最左、最右点的x轴坐标值为x0、x1，最上、最下点
*      的y轴坐标为y0、y1。
* 入口参数： x0		最左点的x坐标值
*           x1		最右点的x坐标值
*           y0		最上点的y坐标值
*           y1      最下点的y坐标值
*           color	填充颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_EllipseFill(uint32 x0, uint32 x1, uint32 y0, uint32 y1, TCOLOR color);


/****************************************************************************
* 名称：GUI_FloodFill()
* 功能：图形填充，将指定点内的封闭图形进行填充。对指定点的颜色区域进行填充，即不是该颜色
*      的像素为边界(如，指定点上的颜色为红色，则其它颜色像素均为边界)。
* 入口参数： x0		指定点的x坐标值
*           y0		指定点的y坐标值
*           color	填充颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围、指定点不在封闭图形内。
****************************************************************************/
extern void  GUI_FloodFill(uint32 x0, uint32 y0, TCOLOR color);


/****************************************************************************
* 名称：GUI_Arc4()
* 功能：画弧。起点及终点只能为0度-90度、90度-180度、180度-270度、270度-0度等。即分别
*      为第1-4像限的90度弧。
* 入口参数： x0		圆心的x坐标值
*           y0		圆心的y坐标值
*           r       圆弧的半径
*           angle	画弧的像限(1-4)
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_Arc4(uint32 x, uint32 y, uint32 r, uint8 angle, TCOLOR color);



/****************************************************************************
* 名称：GUI_Arc()
* 功能：指定起点、终点及半径画弧(不能画圆)。使用的是顺时针方向画图。
* 入口参数： x			圆心的x坐标值
*           y			圆心的y坐标值
*           stangle 	起始角度(0-359度)
*           endangle	终止角度(0-359度)
*           r  			圆的半径终点
*           color		显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_Arc(uint32 x, uint32 y, uint32 r, uint32 stangle, uint32 endangle, TCOLOR color);


/****************************************************************************
* 名称：GUI_Pieslice()
* 功能：指定起点、终点及半径扇形(不能画圆)。使用的是顺时针方向画图。
* 入口参数： x			圆心的x轴坐标值
*           y			圆心的y轴坐标值
*           stangle 	起始角度(0-359度)
*           endangle	终止角度(0-359度)
*           r  			圆的半径终点
*           color		显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
extern void  GUI_Pieslice(uint32 x, uint32 y, uint32 r, uint32 stangle, uint32 endangle, TCOLOR color);


/****************************************************************************
* 名称：GUI_CmpColor()
* 功能：判断颜色值是否一致。
* 入口参数：color1		颜色值1
*		   color2		颜色值2
* 出口参数：返回1表示相同，返回0表示不相同。
* 说明：由于颜色类型TCOLOR可以是结构类型，所以需要用户编写比较函数。
****************************************************************************/
extern int  GUI_CmpColor(TCOLOR color1, TCOLOR color2);

/****************************************************************************
* 名称：GUI_CopyColor()
* 功能：颜色值复制。
* 入口参数：color1		目标颜色变量
*		   color2		源颜色变量
* 出口参数：无
* 说明：由于颜色类型TCOLOR可以是结构类型，所以需要用户编写复制函数。
****************************************************************************/
extern void  GUI_CopyColor(TCOLOR *color1, TCOLOR color2);

#endif