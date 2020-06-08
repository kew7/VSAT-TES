// Abonent.cpp: implementation of the CAbonent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSAT_TES.h"
#include "Abonent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



#include "T90_plus34.h"
#include "Deperem34.h"
#include "Decode34.h"
#include "Dif_dec34.h"
#include "Des2_v35_34.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbonent::CAbonent()
{

}

CAbonent::~CAbonent()
{

}

void CAbonent::init(BYTE Num)
{
	if(Num==0){
			   simv_desdvig1=0;
		       memset(rez1, 0, 12);
			   next1=0;
			  
	}
			   
	if(Num==1){
			   simv_desdvig2=0;
		       memset(rez2, 0, 12);
			   next2=0;
			  
	}
}


BOOL CAbonent::Demultiplex(BYTE *buf, int len)  // функция разделения потока на 2 подпотока
{

	int  k=0,
		 i=0;

	   if(Num_kan==3)
	   {
                              
		 while(i<(len>>3))
		 {
       
		   if((buf[2+8*i]>1)&&(buf[6+8*i]>1))  // проверяем наличие данных в обоих каналах
		   {
			   if(buf[8*i]!=buf[4+8*i])  Num_kan=2; // есть сигнал в обоих каналах    
			   if(buf[8*i]==buf[4+8*i]) 
			   {
				   if(buf[8*i]==0) Num_kan=0;       // есть сигнал по 0-му каналу
				   if(buf[8*i]==1) Num_kan=1;       // есть сигнал по 1-му каналу
			   }
			   break;                          // выходим если есть данные
 		   }
		   i++;
		 }
	   };

	   if(Num_kan==0)
	   {
		while(i<(len>>3))
		{

			{
				buf_in1[k++]=buf[2+8*i];    buf_in1[k++]=buf[3+8*i];  //  0-й канал
				buf_in1[k++]=buf[6+8*i];  buf_in1[k++]=buf[7+8*i];   
           
			}
			if(buf[8*i]>1)
			{
				MessageBox(NULL,"Проверьте сигнал на входе Mirage0","",0);
				exit(0);
			}
			i++;
		}
		SizeBuf_kan=k;
		return TRUE;
	   }	
    
	   if(Num_kan==1)
	   {
		while(i<(len>>3))
		{

			{
				buf_in2[k]=buf[2+8*i];    buf_in2[++k]=buf[3+8*i];  //  1-й канал
				buf_in2[++k]=buf[6+8*i];  buf_in2[++k]=buf[7+8*i];   
				k++;
			}
			if(buf[8*i]>1)
			{
				MessageBox(NULL,"Проверьте сигнал на входе Mirage0","",0);
				exit(0);
			}
			i++;
		}
		SizeBuf_kan=k;
		return TRUE;
	   }	

	   if(Num_kan==2)
		{
		while(i<(len>>3))
		{
			if(buf[8*i]==0) 
			{
				buf_in1[k]=buf[2+8*i];   buf_in2[k]=buf[6+8*i];  // порядок каналов в потоке 0k-1k-0k-1k
				k++;
				buf_in1[k]=buf[3+8*i];   buf_in2[k]=buf[7+8*i];   
				k++;
			}
			if(buf[8*i]==1)                                      // порядок каналов в потоке 1k-0k-1k-0k
			{
				buf_in1[k]=buf[6+8*i];   buf_in2[k]=buf[2+8*i];
				k++;
				buf_in1[k]=buf[7+8*i];   buf_in2[k]=buf[3+8*i];
				k++;
			}
			if(buf[8*i]>1)
			{
				MessageBox(NULL,"Проверьте сигнал на входе Mirage0","",0);
				exit(0);
			}
				i++;
		}
		SizeBuf_kan=k;
		return TRUE;
   }	

return FALSE;
}
 
             // Функция синхронизации для НСК 3/4
