/*
 * Copyright (C) 2005 Leo Osvald <leo.osvald@gmail.com>
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

#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <algorithm>
#include <vector.h>
#include <functional>
#include <fstream.h>
int evoga[9][9]; /*=      {3, 0, 1, 4, 5, 6,
                        0, 6, 7, 8, 0, 0,
                        1, 7, 0, 0, 0, 0,
                        4, 0, 0, 0, 0, 0,
                        2, 0, 0, 1, 3, 4,
                        5, 8, 5, 6, 0, 0};*/
struct sudoku {
    int rez;
    vector<int> niz;
    void init(int x, int y);
} polje[9][9];
void pripremi() {
    for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++) {
        polje[i][j].init(i, j);
        for(int h = 1; h <= 9; h++)
          polje[i][j].niz.push_back(h);
      }
    }
}
int ispisi(int m, int n) {
    m--; n--;
    int da = 0;
    vector<int> temp, res(10), temp2;
    vector<int>::iterator end;
    for(int x = 0; x < 9; x++) {
        if(x != m) {
          temp.push_back(polje[n][x].rez);
          temp2.insert(temp2.end(), polje[n][x].niz.begin(), polje[n][x].niz.end());
        }

    }
    for(int y = 0; y < 9; y++) {
        if(y != n) {
          temp.push_back(polje[y][m].rez);
          temp2.insert(temp2.end(), polje[y][m].niz.begin(), polje[y][m].niz.end());
        }
    }
    if(m <=2 && n <= 2) {
        for(int i = 0; i <= 2; i++)
          for(int j = 0; j <= 2; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    else if(m <=2 && (n > 2 && n <= 5)) {
        for(int i = 0; i <= 2; i++)
          for(int j = 3; j <= 5; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    else if(m <=2 && (n > 5 && n <= 8)) {
        for(int i = 0; i <= 2; i++)
          for(int j = 6; j <= 8; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    else if((m > 2 && m <= 5) && n <= 2) {
        for(int i = 3; i <= 5; i++)
          for(int j = 0; j <= 2; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    else if((m > 2 && m <= 5) && (n > 2 && n <= 5)) {
        for(int i = 3; i <= 5; i++)
          for(int j = 3; j <= 5; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    else if((m > 2 && m <= 5) && (n > 5 && n <= 8)) {
        for(int i = 3; i <= 5; i++)
          for(int j = 6; j <= 8; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    else if((m > 5 && m <= 8) && (n <= 2)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 0; j <= 2; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    else if((m > 5 && m <= 8) && (n > 2 && n <= 5)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 3; j <= 5; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    else if((m > 5 && m <= 8) && (n > 5 && n <= 8)) {
        for(int i = 6; i <= 8; i++)
          for(int j = 6; j <= 8; j++)
            if(i != m || j != n) {
              temp.push_back(polje[j][i].rez);
              temp2.insert(temp2.end(), polje[j][i].niz.begin(), polje[j][i].niz.end());
            }
    }
    sort(temp.begin(), temp.end());
    sort(temp2.begin(), temp2.end());
    end = set_difference(polje[n][m].niz.begin(), polje[n][m].niz.end(),
                  temp.begin(), temp.end(), res.begin());
    res.erase(end, res.end());
    if(res.size() < polje[n][m].niz.size())
      da = 1;
    polje[n][m].niz.clear();
    polje[n][m].niz.resize(res.size());
    copy(res.begin(), res.end(), polje[n][m].niz.begin());
    res.clear();
    end = set_difference(polje[n][m].niz.begin(), polje[n][m].niz.end(), temp2.begin(), temp2.end(),
                   res.begin());
    res.erase(end, res.end());
    /*if(res.size() == 0) {
         polje[n][m].niz.clear();
         polje[n][m].niz.resize(res.size());
         copy(res.begin(), res.end(), polje[n][m].niz.begin());
         cout << "bingo" << m << n;
         da = 1;
    } */
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
    cout << "---" << br << "---" << endl;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++)
            cout << polje[j][i].rez << " ";
        cout << endl;
    }
    cout << "_________" << endl;
    return br;
}
int main() {
    int a, b, t = 0, pr = 1;
    ifstream in("sudoku.txt", ios::in);

    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
          in >> evoga[i][j];
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++)
            cout << evoga[i][j] << " ";
        cout << endl;
    }
    pripremi();
    cout << "Done..." << endl;
    while(radi())
    ;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(polje[i][j].rez == 0) {
              cout << "[" << i+1 << " " << j+1 << "] - ";
              for(vector<int>::iterator iter = polje[i][j].niz.begin();
                  iter != polje[i][j].niz.end(); iter++)
                  cout << *iter << " ";
              cout << endl;
            }
        }
    }
    getch();
}
void sudoku::init(int x, int y) {
    rez = evoga[y][x];
}
