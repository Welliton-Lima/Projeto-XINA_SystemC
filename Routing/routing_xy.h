#ifndef ROUTING
#define ROUTING

#include <systemc.h>
#include "routing_xy_moore.h"
#include "routing_xy_mealy.h"

template<unsigned int MODE,unsigned int WIDTH>
SC_MODULE(routing_xy){
    routing_xy_mealy<WIDTH> *xy_mealy;
    routing_xy_moore<WIDTH> *xy_moore;

    unsigned int X, Y;

    void set_position(int x, int y){
        this->X = x;
        this->Y = y;
    }

    sc_in<bool> clk_i;
    sc_in<sc_bv<1>> rst_i;
    sc_in<sc_bv<1>> frame_i;
    sc_in<sc_bv<1>> rok_i;
    sc_in<sc_bv<1>> rd_i;
    sc_in<sc_bv<WIDTH>> data_i;

    sc_out<sc_bv<1>> req_l_o;
    sc_out<sc_bv<1>> req_n_o;
    sc_out<sc_bv<1>> req_e_o;
    sc_out<sc_bv<1>> req_s_o;
    sc_out<sc_bv<1>> req_w_o;


     SC_CTOR(routing_xy){
         if(MODE == 1){
            xy_mealy = new routing_xy_mealy<WIDTH>("xy_mealy");

            xy_mealy->set_position(X,Y);
            xy_mealy->clk_i(clk_i);
            xy_mealy->rst_i(rst_i);
            xy_mealy->rok_i(rok_i);
            xy_mealy->rd_i(rd_i);
            xy_mealy->data_i(data_i);
            xy_mealy->frame_i(frame_i);
            xy_mealy->req_e_o(req_e_o);
            xy_mealy->req_l_o(req_l_o);
            xy_mealy->req_s_o(req_s_o);
            xy_mealy->req_w_o(req_w_o);
            xy_mealy->req_n_o(req_n_o);
        }
        else{
            xy_moore = new routing_xy_moore<WIDTH>("xy_moore");

            xy_moore->set_position(X,Y);
            xy_moore->clk_i(clk_i);
            xy_moore->rst_i(rst_i);
            xy_moore->rok_i(rok_i);
            xy_moore->rd_i(rd_i);
            xy_moore->data_i(data_i);
            xy_moore->frame_i(frame_i);
            xy_moore->req_e_o(req_e_o);
            xy_moore->req_l_o(req_l_o);
            xy_moore->req_s_o(req_s_o);
            xy_moore->req_w_o(req_w_o);
            xy_moore->req_n_o(req_n_o);
        }

     }

    ~routing_xy(){
        delete  xy_mealy;
        delete  xy_moore;
    }
};

#endif
