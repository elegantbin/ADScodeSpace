#include "EncoderGpt12.h"
#include "FuzzyPID.h"

#define FuzzyPID  (0)
#define FuzzyPID0 (0)
#define FuzzyPID1 (1)
#define FuzzyPID2 (2)
#if(FuzzyPID ==FuzzyPID0)
/************************************************************************************
* @author： 镜璍氺月
* @date : 2018/2/15
* @fuction name：FUZZY_PID_CONTROL
* @fuction description： 模糊自适应控制算法，为了方便测试默认e、ec在[-3,3]区间，
* 如需改变e、ec范围，需引入量化因子(Ke、Kec=N/emax)、缩放因子(Ku=umax/N)。以下代码采
*用三角隶属函数求隶属度以及加权平均法解模糊，PID采用位置式PID算法，算法仅供参考，欢迎报错。
*************************************************************************************/
#define IS_Kp 1
#define IS_Ki 2
#define IS_Kd 3

#define NL   -3
#define NM   -2
#define NS   -1
#define ZE    0
#define PS    1
#define PM    2
#define PL    3



static const float fuzzyRuleKp[7][7]=
{
    PL, PL, PM, PM, PS, PS, ZE,
    PL, PL, PM, PM, PS, ZE, ZE,
    PM, PM, PM, PS, ZE, NS, NM,
    PM, PS, PS, ZE, NS, NM, NM,
    PS, PS, ZE, NS, NS, NM, NM,
    ZE, ZE, NS, NM, NM, NM, NL,
    ZE, NS, NS, NM, NM, NL, NL
};

static const float fuzzyRuleKi[7][7]=
{
    NL, NL, NL, NM, NM, ZE, ZE,
    NL, NL, NM, NM, NS, ZE, ZE,
    NM, NM, NS, NS, ZE, PS, PS,
    NM, NS, NS, ZE, PS, PS, PM,
    NS, NS, ZE, PS, PS, PM, PM,
    ZE, ZE, PS, PM, PM, PL, PL,
    ZE, ZE, PS, PM, PL, PL, PL
};

static const float fuzzyRuleKd[7][7]=
{
    PS, PS, ZE, ZE, ZE, PL, PL,
    NS, NS, NS, NS, ZE, NS, PM,
    NL, NL, NM, NS, ZE, PS, PM,
    NL, NM, NM, NS, ZE, PS, PM,
    NL, NM, NS, NS, ZE, PS, PS,
    NM, NS, NS, NS, ZE, PS, PS,
    PS, ZE, ZE, ZE, ZE, PL, PL
};

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
}PID;


PID fuzzy(float e,float ec)
{

     float etemp,ectemp;
     float eLefttemp,ecLefttemp;
     float eRighttemp ,ecRighttemp;

     int eLeftIndex,ecLeftIndex;
     int eRightIndex,ecRightIndex;
     PID      fuzzy_PID;
     etemp = e > 3.0 ? 0.0 : (e < - 3.0 ? 0.0 : (e >= 0.0 ? (e >= 2.0 ? 2.5: (e >= 1.0 ? 1.5 : 0.5)) : (e >= -1.0 ? -0.5 : (e >= -2.0 ? -1.5 : (e >= -3.0 ? -2.5 : 0.0) ))));

     eLeftIndex = (int)e;
     eRightIndex = eLeftIndex;
     eLeftIndex = (int)((etemp-0.5) + 3);        //[-3,3] -> [0,6]
     eRightIndex = (int)((etemp+0.5) + 3);

     eLefttemp =etemp == 0.0 ? 0.0:((etemp+0.5)-e);
     eRighttemp=etemp == 0.0 ? 0.0:( e-(etemp-0.5));

     ectemp = ec > 3.0 ? 0.0 : (ec < - 3.0 ? 0.0 : (ec >= 0.0 ? (ec >= 2.0 ? 2.5: (ec >= 1.0 ? 1.5 : 0.5)) : (ec >= -1.0 ? -0.5 : (ec >= -2.0 ? -1.5 : (ec >= -3.0 ? -2.5 : 0.0) ))));

     ecLeftIndex = (int)((ectemp-0.5) + 3);        //[-3,3] -> [0,6]
     ecRightIndex = (int)((ectemp+0.5) + 3);

     ecLefttemp =ectemp == 0.0 ? 0.0:((ectemp+0.5)-ec);
     ecRighttemp=ectemp == 0.0 ? 0.0:( ec-(ectemp-0.5));

/*************************************反模糊*************************************/




    fuzzy_PID.Kp = (eLefttemp * ecLefttemp *  fuzzyRuleKp[ecLeftIndex][eLeftIndex]
                    + eLefttemp * ecRighttemp * fuzzyRuleKp[ecRightIndex][eLeftIndex]
                    + eRighttemp * ecLefttemp * fuzzyRuleKp[ecLeftIndex][eRightIndex]
                    + eRighttemp * ecRighttemp * fuzzyRuleKp[ecRightIndex][eRightIndex]);

    fuzzy_PID.Ki =   (eLefttemp * ecLefttemp * fuzzyRuleKi[ecLeftIndex][eLeftIndex]
                    + eLefttemp * ecRighttemp * fuzzyRuleKi[ecRightIndex][eLeftIndex]
                    + eRighttemp * ecLefttemp * fuzzyRuleKi[ecLeftIndex][eRightIndex]
                    + eRighttemp * ecRighttemp * fuzzyRuleKi[ecRightIndex][eRightIndex]);

    fuzzy_PID.Kd = (eLefttemp * ecLefttemp *    fuzzyRuleKd[ecLeftIndex][eLeftIndex]
                    + eLefttemp * ecRighttemp * fuzzyRuleKd[ecRightIndex][eLeftIndex]
                    + eRighttemp * ecLefttemp * fuzzyRuleKd[ecLeftIndex][eRightIndex]
                    + eRighttemp * ecRighttemp * fuzzyRuleKd[ecRightIndex][eRightIndex]);
return fuzzy_PID;

}


