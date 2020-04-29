
static BYTE registr=0x00 ;

void dif_decoder(unsigned char *buf_inp, unsigned char *buf_out, unsigned int len)
{
static BYTE	mask_bit[8]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned int	i,j;
unsigned char	registr1;
	memset(buf_out, 0x00, len);
	for (i=0; i<len; i++)
		for (j=0; j<8; j++) {
			(buf_inp[i]&mask_bit[j])?(registr1=1):(registr1=0);
			(!(registr^registr1))?(buf_out[i]|=mask_bit[j]):(0);
			registr=registr1;
		}
}