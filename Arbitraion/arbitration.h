#include <systemc.h>
#include "arbitration_rr_moore.h"
#include "arbitration_rr_mealy.h"


template<unsigned int mode_p>
SC_MODULE(arbitration){
    arbitration_rr_moore *moore;
    arbitration_rr_mealy *mealy;

    sc_in<bool> clk_i;
    sc_in<sc_bv<1>> rst_i;

    //request and grants
    sc_in<sc_bv<4>>req_i;
    sc_out<sc_bv<4>>gnt_o;

     SC_CTOR(arbitration){
        if(mode_p == 1){
            moore = new arbitration_rr_moore("moore");
            moore->clk_i(clk_i);
            moore->rst_i(rst_i);
            moore->req_i(req_i);
            moore->gnt_o(gnt_o);
        }
        else{
            mealy = new arbitration_rr_mealy("mealy");
            mealy->clk_i(clk_i);
            mealy->rst_i(rst_i);
            mealy->req_i(req_i);
            mealy->gnt_o(gnt_o);
        }
    }
    ~arbitration(){
        delete  moore;
        delete  mealy;
    }
};