float speed_pid()
{
        float tar = 0,cur = 0;                //目标值 , 实际值
    static PID pid= {0, 0, 0};      //赋予初值kp，ki，kd
    static int sumE = 0;                   //累加偏差
    static int lastE = 0;

    PID OUT = {0, 0, 0};
    float e = -1,ec = -2.6;



    e = tar - cur;             //目标值 - 实际值
    ec = e - lastE;            //误差变化率
    sumE += e;
    lastE = e;
    OUT = fuzzy(e, ec);      //模糊控制调整  kp，ki，kd

    return (pid.Kp+OUT.Kp)*e + (pid.Kd+OUT.Kd)*ec + (pid.Ki+OUT.Ki)*sumE;
}



#endif
#if(FuzzyPID ==FuzzyPID1)

// Fuzzy PID controller parameters
float Kp = 1.0;
float Ki = 0.5;
float Kd = 0.2;

// Fuzzy sets for error and error change

#define NB   -1
#define NM   -0.5
#define NS   -0.2
#define ZO    0
#define PS    0.2
#define PM    0.5
#define PB    1
#define NVL   -1
#define NL    -0.5
#define NSL   -0.2
#define PSL   0.2
#define PL    0.5
#define PVL   1


// Fuzzy rules
float rules[7][7] = {
    {PVL, PL, PSL, ZO, NSL, NL, NVL},
    {PVL, PL, PSL, ZO, NSL, NL, NVL},
    {PL, PL, PSL, ZO, NSL, NS, NVL},
    {PL, PSL, ZO, NSL, NS, NB, NVL},
    {PSL, ZO, NSL, NS, NB, NB, NVL},
    {PSL, ZO, NSL, NS, NB, NB, NVL},
    {PVL, PL, PSL, ZO, NSL, NL, NVL}
};

// Fuzzy membership functions
float membership(float x, float a, float b, float c) {
    if (x <= a || x >= c) {
        return 0.0;
    }
    else if (x >= b) {
        return (c - x) / (c - b);
    }
    else {
        return (x - a) / (b - a);
    }
}

// Fuzzy inference
float fuzzyInference(float error, float error_c) {
    float inputs[2] = {error, error_c};
    float outputs[7] = {0.0};
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 2; j++) {
            float x = inputs[j];
            switch (i) {
                case 0: outputs[i] = fmax(outputs[i], membership(x, NS, ZO, PS)); break;
                case 1: outputs[i] = fmax(outputs[i], membership(x, ZO, PS, PM)); break;
                case 2: outputs[i] = fmax(outputs[i], membership(x, PS, PM, PB)); break;
                case 3: outputs[i] = fmax(outputs[i], membership(x, NS, ZO, NS)); break;
                case 4: outputs[i] = fmax(outputs[i], membership(x, ZO, NS, NB)); break;
                case 5: outputs[i] = fmax(outputs[i], membership(x, NS, NB, NB)); break;
                case 6: outputs[i] = fmax(outputs[i], membership(x, PM, PB, PB)); break;
            }
        }
    }
    float output = 0.0;
    float sum = 0.0;
    for (int i = 0; i < 7; i++) {
        output += rules[i][i] * outputs[i];
        sum += outputs[i];
        for (int j = 0; j < 7; j++) {
            output += rules[i][j] * outputs[i] * outputs[j];
            sum += outputs[i] * outputs[j];
        }
    }
    output /= sum;
    return output;
}

