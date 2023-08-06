#include "systemc.h"

template<int data_width_p, int buffer_depth_p>

SC_MODULE(fifo_tb){
    sc_in<bool> clk_i;
    sc_out<sc_bv<1>> rst_i, rd_i, wr_i;

    sc_in<sc_bv<1>> rok_o, wok_o;

    sc_out<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<data_width_p>> data_o;

    void logic(){
        data_i.write("00000000");
        rst_i.write("1");
        wait(10, SC_NS);
        rst_i.write("0");
        wait(10, SC_NS);

        wait(10, SC_NS);
        sc_bv<data_width_p> words[10] = {"00000001", "00000011", "00000111", "00001111", "00011111", "00111111", "01111111", "11111111", "11111110", "11111100"};
        wr_i.write("0");
        //data_i.write(0);
        for(int i=0; i<10; i++){

        if(wok_o.read()=="1"){
            data_i.write(words[i]);
            wr_i.write("1");
        }
            wait(10, SC_NS);
            wr_i.write("0");
            wait(10, SC_NS);
        }
        //wait(1000, SC_NS);
        sc_stop();
    }

    void rd(){
        while(true){
            if(rok_o.read() == "1"){
                rd_i.write("1");
                cout << "data in: "<<data_i.read()<<endl;
                cout << "data out: "<<data_o.read()<<endl;
                wait(10, SC_NS);
            } else {
                rd_i.write("0");
                wait(10, SC_NS);
            }
        }
    }

    SC_CTOR(fifo_tb){
        sensitive << clk_i;
        SC_THREAD(logic);
        SC_THREAD(rd);
    }
};
