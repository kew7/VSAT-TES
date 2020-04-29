// Abonent2.cpp: implementation of the CAbonent2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSAT_TES.h"
#include "Abonent2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "T90_plus12.h"
#include "Deperem12.h"
#include "Decode12.h"
#include "Dif_dec12.h"
#include "Des2_v3512.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbonent2::CAbonent2()
{

}

CAbonent2::~CAbonent2()
{

}

BOOL CAbonent2::Demultiplex(BYTE *buf, int len)  // ������� ���������� ������ �� 2 ���������
{
int  k=0,
	 i=0;

   if(Num_kan==3)
   {
                              
	 while(i<(len>>3))
	 {
       
       if((buf[2+8*i]>1)&&(buf[6+8*i]>1))  // ��������� ������� ������ � ����� �������
	   {
		   if(buf[8*i]!=buf[4+8*i])  Num_kan=2; // ���� ������ � ����� �������    
		   if(buf[8*i]==buf[4+8*i]) 
		   {
			   if(buf[8*i]==0) Num_kan=0;       // ���� ������ �� 0-�� ������
			   if(buf[8*i]==1) Num_kan=1;       // ���� ������ �� 1-�� ������
		   }
           break;                          // ������� ���� ���� ������
 	   }
	   i++;
	 }
   };

   if(Num_kan==0)
   {
    while(i<(len>>3))
	{

		{
			buf_in1[k++]=buf[2+8*i];    buf_in1[k++]=buf[3+8*i];  //  0-� �����
			buf_in1[k++]=buf[6+8*i];  buf_in1[k++]=buf[7+8*i];   
           
		}
		if(buf[8*i]>1)
		{
			MessageBox(NULL,"��������� ������ �� ����� Mirage0","",0);
			exit(0);
		}
		i++;
	}
	SizeBuf_kan=k;
//    fout3.Write(buf_in1,SizeBuf_kan);
//    fout4.Write(buf_in2,SizeBuf_kan);
	return TRUE;
   }	
    
   if(Num_kan==1)
   {
    while(i<(len>>3))
	{

		{
			buf_in2[k]=buf[2+8*i];    buf_in2[++k]=buf[3+8*i];  //  1-� �����
			buf_in2[++k]=buf[6+8*i];  buf_in2[++k]=buf[7+8*i];   
            k++;
		}
		if(buf[8*i]>1)
		{
            MessageBox(NULL,"��������� ������ �� ����� Mirage0","",0);
			exit(0);
		}
		i++;
	}
	SizeBuf_kan=k;
//	fout3.Write(buf_in1,SizeBuf_kan);
//  fout4.Write(buf_in2,SizeBuf_kan);
	return TRUE;
   }	

   if(Num_kan==2)
	{
    while(i<(len>>3))
	{
		if(buf[8*i]==0) 
		{
			buf_in1[k]=buf[2+8*i];   buf_in2[k]=buf[6+8*i];  // ������� ������� � ������ 0k-1k-0k-1k
			k++;
			buf_in1[k]=buf[3+8*i];   buf_in2[k]=buf[7+8*i];   
			k++;
		}
		if(buf[8*i]==1)                                      // ������� ������� � ������ 1k-0k-1k-0k
		{
			buf_in1[k]=buf[6+8*i];   buf_in2[k]=buf[2+8*i];
			k++;
			buf_in1[k]=buf[7+8*i];   buf_in2[k]=buf[3+8*i];
			k++;
		}
		if(buf[8*i]>1)
		{
	        MessageBox(NULL,"��������� ������ �� ����� Mirage0","",0);
			exit(0);
		}
			i++;
	}
	SizeBuf_kan=k;
//    fout3.Write(buf_in1,SizeBuf_kan);
//    fout4.Write(buf_in2,SizeBuf_kan);
	return TRUE;
   }	

return FALSE;
}
 

