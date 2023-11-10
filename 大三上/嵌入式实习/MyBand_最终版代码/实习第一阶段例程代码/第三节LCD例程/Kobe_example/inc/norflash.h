#ifndef	__NORFLASH_H
#define	__NORFLASH_H

int UnlockAllBlks(void);
int ChkNorFlash(void);
void ProgNorFlash(U32 addr, U32 src, U32 len);


#endif