.equ	rGPBCON,0x56000010  
.equ	rGPBDAT,0x56000014
.equ	rGPBUP,0x56000018

.global _start
_start:
    @config GPB5 as output pin
    ldr  r0,=rGPBCON            
    ldr  r1,=0x400
    str  r1,[r0]
    
    @disable pull up function 
    ldr  r0,=rGPBUP
    ldr  r1,=0xffff
    str  r1,[r0]
    
    ldr  r2,=rGPBDAT
     
ledloop:
    ldr  r1,=0xff             
    str  r1,[r2]              @set GPB5 state as high level,light off LED1
    bl   delay
	
    ldr r1,=0x0
    str r1,[r2]               @set GPB5 state as low level,light on LED1
    bl  delay
    b  ledloop 
    
@delay function
delay: 
	ldr r3,=0xbffff           @set the time of delay
delay1:
	sub r3,r3,#1         
	cmp r3,#0x0
	bne delay1
	mov pc,lr                 @return
    
    
  