BOOL CAbonent2::synchro_search(BYTE * buf_in, int lenb,BYTE Num)      //������� ������������� ��������
{

unsigned int l,i;

    init(Num);
	simv_desdvig1=simv_desdvig2=0;
      
		// ���������� ������������������ ��� ����������� ���� ��������
		// ������������ �������� ������ sdvig(BYTE*,int,unsigned i)
	    
  turn_faza=T_0;
  prev_shift=0;
  for (i=0; i<16; i++)                      // �������� + 16 �������
	{
	memcpy(massiv[i],buf_in, LENG_SHAB);
	l=sdvig(massiv[i], LENG_SHAB, i);
	     if(decoder(massiv[i],LENG_SHAB,Num))
		 { 
		  if(Num==0)
		  {
		   turn_faza1=T_0;
           prev_shift1=0;  
		   sdwig1=i;   
		   reg_decode1=reg_decode; 
		  } 
		  else {
           turn_faza2=T_0;
           prev_shift2=0;
		   sdwig2=i; 
		   reg_decode2=reg_decode; 
		  }
          return TRUE;
		 } 
 
	}
    
    turn_faza=T_90;                         // ������� �� 90 + 16 �������
	turn_faza_90_12(buf_in, buf_out, LENG_SHAB, turn_faza); 
 	for (i=0; i<16; i++) 
	{
	    memcpy(massiv[i+16],buf_out, LENG_SHAB);	
	    l=sdvig(massiv[i+16],LENG_SHAB,i);
		if(decoder(massiv[i+16],LENG_SHAB,Num))
		{
		 if(Num==0)
		  {
		   turn_faza1=T_90;
           prev_shift1=0;  
		   sdwig1=i;   
		   reg_decode1=reg_decode; 

		  } 
		  else {
           turn_faza2=T_90;
           prev_shift2=0;
		   sdwig2=i; 
		   reg_decode2=reg_decode; 
		  }
     	 return TRUE;
		}
	}
    
	memcpy(buf_temp,buf_in, LENG_SHAB);
	sdvig(buf_temp, LENG_SHAB, 1)                      ;	// ����� �� 1 ���, ������� �� 90
	turn_faza_90_12(buf_temp,buf_out, LENG_SHAB, turn_faza);   // + 16 �������
	prev_shift=1;
	for (i=0; i<16; i++)
	{                            			     	      
        memcpy(massiv[i+32],buf_out, LENG_SHAB);
		l=sdvig(massiv[i+32], LENG_SHAB, i);
		if(decoder(massiv[i+32],LENG_SHAB,Num))
		{
		  if(Num==0)
		  {
		   turn_faza1=T_90;
           prev_shift1=1;  
		   sdwig1=i;   
		   reg_decode1=reg_decode; 
		  } 
		  else {
           turn_faza2=T_90;
           prev_shift2=1;
		   sdwig2=i; 
		   reg_decode2=reg_decode; 
		  }
		  return TRUE;
		}
	}

return FALSE;
}

int CAbonent2::decoder(BYTE*buf_inp,int len,BYTE Num)
{
        init(Num);

		deperem12(buf_inp, buf_deper,len);

		if ( !decode12(buf_deper, buf_dec, len, 1) ) {
			reg_decode=1;
		    return 1;
		}
		else 
		if ( !decode12(buf_deper, buf_dec, len, 0) ) {
			reg_decode=0;
		    return 1;
			}

return 0;

}


                 //������� ��������� �������� ������

BOOL CAbonent2::Obrabotka(BYTE *buf_inp,int lenb,BYTE Num)
{
    int i,s;

    if(Num==0) sdwig=sdwig1; else sdwig=sdwig2;
	if(Num==0) simv_desdvig=simv_desdvig1; else simv_desdvig=simv_desdvig2;
    if(Num==0) turn_faza=turn_faza1;    else turn_faza=turn_faza2;
    if(Num==0) prev_shift=prev_shift1;  else prev_shift=prev_shift2;
    if(Num==0){
	             buf_save[0]=buf_save1[0];
                 buf_save[1]=buf_save1[1];
				 reg_decode=reg_decode1;
				 nexte=nexte1;
				 registrP=registrP1;
				 registrQ=registrQ1;
				 registr_descr=registr_descr1;
	} else {
	             buf_save[0]=buf_save2[0];
                 buf_save[1]=buf_save2[1];
				 reg_decode=reg_decode2;
				 nexte=nexte2;
				 registrP=registrP2;
				 registrQ=registrQ2;
				 registr_descr=registr_descr2;
	}

    s=sdwig;    	
	if(prev_shift==1) {
     desdvig(buf_inp,lenb,simv_desdvig,Num); //�������� ����� ������ �� 1 ���
	 s+=2;			         // +2 ������
		if (s==16)
			s=0;
		else
			if (s==17)
				s=1;
	}
            turn_faza_90_12(buf_inp, buf_out, lenb, turn_faza);
           
			if(s==0); else
			if(s<8)
			{
             buf_inp[0]=buf_save[0];
    		 buf_inp[1]=(buf_save[1])|(buf_out[0]<<(8-s));
			 for (i=0; i<lenb-2; i++)
			 buf_inp[i+2]=(buf_out[i]>>s)|(buf_out[i+1]<<(8-s));
			 buf_save[0]=(buf_out[lenb-2]>>s)|(buf_out[lenb-1]<<(8-s));
			 buf_save[1]=buf_out[lenb-1]>>s;
			 memcpy(buf_out, buf_inp, lenb);
			}
            if(s==8) 
			{
             buf_inp[0]=buf_save[0];
    		 memcpy(&(buf_inp[1]), buf_out, lenb-1);
			 buf_save[0]=buf_out[lenb-1];
			 memcpy(buf_out, buf_inp, lenb);
			
			}
            if(s>8)
			{
             buf_inp[0]=(buf_save[0])|(buf_out[0]<<(16-s));
			 for (i=0; i<lenb-1; i++)
			 buf_inp[i+1]=(buf_out[i]>>(s-8))|(buf_out[i+1]<<(16-s));
			 buf_save[0]=buf_out[lenb-1]>>(s-8);
			 memcpy(buf_out, buf_inp, lenb);
			
			}

          	deperem12(buf_out, buf_deper, lenb);
			if(decode12(buf_deper,buf_dec,lenb,reg_decode)) 
			{
				//simv_desdvig=0;
				//buf_save[0]=0; buf_save[1]=0;
				return FALSE;
			}
			   
            dif_decoder_12(buf_dec,buf_dif,lenb>>1,Num); 
            descrembler_V35_12(buf_dif,buf_dskr,lenb>>1);
			  if(Num==0) 
			   {
				 memcpy(buf_save1,buf_save,2);
				 nexte1=nexte;
				 registrP1=registrP;
				 registrQ1=registrQ;
				 registr_descr1=registr_descr; 
			   } 
			   if(Num==1)
			   {
				 memcpy(buf_save2,buf_save,2);
				 nexte2=nexte;
				 registrP2=registrP;
  				 registrQ2=registrQ;
				 registr_descr2=registr_descr; 
			   }
		    
         	if(Num==0) 	fout1.Write(buf_dskr,lenb>>1);
			if(Num==1) 	fout2.Write(buf_dskr,lenb>>1);
			

return TRUE;
}

int CAbonent2::sdvig(BYTE *buf, int len , int s)  // �������� ������ ������ 
{                                           // � ����� ����� �� ����� <s> ��������� ��� ����
	int n;
	if(s<=8)
	   for(n=0; n<len; n++) 
	      if(n<(len-1)) buf[n]=((buf[n]>>s)|(buf[n+1]<<(8-s)));
          else buf[n]>>=s;

	if(s>8)
       for(n=0; n<len; n++) 
	       if(n<(len-2)) buf[n]=((buf[n+1]>>(s-8))|(buf[n+2]<<(16-s))); 
		   else
		   {
		   if(n==(len-2)) buf[n]>>=(s-8); else buf[n]=0;
		   }
	          
return n;	
}


int CAbonent2::desdvig(BYTE *buf, int len,BYTE simv,BYTE Num)
{
int	i;
unsigned char simv_p;
    if(Num==0) simv_desdvig1=(((buf[len-1])>>7)&1);
	if(Num==1) simv_desdvig2=(((buf[len-1])>>7)&1);
	for (i=0; i<len; i++) {
		simv_p=(buf[i]>>7)&1;
		buf[i]=((buf[i]<<1)&0xFE)|(simv&1);
		simv=simv_p;

	}
	return 0;
}