BOOL CAbonent::synchro_search(BYTE * buf_in, int lenb,BYTE Num)          //поиск синхронизации
{

	unsigned int l, i;
    
	// Генерируем последовательности для определения фазы декодера
	// Используется операция сдвига sdvig(BYTE*,int,unsigned i)
	init(Num);
	    
	  turn_faza=T_0;
	  prev_shift=0;
	  for (i=0; i<16; i++)                      // Исходный + 16 сдвигов
	  {
		memcpy(massiv[i],buf_in,lenb);
		l=sdvig(massiv[i], lenb, i);
		deperem34(massiv[i],buf_deper,lenb);
		for(int j=0;j<4;j++)
		{
		sdvig(buf_deper,lenb,j); 
		if(Num==0) Variant1=VAR_A; else Variant2=VAR_A;
		if(ch_sind(buf_deper,lenb,Num))
			 { 
			  if(Num==0) turn_faza1=T_0; else turn_faza2=T_0;
			  if(Num==0) prev_shift1=0;  else prev_shift2=0;
			  if(Num==0) reg_shift1=j; else reg_shift2=j;
			  if(Num==0) sdwig1=i;     else sdwig2=i;
			  return TRUE;
			 } 
		if(Num==0) Variant1=VAR_B; else Variant2=VAR_B;
		if(ch_sind(buf_deper,lenb,Num))
			 { 
			  if(Num==0) turn_faza1=T_0; else turn_faza2=T_0;
			  if(Num==0) prev_shift1=0;  else prev_shift2=0;
			  if(Num==0) reg_shift1=j; else reg_shift2=j;
			  if(Num==0) sdwig1=i;     else sdwig2=i;
			  return TRUE;
			 } 
		}
	  }
  
		turn_faza=T_90;               
		turn_faza_90_34(buf_in, buf_out, lenb, turn_faza); 
 		for (i=0; i<16; i++)                           // поворот на 90 + 16 сдвигов
		{
		 memcpy(massiv[i+16],buf_out,lenb);	
		 l=sdvig(massiv[i+16],lenb,i);
		 deperem34(massiv[i+16],buf_deper,lenb);
		 for(int j=0;j<4;j++)
		 {
			sdvig(buf_deper,lenb,j); 
			if(Num==0) Variant1=VAR_A; else Variant2=VAR_A;
			if(ch_sind(buf_deper,lenb,Num))
			{
			 if(Num==0) turn_faza1=T_90; else turn_faza2=T_90;
			 if(Num==0) prev_shift1=0;  else prev_shift2=0;
			 if(Num==0) reg_shift1=j; else reg_shift2=j;
			 if(Num==0) sdwig1=i;     else sdwig2=i;
     		 return TRUE;
			}
			if(Num==0) Variant1=VAR_B; else Variant2=VAR_B;
			if(ch_sind(buf_deper,lenb,Num))
			{
			 if(Num==0) turn_faza1=T_90; else turn_faza2=T_90;
			 if(Num==0) prev_shift1=0;  else prev_shift2=0;	
			 if(Num==0) reg_shift1=j; else reg_shift2=j;
			 if(Num==0) sdwig1=i;     else sdwig2=i;
			 return TRUE;
			} 
		 }
		}
    
		memcpy(buf_temp,buf_in, lenb);
		sdvig(buf_temp, lenb, 1)                      ;	// сдвиг на 1 бит, поворот на 90
		turn_faza_90_34(buf_temp,buf_out,lenb, turn_faza);   // + 16 сдвигов
		prev_shift=1;
		for (i=0; i<16; i++)
		{                            			     	      
			memcpy(massiv[i+32],buf_out, lenb);
			l=sdvig(massiv[i+32],lenb, i);
			deperem34(massiv[i+32],buf_deper,lenb);
			for(int j=0;j<4;j++)
			{
			sdvig(buf_deper,lenb,j); 
			if(Num==0) Variant1=VAR_A; else Variant2=VAR_A;
			if(ch_sind(buf_deper,lenb,Num))
			{
			 if(Num==0) turn_faza1=T_90; else turn_faza2=T_90;
			 if(Num==0) prev_shift1=1;  else prev_shift2=1;
			 if(Num==0) reg_shift1=j; else reg_shift2=j;
			 if(Num==0) sdwig1=i;     else sdwig2=i;
			 return TRUE;
			}
			if(Num==0) Variant1=VAR_B; else Variant2=VAR_B;
			if(ch_sind(buf_deper,lenb,Num))
			 { 
			  if(Num==0) turn_faza1=T_90; else turn_faza2=T_90;
			  if(Num==0) prev_shift1=1;  else prev_shift2=1;
			  if(Num==0) reg_shift1=j; else reg_shift2=j;
			  if(Num==0) sdwig1=i;     else sdwig2=i;
			  return TRUE;
			 } 
			}
		}
return FALSE;
}
                     
