/*
 * Log.java
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

import javax.microedition.lcdui.*;
public class Log {
  List log;
  final int max_line = 50;
  int curr_line;
  public boolean empty() { return curr_line == 0; }
  public int size() { return curr_line; }
  public void clear() {
    log.deleteAll();
  }
  public void push_error(String error) {
    log.append("ERROR: "+error, null);
  }
  public void push_game_msg(String msg) {
    log.append("Game: "+msg, null);
  }
  public void push_msg(String msg) {
    if(++curr_line >= max_line) {
      log.delete(0);
      --curr_line;
    }
    log.append(msg, null);
  }
  public String get_msg(int x) { return log.getString(x); }
  public Log() {
    log = new List("Log", Choice.IMPLICIT);
    curr_line = 0;
  }
}
