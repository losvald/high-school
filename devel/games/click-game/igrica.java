/*
 * Copyright (C) 2007 Leo Osvald <leo.osvald@gmail.com>
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

import java.awt.*;
import java.applet.*;
import java.util.*;
import java.lang.*;
import java.io.*;
class point {
  int x, y;
  point() { x = 0; y = 0; }
  point(int x, int y) { this.x = x; this.y = y; }
}
public class igrica extends Applet implements Runnable
{
  Thread runner;
  public Graphics g;
  Font deffont = new Font("Helvetica", Font.PLAIN,  12);
  Font font1 = new Font("Helvetica", Font.PLAIN,  22);
  int cg_w, cg_h, cg_dot_size, cg_menux, cg_menuy, cg_menuh;
  point[] p;
  point target;
  boolean gotovo;
  int count, delta;
  int best_estimated;
  double curr_dist, last_dist;
  double roundto(double x, int y) {
    return Math.round(x*Math.pow(10, y))/Math.pow(10, y);
  }
  boolean equal(double x, double y) {
    if(Math.abs(x-y) < cg_dot_size) return true;
    return false;
  }
  double dist(point a, point b) {
    return Math.sqrt((double)(a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
  }
  void reset() {
    best_estimated = (int) (2*Math.log(cg_h/cg_dot_size)/Math.log(2))
                     + (int) (2*Math.log(cg_h/cg_dot_size)/Math.log(2));
    count = 0;
    target = new point( (int) (10000*Math.random())%cg_w, (int) (10000*Math.random())%cg_h );
  }
  public void init() {
    cg_w = 1000;
    cg_h = 500;
    cg_menux = 0;
    cg_menuy = cg_h + 5;
    cg_dot_size = 2;
    p = new point[5000];
    reset();
  }
  public void start() {
       if (runner == null)
       {
           runner = new Thread (this);
           runner.start();
       }
  }
  public void stop() {
    if(runner != null) {
      runner.stop();
      runner = null;
    }
  }
  public void run() {
      reset();
      repaint();
  }
  public boolean mouseDown(Event evt, int x, int y) {
     if(x >= 0 && x < cg_w && y >= 0 && y < cg_h) {
       if(gotovo) return true;
       p[count] = new point(x, y);
       ++count;
       last_dist = curr_dist;
       curr_dist = dist(p[count-1], target);
       if(count == 1 || equal(curr_dist, last_dist)) delta = 0;
       else if(curr_dist < last_dist) delta = 1;
       else delta = -1;
       if(curr_dist < 2*cg_dot_size) gotovo = true;
     }
     else {
       gotovo = false;
       reset();
     }
     repaint();
     return true;
  }
  public void paint(Graphics gr) {
    g = gr;
    g.setColor(Color.gray);
    g.drawRect(0, 0, cg_w, cg_h);
    g.setColor(Color.black);
    g.setFont(deffont);
    for(int i = Math.max(count-1, 0); i < count; ++i) {
      //if(i+1 == count) g.setColor(Color.blue);
      //else if(i+2 == count) g.setColor(Color.green);
      if(delta > 0) g.setColor(Color.red);
      else if(delta == 0) g.setColor(Color.gray);
      else if(delta < 0) g.setColor(Color.blue);

      g.fillOval (p[i].x-cg_dot_size/2, p[i].y-cg_dot_size/2, cg_dot_size, cg_dot_size);
      g.drawString(""+(i+1), p[i].x, p[i].y);
    }
    g.setFont(font1);
    if(delta > 0) {
      g.setColor(Color.red);
      g.drawString("TOPLIJE", cg_menux, cg_menuy + 15);
    }
    else if(delta < 0) {
      g.setColor(Color.blue);
      g.drawString("HLADNIJE", cg_menux, cg_menuy + 15);
    }
    else {
      g.setColor(Color.gray);
      g.drawString("ISTO", cg_menux, cg_menuy + 15);
    }
    g.setColor(Color.black);
    g.drawString(""+count, cg_menux + cg_w/2, cg_menuy + 15);
    if(gotovo)
      g.drawString("POBJEDA!", cg_menux + cg_w - 50, cg_menuy + 15);
    else
      g.drawString("Best:"+best_estimated, cg_menux + cg_w - 80, cg_menuy + 15);

  }
}
