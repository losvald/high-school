/*
 * mastermind.cpp
 *
 * Copyright (C) 2007 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of Mastermind Solver.
 *
 * Mastermind Solver is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Mastermind Solver is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mastermind Solver. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;
struct lista { //moja single-linked lista (da bude brze!)
  int code;
  lista* next; //pointer na slijedeci
} code_list[(1 << 12)+1];
int gencode, was, n; //n - trenutni broj mogucih kodova
int max_color = 6; //broj boja s kojima se igra
bool was_code[1 << 12]; //koji su kodovi iskoristeni kod pogadjanja
const int maxn = 1 << 12; //broj kombinacija od 8 boja na 4 mjesta = 8^4 tj. 2^12
const int maxtry = 12; //maximalan broj pokusaja pri igranju
int scores[] = {0,1,2,3,4,5,6,7,8,10,11,12,15,20,-1}; //hashevi za Stanja pogodaka
void print_code(int x) {//ispis nekog Koda slovcano (umjesto octal)
  static const char color[] = {'a','b','c','d','e','f','g','h'}; //imena boja
  for(int i = 0; i < 4; ++i)
    printf("%c", color[((07 << 3*i) & x) >> 3*i]);
}
int make_guess() {//vraca hash za Upisani kod (octal broj [00000, 08888])
  int ret = 0;
  char s[10]; scanf("%s", s);
  for(int i = 0; i < 4; ++i)
    ret |= (tolower(s[i])-'a') << 3*i;
  return ret;
}
void print_score(int x) {//ispis Stanja Pogodaka slovima (umjesto octal)
  for(int i = 0; i < x/5; ++i) printf("R");
  for(int i = 0; i < x%5; ++i) printf("W");
  printf("\n");
}
int make_score() {//vraca hash za upisano Stanje Pogodaka
  int ret = 0;
  for(char ch; (ch = cin.get()) != '\n'; ) {//sve dok ne ucita Enter
    if(toupper(ch) == 'R') ret += 5;
    else if(toupper(ch) == 'W') ++ret;
  }
  return ret;
}
int find(int x, int code) {//trazi boju x na Krivom mjestu
  for(int i = 0; i < 4; ++i) {
    if((1 << i) & was) continue;
    if(((07 << 3*i) & code) == (x << 3*i)) {
      was |= 1 << i; //naso je, i to mjesto je onda iskoristeno
      return 1;
    }
  }
  return 0; //nije naso
}
int eval_guess(int x, int code) {
  //vraca hash za Stanje Pogodaka ako je pokusaj x, kompova sifra code
  int ret = 0, was2 = 0; was = 0;
  for(int i = 0; i < 4; ++i) {//za sva 4 mjesta
    if(((07 << 3*i) & x) == ((07 << 3*i) & code)) {
      //ako je pogodjena Prava boja na Pravom mjestu, "stavi" Crveno (C)
      ret += 5;
      was |= 1 << i;
      was2 |= 1 << i;
    }
  }
  for(int i = 0; i < 4; ++i) {//za sva 4 mjesta
    if((1 << i) & was2) continue; //ako nije to mjesto vec pogodjeno
    //ako je pogodjena Prava boja ali na Krivom mjestu, "stavi" Bijelo (B)
    ret += find(((07 << 3*i) & x) >> 3*i, code);
  }
  return ret;
}
int eliminate(int x, int sc) {//vraca broj eliminiranih kodova i
  //eliminira iz liste nemoguce kodove ako je Stanje Pogodaka sc, a pokusaj x
  int ret = 0;
  for(lista *it = code_list[maxn].next, *prev = &code_list[maxn]; ; it = it->next) {
    if(eval_guess(x, it->code) != sc) {
      prev->next = it->next; //brise trenutni kod iz liste mogucih kodova
      ++ret;
    }
    else prev = it;
    if(!it->next) break; //ak je kraj liste, izadji
  }
  return ret;
}
int count_elim(int x, int sc) {
  //vraca broj nemogucih kodova iz liste ako je Stanje Pogodaka sc, a pokusaj je x
  int ret = 0;
  //za sve moguce slucajeve tvog koda koji komp pogadja
  for(lista* it = code_list[maxn].next; ; it = it->next) {
    //broji one koji su nemoguci sa ovim Stanjem Pogodaka (sc) i ovim pokusajem (x)
    if(eval_guess(x, it->code) != sc) ++ret;
    if(!it->next) break; //ak je kraj liste, izadji
  }
  return ret;
}
int valid_color(const int x) {
  for(int i = 0; i < 4; ++i)
    if( (((07 << 3*i) & x) >> 3*i) >= max_color ) //ako neka boja nije dopustena vrati 0
      return 0;
  return 1;
}
int gen_aabb() {//generira random kod oblika aabb, abab ili abba
  int r1, r2, rs1, rs2, ret = 0;
  for(r1 = rand()%8; (r2 = rand()%8) == r1; ) ; //dobiva 2 razlicita random broja
  for(rs1 = rand()%4; (rs2 = rand()%4) == rs1; ) ; //dobiva 2 razlicita random broja
  for(int i = 0; i < 4; ++i) {
    if(i == rs1 || i == rs2) ret |= r2 << 3*i;
    else ret |= r1 << 3*i;
  }
  return ret;
}
int generate_code() {//vraca hash za zamisljeni Kod koji ti pogadjas
  gencode = 0;
  for(int i = 0; i < 4; ++i) {
    int r = rand()%8;
    gencode |= (r << 3*i);
  }
  return gencode;
}
void init() {//inicijalizacija Codemaker igre
  n = maxn; //broj mogucih kodova je 4096 jer svi na pocetku kandidati
  //konstruira listu mogucih kodova
  for(int i = 0; i < maxn; ++i) {
    code_list[i].code = i;
    code_list[i].next = &code_list[i+1];
  }
  code_list[maxn-1].next = NULL; //zadnji nema slijedeceg
  code_list[maxn].code = -1; //sentinel kod za pocetak liste
  code_list[maxn].next = &code_list[0];
}
int play_breaker() {//ovdje ti pogadjas kompov kod
  generate_code(); //generira kompov kod tj. komp zamisli neki kod
  //print_code(gencode);
  //sad ga ti trebas pogodit al imas maxtry pokusaja
  for(int ntry = 1; ntry <= maxtry; ++ntry) {
    //print_code(gencode);
    printf("%2d. |    |    \\\r", ntry);
    printf("%2d. |", ntry);
    //ucita tvoje kod i izbaci Stanje Pogodaka za tvoj kod
    int myscore = eval_guess(make_guess(), gencode);
    printf("     \\___|    /\r     \\___|");
    print_score(myscore); //ispisuje Stanje Pogodaka za tvoj kod
    if(myscore == 20) {//ak si pogodio kompov kod onda si pobijedio
      printf("You won! Congratulations!\n\n");
      return 1;
    }
  }
  printf("Loser!\n\n"); //ak nisi pogodio u maxtry pokusaja onda si izgubio
  return 0;
}
int play_maker() {//ovdje ti zamisljas kod a komp pogadja
  int first_guess;
  do {
    first_guess  = gen_aabb(); //uzmi random kod tipa aabb kao prvi pokusaj
  } while(!valid_color(first_guess));
  init();
  printf("%2d. |", 1); print_code(first_guess);
  printf("|    \\\n     \\___|    /\r     \\___|");
  was_code[first_guess] = 1; //first_gueess je vec iskoristen
  int first_score = make_score();
  if(first_score == 20) {//ak je komp iz prve pogodio izbubio si
    printf("Loser!\n\n");
    return 0;
  }
  n -= eliminate(first_guess, first_score);
  //sad komp treba pogodit tvoj kod al ima maxtry pokusaja
  int ntry;
  for(ntry = 2; ntry <= maxtry && n > 1; ++ntry) {
    //greedy algoritam za "optimalno" pogadjanje:
    int best_case = 0, best_code = 0000;
    //za sve moguce pokusaje pogadjanja tj. za svih 4096 kodova
    for(int code = 0; code < maxn; ++code) {
      if(!valid_color(code)) continue;
      if(was_code[code]) continue; //ako taj kod nije iskoristen
      if(code % 32 == 0) //ispis na kolko % je kod razmisljanja
        printf("\r%2d. |%3d%%|", ntry, (code*100)/maxn);
      int minimum = maxn;
      //za sva moguca Stanje Pogodaka s tim pokusajem
      for(int *sc = &scores[0]; *sc > -1; ++sc) {
        //pogleda koliko bi ovaj pokusaj eliminirao mogucih kodova
        int curr = count_elim(code, *sc);
        //ali pamti samo najgori slucaj (jer se nezna sta se pogadja)
        if(curr && curr != n) minimum = min(minimum, curr);
      }
      //ali odaberi onaj pokusaj tj. kod koji eliminira najvise u najgorem slucaju
      if(minimum > best_case && minimum != maxn) {
        best_case = minimum;
        best_code = code; //updataj najbolji pokusaj
      }
    }
    printf("\r%2d. |%3d%%|    \\", ntry, 100);
    printf("\r%2d. |", ntry); print_code(best_code);
    printf("\n     \\___|    /\r     \\___|");
    int myscore = make_score(); //ucita Stanje Pogodaka
    if(myscore == 20) {//ako je kod pogodjen onda je pobjeda
      printf("Loser!\n\n");
      return 0;
    }
    was_code[best_code] = true; //ovaj pogodok je iskoristen
    //eliminira sve kodove koji nisu moguci (zbog Stanje Pogodaka)
    n -= eliminate(best_code, myscore);
  }
  printf("\r%2d. |", ntry); print_code(code_list[maxn].next->code);
  printf("|    \\\n     \\___|    /\r     \\___|CCCC\n");
  //komp je pogodio tvoj kod, tj. ti si izgubio (kao i uvijek :) )
  printf("Loser!\n\n");
  return 0;
}
void print_help(int mod) {
  if(mod == 1) {
    printf("HOW TO PLAY:");
    printf("\n1) Imagine a 4-color code consisting of colors a-h, e.g. "); print_code(rand()%maxn);
    printf("\n2) The computer guesses your code; you type in responses consisting of:");
    printf("\n\tR (for each correctly guessed color in the right position)");
    printf("\n\tW (for each correctly guessed color in the wrong position)");
    printf("\n   To confirm the response, press Enter. For example,");
    printf("\n     RRW, RRRR (for broken code), WrRw, 0, W, (just Enter), r, WWWW.\n");
    printf("   Note: The order and case of the letters are irrelevant.\n\n");
    printf("   Example: you had imagined the code: \thead\n");
    printf("     and the computer makes the guess: \tafae\n");
    printf("     you must respond with:            \tRB\n");
    printf("   Explanation: 'a' is the correctly guessed color in the right position\n");
    printf("     and thus the 'R'; 'e' appears in the code but not in the right position\n");
    printf("     and thus the 'W'. (Note that adding yet another 'W' would not be correct\n");
    printf("     because the single 'a' that appears in the code is already guessed.)");
    printf("\n3) If the computer does not break your code in %2d attempts, you win.", maxtry);
    printf("\n4) If the computer breaks your code in at most %2d attempts, you lose.", maxtry);
  }
  else if(mod == 2) {
    printf("HOW TO PLAY:");
    printf("\n1) The computer chooses a 4-color code consisting of colors a-h, e.g. "); print_code(rand()%maxn);
    printf("\n2) You try to break the code; the computer gives response consisting of:");
    printf("\n\tR (for each correctly guessed color in the right position)");
    printf("\n\tW (for each correctly guessed color in the wrong position)");
    printf("\n   For example, RRW, RRRR (for broken code), WRRW, 0, W, (empty), r, WWWW.\n");
    printf("   To make a guess, enter a 4-color code, e.g. fade, and press Enter to confirm.\n");
    printf("   Note: The order and case of the letters are irrelevant.\n\n");
    printf("   Example: you make the guess: \thehe\n");
    printf("     and the computer responds: \tRRW\n");
    printf("   Explanation: two colors are guessed at the right position and\n");
    printf("     an additional one in the wrong position. Therefore, the computer's code\n");
    printf("     must be one of the following: heea, eeha, heeb, eehb, heec, eehc,\n");
    printf("     heed, eehc, hhae, hhbe, hhce, hhde, haee, hbee, hcee, hdee, hfee, hgee,\n");
    printf("     hhfe, hhge, eahe, ebhe, eche, edhe, efhe, eghe, ahhe, bhhe, chhe, dhhe,\n");
    printf("     fhee, ghhe, heef, eehf, heeg, eehg, heah, hebh, hech, hedh, hefh, hegh,\n");
    printf("     aehh, behh, cehh, dehh, fehh, gehh.\n");
    printf("\n3) If you break the code in at most %2d attempts, you win.", maxtry);
    printf("\n4) If you fail to break the code in %2d attempts, you lose.", maxtry);
  }
  printf("\n\n");
}
int main() {
  srand(time(0)); //randomize seed
  for(int mod = 1; mod != 3;) {
    printf("Type mode (1/2) and press Enter:\n1 - Codemaker\t2 - Codebreaker\n\t3 - Exit\n");
    scanf("%d%*c", &mod); //odaberi Mod
    if(mod != 3) print_help(mod);
    if(mod == 1) play_maker();
    else if(mod == 2) play_breaker();
  }
  printf("Thanks for playing!\nPlease send bug reports to: leo.osvald@gmail.com\n\n");
  char ch;
  do {
    printf("Press 'q'/'Q' then Enter to quit.\n");
  } while(tolower(ch = cin.get()) != 'q');
  return 0;
}
