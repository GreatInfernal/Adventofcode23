#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int readLine(std::string& line){
    std::vector<std::string> numbers={
        "zero","one","two","three","four","five","six","seven","eight","nine",
        "0","1","2","3","4","5","6","7","8","9"};
    int firs=line.length();
    int last=-1;
    int fd,ld;
    for(int i=0;i<numbers.size();i++){
        auto a=numbers[i];
        int pos=line.find(a);
        if(pos!=std::string::npos){
            if(pos<firs){
                firs=pos;
                fd=i;
            }
        }
        pos=line.rfind(a);
         if(pos!=std::string::npos){
            if(pos>last){
                last=pos;
                ld=i;
            }
        }
    }
    if(fd<10){
        fd=fd+10;
    }
    if(ld<10){
        ld=ld+10;
    }
    return std::stoi(numbers[fd]+numbers[ld]);
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
