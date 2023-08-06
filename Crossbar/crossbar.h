#include <systemc.h>

SC_MODULE(crossbar){

    //Local channel requests --------------------------

    //inputs
    sc_in<sc_bv<1>>l_req_n_i;
    sc_in<sc_bv<1>>l_req_e_i;
    sc_in<sc_bv<1>>l_req_s_i;
    sc_in<sc_bv<1>>l_req_w_i;

    //outputs
    sc_out<sc_bv<1>>l_req_n_o;
    sc_out<sc_bv<1>>l_req_e_o;
    sc_out<sc_bv<1>>l_req_s_o;
    sc_out<sc_bv<1>>l_req_w_o;

    //North channel requests --------------------------

    //inputs
    sc_in<sc_bv<1>>n_req_l_i;
    sc_in<sc_bv<1>>n_req_e_i;
    sc_in<sc_bv<1>>n_req_s_i;
    sc_in<sc_bv<1>>n_req_w_i;

    //outputs
    sc_out<sc_bv<1>>n_req_l_o;
    sc_out<sc_bv<1>>n_req_e_o;
    sc_out<sc_bv<1>>n_req_s_o;
    sc_out<sc_bv<1>>n_req_w_o;


    //East channel requests --------------------------

    //inputs
    sc_in<sc_bv<1>>e_req_l_i;
    sc_in<sc_bv<1>>e_req_n_i;
    sc_in<sc_bv<1>>e_req_s_i;
    sc_in<sc_bv<1>>e_req_w_i;

    //outputs
    sc_out<sc_bv<1>>e_req_l_o;
    sc_out<sc_bv<1>>e_req_n_o;
    sc_out<sc_bv<1>>e_req_s_o;
    sc_out<sc_bv<1>>e_req_w_o;

    //South channel requests --------------------------

    //inputs
    sc_in<sc_bv<1>>s_req_l_i;
    sc_in<sc_bv<1>>s_req_n_i;
    sc_in<sc_bv<1>>s_req_e_i;
    sc_in<sc_bv<1>>s_req_w_i;

    //outputs
    sc_out<sc_bv<1>>s_req_l_o;
    sc_out<sc_bv<1>>s_req_n_o;
    sc_out<sc_bv<1>>s_req_e_o;
    sc_out<sc_bv<1>>s_req_w_o;

    //West channel requests --------------------------
    //inputs
    sc_in<sc_bv<1>>w_req_l_i;
    sc_in<sc_bv<1>>w_req_n_i;
    sc_in<sc_bv<1>>w_req_e_i;
    sc_in<sc_bv<1>>w_req_s_i;

    //outputs
    sc_out<sc_bv<1>>w_req_l_o;
    sc_out<sc_bv<1>>w_req_n_o;
    sc_out<sc_bv<1>>w_req_e_o;
    sc_out<sc_bv<1>>w_req_s_o;

    /// Local chanel grants --------------------------

    //inputs
    sc_in<sc_bv<1>>l_gnt_n_i;
    sc_in<sc_bv<1>>l_gnt_e_i;
    sc_in<sc_bv<1>>l_gnt_s_i;
    sc_in<sc_bv<1>>l_gnt_w_i;

    //outputs
    sc_out<sc_bv<1>>l_gnt_n_o;
    sc_out<sc_bv<1>>l_gnt_e_o;
    sc_out<sc_bv<1>>l_gnt_s_o;
    sc_out<sc_bv<1>>l_gnt_w_o;

     /// North chanel grants --------------------------

    //inputs
    sc_in<sc_bv<1>>n_gnt_l_i;
    sc_in<sc_bv<1>>n_gnt_e_i;
    sc_in<sc_bv<1>>n_gnt_s_i;
    sc_in<sc_bv<1>>n_gnt_w_i;

    //outputs
    sc_out<sc_bv<1>>n_gnt_l_o;
    sc_out<sc_bv<1>>n_gnt_e_o;
    sc_out<sc_bv<1>>n_gnt_s_o;
    sc_out<sc_bv<1>>n_gnt_w_o;

    /// East chanel grants --------------------------

    //inputs
    sc_in<sc_bv<1>>e_gnt_l_i;
    sc_in<sc_bv<1>>e_gnt_n_i;
    sc_in<sc_bv<1>>e_gnt_s_i;
    sc_in<sc_bv<1>>e_gnt_w_i;

    //outputs
    sc_out<sc_bv<1>>e_gnt_l_o;
    sc_out<sc_bv<1>>e_gnt_n_o;
    sc_out<sc_bv<1>>e_gnt_s_o;
    sc_out<sc_bv<1>>e_gnt_w_o;

   /// South chanel grants --------------------------

    //inputs
    sc_in<sc_bv<1>>s_gnt_l_i;
    sc_in<sc_bv<1>>s_gnt_n_i;
    sc_in<sc_bv<1>>s_gnt_e_i;
    sc_in<sc_bv<1>>s_gnt_w_i;

    //outputs
    sc_out<sc_bv<1>>s_gnt_l_o;
    sc_out<sc_bv<1>>s_gnt_n_o;
    sc_out<sc_bv<1>>s_gnt_e_o;
    sc_out<sc_bv<1>>s_gnt_w_o;

   /// West chanel grants --------------------------

    //inputs
    sc_in<sc_bv<1>>w_gnt_l_i;
    sc_in<sc_bv<1>>w_gnt_n_i;
    sc_in<sc_bv<1>>w_gnt_e_i;
    sc_in<sc_bv<1>>w_gnt_s_i;

    //outputs
    sc_out<sc_bv<1>>w_gnt_l_o;
    sc_out<sc_bv<1>>w_gnt_n_o;
    sc_out<sc_bv<1>>w_gnt_e_o;
    sc_out<sc_bv<1>>w_gnt_s_o;

    void connections(){
        //Requests --------------------------------

        //Local chanel connections
        l_req_n_o.write(l_req_n_i.read());
        l_req_e_o.write(l_req_e_i.read());
        l_req_s_o.write(l_req_s_i.read());
        l_req_w_o.write(l_req_w_i.read());

        //North chanel connections
        n_req_l_o.write(n_req_l_i.read());
        n_req_e_o.write("0");
        n_req_s_o.write(n_req_s_i.read());
        n_req_w_o.write("0");

        //East chanel connections
        e_req_l_o.write(e_req_l_i.read());
        e_req_n_o.write(e_req_n_i.read());
        e_req_s_o.write(e_req_s_i.read());
        e_req_w_o.write(e_req_w_i.read());

        //South chanel connections
        s_req_l_o.write(s_req_l_i.read());
        s_req_n_o.write(s_req_n_i.read());
        s_req_e_o.write("0");
        s_req_w_o.write("0");

        //West chanel connections
        w_req_l_o.write(w_req_l_i.read());
        w_req_n_o.write(w_req_n_i.read());
        w_req_e_o.write(w_req_e_i.read());
        w_req_s_o.write(w_req_s_i.read());

        //Grants ---------------------------------

        // Local channel connections
        l_gnt_n_o.write(l_gnt_n_i.read());
        l_gnt_e_o.write(l_gnt_e_i.read());
        l_gnt_s_o.write(l_gnt_s_i.read());
        l_gnt_w_o.write(l_gnt_w_i.read());

        //North channel connections
        n_gnt_l_o.write(n_gnt_l_i.read());
        n_gnt_e_o.write(n_gnt_e_i.read());
        n_gnt_s_o.write(n_gnt_s_i.read());
        n_gnt_w_o.write(n_gnt_w_i.read());

        //East channel connections
        e_gnt_l_o.write(e_gnt_l_i.read());
        e_gnt_n_o.write("0");
        e_gnt_s_o.write("0");
        e_gnt_w_o.write(e_gnt_w_i.read());

        //South channel connections
        s_gnt_l_o.write(s_gnt_l_i.read());
        s_gnt_n_o.write(s_gnt_n_i.read());
        s_gnt_e_o.write(s_gnt_e_i.read());
        s_gnt_w_o.write(s_gnt_w_i.read());

        //West channel connections
        w_gnt_l_o.write(w_gnt_l_i.read());
        w_gnt_n_o.write("0");
        w_gnt_e_o.write(w_gnt_e_i.read());
        w_gnt_s_o.write("0");
    }

    SC_CTOR(crossbar){
        SC_METHOD(connections);
        sensitive << l_req_n_i << l_req_e_i<< l_req_s_i << l_req_w_i << n_req_l_i << n_req_s_i << e_req_l_i << e_req_n_i << e_req_s_i << e_req_w_i
        << s_req_l_i << s_req_n_i << w_req_l_i << w_req_n_i << w_req_e_i << w_req_s_i << l_gnt_n_i << l_gnt_e_i<< l_gnt_s_i << l_gnt_w_i << n_gnt_l_i
        << n_gnt_e_i << n_gnt_s_i << n_gnt_w_i << e_gnt_l_i << e_gnt_w_i << s_gnt_l_i << s_gnt_n_i << s_gnt_e_i << s_gnt_w_i << w_gnt_l_i << w_gnt_e_i;
    }

};
