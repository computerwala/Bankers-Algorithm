#include<stdio.h>
#include<stdlib.h>


void print(int x[][10],int n,int m){
    int i,j;
    for(i=0;i<n;i++){
        printf("\n");
        for(j=0;j<m;j++){
            printf("%d\t",x[i][j]);
        }
    }
}

//Resource Request algorithm
//here we are taking some additional resources that is given in question
//1. Request1: P0 requests 0 instances of A and 0 instances of B and 2 instances of C like this process will go in safe sate
//2. Request2: P1 requests for 2 instances of A, 0 instances of B and 0 instances of C and this will show error encounter
void res_request(int A[10][10],int N[10][10],int AV[10][10],int pid,int m)
{
    int reqmat[1][10];
    int i;
    printf("\n Enter additional request :- \n");
    for(i=0;i<m;i++){
        printf(" Request for resource %d : ",i+1);
        scanf("%d",&reqmat[0][i]);
    }

    for(i=0;i<m;i++)
        if(reqmat[0][i] > N[pid][i]){
            printf("\n Error encountered.\n");
            exit(0);
    }

    for(i=0;i<m;i++)
        if(reqmat[0][i] > AV[0][i]){
            printf("\n Resources unavailable.\n");
            exit(0);
        }

    for(i=0;i<m;i++){
        AV[0][i]-=reqmat[0][i];
        A[pid][i]+=reqmat[0][i];
        N[pid][i]-=reqmat[0][i];
    }
}

//Safety algorithm
//here it will check weather the process is in safe state or not by using safety algorithm
int safety(int A[][10],int N[][10],int AV[1][10],int n,int m,int a[]){

    int i,j,k,x=0;
    int F[10],W[1][10];
    int pflag=0,flag=0;
    for(i=0;i<n;i++)
        F[i]=0;
    for(i=0;i<m;i++)
        W[0][i]=AV[0][i];

    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            if(F[i] == 0){
                flag=0;
                for(j=0;j<m;j++){
                    if(N[i][j] > W[0][j])
                        flag=1;
                }
                if(flag == 0 && F[i] == 0){
                    for(j=0;j<m;j++)
                        W[0][j]+=A[i][j];
                    F[i]=1;
                    pflag++;
                    a[x++]=i;
                }
            }
        }
        if(pflag == n)
            return 1;
    }
    return 0;
}


//Banker's Algorithm
//by using data structure algorithm this code was written
//here it takes the input from the user
//for example: in question it is given 3 process P0,P1 and P2 and 3 resources A,B and C after entering that value
//it will assign that input in form of matrix and find need matrix by subtracting max- allocation and make its matrix
//after that it will jump toward above code and use safety algorithm by checking work = allocation
//and then comparing need <= Work after that if it false then work = work + allocation and it will check again if it is true then process will be in safe sate
//it will print process according to sequence and print process is in safe sate or it is having deadlock condition or not
void accept(int A[][10],int N[][10],int M[10][10],int W[1][10],int *n,int *m){
    int i,j;
    printf("\n Enter total no. of processes : ");
    scanf("%d",n);
    printf("\n Enter total no. of resources : ");
    scanf("%d",m);
    for(i=0;i<*n;i++){
        printf("\n Process %d\n",i+1);
        for(j=0;j<*m;j++){
            printf(" Allocation for resource %d : ",j+1);
            scanf("%d",&A[i][j]);
            printf(" Maximum for resource %d : ",j+1);
            scanf("%d",&M[i][j]);
        }
    }
    printf("\n Available resources : \n");
    for(i=0;i<*m;i++){
        printf(" Resource %d : ",i+1);
        scanf("%d",&W[0][i]);
    }

    for(i=0;i<*n;i++)
        for(j=0;j<*m;j++)
            N[i][j]=M[i][j]-A[i][j];

    printf("\n Allocation Matrix");
    print(A,*n,*m);
    printf("\n Maximum Requirement Matrix");
    print(M,*n,*m);
    printf("\n Need Matrix");
    print(N,*n,*m);

}

int banker(int A[][10],int N[][10],int W[1][10],int n,int m){
    int j,i,a[10];
    j=safety(A,N,W,n,m,a);
    if(j != 0 ){
        printf("\n\n");
        for(i=0;i<n;i++)
             printf(" P%d  ",a[i]);
        printf("\n A safety sequence has been detected.\n");
        return 1;
    }else{
        printf("\n Deadlock has occured.\n");
        return 0;
    }
}

//it is the main function of program
//after checking all the process it will ask user if they want to add any additional resources
//if user says yes then program will jump to above code where it will take additional resources and check process is in safe state or not
//after completing all the process the program will exit
int main(){
    int ret;
    int A[10][10];
    int M[10][10];
    int N[10][10];
    int W[1][10];
    int n,m,pid,ch;
    printf("\n DEADLOCK AVOIDANCE USING BANKER'S ALGORITHM\n");
    accept(A,N,M,W,&n,&m);
    ret=banker(A,N,W,n,m);
    if(ret !=0 ){
        printf("\n Do you want make an additional request ? (1=Yes|0=No)");
        scanf("%d",&ch);
        if(ch == 1){
            printf("\n Enter process no. : ");
            scanf("%d",&pid);
            res_request(A,N,W,pid-1,m);
            ret=banker(A,N,W,n,m);
            if(ret == 0 )
                exit(0);
        }
    }else
        exit(0);
    return 0;
}
