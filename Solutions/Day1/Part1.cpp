#include <iostream>
#include <vector>
#include <string>
#include <fstream>
int main(){
    std::ifstream data;
    data.open("./../../inputs/Day1/input.txt");
    std::string line;
    int sum=0;
    while(std::getline(data,line)){
            char a=line[line.find_first_of("0123456789")];
            char b=line[line.find_last_of("0123456789")];
            int n=(a-'0')*10+b-'0';
            sum=sum+n;
    }
    std::cout<<"Sum: "<<sum;
    return 0;
}