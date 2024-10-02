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
        create_big_square_from(0, 0);
        create_big_square_from(22, 0);
        create_big_square_from(0, 22);
        create_small_square_from(20, 20);
    }

    void create_big_square_from(int x, int y){
        int square_size = 7;
        create_square_from(x, y, square_size, 1);
        create_square_from(x+1, y+1, square_size-2, 0);
        create_square_from(x+2, y+2, square_size-4, 1);
    }

    void create_small_square_from(int x, int y){
        int square_size = 5;
        create_square_from(x, y, square_size, 1);
        create_square_from(x+1, y+1, square_size-2, 0);
        create_square_from(x+2, y+2, square_size-4, 1);
    }

    void create_square_from(int x, int y, int siz, int col){
        for(int i = 0; i<siz; i++){
            for(int j = 0; j<siz; j++){
                set_bit_at(x+i, y+j, col);
            }
        }
    }
public:

    QRCode(std::string _data){
        width = 29;
        height = 29;
        size = 29*29;
        data = new bool[size]{0};
        used_field = new bool[size]{0};
        create_static_elements();

        int cp = 0;
        for(char cc : _data){
            for(int i = 8; i>=0; i--){
                data[cp] = is_bit_on(cc, i);
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
        return data[pos];
    }

    void set_bit_at(int x, int y, bool val){
        int pos = y*width + x;
        data[pos] = val;
    }
};