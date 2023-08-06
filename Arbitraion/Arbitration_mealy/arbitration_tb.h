#include <systemc.h>

SC_MODULE(arbitration_tb){

    sc_in_clk clk_w;
    sc_out<sc_bv<1>> rst_w;
    sc_out<sc_bv<4>> req_w;
    sc_in<sc_bv<4>> gnt_w;

    void logic(){

        rst_w.write("1");
        wait(10, SC_NS);
        rst_w.write("0");
        wait(10, SC_NS);

        sc_bv<4> count[8] = {"0000", "0011", "0100", "0111", "1010", "1101", "1111", "0101"};
        for(int i=0; i<8; i++){
            req_w.write(count[i]);
            cout<<"Data i: "<<req_w.read()<<endl;
            cout<<"Data o: "<<gnt_w.read()<<endl;
            wait(10,SC_NS);
        }
        wait(10,SC_NS);
        cout<<"Data i: "<<req_w.read()<<endl;
        cout<<"Data o: "<<gnt_w.read()<<endl;
        sc_stop();
    }
    void reset(){
        rst_w.write("1");
        wait(1, SC_NS);
        rst_w.write("0");
        wait(1, SC_NS);
    }


    SC_CTOR(arbitration_tb){
        sensitive<< clk_w;
        SC_THREAD(logic);
        //SC_THREAD(reset);


    }
};
