/*
 * imei_generator.cpp
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
#include <iostream>
#include <string>
#define MAX 0xFFFFF
#define MAX_CODE 1000000
using namespace std;
int Count[MAX];
int hash(int code) {
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
    if(times%3) curr ^= xor2;
    else if(times % 4) curr |= mid_PRIME;
    else curr ^= xor2 & curr & mid_PRIME;
    curr %= mid_PRIME;
    curr ^= xor3;
    curr *= mid_PRIME;
    curr %= high_PRIME;
    if(curr < 100)
      curr *= mid_PRIME;
  }
  if(curr >= MAX) printf("Error (code %d-> %d)\n", code, curr);
  return curr;
}
void test() {
  int isto = 0;
  for(int i = 0; i < MAX_CODE; ++i) {
    int h = hash(i);
    ++Count[ h ];
    if(h == i) ++isto;
  }
  int maxi = 0, avg = 0, n_avg = 0;
  for(int i = 0; i < MAX; ++i) {
    maxi >?= Count[i];
    if(Count[i]) {
      avg += Count[i];
      n_avg++;
    }
  }
  printf("Maxi: %d\t Average: %d\tN_avg = %d\tIsto: %d\n", maxi, avg/n_avg, n_avg, isto);
  for(int k = 10; k < MAX; k*= 10) {
    int cnt = 0;
    for(int i = 0; i < MAX; ++i)
      if(Count[i] < k && Count[i]) ++cnt;
    printf("Istih < %d: %d\n", k, cnt);
  }
}
int main() {
  int code;
  test();
    while(1) {
    printf("IMEI samo onih 6 brojeva:\n");
    scanf("%d", &code);
    if(code < 0) break;
    printf("%d\n", hash(code) );
  }
  scanf("\n");
  return 0;
}
