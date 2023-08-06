#include <systemc.h>

    enum stage_fsm{
      stage0, stage1
    };

//network data width
template<unsigned int data_width_p>
SC_MODULE(flow_out_mealy){

    sc_in<bool> clk_i;
    sc_in<sc_bv<1>> rst_i;

    //link interface
    sc_out<sc_bv<data_width_p>> data_o;
    sc_out<sc_bv<1>> val_o;
    sc_in<sc_bv<1>> ack_i;

    //read from buffer
    sc_in<sc_bv<data_width_p>> data_i;
    sc_in<sc_bv<1>> rok_i;
    sc_out<sc_bv<1>>rd_o;

    sc_signal<stage_fsm> state;

    void flow_out_mealy_logic(){

        if(rst_i.read() == "1"){
            state.write(stage0);
        }
        else if(rst_i.read() != "1" && clk_i.posedge()){
            switch(state){
                case stage0:
                    if (ack_i.read()=="0" && rok_i.read() == "1"){
                        val_o.write("1");
                        rd_o.write("0");
                        state.write(stage1);
                    }
                    else{
                        val_o.write("0");
                        rd_o.write("0");
                        state.write(stage0);
                    }
                 break;

                 case stage1:
                      if (ack_i.read()=="1"){
                          val_o.write("1");
                          rd_o.write("1");
                          state.write(stage0);
                    }
                    else{
                          val_o.write("1");
                          rd_o.write("0");
                        state.write(stage1);
                    }
                break;

                 default:
                    val_o.write("0");
                    rd_o.write("0");
                    state.write(stage0);
                break;
            }

            data_o.write(data_i.read());
        }
    }

    SC_CTOR(flow_out_mealy){
        SC_METHOD(flow_out_mealy_logic);
        sensitive << clk_i << rst_i << ack_i << rok_i << data_i;
    }
};
