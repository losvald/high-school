/*
 * incremental_solver.cpp
 *
 * Copyright (C) 2005 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of Scotland Yard Solver.
 *
 * Scotland Yard Solver is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Scotland Yard Solver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Scotland Yard Solver. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <queue>
#include <deque>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
struct ploca {
    int br[50];
    deque<int> d;
    char voz[50];
} polje[200];
struct detektivi {
    int det[15];
} de[5];
int main() {
    //inicijaliziranje scotland yard ploce:
        polje[1].br[1] = 8; polje[1].voz[1] = 'c';
        polje[1].br[2] = 9; polje[1].voz[2] = 'c';
        polje[1].br[3] = 58; polje[1].voz[3] = 'b';
        polje[1].br[4] = 46; polje[1].voz[4] = 'b';
        polje[1].br[5] = 46; polje[1].voz[5] = 'u';

        polje[2].br[1] = 20; polje[2].voz[1] = 'c';
        polje[2].br[2] = 10; polje[2].voz[2] = 'c';

        polje[3].br[1] = 4; polje[3].voz[1] = 'c';
        polje[3].br[2] = 11; polje[3].voz[2] = 'c';
        polje[3].br[3] = 12; polje[3].voz[3] = 'c';
        polje[3].br[4] = 22; polje[3].voz[4] = 'b';
        polje[3].br[5] = 23; polje[3].voz[5] = 'b';

        polje[4].br[1] = 3; polje[4].voz[1] = 'c';
        polje[4].br[2] = 13; polje[4].voz[2] = 'c';

        polje[5].br[1] = 15; polje[5].voz[1] = 'c';
        polje[5].br[2] = 16; polje[5].voz[2] = 'c';

        polje[6].br[1] = 7; polje[6].voz[1] = 'c';
        polje[6].br[2] = 29; polje[6].voz[2] = 'c';

        polje[7].br[1] = 6; polje[7].voz[1] = 'c';
        polje[7].br[2] = 17; polje[7].voz[2] = 'c';
        polje[7].br[3] = 42; polje[7].voz[3] = 'b';

        polje[8].br[1] = 1; polje[8].voz[1] = 'c';
        polje[8].br[2] = 18; polje[8].voz[2] = 'c';
        polje[8].br[3] = 19; polje[8].voz[3] = 'c';

        polje[9].br[1] = 1; polje[9].voz[1] = 'c';
        polje[9].br[2] = 19; polje[9].voz[2] = 'c';
        polje[9].br[3] = 20; polje[9].voz[3] = 'c';

        polje[10].br[1] = 2; polje[10].voz[1] = 'c';
        polje[10].br[2] = 21; polje[10].voz[2] = 'c';
        polje[10].br[3] = 11; polje[10].voz[3] = 'c';
        polje[10].br[4] = 34; polje[10].voz[4] = 'c';

        polje[11].br[1] = 10; polje[11].voz[1] = 'c';
        polje[11].br[2] = 3; polje[11].voz[2] = 'c';
        polje[11].br[3] = 22; polje[11].voz[3] = 'c';

        polje[12].br[1] = 3; polje[12].voz[1] = 'c';
        polje[12].br[2] = 23; polje[12].voz[2] = 'c';

        polje[13].br[1] = 4; polje[13].voz[1] = 'c';
        polje[13].br[2] = 23; polje[13].voz[2] = 'c';
        polje[13].br[3] = 23; polje[13].voz[3] = 'b';
        polje[13].br[4] = 14; polje[13].voz[4] = 'b';
        polje[13].br[5] = 52; polje[13].voz[5] = 'b';
        polje[13].br[6] = 89; polje[13].voz[6] = 'u';
        polje[13].br[7] = 67; polje[13].voz[7] = 'u';
        polje[13].br[8] = 24; polje[13].voz[8] = 'c';
        polje[13].br[9] = 46; polje[13].voz[9] = 'u';

        polje[14].br[1] = 13; polje[14].voz[1] = 'b';
        polje[14].br[2] = 15; polje[14].voz[2] = 'b';
        polje[14].br[3] = 15; polje[14].voz[3] = 'c';
        polje[14].br[4] = 25; polje[14].voz[4] = 'c';

        polje[15].br[1] = 14; polje[15].voz[1] = 'c';
        polje[15].br[2] = 14; polje[15].voz[2] = 'b';
        polje[15].br[3] = 5; polje[15].voz[3] = 'c';
        polje[15].br[4] = 26; polje[15].voz[4] = 'c';
        polje[15].br[5] = 28; polje[15].voz[5] = 'c';
        polje[15].br[6] = 41; polje[15].voz[6] = 'b';
        polje[15].br[7] = 16; polje[15].voz[7] = 'c';
        polje[15].br[8] = 29; polje[15].voz[8] = 'b';

        polje[16].br[1] = 5; polje[16].voz[1] = 'c';
        polje[16].br[2] = 28; polje[16].voz[2] = 'c';
        polje[16].br[3] = 15; polje[16].voz[3] = 'c';
        polje[16].br[4] = 29; polje[16].voz[4] = 'c';

        polje[17].br[1] = 7; polje[17].voz[1] = 'c';
        polje[17].br[2] = 29; polje[17].voz[2] = 'c';
        polje[17].br[3] = 30; polje[17].voz[3] = 'c';

        polje[18].br[1] = 8; polje[18].voz[1] = 'c';
        polje[18].br[2] = 31; polje[18].voz[2] = 'c';
        polje[18].br[3] = 43; polje[18].voz[3] = 'c';

        polje[19].br[1] = 8; polje[19].voz[1] = 'c';
        polje[19].br[2] = 9; polje[19].voz[2] = 'c';
        polje[19].br[3] = 32; polje[19].voz[3] = 'c';

        polje[20].br[1] = 2; polje[20].voz[1] = 'c';
        polje[20].br[2] = 9; polje[20].voz[2] = 'c';
        polje[20].br[3] = 33; polje[20].voz[3] = 'c';

        polje[21].br[1] = 33; polje[21].voz[1] = 'c';
        polje[21].br[2] = 10; polje[21].voz[2] = 'c';

        polje[22].br[1] = 34; polje[22].voz[1] = 'b';
        polje[22].br[2] = 65; polje[22].voz[2] = 'b';
        polje[22].br[3] = 3; polje[22].voz[3] = 'b';
        polje[22].br[4] = 23; polje[22].voz[4] = 'b';
        polje[22].br[5] = 35; polje[22].voz[5] = 'c';
        polje[22].br[6] = 34; polje[22].voz[6] = 'c';
        polje[22].br[7] = 11; polje[22].voz[7] = 'c';
        polje[22].br[8] = 23; polje[22].voz[8] = 'c';

        polje[23].br[1] = 3; polje[23].voz[1] = 'b';
        polje[23].br[2] = 22; polje[23].voz[2] = 'b';
        polje[23].br[3] = 67; polje[23].voz[3] = 'b';
        polje[23].br[4] = 13; polje[23].voz[4] = 'b';
        polje[23].br[5] = 12; polje[23].voz[5] = 'c';
        polje[23].br[6] = 22; polje[23].voz[6] = 'c';
        polje[23].br[7] = 13; polje[23].voz[7] = 'c';
        polje[23].br[8] = 37; polje[23].voz[8] = 'c';

        polje[24].br[1] = 13; polje[24].voz[1] = 'c';
        polje[24].br[2] = 38; polje[24].voz[2] = 'c';
        polje[24].br[3] = 37; polje[24].voz[3] = 'c';

        polje[25].br[1] = 14; polje[25].voz[1] = 'c';
        polje[25].br[2] = 39; polje[25].voz[2] = 'c';
        polje[25].br[3] = 38; polje[25].voz[3] = 'c';

        polje[26].br[1] = 15; polje[26].voz[1] = 'c';
        polje[26].br[2] = 27; polje[26].voz[2] = 'c';
        polje[26].br[3] = 39; polje[26].voz[3] = 'c';

        polje[27].br[1] = 28; polje[27].voz[1] = 'c';
        polje[27].br[2] = 26; polje[27].voz[2] = 'c';
        polje[27].br[3] = 40; polje[27].voz[3] = 'c';

        polje[28].br[1] = 27; polje[28].voz[1] = 'c';
        polje[28].br[2] = 41; polje[28].voz[2] = 'c';
        polje[28].br[3] = 16; polje[28].voz[3] = 'c';
        polje[28].br[4] = 15; polje[28].voz[4] = 'c';

        polje[29].br[1] = 15; polje[29].voz[1] = 'b';
        polje[29].br[2] = 42; polje[29].voz[2] = 'b';
        polje[29].br[3] = 41; polje[29].voz[3] = 'b';
        polje[29].br[4] = 55; polje[29].voz[4] = 'b';
        polje[29].br[5] = 16; polje[29].voz[5] = 'c';
        polje[29].br[6] = 6; polje[29].voz[6] = 'c';
        polje[29].br[7] = 17; polje[29].voz[7] = 'c';
        polje[29].br[8] = 41; polje[29].voz[8] = 'c';
        polje[29].br[9] = 42; polje[29].voz[9] = 'c';

        polje[30].br[1] = 17; polje[30].voz[1] = 'c';
        polje[30].br[2] = 42; polje[30].voz[2] = 'c';

        polje[31].br[1] = 18; polje[31].voz[1] = 'c';
        polje[31].br[2] = 43; polje[31].voz[2] = 'c';
        polje[31].br[3] = 44; polje[31].voz[3] = 'c';

        polje[32].br[1] = 19; polje[32].voz[1] = 'c';
        polje[32].br[2] = 33; polje[32].voz[2] = 'c';
        polje[32].br[3] = 45; polje[32].voz[3] = 'c';
        polje[32].br[4] = 44; polje[32].voz[4] = 'c';

        polje[33].br[1] = 20; polje[33].voz[1] = 'c';
        polje[33].br[2] = 21; polje[33].voz[2] = 'c';
        polje[33].br[3] = 46; polje[33].voz[3] = 'c';
        polje[33].br[4] = 32; polje[33].voz[4] = 'c';

        polje[34].br[1] = 48; polje[34].voz[1] = 'c';
        polje[34].br[2] = 47; polje[34].voz[2] = 'c';
        polje[34].br[3] = 22; polje[34].voz[3] = 'c';
        polje[34].br[4] = 10; polje[34].voz[4] = 'c';
        polje[34].br[5] = 22; polje[34].voz[5] = 'b';
        polje[34].br[6] = 46; polje[34].voz[6] = 'b';
        polje[34].br[7] = 63; polje[34].voz[7] = 'b';

        polje[35].br[1] = 22; polje[35].voz[1] = 'c';
        polje[35].br[2] = 36; polje[35].voz[2] = 'c';
        polje[35].br[3] = 48; polje[35].voz[3] = 'c';
        polje[35].br[4] = 65; polje[35].voz[4] = 'c';

        polje[36].br[1] = 35; polje[36].voz[1] = 'c';
        polje[36].br[2] = 49; polje[36].voz[2] = 'c';
        polje[36].br[3] = 37; polje[36].voz[3] = 'c';

        polje[37].br[1] = 24; polje[37].voz[1] = 'c';
        polje[37].br[2] = 50; polje[37].voz[2] = 'c';
        polje[37].br[3] = 23; polje[37].voz[3] = 'c';
        polje[37].br[4] = 36; polje[37].voz[4] = 'c';

        polje[38].br[1] = 24; polje[38].voz[1] = 'c';
        polje[38].br[2] = 50; polje[38].voz[2] = 'c';
        polje[38].br[3] = 51; polje[38].voz[3] = 'c';
        polje[38].br[4] = 25; polje[38].voz[4] = 'c';

        polje[39].br[1] = 25; polje[39].voz[1] = 'c';
        polje[39].br[2] = 51; polje[39].voz[2] = 'c';
        polje[39].br[3] = 52; polje[39].voz[3] = 'c';
        polje[39].br[4] = 26; polje[39].voz[4] = 'c';

        polje[40].br[1] = 41; polje[40].voz[1] = 'c';
        polje[40].br[2] = 53; polje[40].voz[2] = 'c';
        polje[40].br[3] = 52; polje[40].voz[3] = 'c';
        polje[40].br[4] = 27; polje[40].voz[4] = 'c';

        polje[41].br[1] = 40; polje[41].voz[1] = 'c';
        polje[41].br[2] = 28; polje[41].voz[2] = 'c';
        polje[41].br[3] = 54; polje[41].voz[3] = 'c';
        polje[41].br[4] = 29; polje[41].voz[4] = 'c';
        polje[41].br[5] = 52; polje[41].voz[5] = 'b';
        polje[41].br[6] = 29; polje[41].voz[6] = 'b';
        polje[41].br[7] = 15; polje[41].voz[7] = 'b';
        polje[41].br[8] = 87; polje[41].voz[8] = 'b';

        polje[42].br[1] = 30; polje[42].voz[1] = 'c';
        polje[42].br[2] = 72; polje[42].voz[2] = 'c';
        polje[42].br[3] = 56; polje[42].voz[3] = 'c';
        polje[42].br[4] = 29; polje[42].voz[4] = 'c';
        polje[42].br[5] = 7; polje[42].voz[5] = 'b';
        polje[42].br[6] = 29; polje[42].voz[6] = 'b';
        polje[42].br[7] = 72; polje[42].voz[7] = 'b';

        polje[43].br[1] = 18; polje[43].voz[1] = 'c';
        polje[43].br[2] = 31; polje[43].voz[2] = 'c';
        polje[43].br[3] = 57; polje[43].voz[3] = 'c';

        polje[44].br[1] = 58; polje[44].voz[1] = 'c';
        polje[44].br[2] = 31; polje[44].voz[2] = 'c';
        polje[44].br[3] = 32; polje[44].voz[3] = 'c';

        polje[45].br[1] = 58; polje[45].voz[1] = 'c';
        polje[45].br[2] = 32; polje[45].voz[2] = 'c';
        polje[45].br[3] = 46; polje[45].voz[3] = 'c';
        polje[45].br[4] = 60; polje[45].voz[4] = 'c';
        polje[45].br[5] = 59; polje[45].voz[5] = 'c';

        polje[46].br[1] = 33; polje[46].voz[1] = 'c';
        polje[46].br[2] = 45; polje[46].voz[2] = 'c';
        polje[46].br[3] = 47; polje[46].voz[3] = 'c';
        polje[46].br[4] = 61; polje[46].voz[4] = 'c';
        polje[46].br[5] = 1; polje[46].voz[5] = 'b';
        polje[46].br[6] = 58; polje[46].voz[6] = 'b';
        polje[46].br[7] = 78; polje[46].voz[7] = 'b';
        polje[46].br[8] = 34; polje[46].voz[8] = 'b';
        polje[46].br[9] = 1; polje[46].voz[9] = 'u';
        polje[46].br[10] = 74; polje[46].voz[10] = 'u';
        polje[46].br[11] = 79; polje[46].voz[11] = 'u';
        polje[46].br[12] = 13; polje[46].voz[12] = 'u';

        polje[47].br[1] = 46; polje[47].voz[1] = 'c';
        polje[47].br[2] = 34; polje[47].voz[2] = 'c';
        polje[47].br[3] = 62; polje[47].voz[3] = 'c';

        polje[48].br[1] = 34; polje[48].voz[1] = 'c';
        polje[48].br[2] = 35; polje[48].voz[2] = 'c';
        polje[48].br[3] = 62; polje[48].voz[3] = 'c';
        polje[48].br[4] = 63; polje[48].voz[4] = 'c';

        polje[49].br[1] = 36; polje[49].voz[1] = 'c';
        polje[49].br[2] = 66; polje[49].voz[2] = 'c';
        polje[49].br[3] = 50; polje[49].voz[3] = 'c';

        polje[50].br[1] = 37; polje[50].voz[1] = 'c';
        polje[50].br[2] = 38; polje[50].voz[2] = 'c';
        polje[50].br[3] = 49; polje[50].voz[3] = 'c';

        polje[51].br[1] = 67; polje[51].voz[1] = 'c';
        polje[51].br[2] = 38; polje[51].voz[2] = 'c';
        polje[51].br[3] = 39; polje[51].voz[3] = 'c';
        polje[51].br[4] = 52; polje[51].voz[4] = 'c';
        polje[51].br[5] = 68; polje[51].voz[5] = 'c';

        polje[52].br[1] = 51; polje[52].voz[1] = 'c';
        polje[52].br[2] = 39; polje[52].voz[2] = 'c';
        polje[52].br[3] = 40; polje[52].voz[3] = 'c';
        polje[52].br[4] = 69; polje[52].voz[4] = 'c';
        polje[52].br[5] = 13; polje[52].voz[5] = 'b';
        polje[52].br[6] = 86; polje[52].voz[6] = 'b';
        polje[52].br[7] = 41; polje[52].voz[7] = 'b';
        polje[52].br[8] = 67; polje[52].voz[8] = 'b';

        polje[53].br[1] = 40; polje[53].voz[1] = 'c';
        polje[53].br[2] = 69; polje[53].voz[2] = 'c';
        polje[53].br[3] = 54; polje[53].voz[3] = 'c';

        polje[54].br[1] = 53; polje[54].voz[1] = 'c';
        polje[54].br[2] = 70; polje[54].voz[2] = 'c';
        polje[54].br[3] = 55; polje[54].voz[3] = 'c';
        polje[54].br[4] = 41; polje[54].voz[4] = 'c';

        polje[55].br[1] = 54; polje[55].voz[1] = 'c';
        polje[55].br[2] = 71; polje[55].voz[2] = 'c';
        polje[55].br[3] = 89; polje[55].voz[3] = 'b';
        polje[55].br[4] = 29; polje[55].voz[4] = 'b';

        polje[56].br[1] = 42; polje[56].voz[1] = 'c';
        polje[56].br[2] = 91; polje[56].voz[2] = 'c';

        polje[57].br[1] = 58; polje[57].voz[1] = 'c';
        polje[57].br[2] = 43; polje[57].voz[2] = 'c';
        polje[57].br[3] = 73; polje[57].voz[3] = 'c';

        polje[58].br[1] = 44; polje[58].voz[1] = 'c';
        polje[58].br[2] = 45; polje[58].voz[2] = 'c';
        polje[58].br[3] = 57; polje[58].voz[3] = 'c';
        polje[58].br[4] = 74; polje[58].voz[4] = 'c';
        polje[58].br[5] = 59; polje[58].voz[5] = 'c';
        polje[58].br[6] = 75; polje[58].voz[6] = 'c';
        polje[58].br[7] = 1; polje[58].voz[7] = 'b';
        polje[58].br[8] = 74; polje[58].voz[8] = 'b';
        polje[58].br[9] = 77; polje[58].voz[9] = 'b';
        polje[58].br[10] = 46; polje[58].voz[10] = 'b';

        polje[59].br[1] = 58; polje[59].voz[1] = 'c';
        polje[59].br[2] = 45; polje[59].voz[2] = 'c';
        polje[59].br[3] = 75; polje[59].voz[3] = 'c';
        polje[59].br[4] = 76; polje[59].voz[4] = 'c';

        polje[60].br[1] = 61; polje[60].voz[1] = 'c';
        polje[60].br[2] = 45; polje[60].voz[2] = 'c';
        polje[60].br[3] = 76; polje[60].voz[3] = 'c';

        polje[61].br[1] = 62; polje[61].voz[1] = 'c';
        polje[61].br[2] = 60; polje[61].voz[2] = 'c';
        polje[61].br[3] = 76; polje[61].voz[3] = 'c';
        polje[61].br[4] = 78; polje[61].voz[4] = 'c';
        polje[61].br[5] = 46; polje[61].voz[5] = 'c';

        polje[62].br[1] = 47; polje[62].voz[1] = 'c';
        polje[62].br[2] = 61; polje[62].voz[2] = 'c';
        polje[62].br[3] = 48; polje[62].voz[3] = 'c';
        polje[62].br[4] = 79; polje[62].voz[4] = 'c';

        polje[63].br[1] = 79; polje[63].voz[1] = 'c';
        polje[63].br[2] = 80; polje[63].voz[2] = 'c';
        polje[63].br[3] = 64; polje[63].voz[3] = 'c';
        polje[63].br[4] = 48; polje[63].voz[4] = 'c';
        polje[63].br[5] = 34; polje[63].voz[5] = 'b';
        polje[63].br[6] = 79; polje[63].voz[6] = 'b';
        polje[63].br[7] = 100; polje[63].voz[7] = 'b';
        polje[63].br[8] = 65; polje[63].voz[8] = 'b';

        polje[64].br[1] = 63; polje[64].voz[1] = 'c';
        polje[64].br[2] = 65; polje[64].voz[2] = 'c';
        polje[64].br[3] = 81; polje[64].voz[3] = 'c';

        polje[65].br[1] = 64; polje[65].voz[1] = 'c';
        polje[65].br[2] = 35; polje[65].voz[2] = 'c';
        polje[65].br[3] = 82; polje[65].voz[3] = 'c';
        polje[65].br[4] = 66; polje[65].voz[4] = 'c';
        polje[65].br[5] = 22; polje[65].voz[5] = 'b';
        polje[65].br[6] = 63; polje[65].voz[6] = 'b';
        polje[65].br[7] = 82; polje[65].voz[7] = 'b';
        polje[65].br[8] = 67; polje[65].voz[8] = 'b';

        polje[66].br[1] = 67; polje[66].voz[1] = 'c';
        polje[66].br[2] = 65; polje[66].voz[2] = 'c';
        polje[66].br[3] = 49; polje[66].voz[3] = 'c';
        polje[66].br[4] = 82; polje[66].voz[4] = 'c';

        polje[67].br[1] = 68; polje[67].voz[1] = 'c';
        polje[67].br[2] = 66; polje[67].voz[2] = 'c';
        polje[67].br[3] = 84; polje[67].voz[3] = 'c';
        polje[67].br[4] = 51; polje[67].voz[4] = 'c';
        polje[67].br[5] = 102; polje[67].voz[5] = 'b';
        polje[67].br[6] = 65; polje[67].voz[6] = 'b';
        polje[67].br[7] = 52; polje[67].voz[7] = 'b';
        polje[67].br[8] = 23; polje[67].voz[8] = 'b';
        polje[67].br[9] = 82; polje[67].voz[9] = 'b';
        polje[67].br[10] = 89; polje[67].voz[10] = 'u';
        polje[67].br[11] = 13; polje[67].voz[11] = 'u';
        polje[67].br[12] = 79; polje[67].voz[12] = 'u';
        polje[67].br[13] = 111; polje[67].voz[13] = 'u';

        polje[68].br[1] = 51; polje[68].voz[1] = 'c';
        polje[68].br[2] = 69; polje[68].voz[2] = 'c';
        polje[68].br[3] = 67; polje[68].voz[3] = 'c';
        polje[68].br[4] = 85; polje[68].voz[4] = 'c';

        polje[69].br[1] = 52; polje[69].voz[1] = 'c';
        polje[69].br[2] = 86; polje[69].voz[2] = 'c';
        polje[69].br[3] = 68; polje[69].voz[3] = 'c';
        polje[69].br[4] = 53; polje[69].voz[4] = 'c';

        polje[70].br[1] = 54; polje[70].voz[1] = 'c';
        polje[70].br[2] = 71; polje[70].voz[2] = 'c';
        polje[70].br[3] = 87; polje[70].voz[3] = 'c';

        polje[71].br[1] = 55; polje[71].voz[1] = 'c';
        polje[71].br[2] = 72; polje[71].voz[2] = 'c';
        polje[71].br[3] = 89; polje[71].voz[3] = 'c';
        polje[71].br[4] = 70; polje[71].voz[4] = 'c';

        polje[72].br[1] = 71; polje[72].voz[1] = 'c';
        polje[72].br[2] = 91; polje[72].voz[2] = 'c';
        polje[72].br[3] = 90; polje[72].voz[3] = 'c';
        polje[72].br[4] = 42; polje[72].voz[4] = 'c';
        polje[72].br[5] = 42; polje[72].voz[5] = 'b';
        polje[72].br[6] = 105; polje[72].voz[6] = 'b';
        polje[72].br[7] = 107; polje[72].voz[7] = 'b';

        polje[73].br[1] = 57; polje[73].voz[1] = 'c';
        polje[73].br[2] = 92; polje[73].voz[2] = 'c';
        polje[73].br[3] = 74; polje[73].voz[3] = 'c';

        polje[74].br[1] = 73; polje[74].voz[1] = 'c';
        polje[74].br[2] = 92; polje[74].voz[2] = 'c';
        polje[74].br[3] = 58; polje[74].voz[3] = 'c';
        polje[74].br[4] = 75; polje[74].voz[4] = 'c';
        polje[74].br[5] = 94; polje[74].voz[5] = 'b';
        polje[74].br[6] = 58; polje[74].voz[6] = 'b';
        polje[74].br[7] = 46; polje[74].voz[7] = 'u';

        polje[75].br[1] = 74; polje[75].voz[1] = 'c';
        polje[75].br[2] = 59; polje[75].voz[2] = 'c';
        polje[75].br[3] = 58; polje[75].voz[3] = 'c';
        polje[75].br[4] = 94; polje[75].voz[4] = 'c';

        polje[76].br[1] = 59; polje[76].voz[1] = 'c';
        polje[76].br[2] = 77; polje[76].voz[2] = 'c';
        polje[76].br[3] = 61; polje[76].voz[3] = 'c';
        polje[76].br[4] = 60; polje[76].voz[4] = 'c';

        polje[77].br[1] = 76; polje[77].voz[1] = 'c';
        polje[77].br[2] = 78; polje[77].voz[2] = 'c';
        polje[77].br[3] = 96; polje[77].voz[3] = 'c';
        polje[77].br[4] = 95; polje[77].voz[4] = 'c';
        polje[77].br[5] = 78; polje[77].voz[5] = 'b';
        polje[77].br[6] = 58; polje[77].voz[6] = 'b';
        polje[77].br[7] = 124; polje[77].voz[7] = 'b';
        polje[77].br[8] = 94; polje[77].voz[8] = 'b';

        polje[78].br[1] = 61; polje[78].voz[1] = 'c';
        polje[78].br[2] = 77; polje[78].voz[2] = 'c';
        polje[78].br[3] = 79; polje[78].voz[3] = 'c';
        polje[78].br[4] = 97; polje[78].voz[4] = 'c';
        polje[78].br[5] = 77; polje[78].voz[5] = 'b';
        polje[78].br[6] = 79; polje[78].voz[6] = 'b';
        polje[78].br[7] = 46; polje[78].voz[7] = 'b';

        polje[79].br[1] = 62; polje[79].voz[1] = 'c';
        polje[79].br[2] = 63; polje[79].voz[2] = 'c';
        polje[79].br[3] = 78; polje[79].voz[3] = 'c';
        polje[79].br[4] = 98; polje[79].voz[4] = 'c';
        polje[79].br[5] = 63; polje[79].voz[5] = 'b';
        polje[79].br[6] = 78; polje[79].voz[6] = 'b';
        polje[79].br[7] = 93; polje[79].voz[7] = 'u';
        polje[79].br[8] = 46; polje[79].voz[8] = 'u';
        polje[79].br[9] = 111; polje[79].voz[9] = 'u';
        polje[79].br[10] = 67; polje[79].voz[10] = 'u';

        polje[80].br[1] = 63; polje[80].voz[1] = 'c';
        polje[80].br[2] = 99; polje[80].voz[2] = 'c';
        polje[80].br[3] = 100; polje[80].voz[3] = 'c';

        polje[81].br[1] = 64; polje[81].voz[1] = 'c';
        polje[81].br[2] = 100; polje[81].voz[2] = 'c';
        polje[81].br[3] = 82; polje[81].voz[3] = 'c';

        polje[82].br[1] = 65; polje[82].voz[1] = 'c';
        polje[82].br[2] = 66; polje[82].voz[2] = 'c';
        polje[82].br[3] = 81; polje[82].voz[3] = 'c';
        polje[82].br[4] = 101; polje[82].voz[4] = 'c';
        polje[82].br[5] = 67; polje[82].voz[5] = 'b';
        polje[82].br[6] = 100; polje[82].voz[6] = 'b';
        polje[82].br[7] = 65; polje[82].voz[7] = 'b';
        polje[82].br[8] = 140; polje[82].voz[8] = 'b';

        polje[83].br[1] = 101; polje[83].voz[1] = 'c';
        polje[83].br[2] = 102; polje[83].voz[2] = 'c';

        polje[84].br[1] = 85; polje[84].voz[1] = 'c';
        polje[84].br[2] = 67; polje[84].voz[2] = 'c';

        polje[85].br[1] = 68; polje[85].voz[1] = 'c';
        polje[85].br[2] = 103; polje[85].voz[2] = 'c';
        polje[85].br[3] = 84; polje[85].voz[3] = 'c';

        polje[86].br[1] = 104; polje[86].voz[1] = 'c';
        polje[86].br[2] = 103; polje[86].voz[2] = 'c';
        polje[86].br[3] = 69; polje[86].voz[3] = 'c';
        polje[86].br[4] = 87; polje[86].voz[4] = 'b';
        polje[86].br[5] = 52; polje[86].voz[5] = 'b';
        polje[86].br[6] = 102; polje[86].voz[6] = 'b';
        polje[86].br[7] = 116; polje[86].voz[7] = 'b';

        polje[87].br[1] = 70; polje[87].voz[1] = 'c';
        polje[87].br[2] = 88; polje[87].voz[2] = 'c';
        polje[87].br[3] = 86; polje[87].voz[3] = 'b';
        polje[87].br[4] = 105; polje[87].voz[4] = 'b';
        polje[87].br[5] = 41; polje[87].voz[5] = 'b';

        polje[88].br[1] = 87; polje[88].voz[1] = 'c';
        polje[88].br[2] = 89; polje[88].voz[2] = 'c';
        polje[88].br[3] = 117; polje[88].voz[3] = 'c';

        polje[89].br[1] = 88; polje[89].voz[1] = 'c';
        polje[89].br[2] = 71; polje[89].voz[2] = 'c';
        polje[89].br[3] = 105; polje[89].voz[3] = 'c';
        polje[89].br[4] = 105; polje[89].voz[4] = 'b';
        polje[89].br[5] = 55; polje[89].voz[5] = 'b';
        polje[89].br[6] = 67; polje[89].voz[6] = 'u';
        polje[89].br[7] = 13; polje[89].voz[7] = 'u';
        polje[89].br[8] = 128; polje[89].voz[8] = 'u';
        polje[89].br[9] = 140; polje[89].voz[9] = 'u';

        polje[90].br[1] = 105; polje[90].voz[1] = 'c';
        polje[90].br[2] = 91; polje[90].voz[2] = 'c';
        polje[90].br[3] = 72; polje[90].voz[3] = 'c';

        polje[91].br[1] = 90; polje[91].voz[1] = 'c';
        polje[91].br[2] = 107; polje[91].voz[2] = 'c';
        polje[91].br[3] = 56; polje[91].voz[3] = 'c';
        polje[91].br[4] = 72; polje[91].voz[4] = 'c';
        polje[91].br[5] = 105; polje[91].voz[5] = 'c';

        polje[92].br[1] = 93; polje[92].voz[1] = 'c';
        polje[92].br[2] = 73; polje[92].voz[2] = 'c';
        polje[92].br[3] = 74; polje[92].voz[3] = 'c';

        polje[93].br[1] = 94; polje[93].voz[1] = 'c';
        polje[93].br[2] = 92; polje[93].voz[2] = 'c';
        polje[93].br[3] = 94; polje[93].voz[3] = 'b';
        polje[93].br[4] = 79; polje[93].voz[4] = 'u';

        polje[94].br[1] = 95; polje[94].voz[1] = 'c';
        polje[94].br[2] = 93; polje[94].voz[2] = 'c';
        polje[94].br[3] = 75; polje[94].voz[3] = 'c';
        polje[94].br[4] = 74; polje[94].voz[4] = 'b';
        polje[94].br[5] = 93; polje[94].voz[5] = 'b';
        polje[94].br[6] = 77; polje[94].voz[6] = 'b';

        polje[95].br[1] = 122; polje[95].voz[1] = 'c';
        polje[95].br[2] = 77; polje[95].voz[2] = 'c';
        polje[95].br[3] = 94; polje[95].voz[3] = 'c';

        polje[96].br[1] = 77; polje[96].voz[1] = 'c';
        polje[96].br[2] = 97; polje[96].voz[2] = 'c';
        polje[96].br[3] = 109; polje[96].voz[3] = 'c';


        polje[97].br[1] = 78; polje[97].voz[1] = 'c';
        polje[97].br[2] = 96; polje[97].voz[2] = 'c';
        polje[97].br[3] = 98; polje[97].voz[3] = 'c';
        polje[97].br[4] = 109; polje[97].voz[4] = 'c';

        polje[98].br[1] = 79; polje[98].voz[1] = 'c';
        polje[98].br[2] = 99; polje[98].voz[2] = 'c';
        polje[98].br[3] = 110; polje[98].voz[3] = 'c';
        polje[98].br[4] = 97; polje[98].voz[4] = 'c';

        polje[99].br[1] = 80; polje[99].voz[1] = 'c';
        polje[99].br[2] = 110; polje[99].voz[2] = 'c';
        polje[99].br[3] = 112; polje[99].voz[3] = 'c';
        polje[99].br[4] = 98; polje[99].voz[4] = 'c';

        polje[100].br[1] = 80; polje[100].voz[1] = 'c';
        polje[100].br[2] = 81; polje[100].voz[2] = 'c';
        polje[100].br[3] = 112; polje[100].voz[3] = 'c';
        polje[100].br[4] = 113; polje[100].voz[4] = 'c';
        polje[100].br[5] = 101; polje[100].voz[5] = 'c';
        polje[100].br[6] = 111; polje[100].voz[6] = 'b';
        polje[100].br[7] = 63; polje[100].voz[7] = 'b';
        polje[100].br[8] = 82; polje[100].voz[8] = 'b';

        polje[101].br[1] = 83; polje[101].voz[1] = 'c';
        polje[101].br[2] = 114; polje[101].voz[2] = 'c';
        polje[101].br[3] = 82; polje[101].voz[3] = 'c';
        polje[101].br[4] = 100; polje[101].voz[4] = 'c';

        polje[102].br[1] = 83; polje[102].voz[1] = 'c';
        polje[102].br[2] = 103; polje[102].voz[2] = 'c';
        polje[102].br[3] = 115; polje[102].voz[3] = 'c';
        polje[102].br[4] = 67; polje[102].voz[4] = 'b';
        polje[102].br[5] = 86; polje[102].voz[5] = 'b';
        polje[102].br[6] = 127; polje[102].voz[6] = 'b';

        polje[103].br[1] = 85; polje[103].voz[1] = 'c';
        polje[103].br[2] = 86; polje[103].voz[2] = 'c';
        polje[103].br[3] = 102; polje[103].voz[3] = 'c';

        polje[104].br[1] = 86; polje[104].voz[1] = 'c';
        polje[104].br[2] = 116; polje[104].voz[2] = 'c';

        polje[105].br[1] = 90; polje[105].voz[1] = 'c';
        polje[105].br[2] = 91; polje[105].voz[2] = 'c';
        polje[105].br[3] = 106; polje[105].voz[3] = 'c';
        polje[105].br[4] = 108; polje[105].voz[4] = 'c';
        polje[105].br[5] = 89; polje[105].voz[5] = 'c';
        polje[105].br[6] = 89; polje[105].voz[6] = 'b';
        polje[105].br[7] = 87; polje[105].voz[7] = 'b';
        polje[105].br[8] = 107; polje[105].voz[8] = 'b';
        polje[105].br[9] = 72; polje[105].voz[9] = 'b';
        polje[105].br[10] = 108; polje[105].voz[10] = 'b';

        polje[106].br[1] = 105; polje[106].voz[1] = 'c';
        polje[106].br[2] = 107; polje[106].voz[2] = 'c';

        polje[107].br[1] = 91; polje[107].voz[1] = 'c';
        polje[107].br[2] = 106; polje[107].voz[2] = 'c';
        polje[107].br[3] = 119; polje[107].voz[3] = 'c';
        polje[107].br[4] = 72; polje[107].voz[4] = 'b';
        polje[107].br[5] = 105; polje[107].voz[5] = 'b';
        polje[107].br[6] = 161; polje[107].voz[6] = 'b';


        polje[108].br[1] = 117; polje[108].voz[1] = 'c';
        polje[108].br[2] = 119; polje[108].voz[2] = 'c';
        polje[108].br[3] = 105; polje[108].voz[3] = 'c';
        polje[108].br[4] = 135; polje[108].voz[4] = 'b';
        polje[108].br[5] = 116; polje[108].voz[5] = 'b';
        polje[108].br[6] = 105; polje[108].voz[6] = 'b';
        polje[108].br[7] = 115; polje[108].voz[7] = 'x';

        polje[109].br[1] = 96; polje[109].voz[1] = 'c';
        polje[109].br[2] = 97; polje[109].voz[2] = 'c';
        polje[109].br[3] = 110; polje[109].voz[3] = 'c';
        polje[109].br[4] = 124; polje[109].voz[4] = 'c';

        polje[110].br[1] = 98; polje[110].voz[1] = 'c';
        polje[110].br[2] = 99; polje[110].voz[2] = 'c';
        polje[110].br[3] = 109; polje[110].voz[3] = 'c';
        polje[110].br[4] = 111; polje[110].voz[4] = 'c';

        polje[111].br[1] = 112; polje[111].voz[1] = 'c';
        polje[111].br[2] = 124; polje[111].voz[2] = 'c';
        polje[111].br[3] = 110; polje[111].voz[3] = 'c';
        polje[111].br[4] = 124; polje[111].voz[4] = 'b';
        polje[111].br[5] = 100; polje[111].voz[5] = 'b';
        polje[111].br[6] = 163; polje[111].voz[6] = 'u';
        polje[111].br[7] = 153; polje[111].voz[7] = 'u';
        polje[111].br[8] = 79; polje[111].voz[8] = 'u';
        polje[111].br[9] = 67; polje[111].voz[9] = 'u';

        polje[112].br[1] = 111; polje[112].voz[1] = 'c';
        polje[112].br[2] = 100; polje[112].voz[2] = 'c';
        polje[112].br[3] = 99; polje[112].voz[3] = 'c';
        polje[112].br[4] = 125; polje[112].voz[4] = 'c';

        polje[113].br[1] = 100; polje[113].voz[1] = 'c';
        polje[113].br[2] = 125; polje[113].voz[2] = 'c';
        polje[113].br[3] = 114; polje[113].voz[3] = 'c';

        polje[114].br[1] = 101; polje[114].voz[1] = 'c';
        polje[114].br[2] = 115; polje[114].voz[2] = 'c';
        polje[114].br[3] = 113; polje[114].voz[3] = 'c';
        polje[114].br[4] = 126; polje[114].voz[4] = 'c';
        polje[114].br[5] = 132; polje[114].voz[5] = 'c';
        polje[114].br[6] = 131; polje[114].voz[6] = 'c';

        polje[115].br[1] = 114; polje[115].voz[1] = 'c';
        polje[115].br[2] = 102; polje[115].voz[2] = 'c';
        polje[115].br[3] = 127; polje[115].voz[3] = 'c';
        polje[115].br[4] = 126; polje[115].voz[4] = 'c';
        polje[115].br[5] = 157; polje[115].voz[5] = 'x';
        polje[115].br[6] = 108; polje[115].voz[6] = 'x';

        polje[116].br[1] = 104; polje[116].voz[1] = 'c';
        polje[116].br[2] = 118; polje[116].voz[2] = 'c';
        polje[116].br[3] = 127; polje[116].voz[3] = 'c';
        polje[116].br[4] = 117; polje[116].voz[4] = 'c';
        polje[116].br[5] = 142; polje[116].voz[5] = 'b';
        polje[116].br[6] = 86; polje[116].voz[6] = 'b';
        polje[116].br[7] = 127; polje[116].voz[7] = 'b';
        polje[116].br[8] = 108; polje[116].voz[8] = 'b';

        polje[117].br[1] = 116; polje[117].voz[1] = 'c';
        polje[117].br[2] = 108; polje[117].voz[2] = 'c';
        polje[117].br[3] = 88; polje[117].voz[3] = 'c';
        polje[117].br[4] = 129; polje[117].voz[4] = 'c';

        polje[118].br[1] = 129; polje[118].voz[1] = 'c';
        polje[118].br[2] = 134; polje[118].voz[2] = 'c';
        polje[118].br[3] = 142; polje[118].voz[3] = 'c';
        polje[118].br[4] = 116; polje[118].voz[4] = 'c';

        polje[119].br[1] = 136; polje[119].voz[1] = 'c';
        polje[119].br[2] = 108; polje[119].voz[2] = 'c';
        polje[119].br[3] = 107; polje[119].voz[3] = 'c';

        polje[120].br[1] = 121; polje[120].voz[1] = 'c';
        polje[120].br[2] = 144; polje[120].voz[2] = 'c';

        polje[121].br[1] = 122; polje[121].voz[1] = 'c';
        polje[121].br[2] = 120; polje[121].voz[2] = 'c';
        polje[121].br[3] = 145; polje[121].voz[3] = 'c';

        polje[122].br[1] = 121; polje[122].voz[1] = 'c';
        polje[122].br[2] = 146; polje[122].voz[2] = 'c';
        polje[122].br[3] = 95; polje[122].voz[3] = 'c';
        polje[122].br[4] = 123; polje[122].voz[4] = 'c';
        polje[122].br[5] = 144; polje[122].voz[5] = 'b';
        polje[122].br[6] = 123; polje[122].voz[6] = 'b';

        polje[123].br[1] = 122; polje[123].voz[1] = 'c';
        polje[123].br[2] = 124; polje[123].voz[2] = 'c';
        polje[123].br[3] = 137; polje[123].voz[3] = 'c';
        polje[123].br[4] = 148; polje[123].voz[4] = 'c';
        polje[123].br[5] = 149; polje[123].voz[5] = 'c';
        polje[123].br[6] = 124; polje[123].voz[6] = 'b';
        polje[123].br[7] = 122; polje[123].voz[7] = 'b';
        polje[123].br[8] = 144; polje[123].voz[8] = 'b';
        polje[123].br[9] = 165; polje[123].voz[9] = 'b';

        polje[124].br[1] = 109; polje[124].voz[1] = 'c';
        polje[124].br[2] = 111; polje[124].voz[2] = 'c';
        polje[124].br[3] = 130; polje[124].voz[3] = 'c';
        polje[124].br[4] = 138; polje[124].voz[4] = 'c';
        polje[124].br[5] = 123; polje[124].voz[5] = 'c';
        polje[124].br[6] = 77; polje[124].voz[6] = 'b';
        polje[124].br[7] = 153; polje[124].voz[7] = 'b';
        polje[124].br[8] = 123; polje[124].voz[8] = 'b';
        polje[124].br[9] = 111; polje[124].voz[9] = 'b';

        polje[125].br[1] = 112; polje[125].voz[1] = 'c';
        polje[125].br[2] = 131; polje[125].voz[2] = 'c';
        polje[125].br[3] = 113; polje[125].voz[3] = 'c';

        polje[126].br[1] = 127; polje[126].voz[1] = 'c';
        polje[126].br[2] = 140; polje[126].voz[2] = 'c';
        polje[126].br[3] = 115; polje[126].voz[3] = 'c';
        polje[126].br[4] = 114; polje[126].voz[4] = 'c';

        polje[127].br[1] = 126; polje[127].voz[1] = 'c';
        polje[127].br[2] = 133; polje[127].voz[2] = 'c';
        polje[127].br[3] = 116; polje[127].voz[3] = 'c';
        polje[127].br[4] = 134; polje[127].voz[4] = 'c';
        polje[127].br[5] = 115; polje[127].voz[5] = 'c';
        polje[127].br[6] = 102; polje[127].voz[6] = 'b';
        polje[127].br[7] = 133; polje[127].voz[7] = 'b';
        polje[127].br[8] = 116; polje[127].voz[8] = 'b';

        polje[128].br[1] = 142; polje[128].voz[1] = 'c';
        polje[128].br[2] = 143; polje[128].voz[2] = 'c';
        polje[128].br[3] = 172; polje[128].voz[3] = 'c';
        polje[128].br[4] = 160; polje[128].voz[4] = 'c';
        polje[128].br[5] = 188; polje[128].voz[5] = 'c';
        polje[128].br[6] = 199; polje[128].voz[6] = 'b';
        polje[128].br[7] = 187; polje[128].voz[7] = 'b';
        polje[128].br[8] = 142; polje[128].voz[8] = 'b';
        polje[128].br[9] = 135; polje[128].voz[9] = 'b';
        polje[128].br[10] = 161; polje[128].voz[10] = 'b';
        polje[128].br[11] = 140; polje[128].voz[11] = 'u';
        polje[128].br[12] = 185; polje[128].voz[12] = 'u';
        polje[128].br[13] = 89; polje[128].voz[13] = 'u';

        polje[129].br[1] = 117; polje[129].voz[1] = 'c';
        polje[129].br[2] = 135; polje[129].voz[2] = 'c';
        polje[129].br[3] = 118; polje[129].voz[3] = 'c';
        polje[129].br[4] = 142; polje[129].voz[4] = 'c';
        polje[129].br[5] = 143; polje[129].voz[5] = 'c';

        polje[130].br[1] = 124; polje[130].voz[1] = 'c';
        polje[130].br[2] = 131; polje[130].voz[2] = 'c';
        polje[130].br[3] = 139; polje[130].voz[3] = 'c';

        polje[131].br[1] = 130; polje[131].voz[1] = 'c';
        polje[131].br[2] = 125; polje[131].voz[2] = 'c';
        polje[131].br[3] = 114; polje[131].voz[3] = 'c';

        polje[132].br[1] = 114; polje[132].voz[1] = 'c';
        polje[132].br[2] = 140; polje[132].voz[2] = 'c';

        polje[133].br[1] = 141; polje[133].voz[1] = 'c';
        polje[133].br[2] = 127; polje[133].voz[2] = 'c';
        polje[133].br[3] = 140; polje[133].voz[3] = 'c';
        polje[133].br[4] = 157; polje[133].voz[4] = 'b';
        polje[133].br[5] = 127; polje[133].voz[5] = 'b';

        polje[134].br[1] = 127; polje[134].voz[1] = 'c';
        polje[134].br[2] = 118; polje[134].voz[2] = 'c';
        polje[134].br[3] = 142; polje[134].voz[3] = 'c';
        polje[134].br[4] = 141; polje[134].voz[4] = 'c';

        polje[135].br[1] = 136; polje[135].voz[1] = 'c';
        polje[135].br[2] = 161; polje[135].voz[2] = 'c';
        polje[135].br[3] = 143; polje[135].voz[3] = 'c';
        polje[135].br[4] = 129; polje[135].voz[4] = 'c';
        polje[135].br[5] = 161; polje[135].voz[5] = 'b';
        polje[135].br[6] = 128; polje[135].voz[6] = 'b';
        polje[135].br[7] = 108; polje[135].voz[7] = 'b';

        polje[136].br[1] = 119; polje[136].voz[1] = 'c';
        polje[136].br[2] = 162; polje[136].voz[2] = 'c';
        polje[136].br[3] = 135; polje[136].voz[3] = 'c';

        polje[137].br[1] = 147; polje[137].voz[1] = 'c';
        polje[137].br[2] = 123; polje[137].voz[2] = 'c';

        polje[138].br[1] = 150; polje[138].voz[1] = 'c';
        polje[138].br[2] = 152; polje[138].voz[2] = 'c';
        polje[138].br[3] = 124; polje[138].voz[3] = 'c';

        polje[139].br[1] = 130; polje[139].voz[1] = 'c';
        polje[139].br[2] = 154; polje[139].voz[2] = 'c';
        polje[139].br[3] = 153; polje[139].voz[3] = 'c';
        polje[139].br[4] = 140; polje[139].voz[4] = 'c';

        polje[140].br[1] = 154; polje[140].voz[1] = 'c';
        polje[140].br[2] = 139; polje[140].voz[2] = 'c';
        polje[140].br[3] = 132; polje[140].voz[3] = 'c';
        polje[140].br[4] = 133; polje[140].voz[4] = 'c';
        polje[140].br[5] = 156; polje[140].voz[5] = 'c';
        polje[140].br[6] = 126; polje[140].voz[6] = 'c';
        polje[140].br[7] = 154; polje[140].voz[7] = 'b';
        polje[140].br[8] = 156; polje[140].voz[8] = 'b';
        polje[140].br[9] = 82; polje[140].voz[9] = 'b';
        polje[140].br[10] = 133; polje[140].voz[10] = 'b';
        polje[140].br[11] = 128; polje[140].voz[11] = 'u';
        polje[140].br[12] = 89; polje[140].voz[12] = 'u';
        polje[140].br[13] = 153; polje[140].voz[13] = 'u';

        polje[141].br[1] = 133; polje[141].voz[1] = 'c';
        polje[141].br[2] = 134; polje[141].voz[2] = 'c';
        polje[141].br[3] = 142; polje[141].voz[3] = 'c';
        polje[141].br[4] = 158; polje[141].voz[4] = 'c';

        polje[142].br[1] = 134; polje[142].voz[1] = 'c';
        polje[142].br[2] = 141; polje[142].voz[2] = 'c';
        polje[142].br[3] = 158; polje[142].voz[3] = 'c';
        polje[142].br[4] = 118; polje[142].voz[4] = 'c';
        polje[142].br[5] = 143; polje[142].voz[5] = 'c';
        polje[142].br[6] = 129; polje[142].voz[6] = 'c';
        polje[142].br[7] = 128; polje[142].voz[7] = 'c';
        polje[142].br[8] = 116; polje[142].voz[8] = 'b';
        polje[142].br[9] = 157; polje[142].voz[9] = 'b';
        polje[142].br[10] = 128; polje[142].voz[10] = 'b';


        polje[143].br[1] = 129; polje[143].voz[1] = 'c';
        polje[143].br[2] = 142; polje[143].voz[2] = 'c';
        polje[143].br[3] = 160; polje[143].voz[3] = 'c';
        polje[143].br[4] = 135; polje[143].voz[4] = 'c';
        polje[143].br[5] = 128; polje[143].voz[5] = 'c';

        polje[144].br[1] = 120; polje[144].voz[1] = 'c';
        polje[144].br[2] = 145; polje[144].voz[2] = 'c';
        polje[144].br[3] = 177; polje[144].voz[3] = 'c';
        polje[144].br[4] = 122; polje[144].voz[4] = 'b';
        polje[144].br[5] = 163; polje[144].voz[5] = 'b';
        polje[144].br[6] = 123; polje[144].voz[6] = 'b';

        polje[145].br[1] = 121; polje[145].voz[1] = 'c';
        polje[145].br[2] = 144; polje[145].voz[2] = 'c';
        polje[145].br[3] = 146; polje[145].voz[3] = 'c';

        polje[146].br[1] = 122; polje[146].voz[1] = 'c';
        polje[146].br[2] = 145; polje[146].voz[2] = 'c';
        polje[146].br[3] = 147; polje[146].voz[3] = 'c';
        polje[146].br[4] = 163; polje[146].voz[4] = 'c';

        polje[147].br[1] = 146; polje[147].voz[1] = 'c';
        polje[147].br[2] = 137; polje[147].voz[2] = 'c';
        polje[147].br[3] = 164; polje[147].voz[3] = 'c';

        polje[148].br[1] = 123; polje[148].voz[1] = 'c';
        polje[148].br[2] = 149; polje[148].voz[2] = 'c';
        polje[148].br[3] = 164; polje[148].voz[3] = 'c';

        polje[149].br[1] = 123; polje[149].voz[1] = 'c';
        polje[149].br[2] = 148; polje[149].voz[2] = 'c';
        polje[149].br[3] = 150; polje[149].voz[3] = 'c';
        polje[149].br[4] = 165; polje[149].voz[4] = 'c';

        polje[150].br[1] = 138; polje[150].voz[1] = 'c';
        polje[150].br[2] = 149; polje[150].voz[2] = 'c';
        polje[150].br[3] = 151; polje[150].voz[3] = 'c';

        polje[151].br[1] = 150; polje[151].voz[1] = 'c';
        polje[151].br[2] = 152; polje[151].voz[2] = 'c';
        polje[151].br[3] = 166; polje[151].voz[3] = 'c';
        polje[151].br[4] = 165; polje[151].voz[4] = 'c';

        polje[152].br[1] = 151; polje[152].voz[1] = 'c';
        polje[152].br[2] = 138; polje[152].voz[2] = 'c';
        polje[152].br[3] = 153; polje[152].voz[3] = 'c';

        polje[153].br[1] = 152; polje[153].voz[1] = 'c';
        polje[153].br[2] = 139; polje[153].voz[2] = 'c';
        polje[153].br[3] = 154; polje[153].voz[3] = 'c';
        polje[153].br[4] = 167; polje[153].voz[4] = 'c';
        polje[153].br[5] = 166; polje[153].voz[5] = 'c';
        polje[153].br[6] = 124; polje[153].voz[6] = 'b';
        polje[153].br[7] = 154; polje[153].voz[7] = 'b';
        polje[153].br[8] = 180; polje[153].voz[8] = 'b';
        polje[153].br[9] = 184; polje[153].voz[9] = 'b';
        polje[153].br[10] = 111; polje[153].voz[10] = 'u';
        polje[153].br[11] = 163; polje[153].voz[11] = 'u';
        polje[153].br[12] = 140; polje[153].voz[12] = 'u';
        polje[153].br[13] = 185; polje[153].voz[13] = 'u';

        polje[154].br[1] = 153; polje[154].voz[1] = 'c';
        polje[154].br[2] = 139; polje[154].voz[2] = 'c';
        polje[154].br[3] = 155; polje[154].voz[3] = 'c';
        polje[154].br[4] = 140; polje[154].voz[4] = 'c';
        polje[154].br[5] = 156; polje[154].voz[5] = 'b';
        polje[154].br[6] = 140; polje[154].voz[6] = 'b';
        polje[154].br[7] = 153; polje[154].voz[7] = 'b';

        polje[155].br[1] = 154; polje[155].voz[1] = 'c';
        polje[155].br[2] = 167; polje[155].voz[2] = 'c';
        polje[155].br[3] = 168; polje[155].voz[3] = 'c';
        polje[155].br[4] = 156; polje[155].voz[4] = 'c';

        polje[156].br[1] = 140; polje[156].voz[1] = 'c';
        polje[156].br[2] = 155; polje[156].voz[2] = 'c';
        polje[156].br[3] = 157; polje[156].voz[3] = 'c';
        polje[156].br[4] = 169; polje[156].voz[4] = 'c';
        polje[156].br[5] = 154; polje[156].voz[5] = 'b';
        polje[156].br[6] = 140; polje[156].voz[6] = 'b';
        polje[156].br[7] = 184; polje[156].voz[7] = 'b';
        polje[156].br[8] = 157; polje[156].voz[8] = 'b';

        polje[157].br[1] = 158; polje[157].voz[1] = 'c';
        polje[157].br[2] = 170; polje[157].voz[2] = 'c';
        polje[157].br[3] = 156; polje[157].voz[3] = 'c';
        polje[157].br[4] = 133; polje[157].voz[4] = 'b';
        polje[157].br[5] = 156; polje[157].voz[5] = 'b';
        polje[157].br[6] = 142; polje[157].voz[6] = 'b';
        polje[157].br[7] = 185; polje[157].voz[7] = 'b';
        polje[157].br[8] = 115; polje[157].voz[8] = 'x';
        polje[157].br[9] = 194; polje[157].voz[9] = 'x';

        polje[158].br[1] = 141; polje[158].voz[1] = 'c';
        polje[158].br[2] = 157; polje[158].voz[2] = 'c';
        polje[158].br[3] = 142; polje[158].voz[3] = 'c';
        polje[158].br[4] = 159; polje[158].voz[4] = 'c';

        polje[159].br[1] = 158; polje[159].voz[1] = 'c';
        polje[159].br[2] = 170; polje[159].voz[2] = 'c';
        polje[159].br[3] = 172; polje[159].voz[3] = 'c';
        polje[159].br[4] = 186; polje[159].voz[4] = 'c';
        polje[159].br[5] = 198; polje[159].voz[5] = 'c';

        polje[160].br[1] = 143; polje[160].voz[1] = 'c';
        polje[160].br[2] = 161; polje[160].voz[2] = 'c';
        polje[160].br[3] = 173; polje[160].voz[3] = 'c';
        polje[160].br[4] = 128; polje[160].voz[4] = 'c';

        polje[161].br[1] = 135; polje[161].voz[1] = 'c';
        polje[161].br[2] = 160; polje[161].voz[2] = 'c';
        polje[161].br[3] = 174; polje[161].voz[3] = 'c';
        polje[161].br[4] = 199; polje[161].voz[4] = 'b';
        polje[161].br[5] = 128; polje[161].voz[5] = 'b';
        polje[161].br[6] = 135; polje[161].voz[6] = 'b';
        polje[161].br[7] = 107; polje[161].voz[7] = 'b';

        polje[162].br[1] = 136; polje[162].voz[1] = 'c';
        polje[162].br[2] = 175; polje[162].voz[2] = 'c';

        polje[163].br[1] = 146; polje[163].voz[1] = 'c';
        polje[163].br[2] = 177; polje[163].voz[2] = 'c';
        polje[163].br[3] = 191; polje[163].voz[3] = 'b';
        polje[163].br[4] = 176; polje[163].voz[4] = 'b';
        polje[163].br[5] = 144; polje[163].voz[5] = 'b';
        polje[163].br[6] = 111; polje[163].voz[6] = 'u';
        polje[163].br[7] = 153; polje[163].voz[7] = 'u';

        polje[164].br[1] = 147; polje[164].voz[1] = 'c';
        polje[164].br[2] = 148; polje[164].voz[2] = 'c';
        polje[164].br[3] = 178; polje[164].voz[3] = 'c';
        polje[164].br[4] = 179; polje[164].voz[4] = 'c';

        polje[165].br[1] = 149; polje[165].voz[1] = 'c';
        polje[165].br[2] = 179; polje[165].voz[2] = 'c';
        polje[165].br[3] = 151; polje[165].voz[3] = 'c';
        polje[165].br[4] = 180; polje[165].voz[4] = 'c';
        polje[165].br[5] = 123; polje[165].voz[5] = 'b';
        polje[165].br[6] = 191; polje[165].voz[6] = 'b';
        polje[165].br[7] = 180; polje[165].voz[7] = 'b';

        polje[166].br[1] = 153; polje[166].voz[1] = 'c';
        polje[166].br[2] = 151; polje[166].voz[2] = 'c';
        polje[166].br[3] = 181; polje[166].voz[3] = 'c';
        polje[166].br[4] = 183; polje[166].voz[4] = 'c';

        polje[167].br[1] = 155; polje[167].voz[1] = 'c';
        polje[167].br[2] = 168; polje[167].voz[2] = 'c';
        polje[167].br[3] = 153; polje[167].voz[3] = 'c';
        polje[167].br[4] = 183; polje[167].voz[4] = 'c';

        polje[168].br[1] = 167; polje[168].voz[1] = 'c';
        polje[168].br[2] = 155; polje[168].voz[2] = 'c';
        polje[168].br[3] = 184; polje[168].voz[3] = 'c';

        polje[169].br[1] = 156; polje[169].voz[1] = 'c';
        polje[169].br[2] = 184; polje[169].voz[2] = 'c';

        polje[170].br[1] = 157; polje[170].voz[1] = 'c';
        polje[170].br[2] = 159; polje[170].voz[2] = 'c';
        polje[170].br[3] = 185; polje[170].voz[3] = 'c';

        polje[171].br[1] = 199; polje[171].voz[1] = 'c';
        polje[171].br[2] = 175; polje[171].voz[2] = 'c';
        polje[171].br[3] = 173; polje[171].voz[3] = 'c';

        polje[172].br[1] = 128; polje[172].voz[1] = 'c';
        polje[172].br[2] = 159; polje[172].voz[2] = 'c';
        polje[172].br[3] = 187; polje[172].voz[3] = 'c';

        polje[173].br[1] = 160; polje[173].voz[1] = 'c';
        polje[173].br[2] = 174; polje[173].voz[2] = 'c';
        polje[173].br[3] = 188; polje[173].voz[3] = 'c';
        polje[173].br[4] = 171; polje[173].voz[4] = 'c';

        polje[174].br[1] = 161; polje[174].voz[1] = 'c';
        polje[174].br[2] = 175; polje[174].voz[2] = 'c';
        polje[174].br[3] = 173; polje[174].voz[3] = 'c';

        polje[175].br[1] = 162; polje[175].voz[1] = 'c';
        polje[175].br[2] = 174; polje[175].voz[2] = 'c';
        polje[175].br[3] = 171; polje[175].voz[3] = 'c';

        polje[176].br[1] = 177; polje[176].voz[1] = 'c';
        polje[176].br[2] = 189; polje[176].voz[2] = 'c';
        polje[176].br[3] = 190; polje[176].voz[3] = 'b';
        polje[176].br[4] = 163; polje[176].voz[4] = 'b';

        polje[177].br[1] = 144; polje[177].voz[1] = 'c';
        polje[177].br[2] = 176; polje[177].voz[2] = 'c';
        polje[177].br[3] = 163; polje[177].voz[3] = 'c';

        polje[178].br[1] = 164; polje[178].voz[1] = 'c';
        polje[178].br[2] = 189; polje[178].voz[2] = 'c';
        polje[178].br[3] = 191; polje[178].voz[3] = 'c';

        polje[179].br[1] = 165; polje[179].voz[1] = 'c';
        polje[179].br[2] = 164; polje[179].voz[2] = 'c';
        polje[179].br[3] = 191; polje[179].voz[3] = 'c';

        polje[180].br[1] = 165; polje[180].voz[1] = 'c';
        polje[180].br[2] = 181; polje[180].voz[2] = 'c';
        polje[180].br[3] = 193; polje[180].voz[3] = 'c';
        polje[180].br[4] = 190; polje[180].voz[4] = 'b';
        polje[180].br[5] = 153; polje[180].voz[5] = 'b';
        polje[180].br[6] = 165; polje[180].voz[6] = 'b';
        polje[180].br[7] = 184; polje[180].voz[7] = 'b';

        polje[181].br[1] = 166; polje[181].voz[1] = 'c';
        polje[181].br[2] = 180; polje[181].voz[2] = 'c';
        polje[181].br[3] = 193; polje[181].voz[3] = 'c';
        polje[181].br[4] = 182; polje[181].voz[4] = 'c';

        polje[182].br[1] = 181; polje[182].voz[1] = 'c';
        polje[182].br[2] = 183; polje[182].voz[2] = 'c';
        polje[182].br[3] = 195; polje[182].voz[3] = 'c';

        polje[183].br[1] = 167; polje[183].voz[1] = 'c';
        polje[183].br[2] = 182; polje[183].voz[2] = 'c';
        polje[183].br[3] = 166; polje[183].voz[3] = 'c';
        polje[183].br[4] = 196; polje[183].voz[4] = 'c';

        polje[184].br[1] = 169; polje[184].voz[1] = 'c';
        polje[184].br[2] = 185; polje[184].voz[2] = 'c';
        polje[184].br[3] = 168; polje[184].voz[3] = 'c';
        polje[184].br[4] = 196; polje[184].voz[4] = 'c';
        polje[184].br[5] = 197; polje[184].voz[5] = 'c';
        polje[184].br[6] = 180; polje[184].voz[6] = 'b';
        polje[184].br[7] = 185; polje[184].voz[7] = 'b';
        polje[184].br[8] = 156; polje[184].voz[8] = 'b';
        polje[184].br[9] = 153; polje[184].voz[9] = 'b';

        polje[185].br[1] = 184; polje[185].voz[1] = 'c';
        polje[185].br[2] = 186; polje[185].voz[2] = 'c';
        polje[185].br[3] = 170; polje[185].voz[3] = 'c';
        polje[185].br[4] = 184; polje[185].voz[4] = 'b';
        polje[185].br[5] = 187; polje[185].voz[5] = 'b';
        polje[185].br[6] = 157; polje[185].voz[6] = 'b';
        polje[185].br[7] = 128; polje[185].voz[7] = 'u';
        polje[185].br[8] = 153; polje[185].voz[8] = 'u';

        polje[186].br[1] = 159; polje[186].voz[1] = 'c';
        polje[186].br[2] = 185; polje[186].voz[2] = 'c';
        polje[186].br[3] = 198; polje[186].voz[3] = 'c';

        polje[187].br[1] = 172; polje[187].voz[1] = 'c';
        polje[187].br[2] = 198; polje[187].voz[2] = 'c';
        polje[187].br[3] = 188; polje[187].voz[3] = 'c';
        polje[187].br[4] = 128; polje[187].voz[4] = 'b';
        polje[187].br[5] = 185; polje[187].voz[5] = 'b';

        polje[188].br[1] = 128; polje[188].voz[1] = 'c';
        polje[188].br[2] = 173; polje[188].voz[2] = 'c';
        polje[188].br[3] = 199; polje[188].voz[3] = 'c';
        polje[188].br[4] = 187; polje[188].voz[4] = 'c';

        polje[189].br[1] = 176; polje[189].voz[1] = 'c';
        polje[189].br[2] = 190; polje[189].voz[2] = 'c';
        polje[189].br[3] = 178; polje[189].voz[3] = 'c';

        polje[190].br[1] = 191; polje[190].voz[1] = 'c';
        polje[190].br[2] = 189; polje[190].voz[2] = 'c';
        polje[190].br[3] = 192; polje[190].voz[3] = 'c';
        polje[190].br[4] = 176; polje[190].voz[4] = 'b';
        polje[190].br[5] = 191; polje[190].voz[5] = 'b';
        polje[190].br[6] = 180; polje[190].voz[6] = 'b';

        polje[191].br[1] = 179; polje[191].voz[1] = 'c';
        polje[191].br[2] = 178; polje[191].voz[2] = 'c';
        polje[191].br[3] = 190; polje[191].voz[3] = 'c';
        polje[191].br[4] = 192; polje[191].voz[4] = 'c';
        polje[191].br[5] = 190; polje[191].voz[5] = 'b';
        polje[191].br[6] = 165; polje[191].voz[6] = 'b';
        polje[191].br[7] = 163; polje[191].voz[7] = 'b';

        polje[192].br[1] = 191; polje[192].voz[1] = 'c';
        polje[192].br[2] = 194; polje[192].voz[2] = 'c';
        polje[192].br[3] = 190; polje[192].voz[3] = 'c';

        polje[193].br[1] = 194; polje[193].voz[1] = 'c';
        polje[193].br[2] = 180; polje[193].voz[2] = 'c';
        polje[193].br[3] = 181; polje[193].voz[3] = 'c';

        polje[194].br[1] = 195; polje[194].voz[1] = 'c';
        polje[194].br[2] = 193; polje[194].voz[2] = 'c';
        polje[194].br[3] = 192; polje[194].voz[3] = 'c';
        polje[194].br[4] = 157; polje[194].voz[4] = 'x';

        polje[195].br[1] = 182; polje[195].voz[1] = 'c';
        polje[195].br[2] = 197; polje[195].voz[2] = 'c';
        polje[195].br[3] = 194; polje[195].voz[3] = 'c';

        polje[196].br[1] = 183; polje[196].voz[1] = 'c';
        polje[196].br[2] = 197; polje[196].voz[2] = 'c';
        polje[196].br[3] = 184; polje[196].voz[3] = 'c';

        polje[197].br[1] = 196; polje[197].voz[1] = 'c';
        polje[197].br[2] = 195; polje[197].voz[2] = 'c';
        polje[197].br[3] = 184; polje[197].voz[3] = 'c';

        polje[198].br[1] = 159; polje[198].voz[1] = 'c';
        polje[198].br[2] = 186; polje[198].voz[2] = 'c';
        polje[198].br[3] = 187; polje[198].voz[3] = 'c';
        polje[198].br[4] = 199; polje[198].voz[4] = 'c';

        polje[199].br[1] = 171; polje[199].voz[1] = 'c';
        polje[199].br[2] = 188; polje[199].voz[2] = 'c';
        polje[199].br[3] = 198; polje[199].voz[3] = 'c';
        polje[199].br[4] = 128; polje[199].voz[4] = 'b';
        polje[199].br[5] = 161; polje[199].voz[5] = 'b';

        /*
        polje[13].br[1] = ; polje[13].voz[1] = '';
        polje[13].br[2] = ; polje[13].voz[2] = '';
        polje[13].br[3] = ; polje[13].voz[3] = '';
        polje[13].br[4] = ; polje[13].voz[4] = '';
        polje[13].br[5] = ; polje[13].voz[5] = '';
        polje[13].br[6] = ; polje[13].voz[6] = '';
        polje[13].br[7] = ; polje[13].voz[7] = '';
        polje[13].br[8] = ; polje[13].voz[8] = '';
        */
    //gotovo
    queue<int> Q; vector<int> v2;
    int poc, x, n, brojac = 0, br_det;
    char ch[100]; const bool da = true;

    for(int i = 0; i < 100; i++) ch[i] = '0';
    n = 1;
    printf("Enter starting field: ");
    scanf("%d", &poc);
    printf("Number of detectives? ");
    scanf("%d", &br_det);

    ponovi:

    printf("\nEnter the means of transportation of that Mr. X used: ");
    char temp[2];
    scanf("%s", temp);
    ch[n-1] = temp[0];
    for(int g = 0; g < br_det; g++) {
      printf("\nEnter the move of detective %d: ", g+1);
      scanf("%d", &de[g].det[n-1]);
    }
    Q.push(poc);
    polje[poc].d.push_back(0);
    while(da && !Q.empty()) {
        x = Q.front();
        Q.pop();
        brojac = polje[x].d.front() + 1;        //udaljenost
        //printf("[[[[%d]]]]]]\t", brojac);
        if(brojac > n) {
          //printf("----%d----", x);
          break; }
        polje[x].d.pop_front();
        //provjerava da li je mister x ulovljen
        for(int h = 0; h < br_det; h++) {
            if(x == de[h].det[brojac-1]) {
              printf("\nMr. X caught!");
              goto izadji2;}
        }
        for(int i = 1; polje[x].br[i] != 0; i++) {
            //provjeravanje nacina prijevoza i dostupnosti mjesta
            if(ch[brojac-1] == polje[x].voz[i] || ch[brojac-1] == 'x') {
                for(int h = 0; h < br_det; h++) {
                  if(polje[x].br[i] == de[h].det[brojac-1])
                      goto izadji;
                }
                v2.push_back(polje[x].br[i]);
                //printf("[%d](%d) ", polje[x].br[i], brojac);
                deque<int>::iterator nadjeno;
                nadjeno = find(polje[ polje[x].br[i] ].d.begin(),
                               polje[ polje[x].br[i] ].d.end(), x);
                               //gleda se da li postoji vec takva udaljenost
                if(nadjeno == polje[ polje[x].br[i] ].d.end()) {  //ako ne postoji
                   polje[ polje[x].br[i] ].d.push_back(brojac);   //  memorira se
                   sort(polje[ polje[x].br[i] ].d.begin(),
                        polje[ polje[x].br[i] ].d.end());        //sortiranje
                }
                Q.push(polje[x].br[i]);         //novo polje stavlja se na vrh kupa
            }
            izadji:
                int bezveze = 0;
        }
        izadji2:
            int bezveze2 = 0;

    }
    vector<int> v1;
    v1.clear();
    for(int i = 1; i < 200; i++) {          //trazenje svih polja s udaljenosti n
        bool found = binary_search(polje[i].d.begin(), polje[i].d.end(), n);
        if(found) v1.push_back(i);
    }
    cout << endl << "_____" << endl;
    for(vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter++)
      cout << *iter << " ";
    cout << endl;
    n++;
    goto ponovi;
    scanf("\n");
    return 0;
}
