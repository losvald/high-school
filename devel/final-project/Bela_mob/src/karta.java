/*
 * karta.java
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

public class karta {

  int broj, boja;

  public karta() {}
  public karta(int x) {
    boja = x/8;
    broj = x%8;
  }
  public int get_id() { return boja*8 + broj; }
  public int get_points(int adut) {
    if(boja == adut && broj == 4) return 20;
    else if(boja == adut && broj == 2) return 14;
    else if(broj == 3) return 10;
    else if(broj == 4) return 2;
    else if(broj == 5) return 3;
    else if(broj == 6) return 4;
    else if(broj == 7) return 11;
    return 0;
  }
  public boolean less_than(karta b, int adut) {
    int v_a = this.broj;
    int v_b = b.broj;
    if(v_a == 7) v_a = 8;
    if(v_b == 7) v_b = 8;
    if(v_a == 3) v_a = 7;
    if(v_b == 3) v_b = 7;
    if(this.boja == b.boja && b.boja == adut) {
      if(v_a == 4) v_a = 100;
      else if(v_a == 2) v_a = 50;
      if(v_b == 4) v_b = 100;
      else if(v_b == 2) v_b = 50;
    }
    if(this.boja == b.boja) return v_a < v_b;
    return this.boja < b.boja;
    /*int v1 = 8*this.boja + this.broj;
    int v2 = 8*b.boja + b.broj;
    return v1 < v2;*/
  }
  public boolean jaca_od(karta b, int adut) {
    if(this.boja == adut && b.boja != adut) return true;
    else if(this.boja != adut && b.boja == adut) return false;
    else if(this.boja != adut && b.boja != adut && this.boja != b.boja) return false;
    return !less_than(b, adut);
  }
  public int get_broj() {return broj; }
  public int get_boja() {return boja; }
  public void set_lowest() { broj = -1; boja = -1; }
  public void update_broj(int x) { broj = x; }
  public void update_boja(int x) { boja = x; }
}