BYTE CAbonent::ch_sind(BYTE*buf_inp, unsigned int len,BYTE Num)
{
unsigned int	i,j,k,l;
double nu=0,ed=0;

BYTE reg=0,*Buf_temp,variant;

	static unsigned int mask_a[18]={0x01, 0x02, 0x10, 0x40, 0x80, 0x200, 0x400,
				    0x1000, 0x2000, 0x10000, 0x40000, 0x100000,
				    0x200000, 0x800000, 0x1000000, 0x2000000,
				    0x4000000, 0x8000000},
						mask_b[18]={0x01, 0x02, 0x20, 0x40, 0x80, 0x100, 0x800,
				    0x1000, 0x2000, 0x20000, 0x80000, 0x100000,
				    0x200000, 0x400000, 0x1000000, 0x2000000,
				    0x4000000, 0x8000000};
	unsigned int registr=0x00000000;

	Buf_temp=new BYTE[len<<1];

        if(Num==0) variant=Variant1; else variant=Variant2; //разделение подканалов

        if(variant==VAR_A)     //Вариант "а"
		for (i=0, l=0; i<len; i++)
			for (j=0; j<5; j+=4, l++) {
				registr=(registr<<4)|((buf_inp[i]>>j)&0xF);
				for (k=0; k<18; k++)
					if (registr&mask_a[k])
						reg^=1;
				Buf_temp[l]=reg;
				reg=0;
			}
   
    	if(variant==VAR_B)  //Вариант "б"
		for (i=0, l=0; i<len; i++)
			for (j=0; j<5; j+=4, l++) {
				registr=(registr<<4)|((buf_inp[i]>>j)&0xF);
				for (k=0; k<18; k++)
					if (registr&mask_b[k])
						reg^=1;
				Buf_temp[l]=reg;
				reg=0;
			}

		j=0;
		for (i=0 ; i<l; ++i)
		{
			if (!Buf_temp[i])
				++j;
		//	else j=0;
		//	if(j==30) break;
		}
		nu=j;
		ed=l-j;
	  
		if(len==30)
		{
				if ((!nu)||(ed/nu>0.1));
				else
				{
					delete [] Buf_temp;
					return 1;	
				}
		}
		else
		{
				if ((!nu)||(ed/nu>0.01));
				else
				{
					 delete [] Buf_temp;
					 return 1;	
				}
	  
		}

	delete [] Buf_temp;
	return 0; //фаза неверна
}

                 //функция обработки входного потока(синхронизация и декодирование)

