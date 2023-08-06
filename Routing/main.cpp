#include <systemc.h>
#include "routing_tb.h"
#include "routing_xy.h"

#define WIDTH 9
#define X 1
#define Y 1
#define MODE 0

SC_MODULE(SYSTEM){
    routing_xy<MODE, WIDTH> *routing0;
    routing_tb<WIDTH> *tb;

    sc_clock clk_w;
    sc_signal<sc_bv<1>> rst_w;
    sc_signal<sc_bv<1>> frame_w;
    sc_signal<sc_bv<WIDTH>> data_w;
    sc_signal<sc_bv<1>> rok_w;
    sc_signal<sc_bv<1>> rd_w;
    sc_signal<sc_bv<1>> req_l_o;
    sc_signal<sc_bv<1>> req_n_o;
    sc_signal<sc_bv<1>> req_e_o;
    sc_signal<sc_bv<1>> req_s_o;
    sc_signal<sc_bv<1>> req_w_o;


     SC_CTOR(SYSTEM):clk_w("clk_w",10,SC_NS){
            routing0 = new routing_xy<MODE,WIDTH>("routing0");

            routing0->set_position(X,Y);
            routing0->clk_i(clk_w);
            routing0->rst_i(rst_w);
            routing0->rok_i(rok_w);
            routing0->rd_i(rd_w);
            routing0->data_i(data_w);
            routing0->frame_i(frame_w);
            routing0->req_e_o(req_e_o);
            routing0->req_l_o(req_l_o);
            routing0->req_s_o(req_s_o);
            routing0->req_w_o(req_w_o);
            routing0->req_n_o(req_n_o);


            tb = new routing_tb<WIDTH>("tb");
            tb->clk_i(clk_w);
            tb->rst_i(rst_w);
            tb->rok_i(rok_w);
            tb->rd_i(rd_w);
            tb->data_i(data_w);
            tb->frame_i(frame_w);
            tb->req_e_o(req_e_o);
            tb->req_l_o(req_l_o);
            tb->req_s_o(req_s_o);
            tb->req_w_o(req_w_o);
            tb->req_n_o(req_n_o);

     }

    ~SYSTEM(){
        delete  routing0;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");
    //sc_start(150, SC_NS);]
    sc_start();
    
    return 0;

}
