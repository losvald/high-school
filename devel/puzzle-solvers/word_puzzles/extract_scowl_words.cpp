/*
 * extract_scowl_words.cpp
 *
 * Copyright (C) 2008 Leo Osvald <leo.osvald@gmail.com>
 *
 * This file is part of Word Games Unpuzzler.
 *
 * Word Games Unpuzzler is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Word Games Unpuzzler is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Word Games Unpuzzler. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
const int pre_size = 8;
FILE *in, *out;
string w = "-words.";
string pre[pre_size] = {"american", "british", "british_z", "canadian", "english",
                "variant_0", "variant_1", "variant_2"};
string strnum(int x) {
  char buff[15];
  sprintf(buff, "%d", x);
  return string(buff);
}
char buff[50];
int main() {
  out = fopen("all_words.txt", "a");
  for(int i = 0; i < pre_size; ++i) {
    for(int x = 0; x < 100; x+=5) {
      string name = pre[i] + w + strnum(x);
      try{
        in = fopen(name.c_str(), "r");
        if(in == NULL) continue;
        while( fgets(buff, 49, in) )
          fprintf(out, "%s", buff);
        fclose(in);
        printf("%s complete!\n", name.c_str());
      }
      catch(int x) {}
    }
  }
  printf("done");
  scanf("\n");
  return 0;
}
