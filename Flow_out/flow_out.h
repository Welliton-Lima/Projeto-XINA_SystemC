#include <systemc.h>
#include "flow_out_mealy.h"
#include "flow_out_moore.h"

//data width and mode
template<unsigned int mode_p, unsigned int data_width_p>

SC_MODULE(flow_out){
    flow_out_mealy<data_width_p> *mealy;
    flow_out_moore<data_width_p> *moore;

    sc_in<bool> clk_i;
    sc_in<sc_bv<data_width_p>> data_i;
    sc_out<sc_bv<data_width_p>> data_o;

    sc_in<sc_bv<1>> rst_i, rok_i,ack_i;
    sc_out<sc_bv<1>> rd_o,val_o;


    SC_CTOR(flow_out){
         if(mode_p == 1){
            mealy = new flow_out_mealy<data_width_p>("mealy");
            mealy->data_i(data_i);
            mealy->data_o(data_o);
            mealy->clk_i(clk_i);
            mealy->rst_i(rst_i);
            mealy->val_o(val_o);
            mealy->rok_i(rok_i);
            mealy->ack_i(ack_i);
            mealy->rd_o(rd_o);
        }
         else{
            moore = new flow_out_moore<data_width_p>("moore");
            moore->data_i(data_i);
            moore->data_o(data_o);
            moore->clk_i(clk_i);
            moore->rst_i(rst_i);
            moore->val_o(val_o);
            moore->rok_i(rok_i);
            moore->ack_i(ack_i);
            moore->rd_o(rd_o);
         }
    }
  ~flow_out(){
        delete  mealy;
        delete  moore;
    }
};
