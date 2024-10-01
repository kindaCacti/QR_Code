#pragma once
#include "qr_code.h"
#include <fstream>
#include <iostream>

class Bmp_file_handler{
public:
    static void write_to_file(std::string data,  std::string file_path){
        std::ofstream output_file(file_path);
        output_file<<data;
        output_file.close();
    }

    static std::string convert_to_bits(int value, int number_of_bits){
        std::string out = "";
        for(int i = 0; i<number_of_bits; i++){
            int mask = 255<<(i*8);
            int tmp = value&mask;
            tmp>>=i;
            out.push_back((char)tmp);
        }
        return out;
    }

    static std::string get_bmp_header(QRCode& code){
        std::string header = "";
        header += "BM";
        header += Bmp_file_handler::convert_to_bits(code.get_size(), 4);
        header += Bmp_file_handler::convert_to_bits(0, 4);
        header += Bmp_file_handler::convert_to_bits(54, 4);
        header += Bmp_file_handler::convert_to_bits(40, 4);
        header += Bmp_file_handler::convert_to_bits(code.get_width(), 4);
        header += Bmp_file_handler::convert_to_bits(code.get_height(), 4);
        header += Bmp_file_handler::convert_to_bits(1, 2);
        header += Bmp_file_handler::convert_to_bits(24, 2);
        header += Bmp_file_handler::convert_to_bits(0, 4);
        header += Bmp_file_handler::convert_to_bits(0, 4);
        header += Bmp_file_handler::convert_to_bits(2835, 4);
        header += Bmp_file_handler::convert_to_bits(2835, 4);
        header += Bmp_file_handler::convert_to_bits(0, 4);
        header += Bmp_file_handler::convert_to_bits(0, 4);

        return header;
    }

    static std::string convert_data_to_bmp(QRCode& code){
        std::string out = "";

        for(int y = code.get_height()-1; y>=0; y--){
            for(int x = code.get_width()-1; x>=0; x--){
                bool is_black = code.get_bit_at(x, y);
                if(is_black){
                    out.push_back((char)0);
                    out.push_back((char)0);
                    out.push_back((char)0);
                }else{
                    out.push_back((char)255);
                    out.push_back((char)255);
                    out.push_back((char)255);
                }
            }
        }

        return out;
    }

    static void output_bmp_file(QRCode& code, std::string file_path){
        std::string data = get_bmp_header(code);
        data += convert_data_to_bmp(code);
        std::cout<<data<<std::endl;
        Bmp_file_handler::write_to_file(data, file_path);
    }
};

int main(){
    QRCode qr(std::string("ala ma kota"));
    Bmp_file_handler::output_bmp_file(qr, "test.bmp");
    return 0;
}