/*�Թ�*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#define INF 99999999
#define SIZE 21     //�Թ���С 
#define bug puts("Hello\n")
using namespace std;
struct Node{
    int x,y;
    Node(){x=0;y=0;}
    Node(int x,int y):x(x),y(y){}
};//����һ���洢�˵�����ݽṹ 
int Maze[SIZE][SIZE];  //�������� 
vector<Node>maze;//�������ȡ�� 
Node Move[4]={Node(-1,0),Node(0,1),Node(1,0),Node(0,-1)};//���������ƶ�����00Ϊ�����ƶ��� 
int rand(int t){//���һ����0-(t-1)������ 
    return (int)rand()%t;   
} 
void init(){//��ʼ�� 
    memset(Maze,0,sizeof(Maze));
    srand(time(0));
    for(int i=0;i<SIZE/2;i++){
        for(int j=0;j<SIZE/2;j++){
            maze.push_back(Node(i,j)); 
        }
    }
}
Node RandNode(){//����һ���б��е�����ڵ� 
    int temp=rand(maze.size());
    Node Now=maze[temp];
    return Now;
}
int FindWay(Node a){//Ѱ�ҿ��ƶ��ķ��� 
    vector<int>temp;
    vector<int>reverse;
    for(int i=0;i<4;i++){
        int tx=a.x+Move[i].x;//��������� 
        int ty=a.y+Move[i].y;
        if(tx<0||tx>=SIZE/2||ty<0||ty>=SIZE/2)continue;
        if(Maze[tx*2+1][ty*2+1]==1){
            reverse.push_back(i);
            continue;
        }
        temp.push_back(i);
    }
    if(temp.size()==0){
    //����޿��ƶ����������Ϊ���㣬�������ܿ���ͨ�ķ���ȫ��ͨ 
        for(int i=0;i<4;i++){
            int tempx=a.x*2+1+Move[i].x;
            int tempy=a.y*2+1+Move[i].y;
            if(tempx>0&&tempx<SIZE-1&&tempy>0&&tempy<SIZE-1)
            Maze[tempx][tempy]=1;
        }
        //��������㣬������һ��2*2�ķ�������Χ������Ϊ�����Ż� 
        for(int i=0;i<=1;i++){
            for(int j=0;j<=1;j++){
                int tx=a.x*2+1+i;
                int ty=a.y*2+1+j;
                if(tx>0&&tx<SIZE-1&&ty>0&&ty<SIZE-1){
                    Maze[tx][ty]=1;
                }
            } 
        }
        return -1;
    } 
    else return temp[rand(temp.size())];
} 
void Erase(Node t){//ɾ���ڵ㣬��֤���ȡ�����ȷ�� 
    int l=-1,r=maze.size();
    while(r-l>1){
        int temp=(l+r)/2;
        if(maze[temp].x>t.x||(maze[temp].x==t.x&&maze[temp].y>t.y)){
            r=temp;
        }
        else l=temp;
    }
    Node lt=maze[l];
    maze.erase(maze.begin()+l);
}
void Generate(){//�����Թ� 
    while(maze.size()){
        Node t=RandNode();
        queue<Node>q;
        q.push(t);
        int flag=0;
        while(q.size()){
            Node temp=q.front();q.pop();
            Erase(temp);
            Maze[temp.x*2+1][temp.y*2+1]=1;         
            int Vocation=FindWay(temp);
            if(Vocation==-1)break;          
            Node Direct=Move[Vocation];
            int Nx=temp.x*2+1+Direct.x,Ny=temp.y*2+1+Direct.y;      
            Maze[Nx][Ny]=1;
            q.push(Node(temp.x+Direct.x,temp.y+Direct.y));
        }
    }
}
void print(){//��ӡ�Թ� 
    for(int i=0;i<SIZE;i++){
        printf("%d:\t",i);
        for(int j=0;j<SIZE;j++) 
        if( Maze[i][j]==1)
        printf(" ");
        else
         printf("*");
        printf("\n");
    }
}
int main(){
    init(); 
    Generate();
    print();
    return 0;
}

