#ifndef ROUTING_MOORE
#define ROUTING_MOORE

#include <systemc.h>

enum fsm_state {
    s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10,s11,s12,s13
};

//router identification and network data width
template<unsigned int data_width_p>

SC_MODULE(routing_xy_moore){
    //Clock and Reset
    unsigned int x_id_p,y_id_p;

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
    sc_signal<fsm_state> state;

    //Variables X and Y
    unsigned int x_dst_v;
    unsigned int y_dst_v;

    void routing_xy_logic(){
        //Reset Logic
        if(rst_i.read() == "1"){
            state.write(s0);
        }
        // Logic
        else if(rst_i.read() != "1" && clk_i.posedge()){

            switch(state){

                case s0:
                if(frame_i.read() == "1" && rok_i.read() == "1"){
                       y_dst_v = data_i.read().range((data_width_p/2)-1,0).to_uint();
                       x_dst_v = data_i.read().range(data_width_p-1, data_width_p/2).to_uint();

                    if(x_dst_v != x_id_p){
                        if(x_dst_v > x_id_p){
                            state.write(s1);
                        }
                        else{
                            state.write(s2);
                        }
                    }
                    else if(y_dst_v != y_id_p){
                        if(y_dst_v > y_id_p){
                            state.write(s3);
                        }
                        else{
                            state.write(s4);
                        }
                    }
                    else{
                        state.write(s5);
                    }
                }
                else{
                    state.write(s0);
                }
                break;

                //x_dst_v > x_id_p
                case s1:
                    if(frame_i.read() == "0" && rd_i.read() == "1" && rok_i.read() == "1"){
                        state.write(s9);
                    }
                    else{
                        state.write(s1);
                    }
                break;

                case s9:
                    if(frame_i.read() == "1" && rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(s0);
                    }
                    else{
                        state.write(s9);
                    }
                break;

                //x_dst_v < x_id_p
                case s2:
                    if(frame_i.read() == "0" && rd_i.read()=="1" && rok_i.read()=="1"){
                        state.write(s10);
                    }
                    else{
                        state.write(s2);
                    }
                break;

                case s10:
                    if(frame_i.read() == "1" and rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(s0);
                    }
                    else{
                        state.write(s10);
                    }
                break;

                //y_dst_v > y_id_p
                case s3:
                    if(frame_i.read() == "0" && rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(s11);
                    }
                    else{
                        state.write(s3);
                    }
                break;

                case s11:
                    if(frame_i.read() == "1" && rd_i.read() == "1" && rok_i.read() == "1"){
                        state.write(s0);

                    }
                    else{
                        state.write(s11);
                    }
                break;

                //y_dst_v < y_id_p
                case s4:
                    if(frame_i.read() == "0" && rd_i.read() == "1" && rok_i.read() =="1" ){
                        state.write(s12);
                    }
                    else{
                        state.write(s4);

                    }
                    break;

                case s12:
                    if(frame_i.read() == "1" && rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(s0);
                    }
                    else{
                        state.write(s12);
                    }
                break;

                //x_dst_v = x_id_p and y_dst_v = y_id_p
                case s5:
                    if(frame_i.read() == "0" && rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(s13);
                    }
                    else{
                        state.write(s5);
                    }
                break;

                case s13:
                    if(frame_i.read() == "1" && rd_i.read() == "1" && rok_i.read() == "1" ){
                        state.write(s0);
                    }
                    else{
                        state.write(s13);
                    }
                break;

                //others
                default:
                    state.write(s0);
                break;

            }
        }
        //Local Channel
        if(state.read() == s5 or state.read() == s13 ){
            req_l_o.write("1");
        }
        else{
            req_l_o.write("0");
        }

        //Norh Channel
        if(state.read() == s3 or state.read() == s11){
            req_n_o.write("1");
        }
        else{
            req_n_o.write("0");
        }
        //East Channel
        if(state.read() == s1 or state.read() == s9 ){
            req_e_o.write("1");
        }
        else{
            req_e_o.write("0");
        }
        //South Chanennel
        if(state.read() == s4 or state.read() == s12 ){
            req_s_o.write("1");
        }
        else{
            req_s_o.write("0");
        }
        //West Channel
        if(state.read() == s2 or state.read() == s10 ){
            req_w_o.write("1");
        }
        else{
            req_w_o.write("0");
        }
    }
    SC_CTOR(routing_xy_moore){
        SC_METHOD(routing_xy_logic);
        sensitive << clk_i << rst_i << data_i << rok_i << rd_i << frame_i;
    }
};

#endif
