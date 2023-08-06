#include <systemc.h>

template<unsigned int data_width_p>
SC_MODULE(xin_tb){

    sc_in<bool> clk_i;
    sc_out<sc_bv<1>> rst_i;
    sc_out<sc_bv<data_width_p+1>> data_i;
    sc_out<sc_bv<1>> val_i;
    sc_in<sc_bv<1>> ack_o;

    sc_in<sc_bv<1>> req_l_o, req_n_o, req_e_o, req_s_o, req_w_o;
    sc_out<sc_bv<4>> gnt_i;

    sc_in<sc_bv<1>> rok_o;
    sc_out<sc_bv<4>> rd_i;
    sc_in<sc_bv<data_width_p+1>> data_o;

    void test(){
        data_i.write("000000000");
        rst_i.write("1");
        wait(10, SC_NS);
        rst_i.write("0");
        wait(10, SC_NS);

        sc_bv<data_width_p> pack_n[5] = {"11111111", "000000010", "000000100", "100000001"};
        wait(10, SC_NS);

        for(int i=0; i<4; i++){
            data_i.write(pack_n[i]);
            wait(10, SC_NS);
            gnt_i.write("0001");
            //wait(10, SC_NS);
            while(rok_o.read() != "0"){
                //rd_i.write("0100");
                wait(10, SC_NS);
            }
        }
        //wait(1, SC_NS);
        data_i.write("000000000");
        gnt_i.write("0000");
        wait(50,SC_NS);
        sc_stop();
    }

    void reset(){
        data_i.write("00000000");
        rst_i.write("1");
        wait(10, SC_NS);
        rst_i.write("0");
        wait(10, SC_NS);
    }
    void ack(){
        val_i.write("0");
        wait(10, SC_NS);
        while(true){
            if(ack_o.read()=="1"){
                val_i.write("0");
                wait(10, SC_NS);
            }else {
                val_i.write("1");
                wait(10,SC_NS);
            }
        }
    }
    void rd(){
        rd_i.write("0000");
        wait(10, SC_NS);
        while(true){
            if(rok_o.read() == "1"){
                rd_i.write("0100");
                wait(10, SC_NS);
            } else {
                rd_i.write("0000");
                wait(10, SC_NS);
            }
        }
    }

    SC_CTOR(xin_tb){
        SC_THREAD(ack);
        //SC_THREAD(reset);
        SC_THREAD(test);
        SC_THREAD(rd);
        sensitive << clk_i << rst_i<< ack_o<<req_l_o<<req_n_o<<req_e_o<<req_s_o<<req_w_o<<rok_o<<data_o;

        sc_trace_file *wf = sc_create_vcd_trace_file("channel_in_mode1");

        sc_trace(wf, clk_i, "clk");
        sc_trace(wf, rst_i, "rst");
        sc_trace(wf, data_i, "data_i");
        sc_trace(wf, val_i, "val_i");
        sc_trace(wf, ack_o, "ack_o");
        sc_trace(wf, req_l_o, "req_l_o");
        sc_trace(wf, req_n_o, "req_n_o");
        sc_trace(wf, req_e_o, "req_e_o");
        sc_trace(wf, req_s_o, "req_s_o");
        sc_trace(wf, req_w_o, "req_w_o");
        sc_trace(wf, gnt_i, "gnt_i");
        sc_trace(wf, rok_o, "rok_o");
        sc_trace(wf, rd_i, "rd_i");
        sc_trace(wf, data_o, "data_o");
    }
};
