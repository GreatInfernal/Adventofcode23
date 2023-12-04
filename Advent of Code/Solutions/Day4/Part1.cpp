#include <fstream>
#include <string>
#include <iostream>
#include <vector>


std::vector<std::string> split(const std::string& string, const std::string& delim){
    std::vector<std::string> result;
    size_t start=0;
    size_t end=0;
    while(end!=std::string::npos){
        end=string.find(delim,start);
        result.emplace_back(string.substr(start,end-start));
        start=end+delim.size();
    }
    return result;
}
int processline(const std::string& line){
    int start=line.find("Card ");
    int end=line.find(": ");
    int id=std::stoi(line.substr(start+5,end));
    std::vector<std::string> sets=split(line.substr(end+2)," | ");
    std::vector<int> wins;
    for(auto& num:split(sets[0]," ")){
        if (num!=""){
            wins.emplace_back(std::stoi(num));
        }
    }
    std::vector<int>cardnums;
    int match=0;
    int score=0;
    for(auto& num:split(sets[1]," ")){
        if(num!=""){
            int c=std::stoi(num);
            for (int n:wins){
                if(c==n){
                    match++;
                    if(match==1){
                        score=1;
                    }
                    if(match>1){
                        score=score*2;
                    }
                }
            }
        }
    }
    return score;
}

int main(){
    std::ifstream file("./../../inputs/Day4/input.txt");
    std::string line;
    int s=0;
    
    while(getline(file,line)){
        int n=processline(line);
        s=s+n;
    }
    std::cout<<"sum:"<<s<<'\n';
    return 0;
}