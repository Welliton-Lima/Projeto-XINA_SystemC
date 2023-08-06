#include <systemc.h>
#include "flow_in.h"
#include "flow_in_tb.h"

#define WIDTH 9
#define MODE 1

SC_MODULE(SYSTEM){
    flow_in<MODE,WIDTH> *flow_i;
    flow_in_tb<WIDTH> *tb;

    sc_clock w_clk;
    sc_signal<sc_bv<WIDTH>> w_data_i, w_data_o;
    sc_signal<sc_bv<1>> w_rst, w_val, w_wok, w_ack, w_wr;

     SC_CTOR(SYSTEM): w_clk("clk",10,SC_NS){
            flow_i = new flow_in<MODE,WIDTH>("flow_i");
            flow_i->data_i(w_data_i);
            flow_i->data_o(w_data_o);
            flow_i->clk_i(w_clk);
            flow_i->rst_i(w_rst);
            flow_i->val_i(w_val);
            flow_i->wok_i(w_wok);
            flow_i->ack_o(w_ack);
            flow_i->wr_o(w_wr);

            tb = new flow_in_tb<WIDTH>("tb");
            tb->data_i(w_data_i);
            tb->data_o(w_data_o);
            tb->clk_i(w_clk);
            tb->rst_i(w_rst);
            tb->val_i(w_val);
            tb->wok_i(w_wok);
            tb->ack_o(w_ack);
            tb->wr_o(w_wr);
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
