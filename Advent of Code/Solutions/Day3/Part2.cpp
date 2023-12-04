#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_map>
#include <windows.h>
typedef struct{
    int x;
    int y;
}Vec2;
typedef struct{
    int n;
    int len;
    Vec2 position;

}number;
typedef struct{
    char a;
    Vec2 position;
}token;
std::vector<Vec2> bound(Vec2 pos,int xmax,int ymax){
    int xi=pos.x-((pos.x==0)?0:1);
    int xf=pos.x-((pos.x==xmax)?0:1);
    int yi=pos.y-((pos.y==0)?0:1);
    int yf=pos.y-((pos.y==ymax)?0:1);
    std::vector<Vec2> result;
    for(int x=xi;x<=xf;x++){
        for(int y=yi;y<=yf;y++){
            result.emplace_back(Vec2{x,y});
        }
    }
    return result;

}

std::tuple<std::vector<number>,std::vector<token>> processline(std::string& line,int y){
    std::vector<number> numbers;
    std::vector<token> tokens;
    int n=0;
    int nx;

    for (int x=0;x<line.length();x++){
        char prev;
        if (x==0){
            prev='.';
        }else{
            prev=line[x-1];
        }
        char present=line[x];
        char next;
        if(x==line.length()-1){
         next='.';
        }else{
            next=line[x+1];
        }
        if(std::isdigit(present)&&!std::isdigit(prev)&&!std::isdigit(next)){
            n=present-'0';
            nx=x;
            int len=x-nx+1;
            number temp={n,len,Vec2{nx,y}};
            numbers.emplace_back(temp);
        }else if (std::isdigit(present)&&!std::isdigit(prev)){
            n=present-'0';
            nx=x;
        }else if(std::isdigit(present)&& !std::isdigit(next)){
            n=n*10+present-'0';
            int len=x-nx+1;
            number temp={n,len,Vec2{nx,y}};
            numbers.emplace_back(temp);
        }else if(std::isdigit(present)){
            n=n*10+present-'0';
        }

        if(present=='*'){
            token temp={present,Vec2{x,y}};
            tokens.emplace_back(temp);
        }
    }
    return {numbers,tokens};
}
int main(){
    std::ifstream input;
    input.open("./../../inputs/Day3/input.txt");
    std::string line;
    std::vector<number> numbers; 
    std::vector<token> tokens;
    int y=0;
    int x=0;
    while(std::getline(input,line)){
        std::tuple<std::vector<number>,std::vector<token>> temp=processline(line,y);
        numbers.insert(numbers.end(),(std::get<0>(temp)).begin(),(std::get<0>(temp)).end());
        tokens.insert(tokens.end(),(std::get<1>(temp)).begin(),(std::get<1>(temp)).end());
        y++;
        x=line.length();
    }
    std::vector<number> found;
    int sum=0;
    for(auto t:tokens){
        Vec2 tpos=t.position;
        std::vector<int> found;
        for (auto n:numbers){
            Vec2 npos=n.position;
            int f=0;
            if ((tpos.x==npos.x-1)&&(tpos.y<=npos.y+1)&&(tpos.y>=npos.y-1)){
                f=1;
            }else if ((tpos.x==(npos.x+n.len))&&(tpos.y<=npos.y+1)&&(tpos.y>=npos.y-1)){
                f=1;
            }else if((tpos.y==npos.y+1)&&(tpos.x<=npos.x+n.len)&&(tpos.x>=npos.x-1)){
                f=1;
            }else if ((tpos.y==npos.y-1)&&(tpos.x<=npos.x+n.len)&&(tpos.x>=npos.x-1)){
                f=1;
            }
            if (f==1){
                found.emplace_back(n.n);
            }
        }
        int n=0;
        if(found.size()==2){
            n=found[0]*found[1];   
        }
        sum+=n;
    }
    std::cout<<"Sum: "<<sum;
    return 0;
}