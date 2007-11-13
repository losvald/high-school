/*
 * hand.java
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

public class hand {
  karta[] a;
  boolean[] used;
  int adut;
  int zvanje_4_size; //kolko ima zvanja od 4 iste
  int zvanje_size; //kolko ima zvanja od uzastopnih karata
  int[] zvanje_4val, zvanje_val; //vrijednosti zvanja od 4 i od uzastopnih
  int[] zvanje_4koje; //popis zvanja od 4 iste (broj)
  int[] zvanje_id; //popis zvanja od uzastopnih karata (do koje karte je)
  int[] zvanje_koliko_karata; //popis kolko karata uzastopnih je neko zvanje
  int zvanje_max; //jacina najjaceg zvanja (bodovi)
  int zvanje_max_sec; //ako ima vise najjacih ovo je drugi kriterij
  int zvanje_tot_val; //ukupni bodovi svih zvanja koje netko hoce zvat
  final int zvanje_max_sec_offset = 100; //sluzi za ovo zvanje_max_sec
  int[] koje_karte; //id karata u zvanju za prikazat, lijepo poslozeno
  int broj_karata; //broj karata ukupno u zvanju
  boolean[] ignore_zvanje; //koje zvanje igrac ne zeli zvati, bazirano na zvanje_(4_)size
  boolean bela; //dal ce se bela zvati ili nece
  public hand() {
    a = new karta[8];
    used = new boolean[8];
    for(int i = 0; i < 8; ++i) used[i] = false;
    zvanje_4_size = 0;
    zvanje_size = 0;
    zvanje_4val = new int[2];
    zvanje_val = new int[2];
    zvanje_4koje = new int[2];
    zvanje_id = new int[2];
    zvanje_koliko_karata = new int[2];
    ignore_zvanje = new boolean[4];
    zvanje_max = 0;
    zvanje_max_sec = 0;
    broj_karata = 0;
    bela = false;
  }
  void nastimano1() {
    a[0] = new karta(4);
    a[1] = new karta(12);
    a[2] = new karta(20);
    a[3] = new karta(28);
    a[4] = new karta(29);
    a[5] = new karta(27);
    a[6] = new karta(24);
    a[7] = new karta(30);
  }
  void nastimano2() {
    a[0] = new karta(5);
    a[1] = new karta(13);
    a[2] = new karta(20);
    a[3] = new karta(28);
    a[4] = new karta(21);
    a[5] = new karta(12);
    a[6] = new karta(4);
    a[7] = new karta(29);
  }
  void nastimano3() {
    a[0] = new karta(24);
    a[1] = new karta(25);
    a[2] = new karta(26);
    a[3] = new karta(27);
    a[4] = new karta(28);
    a[5] = new karta(29);
    a[6] = new karta(30);
    a[7] = new karta(31);
  }
  void nastimano4() {
    a[0] = new karta(21);
    a[1] = new karta(23);
    a[2] = new karta(7);
    a[3] = new karta(5);
    a[4] = new karta(28);
    a[5] = new karta(29);
    a[6] = new karta(30);
    a[7] = new karta(22);
  }
  public void submit_zvanje() {  //updatea max zvanje i tot zvanje ali samo za ono zvanje koje netko hoce zvat
    zvanje_tot_val = 0;
    zvanje_max = 0;
    zvanje_max_sec = 0;
    System.out.println("Submitam zvanje...");
    for(int i = 0; i < zvanje_4_size + zvanje_size; ++i) {
      if(ignore_zvanje[i]) continue; //preskoci ignorirana zvanja
      if(i >= zvanje_size) {//ako nije ignorirano zvanje od 4 iste
        int x = i - zvanje_size;
        if(zvanje_4val[x] > zvanje_max) {
          zvanje_max = zvanje_4val[x];
          zvanje_max_sec = a[x].get_broj() + zvanje_max_sec_offset;
        }
        else if(zvanje_4val[x] == zvanje_max
          && a[x].get_broj() + zvanje_max_sec_offset > zvanje_max_sec)
            zvanje_max_sec = a[x].get_broj() + zvanje_max_sec_offset;
        zvanje_tot_val += zvanje_4val[x];
      }
      else {  //ako nije ignorirano zvanje od uzastopnih
        if(zvanje_val[i] > zvanje_max) {
          zvanje_max = zvanje_val[i];
          zvanje_max_sec = zvanje_id[i]%8; //drugi kriterij je do kud je
        }
        zvanje_tot_val += zvanje_val[i];
      }
    }
    System.out.println("Tot zvanje: "+zvanje_tot_val);
    construct_zvanje_hand();
    System.out.println("Max zvanje: "+zvanje_max);
    System.out.println("Max sec: "+zvanje_max_sec);
  }
  public void construct_zvanje_hand() {
    broj_karata = 0;
    int z = 0, z4 = 0;
    for(int i = 0; i < zvanje_4_size + zvanje_size; ++i) {
      if(ignore_zvanje[i]) continue;
      if(i >= zvanje_size) {//ako je ignorirano zvanje od 4 iste
        broj_karata += 4;
        ++z4;
      }
      else {//ako nije ignorirano zvanje od uzastopnih
        broj_karata += zvanje_koliko_karata[i];
        ++z;
      }
    }
    if(z != zvanje_size || z4 != zvanje_4_size)
      System.out.println("z = "+z+" z4 = "+z4);
    else System.out.println("Checkpoint 1!");
    if(z + z4 == 0) return ;
    broj_karata += z + z4 - 1; //dodaj prazne karte tj -1 kao razmake izmedju cjelina
    boolean[] nemoj_uzet = new boolean[32]; //koje karte se dvaput koriste u zvanju
    if(z4 == 1 && z > 0) {
      //ako ima jedamput 4 iste i barem jednom niz uzastopnih
      //onda je moguce da se jedna karta iskoristi vise puta pa treba to provjerit
      for(int i = 0; i < zvanje_size; ++i) {
        if(ignore_zvanje[i]) continue;
        for(int j = 0; j < 4; ++j)
            if(zvanje_id[i] >= 8*j + zvanje_4koje[0])
              if(zvanje_id[i] - (8*j + zvanje_4koje[0]) <
                zvanje_koliko_karata[i]) {
                  nemoj_uzet[ 8*j + zvanje_4koje[0] ] = true;
                  --broj_karata;
              }
      }
    }
    System.out.println("Broj karata("+broj_karata);
    koje_karte = new int[broj_karata];
    int curr = 0, br = 0;
    for(int i = 0; i < zvanje_size; ++i) {
      if(ignore_zvanje[i]) continue;
      int x = zvanje_id[i];
      int k = zvanje_koliko_karata[i];
      for(int j = x-k+1; j <= x; ++j)
        koje_karte[curr++] = j;
      if(br == 0 && z > 1 || z4 > 0) //dodaj praznu kartu
         koje_karte[curr++] = -1;
      ++br;
    }
    br = 0;
    for(int i = 0; i < zvanje_4_size; ++i) {
      if(ignore_zvanje[zvanje_size + i]) continue;
      int x = zvanje_4koje[i];
      for(int j = 0; j < 4; ++j)
        if(!nemoj_uzet[8*j + x]) koje_karte[curr++] = 8*j + x;
      if(br == 0 && z4 > 1) koje_karte[curr++] = -1; //dodaj praznu kartu
      ++br;
    }
    //print_zvanje();
  }
  public boolean check_zvanje() {
    //sortiraj po brojevima
    for(int i = 0; i < 7; ++i)
      for(int j = i + 1; j < 8; ++j)
        if(a[i].get_broj() > a[j].get_broj()) {
          karta t = a[i]; a[i] = a[j]; a[j] = t;
        }
    //pogledaj za zvanja od 4 iste karte
    for(int i = 0; i < 8-3; ++i)
      if(a[i].get_broj() == a[i+3].get_broj()) {
        if(a[i].get_broj() < 2) continue;
        else if(a[i].get_broj() == 4) zvanje_4val[zvanje_4_size] = 200;
        else if(a[i].get_broj() == 2) zvanje_4val[zvanje_4_size] = 150;
        else zvanje_4val[zvanje_4_size] = 100;
        zvanje_4koje[zvanje_4_size] = a[i].get_broj();
        ++zvanje_4_size;
      }
    //sortiraj po boji pa po brojevima
    for(int i = 0; i < 7; ++i)
      for(int j = i + 1; j < 8; ++j)
        if(a[i].get_boja() > a[j].get_boja() || a[i].get_boja() == a[j].get_boja()
          && a[i].get_broj() > a[j].get_broj()) {
            karta t = a[i]; a[i] = a[j]; a[j] = t;
        }
    //pogledaj za zvanja od 3-8 istih
    int curr = 0;
    for(int i = 0; i < 8; i = curr) {
      for(curr = i+1; curr < 8 && a[curr].get_boja() == a[i].get_boja()
        && a[curr].get_broj() == a[curr-1].get_broj() + 1; ++curr) ;
      if(curr-i == 8) zvanje_val[zvanje_size] = 1001; //BELOT
      else if(curr-i >= 5)  zvanje_val[zvanje_size] = 100;
      else if(curr-i == 4) zvanje_val[zvanje_size] = 50;
      else if(curr-i == 3) zvanje_val[zvanje_size] = 20;
      //ako je bilo zvanje zapamti id kolko karata i do kud
      if(curr-i >= 3) {
        zvanje_id[zvanje_size] = a[curr-1].get_id(); //do kud je (ID)
        zvanje_koliko_karata[zvanje_size] = curr-i; //kolko karata
        ++zvanje_size;
      }
    }
    ignore_zvanje = new boolean[zvanje_4_size + zvanje_size];
     //OVO TREBA MAKNUT, OVO JE SAMO RADI PROBE
    for(int i = 0; i < 7; ++i)
      for(int j = i + 1; j < 8; ++j)
        if(a[i].get_boja() > a[j].get_boja() || a[i].get_boja() == a[j].get_boja()
          && a[i].get_broj() > a[j].get_broj()) {
            karta t = a[i]; a[i] = a[j]; a[j] = t;
        }
    System.out.println("Zvanje_check complete!");
    construct_zvanje_hand();
    //print_zvanje();
    return zvanje_4_size > 0 || zvanje_size > 0;
  }
  public int get_broj_karata() { return broj_karata; }
  public int get_koje_karte(int x) { return koje_karte[x]; }
  public int[] get_array_koje_karte() { return koje_karte; }
  public int get_zvanje_4_size() { return zvanje_4_size; }
  public int get_zvanje_size() { return zvanje_size; }
  public int get_zvanje_4koje(int x) { return zvanje_4koje[x]; }
  public int get_zvanje_id(int x) { return zvanje_id[x]; }
  public int get_zvanje_koliko_karata(int x) { return zvanje_koliko_karata[x]; }
  public int get_zvanje_max() { return zvanje_max; }
  public int get_zvanje_max_sec() { return zvanje_max_sec; }
  public int get_zvanje_tot_val() { return zvanje_tot_val; }
  public void update_ignore_zvanje(int x, boolean state) { ignore_zvanje[x] = state; }
  public boolean get_ignore_zvanje(int x) { return ignore_zvanje[x]; }
  public boolean get_bela() { return bela; }
  public void update_bela(boolean state) { bela = state; }
  public boolean used_kth(int x) { return used[x]; }
  public boolean check_uber(int br, karta first, karta highest, boolean trumped) {
    if(a[br].get_boja() != first.get_boja() && a[br].get_boja() != adut) return true;
    if( trumped && a[br].get_boja() != adut) return true;
    if( !a[br].less_than(highest, adut) ) return true;
    int ima_jacih = 0;
    for(int i = 0; i < 8; ++i)
      if(!used[i] && br != i && a[i].get_boja() == a[br].get_boja() &&
        !a[i].less_than(highest, adut) ) {
          //printf("Varas: nisi uberovao!\n");
          return false;
        }
    return true;
  }
  public boolean check_suit(int br, karta first) {
    if(a[br].get_boja() == first.get_boja()) return true;
    boolean ima_adut = false;
    for(int i = 0; i < 8; ++i) {
      if(!used[i] && br != i && a[i].get_boja() == first.get_boja()) {
        //printf("Varas: nisi postivao boju!\n");
        return false; //ak ne postuje boju onda vara
      }
      if(!used[i] && a[i].get_boja() == adut)
        ima_adut = true;
    }
    if(ima_adut && a[br].get_boja() != adut) {
      //printf("Varas: nisi bacio aduta tj. sijeko!\n");
      return false;
    }
    return true;
  }
  public boolean allowed(int br, int trick_size, boolean trumped, karta first, karta highest) {
    if(used[br]) return false;
    if(trick_size == 0) return true;
    return check_suit(br, first) && check_uber(br, first, highest, trumped);
  }
  public boolean bela_possible() {
    boolean dama = false, kralj = false, used_dama = false, used_kralj = false;
    for(int i = 0; i < 8; ++i)
      if(a[i].get_boja() == adut) {
        if(a[i].get_broj() == 5) {
          dama = true;
          used_dama = used[i];
        }
        else if(a[i].get_broj() == 6) {
          kralj = true;
          used_kralj = used[i];
        }
      }
    return dama && kralj && !used_dama && !used_kralj;
  }
  public boolean is_bela_kth(int x) {
    return a[x].get_boja() == adut && (a[x].get_broj() == 5 || a[x].get_broj() == 6);
  }
  public void play_card(int x) {
    used[x] = true;
  }
  public void update_adut(int x) {
    adut = x;
  }
  public void sort(int l, int r) {
    if(l < r) {
      int i, j, pivot = l;
      i = l; j = r+1;
      while(true) {
   	    do ++i; while( !a[pivot].less_than(a[i], adut) && i <= r );
      	do --j; while( a[pivot].less_than(a[j], adut) );
      	if( i >= j ) break;
   	    karta t = a[i]; a[i] = a[j]; a[j] = t;
      }
      karta t = a[l]; a[l] = a[j]; a[j] = t;

      sort(l, j-1);
      sort(j+1, r);
    }
  }
  public void sort_bf(int n) {
    for(int i = 0; i < n-1; ++i)
      for(int j = i + 1; j < n; ++j)
        if(a[j].less_than(a[i], adut)) {
            karta t = a[i]; a[i] = a[j]; a[j] = t;
        }
  }
  void print_zvanje() {
    final String vr = "789XJQKA";
    final String suit = "CDHS";
    if(broj_karata == 0) {
      System.out.println("Nema zvanja!!!!");
      return ;
    }
    System.out.println("---------ZVANJE--------");
    for(int i = 0; i < broj_karata; ++i) {
      if(koje_karte[i] == -1) System.out.println("-1");
      else {
        int broj = koje_karte[i]%8;
        int boja = koje_karte[i]/8;
        System.out.println(""+vr.charAt(broj)+" "+suit.charAt(boja));
      }
    }
  }
  /*void ispis(int count = 8) {
    printf("Ispis ruke:\n");
    const char suit[] = "HDSC";
    const char vr[] = "789JQKXA";
    for(int i = 0; i < count; ++i) printf(" %d |", i);
    printf("\n");
    for(int i = 0; i < count; ++i)
      if(!used[i])
        printf("%c %c|", vr[ a[i].get_broj() ], suit[ a[i].get_boja() ] );
      else printf(" - |");
  } */
  public karta get_kth(int x) { return a[x]; }
  public void construct_hand(deck d, int k) {
    for(int i = 0; i < 8; ++i)
      a[i] = d.get_kth(k*8+i);
  }
  public void construct_hand(int[] b) {
    for(int i = 0; i < 8; ++i) a[i] = new karta(b[i]);
  }
}
