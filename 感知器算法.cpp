#include<iostream>
#include<math.h>
#include<stdlib.h>
using namespace std;
#define COUNT 20  //����ѵ������
#define DIMEN  5  // ��������ά��
int score[COUNT][DIMEN];
float score1,score2,score3,score4,score5,aver;
double x[COUNT][DIMEN]; 	// ��������ѵ������
int y[COUNT];              // ѵ�����
int d[COUNT];              // �������
double W[COUNT];           // Ȩֵ����
double thres;               // ��ֵ
double eps = 0.0001;       // ���������жϵ�����
double s, dp, ep;   // dpΪ���������ʵ������ĲepΪ�������
double deta = 0.2;          // ѧϰ����
double r[1] = {3.0};            // ���������
int i, j, k;

void train() {
	FILE *fpRead=fopen("scores.txt","r");
	if(fpRead==NULL) exit(0);
	fscanf(fpRead,"%*[^\n]");  //������һ��
	for(i=0; i<20; i++) {
		fscanf(fpRead,"%f\t%f\t%f\t%f\t%f",&score1,&score2,&score3,&score4,&score5);
		x[i][1]=score1/100;
		x[i][2]=score2/100;
		x[i][3]=score3/100;
		x[i][4]=score4/100;
		x[i][5]=score5/100;
		printf("%f\t%f\t%f\t%f\t%f\n",x[i][1],x[i][2],x[i][3],x[i][4],x[i][5]);
		aver = (x[i][1]+x[i][2]+x[i][3]+x[i][4]+x[i][5])/5;
		if((float)aver >= 0.6)
			d[i] = 1;
		else
			d[i] = 0;
		printf("%d\n",d[i]);
	}
	for(j = 0; j < DIMEN; j++)         //��Ȩֵ����ֵ���г�ʼ�����������[-1,1]�����
		W[j] = (2.0 * rand() / RAND_MAX - 1) ;
	thres = (2.0 * rand() / RAND_MAX - 1) ;
//	thres = 0.5;
	k = 0;                        //��������
	while(1) {
		ep = 0;
		for(i = 0; i < COUNT; i++) {
			s = 0;
			for(j = 0; j < DIMEN; j++)
				s += W[j] * x[i][j];
			s = s - thres;
			if(s >= 0.6)
				y[i] = 1;
			else
				y[i] = 0;
			dp = (double)(d[i] - y[i]);
			for(j = 0; j < DIMEN; j++) { //����Ȩֵ����ֵ
				W[j] = W[j] + deta * dp * x[i][j];
				thres = thres - deta * dp;
			}
			dp =(dp * dp )/ 2.0;
			ep += dp;
		}
		k++;
		if(ep <= eps)     
			break;
	}
}

void test () {
	double xt[20][5];          //��������
	int dt[20];                //�����������
	int yt[20];               //�������
	int count = 0;          //������ȷ����Ŀ
	double Rate;             //��ȷ������
	FILE *fpRead1=fopen("scores-test.txt","r");
	if(fpRead1==NULL) exit(0);
	fscanf(fpRead1,"%*[^\n]");  //������һ��
	for(i=0; i<20; i++) {
		fscanf(fpRead1,"%f\t%f\t%f\t%f\t%f",&score1,&score2,&score3,&score4,&score5);
		xt[i][1]=score1/100;
		xt[i][2]=score2/100;
		xt[i][3]=score3/100;
		xt[i][4]=score4/100;
		xt[i][5]=score5/100;
		aver = (xt[i][1]+xt[i][2]+xt[i][3]+xt[i][4]+xt[i][5])/5;
		if((float)aver >= 0.6)
			dt[i] = 1;
		else
			dt[i] = 0;
//		printf("%d\n",d[i]);
		s = 0;
		for(j = 0; j < DIMEN; j++)                          //����������
			s += W[j] * xt[i][j];
		s = s - thres;
		if(s >= 0.6)
			y[i] = 1;
		else
			y[i] = 0;

		if(dt[i] == y[i])
			count++;
	}
	printf("\n�������ݽ����\n");
	printf("��ȷ�������=%d\n",count);
	Rate = (double)(count / (double)COUNT);
	printf("������ȷ�ʣ�\n");
	printf("%f",Rate*100);
	printf("\n������ɼ������ѧ����ţ�");
	for(j = 0; j < COUNT; j++)
		if ((double)y[j] == 1)
			printf("%d ",j+1);
	printf("\n������ɼ��ϸ��ѧ����ţ�");
	for(j = 0; j < COUNT; j++)
		if ((double)y[j] == 0)
			printf("%d ",j+1);
};

int main() {
	train();
	printf("��������=%d\n",k);
	printf("Ȩֵ��\n");
	for(j = 0; j < DIMEN; j++)
		printf("%f\n",W[j]);
	printf("��ֵ��\n");
	printf("%f\n",thres);
	printf("�ɼ������ѧ����ţ�");
	for(j = 0; j < COUNT; j++)
		if ((double)y[j] == 1)
			printf("%d ",j+1);
	printf("\n�ɼ��ϸ��ѧ����ţ�");
	for(j = 0; j < COUNT; j++)
		if ((double)y[j] == 0)
			printf("%d ",j+1);
//		printf("%d\n",y[j]) ;
	test();
	cout<<endl;
}


