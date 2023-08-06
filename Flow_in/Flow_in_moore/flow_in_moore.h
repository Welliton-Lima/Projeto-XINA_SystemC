#ifndef LIST_H_
#define LIST_H_

#include <systemc.h>

// enum stage_fsm {
// 	stage0, stage1, stage2
// };

template <unsigned int data_width_p>
SC_MODULE(flow_in_moore){

    sc_in<bool> clk_i;

    sc_in<sc_bv<1>> rst_i, val_i, wok_i;
    sc_out<sc_bv<1>> ack_o, wr_o;

    sc_in<sc_bv<data_width_p>> data_i;
    sc_out<sc_bv<data_width_p>> data_o;

    enum stage_fsm {
        stage0, stage1, stage2
    };

    sc_signal<stage_fsm> state;

    void flow_in_moore_logic(){

        if(rst_i.read() == "1"){
            state.write(stage0);
        }
        else if(rst_i.read() != "1" && clk_i.posedge()){
            switch(state.read()){
                case stage0:
                    wr_o.write("0");
                    ack_o.write("0");

                    if(val_i.read() == "1" and wok_i.read() == "1"){
                        state.write(stage1);
                    } else {
                        state.write(stage0);
                    }
                break;

                case stage1:
                    ack_o.write("1");
                    wr_o.write("1");

                    if(val_i.read() == "0"){
                        state.write(stage0);
                    } else {
                        state.write(stage2);
                    }
                break;

                case stage2:
                    ack_o.write("1");
                    wr_o.write("0");

                if(val_i.read() == "0"){
                    state.write(stage0);
                } else {
                    state.write(stage2);
                }
                break;

                default:
                    wr_o.write("0");
                    ack_o.write("0");

                    state.write(stage0);
                break;
            }
        }
        data_o.write(data_i.read());
    }

    SC_CTOR(flow_in_moore){
        SC_METHOD(flow_in_moore_logic);
        sensitive << clk_i << rst_i << val_i << wok_i << data_i;
    }

};

#endif
