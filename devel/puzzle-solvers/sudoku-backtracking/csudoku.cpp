/*
 * Copyright (C) 2006 Leo Osvald <leo.osvald@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at
 * 		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <cstring>
#include <fstream>
#include <cmath>
#include <conio.h>
using namespace std;
struct polja {
    int rez;
    vector<int> niz;
};
int br = 0;
class sudoku3 {   //stari program koji logicki rjesava kolko ide
  int evoga[9][9];
  struct sudoku {
    int rez;
    vector<int> niz;

  } polje[9][9];

  void pripremi() {
    for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++) {
        polje[i][j].rez = evoga[j][i];
        for(int h = 1; h <= 9; h++)
          polje[i][j].niz.push_back(h);
      }
    }
  }
  int ispisi(int m, int n) {
    m--; n--;
    int da = 0;
    vector<int> temp, res(10);
    vector<int>::iterator end;
    for(int x = 0; x < 9; x++) {
        if(x != m)
          temp.push_back(polje[n][x].rez);
    }
    for(int y = 0; y < 9; y++) {
        if(y != n)
          temp.push_back(polje[y][m].rez);
    }
    if(m <=2 && n <= 2) {
        for(int i = 0; i <= 2; i++)
          for(int j = 0; j <= 2; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    else if(m <=2 && (n > 2 && n <= 5)) {
        for(int i = 0; i <= 2; i++)
          for(int j = 3; j <= 5; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    else if(m <=2 && (n > 5 && n <= 8)) {
        for(int i = 0; i <= 2; i++)
          for(int j = 6; j <= 8; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    else if((m > 2 && m <= 5) && n <= 2) {
        for(int i = 3; i <= 5; i++)
          for(int j = 0; j <= 2; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    else if((m > 2 && m <= 5) && (n > 2 && n <= 5)) {
        for(int i = 3; i <= 5; i++)
          for(int j = 3; j <= 5; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    else if((m > 2 && m <= 5) && (n > 5 && n <= 8)) {
        for(int i = 3; i <= 5; i++)
          for(int j = 6; j <= 8; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    else if((m > 5 && m <= 8) && (n <= 2)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 0; j <= 2; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    else if((m > 5 && m <= 8) && (n > 2 && n <= 5)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 3; j <= 5; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    else if((m > 5 && m <= 8) && (n > 5 && n <= 8)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 6; j <= 8; j++)
            if(i != m || j != n)
              temp.push_back(polje[j][i].rez);
    }
    sort(temp.begin(), temp.end());
    end = set_difference(polje[n][m].niz.begin(), polje[n][m].niz.end(),
                  temp.begin(), temp.end(), res.begin());
    res.erase(end, res.end());
    /*if(m == 5 && n == 5) {
     for(vector<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
       cout << *iter << " ";
     for(vector<int>::iterator iter = res.begin(); iter != res.end(); iter++)
       cout << *iter << " ";
    } */
    if(res.size() < polje[n][m].niz.size())
      da = 1;
    polje[n][m].niz.clear();
    polje[n][m].niz.resize(res.size());
    copy(res.begin(), res.end(), polje[n][m].niz.begin());
    //cout << "-";
    //if(polje[n][m].rez != 0) {
       //cout << polje[n][m].rez << " {" << n+1 << " " << m+1 << " }" << endl;
    //}
    //cout << " ---- " << polje[n][m].niz.size();
    if(polje[n][m].niz.size() == 1)
     polje[n][m].rez = polje[n][m].niz.front();
     if(da == 1)
       return 1;
     return 0;
  }
  int radi() {
      int br = 0;
      for(int i = 1; i <= 9; i++)
         for(int j = 1; j <= 9; j++) {
            if(polje[i-1][j-1].rez == 0) {
             if(ispisi(j, i) == 1)
               br = 1;
            }
        }
      return br;
  }

  public:

  int mainmain();

} staro;
class csudoku {
    public:
        //var
        int lastx, lasty, pocx, pocy;
        polja polje[10][10];
        int last() {
            lasty = 8; lastx = 8;
            while(polje[lasty][lastx].rez) {
                if(lasty < 0) return 0;
                if(!lastx) {--lasty; lastx = 8;}
                else --lastx;
            }
            return 1;
        }
        void poc() {
            pocy = 0; pocx = 0;
            while(polje[pocy][pocx].rez) {
                if(pocx == 8) ++pocy;
                pocx = (pocx+1)%9;
            }
        }
        void ucitaj() {
            ifstream in("csudoku.txt", ios::in);
            for(int i = 0; i < 9; ++i)
               for(int j = 0; j < 9; ++j)
                  in >> polje[i][j].rez;
        }
        void ispisi() {
            for(int i = 0; i < 9; ++i) printf("-");
            printf("\n");
            for(int i = 0; i < 9; ++i, printf("\n"))
               for(int j = 0; j < 9; ++j)
                  printf("%d ", polje[i][j].rez);
            for(int i = 0; i < 9; ++i) printf("-");
            printf("\n");
        }
        inline int okst(int posy, int posx) {
            for(int i = 0; i < 9; ++i)
              if(i != posy && polje[i][posx].rez == polje[posy][posx].rez) return 0;
            return 1;
        }
        inline int okred(int posy, int posx) {
            for(int i = 0; i < 9; ++i)
              if(i != posx && polje[posy][i].rez == polje[posy][posx].rez) return 0;
            return 1;
        }
        inline int okkv(int n, int m) {

        if(m <=2 && n <= 2) {
        for(int i = 0; i <= 2; i++)
          for(int j = 0; j <= 2; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }
        else if(m <=2 && (n > 2 && n <= 5)) {
        for(int i = 0; i <= 2; i++)
          for(int j = 3; j <= 5; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }
        else if(m <=2 && (n > 5 && n <= 8)) {
        for(int i = 0; i <= 2; i++)
          for(int j = 6; j <= 8; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }
        else if((m > 2 && m <= 5) && n <= 2) {
        for(int i = 3; i <= 5; i++)
          for(int j = 0; j <= 2; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }
        else if((m > 2 && m <= 5) && (n > 2 && n <= 5)) {
        for(int i = 3; i <= 5; i++)
          for(int j = 3; j <= 5; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }
        else if((m > 2 && m <= 5) && (n > 5 && n <= 8)) {
        for(int i = 3; i <= 5; i++)
          for(int j = 6; j <= 8; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }
        else if((m > 5 && m <= 8) && (n <= 2)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 0; j <= 2; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }
        else if((m > 5 && m <= 8) && (n > 2 && n <= 5)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 3; j <= 5; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }
        else if((m > 5 && m <= 8) && (n > 5 && n <= 8)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 6; j <= 8; j++)
            if((i != m || j != n) && polje[j][i].rez == polje[n][m].rez) return 0;
        }

        return 1;
        }
        inline pair<int, int> next(int y, int x) {
            do {
              if(x == 8) ++y;
              x = (x+1)%9;
            } while(polje[y][x].rez);
            return make_pair<int, int>(y, x);
        }
        int rek(int y, int x) {
            ++br;
            //ispisi();  getch()  //za probu
            pair<int, int> npar = next(y, x);
            for(int broj = 1; broj <= 9; ++broj) {
                //rek(y+(x+1)/9-x/9, (x+1)%9);
                polje[y][x].rez = broj;
                if(!okst(y, x) || !okred(y, x) || !okkv(y, x)) {
                    polje[y][x].rez = 0;
                    continue;
                }
                if(y == lasty && x == lastx) return 1;
                if(rek(npar.first, npar.second)) return 1;
            }
            polje[y][x].rez = 0;
            return 0;
        }
        void pocni() {
            if(!last()) return;   //gleda zadnje nerjeseno mjesto ili izlazi ako je sve rjeseno
            poc();
            printf("\n\n%d (%d comp)\n", rek(pocy,pocx), br);
            ispisi();
        }
} curr, prev;
int sudoku3::mainmain() {
      int a, b, t = 0, pr = 1;
    ifstream in("csudoku.txt", ios::in);

    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
          in >> evoga[i][j];
    pripremi();
    while(radi())
    ;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(polje[i][j].rez == 0)
              curr.polje[j][i].niz = polje[i][j].niz;
            else curr.polje[j][i].rez = polje[i][j].rez;
        }
    }
}
int main() {
    staro.mainmain();
    curr.pocni();
    scanf("\n");
    return 0;
}
