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
#include <ctype.h>
#include <fstream.h>
#include <string.h>
using namespace std;
int dr_max = 0;
class save_load {
   public:
       void spremi();
       bool loadaj(int &dr_pr2);
};
save_load l_s;
class hehe {
    friend class save_load;
    private:
        char a[100];
        float zbroj, polu_ocjena;
    public:
        char upis, temp;
        char naziv[15];
        int brojilo, zaokruzeno;
    void racunaj();
    void izbrisi();
    void preslozi(int i2);
    void prikazi();
};
hehe predmeti[15];
inline void hehe::racunaj() {
    zbroj = 0;
    if(upis == '-') {
      upis = getch();
      izbrisi();
     }
     else
       a[brojilo++] = upis;
     for(int l = 0; l < brojilo; l++) {
       if(a[l] == '6') polu_ocjena = 1.5;
       else if(a[l] == '7') polu_ocjena = 2.5;
       else if(a[l] == '8') polu_ocjena = 3.5;
       else if(a[l] == '9') polu_ocjena = 4.5;
       else polu_ocjena = a[l]-'0';
       zbroj+=polu_ocjena;
     }
     if(zbroj/brojilo >= 4.5) zaokruzeno = 5;
     else if(zbroj/brojilo >= 3.5) zaokruzeno = 4;
     else if(zbroj/brojilo >=2.5) zaokruzeno = 3;
     else if(zbroj/brojilo >= 1.5) zaokruzeno = 2;
     else zaokruzeno = 1;
     cout.precision(3);
     cout << strupr(naziv) << " prosjek je za sada " << zbroj/(brojilo) << "\n";
};
void hehe::izbrisi() {
    for(int I = 0; I <= brojilo; I++) {
        if(upis == a[I]) {
            preslozi(I);
            break;
        }
    }
}
void hehe::preslozi(int i2) {
    temp = a[--brojilo];
    a[brojilo] = a[i2];
    a[i2] = temp;
}
void hehe::prikazi() {
    for(int l = 0; l < brojilo; l++) {
        if(a[l] == '6') printf("1/2 ");
        else if(a[l] == '7') printf("2/3 ");
        else if(a[l] == '8') printf("3/4 ");
        else if(a[l] == '9') printf("4/5 ");
        else printf("%c ", a[l]);
    }
    cout << "\n";
}
class opci_uspjeh {
    private:
        float prosjek;
        int uspjeh;
    public:
    void prikazi() {
        prosjek = 0;
        for(int i = 0; i <= dr_max; i++)
            prosjek += predmeti[i].zaokruzeno;
        prosjek /= (dr_max+1);
        if(prosjek >= 4.5) uspjeh = 5;
        else if(prosjek >= 3.5) uspjeh = 4;
        else if(prosjek >= 2.5) uspjeh = 3;
        else if(prosjek >= 1.5) uspjeh = 2;
        else uspjeh = 1;
        cout.precision(3);
        cout << "Opci uspjeh vam je " << prosjek
             << ", a prolazite sa " << uspjeh << ".\n";
    }
} uspjeh;

