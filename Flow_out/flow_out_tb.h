#include "systemc.h"

template<unsigned int data_width_p>
SC_MODULE(flow_out_tb){

    sc_in<bool> clk_i;
    sc_out<sc_bv<1>> rst_i, ack_i, rok_i;
    sc_in<sc_bv<1>> val_o, rd_o;
    sc_out<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<data_width_p>> data_o;

    void logic(){
        data_i.write("00000000");
        rst_i.write("1");
        wait(10, SC_NS);
        rst_i.write("0");
        wait(10, SC_NS);

        sc_bv<data_width_p> words[10] = {"00000001","00000011","00000111","00001111","00011111","00111111","01111111","11111111","11111110","11111100"};
        for(int i=0; i<10; i++){
            //cout<<"i: "<<i <<"Data o: "<<data_o.read()<<endl;
            wait(10, SC_NS);
            data_i.write(words[i]);
            rok_i.write("1");
            wait(10, SC_NS);
            rok_i.write("0");
    }
    //cout<<"Data o: "<<data_o.read()<<endl;
    sc_stop();
    }

    void ack(){
        while(true){
            ack_i.write("0");
            while(val_o.read()!="1"){
                wait(10,SC_NS);
            }
            wait(10, SC_NS);
            ack_i.write("1");
            while(val_o.read()!="0"){
                wait(10,SC_NS);
            }
            wait(10,SC_NS);
        }
    }

    SC_CTOR(flow_out_tb){
        sensitive << clk_i;
        SC_THREAD(logic);
        SC_THREAD(ack);

        sc_trace_file *wf = sc_create_vcd_trace_file("flow_out_tb");

        sc_trace(wf, data_i, "data_i");
        sc_trace(wf, data_o, "data_o");

        sc_trace(wf, clk_i, "clk_i");
        sc_trace(wf, rst_i, "rst_i");
        sc_trace(wf, val_o, "val_o");
        sc_trace(wf, rok_i, "rok_i");
        sc_trace(wf, ack_i, "ack_i");
        sc_trace(wf, rd_o, "rd_o");
    }
};
