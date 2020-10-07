#include "BPSim.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "string.h"

//全局变量定义
double data[]={4.00000000,2.00000000,8.00000000,3.00000000,1.00000000,20.00000000,39.00000000,20.00000000,195.00000000,20.50000000,39.50000000,0.03310830,-0.37441300,-0.00167291,-0.24460609,-0.10438956,0.23382817,-0.05922671,0.71568477,0.73372113,-0.03742807,0.07945321,-0.39183829,-0.11677995,-0.29570070,-0.51158378,-0.81284598,-0.15295506,-0.20596162,-0.40535200,0.38310219,-0.35794901,-0.62758581,-0.17548889,0.04081032,-0.29847953,-0.44078921,-0.05685511,-0.44507755,-0.43257562,0.04194407,-0.26566014,-0.49167953,0.30761305,0.35129332,-0.68091418,-0.51669564,0.05188414,-0.22439041,-0.34538302,0.01056651,-0.34617715,-0.19118015,-0.62926514,-0.38814409,-0.27979596,0.06293768,0.50197621,-0.01550351,0.19158471,0.62419473,1.89221351,-0.17657812,0.79462194,0.00716346,0.16715942,0.31249171};
int layer_all1 = 0;
int *nodes_all1 = NULL;
int num_all = 0;
struct simnetnode **simnetwork=NULL;
float simxminmax[SIMROW_X][2];
float simyminmax[SIMROW_Y][2];

//神经网络节点建立函数
int simNetSetUp(void)
{
	int i = 0,j=0,k=0,n=0;
	//神经网络层数
	layer_all1 = (int)data[n];
	n++;

	//神经网络每层节点数
	nodes_all1 = (int *)malloc(sizeof(int)*layer_all1);
	for (i = 0; i < layer_all1; i++)
	{
		nodes_all1[i] = data[n];
		n++;
	}
	//申请层数
	simnetwork = (struct simnetnode**)malloc(sizeof(struct simnetnode*)*(layer_all1));
	//申请神经网络每层节点
	for (i = 0; i < layer_all1; i++)
	{
		simnetwork[i] = (struct simnetnode*)malloc(sizeof(struct simnetnode)*nodes_all1[i]);
	}

	//映射参数
	for (i = 0; i < SIMROW_X; i++)
	{
		simxminmax[i][0] = data[n];
		n++;
		simxminmax[i][1] = data[n];
		n++;
	}
	for (i = 0; i < SIMROW_Y; i++)
	{
		simyminmax[i][0] = data[n];
		n++;
		simyminmax[i][1] = data[n];
		n++;
	}

	//神经网络节点参数初始化
	for (i = 0; i < layer_all1; i++)
	{
		for (j = 0; j < nodes_all1[i]; j++)
		{
			if (i != layer_all1 - 1)
			{
				simnetwork[i][j].w = (double*)malloc(sizeof(double)*nodes_all1[i + 1]);
				for (k = 0; k < nodes_all1[i + 1]; k++)
				{
					simnetwork[i][j].w[k] = data[n];
					n++;
				}

				simnetwork[i][j].b = data[n];
				n++;
			}
		}
	}
	return 0;

}

int sim(float x[SIMROW_X], float y[SIMROW_Y])
{
	if ((SIMROW_X != nodes_all1[0]) && (SIMROW_Y != nodes_all1[layer_all1 - 1]))
	{
		printf("输入或输出的数量不正确\n");
		return 1;
	}
	int i = 0, j = 0, k = 0;
	for (i = 0; i < layer_all1; i++)
	{
		//如果是输入层
		if (i == 0)
		{
			for (j = 0; j < nodes_all1[i]; j++)
			{
				simnetwork[i][j].input = simDataChange(x[j],j,1);
				simnetwork[i][j].output = simInspirit(simnetwork[i][j].input, simnetwork[i][j].b, 1);
			}
		}
		else
		{
			float s = 0;
			for (j = 0; j < nodes_all1[i]; j++)
			{
				//输入
				s = 0;
				for (k = 0; k < nodes_all1[i - 1]; k++)
				{
					s += (simnetwork[i-1][k].output*simnetwork[i-1][k].w[j]);
				}
				simnetwork[i][j].input = s;
				if (i<(layer_all1-1))
				    simnetwork[i][j].output = simInspirit(simnetwork[i][j].input, simnetwork[i][j].b, 1);
				else
				{
					simnetwork[i][j].output = simnetwork[i][j].input;
					y[j] = simDataRecover(simnetwork[i][j].output,j,1); 
				}
			}
		}
	}
}

//mode1==0,激励函数（sig）
//y=1/(1+exp(x))
//mode1==1,激励函数(正切tansig)
//y=2/(1+e(-2x))-1
double simInspirit(double x, double b, int mode1)
{
	double y = 0;
	x -= b;
	if (mode1 == 0)
	{
		y = 1 + exp(-x);
		y = 1 / y;
	}
	else if (mode1 == 1)
	{
		y = 1 + exp(-2 * x);
		y = 2 / y - 1;
	}
	return y;
}

//int readData(void)
//{
//	FILE *fpread = fopen("data.txt", "r");
//	if (fpread == NULL)
//	{
//		return 1;
//	}
//	double k = 0;
//	num_all = 0;
//	while (fscanf(fpread, "%lf", &k) != EOF)
//		num_all++;
//	fclose(fpread);

//	int i = 0;
//	data = (double*)malloc(num_all*sizeof(double));
//	fpread = fopen("data.txt", "r");
//	while (fscanf(fpread, "%lf", &data[i]) != EOF)
//	{
//		i++;
//	}
//	return 0;
//}

int simInit()
{

//	if (readData())
//	{
//		printf("读取错误\n");
//		return 1;
//	}
	if (simNetSetUp())
	{
		printf("神经网络建立错误\n");
		return 2;
	}
	return 0;
}

//数据映射
double simDataChange(double x,int j,int mode1)
{
	float dis = simxminmax[j][1] - simxminmax[j][0];
	x -= simxminmax[j][0];
	x /= dis;
	if (mode1 == 1)
	{
		x *= 2;
		x -= 1;
	}
	return x;
}

//数据恢复
double simDataRecover(double y, int j,int mode1)
{
	float dis = simyminmax[j][1] - simyminmax[j][0];
	if (mode1 == 1)
	//压缩到0-1区间
	{
		y += 1;
		y /= 2;
	}
	y *= dis;
	y += simyminmax[j][0];
	return y;
}

int simFree(void)
{
	int i = 0, j = 0;
	//释放data
	free(data);
	*data = NULL;

	for (i = 0; i < layer_all1; i++)
	{
		for (j = 0; j < nodes_all1[i]; j++)
		{
			if (i != layer_all1 - 1)
			{
					free(simnetwork[i][j].w);
					simnetwork[i][j].w = NULL;
			}

		}
		free(simnetwork[i]);
		simnetwork[i] = NULL;
	}
	free(simnetwork);
	simnetwork = NULL;
	free(nodes_all1);
	nodes_all1 = NULL;
	return 0;
}
