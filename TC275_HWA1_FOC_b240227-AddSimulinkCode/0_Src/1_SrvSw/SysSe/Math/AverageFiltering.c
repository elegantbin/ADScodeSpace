/*
 * AverageFiltering.c
 *
 *  Created on: 2023Äê12ÔÂ20ÈÕ
 *      Author: Brook.Wu
 */
#include "AverageFiltering.h"

float32 averageFilter1(float32 input_data,uint8 data_num)
{
    static float32 data[512] = {0};
    float32 sum = 0;
    float32 ave = 0;
    for(uint8 i=0; i<data_num-1; i++)
    {
        data[i]=data[i+1];
        sum = sum + data[i];
    }
    data[data_num-1] = input_data;
    sum = sum + data[data_num-1];
    ave = sum/data_num;

    return ave;
}

float32 averageFilter2(float32 input_data,uint8 data_num)
{
    static float32 data[512] = {0};
    float32 sum = 0;
    float32 ave = 0;
    for(uint8 i=0; i<data_num-1; i++)
    {
        data[i]=data[i+1];
        sum = sum + data[i];
    }
    data[data_num-1] = input_data;
    sum = sum + data[data_num-1];
    ave = sum/data_num;

    return ave;
}
