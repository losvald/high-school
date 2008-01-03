/*
 * Igra.java
 *
 * Copyright (C) 2007 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of Bela mob.
 *
 * Bela mob is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Bela mob is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bela mob. If not, see <http://www.gnu.org/licenses/>.
 */

import javax.bluetooth.*;
import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
import javax.microedition.io.*;
import java.io.*;
public class Igra extends Canvas implements Runnable, DiscoveryListener {
    boolean has_started, is_server, client_rdy, has_client_joined, is_sp, game_started, game_over;

    boolean cards_dealt;
    boolean ready_end_turn;
    boolean server_pressed, play_card_pressed;
    boolean server_down;
    Thread runner;
    Graphics g;
    Log log;
    int br;
    final int char_offset = 30;
    //command msgs
    final String join_confirm_msg = "OKK_";
    final String disconnect_msg = "DIS_";
    final String welcome_msg = "WEL_";
    final String error_msg = "ERR_";
    final String info_msg = "INF_";
    final String unk_msg = "UNK_";
    final String server_full_msg = "FUL_";
    final String kick_msg = "KIC_";
    final String game_started_msg = "GSM_";
    final String deal_msg = "DEA_";
    final String adut_msg = "ADU_";
    final String dalje_msg = "DAL_";
    final String card_msg = "CAR_";
    final String zvanje_koje_msg = "ZWH_";
    final String zvanje_max_msg = "ZMA_";
    final String zvanje_max_sec_msg = "ZMS_";
    final String zvanje_tko_msg = "ZMT_";
    final String zvanje_score_msg = "ZSC_";
    final String zvanje_sel_end_msg = "ZSE_";
    final String novo_odigravanje_msg = "NOD_";
    final String update_ime_msg = "UIM_";
    final String bela_msg = "BEL_";

    final String open_slot = "Open";
    public static final UUID RFCOMM_UUID = new UUID(0x0003);
    private static String serverUrl = "btspp://localhost:" +
       RFCOMM_UUID + ";name=rfcommtest;authorize=false";
    StreamConnectionNotifier notifier;
    StreamConnection conn_server;
    StreamConnection[] conn_to_client;
    OutputStream out_stream_server;
    InputStream in_stream_server;
    OutputStream[] out_stream;
    InputStream[] in_stream;

    LocalDevice localDevice;
    ServiceRecord serviceRecord;
    String address;
    //client
    private DiscoveryAgent discoveryAgent;
    private RemoteDevice[] remoteDevices;
    private UUID[] uuidSet;
    private String[] service;
    private final int MAX_DEVICE = 20;
    int[] searchID;
    int n_servers;
    int moj_server;
    int id; //koji si id
    String ime;
    String[] player_name;
    boolean quit;
    int max_players;
    int x, y, dx, dy;
    int zv_max, zv_max_sec, zv_tko, zv_score, zv_koje_karte_size;
    int[] zv_koje_karte;

    private Font font_prop, font_prop_bold, font_mono, font_mono_bold, font_mono_italic, font_system;
    static Image[] img_card, img_card_rot, img_suit;
    final int cg_hand_offset = 12;
    final int cg_cardw = 20, cg_cardh = 31;
    final int cg_table_color = 0x3A923C;
    final int cg_trick_overlap = 6;
    int cg_ul_kutw, cg_ul_kuth;
    int cg_trickx, cg_tricky, cg_infox, cg_infoy, cg_trick_size;
    int[] cg_trick_card_id;
    int[] cg_trick_posx, cg_trick_posy;
    int cg_handx, cg_handy;
    int cg_h, cg_w;
    final int cg_scores_offset = 1;
    final int cg_zovi_size = 19, cg_zovi_offset = 1;
    final int cg_popis_igraca_size = 4;
    int[] cg_arrow_interx, cg_arrow_intery, cg_arrow_v_x, cg_arrow_v_y;
    int[][] cg_arrowx, cg_arrowy;
    int cg_arrowh;
    int cg_scoresx, cg_scoresy, cg_scoresw, cg_scoresh;
    int cg_scores_mix, cg_scores_vix, cg_scores_miviy, cg_scores_splitx;
    int cg_scores_tipx, cg_scores_tip0y, cg_scores_tip1y, cg_scores_tip2y;
    int cg_full_scoresx, cg_full_scoresy, cg_full_scoresw, cg_full_scoresh, cg_full_scores_arc;
    int cg_full_scores_hcenter, cg_full_scores_mix, cg_full_scores_vix;
    int cg_zovix, cg_zoviy, cg_zovi_daljex, cg_zovi_daljey;
    int[] cg_zvane_kartex, cg_zvane_kartey;
    boolean cg_show_zvanje, cg_show_full_scores;
    int cg_zvana_bojax, cg_zvana_bojay;
    int[] cg_namex, cg_namey;
    int cg_namew, cg_nameh, cg_propw, cg_proph, cg_monoh;
    String[] cg_popis_igraca; //kad klijent udje da vidi tko je unutra trenutno
    int[] cg_where; //za rotiranje ploce tj pozicija

    information info;
    deck spil;
    hand[] ruka_sp;
    hand ruka;
    int hand_proba;
    boolean[] allowed_to_play;
    int[] this_trick;