// Fuzzy PID control loop
float32 FuzzyPIDControl(uint16 speed_ref,uint16 raw_speed)
{
    static float error = 0.0;
    static float error_c = 0.0;
    static float integral = 0.0;
    static float derivative = 0.0;
    static float output = 0.0;
    error = speed_ref - raw_speed;
    integral += error;
    derivative = error - error_c;
    error_c = error;
    float u;
    u = Kp * fuzzyInference(error, error_c) + Ki * integral + Kd * derivative;
    uint16 lower = 30;
    uint16 upper = 900;
    if (u >= upper)
       {
           u = upper;
       }
       else if (u <= lower)
       {
           u = lower;
       }

       return u;
    // Apply output to control system
}




#endif

#if(FuzzyPID ==FuzzyPID2)
    const int  num_area = 8; //划分区域个数
    //float e_max;  //误差做大值
    //float e_min;  //误差最小值
    //float ec_max;  //误差变化最大值
    //float ec_min;  //误差变化最小值
    //float kp_max, kp_min;
    float e_membership_values[7] = {-3,-2,-1,0,1,2,3}; //输入e的隶属值
    float ec_membership_values[7] = { -3,-2,-1,0,1,2,3 };//输入de/dt的隶属值
    float kp_menbership_values[7] = { -3,-2,-1,0,1,2,3 };//输出增量kp的隶属值
    float ki_menbership_values[7] = { -3,-2,-1,0,1,2,3 }; //输出增量ki的隶属值
    float kd_menbership_values[7] = { -3,-2,-1,0,1,2,3 };  //输出增量kd的隶属值
    float fuzzyoutput_menbership_values[7] = { -3,-2,-1,0,1,2,3 };

    //int menbership_values[7] = {-3,-};
    float kp;                       //PID参数kp
    float ki;                       //PID参数ki
    float kd;                       //PID参数kd
    float qdetail_kp;               //增量kp对应论域中的值
    float qdetail_ki;               //增量ki对应论域中的值
    float qdetail_kd;               //增量kd对应论域中的值
    float qfuzzy_output;
    float detail_kp;                //输出增量kp
    float detail_ki;                //输出增量ki
    float detail_kd;                //输出增量kd
    float fuzzy_output;
    float qerro;                    //输入e对应论域中的值
    float qerro_c;                  //输入de/dt对应论域中的值
    float errosum;
    float e_gradmembership[2];      //输入e的隶属度
    float ec_gradmembership[2];     //输入de/dt的隶属度
    int e_grad_index[2];            //输入e隶属度在规则表的索引
    int ec_grad_index[2];           //输入de/dt隶属度在规则表的索引
    float gradSums[7] = {0,0,0,0,0,0,0};
    float KpgradSums[7] = { 0,0,0,0,0,0,0 };   //输出增量kp总的隶属度
    float KigradSums[7] = { 0,0,0,0,0,0,0 };   //输出增量ki总的隶属度
    float KdgradSums[7] = { 0,0,0,0,0,0,0 };   //输出增量kd总的隶属度
    #define NB  -3
    #define NM  -2
    #define NS  -1
    #define ZO   0
    #define PS   1
    #define PM   2
    #define PB   3 //论域隶属值

    int  Kp_rule_list[7][7] = { {PB,PB,PM,PM,PS,ZO,ZO},     //kp规则表
                                {PB,PB,PM,PS,PS,ZO,NS},
                                {PM,PM,PM,PS,ZO,NS,NS},
                                {PM,PM,PS,ZO,NS,NM,NM},
                                {PS,PS,ZO,NS,NS,NM,NM},
                                {PS,ZO,NS,NM,NM,NM,NB},
                                {ZO,ZO,NM,NM,NM,NB,NB} };

    int  Ki_rule_list[7][7] = { {NB,NB,NM,NM,NS,ZO,ZO},     //ki规则表
                                {NB,NB,NM,NS,NS,ZO,ZO},
                                {NB,NM,NS,NS,ZO,PS,PS},
                                {NM,NM,NS,ZO,PS,PM,PM},
                                {NM,NS,ZO,PS,PS,PM,PB},
                                {ZO,ZO,PS,PS,PM,PB,PB},
                                {ZO,ZO,PS,PM,PM,PB,PB} };

    int  Kd_rule_list[7][7] = { {PS,NS,NB,NB,NB,NM,PS},    //kd规则表
                                {PS,NS,NB,NM,NM,NS,ZO},
                                {ZO,NS,NM,NM,NS,NS,ZO},
                                {ZO,NS,NS,NS,NS,NS,ZO},
                                {ZO,ZO,ZO,ZO,ZO,ZO,ZO},
                                {PB,NS,PS,PS,PS,PS,PB},
                                {PB,PM,PM,PM,PS,PS,PB} };

    int  Fuzzy_rule_list[7][7] = { {PB,PB,PB,PB,PM,ZO,ZO},
                                   {PB,PB,PB,PM,PM,ZO,ZO},
                                   {PB,PM,PM,PS,ZO,NS,NM},
                                   {PM,PM,PS,ZO,NS,NM,NM},
                                   {PS,PS,ZO,NM,NM,NM,NB},
                                   {ZO,ZO,ZO,NM,NB,NB,NB},
                                   {ZO,NS,NB,NB,NB,NB,NB}};