void save_load::spremi() {
   string ime_save;

   cout << "\nUpisite ime datoteke: ";
   cin >> ime_save;
   fstream van (ime_save.c_str(), ios::out);
   van << dr_max << endl;
   for(int i = 0; i <= dr_max; i++) {
       van << predmeti[i].naziv << " " << predmeti[i].brojilo << " ";
       for(int j = 0; j <= predmeti[i].brojilo; j++)
          van << predmeti[i].a[j] << " ";
       van << "\n";
   }
}
bool save_load::loadaj(int &dr_pr2) {
    string ime_load; char c;

    cout << "Upisite ime datoteke koju zelite otvoriti: ";
    ponovni_upis:
    cin >> ime_load;
    fstream nutra (ime_load.c_str(), ios::in);
    if(!nutra) {
        cerr << "\nNe postoji datoteka \"" << ime_load << "\"!" << endl
             << "Molim upisite ponovno, a ako ne zelite otvoriti niti jednu,"
             << " pritisnite \'q\'!" << endl;
        c = getch();
        if(c == 'q' || c == 'Q')
          return 0;
        else
          goto ponovni_upis;
    }
    nutra >> dr_max;
    dr_pr2 = dr_max;
    for(int i = 0; i <= dr_max; i++) {
        nutra >> predmeti[i].naziv >> predmeti[i].brojilo;
        cout << predmeti[i].naziv << " ";
        for(int j = 0; j < predmeti[i].brojilo; j++) {
          nutra >> predmeti[i].a[j];
          cout << predmeti[i].a[j] << " ";
        }
        cout << "\n";
    }
    return 1;
}
void objasni() {
    cout << "h  -  help" << endl
         << "+  -  prikazivanje ocjena pojedinog predmeta" << endl
         << "*  -  prikazivanje trenutacnog opceg uspjeha" << endl
         << "0  -  prebacivanje na novi/postojeci predmet" << endl
         << "q  -  izlazak" << endl
         << "1-5  -  ocjene od jedan do pet" << endl
         << "6 - 1/2; 7 - 2/3; 8 - 3/4; 9 - 4/5" << endl;
}
int main () {
    int i, dr_pr = 0; char c, upis[15];
    int nadjeno = 0; bool loadano = false;

    cout << "Zelite li otvoriti postojecu datoteku?<d/n>" << endl;
    while((c=getch()) != 'd' && c != 'n' && c != 'D' && c != 'N')
      cout << "Krivi znak molim pritisnite ponovno!\n";
    if(c == 'd' || c == 'D')
      loadano = l_s.loadaj(dr_pr);
    if(!loadano) {
      for(i = 0; i < 15; i++)
          predmeti[i].brojilo = 0;
      printf("\nUpisite predmet: ");
      scanf("%s", &predmeti[0].naziv);
      printf("Sada ocjene:\n");
    }
    ponovi:
    while(isdigit(predmeti[dr_pr].upis = getch()) || predmeti[dr_pr].upis == '-'
          || predmeti[dr_pr].upis == '+' || predmeti[dr_pr].upis == '*'
          || isspace(predmeti[dr_pr].upis)
          || tolower(predmeti[dr_pr].upis) == 'q') {
        if(predmeti[dr_pr].upis == '0') {
          printf("Upisite predmet: ");
          scanf("%s", &upis);
          for(i = 0; i <= dr_max; i++) {
              if(strcmpi(upis, predmeti[i].naziv) == 0) {
                dr_pr = i;
                nadjeno = 1;
                break;
              }
          }
          if(dr_pr > dr_max)
              dr_max = dr_pr;
          if(!nadjeno) {
            strcpy(predmeti[++dr_max].naziv, upis); predmeti[dr_max].brojilo = 0;
            dr_pr = dr_max;
          }
          nadjeno = 0;
          printf("Sada upisujte ocjene:\n");
          continue;
        }
        else if(predmeti[dr_pr].upis == '+') {
          printf("Upisite za koji predmet zelite vidjeti ocjene: ");
          scanf("%s", &upis);
          for(i = 0; i <= dr_pr; i++) {
            if(strcmpi(upis, predmeti[i].naziv) == 0)
              predmeti[i].prikazi();
          }
        }
        else if(predmeti[dr_pr].upis == '*') uspjeh.prikazi();
        else if(tolower(predmeti[dr_pr].upis) == 'q')
          break;
        else if(!isspace(predmeti[dr_pr].upis))
          predmeti[dr_pr].racunaj();
    }
    if(predmeti[dr_pr].upis != 'q' && predmeti[dr_pr].upis != 'Q') {
        if(predmeti[dr_pr].upis == 'h' || predmeti[dr_pr].upis == 'H')
          objasni();
        else
          cout << "Upisali ste krivi znak, molim upisite nesto drugo"
               << "(za help pritisnite 'h')\n";
        goto ponovi;
    }
    cout << "Zelite li spremiti podatke?<d/n>\n";
    while((c = getch()) != 'd' && c != 'D' && c != 'n' && c != 'N')
       cout << "Krivi znak molim pritisnite ponovno!\n";
    if(c == 'd' || c == 'D')
      l_s.spremi();
    return 0;
}
