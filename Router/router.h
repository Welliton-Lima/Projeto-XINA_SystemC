#ifndef ROUTER
#define ROUTER

#include <systemc.h>
#include "../Channel_in/channel_in.h"
#include "../Channel_out/channel_out.h"
#include "../Crossbar/crossbar.h"

template<unsigned int l_ena_p,unsigned int n_ena_p,unsigned int e_ena_p,unsigned int s_ena_p,unsigned int w_ena_p,unsigned int flow_mode_p,unsigned int routing_mode_p,unsigned int arbitration_mode_p,unsigned int buffer_mode_p,unsigned int buffer_depth_p,unsigned int data_width_p>

SC_MODULE(router){
//struct router: sc_module{
//     unsigned int x_id_p = 1,y_id_p=1,l_ena_p=1, n_ena_p=1,e_ena_p=1, s_ena_p=1, w_ena_p=1, flow_mode_p=0,routing_mode_p=0,arbitration_mode_p=0, buffer_mode_p=0,buffer_depth_p=4,data_width_p=8;

    channel_in<l_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p,data_width_p>  *lin0;
    channel_in<n_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p,data_width_p>  *nin0;
    channel_in<e_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p,data_width_p>  *ein0;
    channel_in<s_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p,data_width_p>  *sin0;
    channel_in<w_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p,data_width_p>  *win0;

    channel_out<l_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *lout0;
    channel_out<n_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *nout0;
    channel_out<e_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *eout0;
    channel_out<s_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *sout0;
    channel_out<w_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *wout0;

    crossbar *crossbar0;

    sc_in<bool>     clk_i;
    sc_in<sc_bv<1>> rst_i;

    // local channel interface
    sc_in<sc_bv<data_width_p+1>> l_in_data_i;
    sc_in<sc_bv<1>>              l_in_val_i;
    sc_out<sc_bv<1>>             l_in_ack_o;
    sc_out<sc_bv<data_width_p+1>>l_out_data_o;
    sc_out<sc_bv<1>>             l_out_val_o;
    sc_in<sc_bv<1>>              l_out_ack_i;

    //north channel interface
    sc_in<sc_bv<data_width_p+1>> n_in_data_i;
    sc_in<sc_bv<1>>              n_in_val_i;
    sc_out<sc_bv<1>>             n_in_ack_o;
    sc_out<sc_bv<data_width_p+1>>n_out_data_o;
    sc_out<sc_bv<1>>             n_out_val_o;
    sc_in<sc_bv<1>>              n_out_ack_i;

    //east channel interface
    sc_in<sc_bv<data_width_p+1>>  e_in_data_i;
    sc_in<sc_bv<1>>               e_in_val_i;
    sc_out<sc_bv<1>>              e_in_ack_o;
    sc_out<sc_bv<data_width_p+1>> e_out_data_o;
    sc_out<sc_bv<1>>              e_out_val_o;
    sc_in<sc_bv<1>>               e_out_ack_i;

    //south channel interface
    sc_in<sc_bv<data_width_p+1>>   s_in_data_i;
    sc_in<sc_bv<1>>                s_in_val_i;
    sc_out<sc_bv<1>>               s_in_ack_o;
    sc_out<sc_bv<data_width_p+1>>  s_out_data_o;
    sc_out<sc_bv<1>>               s_out_val_o;
    sc_in<sc_bv<1>>                s_out_ack_i;

    //west port interface
    sc_in<sc_bv<data_width_p+1>>  w_in_data_i;
    sc_in<sc_bv<1>>               w_in_val_i;
    sc_out<sc_bv<1>>              w_in_ack_o;
    sc_out<sc_bv<data_width_p+1>> w_out_data_o;
    sc_out<sc_bv<1>>              w_out_val_o;
    sc_in<sc_bv<1>>               w_out_ack_i;

    //----------------------Signals------------------------------------------------------//

    //channel l wires
        sc_signal<sc_bv<1>>              l_req_n_xin_w;
        sc_signal<sc_bv<1>>              l_req_e_xin_w;
        sc_signal<sc_bv<1>>              l_req_s_xin_w;
        sc_signal<sc_bv<1>>              l_req_w_xin_w;
        sc_signal<sc_bv<1>>              l_gnt_n_xin_w;
        sc_signal<sc_bv<1>>              l_gnt_e_xin_w;
        sc_signal<sc_bv<1>>              l_gnt_s_xin_w;
        sc_signal<sc_bv<1>>              l_gnt_w_xin_w;
        sc_signal<sc_bv<1>>              l_req_n_xout_w;
        sc_signal<sc_bv<1>>              l_req_e_xout_w;
        sc_signal<sc_bv<1>>              l_req_s_xout_w;
        sc_signal<sc_bv<1>>              l_req_w_xout_w;
        sc_signal<sc_bv<1>>              l_gnt_n_xout_w;
        sc_signal<sc_bv<1>>              l_gnt_e_xout_w;
        sc_signal<sc_bv<1>>              l_gnt_s_xout_w;
        sc_signal<sc_bv<1>>              l_gnt_w_xout_w;
        sc_signal<sc_bv<1>>              l_rok_w;
        sc_signal<sc_bv<1>>              l_rd_w;
        sc_signal<sc_bv<data_width_p+1>> l_data_w;

        //channel n wires
        sc_signal<sc_bv<1>>              n_req_l_xin_w;
        sc_signal<sc_bv<1>>              n_req_e_xin_w;
        sc_signal<sc_bv<1>>              n_req_s_xin_w;
        sc_signal<sc_bv<1>>              n_req_w_xin_w;
        sc_signal<sc_bv<1>>              n_gnt_l_xin_w;
        sc_signal<sc_bv<1>>              n_gnt_e_xin_w;
        sc_signal<sc_bv<1>>              n_gnt_s_xin_w;
        sc_signal<sc_bv<1>>              n_gnt_w_xin_w;
        sc_signal<sc_bv<1>>              n_req_l_xout_w;
        sc_signal<sc_bv<1>>              n_req_e_xout_w;
        sc_signal<sc_bv<1>>              n_req_s_xout_w;
        sc_signal<sc_bv<1>>              n_req_w_xout_w;
        sc_signal<sc_bv<1>>              n_gnt_l_xout_w;
        sc_signal<sc_bv<1>>              n_gnt_e_xout_w;
        sc_signal<sc_bv<1>>              n_gnt_s_xout_w;
        sc_signal<sc_bv<1>>              n_gnt_w_xout_w;
        sc_signal<sc_bv<1>>              n_rok_w;
        sc_signal<sc_bv<1>>              n_rd_w;
        sc_signal<sc_bv<data_width_p+1>> n_data_w;

        //channel e wires
        sc_signal<sc_bv<1>>               e_req_l_xin_w;
        sc_signal<sc_bv<1>>               e_req_n_xin_w;
        sc_signal<sc_bv<1>>               e_req_s_xin_w;
        sc_signal<sc_bv<1>>               e_req_w_xin_w;
        sc_signal<sc_bv<1>>               e_gnt_l_xin_w;
        sc_signal<sc_bv<1>>               e_gnt_n_xin_w;
        sc_signal<sc_bv<1>>               e_gnt_s_xin_w;
        sc_signal<sc_bv<1>>               e_gnt_w_xin_w;
        sc_signal<sc_bv<1>>               e_req_l_xout_w;
        sc_signal<sc_bv<1>>               e_req_n_xout_w;
        sc_signal<sc_bv<1>>               e_req_s_xout_w;
        sc_signal<sc_bv<1>>               e_req_w_xout_w;
        sc_signal<sc_bv<1>>               e_gnt_l_xout_w;
        sc_signal<sc_bv<1>>               e_gnt_n_xout_w;
        sc_signal<sc_bv<1>>               e_gnt_s_xout_w;
        sc_signal<sc_bv<1>>               e_gnt_w_xout_w;
        sc_signal<sc_bv<1>>               e_rok_w;
        sc_signal<sc_bv<1>>               e_rd_w;
        sc_signal<sc_bv<data_width_p+1>>  e_data_w;

        // channel s wires
        sc_signal<sc_bv<1>>              s_req_l_xin_w;
        sc_signal<sc_bv<1>>              s_req_n_xin_w;
        sc_signal<sc_bv<1>>              s_req_e_xin_w;
        sc_signal<sc_bv<1>>              s_req_w_xin_w;
        sc_signal<sc_bv<1>>              s_gnt_l_xin_w;
        sc_signal<sc_bv<1>>              s_gnt_n_xin_w;
        sc_signal<sc_bv<1>>              s_gnt_e_xin_w;
        sc_signal<sc_bv<1>>              s_gnt_w_xin_w;
        sc_signal<sc_bv<1>>              s_req_l_xout_w;
        sc_signal<sc_bv<1>>              s_req_n_xout_w;
        sc_signal<sc_bv<1>>              s_req_e_xout_w;
        sc_signal<sc_bv<1>>              s_req_w_xout_w;
        sc_signal<sc_bv<1>>              s_gnt_l_xout_w;
        sc_signal<sc_bv<1>>              s_gnt_n_xout_w;
        sc_signal<sc_bv<1>>              s_gnt_e_xout_w;
        sc_signal<sc_bv<1>>              s_gnt_w_xout_w;
        sc_signal<sc_bv<1>>              s_rok_w;
        sc_signal<sc_bv<1>>              s_rd_w;
        sc_signal<sc_bv<data_width_p+1>> s_data_w;

        //channel w wires
        sc_signal<sc_bv<1>>              w_req_l_xin_w;
        sc_signal<sc_bv<1>>              w_req_n_xin_w;
        sc_signal<sc_bv<1>>              w_req_e_xin_w;
        sc_signal<sc_bv<1>>              w_req_s_xin_w;
        sc_signal<sc_bv<1>>              w_gnt_l_xin_w;
        sc_signal<sc_bv<1>>              w_gnt_n_xin_w;
        sc_signal<sc_bv<1>>              w_gnt_e_xin_w;
        sc_signal<sc_bv<1>>              w_gnt_s_xin_w;
        sc_signal<sc_bv<1>>              w_req_l_xout_w;
        sc_signal<sc_bv<1>>              w_req_n_xout_w;
        sc_signal<sc_bv<1>>              w_req_e_xout_w;
        sc_signal<sc_bv<1>>              w_req_s_xout_w;
        sc_signal<sc_bv<1>>              w_gnt_l_xout_w;
        sc_signal<sc_bv<1>>              w_gnt_n_xout_w;
        sc_signal<sc_bv<1>>              w_gnt_e_xout_w;
        sc_signal<sc_bv<1>>              w_gnt_s_xout_w;
        sc_signal<sc_bv<1>>              w_rok_w;
        sc_signal<sc_bv<1>>              w_rd_w;
        sc_signal<sc_bv<data_width_p+1>> w_data_w;


        sc_signal<sc_bv<1>> openl, openn, opene, opens, openw;

        sc_bv<4> gnt_i_l_w, rd_i_l_w, rok_i_l_w, req_i_l_w;
        sc_signal<sc_bv<4>> w_gnt_i_l, w_rd_i_l, w_gnt_o_l, w_rok_i_l, w_req_i_l;

        sc_bv<4> gnt_i_n_w, rd_i_n_w, rok_i_n_w, req_i_n_w;
        sc_signal<sc_bv<4>> w_gnt_i_n, w_rd_i_n, w_gnt_o_n, w_rok_i_n, w_req_i_n;

        sc_bv<4> gnt_i_e_w, rd_i_e_w,rok_i_e_w, req_i_e_w;
        sc_signal<sc_bv<4>> w_gnt_i_e, w_rd_i_e, w_gnt_o_e, w_rok_i_e, w_req_i_e;

        sc_bv<4> gnt_i_s_w, rd_i_s_w, rok_i_s_w, req_i_s_w;
        sc_signal<sc_bv<4>> w_gnt_i_s, w_rd_i_s, w_gnt_o_s, w_rok_i_s, w_req_i_s;

        sc_bv<4> gnt_i_w_w, rd_i_w_w,rok_i_w_w, req_i_w_w;
        sc_signal<sc_bv<4>> w_gnt_i_w, w_rd_i_w, w_gnt_o_w, w_rok_i_w, w_req_i_w;

        unsigned int X, Y;

        void set_position(int x, int y){
            this->X = x;
            this->Y = y;
        }

    void connections(){
        //---------------Siganls local channel----------------------------//
        //---------Inputs---------//
        gnt_i_l_w[3] = n_gnt_l_xin_w.read().get_bit(0);
        gnt_i_l_w[2] = e_gnt_l_xin_w.read().get_bit(0);
        gnt_i_l_w[1] = s_gnt_l_xin_w.read().get_bit(0);
        gnt_i_l_w[0] = w_gnt_l_xin_w.read().get_bit(0);
        w_gnt_i_l.write(gnt_i_l_w);

        rd_i_l_w[3] = n_rd_w.read().get_bit(0);
        rd_i_l_w[2] = e_rd_w.read().get_bit(0);
        rd_i_l_w[1] = s_rd_w.read().get_bit(0);
        rd_i_l_w[0] = w_rd_w.read().get_bit(0);
        w_rd_i_l.write(rd_i_l_w);

        req_i_l_w[3] = n_req_l_xout_w.read().get_bit(0);
        req_i_l_w[2] = e_req_l_xout_w.read().get_bit(0);
        req_i_l_w[1] = s_req_l_xout_w.read().get_bit(0);
        req_i_l_w[0] = w_req_l_xout_w.read().get_bit(0);
        w_req_i_l.write(req_i_l_w);

        rok_i_l_w[3] = n_rok_w.read().get_bit(0);
        rok_i_l_w[2] = e_rok_w.read().get_bit(0);
        rok_i_l_w[1] = s_rok_w.read().get_bit(0);
        rok_i_l_w[0] = w_rok_w.read().get_bit(0);
        w_rok_i_l.write(rok_i_l_w);

        //---------Outputs---------//
        l_gnt_n_xout_w.write(w_gnt_o_l.read().get_bit(3));
        l_gnt_e_xout_w.write(w_gnt_o_l.read().get_bit(2));
        l_gnt_s_xout_w.write(w_gnt_o_l.read().get_bit(1));
        l_gnt_w_xout_w.write(w_gnt_o_l.read().get_bit(0));


        //---------------Siganls North channel----------------------------//
        //---------Inputs---------//
        gnt_i_n_w[3] = l_gnt_n_xin_w.read().get_bit(0);
        gnt_i_n_w[2] = e_gnt_n_xin_w.read().get_bit(0);
        gnt_i_n_w[1] = s_gnt_n_xin_w.read().get_bit(0);
        gnt_i_n_w[0] = w_gnt_n_xin_w.read().get_bit(0);
        w_gnt_i_n.write(gnt_i_n_w);

        rd_i_n_w[3] = l_rd_w.read().get_bit(0);
        rd_i_n_w[2] = e_rd_w.read().get_bit(0);
        rd_i_n_w[1] = s_rd_w.read().get_bit(0);
        rd_i_n_w[0] = w_rd_w.read().get_bit(0);
        w_rd_i_n.write(rd_i_n_w);

        req_i_n_w[3] = l_req_n_xout_w.read().get_bit(0);
        req_i_n_w[2] = e_req_n_xout_w.read().get_bit(0);
        req_i_n_w[1] = s_req_n_xout_w.read().get_bit(0);
        req_i_n_w[0] = w_req_n_xout_w.read().get_bit(0);
        w_req_i_n.write(req_i_n_w);

        rok_i_n_w[3] = l_rok_w.read().get_bit(0);
        rok_i_n_w[2] = e_rok_w.read().get_bit(0);
        rok_i_n_w[1] = s_rok_w.read().get_bit(0);
        rok_i_n_w[0] = w_rok_w.read().get_bit(0);
        w_rok_i_n.write(rok_i_n_w);

        //---------Outputs---------//
        n_gnt_l_xout_w.write(w_gnt_o_n.read().get_bit(3));
        n_gnt_e_xout_w.write(w_gnt_o_n.read().get_bit(2));
        n_gnt_s_xout_w.write(w_gnt_o_n.read().get_bit(1));
        n_gnt_w_xout_w.write(w_gnt_o_n.read().get_bit(0));

        //---------------Siganls East channel----------------------------//
        //---------Inputs---------//
        gnt_i_e_w[3] = l_gnt_e_xin_w.read().get_bit(0);
        gnt_i_e_w[2] = n_gnt_e_xin_w.read().get_bit(0);
        gnt_i_e_w[1] = s_gnt_e_xin_w.read().get_bit(0);
        gnt_i_e_w[0] = w_gnt_e_xin_w.read().get_bit(0);
        w_gnt_i_e.write(gnt_i_e_w);

        rd_i_e_w[3] = l_rd_w.read().get_bit(0);
        rd_i_e_w[2] = n_rd_w.read().get_bit(0);
        rd_i_e_w[1] = s_rd_w.read().get_bit(0);
        rd_i_e_w[0] = w_rd_w.read().get_bit(0);
        w_rd_i_e.write(rd_i_e_w);

        req_i_e_w[3] = l_req_e_xout_w.read().get_bit(0);
        req_i_e_w[2] = n_req_e_xout_w.read().get_bit(0);
        req_i_e_w[1] = s_req_e_xout_w.read().get_bit(0);
        req_i_e_w[0] = w_req_e_xout_w.read().get_bit(0);
        w_req_i_e.write(req_i_e_w);

        rok_i_e_w[3] = l_rok_w.read().get_bit(0);
        rok_i_e_w[2] = n_rok_w.read().get_bit(0);
        rok_i_e_w[1] = s_rok_w.read().get_bit(0);
        rok_i_e_w[0] = w_rok_w.read().get_bit(0);
        //---------Outputs---------//
        e_gnt_l_xout_w.write(w_gnt_o_e.read().get_bit(3));
        e_gnt_n_xout_w.write(w_gnt_o_e.read().get_bit(2));
        e_gnt_s_xout_w.write(w_gnt_o_e.read().get_bit(1));
        e_gnt_w_xout_w.write(w_gnt_o_e.read().get_bit(0));

        //---------------Siganls South channel----------------------------//
        //---------Inputs---------//
        gnt_i_s_w[3] = l_gnt_s_xin_w.read().get_bit(0);
        gnt_i_s_w[2] = n_gnt_s_xin_w.read().get_bit(0);
        gnt_i_s_w[1] = e_gnt_s_xin_w.read().get_bit(0);
        gnt_i_s_w[0] = w_gnt_s_xin_w.read().get_bit(0);
        w_gnt_i_s.write(gnt_i_s_w);

        rd_i_s_w[3] = l_rd_w.read().get_bit(0);
        rd_i_s_w[2] = n_rd_w.read().get_bit(0);
        rd_i_s_w[1] = e_rd_w.read().get_bit(0);
        rd_i_s_w[0] = w_rd_w.read().get_bit(0);
        w_rd_i_s.write(rd_i_s_w);

        req_i_s_w[3] = l_req_s_xout_w.read().get_bit(0);
        req_i_s_w[2] = n_req_s_xout_w.read().get_bit(0);
        req_i_s_w[1] = e_req_s_xout_w.read().get_bit(0);
        req_i_s_w[0] = w_req_s_xout_w.read().get_bit(0);
        w_req_i_s.write(req_i_s_w);

        rok_i_s_w[3] = l_rok_w.read().get_bit(0);
        rok_i_s_w[2] = n_rok_w.read().get_bit(0);
        rok_i_s_w[1] = e_rok_w.read().get_bit(0);
        rok_i_s_w[0] = w_rok_w.read().get_bit(0);
        w_rok_i_s.write(rok_i_s_w);

        //---------Outputs---------//
        s_gnt_l_xout_w.write(w_gnt_o_s.read().get_bit(3));
        s_gnt_n_xout_w.write(w_gnt_o_s.read().get_bit(2));
        s_gnt_e_xout_w.write(w_gnt_o_s.read().get_bit(1));
        s_gnt_w_xout_w.write(w_gnt_o_s.read().get_bit(0));

        //---------------Siganls West channel----------------------------//
        //---------Inputs---------//
        gnt_i_w_w[3] = l_gnt_w_xin_w.read().get_bit(0);
        gnt_i_w_w[2] = n_gnt_w_xin_w.read().get_bit(0);
        gnt_i_w_w[1] = e_gnt_w_xin_w.read().get_bit(0);
        gnt_i_w_w[0] = s_gnt_w_xin_w.read().get_bit(0);
        w_gnt_i_w.write(gnt_i_w_w);

        rd_i_w_w[3] = l_rd_w.read().get_bit(0);
        rd_i_w_w[2] = n_rd_w.read().get_bit(0);
        rd_i_w_w[1] = e_rd_w.read().get_bit(0);
        rd_i_w_w[0] = s_rd_w.read().get_bit(0);
        w_rd_i_w.write(rd_i_w_w);

        req_i_w_w[3] = l_req_w_xout_w.read().get_bit(0);
        req_i_w_w[2] = n_req_w_xout_w.read().get_bit(0);
        req_i_w_w[1] = e_req_w_xout_w.read().get_bit(0);
        req_i_w_w[0] = s_req_w_xout_w.read().get_bit(0);
        w_req_i_w.write(req_i_w_w);

        rok_i_w_w[3] = l_rok_w.read().get_bit(0);
        rok_i_w_w[2] = n_rok_w.read().get_bit(0);
        rok_i_w_w[1] = e_rok_w.read().get_bit(0);
        rok_i_w_w[0] = s_rok_w.read().get_bit(0);
        w_rok_i_w.write(rok_i_w_w);

        //---------Outputs---------//
        w_gnt_l_xout_w.write(w_gnt_o_w.read().get_bit(3));
        w_gnt_n_xout_w.write(w_gnt_o_w.read().get_bit(2));
        w_gnt_e_xout_w.write(w_gnt_o_w.read().get_bit(1));
        w_gnt_s_xout_w.write(w_gnt_o_w.read().get_bit(0));

//         cout<<"l_in_ack_o: "<<l_in_ack_o<<endl;
//         cout<<"l_req_n_xin_w: "<<l_req_n_xin_w <<endl;
//         cout<<"l_req_e_xin_w: "<<l_req_e_xin_w <<endl;
//         cout<<"l_req_s_xin_w: "<<l_req_s_xin_w <<endl;
//         cout<<"l_req_w_xin_w: "<<l_req_w_xin_w <<endl;
//         cout<<"l_rok_w: "<<l_rok_w <<endl;
//         cout<<"w_req_i_e: "<<w_req_i_e <<endl;
//         cout<<"rok_i_e_w: "<<rok_i_e_w <<endl;
//         cout<<"l_data_w: "<< l_data_w<<endl;
//         cout<<"e_in_ack_o: "<<e_in_ack_o<<endl;
//         cout<<"e_req_n_xin_w: "<<e_req_n_xin_w <<endl;
//         cout<<"e_req_e_xin_w: "<<e_req_l_xin_w <<endl;
//         cout<<"e_req_s_xin_w: "<<e_req_s_xin_w <<endl;
//         cout<<"e_req_w_xin_w: "<<e_req_w_xin_w <<endl;
//         cout<<"e_rok_w: "<<e_rok_w <<endl;
//         cout<<"e_data_w: "<< e_data_w<<endl;
//         cout<<"e_out_data_o: "<< e_out_data_o<<endl;
//         cout<<"e_out_val_o: "<< e_out_val_o<<endl;
//         cout<<"e_out_ack_i: "<< e_out_ack_i<<endl;
//         cout<<"w_gnt_o_e: "<< w_gnt_o_e<<endl;
//
//         cout<<"l_data_w: "<< l_data_w<<endl;
//         cout<<"n_data_w: "<< n_data_w<<endl;
//         cout<<"s_data_w: "<< s_data_w<<endl;
//         cout<<"w_data_w: "<< w_data_w<<endl;
//
//         cout<<"w_req_i_e: "<< w_req_i_e<<endl;
//         cout<<"w_rok_i_e: "<< w_rok_i_e<<endl;
        cout<<"l_out_data_o: "<< l_out_data_o<<endl;
        cout<<"l_in_val_i: "<< l_in_val_i<<endl;
        cout<<"l_in_ack_o: "<< l_in_ack_o<<endl;

    }

    //void connections(){
    SC_CTOR(router){
        SC_METHOD(connections);
        sensitive << clk_i << rst_i;

        lin0 = new channel_in <l_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p,data_width_p>("lin0");

        lin0->set_position(X,Y);
        lin0->clk_i(clk_i);
        lin0->rst_i(rst_i);
        lin0->data_i(l_in_data_i);
        lin0->val_i(l_in_val_i);
        lin0->ack_o(l_in_ack_o);
        lin0->req_l_o(openl);
        lin0->req_n_o(l_req_n_xin_w);
        lin0->req_e_o(l_req_e_xin_w);
        lin0->req_s_o(l_req_s_xin_w);
        lin0->req_w_o(l_req_w_xin_w);
        lin0->gnt_i(w_gnt_i_l);
        lin0->rok_o(l_rok_w);
        lin0->rd_i(w_rd_i_l);
        lin0->data_o(l_data_w);

        //channel_out<l_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *lout0;
        lout0 = new channel_out<l_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>("lout0");

        lout0->clk_i(clk_i);
        lout0->rst_i(rst_i);
        lout0->data_o(l_out_data_o);
        lout0->val_o(l_out_val_o);
        lout0->ack_i(l_out_ack_i);
        lout0->req_i(w_req_i_l);
        lout0->gnt_o(w_gnt_o_l);
        lout0->rok_i(w_rok_i_l);
        lout0->rd_o(l_rd_w);
        lout0->data3_i(n_data_w);
        lout0->data2_i(e_data_w);
        lout0->data1_i(s_data_w);
        lout0->data0_i(w_data_w);

        //channel_in <n_ena_p,x_id_p,y_id_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p>  *nin0;
        nin0 = new channel_in <n_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p,data_width_p>("nin0");

        nin0->set_position(X,Y);
        nin0->clk_i(clk_i);
        nin0->rst_i(rst_i);
        nin0->data_i(n_in_data_i);
        nin0->val_i(n_in_val_i);
        nin0->ack_o(n_in_ack_o);
        nin0->req_l_o(n_req_l_xin_w);
        nin0->req_n_o(openn);
        nin0->req_e_o(n_req_e_xin_w);
        nin0->req_s_o(n_req_s_xin_w);
        nin0->req_w_o(n_req_w_xin_w);
        nin0->gnt_i(w_gnt_i_n);
        nin0->rok_o(n_rok_w);
        nin0->rd_i(w_rd_i_n);
        nin0->data_o(n_data_w);

        //channel_out<n_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *nout0;
        nout0 = new channel_out<n_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>("nout0");

        nout0->clk_i(clk_i);
        nout0->rst_i(rst_i);
        nout0->data_o(n_out_data_o);
        nout0->val_o(n_out_val_o);
        nout0->ack_i(n_out_ack_i);
        nout0->req_i(w_req_i_n);
        nout0->gnt_o(w_gnt_o_n);
        nout0->rok_i(w_rok_i_n);
        nout0->rd_o(n_rd_w);
        nout0->data3_i(l_data_w);
        nout0->data2_i(e_data_w);
        nout0->data1_i(s_data_w);
        nout0->data0_i(w_data_w);
//
//         //channel_in <e_ena_p,x_id_p,y_id_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p>  *ein0;
        ein0 = new channel_in <e_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p>("ein0");

        ein0->set_position(X,Y);
        ein0->clk_i(clk_i);
        ein0->rst_i(rst_i);
        ein0->data_i(e_in_data_i);
        ein0->val_i(e_in_val_i);
        ein0->ack_o(e_in_ack_o);
        ein0->req_l_o(e_req_l_xin_w);
        ein0->req_n_o(e_req_n_xin_w);
        ein0->req_e_o(opene);
        ein0->req_s_o(e_req_s_xin_w);
        ein0->req_w_o(e_req_w_xin_w);
        ein0->gnt_i(w_gnt_i_e);
        ein0->rd_i(w_rd_i_e);
        ein0->rok_o(e_rok_w);
        ein0->data_o(e_data_w);

//         //channel_out<e_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *eout0;
        eout0 = new channel_out<e_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>("eout0");

        eout0->clk_i(clk_i);
        eout0->rst_i(rst_i);
        eout0->data_o(e_out_data_o);
        eout0->val_o(e_out_val_o);
        eout0->ack_i(e_out_ack_i);
        eout0->req_i(w_req_i_e);
        eout0->gnt_o(w_gnt_o_e);
        eout0->rok_i(w_rok_i_e);
        eout0->rd_o(e_rd_w);
        eout0->data3_i(l_data_w);
        eout0->data2_i(n_data_w);
        eout0->data1_i(s_data_w);
        eout0->data0_i(w_data_w);

//         //channel_in <s_ena_p,x_id_p,y_id_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p>  *sin0;
        sin0 = new channel_in <s_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p>("sin0");

        sin0->set_position(X,Y);
        sin0->clk_i(clk_i);
        sin0->rst_i(rst_i);
        sin0->data_i(s_in_data_i);
        sin0->val_i(s_in_val_i);
        sin0->ack_o(s_in_ack_o);
        sin0->req_l_o(s_req_l_xin_w);
        sin0->req_n_o(s_req_n_xin_w);
        sin0->req_e_o(s_req_e_xin_w);
        sin0->req_s_o(opens);
        sin0->req_w_o(s_req_w_xin_w);
        sin0->gnt_i(w_gnt_i_s);
        sin0->rd_i(w_rd_i_s);
        sin0->rok_o(s_rok_w);
        sin0->data_o(s_data_w);

        //channel_out<s_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>  *sout0;
        sout0 = new  channel_out<s_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>("sout0");

        sout0->clk_i(clk_i);
        sout0->rst_i(rst_i);
        sout0->data_o(s_out_data_o);
        sout0->val_o(s_out_val_o);
        sout0->ack_i(s_out_ack_i);
        sout0->req_i(w_req_i_s);
        sout0->gnt_o(w_gnt_o_s);
        sout0->rok_i(w_rok_i_s);
        sout0->rd_o(s_rd_w);
        sout0->data3_i(l_data_w);
        sout0->data2_i(n_data_w);
        sout0->data1_i(e_data_w);
        sout0->data0_i(w_data_w);

//         //channel_in <w_ena_p,x_id_p,y_id_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p>  *win0;
        win0 = new channel_in <w_ena_p,flow_mode_p,routing_mode_p,buffer_mode_p,buffer_depth_p, data_width_p>("win0");

        win0->set_position(X,Y);
        win0->clk_i(clk_i);
        win0->rst_i(rst_i);
        win0->data_i(w_in_data_i);
        win0->val_i(w_in_val_i);
        win0->ack_o(w_in_ack_o);
        win0->req_l_o(w_req_l_xin_w);
        win0->req_n_o(w_req_n_xin_w);
        win0->req_e_o(w_req_e_xin_w);
        win0->req_s_o(w_req_s_xin_w);
        win0->req_w_o(openw);
        win0->gnt_i(w_gnt_i_w);
        win0->rok_o(w_rok_w);
        win0->rd_i(w_rd_i_w);
        win0->data_o(w_data_w);

        wout0 = new channel_out<w_ena_p,flow_mode_p,arbitration_mode_p,data_width_p>("wout0");

        wout0->clk_i(clk_i);
        wout0->rst_i(rst_i);
        wout0->data_o(w_out_data_o);
        wout0->val_o(w_out_val_o);
        wout0->ack_i(w_out_ack_i);
        wout0->req_i(w_req_i_w);
        wout0->gnt_o(w_gnt_o_w);
        wout0->rd_o(w_rd_w);
        wout0->rok_i(w_rok_i_w);
        wout0->data3_i(l_data_w);
        wout0->data2_i(n_data_w);
        wout0->data1_i(e_data_w);
        wout0->data0_i(s_data_w);

        crossbar0 = new  crossbar("crossbar0");

        crossbar0->l_req_n_i(l_req_n_xin_w);
        crossbar0->l_req_e_i(l_req_e_xin_w);
        crossbar0->l_req_s_i(l_req_s_xin_w);
        crossbar0->l_req_w_i(l_req_w_xin_w);
        crossbar0->l_req_n_o(l_req_n_xout_w);
        crossbar0->l_req_e_o(l_req_e_xout_w);
        crossbar0->l_req_s_o(l_req_s_xout_w);
        crossbar0->l_req_w_o(l_req_w_xout_w);

        crossbar0->n_req_l_i(n_req_l_xin_w);
        crossbar0->n_req_e_i(n_req_e_xin_w);
        crossbar0->n_req_s_i(n_req_s_xin_w);
        crossbar0->n_req_w_i(n_req_w_xin_w);
        crossbar0->n_req_l_o(n_req_l_xout_w);
        crossbar0->n_req_e_o(n_req_e_xout_w);
        crossbar0->n_req_s_o(n_req_s_xout_w);
        crossbar0->n_req_w_o(n_req_w_xout_w);

        crossbar0->e_req_l_i(e_req_l_xin_w);
        crossbar0->e_req_n_i(e_req_n_xin_w);
        crossbar0->e_req_s_i(e_req_s_xin_w);
        crossbar0->e_req_w_i(e_req_w_xin_w);
        crossbar0->e_req_l_o(e_req_l_xout_w);
        crossbar0->e_req_n_o(e_req_n_xout_w);
        crossbar0->e_req_s_o(e_req_s_xout_w);
        crossbar0->e_req_w_o(e_req_w_xout_w);

        crossbar0->s_req_l_i(s_req_l_xin_w);
        crossbar0->s_req_n_i(s_req_n_xin_w);
        crossbar0->s_req_e_i(s_req_e_xin_w);
        crossbar0->s_req_w_i(s_req_w_xin_w);
        crossbar0->s_req_l_o(s_req_l_xout_w);
        crossbar0->s_req_n_o(s_req_n_xout_w);
        crossbar0->s_req_e_o(s_req_e_xout_w);
        crossbar0->s_req_w_o(s_req_w_xout_w);

        crossbar0->w_req_l_i(w_req_l_xin_w);
        crossbar0->w_req_n_i(w_req_n_xin_w);
        crossbar0->w_req_e_i(w_req_e_xin_w);
        crossbar0->w_req_s_i(w_req_s_xin_w);
        crossbar0->w_req_l_o(w_req_l_xout_w);
        crossbar0->w_req_n_o(w_req_n_xout_w);
        crossbar0->w_req_e_o(w_req_e_xout_w);
        crossbar0->w_req_s_o(w_req_s_xout_w);

        crossbar0->l_gnt_n_i(l_gnt_n_xout_w);
        crossbar0->l_gnt_e_i(l_gnt_e_xout_w);
        crossbar0->l_gnt_s_i(l_gnt_s_xout_w);
        crossbar0->l_gnt_w_i(l_gnt_w_xout_w);
        crossbar0->l_gnt_n_o(l_gnt_n_xin_w);
        crossbar0->l_gnt_e_o(l_gnt_e_xin_w);
        crossbar0->l_gnt_s_o(l_gnt_s_xin_w);
        crossbar0->l_gnt_w_o(l_gnt_w_xin_w);

        crossbar0->n_gnt_l_i(n_gnt_l_xout_w);
        crossbar0->n_gnt_e_i(n_gnt_e_xout_w);
        crossbar0->n_gnt_s_i(n_gnt_s_xout_w);
        crossbar0->n_gnt_w_i(n_gnt_w_xout_w);
        crossbar0->n_gnt_l_o(n_gnt_l_xin_w);
        crossbar0->n_gnt_e_o(n_gnt_e_xin_w);
        crossbar0->n_gnt_s_o(n_gnt_s_xin_w);
        crossbar0->n_gnt_w_o(n_gnt_w_xin_w);

        crossbar0->e_gnt_l_i(e_gnt_l_xout_w);
        crossbar0->e_gnt_n_i(e_gnt_n_xout_w);
        crossbar0->e_gnt_s_i(e_gnt_s_xout_w);
        crossbar0->e_gnt_w_i(e_gnt_w_xout_w);
        crossbar0->e_gnt_l_o(e_gnt_l_xin_w);
        crossbar0->e_gnt_n_o(e_gnt_n_xin_w);
        crossbar0->e_gnt_s_o(e_gnt_s_xin_w);
        crossbar0->e_gnt_w_o(e_gnt_w_xin_w);

        crossbar0->s_gnt_l_i(s_gnt_l_xout_w);
        crossbar0->s_gnt_n_i(s_gnt_n_xout_w);
        crossbar0->s_gnt_e_i(s_gnt_e_xout_w);
        crossbar0->s_gnt_w_i(s_gnt_w_xout_w);
        crossbar0->s_gnt_l_o(s_gnt_l_xin_w);
        crossbar0->s_gnt_n_o(s_gnt_n_xin_w);
        crossbar0->s_gnt_e_o(s_gnt_e_xin_w);
        crossbar0->s_gnt_w_o(s_gnt_w_xin_w);

        crossbar0->w_gnt_l_i(w_gnt_l_xout_w);
        crossbar0->w_gnt_n_i(w_gnt_n_xout_w);
        crossbar0->w_gnt_e_i(w_gnt_e_xout_w);
        crossbar0->w_gnt_s_i(w_gnt_s_xout_w);
        crossbar0->w_gnt_l_o(w_gnt_l_xin_w);
        crossbar0->w_gnt_n_o(w_gnt_n_xin_w);
        crossbar0->w_gnt_e_o(w_gnt_e_xin_w);
        crossbar0->w_gnt_s_o(w_gnt_s_xin_w);
    }

    ~router(){
        delete  lin0;
        delete  nin0;
        delete  ein0;
        delete  sin0;
        delete  win0;
        delete  lout0;
        delete  nout0;
        delete  eout0;
        delete  sout0;
        delete  wout0;
        delete crossbar0;
    }

};
#endif
