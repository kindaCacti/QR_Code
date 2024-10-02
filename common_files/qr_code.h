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
        create_big_square_from(21, 21);
        create_big_square_from(21, -1);
        create_big_square_from(-1, 21);
        create_small_square_from(4, 4);
    }

    void create_big_square_from(int x, int y){
        int square_size = 9;
        create_square_from(x, y, square_size, 0);
        create_square_from(x+1, y+1, square_size-2, 1);
        create_square_from(x+2, y+2, square_size-4, 0);
        create_square_from(x+3, y+3, square_size-6, 1);
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

    void write_data(std::string _data){
        int x = 0, y = 0, add = 1;
        int cp = 0;
        int bit = 0;
        while(x < width){
            std::cout<<x<<" "<<y<<std::endl;
            if(!is_used_at(x, y)){
                set_bit_at(x, y, is_bit_on(_data[cp], bit));
                bit++;
            }
            if(bit >= 8){
                bit = 0;
                cp++;
            }
            if(cp >= _data.size()) break;
            if(x%2){
                x--;
                y+=add;
                if(y == -1){
                    y = 0;
                    x += 2;
                    add = 1;
                }
                if(y>=height){
                    y = height-1;
                    x += 2;
                    add = -1;
                }
            }else{
                x++;
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

        write_data(_data);
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
        if(x<0 or x>=width) return;
        if(y<0 or y>=height) return;
        int pos = y*width + x;
        used_field[pos] = true;
        data[pos] = val;
    }

    bool is_used_at(int x, int y){
        if(x<0 or x>=width) return 0;
        if(y<0 or y>=height) return 0;
        int pos = y*width + x;
        return used_field[pos];
    }
};