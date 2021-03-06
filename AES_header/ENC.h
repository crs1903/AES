#ifndef __AES_ENC_STD_H
#define __AES_ENC_STD_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define subByte(a) (SBOX[((a)>>4)&0xf][a&0xf])
#define PI(i,j) (subByte(((i)<<4)+(j)))
#define Word(a,i) (((a)>>((3-(i))<<5))&0xffffffff)
#define Byte(b,i) (((b)>>((3-(i))<<3))&0xff)
#define rotWord(W) ((Byte(W,1)<<24)|(Byte(W,2)<<16)|(Byte(W,3)<<8)|Byte(W,0))
#define subWord(W) ((subByte(Byte(W,0))<<24)|(subByte(Byte(W,1))<<16)|(subByte(Byte(W,2))<<8)|subByte(Byte(W,3)))
#define putAt(t,i,j) (((t)<<((3-(i))<<5))<<((3-(j))<<3))
#define inv(a) (INV[((a)>>4)&15][(a)&15])

typedef __uint128_t uint128;

unsigned int const I = 0b100011011;
unsigned char const SBOX[16][16] =  {	{0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76 },
					{0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0 },
					{0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15 },
					{0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75 },
					{0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84 },
					{0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf },
					{0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8 },
					{0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2 },
					{0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73 },
					{0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb },
					{0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79 },
					{0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08 },
					{0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a },
					{0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e },
					{0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf },
					{0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16 }	};

unsigned char const INV[16][16] =   {	{0x00 ,0x01 ,0x8d ,0xf6 ,0xcb ,0x52 ,0x7b ,0xd1 ,0xe8 ,0x4f ,0x29 ,0xc0 ,0xb0 ,0xe1 ,0xe5 ,0xc7 },
					{0x74 ,0xb4 ,0xaa ,0x4b ,0x99 ,0x2b ,0x60 ,0x5f ,0x58 ,0x3f ,0xfd ,0xcc ,0xff ,0x40 ,0xee ,0xb2 },
					{0x3a ,0x6e ,0x5a ,0xf1 ,0x55 ,0x4d ,0xa8 ,0xc9 ,0xc1 ,0x0a ,0x98 ,0x15 ,0x30 ,0x44 ,0xa2 ,0xc2 },
					{0x2c ,0x45 ,0x92 ,0x6c ,0xf3 ,0x39 ,0x66 ,0x42 ,0xf2 ,0x35 ,0x20 ,0x6f ,0x77 ,0xbb ,0x59 ,0x19 },
					{0x1d ,0xfe ,0x37 ,0x67 ,0x2d ,0x31 ,0xf5 ,0x69 ,0xa7 ,0x64 ,0xab ,0x13 ,0x54 ,0x25 ,0xe9 ,0x09 },
					{0xed ,0x5c ,0x05 ,0xca ,0x4c ,0x24 ,0x87 ,0xbf ,0x18 ,0x3e ,0x22 ,0xf0 ,0x51 ,0xec ,0x61 ,0x17 },
					{0x16 ,0x5e ,0xaf ,0xd3 ,0x49 ,0xa6 ,0x36 ,0x43 ,0xf4 ,0x47 ,0x91 ,0xdf ,0x33 ,0x93 ,0x21 ,0x3b },
					{0x79 ,0xb7 ,0x97 ,0x85 ,0x10 ,0xb5 ,0xba ,0x3c ,0xb6 ,0x70 ,0xd0 ,0x06 ,0xa1 ,0xfa ,0x81 ,0x82 },
					{0x83 ,0x7e ,0x7f ,0x80 ,0x96 ,0x73 ,0xbe ,0x56 ,0x9b ,0x9e ,0x95 ,0xd9 ,0xf7 ,0x02 ,0xb9 ,0xa4 },
					{0xde ,0x6a ,0x32 ,0x6d ,0xd8 ,0x8a ,0x84 ,0x72 ,0x2a ,0x14 ,0x9f ,0x88 ,0xf9 ,0xdc ,0x89 ,0x9a },
					{0xfb ,0x7c ,0x2e ,0xc3 ,0x8f ,0xb8 ,0x65 ,0x48 ,0x26 ,0xc8 ,0x12 ,0x4a ,0xce ,0xe7 ,0xd2 ,0x62 },
					{0x0c ,0xe0 ,0x1f ,0xef ,0x11 ,0x75 ,0x78 ,0x71 ,0xa5 ,0x8e ,0x76 ,0x3d ,0xbd ,0xbc ,0x86 ,0x57 },
					{0x0b ,0x28 ,0x2f ,0xa3 ,0xda ,0xd4 ,0xe4 ,0x0f ,0xa9 ,0x27 ,0x53 ,0x04 ,0x1b ,0xfc ,0xac ,0xe6 },
					{0x7a ,0x07 ,0xae ,0x63 ,0xc5 ,0xdb ,0xe2 ,0xea ,0x94 ,0x8b ,0xc4 ,0xd5 ,0x9d ,0xf8 ,0x90 ,0x6b },
					{0xb1 ,0x0d ,0xd6 ,0xeb ,0xc6 ,0x0e ,0xcf ,0xad ,0x08 ,0x4e ,0xd7 ,0xe3 ,0x5d ,0x50 ,0x1e ,0xb3 },
					{0x5b ,0x23 ,0x38 ,0x34 ,0x68 ,0x46 ,0x03 ,0x8c ,0xdd ,0x9c ,0x7d ,0xa0 ,0xcd ,0x1a ,0x41 ,0x1c }	};

unsigned int const RCON[10] = {0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000,0x1b000000,0x36000000};

/*unsigned char divi(unsigned int a,unsigned int b);
unsigned char mod(unsigned int a,unsigned int b);*/

