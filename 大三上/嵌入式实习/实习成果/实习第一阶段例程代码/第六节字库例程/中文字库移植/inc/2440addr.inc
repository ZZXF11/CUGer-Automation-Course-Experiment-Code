;====================================================================
; File Name : 2440addr.a
; Function  : TQ2440 Define Address Register (Assembly)
; Revision  : 1.0
;====================================================================

        GBLL   BIG_ENDIAN__
BIG_ENDIAN__   SETL   {FALSE}

;=================
; Memory control
;=================
BWSCON  	EQU  0x48000000     ;Bus width & wait status
BANKCON0	EQU  0x48000004     ;Boot ROM control
BANKCON1	EQU  0x48000008     ;BANK1 control
BANKCON2	EQU  0x4800000c     ;BANK2 control
BANKCON3	EQU  0x48000010     ;BANK3 control
BANKCON4	EQU  0x48000014     ;BANK4 control
BANKCON5	EQU  0x48000018     ;BANK5 control
BANKCON6	EQU  0x4800001c     ;BANK6 control
BANKCON7	EQU  0x48000020     ;BANK7 control
REFRESH 	EQU  0x48000024     ;DRAM/SDRAM refresh
BANKSIZE	EQU  0x48000028     ;Flexible Bank Size
MRSRB6  	EQU  0x4800002c     ;Mode register set for SDRAM Bank6
MRSRB7  	EQU  0x48000030     ;Mode register set for SDRAM Bank7


;==========================
; CLOCK & POWER MANAGEMENT
;==========================
LOCKTIME	EQU  0x4c000000     ;PLL lock time counter
MPLLCON 	EQU  0x4c000004     ;MPLL Control
UPLLCON 	EQU  0x4c000008     ;UPLL Control
CLKCON  	EQU  0x4c00000c     ;Clock generator control
CLKSLOW 	EQU  0x4c000010     ;Slow clock control
CLKDIVN 	EQU  0x4c000014     ;Clock divider control


;=================
; INTERRUPT
;=================
SRCPND   	EQU  0x4a000000    ;Interrupt request status
INTMOD   	EQU  0x4a000004    ;Interrupt mode control
INTMSK   	EQU  0x4a000008    ;Interrupt mask control
PRIORITY 	EQU  0x4a00000c    ;IRQ priority control           <-- May 06, 2002 SOP
INTPND   	EQU  0x4a000010    ;Interrupt request status
INTOFFSET	EQU  0x4a000014    ;Interruot request source offset
SUSSRCPND	EQU  0x4a000018    ;Sub source pending
INTSUBMSK	EQU  0x4a00001c    ;Interrupt sub mask


;=================
; I/O PORT for LED
;=================
GPFCON  	EQU  0x56000050     ;Port F control
GPFDAT  	EQU  0x56000054     ;Port F data
GPFUP   	EQU  0x56000058     ;Pull-up control F

;Miscellaneous register
MISCCR  	EQU  0x56000080     ;Miscellaneous control
DCKCON  	EQU  0x56000084     ;DCLK0/1 control
EXTINT0 	EQU  0x56000088     ;External interrupt control register 0
EXTINT1 	EQU  0x5600008c     ;External interrupt control register 1
EXTINT2 	EQU  0x56000090     ;External interrupt control register 2
EINTFLT0	EQU  0x56000094     ;Reserved
EINTFLT1	EQU  0x56000098     ;Reserved
EINTFLT2	EQU  0x5600009c     ;External interrupt filter control register 2
EINTFLT3	EQU  0x560000a0     ;External interrupt filter control register 3
EINTMASK	EQU  0x560000a4     ;External interrupt mask
EINTPEND	EQU  0x560000a8     ;External interrupt pending
GSTATUS0	EQU  0x560000ac     ;External pin status
GSTATUS1	EQU  0x560000b0     ;Chip ID(0x32440000)
GSTATUS2	EQU  0x560000b4     ;Reset type
GSTATUS3	EQU  0x560000b8     ;Saved data0(32-bit) before entering POWER_OFF mode
GSTATUS4	EQU  0x560000bc     ;Saved data1(32-bit) before entering POWER_OFF mode

;Added for 2440					; DonGo
MSLCON		EQU  0x560000cc     ;Memory sleep control register

;=================
; WATCH DOG TIMER
;=================
WTCON 	EQU  0x53000000       ;Watch-dog timer mode
WTDAT 	EQU  0x53000004       ;Watch-dog timer data
WTCNT 	EQU  0x53000008       ;Eatch-dog timer count

;=================
; Nand Flash
;=================
NFCONF		EQU	0x4E000000	;NAND Flash configuration
NFCONT		EQU	0x4E000004      ;NAND Flash control
NFCMD		EQU	0x4E000008      ;NAND Flash command
NFADDR		EQU	0x4E00000C      ;NAND Flash address
NFDATA		EQU	0x4E000010      ;NAND Flash data
NFDATA8		EQU	0x4E000010      ;NAND Flash data
NFMECCD0	EQU	0x4E000014      ;NAND Flash ECC for Main Area
NFMECCD1	EQU	0x4E000018
NFSECCD		EQU	0x4E00001C	;NAND Flash ECC for Spare Area
NFSTAT		EQU	0x4E000020	;NAND Flash operation status
NFESTAT0	EQU	0x4E000024
NFESTAT1	EQU	0x4E000028
NFMECC0		EQU	0x4E00002C
NFMECC1		EQU	0x4E000030
NFSECC		EQU	0x4E000034
NFSBLK		EQU	0x4E000038	;NAND Flash Start block address
NFEBLK		EQU	0x4E00003C	;NAND Flash End block address

        END