//输入e与de/dt隶属度计算函数///
void Get_grad_membership(float erro,float erro_c)
{
    if (erro > e_membership_values[0] && erro < e_membership_values[6])
    {
        for (int i = 0; i < num_area - 2; i++)
        {
            if (erro >= e_membership_values[i] && erro <= e_membership_values[i + 1])
            {
                e_gradmembership[0] = -(erro - e_membership_values[i + 1]) / (e_membership_values[i + 1] - e_membership_values[i]);
                e_gradmembership[1] = 1+(erro - e_membership_values[i + 1]) / (e_membership_values[i + 1] - e_membership_values[i]);
                e_grad_index[0] = i;
                e_grad_index[1] = i + 1;
                break;
            }
        }
    }
    else
    {
        if (erro <= e_membership_values[0])
        {
            e_gradmembership[0] = 1;
            e_gradmembership[1] = 0;
            e_grad_index[0] = 0;
            e_grad_index[1] = -1;
        }
        else if (erro >= e_membership_values[6])
        {
            e_gradmembership[0] = 1;
            e_gradmembership[1] = 0;
            e_grad_index[0] = 6;
            e_grad_index[1] = -1;
        }
    }

    if (erro_c > ec_membership_values[0] && erro_c < ec_membership_values[6])
    {
        for (int i = 0; i < num_area - 2; i++)
        {
            if (erro_c >= ec_membership_values[i] && erro_c <= ec_membership_values[i + 1])
            {
                ec_gradmembership[0] = -(erro_c - ec_membership_values[i + 1]) / (ec_membership_values[i + 1] - ec_membership_values[i]);
                ec_gradmembership[1] = 1 + (erro_c - ec_membership_values[i + 1]) / (ec_membership_values[i + 1] - ec_membership_values[i]);
                ec_grad_index[0] = i;
                ec_grad_index[1] = i + 1;
                break;
            }
        }
    }
    else
    {
        if (erro_c <= ec_membership_values[0])
        {
            ec_gradmembership[0] = 1;
            ec_gradmembership[1] = 0;
            ec_grad_index[0] = 0;
            ec_grad_index[1] = -1;
        }
        else if (erro_c >= ec_membership_values[6])
        {
            ec_gradmembership[0] = 1;
            ec_gradmembership[1] = 0;
            ec_grad_index[0] = 6;
            ec_grad_index[1] = -1;
        }
    }

}

