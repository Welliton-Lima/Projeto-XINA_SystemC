#include <systemc.h>
#include "router.h"
#include "router_tb.h"

#define x_id_p             1
#define y_id_p             1
#define l_ena_p            1
#define n_ena_p            1
#define e_ena_p            1
#define s_ena_p            1
#define w_ena_p            1
#define flow_mode_p        0
#define routing_mode_p     0
#define arbitration_mode_p 0
#define buffer_mode_p      1
#define buffer_depth_p     4
#define data_width_p       8

SC_MODULE(SYSTEM){

    router<l_ena_p,n_ena_p,e_ena_p,s_ena_p,w_ena_p,flow_mode_p,routing_mode_p,arbitration_mode_p,buffer_mode_p, buffer_depth_p,data_width_p> *router0;
    router_tb<data_width_p> *tb;

    sc_clock        clk_i;
    sc_signal<sc_bv<1>> rst_i;

    sc_signal<sc_bv<data_width_p+1>> l_in_data_i;
    sc_signal<sc_bv<1>>              l_in_val_i;
    sc_signal<sc_bv<1>>              l_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> l_out_data_o;
    sc_signal<sc_bv<1>>              l_out_val_o;
    sc_signal<sc_bv<1>>              l_out_ack_i;

    sc_signal<sc_bv<data_width_p+1>> n_in_data_i;
    sc_signal<sc_bv<1>>              n_in_val_i;
    sc_signal<sc_bv<1>>              n_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> n_out_data_o;
    sc_signal<sc_bv<1>>              n_out_val_o;
    sc_signal<sc_bv<1>>              n_out_ack_i;

    sc_signal<sc_bv<data_width_p+1>> e_in_data_i;
    sc_signal<sc_bv<1>>              e_in_val_i;
    sc_signal<sc_bv<1>>              e_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> e_out_data_o;
    sc_signal<sc_bv<1>>              e_out_val_o;
    sc_signal<sc_bv<1>>              e_out_ack_i;

    sc_signal<sc_bv<data_width_p+1>> s_in_data_i;
    sc_signal<sc_bv<1>>              s_in_val_i;
    sc_signal<sc_bv<1>>              s_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> s_out_data_o;
    sc_signal<sc_bv<1>>              s_out_val_o;
    sc_signal<sc_bv<1>>              s_out_ack_i;

    sc_signal<sc_bv<data_width_p+1>> w_in_data_i;
    sc_signal<sc_bv<1>>              w_in_val_i;
    sc_signal<sc_bv<1>>              w_in_ack_o;
    sc_signal<sc_bv<data_width_p+1>> w_out_data_o;
    sc_signal<sc_bv<1>>              w_out_val_o;
    sc_signal<sc_bv<1>>              w_out_ack_i;


     SC_CTOR(SYSTEM):clk_i("clk_i",10,SC_NS){

        router0 = new router<l_ena_p,n_ena_p,e_ena_p,s_ena_p,w_ena_p,flow_mode_p,routing_mode_p,arbitration_mode_p,buffer_mode_p,buffer_depth_p,data_width_p>("router0");

        router0->set_position(x_id_p,y_id_p);
        router0->clk_i(clk_i);
        router0->rst_i(rst_i);
        router0->l_in_data_i(l_in_data_i);
        router0->l_in_val_i(l_in_val_i);
        router0->l_in_ack_o(l_in_ack_o);
        router0->l_out_data_o(l_out_data_o);
        router0->l_out_val_o(l_out_val_o);
        router0->l_out_ack_i(l_out_ack_i);

        router0->n_in_data_i(n_in_data_i);
        router0->n_in_val_i(n_in_val_i);
        router0->n_in_ack_o(n_in_ack_o);
        router0->n_out_data_o(n_out_data_o);
        router0->n_out_val_o(n_out_val_o);
        router0->n_out_ack_i(n_out_ack_i);

        router0->e_in_data_i(e_in_data_i);
        router0->e_in_val_i(e_in_val_i);
        router0->e_in_ack_o(e_in_ack_o);
        router0->e_out_data_o(e_out_data_o);
        router0->e_out_val_o(e_out_val_o);
        router0->e_out_ack_i(e_out_ack_i);

        router0->s_in_data_i(s_in_data_i);
        router0->s_in_val_i(s_in_val_i);
        router0->s_in_ack_o(s_in_ack_o);
        router0->s_out_data_o(s_out_data_o);
        router0->s_out_val_o(s_out_val_o);
        router0->s_out_ack_i(s_out_ack_i);

        router0->w_in_data_i(w_in_data_i);
        router0->w_in_val_i(w_in_val_i);
        router0->w_in_ack_o(w_in_ack_o);
        router0->w_out_data_o(w_out_data_o);
        router0->w_out_val_o(w_out_val_o);
        router0->w_out_ack_i(w_out_ack_i);

        tb = new router_tb<data_width_p>("tb");

        tb->clk_i(clk_i);
        tb->rst_i(rst_i);

        tb->l_in_data_i(l_in_data_i);
        tb->l_in_val_i(l_in_val_i);
        tb->l_in_ack_o(l_in_ack_o);
        tb->l_out_data_o(l_out_data_o);
        tb->l_out_val_o(l_out_val_o);
        tb->l_out_ack_i(l_out_ack_i);

        tb->n_in_data_i(n_in_data_i);
        tb->n_in_val_i(n_in_val_i);
        tb->n_in_ack_o(n_in_ack_o);
        tb->n_out_data_o(n_out_data_o);
        tb->n_out_val_o(n_out_val_o);
        tb->n_out_ack_i(n_out_ack_i);

        tb->e_in_data_i(e_in_data_i);
        tb->e_in_val_i(e_in_val_i);
        tb->e_in_ack_o(e_in_ack_o);
        tb->e_out_data_o(e_out_data_o);
        tb->e_out_val_o(e_out_val_o);
        tb->e_out_ack_i(e_out_ack_i);

        tb->s_in_data_i(s_in_data_i);
        tb->s_in_val_i(s_in_val_i);
        tb->s_in_ack_o(s_in_ack_o);
        tb->s_out_data_o(s_out_data_o);
        tb->s_out_val_o(s_out_val_o);
        tb->s_out_ack_i(s_out_ack_i);

        tb->w_in_data_i(w_in_data_i);
        tb->w_in_val_i(w_in_val_i);
        tb->w_in_ack_o(w_in_ack_o);
        tb->w_out_data_o(w_out_data_o);
        tb->w_out_val_o(w_out_val_o);
        tb->w_out_ack_i(w_out_ack_i);

     }
    ~SYSTEM(){
        delete  router0;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");
    ///sc_start(1500, SC_NS);
    sc_start();

    return 0;

}
