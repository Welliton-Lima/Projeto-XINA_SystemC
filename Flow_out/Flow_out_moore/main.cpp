#include <systemc.h>
#include "flow_out_moore.h"
#include "flow_out_tb.h"

#define WIDTH 8

SC_MODULE(SYSTEM){
    flow_out_moore<WIDTH> *flow_out;
    flow_out_tb<WIDTH> *tb;

    sc_clock w_clk_i;

    sc_signal<sc_bv<WIDTH>> w_data_i, w_data_o;
    sc_signal<sc_bv<1>> w_rst_i, w_val_o, w_rok_i, w_ack_i, w_rd_o;


     SC_CTOR(SYSTEM): w_clk_i("clk_i",10,SC_NS){
            flow_out = new flow_out_moore<WIDTH>("flow_out");
            flow_out->data_i(w_data_i);
            flow_out->data_o(w_data_o);
            flow_out->clk_i(w_clk_i);
            flow_out->rst_i(w_rst_i);
            flow_out->val_o(w_val_o);
            flow_out->rok_i(w_rok_i);
            flow_out->ack_i(w_ack_i);
            flow_out->rd_o(w_rd_o);

            tb = new flow_out_tb<WIDTH>("tb");
            tb->data_i(w_data_i);
            tb->data_o(w_data_o);
            tb->clk_i(w_clk_i);
            tb->rst_i(w_rst_i);
            tb->val_o(w_val_o);
            tb->rok_i(w_rok_i);
            tb->ack_i(w_ack_i);
            tb->rd_o(w_rd_o);
     }
    ~SYSTEM(){
        delete  flow_out;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");

    sc_start();
    
    return 0;

}
