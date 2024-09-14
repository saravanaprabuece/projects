/*
This Project is made for the demonstration purpose which is useful for the college purpose.
It contains three candidates: AAP, BJP, INC
Votes are stored in EEPROM, hence loss of supply or power ensures the votes are safe with the device and the voting process can be resumed.
PIC16F877a is an 8bit microcontroller from Microchip company.
It is one of the important microcontroller in the 8bit Microcontroller industry.

************ ENJOY CODING*****************************

*********AUTHOR: VISHAL KUMAR *************
*********Description: Electronics Guy ************
*********Profile : http://github.com/vishalkumargithub 
*/
#include<pic.h>
#define lcdport PORTB
#define EN RD7
#define RS RD6

int del=0,count=0,two=0,three=0,d=0,a=0,d2=0,a2=0,d3=0,a3=0,aa=0;
void cmd();
void data();
void delay(unsigned int);
void write(unsigned char adr,unsigned char dat);
void can1(unsigned char,unsigned char,unsigned char);
void can2(unsigned char,unsigned char,unsigned char);
void can3(unsigned char,unsigned char,unsigned char);
void disable();
void clear();
unsigned char read(unsigned char);

void clear()
{
write(0x01,0x00);
write(0x08,0x00);
write(0x15,0x00);
count=read(0x01);
two=read(0x01);
three=read(0x01);
}
char arr[40]={"                 Digital Voting Machine"};
char candi[14]={"AAP  BJP  INC"};
char line[17]={"***  ***  *** DV"};
char aap[]={"AAP=    BJP=    INC=    "};

void cmd()
{
	RS=0;
	EN=1;//ENABLES HIGH PULSE
	delay(250);
	EN=0;//ENABLES LOW PULSE
	delay(500);
}

void data()
{
	RS=1;
	EN=1;//ENABLES HIGH PULSE
	delay(250);
	EN=0;//ENABLES LOW PULSE
     delay(500);
}

void disable()
{
	line[14]='D';
	lcdport=0xC0;
	cmd();
	for(int k2=0;k2<22;k2++)
	{
		lcdport=line[k2];
		data();		
	}
}	

void main()
{		
	int y=0;char count,two,three;
	TRISB=0x00;PORTB=0x00;
	TRISD=0x0F;PORTD=0x00;
	TRISC=0X33;PORTC=0X00;
	lcdport=0x38;//INITIALISING LCD
	cmd();
	
	lcdport=0x0C;//LCD ON WITHOUT CURSOR
	cmd();
	lcdport=0x01;//CLEARS CONTENT OF LCD INITIALLY
	cmd();	
	
	lcdport=0x80;//FIRST ADDRESS OF LCD REGISTERS/RAM ADDRESS
	cmd();
	while(1)
	{
	for(int i=0;i<39;i++)
	{
	lcdport=arr[i];//MOVING 'D' TO ADDRESS 0x80 AS A DATA
	data();	
	}
	//For rotation of Digital Voting machine
	for(int y=0;y<39;y++) 
	{
      lcdport=0x18;
	cmd();
	delay(60000);
	delay(40000);
	}
	lcdport=0x01;
	cmd();
	delay(60000);
	delay(60000);
	lcdport=0x80;
	cmd();
	for(int j=0;j<13;j++)
	{
	lcdport=candi[j];//MOVING 'D' TO ADDRESS 0x80 AS A DATA
	data();	
	}
	lcdport=0xC0;
	cmd();
	
	for(int k=0;k<22;k++)
	{
	lcdport=line[k];
	data();		
	}
		RC2=1;//FOR LED
	while(RC0==0);
	
	z: // The main logic(IMPORTANT)	
	while(1)
	{
	
	if(RC0==1)//Checks Authority button
	{		
		RC2=0;RC3=1;
		line[14]='E';
			lcdport=0xC0;
			cmd();
			for(int k1=0;k1<22;k1++)
			{
				lcdport=line[k1];
				data();		
			}
			
		while(RD2!=1||RD3!=1||RC4!=1||RC5!=1) // Untill the key is pressed or waiting the for the key to be released
		{
		if(RD2==1)//Candidate 1
		{
			while(RD2==1);		
		     count++;
		     disable();
			write(0x01,count);
			RC3=0;RC2=1;//LED
			goto z;
		}	
		if(RD3==1)//Candidate2
		{
			while(RD3==1);
			two=two++;
			disable();
			write(0x08,two);
			RC3=0;RC2=1;
			goto z;
		}
		if(RC4==1) //Candidate 3
		{
			while(RC4==1);
			three=three++;
			disable();
			write(0x15,three);
			RC3=0;RC2=1;
			goto z;
		}
		if(RC5==1)//CLEAR EEPROM
		{
			
			while(RC5==1);
			RC3=0;RC2=1;
			disable();
			write(0x01,0x00);write(0x08,0x00);write(0x15,0x00);
			count=read(0x01);two=read(0x08);three=read(0x15);
			delay(60000);
			goto z;
		}	
		
		if(RC1==1) // RESULT SWITCh
		{
		count=read(0x01);
		two=read(0x08);
		three=read(0x15);
		if(count>two&&count>three)
		{
		can1(count,two,three);
		}
		if(two>count&&two>three)
		{
		can2(count,two,three);
		}
		if(three>two&&three>count)
		{
		can3(count,two,three);
		}
		if(count==two&&two==three)
		{
		char error[]={" Something went"};
		char error2[]={" wrong !!"};
		lcdport=0x01;
		cmd();
		lcdport=0x80;
		cmd();
		for(int err=0;err<15;err++)
		{
		lcdport=error[err];
		data();
		}
		lcdport=0xC0;
		cmd();
		for(int err2=0;err2<9;err2++)
		{
		lcdport=error2[err2];
		data();
		}
		for (int del=0;del<20;del++)
		{
		delay(60000);
		}
		clear();
		main();	
		}	
		
		}		
    }
    }
    }
}
}
void delay(unsigned int x)
{
	while(x>0)
	x--;
}

