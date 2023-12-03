#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
typedef struct{
    int red;
    int green;
    int blue;
} Cubes;
std::vector<std::string> split(const std::string& str, const std::string& delim){
    std::vector<std::string> results;
    size_t start=0;
    size_t end=0;
    while(end!=std::string::npos){
        end=str.find(delim,start);
        results.emplace_back(str.substr(start,end-start));
        start=end+delim.size();
    }
    return results;
}
std::tuple<int,std::vector<Cubes>> readGame(const std::string& line){
    size_t start, end;
    start=line.find("Game ");
    end=line.find(":",start);
    int id=std::stoi(line.substr(start+5,end));
    std::vector<Cubes> drawsets;

    for (auto& set:split(line.substr(end+2),"; ")){
        std::vector<std::string> draws=split(set,", ");
        Cubes c={0,0,0};
        for (auto& draw:draws){
            std::vector<std::string> temp=split(draw," ");
            std::string color=temp[1];
            int count=std::stoi(temp[0]);
            if(color=="red"){
                c.red=count;
            }else if(color=="blue"){
                c.blue=count;
            }else if(color=="green"){
                c.green=count;
            }
        }
        drawsets.emplace_back(c);
    }
    
    return {id,drawsets};
}
int process_draws(std::tuple<int,std::vector<Cubes>> pair){
    int max_red=12;
    int max_blue=14;
    int max_green=13;
    int id=std::get<0>(pair);
    for (auto cube:std::get<1>(pair)){
        if (cube.red>max_red){
            id=0;
        }
        if (cube.blue>max_blue){
            id=0;
        }
        if (cube.green>max_green){
            id=0;
        }
    }
    return id;
}
int main(){
    std::ifstream input;
    input.open("./../../inputs/Day2/input.txt");
    std::string line;
    int sum=0;
    int i=0;
    while(std::getline(input,line)){
        sum=sum+process_draws(readGame(line));
        i++;
    }
    std::cout<<"Sum: "<<sum;
    return 0;
}
