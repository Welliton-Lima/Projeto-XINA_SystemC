#include <systemc.h>
#include "channel_in.h"
#include "xin_tb.h"

#define c_ena_p         0
#define x_id_p          1
#define y_id_p          1
#define flow_mode_p     0
#define routing_mode_p  0
#define buffer_mode_p   1
#define buffer_depth_p  4
#define data_width_p    8

SC_MODULE(SYSTEM){
    channel_in<c_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p> *channel_in0;
    xin_tb<data_width_p> *tb;

    sc_clock clk_i;
    sc_signal<sc_bv<1>> rst_i;
    sc_signal<sc_bv<data_width_p+1>> data_i;
    sc_signal<sc_bv<1>> val_i;
    sc_signal<sc_bv<1>> ack_o;

    sc_signal<sc_bv<1>> req_l_o, req_n_o, req_e_o, req_s_o, req_w_o;
    sc_signal<sc_bv<4>> gnt_i;

    sc_signal<sc_bv<1>> rok_o;
    sc_signal<sc_bv<4>> rd_i;
    sc_signal<sc_bv<data_width_p+1>> data_o;


     SC_CTOR(SYSTEM): clk_i("clk_i",10,SC_NS){

        channel_in0 = new channel_in<c_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p> ("channel_in0");

        channel_in0->set_position(x_id_p,y_id_p);
        channel_in0->rst_i(rst_i);
        channel_in0->clk_i(clk_i);
        channel_in0->data_i(data_i);
        channel_in0->val_i(val_i);
        channel_in0->ack_o(ack_o);
        channel_in0->req_l_o(req_l_o);
        channel_in0->req_n_o(req_n_o);
        channel_in0->req_e_o(req_e_o);
        channel_in0->req_s_o(req_s_o);
        channel_in0->req_w_o(req_w_o);
        channel_in0->gnt_i(gnt_i);
        channel_in0->rok_o(rok_o);
        channel_in0->rd_i(rd_i);
        channel_in0->data_o(data_o);

        tb = new xin_tb<data_width_p>("tb");

        tb->rst_i(rst_i);
        tb->clk_i(clk_i);
        tb->data_i(data_i);
        tb->val_i(val_i);
        tb->ack_o(ack_o);
        tb->req_l_o(req_l_o);
        tb->req_n_o(req_n_o);
        tb->req_e_o(req_e_o);
        tb->req_s_o(req_s_o);
        tb->req_w_o(req_w_o);
        tb->gnt_i(gnt_i);
        tb->rok_o(rok_o);
        tb->rd_i(rd_i);
        tb->data_o(data_o);
    }
    ~SYSTEM(){
        delete  channel_in0;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]) {

    top = new SYSTEM("top");

    sc_start();

    return 0;
}
