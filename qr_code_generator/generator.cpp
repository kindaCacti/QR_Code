#include <iostream>
#include <fstream>

bool isBitOn(int value, int bit){
    if(bit < 0 or bit >= 8) return false;

    int mask = 1<<bit;
    return (bool)(value&mask);
}

int main(){
    std::string data_to_encode;
    std::cin>>data_to_encode;

    unsigned int bytes_of_data = data_to_encode.size();

    for(char current_char : data_to_encode){
        for(int i = 7; i>=0; i--){
            std::cout<<isBitOn(current_char, i);
        }
        std::cout<<std::endl;
    }

    std::cout<<data_to_encode<<std::endl;
    return 0;
}