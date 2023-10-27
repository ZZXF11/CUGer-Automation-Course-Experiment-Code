	
;====================
;clock registers
;===================

LOCKTIME	EQU	0x4c000000

MPLLCON		EQU	0x4c000004

CLKDIVN		EQU	0x4c000014

MPLL_200MHz	EQU	((0x5c<<12)+(0x01<<4)+(0x02))

;=================
; WATCH DOG TIMER
;=================

WTCON     EQU  0x53000000       ;Watch-dog timer mode

NOINT     EQU  0xc0    			;1100 0000
	
	
	IMPORT init_led
	
	IMPORT init_irq
	
	IMPORT irq_hander

	
	AREA  Init,CODE,READONLY   ;��αָ�����һ������Σ�����ΪInit������ֻ��
		
	ENTRY                      ;�������ڵ��ʶ
	

;*************************************************************;�ж�����,��������,��Reset��HandleIRQ��,�����쳣������û��ʹ��

;*************************************************************
	
	b Reset;@0x04:δ����ָ����ֹģʽ��������ַ

HandleUndef
	
	b HandleUndef;@0x08:����ģʽ��������ַ��ͨ��SWIָ������ģʽ

HandleSWI
	
	b HandleSWI
;@0x0c:ָ��Ԥȡ��ֹ���µ��쳣��������ַ

HandlePrefetchAbort
	
	b HandlePrefetchAbort;@0x10:���ݷ�����ֹ���µ��쳣��������ַ

HandleDataAbort
	
	b HandleDataAbort;@0x14:����

HandleNotUsed
	
	b HandleNotUsed
;@0x18:�ж�ģʽ��������ַ
	
	b HandleIRQ;@0x1c:���ж�ģʽ��������ַ

HandleFIQ
	
	b HandleFIQ
	
Reset   
	ldr     r0,=WTCON
	
	mov     r1,#0x0
	
	str     r1,[r0]
	
	
	ldr	r0,=LOCKTIME	;//set locktime//
	
	ldr	r1,=0xffffffff
	
	str	r1,[r0]	
	
	ldr	r0,=CLKDIVN		;//set clock ratio//
	
	mov	r1,#0x5			;//FCLK:HCLK:PCLK=1:2:4//
	
	str	r1,[r0]	
	
	ldr	r0,=MPLLCON		;//set MPLL//
	
	ldr	r1,=MPLL_200MHz
	
	str	r1,[r0]			;//Fout=200MHz//
	
	
	mrc	p15,0,r1,c1,c0,0	;//set asynchronous bus mode//
	
	orr	r1,r1,#0xc0000000
	
	mcr	p15,0,r1,c1,c0,0	
	
	

	ldr sp,=1024*4
	
	
	msr cpsr_c,#0xd2
	

	ldr sp,=1024*3
	
	
	msr cpsr_c,#0xdf
	

	bl init_led
	
	bl init_irq
	
	msr cpsr_c,#0x5f	

halt_loop
	
	b halt_loop
HandleIRQ
	
	sub lr, lr, #4
	
	stmdb sp!, {r0-r12,lr}
	
	ldr lr, =irq_return
	
	ldr pc, =irq_hander
irq_return
	
	ldmia sp!, {r0-r12,pc}^
	
;delay function
	
	EXPORT delay

delay
	
	sub r0,r0,#1              ;r0=r0-1            
	
	cmp r0,#0x0               ;��r0��ֵ��0��Ƚ�
	
	bne delay                ;�ȽϵĽ����Ϊ0��r0��Ϊ0������������delay,����ִ����һ�����
	
	mov pc,lr                 ;����
	
	

	EXPORT	EnterCritical
EnterCritical   
	
	mrs	r1, cpsr
	
	str	r1, [r0]
	
	orr	r1, r1, #NOINT	;NOINIT=0xC0 disables interrupt
	
	msr	cpsr_cxsf, r1		
	
	mov pc,lr
	
;restore cpsr, r0 = address to restore cpsr	
	

	EXPORT	ExitCritical

ExitCritical
	
	ldr	r1, [r0]
	
	msr	cpsr_cxsf, r1	
	
	mov pc,lr	
    
    
	END                       ;��������� 

;�����cxsf��ʾ�ӵ͵��߷ֱ�ռ�õ�4��8bit��������-  
;ָ������ʱ���г���cpsr_cf, cpsr_all, cpsr_c�ȣ����-  
;c ָCPSR�е�control field ( PSR[7:0])-  
;f ָflag field (PSR[31:24])-  
;x ָ extend field (PSR[15:8])-  
;s ָstatus field ( PSR[23:16])-  
;����cpsr��λ��ʾΪ��-  
;31 30 29 28 --- 7 6 -  4   3   2   1   0-  
;N  Z  C  V      I F   M4  M3  M2  M1  M0  
	