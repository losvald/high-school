/*
 * information.java
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

public class information {
  int host;
  int adut, zvali, zvao;
  boolean zvan_adut;
  boolean bela;
  boolean zvanje_select; //dal je u tijeku selektiranje zvanja
  boolean brutal_play;
  boolean quick_play;
  boolean autoplay;
  boolean[] stilja_partija; //dal je u nekoj partiji bila stilja

  int bela_tko;
  int na_redu;

  int zvanje, zvanje_tko, zvanje_max, zvanje_max_sec;
  int[] zvanje_score, zvanje_koje_size, zvali_partija;
  int[][] zvanje_koje;
  int[][] sva_zvanja;
  int[] sva_zvanja_size, sva_zvanja_score;
  int dealer;
  int n_scores;
  int[][] scores; //[15][2] ovo treba promijeniti
  int[] curr_score, tot_score;
  int[] tricks;
  int nth_trick;
  karta[] this_trick;
  karta highest, first_card;
  int trick_size;
  boolean trumped;
  int whose_trick;
  int whose_first_card;
  int last_trick_points;
  int winner;

  public information() {
    scores = new int[15][2];
    zvali_partija = new int[15];
    stilja_partija = new boolean[15];
    curr_score = new int[2];
    tot_score = new int[2];
    tricks = new int[2];
    this_trick = new karta[4];
    zvanje_score = new int[2];
    zvanje_koje_size = new int[2];
    zvanje_koje = new int[2][11];
    sva_zvanja = new int[4][11];
    sva_zvanja_size = new int[4];
    sva_zvanja_score = new int[4];
    nth_trick = 0;
    n_scores = 0;
    dealer = 0;
    na_redu = (dealer+1)%4;
    whose_trick = na_redu;
    highest = new karta();
    first_card = new karta();
    highest.set_lowest();
    winner = -1;

    zvanje_tko = -1;
    zvanje_max = 0;
    zvanje_max_sec = 0;
    zvanje_select = false;
    brutal_play = false;
    quick_play = false;
    autoplay = false;
    bela = false;
    bela_tko = -1;
    adut = -1;
    zvan_adut = false;
    zvao = -1;
    zvali = -1;
    trick_size = 0;
    last_trick_points = 0;
    for(int i = 0; i < 2; ++i) {
      curr_score[i] = 0;
      tot_score[i] = 0;
      scores[0][i] = 0;
      zvanje_score[i] = 0;
      zvanje_koje_size[i] = 0;
    }
    for(int i = 0; i < 4; ++i) {
      sva_zvanja_size[i] = 0;
      sva_zvanja_score[i] = 0;
    }
  }
  public void update_adut(int x, int y) { adut = x; zvao = y; zvali = zvao & 1; }
  public int get_zvanje_tko() { return zvanje_tko; }
  public int get_zvanje(int k) { return zvanje_score[k & 1]; }
  public int get_zvanje_koje_size(int k) { return zvanje_koje_size[k]; }
  public int get_zvanje_koje(int k, int x) { return zvanje_koje[k][x]; }
  public int get_sva_zvanja_score(int k) { return sva_zvanja_score[k]; }
  public int get_sva_zvanja_size(int k) { return sva_zvanja_size[k]; }
  public int[] get_array_sva_zvanja(int k) { return sva_zvanja[k]; }
  public void save_sva_zvanja(int[] a, int a_size, int k, int x) {
    sva_zvanja_score[k] = x;
    sva_zvanja_size[k] = a_size;
    for(int i = 0; i < a_size; ++i)
      sva_zvanja[k][i] = a[i];
  }
  public void save_zvanje_team(int x, int curr, int[] a, int a_size) {
    final String vr = "789XJQKA";
    final String suit = "CDHS";
    zvanje_score[zvanje_tko&1] += x;
    //spremi zvanje od igraca kojem je proslo zvanje
    zvanje_koje_size[curr] = a_size;
    System.out.println("SAVE TEAM:::::: "+zvanje_max+" "+sva_zvanja_score[0]+" "
    +sva_zvanja_score[1]+" "+sva_zvanja_score[2]+" "+sva_zvanja_score[3]);
    //System.out.println("-----Curr: "+curr+ " Size: "+a_size+"Val:"+x);
    zvanje_koje[curr] = new int[a_size];
    for(int i = 0; i < a_size; ++i)  {
      zvanje_koje[curr][i] = a[i];
      if(a[i] == -1) System.out.println("-1");
      else {
        int broj = a[i]%8;
        int boja = a[i]/8;
        //System.out.println(">"+vr.charAt(broj)+" "+suit.charAt(boja));
      }
    }
  }
  public void update_zvanje(int x, int sec, int k, int tot) {
    if(x > zvanje_max || x == zvanje_max && sec > zvanje_max_sec) {
      zvanje_max = x;
      zvanje_max_sec = sec;
      zvanje_tko = k;
    }
  }
  public void set_brutal_play() { brutal_play = true; autoplay = false; }
  public void set_quick_play() { quick_play = true; autoplay = true; }
  public boolean is_brutal_play() { return brutal_play; }
  public boolean is_quick_play() { return quick_play; }
  public boolean is_autoplay() { return autoplay; }
  public boolean get_bela() { return bela; }
  public int get_bela_tko() { return bela_tko; }
  public void update_bela(int k) { bela = true; bela_tko = k; zvanje_score[k&1] += 20; }
  public void update_zvanje_select(boolean state) { zvanje_select = state; }
  public void update_zvan_adut(boolean state) { zvan_adut = state; }
  public void set_first_turn() { na_redu = (dealer + 1) % 4; }
  public void next_turn() { na_redu = (na_redu + 1) % 4; }
  public karta get_first_card() { return first_card; }
  public int get_whose_first_card() { return whose_first_card; }
  public int get_adut() { return adut; }
  public int get_zvao() { return zvao; }
  public int get_dealer() { return dealer; }
  public int get_na_redu() { return na_redu; }
  public boolean is_stilja_partija(int x) { return stilja_partija[x]; }
  public int koja_partija() { return n_scores; }
  public int get_trick_size() { return trick_size; }
  public boolean is_end_partija() { return nth_trick >= 8; }
  public boolean is_end_trick() { return trick_size >= 4; }
  public boolean get_trumped() { return trumped; }
  public karta get_highest() { return highest; }
  public karta get_trick_card(int x) { return this_trick[x]; }
  public boolean have_you_won(int k) { return (k&1) == (winner&1); }
  public int get_tot_score(int x) { return tot_score[x]; }
  public int get_curr_score(int x) { return curr_score[x]; }
  public int get_partija_score(int x, int k) { return scores[x][k]; }
  public int get_last_trick_points() { return last_trick_points; }
  public int get_trick_points() {
    int ret = 0;
    for(int i = 0; i < trick_size; ++i) ret += this_trick[i].get_points(adut);
    return ret;
  }
  public void play_card(karta x) {
    if(trick_size == 0 || x.jaca_od(highest, adut) ) {
      highest = x;
      whose_trick = na_redu;
    }
    this_trick[trick_size] = x;
    if(trick_size == 0) first_card = x;
    else if(!trumped && first_card.get_boja() != adut && x.get_boja() == adut)
      trumped = true;
    if(trick_size == 0) {
      whose_first_card = na_redu;
      last_trick_points = 0;
    }
    last_trick_points += x.get_points(adut);
    ++trick_size;
    next_turn();
  }
  public void save_results() {
    for(int i = 0; i < 2; ++i) {
      if(tricks[i] != 0)
        curr_score[i] += zvanje_score[i];
      else {
        System.out.println("Stilja");
        curr_score[i] += 90;
        stilja_partija[i] = true;
      }
    }
    int total = curr_score[0] + curr_score[1];
    if(curr_score[zvali] <= curr_score[1-zvali]) {
      //printf("Pali su!\n");
      curr_score[zvali] = 0;
      curr_score[1-zvali] = total;
    }
    for(int i = 0; i < 2; ++i)
      tot_score[i] += scores[n_scores][i] = curr_score[i];
    zvali_partija[n_scores] = zvali;
    ++n_scores;
  }
  public void save_end_trick() {
    ++tricks[whose_trick & 1];
    for(int i = 0; i < 4; ++i)
      curr_score[whose_trick & 1] += this_trick[i].get_points(adut);
    ++nth_trick;
    if(nth_trick == 8) {
      System.out.println("Zadnji stih!");
      curr_score[whose_trick & 1] += 10; //zadnji stih
    }
    highest.set_lowest();
    trick_size = 0;
    trumped = false;
    na_redu = whose_trick;
  }
  public void reset() {
    //++n_scores;
    tricks[0] = tricks[1] = 0;
    nth_trick = 0;
    trick_size = 0;
    dealer = (dealer+1) % 4;
    na_redu = (dealer+1) % 4;
    whose_trick = na_redu;

    zvanje_tko = -1;
    zvanje_max = 0;
    zvanje_max_sec = 0;
    zvanje_select = false;

    highest.set_lowest();
    zvao = -1;
    zvali = -1;
    zvan_adut = false;
    zvanje_select = false;
    bela = false;
    bela_tko = -1;
    last_trick_points = 0;
    for(int i = 0; i < 2; ++i) {
      curr_score[i] = 0;
      scores[n_scores][i] = 0;
      zvanje_score[i] = 0;
      zvanje_koje_size[i] = 0;
    }
    for(int i = 0; i < 4; ++i) {
      sva_zvanja_size[i] = 0;
      sva_zvanja_score[i] = 0;
    }
  }
  public boolean jel_zvano() {return zvan_adut; }
  public boolean jel_zvanje_select() { return zvanje_select; }
  public boolean jel_odigravanje() { return zvan_adut && !zvanje_select; }
  public boolean game_over() {
    if(n_scores == 0) return false;
    if(tot_score[0] == tot_score[1]) return false;
    if(tot_score[0] >= 1001 ^ tot_score[1] >= 1001) {
      if(tot_score[0] >= 1001) winner = 0;
      else winner = 1;
      return true;
    }
    else if(tot_score[0] >= 1001) {
      if(tot_score[0] > tot_score[1]) winner = 0;
      else winner = 1;
      return true;
    }
    return false;
  }
}
