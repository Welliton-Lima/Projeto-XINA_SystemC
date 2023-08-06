#include <systemc.h>
#include "ring_buffering.h"
#include "shift_buffering.h"

//data width and buffer depth
template<unsigned int mode_p, unsigned int data_width_p, unsigned int buffer_depth_p>

SC_MODULE(buffering){
    shift_buffering<data_width_p, buffer_depth_p> *shift;
    ring_buffering<data_width_p,buffer_depth_p> *ring;

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

    SC_CTOR(buffering){
         if(mode_p == 1){

            //shift_buffering<data_width_p, buffer_depth_p> shift("shift");

            shift = new shift_buffering<data_width_p, buffer_depth_p>("shift");
            shift->data_i(data_i);
            shift->data_o(data_o);
            shift->clk_i(clk_i);
            shift->rst_i(rst_i);
            shift->rd_i(rd_i);
            shift->wr_i(wr_i);
            shift->rok_o(rok_o);
            shift->wok_o(wok_o);

        }
         else{
            //ring_buffering<data_width_p,buffer_depth_p> ring("ring");

            ring = new ring_buffering<data_width_p,buffer_depth_p>("ring");
            ring->data_i(data_i);
            ring->data_o(data_o);
            ring->clk_i(clk_i);
            ring->rst_i(rst_i);
            ring->rd_i(rd_i);
            ring->wr_i(wr_i);
            ring->rok_o(rok_o);
            ring->wok_o(wok_o);
         }

    }
  ~buffering(){
        delete  ring;
        delete  shift;
    }
};