//获取输出增量kp,ki,kd的总隶属度
void GetSumGrad()
{
    for (int i = 0; i <= num_area - 1; i++)
    {
        KpgradSums[i] = 0;
        KigradSums[i] = 0;
    KdgradSums[i] = 0;

    }
  for (int i=0;i<2;i++)
  {
      if (e_grad_index[i] == -1)
      {
       continue;
      }
      for (int j = 0; j < 2; j++)
      {
          if (ec_grad_index[j] != -1)
          {
              int indexKp = Kp_rule_list[e_grad_index[i]][ec_grad_index[j]] + 3;
              int indexKi = Ki_rule_list[e_grad_index[i]][ec_grad_index[j]] + 3;
              int indexKd = Kd_rule_list[e_grad_index[i]][ec_grad_index[j]] + 3;
              //gradSums[index] = gradSums[index] + (e_gradmembership[i] * ec_gradmembership[j])* Kp_rule_list[e_grad_index[i]][ec_grad_index[j]];
              KpgradSums[indexKp]= KpgradSums[indexKp] + (e_gradmembership[i] * ec_gradmembership[j]);
              KigradSums[indexKi] = KigradSums[indexKi] + (e_gradmembership[i] * ec_gradmembership[j]);
              KdgradSums[indexKd] = KdgradSums[indexKd] + (e_gradmembership[i] * ec_gradmembership[j]);
          }
          else
          {
            continue;
          }

      }
  }

}

//计算输出增量kp,kd,ki对应论域值
void GetOUT()
{
    for (int i = 0; i < num_area - 1; i++)
    {
        qdetail_kp += kp_menbership_values[i] * KpgradSums[i];
        qdetail_ki += ki_menbership_values[i] * KigradSums[i];
        qdetail_kd+= kd_menbership_values[i] * KdgradSums[i];
    }
}

//模糊PID控制实现函数
float FuzzyPIDcontroller(float e_max, float e_min, float ec_max, float ec_min, float kp_max, float kp_min, float erro, float erro_c,float ki_max,float ki_min,float kd_max,float kd_min,float erro_pre,float errp_ppre)
{
    errosum += erro;
    //Arear_dipart(e_max, e_min, ec_max, ec_min, kp_max, kp_min,ki_max,ki_min,kd_max,kd_min);
    qerro = Quantization(e_max, e_min, erro);
    qerro_c = Quantization(ec_max, ec_min, erro_c);
    Get_grad_membership(qerro, qerro_c);
    GetSumGrad();
    GetOUT();
    detail_kp = Inverse_quantization(kp_max, kp_min, qdetail_kp);
    detail_ki = Inverse_quantization(ki_max, ki_min, qdetail_ki);
    detail_kd = Inverse_quantization(kd_max, kd_min, qdetail_kd);
    qdetail_kd = 0;
    qdetail_ki = 0;
    qdetail_kp = 0;

    kp = kp + detail_kp;
    ki = ki + detail_ki;
    kd = kd + detail_kd;
    if (kp < 0)
        kp = 0;
    if (ki < 0)
        ki = 0;
    if (kd < 0)
        kd = 0;
    detail_kp = 0;
  detail_ki=0;
  detail_kd=0;
  float output = kp*(erro - erro_pre) + ki * erro + kd * (erro - 2 * erro_pre + errp_ppre);
    return output;
}

///区间映射函数///
float Quantization(float maximum,float minimum,float x)
{
    float qvalues= 6.0 *(x-minimum)/(maximum - minimum)-3;
    //float qvalues=6.0*()
    return qvalues;

    //qvalues[1] = 3.0 * ecerro / (maximum - minimum);
}

//反区间映射函数
float Inverse_quantization(float maximum, float minimum, float qvalues)
{
    float x = (maximum - minimum) *(qvalues + 3)/6 + minimum;
    return x;
}

float32 FuzzyPIDControl(uint16 speed_ref,uint16 raw_speed)
{
    float e_max = 12 ;
    float e_min = -12;
    float ec_max = 4;
    float ec_min = -4;
    float kp_max = 1;
    float kp_min = -1;
    float ki_max = 0.1;
    float ki_min = -0.1;
    float kd_max = 0;
    float kd_min = 0;
    float erro;
    float erro_c;
    float erro_pre = 0;
    float erro_ppre = 0;
    uint16 lower = 30;
    uint16 upper = 900;
    erro = speed_ref - raw_speed;
    erro_c = erro - erro_pre;

    float u;
    u = FuzzyPIDcontroller(e_max, e_min, ec_max, ec_min, kp_max, kp_min, erro, erro_c,ki_max,ki_min,kd_max,kd_min,erro_pre,erro_ppre);
//    uk +=u;
    erro_ppre = erro_pre;
    erro_pre = erro;
    erro = speed_ref - raw_speed;
    erro_c= erro - erro_pre;

    if (u >= upper)
       {
           u = upper;
       }
       else if (u <= lower)
       {
           u = lower;
       }

       return u;

}
#endif

