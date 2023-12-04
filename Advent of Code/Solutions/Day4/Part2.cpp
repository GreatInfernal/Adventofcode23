#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>

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
std::tuple<int,int> processline(const std::string& line){
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
    for(auto& num:split(sets[1]," ")){
        if(num!=""){
            int c=std::stoi(num);
            for (int n:wins){
                if(c==n){
                    match++;
                }
            }
        }
    }
    return {id,match};
}

int processcard(int n,int total, const std::unordered_map<int,int>& mapwins,const std::unordered_map<int,int>& mapcopies){
    if(mapcopies.find(n)!=mapcopies.end()){
        return mapcopies.at(n);
    }else if(mapwins.at(n)==0){
        return 0;
    }else if(n==total){
        return 0;
    }else{
        int result=0;
        if (n+mapwins.at(n)>total){
            result=total-n;
            for (int i=total;i>n;i--){
                result+=processcard(i,total,mapwins,mapcopies);
            }
        }else{
            result=mapwins.at(n);
            for(int i=n+mapwins.at(n);i>n;i--){
                result+=processcard(i,total,mapwins,mapcopies);
            }
        }
        return result;
        
    }
}

int main(){
    std::ifstream file("./../../inputs/Day4/input.txt");
    std::string line;
    std::unordered_map<int,int> mapwins;
    std::unordered_map<int,int> mapcopies;
    int total=0;
    while(getline(file,line)){
    std::tuple<int,int> temp=processline(line);
    mapwins[std::get<0>(temp)]=std::get<1>(temp);
    total=std::get<0>(temp);
    }
    
    for (int i=total;i>=1;i--){
        mapcopies[i]=processcard(i,total,mapwins,mapcopies);
    }
    int s=total;
    for (int i=1;i<=total;i++){
        s+=mapcopies[i];
    }
    std::cout<<"sum:"<<s<<'\n';
    return 0;
}