uint128  shiftRows(uint128 a);
uint128  mixColumn(uint128 a);
unsigned int bits(unsigned int a);
unsigned char mult(unsigned int a,unsigned int b);
unsigned char F(unsigned int a);
uint128 *keyExpansion(uint128 k);
unsigned char *AES(const unsigned char *str,const unsigned char *key);


unsigned int bits(unsigned int a)
{
	unsigned int count=0;
	while(a!=0)
	{
		a>>=1;
		count++;
	}
	return count;
}
unsigned char mult(unsigned int a,unsigned int b)
{
	int i,j;
	unsigned int x = 0;
	unsigned int p,q;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			p = (a>>i)&1;
			q = (b>>j)&1;
			if(p&q)
				x^=(1<<(i+j));
		}
	return F(x);
}
unsigned char F(unsigned int a)
{
	if(bits(a)<9)
		return a;
	unsigned int p,k;
	unsigned int x,y,q=0;
	x=a;
	while(bits(x)>=9)
	{
		p=bits(x);
		k=p-9;
		y=I<<k;
		x^=y;
	}
	
	return (unsigned char)x;
}
uint128 shiftRows(uint128 a)
{	
	uint128 t = 0,k;
	int i,j;
	unsigned int word;
	for(int i=0;i<4;i++)
	{
		word = Word(a,i);
		for(int j=0;j<4;j++)	
		{
			k = Byte(word,j);
			t|=putAt(k,(4+j+i)&3,j);
		}
	}
	return t;
	
}
unsigned int multVector(unsigned int a,unsigned int b)
{
	unsigned int t,k=0;
	
	for(int i=0;i<4;i++)
	{
		t= mult(Byte(a,i),Byte(b,i));
		k^=t;
	}
	return k;
}
uint128 mixColumn(uint128 a)
{
	unsigned int ti[4]={0x02030101,0x01020301,0x01010203,0x03010102},word;
	uint128 u=0,k,t;
	for(int i=0;i<4;i++)
	{
		word = Word(a,i);
		for(int j=0;j<4;j++)	
		{	
			t=multVector(ti[j],word);
			u |= putAt(t,i,j);
		}
	}
	return u;	
}
uint128 *keyExpansion(uint128 k)
{
	uint128 *key = (uint128*)malloc(11*sizeof(uint128)),t;
	unsigned int temp,*w = (unsigned int*)malloc(44*sizeof(unsigned int));
	int i;
	
	for(i=0;i<4;i++)
		w[i] = Word(k,i);
	for(i=4;i<44;i++)
	{
		temp = w[i-1];
		if((i&3)==0)
			temp = (subWord(rotWord(temp)))^RCON[(i>>2)-1];
		w[i] = w[i-4]^temp;
	}
	for(i=0;i<11;i++)
	{	
		key[i] = 0;
		t = w[i<<2];
		key[i] |= t<<96;
		t = w[(i<<2)+1];
		key[i] |= t<<64;
		t = w[(i<<2)+2];
		key[i] |= t<<32;
		t = w[(i<<2)+3];
		key[i] |= t;
	}
	return key;
}
unsigned char *AES(const unsigned char *str,const unsigned char *k)
{	
	uint128 key = 0,t,*K,x = 0,y;
	unsigned int word;
	unsigned char *res = (unsigned char*)malloc(17);
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)	
		{
			t = k[(i<<2)+j];
			key|=putAt(t,i,j);
			t = str[(i<<2)+j];
			x  |=putAt(t,i,j);
		}
	
	K = keyExpansion(key);
	x ^= K[0];
	for(int r=1;r<10;r++)
	{
		y=x;
		x=0;
		for(int i=0;i<4;i++)
		{
			word = Word(y,i);
			for(int j=0;j<4;j++)
			{
				t = subByte(Byte(word,j));
				x |= putAt(t,i,j);
			}
			
		}
		x = shiftRows(x);
		x = mixColumn(x);
		x ^= K[r];
	}
	y=x;
	x=0;
	for(int i=0;i<4;i++)
	{
		word = Word(y,i);
		for(int j=0;j<4;j++)
		{
			t = subByte(Byte(word,j));
			x |= putAt(t,i,j);
		}
		
	}
	x = shiftRows(x);
	x ^= K[10];
	for(int i=0;i<4;i++)
	{
		word = Word(x,i);
		for(int j=0;j<4;j++)
		{	
			res[(i<<2)+j] = (unsigned char)Byte(word,j);
		}
	}
	res[16] = '\0';
	return res;
}
/*unsigned char divi(unsigned int a,unsigned int b)
{
	if(bits(a)<bits(b))	
		return 0;
	unsigned int p,t=bits(b),k;
	unsigned int x,y,q=0;
	x=a;
	while(bits(x)>=t)
	{
		p=bits(x);
		k=p-t;
		y=b<<k;
		x^=y;
		q|=(1<<k);
	}
	return F(q);
}
unsigned char mod(unsigned int a,unsigned int b)
{
	if(bits(a)<bits(b))
		return a;
	unsigned int p,t=bits(b),k;
	unsigned int x,y,q=0;
	x=a;
	while(bits(x)>=t)
	{
		p=bits(x);
		k=p-t;
		y=b<<k;
		x^=y;
	}
	return F(x);
}
unsigned char subByte(unsigned char a)
{
	unsigned char z = a, c = 0b01100011,b;
	if(z != 0)
		z = inv(z);
	a = z;
	b = 0;
	for(int i = 0; i<8 ;i++)
	{	
		b|=(((a>>i)^(a>>((i+4)&7))^(a>>((i+5)&7))^(a>>((i+6)&7))^(a>>((i+7)&7))^(c>>i))&1)<<i;
	}
	return b;	
}
*/
#endif






