void write(unsigned char adr,unsigned char dat)
{
	EEPGD=0;//selecting the data memory
	EEADR=adr;//selects adress in EEADR
	EEDATA=dat;//stores value in 0x34
	WRERR=0;//write operation completed
	WREN=1;//Allows write cycle
	EECON2=0x55;//necessary condition for writing
	EECON2=0xAA;
	WR=1;
	while(WR==1);
	WREN=0;
}

void can1(unsigned char count,unsigned char two,unsigned char three)
{
	lcdport=0x01;
	cmd();
	lcdport=0x80;
	cmd();
char cand1[16]={" AAP wins!!"};
for(int c1=0;c1<11;c1++)
{
lcdport=cand1[c1];
data();
}
for(int del=0;del<60;del++)
{
delay(60000);
}
lcdport=0x01;
cmd();
lcdport=0x80;
cmd();
int d=(count/0x0A)%0x0A;// Stores the ten's digit of count
int a =count%0x0A;//stores the unit digit of count

aap[4]=d+48;
aap[5]=a+48;

int d2=(two/0x0A)%0x0A;// Stores the ten's digit of two
int a2 =two%0x0A;//stores the unit digit of two
aap[12]=d2+48;
aap[13]=a2+48;

int d3=(three/0x0A)%0x0A;// Stores the ten's digit of three
int a3 =three%0x0A;//stores the unit digit of three
aap[20]=d3+48;
aap[21]=a3+48;


for(int aa=0;aa<23;aa++)
{
lcdport=aap[aa];
data();
}
for(int r=0;r<62;r++)
{
lcdport=0x18;
cmd();
delay(60000);
delay(40000);
}

for(int del=0;del<20;del++)
{
delay(50000);
}

write(0x01,0);write(0x08,0);write(0x15,0);
count=read(0x01);two=read(0x08);three=read(0x15);
disable();
main();

}
void can2(unsigned char count,unsigned char two,unsigned char three)
{
	lcdport=0x01;
	cmd();
	lcdport=0x80;
	cmd();
char cand2[16]={" BJP wins!!"};
for(int c2=0;c2<11;c2++)
{
lcdport=cand2[c2];
data();
}
for(int del=0;del<60;del++)
{
delay(60000);
}
lcdport=0x01;
cmd();
lcdport=0x80;
cmd();
int d=(count/0x0A)%0x0A;// Stores the ten's digit of count
int a =count%0x0A;//stores the unit digit of count

aap[4]=d+48;
aap[5]=a+48;

int d2=(two/0x0A)%0x0A;// Stores the ten's digit of two
int a2 =two%0x0A;//stores the unit digit of two
aap[12]=d2+48;
aap[13]=a2+48;

int d3=(three/0x0A)%0x0A;// Stores the ten's digit of three
int a3 =three%0x0A;//stores the unit digit of three
aap[20]=d3+48;
aap[21]=a3+48;


for(int aa=0;aa<23;aa++)
{
lcdport=aap[aa];
data();
}
for(int r=0;r<62;r++)
{
lcdport=0x18;
cmd();
delay(60000);
delay(40000);
}
for(int del=0;del<20;del++)
{
delay(50000);
}

write(0x01,0);write(0x08,0);write(0x15,0);
count=read(0x01);two=read(0x08);three=read(0x15);
disable();
main();
}

void can3(unsigned char count,unsigned char two,unsigned char three)
{
	lcdport=0x01;
	cmd();
	lcdport=0x80;
	cmd();
char cand3[16]={" Congress wins!!"};
for(int c3=0;c3<16;c3++)
{
lcdport=cand3[c3];
data();
}
for(int del=0;del<60;del++)
{
delay(60000);
}
lcdport=0x01;
cmd();
lcdport=0x80;
cmd();
int d=(count/0x0A)%0x0A;// Stores the ten's digit of count
int a =count%0x0A;//stores the unit digit of count

aap[4]=d+48;
aap[5]=a+48;

int d2=(two/0x0A)%0x0A;// Stores the ten's digit of two
int a2 =two%0x0A;//stores the unit digit of two
aap[12]=d2+48;
aap[13]=a2+48;

int d3=(three/0x0A)%0x0A;// Stores the ten's digit of three
int a3 =three%0x0A;//stores the unit digit of three
aap[20]=d3+48;
aap[21]=a3+48;


for(int aa=0;aa<23;aa++)
{
lcdport=aap[aa];
data();
}
for(int r=0;r<62;r++)
{
lcdport=0x18;
cmd();
delay(60000);
delay(40000);
}
for(int del=0;del<20;del++)
{
delay(50000);
}

write(0x01,0);write(0x08,0);write(0x15,0);
count=read(0x01);two=read(0x08);three=read(0x15);
disable();
main();
}

unsigned char read(unsigned char adr)
{
	unsigned char dat;
	EEPGD=0;
	EEADR=adr;
	WREN=0;//Disables write cycle
	RD=1;//Enables write operation
	while(RD==1);
	dat=EEDATA;
	return(dat);
}		




			