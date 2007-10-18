/*
 * deck.java
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

import java.lang.Math;
import java.util.Random;
public class deck {
  karta[] a;
  Random random;
  int rand_offset;
  final int number_of_swaps = 300;
  public deck() {
    a = new karta[32];
    for(int i = 0; i < 32; ++i)
      a[i] = new karta(i);
    random = new Random();
    rand_offset = 1;
  }
  public int rand(int x) {
    rand_offset *= 1997;
    rand_offset %= 97;
    if(rand_offset == 0) rand_offset = 1;
    return Math.abs( (random.nextInt()+rand_offset) % x );
  }
  public karta get_kth(int x) { return a[x]; }
  public void shuffle() {
    for(int i = 0; i < 32; ++i) a[i] = new karta(i); //mozda treba new...
    for(int i = 0; i < number_of_swaps; ++i) {
      int r1 = rand(32);
      int r2 = rand(32);
      karta t = a[r1]; a[r1] = a[r2]; a[r2] = t;
    }
  }
}
