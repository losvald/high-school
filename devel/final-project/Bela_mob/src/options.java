/*
 * options.java
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

import java.util.Random;
import java.lang.Math;
public class options {
   String ime, default_ime;
   int ID;
   boolean selected[];
   int selected_size;
   public options() {
     Random random = new Random();
     default_ime = new String("Igr");
     for(int i = 0; i < 4; ++i)
       default_ime += Math.abs( random.nextInt() % 10 );
     ime = default_ime;
     selected = new boolean[2];
     selected[0] = false;
     selected[1] = true;
   }
   public void update_ime(String s) { ime = s; }
   public void update_selected(boolean sel[], int len) {
     selected_size = len;
     selected = new boolean[len];
     for(int i = 0; i < len; ++i)
       selected[i] = sel[i];
   }
   public boolean get_selected(int x) { return selected[x]; }
   public String get_ime() { return ime; }
   public String get_default_ime() { return default_ime; }
}
