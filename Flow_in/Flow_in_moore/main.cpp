#include <systemc.h>
#include "flow_in_moore.h"
#include "flow_in_tb.h"

#define WIDTH 8

SC_MODULE(SYSTEM){
    flow_in_moore<WIDTH> *flow_i;
    flow_in_tb<WIDTH> *tb;

    sc_clock w_clk_i;

    sc_signal<sc_bv<WIDTH>> w_data_i, w_data_o;

    sc_signal<sc_bv<1>> w_rst_i, w_val_i, w_wok_i, w_ack_o, w_wr_o;
    sc_signal<sc_bv<2>> w_current_r, w_next_w;

     SC_CTOR(SYSTEM): w_clk_i("clk_i",10,SC_NS){

            //buffering<MODE, WIDTH, DEPTH> *fifo;

            flow_i = new flow_in_moore<WIDTH>("flow_i");
            flow_i->data_i(w_data_i);
            flow_i->data_o(w_data_o);
            flow_i->clk_i(w_clk_i);
            flow_i->rst_i(w_rst_i);
            flow_i->val_i(w_val_i);
            flow_i->wok_i(w_wok_i);
            flow_i->ack_o(w_ack_o);
            flow_i->wr_o(w_wr_o);

            tb = new flow_in_tb<WIDTH>("tb");
            tb->data_i(w_data_i);
            tb->data_o(w_data_o);
            tb->clk_i(w_clk_i);
            tb->rst_i(w_rst_i);
            tb->val_i(w_val_i);
            tb->wok_i(w_wok_i);
            tb->ack_o(w_ack_o);
            tb->wr_o(w_wr_o);
     }
    ~SYSTEM(){
        delete  flow_i;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");

    sc_start();
    
    return 0;

}