BOOL CAbonent::Obrabotka(BYTE *buf_inp,int lenb,BYTE Num)
{

    int i,s,m;

	if(Num==0) sdwig=sdwig1; else sdwig=sdwig2;
	if(Num==0) simv_desdvig=simv_desdvig1; else simv_desdvig=simv_desdvig2;
    if(Num==0) reg_shift=reg_shift1;    else reg_shift=reg_shift2;
    if(Num==0) turn_faza=turn_faza1;    else turn_faza=turn_faza2;
    if(Num==0) prev_shift=prev_shift1;  else prev_shift=prev_shift2;
    if(Num==0){
		         Variant=Variant1;
	             buf_save[0]=buf_save1[0];
                 buf_save[1]=buf_save1[1];
	} else {
		         Variant=Variant2;
                 buf_save[0]=buf_save2[0];
                 buf_save[1]=buf_save2[1];
	}
    
	if((sdwig+=reg_shift)>=16) sdwig=sdwig-16; //учитываем сдвиг для нимбов
    s=sdwig;    	
	if(prev_shift==1) {
     desdvig(buf_inp,lenb,simv_desdvig,Num); //сдвигаем поток вправо на 1 бит
	 s+=2;			                        // в результате общий сдвиг увеличился на 2 бита
		if (s==16)
			s=0;
		else
			if (s==17)
 				s=1;
	}
            turn_faza_90_34(buf_inp, buf_out, lenb, turn_faza);
           
			if(s==0); else
			if(s<8)
			{
             buf_inp[0]=buf_save[0];
    		 buf_inp[1]=(buf_save[1])|(buf_out[0]<<(8-s));
			 for (i=0; i<lenb-2; i++)
			 buf_inp[i+2]=(buf_out[i]>>s)|(buf_out[i+1]<<(8-s));
			 //buf_save[0]=buf_out[lenb-1]>>s;
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
			if(Num==0) memcpy(buf_save1,buf_save,2);
			if(Num==1) memcpy(buf_save2,buf_save,2);

            deperem34(buf_out, buf_deper, lenb);  // cнимаем перемежение

			if(!ch_sind(buf_deper,lenb,Num))   // проверяем наличие синхронизации 
			{ 
				if(FlagG728==TRUE)
			     if(SynchroG728[Num]==TRUE)
				{
                  if(m_MaxSynIndex[Num]<8)
				  {
                    if(Num==0) fout1.Write(buf_saveG728[Num],1); // записываем в файл
			        if(Num==1) fout2.Write(buf_saveG728[Num],1);
				  }
				  else
                  if(m_MaxSynIndex[Num]==8);
				  else
				  if(m_MaxSynIndex[Num]>8)
				  {
                   	if(Num==0) fout1.Write(buf_saveG728[Num],2); // записываем в файл
			        if(Num==1) fout2.Write(buf_saveG728[Num],2);                    
				  }

				}
				if(Num==0 ) {buf_save1[0]=0; buf_save1[1]=0;}
				else {buf_save2[0]=0; buf_save2[1]=0;}
				return FALSE; 
			}
    	    m=decode34(buf_deper,buf_dec,lenb,Variant,Num); // декодируем
			dif_decoder34(buf_dec,buf_dif,m,Num); // диф.декодируем
            descrembler_V35_34(buf_dif,buf_dskr,m,Num); // дескремблируем
			 
			if(FlagG728==TRUE) //если в абон.каналах скорость для G.728
			{
			 if(SynchroG728[Num]!=TRUE)
			 {
              SinchroSearhG728(Num);
			  SdvigG728(Num,m);
			  SynchroG728[Num]=TRUE;
			  return TRUE;
			 }
			 else 
			 {
			  SdvigG728(Num,m);
			  return TRUE;
			 }
			}

            else

            if(FlagG726==TRUE) //если в абон.каналах скорость для G.726
			{
			 if(SynchroG726[Num]!=TRUE) 
			 {
	            SdvigG726(Num,m);
				SynchroG726[Num]=TRUE;
				return TRUE;
			 }
             else 
			 {
                SdvigG726(Num,m);
				return TRUE;
			 }
			
			}
            
       		if(Num==0) fout1.Write(buf_dskr,m); // записываем в файл
   			if(Num==1) fout2.Write(buf_dskr,m);
			

return TRUE;
}


int CAbonent::sdvig(BYTE *buf, int len , int s)  // операция сдвига потока 
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


VOID CAbonent::desdvig(BYTE *buf, int len,BYTE simv,BYTE Num)
{
	int	i;
	unsigned char simv_p;
	if (Num == 0) simv_desdvig1 = (((buf[len - 1]) >> 7) & 1);
	if (Num == 1) simv_desdvig2 = (((buf[len - 1]) >> 7) & 1);
	for (i = 0; i < len; i++) {
		simv_p = (buf[i] >> 7) & 1;
		buf[i] = ((buf[i] << 1) & 0xFE) | (simv & 1);
		simv = simv_p;

	}
}


 // Функция синхронизации для G728. Битовый анализ показывает что синхронизироваться
 // необходимо по следующему критерию:
 // второй бит в 10-битных кодовых словах принимает "0", а десятый бит - "1"  
 // намного чаще, чем остальные биты 

void CAbonent::SinchroSearhG728(int N)
{
	BYTE * massiv,
		   m_Byte[2];
	ULONG m_Number[10],m_MaxSyn;
	unsigned short int sss,m_Word;

	 // Попрубуем засинхронизироватья на выборке в 500 байт (400 10-битных кодовых слов )
	 if((massiv=new BYTE[500])==NULL) exit(0);
 
	 for(int i=0;i<10;i++)
	 {
	   m_Number[i]=0;
	   memcpy(massiv,buf_dskr,500);
	   sdvig(massiv,500,i);
	   sss=0;
	  for(int k=0;k<499;k++)
	  {
		  m_Byte[0]=massiv[k]>>sss;
		  m_Byte[1]=massiv[k+1]; 
		  m_Word=m_Byte[1];
		  m_Word=m_Word<<(8-sss);
		  m_Word=m_Word|m_Byte[0];
	 
		  if((m_Word&0x0202)==0x0200) m_Number[i]++;
		  sss+=2;
		  if(sss==8)
		  {
			  sss=0;
			  ++k;
		  }
	  }
  
	 }

	 delete [] massiv;

	 m_MaxSyn=m_Number[0];
	 m_MaxSynIndex[N]=0;
	 for(int i=1;i<10;i++)
	 {
	   if(m_Number[i]>m_MaxSyn)
	   {
		   m_MaxSyn=m_Number[i];
		   m_MaxSynIndex[N]=i;       // сдвиг для 728Vocoder
	   }
	 }
 return;
}

  // Пока не знаю, но почему-то при любом сдвиге sdwig выходной файл необходимо
  // сдвинуть на 1 бит, тогда транскодирование для G726 пройдет нормально
  // Поэтому сдвигаем весь обработанный битовый поток на 1 бит
void CAbonent::SdvigG726(int Num,UINT lenb)
{
	BYTE *BufTemp;

    if((BufTemp=new BYTE[lenb])==NULL) exit(0);

			if(SynchroG726[Num]==TRUE)
			   {
                  buf_saveG726[Num]=buf_saveG726[Num]|(buf_dskr[0]<<7);                   
				  if(Num==0) fout1.Write(&buf_saveG726[0],1); // записываем в файл
				  if(Num==1) fout2.Write(&buf_saveG726[1],1);
			   }

			  for (UINT i=0; i<lenb-1; i++)
			  BufTemp[i]=(buf_dskr[i]>>1)|(buf_dskr[i+1]<<7);

              buf_saveG726[Num]=buf_dskr[lenb-1]>>1;

              memcpy(buf_dskr,BufTemp,lenb-1);

			  if(Num==0) fout1.Write(buf_dskr,lenb-1); // записываем в файл
			  if(Num==1) fout2.Write(buf_dskr,lenb-1);

	delete [] BufTemp;
	return;
}


void CAbonent::SdvigG728(int Num,UINT lenb)
{
  
  BYTE *BufTemp;
  int s = m_MaxSynIndex[Num];

  if((BufTemp=new BYTE[lenb])==NULL) exit(0);

			if(s<8)
			{
               if(SynchroG728[Num]==TRUE)
			   {
                  buf_saveG728[Num][0]=buf_saveG728[Num][0]|(buf_dskr[0]<<(8-s));                   
				  if(Num==0) fout1.Write(buf_saveG728[Num],1); // записываем в файл
			      if(Num==1) fout2.Write(buf_saveG728[Num],1);
			   }

			  for (UINT i=0; i<lenb-1; i++)
			  BufTemp[i]=(buf_dskr[i]>>s)|(buf_dskr[i+1]<<(8-s));

              buf_saveG728[Num][0]=buf_dskr[lenb-1]>>s;
              memcpy(buf_dskr,BufTemp,lenb-1);

			  if(Num==0) fout1.Write(buf_dskr,lenb-1); // записываем в файл
			  if(Num==1) fout2.Write(buf_dskr,lenb-1);
			}
		
            if(s==8) 
			{
			  if(SynchroG728[Num]==TRUE)
			   {
				  buf_saveG728[Num][0]=buf_dskr[0];
                  if(Num==0) fout1.Write(buf_saveG728[Num],1); // записываем в файл
			      if(Num==1) fout2.Write(buf_saveG728[Num],1);
			   }
       		  memcpy(BufTemp, &buf_dskr[1], lenb-1);
			  if(Num==0) fout1.Write(BufTemp,lenb-1); // записываем в файл
			  if(Num==1) fout2.Write(BufTemp,lenb-1);
			}

            if(s>8)
			{
             if(SynchroG728[Num]==TRUE)
			   {
                  buf_saveG728[Num][0]=buf_saveG728[Num][0]|(buf_dskr[0]<<(16-s));
                  buf_saveG728[Num][1]=(buf_dskr[0]<<(s-8))|(buf_dskr[1]<<(16-s));
				  if(Num==0) fout1.Write(buf_saveG728[Num],2); // записываем в файл
			      if(Num==1) fout2.Write(buf_saveG728[Num],2);
			   }

             memcpy(BufTemp, &buf_dskr[1], lenb-1);
			 for (UINT i=0; i<lenb-2; i++)
			 buf_dskr[i]=(BufTemp[i]>>(s-8))|(BufTemp[i+1]<<(16-s));

			 buf_saveG728[Num][0]=BufTemp[lenb-2]>>(s-8);   

			 if(Num==0) fout1.Write(buf_dskr,lenb-2); // записываем в файл
			 if(Num==1) fout2.Write(buf_dskr,lenb-2);
             
			}
	delete [] BufTemp;
	return;
}



