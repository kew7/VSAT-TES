// Occ.cpp: implementation of the Occ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSAT_TES.h"
#include "Occ.h"

#include "T90_plus.h"
#include "Deperem.h"
#include "Decode.h"
#include "Dif_dec.h"
#include "Des2_v35.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Occ::Occ()
{


}

Occ::~Occ()
{

}




BOOL Occ::synchro_search(BYTE * buf_in, int lenb)          //функция синхронизации декодера
{

unsigned int l,i;

    init();
      
		// Генерируем последовательности для определения фазы декодера
		// Используется операция сдвига sdvig(BYTE*,int,unsigned i)
	    
  turn_faza=T_0;
  prev_shift=0;
  for (i=0; i<16; i++)                      // Исходный + 16 сдвигов
	{
	memcpy(massiv[i],buf_in, LENG_SHAB);
	l=sdvig(massiv[i], LENG_SHAB, i);
	     if(decoder(massiv[i],LENG_SHAB))
		 { 
		  sdwig=i;  
          return TRUE;
		 } 
 
	}
    
    turn_faza=T_90;                         // поворот на 90 + 16 сдвигов
	turn_faza_90(buf_in, buf_out, LENG_SHAB, turn_faza); 
 	for (i=0; i<16; i++) 
	{
	    memcpy(massiv[i+16],buf_out, LENG_SHAB);	
	    l=sdvig(massiv[i+16],LENG_SHAB,i);
		if(decoder(massiv[i+16],LENG_SHAB))
		{
		sdwig=i;
     	return TRUE;
		}
	}

    
	memcpy(buf_temp,buf_in, LENG_SHAB);
	sdvig(buf_temp, LENG_SHAB, 1)                      ;	// сдвиг на 1 бит, поворот на 90
	turn_faza_90(buf_temp,buf_out, LENG_SHAB, turn_faza);   // + 16 сдвигов
	prev_shift=1;
	for (i=0; i<16; i++)
	{                            			     	      
        memcpy(massiv[i+32],buf_out, LENG_SHAB);
		l=sdvig(massiv[i+32], LENG_SHAB, i);
		if(decoder(massiv[i+32],LENG_SHAB))
		{
			sdwig=i;  
		    return TRUE;
		}
	}

/*	turn_faza=T_180;                         // поворот на 180 + 16 сдвигов
	turn_faza_90(buf_in, buf_out, LENG_SHAB, turn_faza);
	prev_shift=0;
 	for (i=0; i<16; i++) {
		memcpy(massiv[i+48],buf_out, LENG_SHAB);	
	    l=sdvig(massiv[i+48],LENG_SHAB,i);
		if(decoder(massiv[i+48],LENG_SHAB))
		{
			sdwig=i;  
            return TRUE;
		}
	}

    
    memcpy(buf_temp,buf_in, LENG_SHAB);
	sdvig(buf_temp, LENG_SHAB, 1);                  // сдвиг на 1 бит, поворот на 180
	turn_faza_90(buf_temp, buf_out, LENG_SHAB, turn_faza); // + 16 сдвигов
	prev_shift=1;
	for (i=0; i<16; i++) 
	{		
		memcpy(massiv[i+64],buf_out, LENG_SHAB);	
	    l=sdvig(massiv[i+64],LENG_SHAB,i);
		if(decoder(massiv[i+64],LENG_SHAB)) 
		{
			sdwig=i; 
		    return TRUE;
		}
	}
    
	
	turn_faza=T_270;                         // поворот на 270 + 16 сдвигов
	turn_faza_90(buf_in, buf_out, LENG_SHAB, turn_faza);
	prev_shift=0;
 	for (i=0; i<16; i++) 
	{
		memcpy(massiv[i+80],buf_out, LENG_SHAB);	
	    l=sdvig(massiv[i+80],LENG_SHAB,i);
		if(decoder(massiv[i+80],LENG_SHAB)) 
		{
			sdwig=i;  
			return TRUE;
		}
	}

   	memcpy(buf_temp,buf_in, LENG_SHAB );
	sdvig(buf_temp, LENG_SHAB, 1);                  // сдвиг на 1 бит, поворот на 270
    turn_faza_90(buf_temp, buf_out, LENG_SHAB, turn_faza); // + 16 сдвигов
	prev_shift=1;
	for (i=0; i<16; i++)
	{			 	    
	    memcpy(massiv[i+96],buf_out, LENG_SHAB);	
	    l=sdvig(massiv[i+96],LENG_SHAB,i);
		if(decoder(massiv[i+96],LENG_SHAB)) 
		{
			sdwig=i; 
		    return TRUE;
		}
 	
 }*/
return FALSE;
}


int Occ::decoder(BYTE*buf_inp,int len)
{
        init();
		deperem(buf_inp, buf_deper,len);

		if ( !decode(buf_deper, buf_dec, len, 1) ) {
			reg_decode=1;
		    return 1;
		}
		else 
		if ( !decode(buf_deper, buf_dec, len, 0) ) {
			reg_decode=0;
		    return 1;
			}

return 0;

}


                 //функция обработки входного потока

BOOL Occ::Obrabotka(BYTE *buf_inp,int lenb)
{
	                                   // создаем текущий буфер, чтобы объединить
//	static BYTE buf_save[2]={0,0};     // текущий и предыдущий блоки без потерь
//	static BYTE simv_desdvig=0;
    int i,s;
    s=sdwig;    	
	if(prev_shift==1) {
     desdvig(buf_inp,lenb,simv_desdvig); //сдвигаем поток вправо на 1 бит
	 s+=2;			         // +2 сдвига
		if (s==16)
			s=0;
		else
			if (s==17)
				s=1;
	}
            turn_faza_90(buf_inp, buf_out, lenb, turn_faza);
           
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

          	deperem(buf_out, buf_deper, lenb);
			if(decode(buf_deper,buf_dec,lenb,reg_decode)) 
			{
			//MessageBox(NULL,"NO!!!","",NULL);
				simv_desdvig=0;
				buf_save[0]=0; buf_save[1]=0;
				return FALSE;
			}
			
            dif_decoder(buf_dec,buf_dif,lenb>>1); 
            descrembler_V35(buf_dif,buf_dskr,lenb>>1);
//            fout.Write(buf_dskr,lenb>>1);
            Process.FirstFlag(buf_dskr,lenb>>1);

return TRUE;

}


int Occ::sdvig(BYTE *buf, int len , int s)  // операция сдвига потока 
{                                           // в конце блока на месте <s> сдвинутых бит нули
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


void Occ::desdvig(BYTE *buf, int len,BYTE simv)
{
int	i;
unsigned char simv_p;
    simv_desdvig=(((buf[len-1])>>7)&1);
	for (i=0; i<len; i++) {
		simv_p=(buf[i]>>7)&1;
		buf[i]=((buf[i]<<1)&0xFE)|(simv&1);
		simv=simv_p;
     
}
}
