;汇编指令实验
;定义端口B寄存器预定义
GPBCON EQU 0x56000010
GPBDAT EQU 0x56000014
GPBUP EQU  0x56000018
   
	AREA Init,CODE,READONLY ;该伪指令定义了一个代码段，段名为Init，属性只读
   	ENTRY ;程序的入口点标识
ResetEntry
	;下面这三条语句，主要是用来设置GPB5--GPB8为输出属性
	ldr r0,= GPBCON  ;将寄存器GPBCON的地址存放到寄存器r0中
	ldr r1,=0x15400
	str r1,[r0]         ;将r1中的数据存放到地址为r0的内存单元中

	;下面这三条语句，设置GPB5--GPB8禁止上拉电阻
   	ldr r0,= GPBUP
	ldr r1,=0xffff
	str r1,[r0]

	ldr r2,=GPBDAT   ; 将寄存器GPBDAT的地址存放到寄存器r2中

ledloop
	ldr r1,=0xffff
	
  	str r1,[r2]      ;使 GPB--GPB8输出高电平，LED1--LED4全灭  
  	bl delay        ;调用延迟子程序

	ldr r1,=0x1c0
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
   	
   	ldr r1,=0x1a0
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x180
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x160
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x140
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x120
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x100
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x0e0
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	
	ldr r1,=0x0c0
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
   	
   	ldr r1,=0x0a0
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x080
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x060
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x040
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x020
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
	ldr r1,=0x000
	str r1,[r2]       ; 使GPB5输出低电平，GPB6--GPB8输出高电平，LED1亮   1 
	bl delay           ;调用延迟子程序
	
   	
   	b ledloop         ;不断的循环，LED1-LED7将不停的闪烁

;下面是延迟子程序
delay
	ldr r3,=0xbffff ;设置延迟的时间
delay1
	sub r3,r3,#1 ;r3=r3-1
	cmp r3,#0x0 ;将 r3 的值与 0 相比较
   	bne delay1 ;比较的结果不为 0（r3 不为 0），继续调用 delay1,否则执行下一条语句
   
   	mov pc,lr ;返回
   	END ;程序结束符
