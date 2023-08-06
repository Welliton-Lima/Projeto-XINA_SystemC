#ifndef ROUTING_MEALY
#define ROUTING_MEALY

#include <systemc.h>

enum fsm_mealy_state {
    stage0, stage1, stage2, stage3, stage4, stage5, stage6
};

//router identification and network data width
template<unsigned int data_width_p>

SC_MODULE(routing_xy_mealy){
    //Clock and Reset
    unsigned int x_id_p, y_id_p;

    void set_position(int x, int y){
        this->x_id_p = x;
        this->y_id_p = y;
    }
    sc_in<bool> clk_i;
    sc_in<sc_bv<1>> rst_i;

    //frame and data
    sc_in<sc_bv<1>> frame_i;
    sc_in<sc_bv<data_width_p>> data_i;

    //buffer read
    sc_in<sc_bv<1>>rok_i;
    sc_in<sc_bv<1>>rd_i;

    //requests
    sc_out<sc_bv<1>>req_l_o;
    sc_out<sc_bv<1>>req_n_o;
    sc_out<sc_bv<1>>req_e_o;
    sc_out<sc_bv<1>>req_s_o;
    sc_out<sc_bv<1>>req_w_o;

    //signal state finite state machine
    sc_signal<fsm_mealy_state> state;

    //Variables X and Y
    unsigned int x_dst_v;
    unsigned int y_dst_v;

    void routing_xy_logic(){
        //Reset Logic
        if(rst_i.read() == "1"){
            state.write(stage0);
        }
        // Logic
        else if(rst_i.read() != "1" && clk_i.posedge()){

            switch(state){

                case stage0:
                if(frame_i.read() == "1" && rok_i.read() == "1"){
                       y_dst_v = data_i.read().range((data_width_p/2)-1,0).to_uint();
                       x_dst_v = data_i.read().range(data_width_p-1, data_width_p/2).to_uint();

                    if(x_dst_v != x_id_p){
                        if(x_dst_v > x_id_p){
                            req_l_o.write("0");
                            req_n_o.write("0");
                            req_e_o.write("1");
                            req_s_o.write("0");
                            req_w_o.write("0");

                            if(rd_i.read() == "1"){
                                state.write(stage1);
                            }
                            else{
                                state.write(stage0);
                            }
                        }
                        else{
                            req_l_o.write("0");
                            req_n_o.write("0");
                            req_e_o.write("0");
                            req_s_o.write("0");
                            req_w_o.write("1");
                            if(rd_i.read() == "1"){
                                state.write(stage2);
                            }

                            else{
                                state.write(stage0);
                            }
                       }
                    }

                else if(y_dst_v != y_id_p){
                    if(y_dst_v > y_id_p){
                        req_l_o.write("0");
                        req_n_o.write("1");
                        req_e_o.write("0");
                        req_s_o.write("0");
                        req_w_o.write("0");

                        if(rd_i.read() == "1"){
                            state.write(stage3);
                        }

                        else{
                            state.write(stage0);
                        }
                    }
                    else{
                        req_l_o.write("0");
                        req_n_o.write("0");
                        req_e_o.write("0");
                        req_s_o.write("1");
                        req_w_o.write("0");
                        if(rd_i.read() == "1"){
                            state.write(stage4);
                        }

                        else{
                            state.write(stage0);
                        }
                    }
                }
                else{
                    req_l_o.write("1");
                    req_n_o.write("0");
                    req_e_o.write("0");
                    req_s_o.write("0");
                    req_w_o.write("0");

                    if(rd_i.read() == "1"){
                        state.write(stage5);
                    }

                    else{
                        state.write(stage0);
                    }
                }
            }
            else{
                req_l_o.write("0");
                req_n_o.write("0");
                req_e_o.write("0");
                req_s_o.write("0");
                req_w_o.write("0");
                state.write(stage0);
            }
                break;

                //x_dst_v > x_id_p
                case stage1:
                    req_l_o.write("0");
                    req_n_o.write("0");
                    req_e_o.write("1");
                    req_s_o.write("0");
                    req_w_o.write("0");

                    if(frame_i.read() == "1" && rd_i.read() == "1" && rok_i.read() == "1"){
                        state.write(stage6);
                    }
                    else{
                        state.write(stage1);
                    }
                break;

                case stage2:
                    req_l_o.write("0");
                    req_n_o.write("0");
                    req_e_o.write("0");
                    req_s_o.write("0");
                    req_w_o.write("1");
                    if(frame_i.read() == "1" && rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(stage6);
                    }
                    else{
                        state.write(stage2);
                    }
                break;

                //x_dst_v < x_id_p
                case stage3:
                    req_l_o.write("0");
                    req_n_o.write("1");
                    req_e_o.write("0");
                    req_s_o.write("0");
                    req_w_o.write("0");
                    if(frame_i.read() == "1" && rd_i.read()=="1" && rok_i.read()=="1"){
                        state.write(stage6);
                    }
                    else{
                        state.write(stage3);
                    }
                break;

                case stage4:
                    req_l_o.write("0");
                    req_n_o.write("0");
                    req_e_o.write("0");
                    req_s_o.write("1");
                    req_w_o.write("0");
                    if(frame_i.read() == "1" and rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(stage6);
                    }
                    else{
                        state.write(stage4);
                    }
                break;

                //y_dst_v > y_id_p
                case stage5:
                    req_l_o.write("1");
                    req_n_o.write("0");
                    req_e_o.write("0");
                    req_s_o.write("0");
                    req_w_o.write("0");
                    if(frame_i.read() == "1" && rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(stage6);
                    }
                    else{
                        state.write(stage5);
                    }
                break;

                //others
                case stage6:
                    req_l_o.write("0");
                    req_n_o.write("0");
                    req_e_o.write("0");
                    req_s_o.write("0");
                    req_w_o.write("0");
                    state.write(stage0);
                break;

                default:
                    req_l_o.write("0");
                    req_n_o.write("0");
                    req_e_o.write("0");
                    req_s_o.write("0");
                    req_w_o.write("0");

                    state.write(stage0);
                break;
            }
        }

    }
    SC_CTOR(routing_xy_mealy){
        SC_METHOD(routing_xy_logic);
        sensitive << clk_i << rst_i << data_i << rok_i << rd_i << frame_i;
    }
};

#endif
