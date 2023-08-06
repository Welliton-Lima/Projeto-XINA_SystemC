#include <systemc.h>

#define data_width_p       8

SC_MODULE(channel_out_tb){

    sc_in<bool> clk_i;
    sc_out<sc_bv<1>> rst_i;

    sc_in<sc_bv<data_width_p+1>> data_o;
    sc_in<sc_bv<1>> val_o;
    sc_out<sc_bv<1>> ack_i;

    sc_out<sc_bv<4>> req_i;
    sc_in<sc_bv<4>> gnt_o;

    sc_out<sc_bv<4>> rok_i;
    sc_in<sc_bv<1>> rd_o;
    sc_out<sc_bv<data_width_p+1>> data3_i, data2_i, data1_i, data0_i;

    void test(){
        data3_i.write("000000000");
        data2_i.write("000000000");
        data1_i.write("000000000");
        data0_i.write("000000000");
        rst_i.write("1");
        wait(10, SC_NS);
        rst_i.write("0");
        wait(10, SC_NS);

        sc_bv<data_width_p+1> pack_n[5] = {"111000111", "000000010", "000000100", "100000000", "000000000"};
        wait(10, SC_NS);
        for(int i=0; i<5; i++){
            rok_i.write("1000");
            req_i.write("0010");
            wait(10, SC_NS);
            data3_i.write(pack_n[i]);
            wait(10, SC_NS);
        }
        rok_i.write("0000");
        req_i.write("0000");
        wait(30, SC_NS);
        sc_stop();
    }

    void ack(){
        while(true){
            ack_i.write("0");
            while (val_o.read() != "1")
            {
                wait(10, SC_NS);
            }
            ack_i.write("1");
            wait(10, SC_NS);
            while (val_o.read() != "0")
            {
                wait(10, SC_NS);
            }
            //wait(10, SC_NS);
        }
    }

    SC_CTOR(channel_out_tb){
        SC_THREAD(test);
        SC_THREAD(ack);
        sensitive << clk_i;

        sc_trace_file *wf = sc_create_vcd_trace_file("channelout_tb_mode1");

        sc_trace(wf, clk_i, "clk_i");
        sc_trace(wf, rst_i, "rst_i");
        sc_trace(wf, data_o, "data_o");
        sc_trace(wf, val_o, "val_o");
        sc_trace(wf, ack_i, "ack_i");
        sc_trace(wf, req_i, "req_i");
        sc_trace(wf, gnt_o, "gnt_o");
        sc_trace(wf, rok_i, "rok_i");
        sc_trace(wf, rd_o, "rd_o");
        sc_trace(wf, data3_i, "data3_i");
        sc_trace(wf, data2_i, "data2_i");
        sc_trace(wf, data1_i, "data1_i");
        sc_trace(wf, data0_i, "data0_i");
    }
};