    int[] keynum;
    public List server_list;
    public List joined_list;
    public List player_list;
    public Igra() {
        //KEYNUM INIT
        keynum = new int[10];
        keynum[0] = KEY_NUM0;
        keynum[1] = KEY_NUM1;
        keynum[2] = KEY_NUM2;
        keynum[3] = KEY_NUM3;
        keynum[4] = KEY_NUM4;
        keynum[5] = KEY_NUM5;
        keynum[6] = KEY_NUM6;
        keynum[7] = KEY_NUM7;
        keynum[8] = KEY_NUM8;
        keynum[9] = KEY_NUM9;

        info = new information();
        log = new Log();

        cards_dealt = false;

        allowed_to_play = new boolean[8];
        ready_end_turn = true;
        this_trick = new int[4];
        for(int i = 0; i < 4; ++i) this_trick[i] = -1;
        hand_proba = info.get_na_redu();
        spil = new deck();

        //cg INIT

        font_prop = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_SMALL);
        font_prop_bold = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_BOLD, Font.SIZE_SMALL);
        font_mono = Font.getFont(Font.FACE_MONOSPACE, Font.STYLE_PLAIN, Font.SIZE_SMALL);
        font_mono_bold = Font.getFont(Font.FACE_MONOSPACE, Font.STYLE_BOLD, Font.SIZE_SMALL);
        font_mono_italic = Font.getFont(Font.FACE_MONOSPACE, Font.STYLE_ITALIC, Font.SIZE_SMALL);
        font_system = Font.getFont(Font.FACE_SYSTEM, Font.STYLE_PLAIN, Font.SIZE_SMALL);

        cg_w = getWidth(); cg_h = getHeight();
        //cg_w = 128; cg_h = 128;
        cg_monoh = font_mono.getHeight();
        cg_proph = font_prop.getHeight();
        cg_namew = font_mono.stringWidth("1234567");
        cg_nameh = font_mono.getHeight();

        cg_handx = (cg_w - (8*cg_cardw-7*(cg_cardw-cg_hand_offset)))/2;
        cg_handy = cg_h - (cg_cardh + cg_proph);
        cg_trick_size = 2*cg_cardw + cg_cardh - 2*cg_trick_overlap;

        cg_trickx = (cg_w - cg_trick_size)/2;
        cg_tricky = (cg_handy - cg_trick_size)/2;
        if(cg_tricky < cg_proph) cg_tricky = cg_proph;
        else if(cg_tricky + cg_trick_size + 2 > cg_handy)
          cg_tricky = cg_handy - (cg_trick_size + 2);
        cg_trick_posx = new int[4];
        cg_trick_posy = new int[4];

        cg_trick_posx[0] = cg_cardw - cg_trick_overlap;
        cg_trick_posy[0] = cg_cardw - cg_trick_overlap + cg_cardh - cg_trick_overlap;
        cg_trick_posx[1] = cg_cardw - cg_trick_overlap + cg_cardh - cg_trick_overlap;
        cg_trick_posy[1] = cg_cardw - cg_trick_overlap;
        cg_trick_posx[2] = cg_cardw - cg_trick_overlap;
        cg_trick_posy[2] = 0;
        cg_trick_posx[3] = 0;
        cg_trick_posy[3] = cg_cardw - cg_trick_overlap;
        cg_trick_card_id = new int[4];

        cg_arrowh = 4;
        cg_arrowx = new int[4][3];
        cg_arrowy = new int[4][3];
        cg_arrow_v_x = new int[4];
        cg_arrow_v_y = new int[4];
        cg_arrow_interx = new int[4];
        cg_arrow_intery = new int[4];

        cg_arrow_interx[0] = cg_trickx + cg_cardw + cg_arrowh;
        cg_arrow_intery[0] = cg_tricky + cg_cardw + cg_cardh - 2*cg_trick_overlap - cg_arrowh;
        cg_arrow_interx[1] = cg_trickx + cg_cardw + cg_cardh - 2*cg_trick_overlap - cg_arrowh;
        cg_arrow_intery[1] = cg_tricky + cg_cardw + cg_cardh - 2*cg_trick_overlap - cg_arrowh;
        cg_arrow_interx[2] = cg_trickx + cg_cardw + cg_cardh - 2*cg_trick_overlap - cg_arrowh;
        cg_arrow_intery[2] = cg_tricky + cg_cardw + cg_arrowh;
        cg_arrow_interx[3] = cg_trickx + cg_cardw + cg_arrowh;
        cg_arrow_intery[3] = cg_tricky + cg_cardw + cg_arrowh;

        cg_arrow_v_x[0] = (cg_arrow_interx[0] + cg_arrow_interx[1])/2;
        cg_arrow_v_y[0] = cg_arrow_intery[0] + (cg_arrowh - 1);
        cg_arrow_v_x[1] = cg_arrow_interx[1] + (cg_arrowh - 1);
        cg_arrow_v_y[1] = (cg_arrow_intery[1] + cg_arrow_intery[2])/2;
        cg_arrow_v_x[2] = (cg_arrow_interx[2] + cg_arrow_interx[3])/2;
        cg_arrow_v_y[2] = cg_arrow_intery[2] - (cg_arrowh - 1);
        cg_arrow_v_x[3] = cg_arrow_interx[3] - (cg_arrowh - 1);
        cg_arrow_v_y[3] = (cg_arrow_intery[3] + cg_arrow_intery[0])/2;

        for(int i = 0; i < 4; ++i) {
            int next_i = (i+1)%4;
            cg_arrowx[i][0] = cg_arrow_interx[i];
            cg_arrowy[i][0] = cg_arrow_intery[i];
            cg_arrowx[i][1] = cg_arrow_interx[next_i];
            cg_arrowy[i][1] = cg_arrow_intery[next_i];
            cg_arrowx[i][2] = cg_arrow_v_x[i];
            cg_arrowy[i][2] = cg_arrow_v_y[i];
        }

        cg_scoresw = 2*font_mono.stringWidth("1234");
        cg_scoresh = 4*cg_nameh;
        cg_scoresx = cg_w - cg_scoresw;
        cg_scoresy = 0;
        cg_scores_splitx = cg_w - cg_scoresw/2;
        cg_scores_mix = cg_scores_splitx;
        cg_scores_vix = cg_w;
        //cg_scores_tipx = cg_scoresx + cg_scores_offset;
        cg_scores_miviy = 0;
        cg_scores_tip0y = cg_nameh;
        cg_scores_tip1y = 2*cg_nameh;
        cg_scores_tip2y = 3*cg_nameh;

        cg_show_full_scores = false;
        cg_full_scores_arc = 10;
        cg_full_scoresw = 2*cg_full_scores_arc + 2*font_mono.stringWidth(" 1234");
        cg_full_scoresh = cg_h - 4;
        cg_full_scoresx = (cg_w - cg_full_scoresw)/2;
        cg_full_scoresy = (cg_h - cg_full_scoresh)/2;
        cg_full_scores_hcenter = (2*cg_full_scoresx + cg_full_scoresw)/2;
        cg_full_scores_mix = cg_full_scoresx + cg_full_scores_arc + font_mono.stringWidth(" 1234");
        cg_full_scores_vix = cg_full_scoresx + cg_full_scoresw - cg_full_scores_arc;

        cg_zovix = (cg_w - (5*cg_zovi_size + 6*cg_zovi_offset))/2;
        cg_zoviy = cg_handy - (cg_zovi_size + 2*cg_zovi_offset) - 2;//2 je razmak izmedju

        cg_show_zvanje = false;
        cg_zvane_kartex = new int[4];
        cg_zvane_kartey = new int[4];
        for(int i = 0; i < 4; ++i) cg_zvane_kartex[i] = cg_zvane_kartey[i] = 0;
        cg_zvane_kartey[0] = cg_handy - cg_cardh - 2;
        cg_zvane_kartex[1] = cg_w - cg_cardh - 2;
        cg_zvane_kartey[2] = 2;
        cg_zvane_kartex[3] = 2;

        cg_ul_kutw = cg_ul_kuth = cg_namew;


        cg_zvana_bojax = (cg_ul_kutw - cg_zovi_size)/2;
        cg_zvana_bojay = (cg_ul_kuth - cg_monoh - cg_zovi_size)/2;

        cg_namex = new int[4];
        cg_namey = new int[4];

        cg_namex[1] = cg_w - cg_namew;
        cg_namey[1] = (2*cg_trick_posy[1] + cg_cardh + 4)/2;
        cg_namex[2] = (cg_w - cg_namew)/2;
        cg_namey[2] = 0;
        cg_namex[3] = 0;
        cg_namey[3] = (2*cg_trick_posy[3] + cg_cardh + 4)/2;
        if(cg_namey[1] < cg_scoresy+cg_scoresh) {
          cg_namey[1] = cg_namey[3] = cg_scoresy+cg_scoresh;
        }

        player_name = new String[4];
        cg_popis_igraca = new String[4];
        for(int i = 0; i < 4; ++i) {
          //player_name[i] = "Proba"+i;
          player_name[i] = "";
          cg_popis_igraca[i] = ""+i;
        }

        cg_where = new int[4]; //za server je ovak dobro
        for(int i = 0; i < 4; ++i)  cg_where[i] = i;

        //IMAGE INIT

        final String img_prefix = "/images/", img_postfix = ".png";
        img_card = new Image[32];
        img_card_rot = new Image[32];
        img_suit = new Image[5];
        for(int i = 0; i < 32; ++i) {
            String img_name = img_prefix + i + img_postfix;
            String img_name_rot = img_prefix + "r" + i + img_postfix;
            try {
                img_card[i] = Image.createImage(img_name);
                img_card_rot[i] = Image.createImage(img_name_rot);
            } catch (IOException ex) {
                System.out.println("IMAGE LOADING ERROR ("+img_name+"):"+ex);
            }
        }
        for(int i = 0; i < 4; ++i) {
            String img_name = img_prefix + "sm" + i + img_postfix;
            try {
                img_suit[i] = Image.createImage(img_name);
            } catch(IOException ex) {
                System.out.println("SUIT IMAGE LOADING ERROR!");
            }
        }
        try {
            img_suit[4] = Image.createImage(img_prefix + "dalje" + img_postfix);
        } catch(IOException ex) {
            System.out.println("DALJE IMAGE LOADING ERROR!");
        }
        System.out.println("LOADING COMPLETED!");

        //Bluetooth INIT
        service = new String[MAX_DEVICE];
        searchID = new int[MAX_DEVICE];
        conn_server = null;
        n_servers = 0;
        is_server = false;
        has_client_joined = false;
        client_rdy = false;
        moj_server = 0;
        id = -1;
        is_sp = false;
        game_started = false; //dal je igra zapocela
        has_started = false;
        game_over = false;
        server_down = false;
        //zezancija
        br = 0;
        x = 0; y = 0; dx = dy = 20;

        //;
    }
    public void update_cg_where() {
      for(int i = 0; i < 4; ++i)  cg_where[i] = (i + 4 - id)%4;
    }
    public void nova_partija_SP() {
        spil.shuffle();
        ruka_sp = new hand[4];
        for(int i = 0; i < 4; ++i) {
            ruka_sp[i] = new hand();
            /*if(i == 0) ruka_sp[0].nastimano1();
            else if(i == 1) ruka_sp[1].nastimano2();
            else if(i == 2) ruka_sp[2].nastimano3();
            else if(i == 3) ruka_sp[3].nastimano4();*/
            ruka_sp[i].construct_hand(spil, i);
            ruka_sp[i].sort_bf(6);
            ruka_sp[i].check_zvanje();
        }
        cards_dealt = true;
        cg_show_zvanje = true;
        hand_proba = info.get_na_redu();
        repaint();
    }
    public void cheat() {
      if(id == 0) ruka.nastimano1();
      else if(id == 1) ruka.nastimano2();
      else if(id == 2) ruka.nastimano3();
      else if(id == 3) ruka.nastimano4();
    }
    public void nova_partija() {
        cg_show_zvanje = false;
        cards_dealt = false;
        play_card_pressed = false;
        System.out.println("!!!!!!!!!!!!!!!!!!!!!!!!!!("+id+")");
        if(info.is_quick_play()) {
          if(is_server) System.out.println("^^^^^^^^^QUICK^^SERVER");
          else System.out.println("*************QUICK**CLIENT");
        }
        spil.shuffle();
        ruka = new hand();
        int[] a = new int[8];
        if(is_server) {
          System.out.println("Dijelim karte sebi...");
          for(int i = 0; i < 8; ++i)
            a[i] = spil.get_kth(i).get_id();
          ruka.construct_hand(a);
          //cheat(); //ovo MAKNUTI
          System.out.println("Podijelio sebi!");
          ruka.sort_bf(6);
          cards_dealt = true;
          repaint();
          System.out.println("Saljem karte...");
          for(int curr = 0; curr < 3; ++curr) {
            for(int i = 0; i < 8; ++i)
              a[i] = spil.get_kth(8*(curr+1) + i).get_id();
            System.out.println("Saljem deck clientu "+curr);
            String s = array_to_str(a, 8);
            send_msg_to_client(deal_msg+s, curr);
            System.out.println("Poslao ruke clientu "+curr);
          }
          System.out.println("Gotovo slanje decka!");
        }
        else {
            System.out.println("Cekam da dobijem karte...");
            String msg = read_from_server();
            String cmd = get_msg_type(msg);
            String s = get_msg_text(msg);
            System.out.println("Cekam Karte, tip poruke: "+cmd);
            System.out.println("Karte str: "+s);
            str_to_array(a, s);
            ruka.construct_hand(a);
            //cheat(); //ovo MAKNUTI
            System.out.println("Dobio sam.");
            ruka.sort_bf(6);
        }
        cards_dealt = true;
        //cg_show_zvanje = true;
        repaint();
    }
    public void sredi_game_over() {
      cg_show_full_scores = true;
      game_over = true;
      repaint();
    }
    public void sredi_turn(int card_id) {
        cg_trick_card_id[ info.get_trick_size() ] = card_id;
        info.play_card(new karta(card_id));
        ready_end_turn = true;
        if(info.is_end_trick()) {
            info.save_end_trick();
            if(info.is_end_partija()) {
                info.save_results();
                info.reset();
                if(info.game_over()) sredi_game_over();
                else nova_partija();
            }
            ready_end_turn = false;
        }
    }
    public void autoplay() {
      if(!info.jel_odigravanje()) return ;
      if(server_pressed || play_card_pressed) return ;
      int which = 0, cnt = 0;
      for(int i = 0; i < 8; ++i) {
        if(ruka.used_kth(i)) continue;
        if(allowed_to_play[i]) {
          ++cnt;
          which = i;
        }
      }
      if(cnt != 1) return ;

      karta autoplay_card = ruka.get_kth(which);
      boolean bela_card = false;
      if(ruka.get_bela() && ruka.bela_possible() && ruka.is_bela_kth(which))
        bela_card = true;
      ruka.play_card(which);
      if(is_server) {
        send_msg_to_all(card_msg+autoplay_card.get_id());
        if(bela_card) {
          info.update_bela(id);
          send_msg_to_all(bela_msg+id);
        }
        sredi_turn(autoplay_card.get_id());
        server_pressed = true;
      }
      else {
        send_msg_to_server(card_msg+autoplay_card.get_id());
        if(bela_card) {
          send_msg_to_server(bela_msg+id);
        }
        play_card_pressed = true;
      }
    }
    public void novo_adut(int adut) {
        ruka.update_adut(adut);
        ruka.sort_bf(8);
        info.update_adut(adut, hand_proba);
        info.update_zvan_adut(true);
        info.update_zvanje_select(true);
        info.set_first_turn();
        ruka.check_zvanje();
        if(!info.is_brutal_play()) {//ako nije brutal ukljuci belu
          if(ruka.bela_possible())
            ruka.update_bela(true);
        }
    }
    public void set_brutal_play() { info.set_brutal_play(); }
    public void set_quick_play() { info.set_quick_play(); }
    public void novo_odigravanje_SP() {
        //update zvanja od teama tj. od oba igraca koji su dobili zvanje
        if(info.get_zvanje_tko() != -1) {
          int prvi = info.get_zvanje_tko()&1, drugi = (info.get_zvanje_tko()&1) + 2;
          info.save_zvanje_team(ruka_sp[prvi].get_zvanje_tot_val(), 0,
            ruka_sp[prvi].get_array_koje_karte(), ruka_sp[prvi].get_broj_karata());
          info.save_zvanje_team(ruka_sp[drugi].get_zvanje_tot_val(), 1,
            ruka_sp[drugi].get_array_koje_karte(), ruka_sp[drugi].get_broj_karata());
        }
        info.update_zvanje_select(false);
        info.set_first_turn();
        cg_show_zvanje = true;
    }
    public void novo_odigravanje_MP() {
        //update zvanja od teama tj. od oba igraca koji su dobili zvanje
        if(info.get_zvanje_tko() != -1) {
          int prvi = info.get_zvanje_tko()&1, drugi = (info.get_zvanje_tko()&1) + 2;
          info.save_zvanje_team(info.get_sva_zvanja_score(prvi), 0,
            info.get_array_sva_zvanja(prvi), info.get_sva_zvanja_size(prvi));
          info.save_zvanje_team(info.get_sva_zvanja_score(drugi), 1,
            info.get_array_sva_zvanja(drugi), info.get_sva_zvanja_size(drugi));
        }
        info.update_zvanje_select(false);
        info.set_first_turn();
        cg_show_zvanje = true;
    }
    public String get_msg_type(String s) {
        if(s.length() < 4) return unk_msg;
        return s.substring(0, 4);
    }
    public String get_msg_text(String s) {
        return s.substring(s.indexOf('_')+1);
    }
    public boolean already_started() { return has_started; }
    public boolean client_ready() { return client_rdy; }
    public boolean is_client() { return !is_server; }
    public boolean client_joined() { return has_client_joined; }
    public boolean has_game_started() { return game_started; }
    public boolean na_redu_sam() { return info.get_na_redu() == id; }
    public void set_game_started() { game_started = true; log.push_msg("Game started!"); }
    public void set_server() { is_server = true; }
    public void set_started() { has_started = true; }
    public void set_single_player() { is_sp = true; game_started = true; }
    public void update_ime(String s) { ime = s; }
    public void update_id(int x) { id = x; for(int i = 0; i < 4; ++i)  cg_where[i] = (i + 4 - id)%4; }
    public void update_moj_server(int x) { moj_server = x; }
    public int get_moj_server() { return moj_server; }
    public int wait_for_response_server(int current_client) {
        try {
            System.out.println(RFCOMM_UUID + "===Cekam msg od Clienta  "+current_client);
            String response = read_msg_from_client(current_client);
            System.out.println(">>Poruka od clienta: "+response);
            String cmd = get_msg_type(response);
            String msg = get_msg_text(response);
            System.out.println("((("+cmd+" "+msg);
            if( cmd.equals(disconnect_msg) ) return -1;
            else if(cmd.equals(dalje_msg)) {
              //System.out.println("DALJEE od servera.");
              info.next_turn();
              send_msg_to_all(response);
            }
            else if(cmd.equals(adut_msg)) {
              novo_adut(Integer.parseInt(msg));
              send_msg_to_all(response);
            }
            else if(cmd.equals(zvanje_max_msg))
              zv_max = Integer.parseInt(msg);
            else if(cmd.equals(zvanje_max_sec_msg))
              zv_max_sec = Integer.parseInt(msg);
            else if(cmd.equals(zvanje_tko_msg))
              zv_tko = Integer.parseInt(msg);
            else if(cmd.equals(zvanje_score_msg))
              zv_score = Integer.parseInt(msg);
            else if(cmd.equals(zvanje_koje_msg)) {
              zv_koje_karte_size = msg.length()/2;
              zv_koje_karte = new int[zv_koje_karte_size];
              str_to_array(zv_koje_karte, msg);
            }
            else if(cmd.equals(zvanje_sel_end_msg))
              sredi_zvanje_server();
            else if(cmd.equals(novo_odigravanje_msg)) {
              System.out.println("NOVO ODIGRAVANJE NA SERVERU!"
              +info.get_zvanje(0) +" "+info.get_zvanje(1) );
              send_msg_to_all(response);
              novo_odigravanje_MP();
            }
            else if(cmd.equals(card_msg)) {
              send_msg_to_all(response);
              sredi_turn(Integer.parseInt(msg));
            }
            else if(cmd.equals(bela_msg)) {
              info.update_bela(Integer.parseInt(msg));
              send_msg_to_all(response);
            }
        } catch (Exception ex) {
            System.err.println("IGRA u tijeku Running Error: " + ex);
            log.push_error("Unable to receive msg from client "+current_client+": "+ex);
        }
        return 0;
    }
    public int get_first_open_slot() {
      for(int i = 0; i < 4; ++i)
        if(conn_to_client[i] == null) return i;
      return -1;
    }
    public boolean is_open_slot(int x) { return conn_to_client[x] == null; }
    public int wait_for_client_join() {
        int ret = 0, current_client = get_first_open_slot();
        System.out.println("Prvi slot = "+current_client);
        try {
            System.out.println(RFCOMM_UUID + "...Wating for "+ current_client);
            // Pauses thread until Transmission occurs
            conn_to_client[current_client] = notifier.acceptAndOpen();
            //otvaranje streamova prema clientu
            out_stream[current_client] = conn_to_client[current_client].openOutputStream();
            in_stream[current_client] = conn_to_client[current_client].openInputStream();
            System.out.println("Msg received...");
            // Read Data Transmission
            String msg = read_msg_from_client(current_client);
            String cmd = null, s = null;
            if(msg.indexOf('_') >= 0) {
                cmd = get_msg_type(msg);
                s = get_msg_text(msg);
                System.out.println(">>>>Naredba:"+cmd+"!");
                System.out.println("Ime:"+s+"!");
            }
            System.out.println("Poruka od Client "+s+"("+cmd+s);
            if(cmd == null) {
                System.err.println("Error u citanju!!!!!");
                close_conn_to_client(current_client);
                return 0;
            }
            else if(cmd.equals(welcome_msg)) {
                System.out.println("To je bila welcome poruka");
                String wmsg = welcome_msg+ime+get_first_open_slot();
                System.out.println("To client "+s+ ": "+wmsg);
                send_msg_to_client(wmsg, current_client);
                System.out.println("Poslao poruku clientu "+s);
                close_conn_to_client(current_client);
            }
            else if(cmd.equals(join_confirm_msg)) {
                player_name[current_client+1] = s;
                System.out.println("################");
                for(int i = 0; i < 4; ++i)
                   System.out.println("# "+player_name[i]);
                System.out.println("################");
                System.out.println(s+" se netko JOINAO");
                log.push_msg("Player#"+current_client+"JOINED: Name: "+s);
                joined_list.delete(current_client);
                joined_list.insert(current_client, s, null);
                String jmsg = join_confirm_msg+(current_client+1);
                //for(int i = 0; i < 3; ++i) {
                  //jmsg += "_";
                  //if(!is_open_slot(i)) jmsg += player_name[i+1];
                //}
                //jmsg += "_";
                send_msg_to_client(jmsg, current_client);
                ret = 1;
            }
            else if(cmd.equals(disconnect_msg)) {
                int tko = Integer.parseInt(s) - 1;
                System.out.println(joined_list.getString(tko)+" je otisao");
                set_free_slot(tko);
                close_conn_to_client(current_client);
                if(tko != current_client) close_conn_to_client(tko);
                ret = -1;
            }
        } catch (Exception ex) {
            System.err.println("Bluetooth Server Running Error: " + ex);
            log.push_error("Opening connection to client: "+ex);
        }
        return ret;
    }
    public void set_free_slot(int wh) {
      joined_list.delete(wh);
      joined_list.insert(wh, open_slot, null);
    }
    public void notify_kicked(int wh) {
      player_name[wh+1] = "";
      send_msg_to_all(update_ime_msg+(wh+1));
      send_msg_to_client(kick_msg, wh);
    }
    public void notify_game_started() {
      for(int i = 0; i < 3; ++i) {
        //for(int wh = 0; wh < 4; ++wh)
          //send_msg_to_client(update_ime_msg+player_name[wh], i);
        String tip_igre = null;
        if(info.is_brutal_play()) tip_igre = "B";
        else if(info.is_quick_play()) tip_igre = "Q";
        else tip_igre = "N";
        send_msg_to_client(game_started_msg+tip_igre, i);
      }
    }
    public void pause_end_turn() {
        try {
            runner.sleep(500);
        } catch(Exception e) { log.push_error("Timer: "+e); }
    }
    public void igraj() {
        quit = false;
        runner = new Thread(this);
        runner.start();
    }
    public String array_to_str(int[] a, int k) {
        String ret = "";
        for(int i = 0; i < k; ++i)  ret += a[i] + char_offset;
        return ret;
    }
    public void str_to_array(int[] a, String s) {
        int k = s.length();
        for(int i = 0; i < k; i+=2)
          a[i/2] = Integer.parseInt(s.substring(i, i+2)) - char_offset;
    }
    public void sredi_zvanje_server() {
      info.update_zvanje(zv_max, zv_max_sec, zv_tko, zv_score);
      info.save_sva_zvanja(zv_koje_karte, zv_koje_karte_size, zv_tko, zv_score);

      send_msg_to_all(zvanje_max_msg + zv_max);
      send_msg_to_all(zvanje_max_sec_msg + zv_max_sec);
      send_msg_to_all(zvanje_tko_msg + zv_tko);
      send_msg_to_all(zvanje_score_msg + zv_score);
      send_msg_to_all(zvanje_koje_msg + array_to_str(zv_koje_karte, zv_koje_karte_size));
      send_msg_to_all(zvanje_sel_end_msg);

      if(zv_tko == info.get_dealer()) {
        send_msg_to_all(novo_odigravanje_msg);
        novo_odigravanje_MP();
      }
      else info.next_turn();
    }
    public void sredi_join(String msg) {
      System.out.println("EJJJJJJJJJJJJJJJJ");
      String s = server_list.getString(moj_server);
      cg_popis_igraca[id] = s;
      int last = 1, curr = 1;
      for(int i = 1; i < msg.length() && curr < 4; ++i) {
        if(msg.charAt(i) == '_') {
          cg_popis_igraca[curr++] = msg.substring(last, i);
          last = i+1;
        }
      }
      repaint();
    }
    public void run() {
        has_started = true;
        max_players = 4;
        System.out.println("Run...\n");
        log.push_msg("RUN function initiated...");
        if(is_server || is_sp) start_server();
        else if(!is_sp) start_client();
        repaint();
        if(is_server && !is_sp) {
            System.out.println("Sada se treba joinat 4 igraca");
            log.push_msg("Waiting for 3 clients to join...");
            int client_joined = 0;
            while(client_joined < max_players-1) {
                int delta = wait_for_client_join();
                client_joined += delta;
                if(delta != 0) {
                  for(int i = 0; i < 4; ++i) {
                    send_msg_to_all(update_ime_msg+i+player_name[i]);
                  }
                }
            }
            System.out.println("Server je spreman, stisni Kreni!");
            log.push_msg("SERVER READY to start! Press Kreni...");
            while(!game_started) {
                 try {
                    runner.sleep(100);
                } catch(Exception e) { log.push_error("Timer: "+e); }
            }
            notify_game_started();
            System.out.println("Pocetak IGRE SERVERA..");
            nova_partija();
            while(!quit) {
                /*try {
                    runner.sleep(30);
                } catch(Exception e) { }
                x += 20; y += 10;
                if(x > 200) x = 0;
                if(y > 200) y = 0;
                repaint();*/
                if(na_redu_sam()) {
                  server_pressed = false;
                  //if(info.is_autoplay()) autoplay(); //odigraj autoplay ako mozes
                  while(!server_pressed) {
                    try {
                      runner.sleep(100);
                    } catch(Exception e) { log.push_error("Timer: "+e); }
                  }
                }
                else if( wait_for_response_server(info.get_na_redu()-1) == -1) {
                  System.out.println("Treba iskljucit server...");
                  send_msg_to_all(disconnect_msg);
                  server_down = true;
                  g.setColor(0x0000FF);
                  repaint();
                  end_server();
                }
                repaint();
            }
            System.out.println("GAME OVER na SERVERU!");
        }
        else if(!is_sp) {//ako je client
            while(!has_client_joined) {
                 try {
                    runner.sleep(100);
                } catch(Exception e) { log.push_error("Timer: "+e); }
            }
            System.out.println("CITANJE!!!!!");
            while(!quit) {
                System.out.println("Cekam da mi server nesto posalje..." );
                String msg = read_from_server();
                System.out.println(">>("+id+"(From server: "+ msg );
                String cmd = get_msg_type(msg);
                msg = get_msg_text(msg);
                if(cmd.equals(join_confirm_msg)) {
                  update_id(Integer.parseInt(msg.substring(0, 1)));
                  //sredi_join(msg.substring(1));
                }
                else if(cmd.equals(disconnect_msg)) {
                  server_down = true;
                }
                else if(cmd.equals(kick_msg)) {
                  notify_left_server();
                  log.push_msg("Kicked from the server!");
                  System.out.println("Kickan sam");
                }
                else if(cmd.equals(update_ime_msg)) {
                  int wh = Integer.parseInt(msg.substring(0, 1));
                  cg_popis_igraca[wh] = player_name[wh] = msg.substring(1);
                }
                else if(cmd.equals(game_started_msg)) {
                  set_game_started();
                  if(msg.equals("B")) set_brutal_play();
                  else if(msg.equals("Q")) set_quick_play();
                  nova_partija();
                   System.out.println("$$$$$$$$$$$"+msg.substring(0, 1));

                  for(int i = 0; i < 4; ++i)
                    System.out.println("$ "+player_name[i]);
                  System.out.println("$$$$$$$$$$$");
                }
                else if(cmd.equals(adut_msg)) {
                  novo_adut(Integer.parseInt(msg));
                }
                else if(cmd.equals(dalje_msg)) {
                  //System.out.println("DAlje od servera.("+id+")");
                  info.next_turn();
                }
                else if(cmd.equals(zvanje_max_msg)) {
                  System.out.println("Primam zvanje max("+id+")");
                  zv_max = Integer.parseInt(msg);
                }
                else if(cmd.equals(zvanje_max_sec_msg)) {
                  //System.out.println("Primam zvanje max Sec("+id+")");
                  zv_max_sec = Integer.parseInt(msg);
                }
                else if(cmd.equals(zvanje_tko_msg)) {
                  //System.out.println("Primam zvanje max("+id+")");
                  zv_tko = Integer.parseInt(msg);
                }
                else if(cmd.equals(zvanje_score_msg)) {
                   //System.out.println("Primam zvanje Tot("+id+")");
                   zv_score = Integer.parseInt(msg);
                   System.out.println("||||||||||("+zv_score+")"+Integer.parseInt(msg));
                }
                else if(cmd.equals(zvanje_koje_msg)) {
                  //System.out.println("Primam zvanje Array("+id+")");
                  zv_koje_karte_size = msg.length()/2;
                  zv_koje_karte = new int[zv_koje_karte_size];
                  str_to_array(zv_koje_karte, msg);
                }
                else if(cmd.equals(zvanje_sel_end_msg)) {
                  System.out.println("+++++++UPDATE zvanja("+id+")");
                  info.update_zvanje(zv_max, zv_max_sec, zv_tko, zv_score);
                  info.save_sva_zvanja(zv_koje_karte, zv_koje_karte_size, zv_tko, zv_score);
                  info.next_turn();
                }
                else if(cmd.equals(novo_odigravanje_msg)) {
                  System.out.println("O D I G R A V A N J E ("+id+")"
                    +info.get_zvanje(0) +" "+info.get_zvanje(1) );
                  novo_odigravanje_MP();
                }
                else if(cmd.equals(card_msg)) {
                  sredi_turn(Integer.parseInt(msg));
                  play_card_pressed = false;
                }
                else if(cmd.equals(bela_msg)) {
                  info.update_bela(Integer.parseInt(msg));
                }
                repaint();
            }
        }
        else {//single player
           nova_partija_SP();
           try { StreamConnection conn = notifier.acceptAndOpen();
           } catch(Exception ex) { System.out.println("SP server error: "+ex); }
        }
    }
    public void destroy() {
        game_started = false;
        has_started = false;
        quit = true;
    }
    public void draw_SP(Graphics g) {
        draw_scores(g);
        if(cards_dealt) {
          if(info.jel_zvano()) {
            draw_ul_kut(g);
            if(info.jel_zvanje_select()) {
              draw_hand_SP(g, 8);
              draw_zvanje_select_SP(g);
            }
            else {
              draw_hand_SP(g, 8);
              draw_trick(g);
              if(cg_show_zvanje)
                draw_zvanje(g);
            }
          }
          else {
            draw_hand_SP(g, 6);
            draw_zovi(g);
          }
          draw_arrow(g);
        }
        draw_names(g);
    }
    public void draw_MP(Graphics g) {
        draw_scores(g);
        if(cards_dealt) {
          if(info.jel_zvano()) {
            draw_ul_kut(g);
            draw_hand_MP(g, 8);
            if(info.jel_zvanje_select()) {
              if(na_redu_sam())
                draw_zvanje_select_MP(g);
            }
            else {
              draw_trick(g);
              if(cg_show_zvanje)
                draw_zvanje(g);
            }
          }
          else {
            draw_hand_MP(g, 6);
            if(na_redu_sam()) draw_zovi(g);
          }
          draw_arrow(g);
        }
        draw_names(g);
    }
    public void paint(Graphics g) {
        if(!game_started) {
          draw_popis_igraca(g);
          return ;
        }
        g.setColor(0xFFFFFF);
        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(cg_table_color);
        g.fillRect(0, 0, cg_w, cg_h);
        g.setColor(0xFFFFFF);
        g.fillRect(0, 0, cg_ul_kutw, cg_ul_kuth);


        g.setColor(0x000000);


        if(is_sp) draw_SP(g);
        else draw_MP(g);


        if(na_redu_sam()) {
          g.setColor(0x0000FF);
          g.fillRoundRect(cg_w-20, cg_h-20, 20, 20, 5, 5);
        }
        if(server_down) {
          g.fillRect(0, 0, cg_w, cg_h);
        }
        if(cg_show_full_scores)
          draw_full_scores(g);
    }
    public void keyPressed_MP(int keyCode) {
        //
        if(info.jel_zvano()) {
         if(info.jel_zvanje_select()) {
            for(int i = 1; i <= 5; ++i)
              if(keyCode == keynum[i]) {
                if(i <= ruka.get_zvanje_4_size() + ruka.get_zvanje_size()) {
                  boolean state = ruka.get_ignore_zvanje(i-1);
                  ruka.update_ignore_zvanje(i-1, state ^ true); //switch on/off
                }
                if(i == 5) {//saveaj sta netko hoce zvat i endaj turn
                  ruka.submit_zvanje();

                  if(is_server) {
                    send_msg_to_all(zvanje_max_msg + ruka.get_zvanje_max());
                    send_msg_to_all(zvanje_max_sec_msg + ruka.get_zvanje_max_sec());
                    send_msg_to_all(zvanje_tko_msg + id);
                    send_msg_to_all(zvanje_score_msg + ruka.get_zvanje_tot_val());
                    send_msg_to_all(zvanje_koje_msg + array_to_str(ruka.get_array_koje_karte(),
                      ruka.get_broj_karata()) );
                    send_msg_to_all(zvanje_sel_end_msg);

                    info.update_zvanje(ruka.get_zvanje_max(),
                      ruka.get_zvanje_max_sec(), info.get_na_redu(),
                      ruka.get_zvanje_tot_val() );
                    info.save_sva_zvanja(ruka.get_array_koje_karte(), ruka.get_broj_karata(),
                      id, ruka.get_zvanje_tot_val());

                    if(id == info.get_dealer()) {
                      System.out.println("SERVER ODIGRAVANJE "
                        +info.get_zvanje(0) +" "+info.get_zvanje(1) );
                      send_msg_to_all(novo_odigravanje_msg);
                      novo_odigravanje_MP();
                    }
                    else info.next_turn();
                  }
                  else {
                    send_msg_to_server(zvanje_max_msg + ruka.get_zvanje_max());
                    send_msg_to_server(zvanje_max_sec_msg + ruka.get_zvanje_max_sec());
                    send_msg_to_server(zvanje_tko_msg + id);
                    send_msg_to_server(zvanje_score_msg + ruka.get_zvanje_tot_val());
                    send_msg_to_server(zvanje_koje_msg + array_to_str(ruka.get_array_koje_karte(),
                      ruka.get_broj_karata()) );
                    send_msg_to_server(zvanje_sel_end_msg);
                  }

                }
              }
         }
         else {
          //provjeri dal si bacio kartu
          for(int i = 1; i <= 8; ++i)
            if(keyCode == keynum[i]) {
                if( ruka.used_kth(i-1) ) break;
                if( !allowed_to_play[i-1] ) break;
                if( play_card_pressed ) break; //ako si vec stisnuo onda nista
                play_card_pressed = true;
                boolean bela_card = false;
                if(ruka.get_bela() && ruka.bela_possible() && ruka.is_bela_kth(i-1))
                  bela_card = true;
                ruka.play_card(i-1);
                if(is_server) {
                  send_msg_to_all(card_msg+ruka.get_kth(i-1).get_id());
                  if(bela_card) {
                    info.update_bela(id);
                    send_msg_to_all(bela_msg+id);
                  }
                  sredi_turn(ruka.get_kth(i-1).get_id());
                  play_card_pressed = false;
                }
                else {
                  send_msg_to_server(card_msg+ruka.get_kth(i-1).get_id());
                  if(bela_card) send_msg_to_server(bela_msg+id);
                }
            }
          if(keyCode == keynum[0]) {
            if(ruka.bela_possible()) {
              ruka.update_bela(ruka.get_bela() ^ true);
            }
          }
         }
        }
        else {
            //pogledaj dal zoves
            for(int i = 1; i <= 5; ++i)
              if(keyCode == keynum[i]) {
                if(i == 1 && info.get_na_redu() == info.get_dealer()) break;
                if(i == 1) {//ako je netko rekao Dalje
                  if(is_server) {
                    info.next_turn();
                    send_msg_to_all(dalje_msg);
                  }
                  else {
                    //System.out.println("SALJEM DALJE ("+id+")");
                    send_msg_to_server(dalje_msg);
                  }
                }
                else {
                    int adut = i-2;
                    if(is_server) {
                      novo_adut(adut);
                      send_msg_to_all(adut_msg+adut);
                    }
                    else {
                      send_msg_to_server(adut_msg+adut);
                    }
                }
              }
        }
        if(is_server) server_pressed = true;
        System.out.println("MP press("+id+")");
    }
    public void keyPressed_SP(int keyCode) {
        if( keyCode == KEY_NUM9) {
            hand_proba = (hand_proba+1)%4;
            //ruka_sp.construct_hand(spil, hand_proba);
        }
        else if( keyCode == KEY_NUM0) {
            info.reset();
            nova_partija_SP();
        }
        if(info.jel_zvano()) {
         if(info.jel_zvanje_select()) {
            for(int i = 1; i <= 5; ++i)
              if(keyCode == keynum[i]) {
                if(i <= ruka_sp[hand_proba].get_zvanje_4_size() + ruka_sp[hand_proba].get_zvanje_size()) {
                  boolean state = ruka_sp[hand_proba].get_ignore_zvanje(i-1);
                  ruka_sp[hand_proba].update_ignore_zvanje(i-1, state ^ true); //switch on/off
                }
                if(i == 5) {//saveaj sta netko hoce zvat i endaj turn
                  ruka_sp[hand_proba].submit_zvanje();
                  info.update_zvanje(ruka_sp[hand_proba].get_zvanje_max(),
                      ruka_sp[hand_proba].get_zvanje_max_sec(), info.get_na_redu(),
                      ruka_sp[hand_proba].get_zvanje_tot_val() );
                  if(info.get_na_redu() == info.get_dealer()) {
                    novo_odigravanje_SP();
                  }
                  else info.next_turn();
                  hand_proba = info.get_na_redu();
                }
              }
         }
         else {
          //provjeri dal si bacio kartu
          for(int i = 1; i <= 8; ++i)
            if(keyCode == keynum[i]) {
                if( ruka_sp[hand_proba].used_kth(i-1) ) break;
                if( !allowed_to_play[i-1] ) break;
                ruka_sp[hand_proba].play_card(i-1);
                cg_trick_card_id[ info.get_trick_size() ] = ruka_sp[hand_proba].get_kth(i-1).get_id();
                info.play_card( ruka_sp[hand_proba].get_kth(i-1) );
                ready_end_turn = true;
                if(info.is_end_trick()) {
                  info.save_end_trick();
                  if(info.is_end_partija()) {
                    info.save_results();
                    info.reset();
                    if(info.game_over()) sredi_game_over();
                    else nova_partija_SP();
                  }
                  ready_end_turn = false;
                }
                hand_proba = info.get_na_redu();
            }
           }
        }
        else {
            //pogledaj dal zoves
            for(int i = 1; i <= 5; ++i)
              if(keyCode == keynum[i]) {
                if(i == 1 && info.get_na_redu() == info.get_dealer()) break;
                if(i == 1) {
                  info.next_turn();
                }
                else {
                    int adut = i-2;
                    for(int j = 0; j < 4; ++j) {
                        ruka_sp[j].update_adut(adut);
                        ruka_sp[j].sort_bf(8);
                    }
                    info.update_adut(adut, hand_proba);
                    info.update_zvan_adut(true);
                    info.update_zvanje_select(true);
                    info.set_first_turn();
                    for(int j = 0; j < 4; ++j)
                      ruka_sp[j].check_zvanje();
                }
              }
            hand_proba = info.get_na_redu();
        }
    }
    public void keyPressed(int keyCode) {

		// what game action does this key map to?
		int gameAction = getGameAction(keyCode);
        if(game_started) {
          if(is_sp)  keyPressed_SP(keyCode);
          else if(na_redu_sam())  keyPressed_MP(keyCode);
          else System.out.println("BUG!");
        }
        else {
        }
        if(keyCode == KEY_POUND) {
           if(info.jel_odigravanje())
             cg_show_zvanje ^= true;
        }
        else if(keyCode == KEY_STAR) {
          if(cards_dealt)
            cg_show_full_scores ^= true;
        }
		/*if(gameAction == RIGHT) {
			x += dx;
		} else if(gameAction == LEFT) {
			x -= dx;
		} else if(gameAction == UP) {
			y -= dy;
		} else if(gameAction == DOWN) {
			y += dy;
		}
		else if(gameAction == GAME_A) {
            System.out.println("GAME_A");
            if(!is_server) {
                if( client_rdy ) {
                    System.out.println("Saljem poruku na "+moj_server+". server...");
                    send_msg_to_server(info_msg+ime);
                }
                else System.out.println("Nije jos moguce poslat poruku.");
            }
            else {
                System.out.println("Saljem poruku na Client0");
                send_msg_to_client(info_msg+"SERVER PORUKA "+br, 0);
            }
		}*/
        System.out.println("Stisnuo si nesto "+(++br)+". put");
		// make sure to repaint
		repaint();
	}
	//KOMUNIKACIJSKE FUNKCIJE

	//start server/client functions
    public void start_server() {
        log.push_msg("Starting Server...");
        id = 0;
        player_name[0] = ""+ime;
        out_stream = new OutputStream[4];
        in_stream = new InputStream[4];
        conn_to_client = new StreamConnection[4];
        for(int i = 0; i < 4; ++i) {
            conn_to_client[i] = null;
            out_stream[i] = null;
            in_stream[i] = null;
            if(i == 3) joined_list.append("JA", null);
            else joined_list.append(open_slot, null);
        }
        try {
            localDevice = LocalDevice.getLocalDevice();

            localDevice.setDiscoverable( DiscoveryAgent.GIAC );
            notifier = (StreamConnectionNotifier)Connector.open(serverUrl);
        } catch (BluetoothStateException e) {
          System.err.println( "BluetoothStateException: " + e.getMessage() );
          log.push_error("BT State Exc: "+e.getMessage());
        } catch (IOException e) {
          System.err.println( "IOException: " + e.getMessage() );
          log.push_error("Start server (Bluetooth)");
        }
        System.out.println( "Starting Echo Server" );
        log.push_msg("Starting Server COMPLETED!");
    }
    public void start_client() {
        log.push_msg("Starting client...");
        try {
            //postavi da trazi samo ove UUIDove
            uuidSet = new UUID[1];
            uuidSet[0] = RFCOMM_UUID;

            LocalDevice localDevice = LocalDevice.getLocalDevice();
            discoveryAgent = localDevice.getDiscoveryAgent();
            discoveryAgent.startInquiry(DiscoveryAgent.GIAC, this);
        } catch (Exception e) {
            System.out.println(e);
            log.push_error("Start client: "+e);
        }
        log.push_msg("Starting client COMPLETED!");
    }
    //end server/client functions
    public void end_server() {
        send_msg_to_all(disconnect_msg);
        for(int i = 0; i < 4; ++i)
          close_conn_to_client(i);
        destroy();
    }
    public void close_conn_to_client(int current_client) {
      try {
        if(out_stream[current_client] != null) out_stream[current_client].close();
        if(in_stream[current_client] != null) in_stream[current_client].close();
        out_stream[current_client] = null;
        in_stream[current_client] = null;
      }
      catch(IOException ex) {
        System.out.println("GRESKA u zatvaranju streamova!"+ex);
        log.push_error("Closing streams to client "+current_client+": "+ex);
      }
      finally {
        try {
          System.out.println("Probam Zatvaram konekciju prema klientu "+current_client);
      	  if(conn_to_client[current_client] != null) {
      	    System.out.println("ZATVARAM...");
            conn_to_client[current_client].close();
            System.out.println("ZATVARENO!!!");
            conn_to_client[current_client] = null;
          }
      	} catch (IOException ioe) {
      	  System.out.println("Greska Closing connection " + ioe);
      	  log.push_error("Closing connection to client "+current_client+": "+ioe);
        }
      }
    }
    public void close_conn_to_server() {
      if(conn_server != null) {
            try { out_stream_server.close(); in_stream_server.close(); }
            catch(IOException ex) {
              System.out.println("Error zatvaranje in/out str prema serveru:"+ex);
              log.push_error("Closing streams to server: "+ex);
            }
            try { conn_server.close(); }
            catch(IOException ex) {
              System.out.println("Error zatvaranje konekcije prema serveru:"+ex);
              log.push_error("Closing connection to server: "+ex);
            }
            finally {conn_server = null; }
      }
    }
	//Bluetooth functions
    public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
      log.push_msg("Starting BT Inquiry...");
      try {
        // Get Device Info
        System.out.println("Device Discovered");
        //System.out.println("Major Device Class: " + cod.getMajorDeviceClass() + " Minor Device Class: " + cod.getMinorDeviceClass());
        //System.out.println("Bluetooth Address: " + btDevice.getBluetoothAddress());
        System.out.println("Bluetooth Friendly Name: " + btDevice.getFriendlyName(true));

        // Search for Services
        System.out.println("Sada pocinje trazenje servisa " + n_servers + ". uredjaja");
        searchID[n_servers] = discoveryAgent.searchServices(null,uuidSet,btDevice,this);
        } catch (Exception e) {
          System.out.println("Device Discovered Error: " + e);
          log.push_error("Device Discovered: "+e);
        }
    }
      public void inquiryCompleted(int discType) {
    System.out.println("InquiryCompleted");
    log.push_msg("BT Inquiry COMPLETED!");
  }

  public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
    System.out.println("ServicesDiscovered");
    log.push_msg("Service Discovered!");
    //in this example there is only one service
    service[ n_servers ] = servRecord[0].getConnectionURL(0,false);

    ++n_servers;
  }

  public void serviceSearchCompleted(int transID, int responseCode) {
    if(responseCode == SERVICE_SEARCH_ERROR)
      System.out.println("SERVICE_SEARCH_ERROR\n");

    if(responseCode == SERVICE_SEARCH_COMPLETED) {
      System.out.println("SERVICE_SEARCH_COMPLETED\n");
      System.out.println("Service URL: " + service[0]);
      log.push_msg("SERVICE_SEARCH_COMPLETED!");

      StreamConnection conn = null;
      //tu treba poslat poruku
      System.out.println("Tu treba sad poslat poruku");
      client_rdy = true;
      send_welcome_msg(welcome_msg+ime, 0);
    }

    if(responseCode == SERVICE_SEARCH_TERMINATED) {
      System.out.println("SERVICE_SEARCH_TERMINATED\n");
      log.push_error("SERVICE_SEARCH_TERMINATED");
    }
    if(responseCode == SERVICE_SEARCH_NO_RECORDS) {
      System.out.println("SERVICE_SEARCH_NO_RECORDS\n");
      log.push_error("SERVICE_SEARCH_NO_RECORDS");
    }
    if(responseCode == SERVICE_SEARCH_DEVICE_NOT_REACHABLE) {
      System.out.println("SERVICE_SEARCH_DEVICE_NOT_REACHABLE\n");
      log.push_error("SERVICE_SEARCH_DEVICE_NOT_REACHABLE");
    }
  }

  //connect and disconnect functions

  public void open_conn_to_server() {
    try {
        System.out.println("Trying to establish connection...");
        conn_server = (StreamConnection)Connector.open(service[moj_server]);
        System.out.println("Otvaranje OUTPUT streama prema serveru...");
        out_stream_server = conn_server.openOutputStream();
        System.out.println("Otvaranje INPUT streama prema serveru...");
        in_stream_server = conn_server.openInputStream();
        System.out.println("Uspio!");
    }
    catch(Exception ex) {
      System.out.println("Open conn to server FAILED!!!"+ex);
      log.push_error("Open conn to server Failed: "+ex);
    }
  }
  public boolean try_to_join() {
        System.out.println("Ulazim u "+moj_server+" ( "+ime+") size = "+ join_confirm_msg.length() );
        log.push_msg("Trying to join server...");
        try {
            open_conn_to_server();
            System.out.println("OK...Now sending a join_confirm_msg...");
            send_msg_to_server(join_confirm_msg+ime);
            has_client_joined = true;
            log.push_msg("SUCCEEDED");
            return true;
        }
        catch(Exception ex) {
          System.out.println("Failed: "+ex);
          log.push_error("FAILED: "+ex);
        }
        return false;
  }
  public void notify_left_server() {
        System.out.println("Leavam iz servera prije pocetka...");
        log.push_msg("Leaving the server...");
        close_conn_to_server();
        open_conn_to_server();
        send_msg_to_server(disconnect_msg+id);
        close_conn_to_server();
  }
  public void notify_disconnected() {
        System.out.println("Izlazim iz" + moj_server);
        send_msg_to_server(disconnect_msg+id);
        close_conn_to_server();
  }

  //send and read functions

  public final static String readData(StreamConnection conn) {

        InputStream input = null;
        byte[] data = null;

        try {
            System.out.println("Pokusavam otvorit INPUT stream...");
            input = conn.openInputStream();
            System.out.println("Uspio!");
            // Probably want to throw an exception if length is not greater then 0
            int length = input.read();
            data= new byte[length];
            length = 0;

            // Assemble data
            while (length != data.length) {
                int ch = input.read(data, length, data.length - length);
                if (ch == -1) {
                    throw new IOException("Can't read data");
                }
                length += ch;
            }

        } catch (IOException e) {
          System.err.println(e);
        } finally {
            // close input stream
            if (input != null) {
            try {
                input.close();
            } catch (IOException e) { }
      }
    }
    String ret = new String(data);
    //ispis poruke
    return ret;
  }
  public void send_welcome_msg(String msg, int where) {
        log.push_msg("Sending welcome msg...");
        boolean ok = true;
        StreamConnection conn = null;
        try {
            conn = (StreamConnection)Connector.open(service[where]);
            OutputStream output = conn.openOutputStream();
            msg = welcome_msg+ime;
            output.write(msg.length());
            output.write(msg.getBytes());
            output.close();
        System.out.println("Welcome_msg SEND! Waiting for response...");
        log.push_msg("SENT. Waiting for response...");
        msg = readData(conn);
        log.push_msg("RECEIVED!");
        System.out.println("Msg from SERVER: " + msg);
        msg = get_msg_text(msg);
        int koji = Integer.parseInt(msg.substring(msg.length()-1));
        server_list.append(msg.substring(0, msg.length()-1)+" ("+koji+")", null);

      } catch (Exception ex) {
      	System.out.println("Send_welcome ERROR:"+ex);
      	log.push_error("Welcom msg: "+ex);
      }
        finally {
      	try {
      	  conn.close();
      	} catch (IOException ioe) {
      	  System.out.println("Error Closing connection " + ioe);
      	  log.push_error("Error closing connection " + ioe);
        }
      }
  }
  public void send_msg_to_server(String msg) {
      try {
        out_stream_server.write(msg.length());
        out_stream_server.write(msg.getBytes());
        out_stream_server.flush(); //posalji poruku
      } catch (Exception ex) {
      	System.out.println(ex);
      	log.push_error("Send msg to server: "+ex);
      }
  }
  public String read_from_server() {
      byte[] data = null;
        try {
            // Probably want to throw an exception if length is not greater then 0
            int length = in_stream_server.read();
            data = new byte[length];
            length = 0;

            // Assemble data
            while (length != data.length) {
                int ch = in_stream_server.read(data, length, data.length - length);
                if (ch == -1) {
                    throw new IOException("Nemogu citati data");
                }
                length += ch;
            }

        } catch (IOException e) {
          System.err.println(e);
          log.push_error("Reading from server: "+e);
        }
        return new String(data);
  }
  public void send_msg_to_client(String msg, int wh) {
      try {
        out_stream[wh].write(msg.length());
        out_stream[wh].write(msg.getBytes());
        out_stream[wh].flush(); //posalji poruku
      } catch (Exception ex) {
      	System.out.println(ex);
      	log.push_error("Sending msg to client: "+ex);
      }
  }
  public String read_msg_from_client(int wh) {
      byte[] data = null;
        try {
            // Probably want to throw an exception if length is not greater then 0
            int length = in_stream[wh].read();
            data = new byte[length];
            length = 0;

            // Assemble data
            while (length != data.length) {
                int ch = in_stream[wh].read(data, length, data.length - length);
                if (ch == -1) {
                    throw new IOException("Nemogu citati data");
                }
                length += ch;
            }

        } catch (IOException e) {
          System.err.println(e);
          log.push_error("Read msg from client: "+e);
        }
        return new String(data);
  }
  public void send_msg_to_all(String msg) {
    for(int i = 0; i < 3; ++i) {
      if(is_open_slot(i)) continue;
      send_msg_to_client(msg, i);
    }
  }
  public void send_array_to_all(String msg_type, int[] a, int a_size) {
    msg_type += array_to_str(a, a_size);
    for(int i = 0; i < 3; ++i)
      send_msg_to_client(msg_type, i);
  }
  //Drawing functions

  //SP
  public void draw_hand_SP(Graphics g, int k) {
    g.setFont(font_prop);
    for(int i = 0; i < k; ++i) {
        if( ruka_sp[hand_proba].used_kth(i) ) continue;
        if( ruka_sp[hand_proba].allowed(i, info.get_trick_size(), info.get_trumped(),
            info.get_first_card(), info.get_highest() ) ) {
            g.setColor(0x000000);
            allowed_to_play[i] = true;
        }
        else {
            g.setColor(0xBBBBBB);
            allowed_to_play[i] = false;
        }
        g.drawImage(img_card[ ruka_sp[hand_proba].get_kth(i).get_id() ], cg_handx+i*cg_hand_offset, cg_handy,
          Graphics.TOP | Graphics.LEFT);
        if(info.jel_odigravanje())
          g.drawString(""+(i+1), cg_handx+i*cg_hand_offset+cg_hand_offset/2,
              cg_handy+cg_cardh, Graphics.HCENTER | Graphics.TOP);
    }
    g.setColor(0x000000);
  }
  public void draw_zvanje_select_SP(Graphics g) {
    int k = ruka_sp[hand_proba].get_broj_karata();
    if(k == 0) return ;
    int last = 0, br = 0;
    cg_zvane_kartex[0] = (cg_w - (k*cg_cardw - (k-1)*(cg_cardw-cg_hand_offset)))/2;
    System.out.println("Zvanje_select::::");
    for(int i = 0; i < ruka_sp[hand_proba].get_zvanje_4_size()+ ruka_sp[hand_proba].get_zvanje_size(); ++i)
      System.out.println(""+ruka_sp[hand_proba].get_ignore_zvanje(i));
    for(int i = 0; i < k; ++i) {
        if(ruka_sp[hand_proba].get_koje_karte(i) != -1)
          g.drawImage(img_card[ ruka_sp[hand_proba].get_koje_karte(i) ], cg_zvane_kartex[0]
          +i*cg_hand_offset, cg_zvane_kartey[0], Graphics.TOP | Graphics.LEFT);
        if(i == 0 || ruka_sp[hand_proba].get_koje_karte(i-1) == -1) last = i;
        if(i+1 == k || ruka_sp[hand_proba].get_koje_karte(i+1) == -1) {
          if(ruka_sp[hand_proba].get_ignore_zvanje(br) == true) {
            g.setColor(0xFF0000);
            //prekrizi one karte koje neces zvat sa crvenom
            g.drawLine(cg_zvane_kartex[0]+last*cg_hand_offset, cg_zvane_kartey[0],
                 cg_zvane_kartex[0]+i*cg_hand_offset+cg_cardw, cg_zvane_kartey[0]+cg_cardh);
            g.drawLine(cg_zvane_kartex[0]+last*cg_hand_offset, cg_zvane_kartey[0]+cg_cardh,
                 cg_zvane_kartex[0]+i*cg_hand_offset+cg_cardw, cg_zvane_kartey[0]);
            g.setColor(0xBBBBBB); //postavi boju sivu
          }
          else g.setColor(0x000000);
          g.drawString(""+(br+1), (cg_zvane_kartex[0]+last*cg_hand_offset
              + cg_zvane_kartex[0]+i*cg_hand_offset+cg_cardw)/2,
            cg_zvane_kartey[0]+cg_cardh, Graphics.HCENTER | Graphics.TOP);
        }
        if(ruka_sp[hand_proba].get_koje_karte(i) == -1) ++br;
    }
  }
  public void draw_hand_MP(Graphics g, int k) {
    g.setFont(font_prop);
    for(int i = 0; i < k; ++i) {
        if( ruka.used_kth(i) ) continue;
        if( ruka.allowed(i, info.get_trick_size(), info.get_trumped(),
            info.get_first_card(), info.get_highest() ) ) {
            g.setColor(0x000000);
            allowed_to_play[i] = true;
        }
        else {
            g.setColor(0xBBBBBB);
            allowed_to_play[i] = false;
        }
        g.drawImage(img_card[ ruka.get_kth(i).get_id() ], cg_handx+i*cg_hand_offset, cg_handy,
          Graphics.TOP | Graphics.LEFT);
        if(info.jel_odigravanje() && na_redu_sam())
          g.drawString(""+(i+1), cg_handx+i*cg_hand_offset+cg_hand_offset/2,
              cg_handy+cg_cardh, Graphics.HCENTER | Graphics.TOP);
    }
    if(ruka.bela_possible()) {
      if(ruka.get_bela()) g.setColor(0x0000FF);
      else g.setColor(0xBBBBBB);
      g.drawString("B", cg_handx, (2*cg_handy+cg_cardh)/2, Graphics.RIGHT | Graphics.BASELINE);
    }
    g.setColor(0x000000);
    if(na_redu_sam() && info.is_autoplay())
      autoplay();
  }
  public void draw_zvanje_select_MP(Graphics g) {
    int k = ruka.get_broj_karata();
    if(k == 0) {
      g.setColor(0x0000FF);
      g.drawString("5 - Dalje", cg_w/2, cg_handy+cg_cardh, Graphics.TOP | Graphics.HCENTER);
      return ;
    }
    int last = 0, br = 0;
    cg_zvane_kartex[0] = (cg_w - (k*cg_cardw - (k-1)*(cg_cardw-cg_hand_offset)))/2;
    g.setColor(0xFFFFFF);
    System.out.println("Zvanje_select::::");
    for(int i = 0; i < ruka.get_zvanje_4_size()+ ruka.get_zvanje_size(); ++i)
      System.out.println(""+ruka.get_ignore_zvanje(i));
    for(int i = 0; i < k; ++i) {
        if(ruka.get_koje_karte(i) != -1)
          g.drawImage(img_card[ ruka.get_koje_karte(i) ], cg_zvane_kartex[0]
          +i*cg_hand_offset, cg_zvane_kartey[0], Graphics.TOP | Graphics.LEFT);
        if(i == 0 || ruka.get_koje_karte(i-1) == -1) last = i;
        if(i+1 == k || ruka.get_koje_karte(i+1) == -1) {
          if(ruka.get_ignore_zvanje(br) == true) {
            g.setColor(0xFF0000);
            //prekrizi one karte koje neces zvat sa crvenom
            g.drawLine(cg_zvane_kartex[0]+last*cg_hand_offset, cg_zvane_kartey[0],
                 cg_zvane_kartex[0]+i*cg_hand_offset+cg_cardw, cg_zvane_kartey[0]+cg_cardh);
            g.drawLine(cg_zvane_kartex[0]+last*cg_hand_offset, cg_zvane_kartey[0]+cg_cardh,
                 cg_zvane_kartex[0]+i*cg_hand_offset+cg_cardw, cg_zvane_kartey[0]);
            g.setColor(0xBBBBBB); //postavi boju sivu
          }
          else g.setColor(0x0000FF);//postavi plavu boju za ona zvanja koja se vaze
          g.drawString(""+(br+1), (cg_zvane_kartex[0]+last*cg_hand_offset
              + cg_zvane_kartex[0]+i*cg_hand_offset+cg_cardw)/2,
            cg_zvane_kartey[0]+cg_cardh, Graphics.HCENTER | Graphics.TOP);
        }
        if(ruka.get_koje_karte(i) == -1) ++br;
    }
    g.setColor(0x0000FF);
    g.drawString("5 - Zovi", cg_w/2, cg_handy+cg_cardh, Graphics.TOP | Graphics.HCENTER);
  }
  //Univerzalne draw funkcije
  public void draw_trick(Graphics g) {
    g.setFont(font_mono);
    g.setColor(0xFFFFFF);
    int k = info.get_trick_size();
    if( !ready_end_turn ) k = 4;
    for(int i = 0; i < k; ++i) {
        int wh = cg_where[(i + info.get_whose_first_card())%4];
        if(wh%2 == 0) g.drawImage(img_card_rot[ cg_trick_card_id[i] ], cg_trickx+cg_trick_posx[wh],
                   cg_tricky+cg_trick_posy[wh], Graphics.TOP | Graphics.LEFT);
        else  g.drawImage(img_card[ cg_trick_card_id[i] ], cg_trickx+cg_trick_posx[wh],
                   cg_tricky+cg_trick_posy[wh], Graphics.TOP | Graphics.LEFT);
    }
    g.drawString(""+info.get_last_trick_points(),
      (2*cg_trickx+cg_trick_size)/2,
      cg_arrowy[0][0], Graphics.BOTTOM | Graphics.HCENTER);
  }
  public void draw_arrow(Graphics g) {
    g.setColor(0xFF0000);
    int wh = cg_where[info.get_na_redu()];
    for(int i = 0; i < 3; ++i) {
      int next_i = (i+1)%3;
      g.drawLine(cg_arrowx[wh][i], cg_arrowy[wh][i],
        cg_arrowx[wh][next_i], cg_arrowy[wh][next_i]);
    }
  }
  public void draw_scores(Graphics g) {
    int wh_mi = id & 1; int wh_vi = wh_mi ^ 1;
    g.setColor(0xFFFFFF);
    g.fillRect(cg_scoresx, cg_scoresy, cg_scoresw, cg_scoresh);
    g.setColor(0xCCCCCC);
    g.drawLine( cg_scoresx + cg_scores_offset, cg_scores_tip0y,
        cg_scoresx + cg_scoresw - cg_scores_offset, cg_scores_tip0y);
    g.drawLine( cg_scores_splitx, cg_scoresy + cg_scores_offset,
        cg_scores_splitx, cg_scoresy + cg_scoresh - cg_scores_offset);
    if(info.jel_odigravanje()) {
      g.setFont(font_mono_italic);
      g.drawString(""+info.get_zvanje(wh_mi), cg_scores_mix, cg_scores_tip1y, Graphics.TOP | Graphics.RIGHT);
      g.drawString(""+info.get_zvanje(wh_vi), cg_scores_vix, cg_scores_tip1y, Graphics.TOP | Graphics.RIGHT);
    }
    g.setFont(font_mono);
    g.setColor(0x000000);
    g.drawString("MI", cg_scores_mix, cg_scores_miviy, Graphics.TOP | Graphics.RIGHT);
    g.drawString("VI", cg_scores_vix, cg_scores_miviy, Graphics.TOP | Graphics.RIGHT);
    g.setColor(0x0000FF);
    g.drawString(""+info.get_curr_score(wh_mi), cg_scores_mix, cg_scores_tip0y, Graphics.TOP | Graphics.RIGHT);
    g.drawString(""+info.get_curr_score(wh_vi), cg_scores_vix, cg_scores_tip0y, Graphics.TOP | Graphics.RIGHT);
    g.drawLine( cg_scoresx + cg_scores_offset, cg_scoresy + 3*cg_nameh,
        cg_scoresx + cg_scoresw - cg_scores_offset, cg_scoresy + 3*cg_nameh);
    g.drawString(""+info.get_tot_score(wh_mi), cg_scores_mix, cg_scores_tip2y, Graphics.TOP | Graphics.RIGHT);
    g.drawString(""+info.get_tot_score(wh_vi), cg_scores_vix, cg_scores_tip2y, Graphics.TOP | Graphics.RIGHT);
  }
  public void draw_zovi(Graphics g) {
    g.setColor(0x0000FF);
    g.drawLine(cg_zovix, cg_zoviy,
              cg_zovix + 5*(cg_zovi_size + cg_zovi_offset), cg_zoviy);
    g.drawLine(cg_zovix + cg_zovi_offset, cg_zoviy + cg_zovi_size + cg_zovi_offset,
              cg_zovix + 5*(cg_zovi_size + cg_zovi_offset), cg_zoviy + cg_zovi_size + cg_zovi_offset);
    for(int i = 0; i < 6; ++i) {
      g.drawLine(cg_zovix + i*(cg_zovi_size + cg_zovi_offset), cg_zoviy,
          cg_zovix + i*(cg_zovi_size + cg_zovi_offset), cg_zoviy + cg_zovi_size + cg_zovi_offset);
    }
    g.setColor(0x000000);
    g.setFont(font_prop);
    if( info.get_na_redu() != info.get_dealer() ) {
        g.drawImage(img_suit[4], cg_zovix + cg_zovi_offset, cg_zoviy + cg_zovi_offset,
            Graphics.TOP | Graphics.LEFT);
        g.drawString("1", cg_zovix + cg_zovi_offset + cg_zovi_size,
            cg_zoviy + cg_zovi_offset + cg_zovi_size, Graphics.BASELINE | Graphics.RIGHT);
    }
    for(int i = 0; i < 4; ++i) {
        g.drawImage(img_suit[i], cg_zovix + (i+1)*cg_zovi_size + (i+2)*cg_zovi_offset,
            cg_zoviy + cg_zovi_offset, Graphics.TOP | Graphics.LEFT);
        g.drawString(""+(i+2), cg_zovix + (i+2)*cg_zovi_size + (i+2)*cg_zovi_offset,
            cg_zoviy + cg_zovi_offset + cg_zovi_size, Graphics.BASELINE | Graphics.RIGHT);
    }
  }
  public void draw_zvanje(Graphics g) {
    g.setColor(0x0000FF);
    g.drawString("Z", 0, 0, Graphics.TOP | Graphics.LEFT);
    int wh = 0;

    //prikazi zvanja od teama koji ima zvanje
    for(int curr = cg_where[info.get_zvanje_tko() & 1]; wh < 2;  ++wh, curr = (curr+2)%4) {
      int k = info.get_zvanje_koje_size(wh), br = 0;
      if(k == 0) continue;
      if(curr % 2 == 0)
        cg_zvane_kartex[curr] = (cg_w - (k*cg_cardw - (k-1)*(cg_cardw-cg_hand_offset)))/2;
      else
        cg_zvane_kartey[curr] = (cg_h - (k*cg_cardw - (k-1)*(cg_cardw-cg_hand_offset)))/2;
      if(curr % 2 == 0)
        for(int i = 0; i < k; ++i) {
          if( info.get_zvanje_koje(wh, i) == -1) { ++br; continue; }
          g.drawImage(img_card[ info.get_zvanje_koje(wh, i) ], cg_zvane_kartex[curr]
              +i*cg_hand_offset, cg_zvane_kartey[curr], Graphics.TOP | Graphics.LEFT);
        }
      else
        for(int i = 0; i < k; ++i) {
          if( info.get_zvanje_koje(wh, i) == -1) { ++br; continue; }
          g.drawImage(img_card_rot[ info.get_zvanje_koje(wh, i) ], cg_zvane_kartex[curr],
              cg_zvane_kartey[curr]+i*cg_hand_offset, Graphics.TOP | Graphics.LEFT);
        }
    }
  }
  public void draw_names(Graphics g) {
    g.setFont(font_mono);
    for(int i = 0; i < 4; ++i) {
      if(cg_where[i] == 0) continue;
      if(i == info.get_zvao()) g.setColor(0x0000FF);
      else g.setColor(0x000000);
      g.drawString(player_name[i], cg_namex[cg_where[i]], cg_namey[cg_where[i]], Graphics.TOP | Graphics.LEFT);
      if(i == info.get_bela_tko()) {
        g.setColor(0xFF0000);
        g.drawString("Bela!", cg_namex[cg_where[i]], cg_nameh+cg_namey[cg_where[i]], Graphics.TOP | Graphics.LEFT);
      }
    }
  }
  public void draw_ul_kut(Graphics g) {
    g.setFont(font_mono);
    g.setColor(0x000000);
    g.drawImage(img_suit[info.get_adut()], cg_zvana_bojax, cg_zvana_bojay, Graphics.TOP | Graphics.LEFT);
    g.drawString(player_name[info.get_zvao()], cg_ul_kutw/2, cg_ul_kuth,
        Graphics.HCENTER | Graphics.BOTTOM);
  }
  public void draw_server_down() {
    g.setColor(0xFF0000);
    g.fillRect(0, 0, cg_w, cg_h);
    g.setColor(0x0000FF);
    g.setFont(font_prop_bold);
    g.drawString("Server se srusio!", cg_w/2, cg_h/2, Graphics.BASELINE | Graphics.HCENTER);
  }
  public void draw_full_scores(Graphics g) {
    int k = info.koja_partija();
    int curr_h = cg_full_scoresy+2*cg_full_scores_arc+(k+2)*cg_nameh;
    g.setFont(font_mono);
    g.setColor(0xFFFFFF);
    g.fillRoundRect(cg_full_scoresx, cg_full_scoresy, cg_full_scoresw, curr_h,
      cg_full_scores_arc, cg_full_scores_arc);
    g.setColor(0x000000);
    g.drawLine(cg_full_scoresx+cg_full_scores_arc, cg_full_scoresy+cg_full_scores_arc+cg_nameh,
      cg_full_scoresx+cg_full_scoresw-cg_full_scores_arc, cg_full_scoresy+cg_full_scores_arc+cg_nameh);
    g.drawLine(cg_full_scores_hcenter, cg_full_scoresy+cg_full_scores_arc,
      cg_full_scores_hcenter, curr_h-cg_full_scores_arc);
    g.drawLine(cg_full_scoresx+cg_full_scores_arc, cg_full_scoresy+cg_full_scores_arc+(k+1)*cg_nameh,
      cg_full_scoresx+cg_full_scoresw-cg_full_scores_arc, cg_full_scoresy+cg_full_scores_arc+(k+1)*cg_nameh);
    g.drawString("MI", cg_full_scores_mix, cg_full_scoresy+cg_full_scores_arc,
      Graphics.TOP | Graphics.RIGHT);
    g.drawString("VI", cg_full_scores_vix, cg_full_scoresy+cg_full_scores_arc,
      Graphics.TOP | Graphics.RIGHT);

    int wh_mi = id & 1; int wh_vi = wh_mi ^ 1;
    for(int i = 0; i < k; ++i) {
      int curr_mi = info.get_partija_score(i, wh_mi), curr_vi = info.get_partija_score(i, wh_vi);
      if(info.is_stilja_partija(i)) g.setColor(0x00FF00);
      else g.setColor(0x000000);
      g.drawString(""+curr_mi, cg_full_scores_mix, cg_full_scoresy+cg_full_scores_arc+(i+1)*cg_nameh,
        Graphics.TOP | Graphics.RIGHT);
      g.drawString(""+curr_vi, cg_full_scores_vix, cg_full_scoresy+cg_full_scores_arc+(i+1)*cg_nameh,
        Graphics.TOP | Graphics.RIGHT);
    }
    g.setColor(0xFF0000);
    g.drawString(""+info.get_tot_score(wh_mi), cg_full_scores_mix,
      cg_full_scoresy+cg_full_scores_arc+(k+1)*cg_nameh, Graphics.TOP | Graphics.RIGHT);
    g.drawString(""+info.get_tot_score(wh_vi), cg_full_scores_vix,
        cg_full_scoresy+cg_full_scores_arc+(k+1)*cg_nameh, Graphics.TOP | Graphics.RIGHT);
    g.setColor(0x0000FF);
    if(game_over) {
      if(info.have_you_won(id))
        g.drawString("Pobijedili!", (2*cg_full_scoresx+cg_full_scoresw)/2,
          cg_full_scoresy+cg_full_scores_arc+(k+2)*cg_nameh, Graphics.TOP | Graphics.HCENTER);
      else
        g.drawString("Izgubili!", (2*cg_full_scoresx+cg_full_scoresw)/2,
          cg_full_scoresy+cg_full_scores_arc+(k+2)*cg_nameh, Graphics.TOP | Graphics.HCENTER);
    }
  }
  public void draw_popis_igraca(Graphics g) {
    g.setColor(0xFFFFFF);
    g.fillRect(0, 0, cg_w, cg_h);
    g.setColor(0x000000);
    g.setFont(font_mono);
    int x = (cg_w - 2*cg_namew)/2, y = (cg_h-5*cg_nameh)/2;
    g.drawString("Popis igraca: ", x, y, Graphics.TOP | Graphics.LEFT);
    for(int i = 1; i < cg_popis_igraca_size; ++i) {
      g.drawString(cg_popis_igraca[i], x, y+i*cg_nameh, Graphics.TOP | Graphics.LEFT);
    }
    g.drawString(cg_popis_igraca[0]+" (server)", x, y+4*cg_nameh, Graphics.TOP | Graphics.LEFT);
  }
}
