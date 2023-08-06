#include <systemc.h>


template<unsigned int data_width_p>
SC_MODULE(router_tb){

    sc_in<bool>      clk_i;
    sc_out<sc_bv<1>> rst_i;

    // local channel interface
    sc_out<sc_bv<data_width_p+1>>l_in_data_i;
    sc_out<sc_bv<1>>             l_in_val_i;
    sc_in<sc_bv<1>>              l_in_ack_o;
    sc_in<sc_bv<data_width_p+1>> l_out_data_o;
    sc_in<sc_bv<1>>              l_out_val_o;
    sc_out<sc_bv<1>>             l_out_ack_i;

    // north channel interface
    sc_out<sc_bv<data_width_p+1>> n_in_data_i;
    sc_out<sc_bv<1>>              n_in_val_i;
    sc_in<sc_bv<1>>               n_in_ack_o;
    sc_in<sc_bv<data_width_p+1>>  n_out_data_o;
    sc_in<sc_bv<1>>               n_out_val_o;
    sc_out<sc_bv<1>>              n_out_ack_i;

    // east channel interface
    sc_out<sc_bv<data_width_p+1>> e_in_data_i;
    sc_out<sc_bv<1>>              e_in_val_i;
    sc_in<sc_bv<1>>               e_in_ack_o;
    sc_in<sc_bv<data_width_p+1>>  e_out_data_o;
    sc_in<sc_bv<1>>               e_out_val_o;
    sc_out<sc_bv<1>>              e_out_ack_i;

    // south channel interface
    sc_out<sc_bv<data_width_p+1>> s_in_data_i;
    sc_out<sc_bv<1>>              s_in_val_i;
    sc_in<sc_bv<1>>               s_in_ack_o;
    sc_in<sc_bv<data_width_p+1>>  s_out_data_o;
    sc_in<sc_bv<1>>               s_out_val_o;
    sc_out<sc_bv<1>>              s_out_ack_i;

    // west port interface
    sc_out<sc_bv<data_width_p+1>>w_in_data_i;
    sc_out<sc_bv<1>>             w_in_val_i;
    sc_in<sc_bv<1>>              w_in_ack_o;
    sc_in<sc_bv<data_width_p+1>> w_out_data_o;
    sc_in<sc_bv<1>>              w_out_val_o;
    sc_out<sc_bv<1>>             w_out_ack_i;

    void rst(){
        rst_i.write("1");
        wait(10, SC_NS);
        rst_i.write("0");
        wait(10, SC_NS);
    }

    void in(){
        rst_i.write("1");
        wait(10, SC_NS);
        rst_i.write("0");
        wait(10, SC_NS);

        cout<<"A: "<<endl;
        sc_bv<data_width_p+1> pack_n[6]  = {"111111111", "000000101", "000010101", "001000101", "000010000", "100000001"};
        sc_bv<data_width_p+1> pack_n2[6] = {"100000001", "000000111", "000100101", "000001101", "000010000", "100000000"};
        l_in_val_i.write("0");
        e_in_val_i.write("0");
            wait(10, SC_NS);
        for(int i=0; i<6; i++){
            cout<<"B: "<<endl;
            l_in_val_i.write("0");
            l_in_data_i.write(pack_n[i]);
            wait(10, SC_NS);
            l_in_val_i.write("1");
            while(l_in_ack_o.read() != "1"){
                wait(10, SC_NS);
                     cout<<"C: "<<endl;
            }
            l_in_val_i.write("0");
            while(l_in_ack_o.read() != "0"){
                wait(10, SC_NS);
                     cout<<"D: "<<endl;
            }
        }

        l_in_data_i.write("00000000");
        l_in_val_i.write("0");
        e_in_val_i.write("0");
            wait(10, SC_NS);
        for(int i=0; i<6; i++){
            cout<<"F: "<<endl;
            e_in_val_i.write("0");
            e_in_data_i.write(pack_n2[i]);
            wait(10, SC_NS);
            e_in_val_i.write("1");
            while(e_in_ack_o.read() != "1"){
                wait(10, SC_NS);
                cout<<"F: "<<endl;
            }
            e_in_val_i.write("0");
            while(e_in_ack_o.read() != "0"){
                wait(10, SC_NS);
                cout<<"G: "<<endl;
            }
        }
        //cout<<"B: "<<endl;
        e_in_val_i.write("0");
        e_in_data_i.write("00000000");
        wait(400, SC_NS);
        sc_stop();
    }

    void e_o(){
        while(true){
            e_out_ack_i.write("0");
            wait(10, SC_NS);
            while (e_out_val_o.read() != "1")
            {
                wait(10, SC_NS);
            }
            e_out_ack_i.write("1");
            wait(10, SC_NS);
            while (e_out_val_o.read() != "0")
            {
                wait(10, SC_NS);
            }
        }
    }

    void s_o(){
        while(true){
            s_out_ack_i.write("0");
            while (s_out_val_o.read() != "1")
            {
                wait(10, SC_NS);
            }
            s_out_ack_i.write("1");
            wait(10,SC_NS);
            while (s_out_val_o.read() != "0")
            {
                wait(10, SC_NS);
            }
        }
    }

    void n_o(){
        while(true){
            n_out_ack_i.write("0");
            while (n_out_val_o.read() != "1")
            {
                wait(10, SC_NS);
            }
            n_out_ack_i.write("1");
            wait(10, SC_NS);
            while (n_out_val_o.read() != "0")
            {
                wait(10, SC_NS);
            }
        }
    }

    void w_o(){
        while(true){
            w_out_ack_i.write("0");
            while (w_out_val_o.read() != "1")
            {
                wait(10, SC_NS);
            }
            w_out_ack_i.write("1");
            wait(10, SC_NS);
            while (w_out_val_o.read() != "0")
            {
                wait(10, SC_NS);
            }
        }
    }

    void l_o(){
        while(true){
            l_out_ack_i.write("0");
            while (l_out_val_o.read() != "1")
            {
                wait(10, SC_NS);
            }
            l_out_ack_i.write("1");
            wait(10, SC_NS);
            while (l_out_val_o.read() != "0")
            {
                wait(10, SC_NS);
            }
        }
    }

    SC_CTOR(router_tb){

        SC_THREAD(n_o);
        SC_THREAD(e_o);
        SC_THREAD(s_o);
        SC_THREAD(w_o);
        SC_THREAD(l_o);
        SC_THREAD(in);
        //SC_THREAD(rst);

        sensitive << clk_i<<rst_i << l_in_ack_o<< l_out_data_o<<l_out_val_o<< n_in_ack_o<< n_out_data_o<<n_out_val_o<<e_in_ack_o<< e_out_data_o<<e_out_val_o<< s_in_ack_o<< s_out_data_o<<s_out_val_o<<w_in_ack_o<< w_out_data_o<<w_out_val_o;

        sc_trace_file *wf = sc_create_vcd_trace_file("router_tb_mode_1");

        sc_trace(wf, clk_i, "clk");
        sc_trace(wf, rst_i, "rst");

        sc_trace(wf, l_in_data_i, "l_in_data_i");
        sc_trace(wf, l_in_val_i,  "l_in_val_i");
        sc_trace(wf, l_in_ack_o,  "l_in_ack_o");
        sc_trace(wf, l_out_data_o,"l_out_data_o");
        sc_trace(wf, l_out_val_o, "l_out_val_o");
        sc_trace(wf, l_out_ack_i, "l_out_ack_i");

        sc_trace(wf, n_in_data_i, "n_in_data_i");
        sc_trace(wf, n_in_val_i,  "n_in_val_i");
        sc_trace(wf, n_in_ack_o,  "n_in_ack_o");
        sc_trace(wf, n_out_data_o,"n_out_data_o");
        sc_trace(wf, n_out_val_o, "n_out_val_o");
        sc_trace(wf, n_out_ack_i, "n_out_ack_i");

        sc_trace(wf, e_in_data_i, "e_in_data_i");
        sc_trace(wf, e_in_val_i,  "e_in_val_i");
        sc_trace(wf, e_in_ack_o,  "e_in_ack_o");
        sc_trace(wf, e_out_data_o,"e_out_data_o");
        sc_trace(wf, e_out_val_o, "e_out_val_o");
        sc_trace(wf, e_out_ack_i, "e_out_ack_i");

        sc_trace(wf, s_in_data_i, "s_in_data_i");
        sc_trace(wf, s_in_val_i,  "s_in_val_i");
        sc_trace(wf, s_in_ack_o,  "s_in_ack_o");
        sc_trace(wf, s_out_data_o,"s_out_data_o");
        sc_trace(wf, s_out_val_o, "s_out_val_o");
        sc_trace(wf, s_out_ack_i, "s_out_ack_i");

        sc_trace(wf, w_in_data_i, "w_in_data_i");
        sc_trace(wf, w_in_val_i,  "w_in_val_i");
        sc_trace(wf, w_in_ack_o,  "w_in_ack_o");
        sc_trace(wf, w_out_data_o,"w_out_data_o");
        sc_trace(wf, w_out_val_o, "w_out_val_o");
        sc_trace(wf, w_out_ack_i, "w_out_ack_i");
     }
};
