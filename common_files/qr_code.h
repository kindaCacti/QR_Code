#pragma once
#include <string>
#include <iostream>

class QRCode{
    int size;
    int width;
    int height;
    bool* data;
    bool* used_field;

    bool is_bit_on(unsigned short value, unsigned short bit){
        if(bit < 0 or bit >= 8) return false;

        short mask = 1<<bit;
        return (bool)(value&mask);
    }

    void create_static_elements(){

    }
public:

    QRCode(std::string _data){
        width = 25;
        height = 25;
        size = 25*25;
        data = new bool[size]{0};
        used_field = new bool[size]{0};
        create_static_elements();

        int cp = 0;
        for(char cc : _data){
            for(int i = 8; i>=0; i--){
                data[cp] = is_bit_on(cc, i);
                std::cout<<data[cp];
                cp++;
            }
        }
    }

    int get_size(){
        return size;
    }

    bool* get_data(){
        return data;
    }

    int get_width(){
        return width;
    }

    int get_height(){
        return height;
    }

    /* point (0, 0) is the bottom right point of the QR Code,
    and point (width-1, height-1) is the top left point of the QR Code*/
    int get_bit_at(int x, int y){
        int pos = y*width + x;
        std::cout<<pos<<" ";
        return data[pos];
    }
};