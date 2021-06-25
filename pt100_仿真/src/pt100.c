#include "pt100.h"

bit ng;

float calc_pt100res(uint u_out)
{
	return u_out / K / I;
}

uint median(uint* dat, uchar num_d)  //需要排序的数组
{ 
	uchar i,j;
	uint temp;

	for(i=0;i<num_d;i++) //采用冒泡法对采样温度进行排序
	{
	    for(j=0;j<i;j++)
		{
		    if(*(dat+i)>*(dat+j))
			{
			    temp=*(dat+i);	  //交换两值  从大到小排
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
	temp1 = calc_pt100res(temp1); //计算Pt100阻值 
	temp2 = (uint)temp1; //取Pt100阻值高位
	
	if(temp2<100){ng=1;}else{ng=0;}//负温度  
	if(temp2<96) T_out=777;	   //小于-10℃ 
	else if(temp2<100) T_out=255.1239-2.5511*temp1; //若阻值在小于0℃到负20℃之间 
	else if(temp2<112) T_out=2.5703*temp1-257.0501; //若阻值在0℃~30℃之间 
	else if(temp2<123) T_out=2.5935*temp1-259.6416; //若阻值在30℃~60℃之间 
	else if(temp2<135) T_out=2.6171*temp1-262.5538; //若阻值在60℃~90℃之间 
	else if(temp2<139) T_out=2.6412*temp1-265.7953; //若阻值在90℃~120℃(146.06)之间   100℃(138.5)
	else if(temp2>=139) T_out=2.6412*temp1-265.7953;; //若阻值在大于100℃之间	 */

    return(T_out); 
}

bit get_sign()
{
	return ng;
}
