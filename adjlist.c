#include<stdio.h>

int top=-1,q[20],stack[20],front=-1,rear=-1,arr[20][20],visited[20]={0};

void add(int item);
int delete();
void push(int item);
int pop();

int bfs(int s,int n);
int dfs(int s,int n);

int main()
{
   int i,j,n,ch,s;

   printf("Enter the Number of Vertices :");
   scanf("%d",&n);

   for(i=1;i<=n;i++)
       {
        for(j=1;j<=n;j++)
            {
             printf("\nEnter '1' if %d has a arc with %d else '0' :",i,j);
             scanf("%d",&arr[i][j]);
            }
       }
    while(1)
    {
        printf("\nEnter Choice 1:BFS 2:DFS \n");
        scanf("%d",&ch);
        printf("\nEnter stating vertex\n");
        scanf("%d",&s);
        while(ch!=3)
          {
            switch(ch)
                {
                  case 1:bfs(s,n);
                  break;

                  case 2:dfs(s,n);
                  break;
                }
            scanf("%d",&ch);
            for(i=0;i<=n;i++){visited[i]=0;}
          }
    }

}




void add(int item)
    {
        if(rear==19)
            printf("QUEUE FULL");
        else
            {
              if(rear==-1)
                    {
                        q[++rear] = item;
                        front++;
                    }
                else
                    q[++rear]=item;
            }
    }

int delete()
{
    int k;

    if ((front>rear)||(front==-1))
        return (0);
    else
        {
          k=q[front++];
            return(k);
        }
}


void push(int item)
{
    if ( top == 19 )
        printf( "Stack overflow " );
    else
        stack[ ++top ] = item;
}

int pop()
{
    int k;

    if ( top == -1 )
        return ( 0 );
    else
        {
            k = stack[ top-- ];
            return ( k );
        }
}

int bfs(int s,int n)
{
    int i,p;
    add(s);
    visited[s]=1;
    p=delete();
    if(p!=0) printf("%d",p);
    while(p!=0)
        {
        for(i=1;i<=n;i++)
            {
            if((arr[p][i]!=0)&&(visited[i]==0))
                {
                add(i);
                visited[i]=1;
                }
            }
        p=delete();
        if(p!=0) printf("%d",p);
        }
    for(i=1;i<=n;i++)
        {
        if(visited[i]==0) bfs(i,n);
        }
}

int dfs(int s,int n)
{
    int k,i;
    push(s);
    visited[s]=1;
    k=pop();
    if(k!=0) printf("%d",k);

    while(k!=0)
        {
        for(i=1;i<=n;i++)
            {
            if((arr[k][i]!=0)&&(visited[i]==0))
                {
                push(i);
                visited[i]=1;
                }
            k=pop();
            if(k!=0) printf("%d",&k);
            }
        }
        for(i=1;i<=n;i++)
            {
        if(visited[i]==0) dfs(i,n);
            }
}
