#include <systemc.h>

//template<unsigned int mode_p>

SC_MODULE(arbitration_rr_moore){
    sc_in<bool> clk_i;
    sc_in<sc_bv<1>> rst_i;

    //request and grants
    sc_in<sc_bv<4>>req_i;
    sc_out<sc_bv<4>>gnt_o;

    enum fsm_state{
        stage0,stage1,stage2,stage3,stage4,stage5,stage6,stage7
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
                        state.write(stage1);
                    }
                    else if(req_i.read()[2] == "1"){
                        state.write(stage3);
                    }
                    else if(req_i.read()[1]== "1"){
                        state.write(stage5);
                    }
                    else if(req_i.read()[0]== "1"){
                        state.write(stage7);
                    }
                    else{
                         state.write(stage0);
                    }
                break;

                case stage1:
                    if(req_i.read()[3]== "1"){
                        state.write(stage1);
                    }
                    else if(req_i.read()[2] == "1"){
                        state.write(stage3);
                    }
                    else if(req_i.read()[1]== "1"){
                        state.write(stage5);
                    }
                    else if(req_i.read()[0]== "1"){
                        state.write(stage7);
                    }
                    else{
                         state.write(stage2);
                    }
                break;

                case stage2:
                    if(req_i.read()[3]== "1"){
                        state.write(stage1);
                    }
                    else if(req_i.read()[2] == "1"){
                        state.write(stage3);
                    }
                    else if(req_i.read()[1]== "1"){
                        state.write(stage5);
                    }
                    else if(req_i.read()[0]== "1"){
                        state.write(stage7);
                    }
                    else{
                         state.write(stage2);
                    }
                break;

                case stage3:
                    if(req_i.read()[2] == "1"){
                        state.write(stage3);
                    }
                    else if(req_i.read()[1]== "1"){
                        state.write(stage5);
                    }
                    else if(req_i.read()[0]== "1"){
                        state.write(stage7);
                    }
                    else if(req_i.read()[3]== "1"){
                        state.write(stage1);
                    }
                    else{
                         state.write(stage4);
                    }
                break;

                case stage4:

                    if(req_i.read()[1]== "1"){
                        state.write(stage5);
                    }
                    else if(req_i.read()[0]== "1"){
                        state.write(stage7);
                    }
                    else if(req_i.read()[3]== "1"){
                        state.write(stage1);
                    }
                   else if(req_i.read()[2] == "1"){
                        state.write(stage3);
                    }
                    else{
                         state.write(stage4);
                    }
                break;

                case stage5:
                    if(req_i.read()[1]== "1"){
                        state.write(stage5);
                    }
                    else if(req_i.read()[0]== "1"){
                        state.write(stage7);
                    }
                    else if(req_i.read()[3]== "1"){
                        state.write(stage1);
                    }
                   else if(req_i.read()[2] == "1"){
                        state.write(stage3);
                    }
                    else{
                         state.write(stage6);
                    }
                break;

                case stage6:
                    if(req_i.read()[0]== "1"){
                        state.write(stage7);
                    }
                    else if(req_i.read()[3]== "1"){
                        state.write(stage1);
                    }
                   else if(req_i.read()[2] == "1"){
                        state.write(stage3);
                    }
                   else if(req_i.read()[1]== "1"){
                        state.write(stage5);
                    }
                    else{
                         state.write(stage6);
                    }
                break;

                case stage7:
                    if(req_i.read()[0]== "1"){
                        state.write(stage7);
                    }
                    else if(req_i.read()[3]== "1"){
                        state.write(stage1);
                    }
                   else if(req_i.read()[2] == "1"){
                        state.write(stage3);
                    }
                   else if(req_i.read()[1]== "1"){
                        state.write(stage5);
                    }
                    else{
                         state.write(stage0);
                    }
                break;

                default:
                    state.write(stage0);
                break;
            }
        }

        if(state.read() == stage1){
            gnt_w.write("1000");
        }
        else if(state.read() == stage3){
            gnt_w.write("0100");
        }
       else if(state.read() == stage5){
            gnt_w.write("0010");
        }
       else if(state.read() == stage7){
            gnt_w.write("0001");
        }
        else{
            gnt_w.write(0);
        }
        //cout<<"\n\nStage: "<<state.read()<<" gnt_w "<<gnt_w.read()<<endl;
        gnt_o.write(gnt_w.read() & req_i.read());
    }
    SC_CTOR(arbitration_rr_moore){
        SC_METHOD(arbitration_logic);
        sensitive << clk_i << rst_i << req_i;
    }

};
