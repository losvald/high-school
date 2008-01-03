/*
 * Bela.java
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
public class Bela extends MIDlet implements CommandListener {
    Display display;
    Igra game;
    Alert Saved_msg;
    options opt;
    Form form_main, form_options, form_log, form_about;
    TextField txtName, log_tf;
    ChoiceGroup cg_autoplay;
    List list_novaigra, server_opcije;
    Image img_about;
    String moj_imei;
    Log last_log;
    boolean first_game, in_join_list, options_active, loading_igra_complete;
    boolean autoplay_sel[];
    //komande
    final Command cmd_View_Log = new Command("Log", Command.SCREEN, 6);
    final Command cmd_Izlaz = new Command("Izlaz", Command.EXIT, 1);
    final Command cmd_Novaigra = new Command("Nova Igra", Command.SCREEN, 2);
    final Command cmd_Opcije = new Command("Opcije", Command.SCREEN, 3);
    final Command cmd_Natrag =  new Command("Natrag", Command.BACK, 1);
    final Command cmd_About = new Command("O autoru", Command.SCREEN, 100);

    final Command cmd_Ulaz = new Command("Ulaz", Command.OK, 2);
    //final Command cmd_Refresh = new Command("Refresh", Command.SCREEN, 3);

    final Command cmd_Exit_Log = new Command("Vrati se", Command.SCREEN, 7);
    final Command cmd_Clear_Log = new Command("Clear", Command.SCREEN, 8);

    final Command cmd_Kreni = new Command("Kreni", Command.SCREEN, 3);
    final Command cmd_Server_Opcije = new Command("Postavke Igre", Command.SCREEN, 4);
    final Command cmd_Kick = new Command("Kick", Command.SCREEN, 5);

    final Command cmd_Natrag_Server = new Command("Natrag", Command.BACK, 2);

    final Command cmd_Login = new Command("Login", Command.SCREEN, 1);

    final Command cmd_View = new Command("View", Command.OK, 3);
    final Command cmd_Start = new Command("Start", Command.OK, 2);
    public String retrieve_imei() {
        String imei = null;
        //Sony Ericsson
        imei = System.getProperty("com.sonyericsson.imei");
        if(imei != null) return imei;
        imei = System.getProperty("com.sonyericsson.IMEI");
        if(imei != null) return imei;
        //Nokia
        imei = System.getProperty("com.nokia.mid.imei");
        if(imei != null) return imei;
        imei = System.getProperty("com.nokia.mid.IMEI");
        if(imei != null) return imei;
        imei = System.getProperty("com.nokia.imei");
        if(imei != null) return imei;
        imei = System.getProperty("com.nokia.IMEI");
        if(imei != null) return imei;
        //Siemens
        imei = System.getProperty("com.siemens.IMEI");
        if(imei != null) return imei;
        imei = System.getProperty("com.siemens.imei");
        if(imei != null) return imei;
        //Motorola
        imei = System.getProperty("com.motorola.IMEI");
        if(imei != null) return imei;
        imei = System.getProperty("com.motorola.imei");
        if(imei != null) return imei;
        //Samsung
        imei = System.getProperty("com.samsung.imei");
        if(imei != null) return imei;
        imei = System.getProperty("com.samsung.IMEI");
        if(imei != null) return imei;
        //Ostalo
        imei = System.getProperty("phone.imei");
        if(imei != null) return imei;
        imei = System.getProperty("phone.IMEI");
        if(imei != null) return imei;
        imei = System.getProperty("IMEI");
        if(imei != null) return imei;
        imei = System.getProperty("imei");
        if(imei != null) return imei;
        imei = System.getProperty("com.imei");
        if(imei != null) return imei;
        imei = System.getProperty("com.IMEI");
        if(imei != null) return imei;

        return "35238201-100150-6-02"; //andrejev IMEI
    }
    public String detokanize_imei() {
        String ret = "";
        for(int i = 0; i < moj_imei.length(); ++i)
          if(moj_imei.charAt(i) >= '0' && moj_imei.charAt(i) <= '9') ret += moj_imei.charAt(i);
        return ret.substring(8, 14);
    }
    public int hash(int code) {
        int curr = code;
        int high_PRIME = 999983, low_PRIME = 617, mid_PRIME = 7393;
        int itr = (code & 0x7) + 1;//0xa57c2
        int xor1 = 0x55555, xor2 = 0xa57c2, xor3 = 0x20093;
        for(int times = 0; times < itr; ++times) {
            if((curr ^ xor1) != curr) curr ^= xor1;
            else curr ^= ~xor1;
            curr *= low_PRIME;
            curr += 0x2342;
            curr %= high_PRIME;
            //if(curr % 13 > 5) curr = times*times ;
            if(times%3 != 0) curr ^= xor2;
            else if(times % 4 != 0) curr |= mid_PRIME;
            else curr ^= xor2 & curr & mid_PRIME;
                curr %= mid_PRIME;
                curr ^= xor3;
                curr *= mid_PRIME;
                curr %= high_PRIME;
                if(curr < 100)
                    curr *= mid_PRIME;
            }
        return curr;
    }
    public boolean is_valid_password(String s) {
        int val = Integer.parseInt( moj_imei );
        System.out.println("Dio imeia:"+val);
        String hashed = "" + hash(val);
        return s.equals(hashed);
    }
    public void save_options() {
      opt.update_ime( txtName.getString() );
      autoplay_sel = new boolean[cg_autoplay.size()];
      cg_autoplay.getSelectedFlags( autoplay_sel );
      opt.update_selected( autoplay_sel, cg_autoplay.size() );

      game.update_ime( opt.get_ime() );
    }
    public void poruka() {
        save_options();
        Saved_msg.setString( "Spremnjeno!\n");
        Saved_msg.setString( Saved_msg.getString() + "Ime: " + opt.get_ime() + "\n");
        //for(int i = 0; i < 2; ++i) {
          //Saved_msg.setString( Saved_msg.getString() + opt.get_selected(i) + "\n");
        //}
        String s = System.getProperty("com.sonyericsson.imei");
        Saved_msg.setString( Saved_msg.getString() +  "Code: "+ moj_imei );
        display.setCurrent(Saved_msg);
    }
    public void set_options() {
        display.setCurrent(form_options);
        form_options.setCommandListener(this);
        options_active = true;
    }
    void load_last_log() {
      for(int i = 0; i < last_log.size(); ++i)
        game.log.push_msg( last_log.get_msg(i) );
      game.log.push_msg("----------");
    }
    void reset_game() {
        if(!first_game) last_log = game.log;
        game = new Igra();
        if(!first_game) load_last_log();
        game.log.push_msg("Loading game data COMPLETED!");
        first_game = false;
        game.addCommand( cmd_Izlaz );
        //game.addCommand( cmd_Refresh );
        //game.addCommand( cmd_View_Log );

        game.log.log.addCommand( cmd_Clear_Log );
        game.log.log.addCommand( cmd_Exit_Log );

        game.server_list = new List("Popis servera", Choice.IMPLICIT);
        game.server_list.addCommand( cmd_Ulaz );
        game.server_list.addCommand( cmd_View_Log );
        //game.server_list.addCommand( cmd_Refresh );
        game.server_list.addCommand( cmd_Natrag );
        game.joined_list = new List("Popis joinanih igraca", Choice.IMPLICIT);
        game.joined_list.addCommand( cmd_Kreni );
        game.joined_list.addCommand( cmd_Kick );
        game.joined_list.addCommand( cmd_Server_Opcije );
        game.joined_list.addCommand( cmd_View_Log );
        game.joined_list.addCommand( cmd_Natrag );

        server_opcije = new List("Odaberi mod", Choice.IMPLICIT);
        server_opcije.append("Quick", null);
        server_opcije.append("Normal", null);
        server_opcije.append("Brutal", null);
        server_opcije.addCommand( cmd_Natrag_Server );

        game.update_ime( opt.get_ime() );

    }
    public Bela() {
        opt = new options();
        //reset_game();
        first_game = true;

        moj_imei = retrieve_imei();
        moj_imei = detokanize_imei();

        in_join_list = false;

        //game.addCommand( cmd_Izlaz );
        //glavni meni
        form_main = new Form("Glavni Izbornik");
        StringItem s = new StringItem("Dobrodosli u Belu v0.55 alpha!", "Hello!");
        form_main.append(s);
        form_main.addCommand( cmd_Novaigra );
        form_main.addCommand( cmd_About );
        form_main.addCommand( cmd_Opcije );

        form_main.addCommand( cmd_Izlaz );
        //opcije
        form_options = new Form("Opcije");
        form_options.addCommand( cmd_Natrag );
        form_options.addCommand( cmd_View );
        txtName = new TextField("Ime: ", opt.get_default_ime(), 7, TextField.ANY);
        form_options.append(txtName);
        //autoplay
        cg_autoplay = new ChoiceGroup("Automatsko igranje: ", Choice.MULTIPLE);
        cg_autoplay.append("Quick play", null);
        cg_autoplay.append("Automatsko zvanje", null);
        cg_autoplay.setSelectedIndex(1, true);
        form_options.append(cg_autoplay);
        options_active = false;

        Saved_msg = new Alert("Haha", "", null, AlertType.INFO);
        Saved_msg.setString("Opcije spremljene.");
        //nova igra
        list_novaigra = new List("Nova igra", Choice.IMPLICIT);
        list_novaigra.append("Join", null);
        list_novaigra.append("Host", null);
        list_novaigra.append("Single player", null);
        list_novaigra.addCommand( cmd_Start );
        list_novaigra.addCommand( cmd_Natrag );

        form_log = new Form("Login");
        form_log.addCommand( cmd_Login );

        log_tf = new TextField("Activation code:"+moj_imei, "", 6, TextField.NUMERIC | TextField.PASSWORD);
        //form_log.append( new StringItem("Activation code:", moj_imei) );
        form_log.append( log_tf );
        try {
          img_about = Image.createImage("/images/about.png");
        } catch(Exception ex) {}

        form_about = new Form("O autoru");
        form_about.append(img_about);
        form_about.append(new StringItem("Leo Osvald","\n4.a, XV. Gimnazija\nCroatia, Zagreb") );
        form_about.append(new StringItem("O programu:\nBela v0.55 alpha\n",
          "MIDP version: 2.0\nCLDC: 1.0\n2800 linija Java koda") );
        form_about.addCommand(cmd_Natrag);
    }
    public void nova_igra() {
        reset_game();
        display.setCurrent(list_novaigra);
        list_novaigra.setCommandListener(this);
        loading_igra_complete = true;
    }
    public void main_menu() {
        display.setCurrent(form_main);
        form_main.setCommandListener(this);
        loading_igra_complete = true;
        in_join_list = false;
    }
    public void commandAction(Command com, Displayable dis) {
        if(com == cmd_Novaigra) {
          if(loading_igra_complete) {
            loading_igra_complete = false;
            nova_igra();
          }
        }
        else if(com == cmd_Opcije ) set_options();
        else if(com == cmd_Izlaz ) {
            if( game.already_started() ) {
                if(game.is_client() ) {
                  if(game.has_game_started()) game.notify_disconnected();
                  else game.notify_left_server();
                }
                else {
                  game.end_server();
                }
                game.destroy();
                //reset_game();
                main_menu();
            }
            else  notifyDestroyed();
        }
        else if(com == cmd_View ) {
            poruka();
        }
        else if(com == cmd_Login) {
            if( is_valid_password(log_tf.getString() ) ) main_menu();
        }
        else if(com == cmd_Natrag ) {
            System.out.println("NATRAG....");
            if( game.already_started() ) {
                System.out.println("Natrag iz igre...");
                if(game.is_client() ) game.notify_disconnected();
                game.destroy();
                //reset_game();
                main_menu();
            }
            else {
                System.out.println("Igra nije bila u tijeku.");
                if(options_active) {
                  save_options();
                  options_active = false;
                }
                main_menu();
            }
        }
        /*else if(com == cmd_Refresh ) {
            System.out.println("Refreshing....");
        }*/
        else if(com == cmd_Ulaz) {
            if(game.client_ready() ) {
                System.out.println("Ulazim u server" + game.server_list.getSelectedIndex());
                game.update_moj_server( game.server_list.getSelectedIndex() );
                if( game.try_to_join() ) {
                    System.out.println("Usao sam u IGRUUUUUUUU!");
                    display.setCurrent(game);
                    game.setCommandListener(this);
                }
            }
            else {
                System.out.println("Nemogu poslat jos poruku!");
            }
        }
        else if(com == cmd_Kreni) {
            game.set_game_started();
            display.setCurrent(game);
            game.setCommandListener(this);
        }
        else if(com == cmd_Server_Opcije) {
          display.setCurrent(server_opcije);
          server_opcije.setCommandListener(this);
        }
        else if(com == cmd_Natrag_Server) {
          if(server_opcije.getSelectedIndex() == 0)
            game.set_quick_play();
          else if(server_opcije.getSelectedIndex() == 2)
            game.set_brutal_play();
          display.setCurrent(game.joined_list);
          game.joined_list.setCommandListener(this);
        }
        else if(com == cmd_Kick) {
            if(!game.is_open_slot(game.joined_list.getSelectedIndex())
             && game.get_first_open_slot() < 3)
                game.notify_kicked(game.joined_list.getSelectedIndex());
        }
        else if(com == cmd_Start) {
            display.setCurrent(game);
            game.setCommandListener(this);

            if(list_novaigra.getSelectedIndex() == 1) {
                System.out.println("Napravio si igru");
                game.set_server();

                display.setCurrent(game.joined_list);
                (game.joined_list).setCommandListener(this);
            }
            else if(list_novaigra.getSelectedIndex() == 0) {
                System.out.println("Usao si u igru");
                System.out.println("Stavljena je lista");
                in_join_list = true;
                display.setCurrent(game.server_list);
                (game.server_list).setCommandListener(this);
            }
            else {
              game.set_single_player();
            }
            game.igraj();
            //game.server_list.setCommandListener(this);

        }
        else if(com == cmd_About) {
          display.setCurrent(form_about);
          form_about.setCommandListener(this);
        }
        else if(com == cmd_View_Log) {
          display.setCurrent(game.log.log);
          game.log.log.setCommandListener(this);
        }
        else if(com == cmd_Clear_Log) {
          game.log.clear();
        }
        else if(com == cmd_Exit_Log) {
          if(game.has_game_started() || game.client_joined()) {
            System.out.println("RAAAAAAADIIIIIIIIIIII!!!!!!!!!!!!!!!!!");
            display.setCurrent(game);
            game.setCommandListener(this);
            game.repaint();
          }
          if(list_novaigra.getSelectedIndex() == 0) {
            display.setCurrent(game.server_list);
            (game.server_list).setCommandListener(this);
          }
          else if(list_novaigra.getSelectedIndex() == 1) {
            display.setCurrent(game.joined_list);
            (game.joined_list).setCommandListener(this);
          }
        }
    }
    public void startApp() {
        display = Display.getDisplay(this);
        display.setCurrent( form_log );
        form_log.setCommandListener(this);
        reset_game();
        main_menu();
    }
    public void pauseApp() {
    }
    public void destroyApp(boolean unc) {
        game.destroy();
        display.setCurrent((Displayable) null );
    }
}
