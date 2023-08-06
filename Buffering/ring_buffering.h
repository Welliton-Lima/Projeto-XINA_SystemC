#include <systemc.h>
#include "math.h"
#include <cmath>

//data width and buffer depth
template<int data_width_p, int buffer_depth_p>

SC_MODULE(ring_buffering){
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
    sc_signal<sc_uint< static_cast<int>(std::round(log2(buffer_depth_p)))> > wr_ptr_r;
    sc_signal<sc_uint< (static_cast<int>(std::round(log2(buffer_depth_p))))+1> > n_pos_r;

    void ring_buffering_fifo(){
        if(rst_i.read() == "1"){
            rd_ptr_r.write(0);
            wr_ptr_r.write(0);
            n_pos_r.write(0);
        }
        else if(clk_i.posedge() ){
            if(wr_i.read()== "1"  and n_pos_r.read() != buffer_depth_p){

                wr_ptr_r.write(wr_ptr_r.read()+1);
                fifo_r[wr_ptr_r.read()].write(data_i.read());

                if(rd_i.read()=="1" and n_pos_r.read() != 0){
                    rd_ptr_r.write(rd_ptr_r.read()+1);
                }
                else {
                    n_pos_r.write(n_pos_r.read()+1);
                }
            }
            else if(rd_i.read()=="1" and n_pos_r.read() != 0){
                     rd_ptr_r.write(rd_ptr_r.read()+1);
                     n_pos_r.write(n_pos_r.read()-1);
                }
        }

        if(n_pos_r.read()!=0){

            rok_o.write("1");
        }
        else
        {
            rok_o.write("0");
        }
        if(n_pos_r.read()!=buffer_depth_p)
        {
            wok_o.write("1");
        }
        else
        {
            wok_o.write("0");
        }
        data_o.write(fifo_r[rd_ptr_r.read()].read());
//         if(rd_ptr_r.read()==0){
//             data_o.write(fifo_r[rd_ptr_r.read()].read());
//         }else{
//             data_o.write(fifo_r[rd_ptr_r.read()-1].read());
//         }

    }

    SC_CTOR(ring_buffering){
        SC_METHOD(ring_buffering_fifo);
        sensitive << clk_i << rst_i << rd_i << wr_i << data_i;
    }

};
