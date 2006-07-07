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
#include <algorithm>
#include <iostream>
#include <cstring>
#include <deque>
#define N 10000
using namespace std;
int maks = 0;
deque<int> deck(52);
deque<int> d[2];
void srnd(void)
{
  srand((unsigned) time(NULL));
}
void rndshuff()
{
  int r1, r2;
  r1 = rand()%52;
  while((r2 = rand()%52) == r1) ;
  swap(deck[r1],deck[r2]);
}
void promijesaj() {
    for(int i = 0; i < 52; ++i) deck[i] = (i < 13);
    for(int i = 0; i < 100; rndshuff(), ++i);
}
void raspolovi() {
    for(int i = 0; i < 52; ++i) d[i/26].push_back(deck[i]);
}
int igraj() {
    d[0].clear(); d[1].clear(); deck.clear();
    promijesaj();
    raspolovi();
    int sec = 0;
    deque<int> kup;
    for(int curr = 0; !d[0].empty() && !d[1].empty(); curr ^= 1, sec+=2) {
        if(!kup.empty() && kup.back() == 1) {
            d[curr].insert(d[curr].begin(), kup.begin(), kup.end());
            kup.clear();
            //printf("%d %d\n",  d[0].size(), d[1].size() );
        }
        kup.insert(kup.end(), d[curr].back());
        d[curr].pop_back();
    }
    maks = max(maks, sec);
    return sec;
}
int main() {
    srnd(); long long tsec = 0;
    for(int i = 0; i < N; ++i) tsec += igraj();
      //printf("Sec = %d\n", igraj());
    int pros = tsec/N;
    int h, m, s;
    h = maks/3600; maks %= 3600;
    m = maks/60; maks %= 60;
    s = maks;
    printf("\n\nMax(hh:mm::ss) = %02d:%02d:%02d", h, m, s);
    h = pros/3600; pros %= 3600;
    m = pros/60; pros %= 60;
    s = pros;
    printf("\n\nAverage(hh:mm::ss) = %02d:%02d:%02d", h, m, s);
    scanf("\n");
    return 0;
}
