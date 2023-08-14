- [写在前面](#写在前面)
- [课程安排及要求](#课程安排及要求)
- [使用](#使用)
  - [原理图](#原理图)
  - [PCB板](#pcb板)
  - [代码](#代码)
- [特别提醒](#特别提醒)

#电路综合实践
---
# 写在前面
___
这是一门浙江大学生仪学院开的短学期课程，全称为电路综合创新实践。此门课程，是我认为从严格意义上来说第一门电路实践课程。(~~虽然之前的单片机也有实验课程，但张老师的实验真的可以说是一言难尽~~)在短学期中大约两三个星期的时间里，我第一次实现了从画原理图，到pcb封装，再投版制作，焊接，最后写代码这一完整的流程。在这里真得**感谢刘雪松老师和助教gg的答疑，非常的耐心，几乎是手把手教学**，也正因如此，课程给我的大体感受很好，是生仪为数不多学到东西的课程。
# 课程安排及要求
___
课程安排三个星期，但实际上越早做完就能越早结束，可能用两到三天的时间完成授课，其余时间便是自己动手完成项目，可以在自己寝室，也可以在专教中完成，建议是自己遇到问题后到专教问老师或者助教。要求每个学期都差不多。2023短学期，可以在计温、nfc、和计步器三个中任选其一，或者自己已经有计划。我选的是用**芯片ADXL345以及OLED屏完成计步器的实现**。整个项目可大致分为：
>1. **画原理图**
>2. **做元件的封装以及pcb板制作**
>3. 投板（投给厂家，自己不用做）
>4. 写代码，以及调试.
在验收时，老师会检查你的原理图、pcb图、代码、以及完成效果。

# 使用
___
## 原理图
1. 画元器件
> Csv文件的编写可参考Csv_Libary的文件，以及器件资料中的相关规范。

2. 画原理图
> 原理图的连接可参考Design_entry的文件，也可在网上搜索51单片机各模块的基本电路。
> ==连接前要想清楚个引脚的功能，连错等到板子做好了再改很麻烦==

## PCB板
1. 器件的封装
> 在原理图中画完元器件后，应给每个元器件做PCB的封装，详细步骤参考ppt，在做封装前，应通过datasheet了解元件的尺寸以及各引脚的作用。

2. 画pcb
>详细阅读制作规范；
>制作时可以尽可能多的探索左边工具栏的作用，可以节省不少的时间。

## 代码
我是参考的网上的ADXL345做计步器和OLED显示的代码，也就没啥好说的。

# 特别提醒
____
如何参考我的原理图的话，有两处错误，USB通信口，以及OLED通过IIC通信的接口连接有问题，可以看一下。