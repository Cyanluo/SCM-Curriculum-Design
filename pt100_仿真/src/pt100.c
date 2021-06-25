#include "pt100.h"

bit ng;

float calc_pt100res(uint u_out)
{
	return u_out / K / I;
}

uint median(uint* dat, uchar num_d)  //��Ҫ���������
{ 
	uchar i,j;
	uint temp;

	for(i=0;i<num_d;i++) //����ð�ݷ��Բ����¶Ƚ�������
	{
	    for(j=0;j<i;j++)
		{
		    if(*(dat+i)>*(dat+j))
			{
			    temp=*(dat+i);	  //������ֵ  �Ӵ�С��
				*(dat+i)=*(dat+j);
				*(dat+j)=temp;
			}
		}
	}

	return dat[(num_d-1)/2];
}

float temperature(uint* u_out, uchar num) 
{ 
    float temp1, T_out; 
    uint temp2; 

	temp1 = median(u_out, num);
	temp1 = calc_pt100res(temp1); //����Pt100��ֵ 
	temp2 = (uint)temp1; //ȡPt100��ֵ��λ
	
	if(temp2<100){ng=1;}else{ng=0;}//���¶�  
	if(temp2<96) T_out=777;	   //С��-10�� 
	else if(temp2<100) T_out=255.1239-2.5511*temp1; //����ֵ��С��0�浽��20��֮�� 
	else if(temp2<112) T_out=2.5703*temp1-257.0501; //����ֵ��0��~30��֮�� 
	else if(temp2<123) T_out=2.5935*temp1-259.6416; //����ֵ��30��~60��֮�� 
	else if(temp2<135) T_out=2.6171*temp1-262.5538; //����ֵ��60��~90��֮�� 
	else if(temp2<139) T_out=2.6412*temp1-265.7953; //����ֵ��90��~120��(146.06)֮��   100��(138.5)
	else if(temp2>=139) T_out=2.6412*temp1-265.7953;; //����ֵ�ڴ���100��֮��	 */

    return(T_out); 
}

bit get_sign()
{
	return ng;
}
