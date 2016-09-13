#include<iostream>
#include<vector>
#include<utility>
#include<graphics.h>
using namespace std;
#define pr pair<int,int>
int findOrientation(pr p1,pr p2,pr p3);
bool doIntersect(pr p1,pr p2,pr p3,pr p4);
bool onSegment(pr p1,pr p2,pr p3);
int isInside(vector<pr > polygon,pr test);
void drawPolygon(vector<pr > polygon,pr test);
int main(){
    int N;
    cout << "Enter Number of Vertices: ";
    cin >> N;
    vector<pr > polygon;
    int i =1,x,y;
    while(N--){
        cout << "Enter Vertex " << i << " (x,y): ";
        i++;
        cin >> x >> y;
        polygon.push_back(make_pair(x,y));
    }
    pr test;
    int choice;
    do{
        cout << "Enter testing point (x,y): ";
        cin >> x >> y;
        test = make_pair(x,y);
        if(isInside(polygon,test)==0)
            cout << "ON" << endl;
        else if(isInside(polygon,test)==1)
            cout << "OUTSIDE" << endl;
        else
            cout << "INSIDE" << endl;
        drawPolygon(polygon,test);
        cout << "Continue Testing... (1/0): ";
        cin >> choice;
    }while(choice!=0);
    return 0;
}
void drawPolygon(vector<pr > polygon,pr test){
    int arr[(2*(polygon.size()+1))];
    int j=0;
    for(int i=0;i<(2*(polygon.size()+1))-2;i+=2){
        arr[i]=(polygon[j].first*20 + 100);
        arr[i+1]=(polygon[j].second*20 + 100);
        j++;
    }
    arr[(2*(polygon.size()+1))-2] = polygon[0].first*20 + 100;
    arr[(2*(polygon.size()+1))-1] = polygon[0].second*20 + 100;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    setfillstyle(SOLID_FILL,DARKGRAY);
    fillpoly(polygon.size()+1,arr);
    setcolor(WHITE);
    outtextxy(test.first*20+100,test.second*20+100,"*");
    getch();
    closegraph();
}
int findOrientation(pr p1,pr p2,pr p3){
    int comparisionLogic = (((p3.second-p2.second)*(p2.first-p1.first))-((p2.second-p1.second)*(p3.first-p2.first)));
    if(comparisionLogic>0)
        return -1;//CW
    else if(comparisionLogic<0)
        return 1;//A/CW
    else
        return 0;
}
bool onSegment(pr p1,pr p2,pr p3){
    if(p3.first>=min(p1.first,p2.first) && p3.first<=max(p1.first,p2.first) && p3.second>=min(p1.second,p2.second) && p3.second<=max(p1.second,p2.second))
        return true;
    return false;
}
bool doIntersect(pr p1,pr p2,pr p3,pr p4){
    int o1 = findOrientation(p1,p2,p3);
    int o2 = findOrientation(p1,p2,p4);
    int o3 = findOrientation(p3,p4,p1);
    int o4 = findOrientation(p3,p4,p2);
    if(o1!=o2 && o3!=o4)
        return true;
    if(o1==0 && onSegment(p1,p2,p3))
        return true;
    if(o2==0 && onSegment(p1,p2,p4))
        return true;
    if(o3==0 && onSegment(p3,p4,p1))
        return true;
    if(o4==0 && onSegment(p3,p4,p2))
        return true;
    return false;
}
int isInside(vector<pr > polygon,pr test){
    int i=0;
    int N = polygon.size();
    pr pt_at_infinity = make_pair(100,test.second);
    int count =0;
    int next;
    do{
        next = (i+1)%N;
        if(!findOrientation(polygon[i],polygon[next],test) && onSegment(polygon[i],polygon[next],test)){
            return 0;
        }
        if(doIntersect(polygon[i],polygon[next],test,pt_at_infinity))
            count++;
        i=next;
    }while(next!=0);
    if(count%2==0)
        return 1;//OUTSIDE
    else
        return -1;//INSIDE
}
