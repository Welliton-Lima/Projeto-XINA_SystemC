#include <systemc.h>
#include "arbitration_tb.h"
#include "arbitration_rr_mealy.h"

SC_MODULE(SYSTEM){
    arbitration_rr_mealy *mealy_rr;
    arbitration_tb *tb;

    sc_clock w_clk_i;
    sc_signal<sc_bv<1>> rst_w;
    sc_signal<sc_bv<4>> req_w;
    sc_signal<sc_bv<4>> gnt_w;


     SC_CTOR(SYSTEM): w_clk_i("w_clk_i",10,SC_NS){
            mealy_rr = new arbitration_rr_mealy("mealy_rr");
            mealy_rr->clk_i(w_clk_i);
            mealy_rr->rst_i(rst_w);
            mealy_rr->req_i(req_w);
            mealy_rr->gnt_o(gnt_w);

            tb = new arbitration_tb("tb");
            tb->clk_w(w_clk_i);
            tb->rst_w(rst_w);
            tb->req_w(req_w);
            tb->gnt_w(gnt_w);

     }
    ~SYSTEM(){
        delete  mealy_rr;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");

    sc_start();
    
    return 0;

}
