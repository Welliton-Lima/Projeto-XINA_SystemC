#include <systemc.h>
#include "switch_tb.h"
#include "switch.h"

#define WIDTH 9

SC_MODULE(SYSTEM){
    switch_module<WIDTH> *sw;
    switch_tb<WIDTH> *tb;

    sc_signal<sc_bv<4>> w_sel_i;

    sc_signal<sc_bv<WIDTH>> w_data3_i;
    sc_signal<sc_bv<WIDTH>> w_data2_i;
    sc_signal<sc_bv<WIDTH>> w_data1_i;
    sc_signal<sc_bv<WIDTH>> w_data0_i;
    sc_signal<sc_bv<WIDTH>> w_data_o;


     SC_CTOR(SYSTEM){
            sw = new switch_module<WIDTH>("sw");
            sw->data0_i(w_data0_i);
            sw->data1_i(w_data1_i);
            sw->data2_i(w_data2_i);
            sw->data3_i(w_data3_i);
            sw->sel_i(w_sel_i);
            sw->data_o(w_data_o);


            tb = new switch_tb<WIDTH>("tb");
            tb->data0_i(w_data0_i);
            tb->data1_i(w_data1_i);
            tb->data2_i(w_data2_i);
            tb->data3_i(w_data3_i);
            tb->sel_i(w_sel_i);
            tb->data_o(w_data_o);

     }
    ~SYSTEM(){
        delete  sw;
        delete  tb;
    }
};

SYSTEM *top = NULL;

int sc_main(int argc, char* argv[]){

    top = new SYSTEM("top");
    sc_start(150, SC_NS);
    
    return 0;

}
