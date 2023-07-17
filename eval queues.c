#include<stdio.h>
#include<stdlib.h>
#define MAX 1000
struct queue
{
    int elements[1000];
    int front;
    int rear;
};
void readarray(int a[],int n);
void roundrobin(int a[],int n,int k);
void initqueue(struct queue*q);
int isqempty(struct queue*q);
int isqfull(struct queue*q);
void enQueueRear(struct queue *q,int e);
int deQueueFront(struct queue *q);
int deQueueRear(struct queue *q);
void display(struct queue*q);




int main()
{
    int a[MAX];
    int k,Q;
    int n;
    printf("enter number of process:");
    scanf("%d",&n);
    printf("enter number of quantum time:");
    scanf("%d",&Q);
    printf("enter number of rounds:");
    scanf("%d",&k);
    readarray(a,n);
    roundrobin(a,n,k);
}
void readarray(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
}
void roundrobin(int a[],int n,int k)
{
    struct queue q;
    initqueue(&q);
    int N;
    int e,p;
    if(isempty(&q))
        return 0;
    else
        for(int i=0;i<n;i++)
    {
        while(n[i]-k)
        {
            int p=enqueue(&q,(n[i]-k));

        }
        if(n[i]-k==NULL)
        {
        int e=dequeue((&n[i]-k));
        }
    }
    display(&p);
    display(&e);

}
void initqueue(struct queue*q)
{
    q->front=-1;
    q->rear=-1;
}
int isqempty(struct queue*q)
{
    if(q->front==-1)
        return 1;
    else
        return 0;
}
int isqfull(struct queue*q)
{
    if((q->rear+1)% MAX==q->front)
    return 1;
    else
        return 0;
}
void enQueueRear(struct queue *q,int e)
{
    q->rear=(q->rear+1)%MAX;
    q->elements[q->rear]=e;

    if(q->front==-1)
        q->front=0;
}

int deQueueFront(struct queue *q)
{
    int e = q->elements[q->front];

    if(q->front==q->rear)
    {
        q->front=q->rear=-1;
    }

    else
    {

   q->front=(q->front+1)%MAX;
    }


        return e;
}

int deQueueRear(struct queue *q)
{
    int e=q->elements[q->rear];

    if(q->front==q->rear)
        q->front=q->rear=-1;

    else
    {
        q->rear--;
        if(q->rear<0)
            q->rear=MAX-1;
    }
    return e;
}
void display(struct queue*q)
{
    int i;
    if(isqempty(&q))
    return 0;
    else
    {
        for(int i=q->front;i!=q->rear;i=(i+1)%MAX)
            printf("%d",a(q->elements[i]));
    }
    printf("%d ",(q->elements[i]));

}
