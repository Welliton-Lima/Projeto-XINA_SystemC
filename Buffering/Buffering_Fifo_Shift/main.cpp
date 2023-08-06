#include <systemc.h>
#include "shift_buffering.h"
#include "fifo_tb.h"

#define WIDTH  8
#define DEPTH  4

SC_MODULE(SYSTEM){
    shift_buffering<WIDTH, DEPTH> *fifo;
    fifo_tb<WIDTH, DEPTH> *tb;

    sc_signal<sc_bv<WIDTH>> w_data_i,w_data_o;
    sc_signal<sc_bv<1>> w_rst, w_rd_i, w_wr_i, w_rok_o, w_wok_o;
    sc_clock clk;

    SC_CTOR(SYSTEM): clk("clk",10,SC_NS){
        fifo = new shift_buffering<WIDTH, DEPTH>("fifo");
        fifo->data_i(w_data_i);
        fifo->data_o(w_data_o);
        fifo->rst_i(w_rst);
        fifo->rd_i(w_rd_i);
        fifo->wr_i(w_wr_i);
        fifo->rok_o(w_rok_o);
        fifo->wok_o(w_wok_o);
        fifo->clk_i(clk);

        tb = new fifo_tb<WIDTH, DEPTH>("tb");
        tb->data_i(w_data_i);
        tb->data_o(w_data_o);
        tb->rst_i(w_rst);
        tb->rd_i(w_rd_i);
        tb->wr_i(w_wr_i);
        tb->rok_o(w_rok_o);
        tb->wok_o(w_wok_o);
        tb->clk_i(clk);
    }
    ~SYSTEM(){
        delete  fifo;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]) {

    top = new SYSTEM("top");

    sc_start();

    return 0;
}
