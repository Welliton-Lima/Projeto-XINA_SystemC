#include <systemc.h>
#include "channel_out.h"
#include "channel_out_tb.h"

#define c_ena_p            1
#define flow_mode_p        0
#define arbitration_mode_p 0
#define data_width_p       8

SC_MODULE(SYSTEM){
    channel_out<c_ena_p,flow_mode_p,arbitration_mode_p,data_width_p> *channel_out0;
    channel_out_tb *tb0;

    sc_clock clk_i;
    sc_signal<sc_bv<1>> w_rst_i;

    sc_signal<sc_bv<data_width_p+1>> w_data_o;
    sc_signal<sc_bv<1>> w_val_o;
    sc_signal<sc_bv<1>> w_ack_i;

    sc_signal<sc_bv<4>> w_req_i;
    sc_signal<sc_bv<4>> w_gnt_o;

    sc_signal<sc_bv<4>> w_rok_i;
    sc_signal<sc_bv<1>> w_rd_o;
    sc_signal<sc_bv<data_width_p+1>> w_data3_i, w_data2_i, w_data1_i, w_data0_i;



     SC_CTOR(SYSTEM): clk_i("clk_i",10,SC_NS){

        channel_out0 = new channel_out<c_ena_p,flow_mode_p,arbitration_mode_p,data_width_p> ("channel_out0");

        channel_out0->clk_i(clk_i);
        channel_out0->rst_i(w_rst_i);
        channel_out0->data_o(w_data_o);
        channel_out0->val_o(w_val_o);
        channel_out0->ack_i(w_ack_i);
        channel_out0->req_i(w_req_i);
        channel_out0->gnt_o(w_gnt_o);
        channel_out0->rok_i(w_rok_i);
        channel_out0->rd_o(w_rd_o);
        channel_out0->data3_i(w_data3_i);
        channel_out0->data2_i(w_data2_i);
        channel_out0->data1_i(w_data1_i);
        channel_out0->data0_i(w_data0_i);

        tb0 = new channel_out_tb("tb");

        tb0->clk_i(clk_i);
        tb0->rst_i(w_rst_i);
        tb0->data_o(w_data_o);
        tb0->val_o(w_val_o);
        tb0->ack_i(w_ack_i);
        tb0->req_i(w_req_i);
        tb0->gnt_o(w_gnt_o);
        tb0->rok_i(w_rok_i);
        tb0->rd_o(w_rd_o);
        tb0->data3_i(w_data3_i);
        tb0->data2_i(w_data2_i);
        tb0->data1_i(w_data1_i);
        tb0->data0_i(w_data0_i);


    }
    ~SYSTEM(){
        delete  channel_out0;
        delete  tb0;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]) {

    top = new SYSTEM("top");

    sc_start();

    return 0;
}
