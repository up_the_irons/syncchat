/****************************************************************************
 * Reggie, the Reg' Number Generator! v2.0 *** Copyright (C) 1995,  Ryan Dodd
 ****************************************************************************
 * Coded Originally In 	TURBO PASCAL 7.0 	on 6/8/95
 * And Translated To 	TURBO C 3.0 		on 9/24/95
 ****************************************************************************
 ********************* v2.0 ---- SyncChat                ********************
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
/* #include <conio.h> */

#define TLB textcolor(9)
#define TDB textcolor(1)
#define TDW textcolor(7)
#define TDG textcolor(2)
#define TLW textcolor(15)

void main()
{
	long namecode = 0, bbscode = 0;
	long index, len, len1, len2, regcode;
	char name[50], bbsname[50], temp;

	//clrscr();
	//TLB;
	//cprintf("Enter sysop's name EXACTLY as it is shown in Registration.\r\n");
	printf("Enter sysop's name EXACTLY as it is shown in Registration.\r\n");
	//TDB;
	//cprintf(": ");
	printf(": ");
	gets(name);
	len = strlen(name);
	//TLB;
	//cprintf("\n\nEnter sysop's BBS name EXACTLY as it is shown in Registration.\r\n");
	printf("\n\nEnter sysop's BBS name EXACTLY as it is shown in Registration.\r\n");
	//TDB;
	//cprintf(": ");
	printf(": ");
	gets(bbsname);
	len1 = strlen(bbsname);
	len2 = len+len1;
	len2 = len2+( (atol(name) + 9) * (atol(bbsname) + 3) );
  len2 = len2*105;
	len2 = len2*34;
	for(index = 0 ; index <= len ; index++)
	{
			temp = name[index];
			namecode = namecode + temp;
	}

	temp = 0;
	for(index = 0 ; index <= len1 ; index++)
	{
			temp = bbsname[index];
			bbscode = bbscode + temp;
	}
	regcode = ((namecode*len)+(bbscode));
	regcode = regcode*len2;
	//TDG;
	//cprintf("\nYour Registration number is ");
	printf("\nYour Registration number is ");
	//TLW;
	//cprintf("%li.\r\n\r\n", regcode);
	printf("%li.\r\n\r\n", regcode);
	//TDW;
}
