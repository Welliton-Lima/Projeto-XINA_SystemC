#include <systemc.h>

SC_MODULE(arbitration_rr_mealy){
    sc_in<bool> clk_i;
    sc_in<sc_bv<1>> rst_i;

    //request and grants
    sc_in<sc_bv<4>>req_i;
    sc_out<sc_bv<4>>gnt_o;

    enum fsm_state{
        stage0,stage1,stage2,stage3
    };
    sc_signal<fsm_state> state;
    sc_signal<sc_bv<4>>gnt_w;

    void arbitration_logic(){

        if(rst_i.read() == "1"){
            state.write(stage0);
        }
        else if(rst_i.read() != "1" && clk_i.posedge()){
            switch(state){
                case stage0:
                    if(req_i.read()[3]== "1"){
                        state.write(stage0);
                        gnt_o.write("1000");
                    }
                    else if(req_i.read()[2] == "1"){
                        gnt_o.write("0100");
                        state.write(stage1);
                    }
                    else if(req_i.read()[1]== "1"){
                        gnt_o.write("0010");
                        state.write(stage2);
                    }
                    else if(req_i.read()[0]== "1"){
                        gnt_o.write("0001");
                        state.write(stage3);
                    }
                    else{
                         gnt_o.write("0000");
                         state.write(stage0);
                    }
                break;

                case stage1:

                    if(req_i.read()[2] == "1"){
                        gnt_o.write("0100");
                        state.write(stage1);
                    }
                    else if(req_i.read()[1]== "1"){
                        gnt_o.write("0010");
                        state.write(stage2);
                    }
                    else if(req_i.read()[0]== "1"){
                        gnt_o.write("0001");
                        state.write(stage3);
                    }
                    else if(req_i.read()[3]== "1"){
                        gnt_o.write("1000");
                        state.write(stage0);
                    }
                    else{
                         gnt_o.write("0000");
                         state.write(stage1);
                    }
                break;

                case stage2:
                    if(req_i.read()[1]== "1"){
                        gnt_o.write("0010");
                        state.write(stage2);
                    }
                    else if(req_i.read()[0]== "1"){
                       gnt_o.write("0001");
                        state.write(stage3);
                    }
                    else if(req_i.read()[3]== "1"){
                        gnt_o.write("1000");
                        state.write(stage0);
                    }
                    else if(req_i.read()[2] == "1"){
                        gnt_o.write("0100");
                        state.write(stage1);
                    }
                    else{
                         gnt_o.write("0000");
                         state.write(stage2);
                    }
                break;

                case stage3:

                    if(req_i.read()[0]== "1"){
                        gnt_o.write("0001");
                        state.write(stage3);
                    }
                    else if(req_i.read()[3]== "1"){
                       gnt_o.write("1000");
                        state.write(stage0);
                    }
                    else if(req_i.read()[2] == "1"){
                       gnt_o.write("0100");
                        state.write(stage1);
                    }
                    else if(req_i.read()[1]== "1"){
                        gnt_o.write("0010");
                        state.write(stage2);
                    }
                    else{
                        gnt_o.write("0000");
                        state.write(stage3);
                    }
                break;

                default:
                    gnt_o.write("0000");
                    state.write(stage0);;
                break;
            }
        }
        //cout<<"\n\nStage: "<<state.read()<<" gnt_o: "<<gnt_o.read()<<endl;
    }
    SC_CTOR(arbitration_rr_mealy){
        SC_METHOD(arbitration_logic);
        sensitive << clk_i << rst_i << req_i;
    }

};
