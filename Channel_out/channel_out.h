#ifndef CHANNEL_OUT
#define CHANNEL_OUT

#include <systemc.h>
#include "../Flow_out/flow_out.h"
#include "../Switch/switch.h"
#include "../Arbitraion/arbitration.h"

template<unsigned int c_ena_p, unsigned int flow_mode_p,unsigned int arbitration_mode_p,unsigned int data_width_p>
SC_MODULE(channel_out){
    sc_in<bool> clk_i;
    sc_in<sc_bv<1>> rst_i;

    //Link inerface
    sc_out<sc_bv<data_width_p+1>> data_o;
    sc_out<sc_bv<1>> val_o;
    sc_in<sc_bv<1>> ack_i;

    //Requeriments and grants
    sc_in<sc_bv<4>> req_i;
    sc_out<sc_bv<4>> gnt_o;


    //Intra router signals
    sc_in<sc_bv<4>> rok_i;
    sc_out<sc_bv<1>>  rd_o;

    sc_in<sc_bv<data_width_p+1>> data3_i;
    sc_in<sc_bv<data_width_p+1>> data2_i;
    sc_in<sc_bv<data_width_p+1>> data1_i;
    sc_in<sc_bv<data_width_p+1>> data0_i;

    sc_signal<sc_bv<1>> rok_w;
    sc_signal<sc_bv<data_width_p+1>> data_w;
    sc_signal<sc_bv<4>> gnt_w;

    sc_signal<sc_bv<1>> rok0_w, rok1_w, rok2_w, rok3_w;

    flow_out<flow_mode_p,data_width_p+1> * flow_out0;
    switch_module<data_width_p+1> *data_switch;
    switch_module<1> *rok_switch;
    arbitration<arbitration_mode_p> *arbitration0;

    void logic(){
        gnt_o.write(gnt_w.read());

        rok0_w.write(rok_i.read().get_bit(0));
        rok1_w.write(rok_i.read().get_bit(1));
        rok2_w.write(rok_i.read().get_bit(2));
        rok3_w.write(rok_i.read().get_bit(3));
        //cout << "rok: " << rok_i.read() << endl << "gnt: " << gnt_w.read() << endl;
    }


    SC_CTOR(channel_out){

        SC_METHOD(logic);
        sensitive << clk_i << rst_i << ack_i << req_i << rok_i << data3_i << data2_i << data1_i << data0_i;

        if(c_ena_p == 0){
            data_o.write(0);
            val_o.write("0");
            gnt_o.write(0);
            rd_o.write("0");
        }
        else{
            flow_out0 = new flow_out<flow_mode_p,data_width_p+1>("flow_out0");
            data_switch = new switch_module<data_width_p+1>("data_switch");
            rok_switch = new switch_module<1>("rok_switch");
            arbitration0 = new arbitration<arbitration_mode_p>("arbitration0");

            flow_out0->clk_i(clk_i);
            flow_out0->rst_i(rst_i);
            flow_out0->data_o(data_o);
            flow_out0->val_o(val_o);
            flow_out0->ack_i(ack_i);
            flow_out0->data_i(data_w);
            flow_out0->rok_i(rok_w);
            flow_out0->rd_o(rd_o);

            arbitration0->clk_i(clk_i);
            arbitration0->rst_i(rst_i);
            arbitration0->req_i(req_i);
            arbitration0->gnt_o(gnt_w);

            data_switch->sel_i(gnt_w);
            data_switch->data3_i(data3_i);
            data_switch->data2_i(data2_i);
            data_switch->data1_i(data1_i);
            data_switch->data0_i(data0_i);
            data_switch->data_o(data_w);

            rok_switch->sel_i(gnt_w);
            rok_switch->data3_i(rok3_w);
            rok_switch->data2_i(rok2_w);
            rok_switch->data1_i(rok1_w);
            rok_switch->data0_i(rok0_w);
            rok_switch->data_o(rok_w);
        }
    }
    ~channel_out(){
        delete flow_out0;
        delete rok_switch;
        delete data_switch;
        delete arbitration0;
    }
};
#endif
