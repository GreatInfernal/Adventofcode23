#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int readLine(std::string& line){
    std::vector<std::string> numbers={"0","1","2","3","4","5","6","7","8","9"};
    int firs=line.length();
    int last=-1;
    std::string fd,ld;
    for(auto a:numbers){
        int pos=line.find(a);
        if(pos!=std::string::npos){
            if(pos<firs){
                firs=pos;
                fd=a;
            }
        }
        pos=line.rfind(a);
         if(pos!=std::string::npos){
            if(pos>last){
                last=pos;
                ld=a;
            }
        }
    }
    return std::stoi(fd+ld);
}


int main(){
    std::ifstream data;
    data.open("./../../inputs/Day1/input.txt");
    std::string line;
    int sum=0;
    while(std::getline(data,line)){
        sum=sum+readLine(line);
    }
    std::cout<<"Sum: "<<sum;
    return 0;
}
