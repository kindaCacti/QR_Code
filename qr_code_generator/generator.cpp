#include <iostream>
#include <fstream>

int main(){
    std::string data_to_encode;
    std::cin>>data_to_encode;

    unsigned short bytes_of_data = data_to_encode.size();

    for(char current_char : data_to_encode){
        for(int i = 7; i>=0; i--){
            std::cout<<isBitOn(current_char, i);
        }
        std::cout<<std::endl;
    }

    std::cout<<data_to_encode<<std::endl;
    return 0;
}