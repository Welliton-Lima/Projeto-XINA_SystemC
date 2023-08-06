#include <systemc.h>
#include "math.h"
#include <cmath>

//data width and buffer depth
template<int data_width_p, int buffer_depth_p>

SC_MODULE(shift_buffering){
    sc_in<bool> clk_i;
    sc_in<sc_bv<1>> rst_i;

    // read from buffer
    sc_out<sc_bv<1>> rok_o;
    sc_in<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<1>> rd_i;

    //write to buffer
    sc_out<sc_bv<data_width_p>> data_o;
    sc_in<sc_bv<1>> wr_i;
    sc_out<sc_bv<1>> wok_o;

    //signals
    //sc_signal<sc_bv<buffer_depth_p>> fifo_r[data_width_p];
    sc_signal<sc_bv<data_width_p>> fifo_r[buffer_depth_p];
    //sc_signal<sc_uint<buffer_depth_p>> rd_ptr_r;
    sc_signal<sc_uint< static_cast<int>(std::round(log2(buffer_depth_p)))> > rd_ptr_r;


    void shift_buffering_fifo(){
        if(rst_i.read() == "1"){
            rd_ptr_r.write(0);
        }
        else if(clk_i.posedge() ){
            if(wr_i.read()== "1"  and rd_ptr_r.read() != buffer_depth_p){

                fifo_r[0].write(data_i.read());

                for(int i=1;i<buffer_depth_p; i++){

                    fifo_r[i].write(fifo_r[i-1].read());
                }

                if(!(rd_i.read()=="1" and rd_ptr_r.read() != 0)){
                    rd_ptr_r.write(rd_ptr_r.read()+1);
                }

            }
            else if(rd_i.read()=="1" and rd_ptr_r.read() != 0){
                    rd_ptr_r.write(rd_ptr_r.read()-1);
                }
        }

        if(rd_ptr_r.read()!=0){

            rok_o.write("1");
        }
        else
        {
            rok_o.write("0");
        }
        if(rd_ptr_r.read()!=buffer_depth_p)
        {
            wok_o.write("1");
        }
        else
        {
            wok_o.write("0");
        }
        if(rd_ptr_r.read()==0){
            data_o.write(fifo_r[rd_ptr_r.read()].read());
        }else{
            data_o.write(fifo_r[rd_ptr_r.read()-1].read());
        }

    }

    SC_CTOR(shift_buffering){
        SC_METHOD(shift_buffering_fifo);
        sensitive << clk_i << rst_i << rd_i << wr_i << data_i;
    }

};
