/*
 * bela_multiplayer.cpp
 *
 * Copyright (C) 2007 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of Bela multiplayer.
 *
 * Bela multiplayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Bela multiplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bela multiplayer. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <ctime>
#include <cstring>
#include <cstdlib>
#define F "bela_0.txt"
#define IP 0
FILE* f;
class karta {
private:
  int broj, boja;
public:
  karta() {}
  karta(int x) {
    boja = x/8;
    broj = x%8;
  }
  int get_points(int adut) {
    if(boja == adut && broj == 3) return 20;
    else if(boja == adut && broj == 2) return 14;
    else if(broj == 3) return 2;
    else if(broj == 4) return 3;
    else if(broj == 5) return 4;
    else if(broj == 6) return 10;
    else if(broj == 7) return 11;
    return 0;
  }
  bool less_than(karta b, int adut) {
    if(this->boja == b.boja && b.boja == adut) {
      int v_a = this->broj;
      int v_b = b.broj;
      if(v_a == 3) v_a = 100;
      else if(v_a == 2) v_a = 50;
      if(v_b == 3) v_b = 100;
      else if(v_b == 2) v_b = 50;
      return v_a < v_b;
    }
    int v1 = 8*this->boja + this->broj;
    int v2 = 8*b.boja + b.broj;
    return v1 < v2;
  }
  bool jaca_od(karta b, int adut) {
    if(this->boja == adut && b.boja != adut) return true;
    else if(this->boja != adut && b.boja == adut) return false;
    else if(this->boja != adut && b.boja != adut && this->boja != b.boja) return false;
    return !less_than(b, adut);
  }
  int get_broj() {return broj; }
  int get_boja() {return boja; }
  void set_lowest() { broj = -1; boja = -1; }
  void update_broj(int x) { broj = x; }
  void update_boja(int x) { boja = x; }
};
struct inter {
  int host;
  char host_name[25];
  void send_cmd(int cmd, const int ip = IP) {
    char ime[] = F;
    ime[5] = '0' + ip;
    f = fopen(ime, "a");
    fprintf(f, "%d\n", cmd);
    fclose(f);
  }
  void clear_cmd(const int ip = IP) {
    char ime[] = F;
    ime[5] = '0' + ip;
    f = fopen(ime, "w");
    fclose(f);
  }
  int get_cmd(int ip = IP) {
    int cmd;
    char ime[] = F;
    ime[5] = '0' + ip;
    f = fopen(ime, "r");
    if( fscanf(f, "%d", &cmd) == EOF) return -1;
    fclose(f);
    return cmd;
  }
  int pokreni_server() {
    printf("Starting server...\n");
    host = IP;
    strcpy(host_name, F);
    f = fopen(host_name, "w");
    fclose(f);
    for(int i = 0; i < 4; ++i) {
      if(i == IP) continue;
      //posalji svima informaciju da si ti server
      send_cmd(host, i);
    }
    for(int joined = -1; joined < 3; ) {
      if(joined != -1) printf("Nema dovoljno igraca...\n");
      printf("Upisi nesto za start igre. ");
      scanf("%*s");

      f = fopen(host_name, "r");
      printf("Lista onih koji su se joinali:\n");
      for(joined = 0; ; ++joined) {
        int x;
        if( fscanf(f, "%d", &x) == EOF) break;
        printf("%d. %d\n", joined, x);
      }
      fclose(f);
    }
    return 1;
  }
  int join_server() {
    host = get_cmd();
    strcpy(host_name, F);
    host_name[5] = '0' + host;

    printf("Joining server %s (IP = %d)...\n", host_name, host);

    send_cmd(IP, host);
  }
  void get_ready() {
    clear_cmd();
    int x;
    printf("Host/Join (0/1)? ");
    scanf("%d", &x);
    if(x) {
      printf("Cekaj da netko hosta pa stisni kad si spreman.");
      scanf("%*s");
      join_server();
    }
    else if(pokreni_server() )
      printf("Pokretanje gotovo!\n");
    else printf("ERROR: Server se nije uspio pokrenuti.\n");
  }
  int zovi() {
    const char suit[] = "HDSC0";
    char s[3];
    scanf("%s", &s);
    int adut = 0;
    while(1) {
      printf("Upisi adut: \n");
      scanf("%s", &s);
      for(int i = 0; i <= 4; ++i)
        if(suit[i] == s[0]) {
          if(i < 4) return i;
          return -1;
        }
    }
    return -1;
  }
  int play_card() {
    int x = -1;
    while(x < 0 || x >= 8) {
      printf("Upisi koju kartu bacas [1-8]: ");
      scanf("%d", &x);
    }
    return x;
  }
  karta get_card(int ip = IP) {
    int boja, broj;
    karta ret;
    char ime[] = F;
    ime[5] = '0' + ip;
    f = fopen(ime, "r");
    if( fscanf(f, "%d %d", &boja, &broj) == EOF) return -1;
    fclose(f);
    ret.update_boja(boja);
    ret.update_broj(broj);
    return ret;
}
} io;
class information {
private:
  int host;
  int adut, zvali, zvao, zvan_adut;
  int na_redu;
  int zvanja, tko;
  int dealer;
  int n_scores, scores[15][2]; //ovo treba promijeniti
  int *curr_score, *tot_score;
  int *tricks, nth_trick;
  karta *this_trick, highest, first_card;
  int trick_size, trumped;
  int whose_trick;
  int winner;
public:
  information() {
    //scores = new (int*)[2];
    //treba valjda scores = new int[15][2];
    curr_score = new int[2];
    tot_score = new int[2];
    tricks = new int[2];
    this_trick = new karta[4];
    n_scores = 0;
    zvanja = 0;
    host = dealer = io.host;
    na_redu = (dealer+1)%4;
    whose_trick = na_redu;
    nth_trick = 0;
    highest.set_lowest();
    winner = -1;
    zvao = -1;
    zvan_adut = 0;
    trick_size = 0;
    for(int i = 0; i < 2; ++i) {
      curr_score[i] = 0;
      tot_score[i] = 0;
      scores[0][i] = 0;
    }
  }
  void update_adut(int x, int y) { adut = x; zvao = y; zvali = zvao & 1; }
  void update_zvanja(int x, int k) { zvanja = x; tko = k; }
  void update_zvan_adut(int state) { zvan_adut = state; }
  void set_first_turn() { na_redu = (dealer + 1) % 4; }
  void next_turn() { na_redu = (na_redu + 1) % 4; }
  int is_end_trick() { return trick_size >= 4; }
  karta get_first_card() { return first_card; }
  int get_adut() {return adut; }
  int get_dealer() { return dealer; }
  int get_na_redu() { return na_redu; }
  int koja_partija() { return n_scores; }
  int get_trick_size() { return trick_size; }
  int get_trumped() { return trumped; }
  karta get_highest() { return highest; }
  karta get_trick_card(int x) { return this_trick[x]; }
  void play_card(karta x) {
    if(!trick_size || x.jaca_od(highest, adut) ) {
      highest = x;
      whose_trick = na_redu;
    }
    this_trick[trick_size] = x;
    if(!trick_size) first_card = x;
    else if(!trumped && first_card.get_boja() != adut && x.get_boja() == adut)
      trumped = 1;
    ++trick_size;
    next_turn();
  }
  int save_results() {
    if(tricks[tko])
      curr_score[tko] += zvanja;
    if(!tricks[0]) { printf("Stilja\n"); curr_score[1] += 90; }
    else if(!tricks[1]) { printf("Stilja\n"); curr_score[0] += 90; }
    int total = curr_score[0] + curr_score[1];
    if(curr_score[zvali] <= curr_score[1-zvali]) {
      printf("Pali su!\n");
      curr_score[zvali] = 0;
      curr_score[1-zvali] = total;
    }
    for(int i = 0; i < 2; ++i)
      tot_score[i] += scores[n_scores][i] = curr_score[i];

  }
  void save_end_trick() {
    ++tricks[whose_trick & 1];
    for(int i = 0; i < 4; ++i)
      curr_score[whose_trick & 1] += this_trick[i].get_points(adut);
    ++nth_trick;
    if(nth_trick == 8) curr_score[whose_trick & 1] += 10; //zadnji stih
    highest.set_lowest();
    trick_size = 0;
    trumped = 0;
    na_redu = whose_trick;
  }
  void reset() {
    ++n_scores;
    tricks[0] = tricks[1] = 0;
    dealer = (dealer+1) % 4;
    na_redu = (dealer+1) % 4;
    whose_trick = na_redu;
    zvan_adut = 0;
    //
    zvanja = 0;
    nth_trick = 0;
    highest.set_lowest();
    zvao = -1;
    zvan_adut = 0;
    trick_size = 0;
    for(int i = 0; i < 2; ++i) {
      curr_score[i] = 0;
      scores[n_scores][i] = 0;
    }
  }
  int jel_zvano() {return zvan_adut; }
  bool game_over() {
    if(!n_scores) return false;
    if(scores[n_scores-1][0] == scores[n_scores-1][1]) return false;
    if(scores[n_scores-1][0] >= 1001 ^ scores[n_scores-1][1] >= 1001) {
      if(scores[n_scores-1][0] >= 1001) winner = 0;
      else winner = 1;
      return true;
    }
    else if(scores[n_scores-1][0] >= 1001) {
      if(scores[n_scores-1][0] > scores[n_scores-1][1]) winner = 0;
      else winner = 1;
      return true;
    }
    return false;
  }
  void print() {
    const char suit[] = "HDSC";
    const char vr[] = "789JQKXA";
    printf("Info... (Partija %d) (Adut %c) (Stih %d)\n", n_scores, suit[adut], nth_trick);
    printf("Bodovi: MI: %d, VI: %d\t, Ukupno: %d %d\n", curr_score[0], curr_score[1],
        tot_score[0], tot_score[1]);
    printf("Karte u ovom %d. stihu (od %d) (Trumped = %d):\n", nth_trick, trick_size, trumped);
    for(int i = 0; i < trick_size; ++i)
      printf("%c %c|", vr[this_trick[i].get_broj()], suit[this_trick[i].get_boja()] );
    if(trick_size) printf("\nNajjaca dosad (IP = %d): %c %c\n", whose_trick,
      vr[highest.get_broj()], suit[highest.get_boja()] );
  }
};
class deck;
class hand {
private:
  karta *a;
  int *used;
  int adut;
public:
  hand() {
    a = new karta[8];
    used = new int[8];
    for(int i = 0; i < 8; ++i) used[i] = 0;
  }
  int check_uber(int br, karta first, karta highest, int trumped) {
    if(a[br].get_boja() != first.get_boja()) return 1;
    if( trumped && a[br].get_boja() != adut) return 1;
    if( !a[br].less_than(highest, adut) ) return 1;
    int ima_jacih = 0;
    for(int i = 0; i < 8; ++i)
      if(!used[i] && br != i && a[i].get_boja() == a[br].get_boja() &&
        !a[i].less_than(highest, adut) ) {
          printf("Varas: nisi uberovao!\n");
          return 0;
        }
    return 1;
  }
  int check_suit(int br, karta first) {
    if(a[br].get_boja() == first.get_boja()) return 1;
    int ima_adut = 0;
    for(int i = 0; i < 8; ++i) {
      if(!used[i] && br != i && a[i].get_boja() == first.get_boja()) {
        printf("Varas: nisi postivao boju!\n");
        return 0; //ak ne postuje boju onda vara
      }
      if(!used[i] && a[i].get_boja() == adut)
        ima_adut = 1;
    }
    if(ima_adut && a[br].get_boja() != adut) {
      printf("Varas: nisi bacio aduta tj. sijeko!\n");
      return 0;
    }
    return 1;
  }
  int allowed(int br, int trick_size, int trumped, karta first, karta highest) {
    if(used[br]) return 0;
    if( !trick_size ) return 1;
    return check_suit(br, first) && check_uber(br, first, highest, trumped);
  }
  void play_card(int x) {
    used[x] = 1;
  }
  void update_adut(int x) {
    adut = x;
  }
  void swap(int k1, int k2) {
    karta t = a[k1];
    a[k1] = a[k2];
    a[k2] = t;
  }
  void sort(int l, int r) {
    if(l < r) {
      int i, j, pivot = l;
      i = l; j = r+1;
      while(1) {
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
  void ispis(int count = 8) {
    printf("Ispis ruke:\n");
    const char suit[] = "HDSC";
    const char vr[] = "789JQKXA";
    for(int i = 0; i < count; ++i) printf(" %d |", i);
    printf("\n");
    for(int i = 0; i < count; ++i)
      if(!used[i])
        printf("%c %c|", vr[ a[i].get_broj() ], suit[ a[i].get_boja() ] );
      else printf(" - |");
  }
  void load_hand();
  hand(deck , int );
  karta get_kth(int x) { return a[x]; }
};
class deck {
private:
  karta *a;
  int number_of_swaps;
public:
  karta get_kth(int x) {return a[x]; }
  void shuffle() {
    number_of_swaps = 100;
    srand(time(0));
    a = new karta[32];
    for(int i = 0; i < 32; ++i) a[i] = karta(i); //mozda treba new...
    for(int i = 0; i < number_of_swaps; ++i) {
      int r1 = (rand()+i)%32;
      int r2 = (rand()+i/2)%32;
      karta t = a[r1]; a[r1] = a[r2]; a[r2] = t;
    }
  }
  void ispis() {
    printf("Ispis ruke:\n");
    const char suit[] = "HDSC";
    const char vr[] = "789JQKXA";
    for(int i = 0; i < 32; ++i) {
      if(i % 8 == 0) printf("Igrac %d:\n", i/8);
      printf("%c %c\n", vr[ a[i].get_broj() ], suit[ a[i].get_boja() ] );
    }
  }
};
hand::hand(deck d, int from) {
  a = new karta[8];
  for(int i = 0; i < 8; ++i)
    a[i] = d.get_kth(from+i);
}
void hand::load_hand() {
  printf("Loading hand...\n");
  adut = -1;
  f = fopen(F, "r");
  for(int i = 0; i < 8; ++i) {
    int broj, boja;
    fscanf(f, "%d %d", &boja, &broj);
    a[i].update_boja(boja); //treba mozda new...
    a[i].update_broj(broj);
  }
  fclose(f);
  io.clear_cmd();
}
class glavni {
private:
  hand ruka;
  deck d;
  information info;
public:
  void jedna_partija() {
  }
  void kreni() {
    info = information();
    jedna_partija();
  }
  void send_hand(int who, int from) {
    printf("Sending hand...\n");
    for(int i = 0; i < 8; ++i) {
      io.send_cmd( d.get_kth(from+i).get_boja(), who);
      io.send_cmd( d.get_kth(from+i).get_broj(), who);
    }
  }
  void reveal_cards() {
    ruka.sort(0, 8);
    ruka.ispis();
  }
  void play_trick() {
    ruka.ispis();
    printf("Igranje stiha:\n");
    while( !info.is_end_trick() ) {
      karta curr;
      info.print();
      if(info.get_na_redu() == IP) {
        ruka.ispis();
        int x;
        while(1) {
          x = io.play_card();
          if(ruka.allowed(x, info.get_trick_size(), info.get_trumped(),
            info.get_first_card(), info.get_highest()) ) break;
        }
        ruka.play_card(x);
        //tu trebaju provjere doc
        io.clear_cmd(io.host);
        io.send_cmd( ruka.get_kth(x).get_boja(), io.host);
        io.send_cmd( ruka.get_kth(x).get_broj(), io.host);
      }
      else {
        printf("Upisi nesto kad (%d) baci kartu ", info.get_na_redu());
        scanf("%*s");
      }
      printf("Bacena je karta...\n");
      curr = io.get_card(io.host);
      info.play_card( curr );
    }
  }
  void common() {
    ruka.load_hand();
    ruka.sort(0, 6);
    ruka.ispis(6);

    //posalji da jos nije odredjen adut
    if(IP == io.host) {
      io.clear_cmd(io.host);
      io.send_cmd(-2, io.host);
    }

    printf("Upisi nesto da pocne licitiranje od (%d): ", info.get_na_redu());
    scanf("%*s");
    //licitaza
    for( info.set_first_turn(); !info.jel_zvano();  ) {
      if(info.get_na_redu() == IP) {
        printf("Sta zoves (H D S C %s)? ",
         (info.get_dealer() != info.get_na_redu()) ? "0" : "");
        int adut = -1;
        while(1) {
          adut = io.zovi();
          if(info.get_dealer() == info.get_na_redu() && adut == -1) {
            printf("Nemoze!\n");
            continue;
          }
          break;
        }
        if(adut != -1) {
          io.clear_cmd(io.host);
          io.send_cmd(adut, io.host);
          io.send_cmd(io.host, io.host);
        }
      }
      else {
        printf("Upisi nesto kad netko zove/ne zove ");
        scanf("%*s");
      }
      int stanje = io.get_cmd(io.host);
      if(stanje != -2) info.update_zvan_adut(1); //zvano je
      else info.next_turn(); //netko drugi je sad na redu da zove
    }

    info.update_adut(io.get_cmd(io.host), info.get_na_redu());
    ruka.update_adut( info.get_adut() );
    printf("Zvan je adut %d\n", info.get_adut());

    printf("Sada ce se otrkiti talon...\n");
    reveal_cards();
    printf("Talon otkriven...\n");
    //zvanje

    //igra
    info.set_first_turn();

    for(int i = 0; i < 8; ++i) {
      play_trick();
      info.save_end_trick();
    }

    info.save_results();
    info.reset();

    io.clear_cmd();
  }
  void deal() {
    printf("Mjesam deck...\n");
    d.shuffle();
    d.ispis();
    int k = info.get_na_redu();
    printf("Dijelim karte...\n");
    for(int i = 0; i < 4; ++i, k = (k+1) % 4) {
      io.clear_cmd(k);
      send_hand(k, 8*i);
    }
  }
  void start_server() {
    info = information();
    while(!info.game_over()) {
      deal();
      common();
    }
  }
  void start_client() {
    info = information();
    while(!info.game_over()) {
      printf("Upisi nesto kad se podijele karte: ");
      scanf("%*s");

      common();
    }
  }
  void menu() {
    io.get_ready();
    if(io.host == IP) start_server();
    else start_client();
  }
};
int main() {
  glavni g;
  g.menu();
  scanf("\n");
  return 0;
}
