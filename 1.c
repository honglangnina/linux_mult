#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#define PMODE 0644
#define BSIZE 512
char abuf[512];


typedef struct timespec tp;
typedef struct{
	tp st[100],en[100],us[100],ast,aen,alltime; //记录时间的变量

	int file1,file2;//进行实验的两个文件名
}cs;


cs f,s;//分别给父进程和子进程用

//把测得的数据写到文件里
void  wf(cs * p,char *s){
	FILE * wf;
	int i=0;
	char path[30];
	strcpy(path,"./");
	strcat(path,s);
	if((wf=fopen(path,"w"))==-1){
		printf("can not open the file %s \n",path);
	}
	printf("写文件的句柄%s:%d\n",s,wf);
	printf("开始写数据到文件：%s \n",s);
	fprintf(wf,"程序开始时间:%ld ,程序结束时间：%ld ,程序的总时间：%ld\n",p->ast.tv_nsec,p->aen.tv_nsec,(p->aen).tv_nsec-(p->ast).tv_nsec)
	fprintf(stdout,"程序开始时间:%ld ,程序结束时间：%ld ,程序的总时间：%ld\n",p->ast.tv_nsec,p->aen.tv_nsec,(p->aen).tv_nsec-(p->ast).tv_nsec);
	while(fprintf(stdout,"%ld,\t%ld,\t%ld\n",(p->st[i]).tv_nsec,(p->en[i]).tv_nsec,(p->en[i]).tv_nsec-(p->st[i]).tv_nsec,(fprintf(wf,"%ld,\t%ld,\t%ld\n",(p->st[i]).tv_nsec,(p->en[i]).tv_nsec,(p->en[i]).tv_nsec-(p->st[i]).tv_nsec))==3)
	i++;

}	

//模仿读文件函数

void  my_read(int file,char *,int size){

}


int main(int argc,char *argv[]){

	int n;
	int x;
	//打开文件file1
	if((f.file1=open(argv[1],0))==-1){
		printf("can not open the file1 !\n");
		getchar();
	}
	printf("文件file1的句柄:%d\n",f.file1);
	//打开文件file2
	if((s.file2=open(argv[2],0))==-1){
		printf("can not open the file2!\n");
		getchar();
	}
	printf("文件file2的文件句柄：%d\n",s.file2);
	clock_gettime(CLOCK_MONOTONIC,&f.ast);
	s.ast=f.ast;
	//创建子进程
	while((x=fork())==-1)
		printf("Create procces!\n");
	//子进程
	if(x==0){
		int i=0;
	
		printf("子进程开始。。。\n");

		do{
			clock_gettime(CLOCK_MONOTONIC,s.st+i);
			n=read(s.file2,abuf,BSIZE);
			clock_gettime(CLOCK_MONOTONIC,s.en+i);
			if(n<=0) break;
			i++;
			printf("子\n");
		}while(i<100);
		
		
		clock_gettime(CLOCK_MONOTONIC,&s.aen);
		printf("子进程结束。\n");
		wf(&s,"son.txt");
		}
	else{
		int j=0;
		printf("父进程开始。。。\n");

		do{
			clock_gettime(CLOCK_MONOTONIC,f.st+j);
			n=read(f.file1,abuf,BSIZE);
			clock_gettime(CLOCK_MONOTONIC,f.en+j);
			if(n<=0) break;
			j++;
			printf("父\n");
		}while(j<100);
		clock_gettime(CLOCK_MONOTONIC,&f.aen);
		printf("父进程结束。\n");
		wf(&f,"father.txt");
	}
	
	return 0;
}

	

