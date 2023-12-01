#include <iostream>
#include <vector>
#include <string>
#include <fstream>
int main(){
    std::ifstream data;
    data.open("./../../inputs/Day1/input.txt");
    std::vector<std::pair<std::string,std::string>> nums={
        std::make_pair("zero","z0o"),
        std::make_pair("one","o1e"),
        std::make_pair("two","t2o"),
        std::make_pair("three","t3e"),
        std::make_pair("four","f4r"),
        std::make_pair("five","f5e"),
        std::make_pair("six","s6x"),
        std::make_pair("seven","s7n"),
        std::make_pair("eight","e8t"),
        std::make_pair("nine","n9e"),

    };
    std::string line;
    int sum=0;
    while(std::getline(data,line)){
        for(int i=0;i<nums.size();i++){
            int pos=0;
            while (line.find(nums[i].first,pos)!=std::string::npos){
                line.replace(line.find(nums[i].first,pos),nums[i].first.length(),nums[i].second);
                pos=line.find(nums[i].first,pos);
            }
        }
        char a=line[line.find_first_of("0123456789")];
        char b=line[line.find_last_of("0123456789")];
        int n=(a-'0')*10+b-'0';
         sum=sum+n;
    }
    std::cout<<"Sum: "<<sum;
    return 0;
}