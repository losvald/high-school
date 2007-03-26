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
class star {
   double info1, info2;
   String name; //ime
   double d; //declination
   double r; //right ascension
   double M1, M2; //aps magnituda
   double m1, m2; //prividna magnituda
   double dist;
   double dd, dr, ddist; //default that
   double x, y, z; //current position
   double vx, vy; //position on map
   int size; //size on map
   boolean vis; //visible on map
   public star() {d = 0; r = 0; size = 5;}
   void set(double a, double b, double c, double mag1, double mag2) {
      if(b < 0) b = 360-b;
      dd = d = a; dr = r = b; ddist = dist = c;
      z = Math.sin(Math.toRadians(d))*dist;
      double t = Math.cos(Math.toRadians(d))*dist;
      x = Math.sin(Math.toRadians(r))*t;
      y = Math.cos(Math.toRadians(r))*t;
      dist = Math.sqrt(x*x+y*y+z*z);
      m1 = mag1; m2 = mag2;
      M1 = m1-5*(Math.log(dist)/Math.E)+5;
      M2 = m2-5*(Math.log(dist)/Math.E)+5;
   }
   void rename(String novoime) {
     name = novoime;
   }
   void change(double a, double b, double c) {
     d = a; r = b; dist = c;
     m1 = M1+5*(Math.log(dist)/Math.E)-5;
     m2 = M2+5*(Math.log(dist)/Math.E)-5;
   }
   void setv(double a, double b) {vx = a; vy = -b;}
   void show() {vis = true;}
   void hide() {vis = false;}
   boolean visible() {return vis;}
   double getvx() {return vx;}
   double getvy() {return vy;}
   int getsize() {return size;}
   double getdist() {return dist; }
   double getd() {return d;}
   double getr() {return r;}
   double getx() {return x;}
   double gety() {return y;}
   double getz() {return z;}
   double getM1() {return M1;}
   double getM2() {return M2;}
   double getm1() {return m1;}
   double getm2() {return m2;}
   String getname() {return name;}
   double getinfo1() {return info1;}
   double getinfo2() {return info2;}
   void setinfo(double a, double b) {info1=a; info2=b;}
}
public class simulacija extends Applet implements Runnable
{
  Thread runner;
  public Graphics g;
  Font deffont = new Font("Helvetica", Font.PLAIN,  12);
  Font font1 = new Font("Helvetica", Font.PLAIN,  22);
  int posx, posy, R, defR;
  int xx, yy, ly, lx;
  int kw;
  double alpha, defalpha; //viewing angle 2*alpha = all
  double dist, defdist; //default distance = R/tan(alpha)
  double cd, cr; //center r and d
  int clickR;
  int bupx, bupy, bupw, buph, bdownx, bdowny, bdownw, bdownh,
      bleftx, blefty, bleftw, blefth, brightx, brighty, brightw, brighth,
      bzoominx, bzoominy, bzoomoutx, bzoomouty, bzoomh, bzoomw,
      bfixx, bfixy, bfixw, bfixh, bdvx, bdvy, bdvw, bdvh; //gumbi
  star obj[];
  int n; //broj zvijezda
  int m; //broj veza u grafu
  int curr;
  int sel; //selected
  int sad;
  int graf[][];
  File infile;
  Scanner scan;
  double roundto(double x, int y) {
    return Math.round(x*Math.pow(10, y))/Math.pow(10, y);
  }
  boolean equal(double x, double y) {
    if(Math.abs(x-y) < 1E-9) return true;
    return false;
  }
  boolean istipred(double x, double y) {
    if(x < 0 && y >= 0) return false;
    if(x >= 0 && y < 0) return false;
    return true;
  }
  boolean inview(double d, double r) {
     double r2 = 0, d2 = 0;
     double D = 0, E = 0; //kut sa suprotnim polupravcem od d i r
     if(r-cr >= 180)  r-=360;
     else if(r-cr <= -180)  r+=360;
     if(Math.abs(r-cr) >= 90 && istipred(d, cd)) {
	   if(r-cr >= 90) r2 = (r-cr) - 90;
	   else r2 = 90+(r-cr);
	   d = Math.toRadians(d);
	   r2 = Math.toRadians(r2);
	   if(cd >= 0) {
	     D = Math.acos(Math.cos(d)*Math.sqrt(Math.tan(d)*Math.tan(d)+Math.cos(r2)*Math.cos(r2)));
	     D = Math.toDegrees(D);
	     E = Math.acos(Math.cos(d)*Math.sqrt(Math.tan(d)*Math.tan(d)+Math.sin(r2)*Math.sin(r2)));
	     E = Math.toDegrees(E);
	     d2 = D+(90-cd);
	   }
	   else {
	     D = Math.acos(Math.cos(-d)*Math.sqrt(Math.tan(-d)*Math.tan(-d)+Math.cos(r2)*Math.cos(r2)));
	     D = Math.toDegrees(D);
	     E = Math.acos(Math.cos(-d)*Math.sqrt(Math.tan(-d)*Math.tan(-d)+Math.sin(r2)*Math.sin(r2)));
	     E = Math.toDegrees(E);
	     d2 = -(D+(90+cd));
	   }
	   if(r-cr >= 90) r2 = E;
	   else r2 = -E;
        }
     else  { d2 = d-cd; r2 = r-cr;}
     obj[sad].setinfo(D, E);
     if(Math.abs(d2) > alpha || Math.abs(r2) > alpha)
       return false;
     double dd = Math.toRadians(d2);
     double rr = Math.toRadians(r2);
     return (dist*Math.tan(dd))*(dist*Math.tan(dd))
          + (dist*Math.tan(rr))*(dist*Math.tan(rr))
          <= R*R;
  }
  double kvadrant(double x, double y) {
    //vraca [0,360]
    if(x == 0 && y == 0) return 0;
    else if(y == 0 && x > 0) return 90;
    else if(y == 0 && x < 0) return 270;
    else if(x == 0 && y > 0) return 0;
    else if(x == 0 && y < 0) return 180;
    else if(y < 0) return 180+Math.toDegrees(Math.atan(x/y));
    else if(x < 0) return 360+Math.toDegrees(Math.atan(x/y));
    return Math.toDegrees(Math.atan(x/y));

  }
  void updview() {
    for(int i = 0; i < n; ++i) {
      sad = i;
      if( inview(obj[i].getd(), obj[i].getr()) && i != curr) {
         obj[i].show();
	 double r = obj[i].getr(), d = obj[i].getd();
	 double r2 = 0, d2 = 0;
	 double D, E; //kut sa suprotnim polupravcem od r
	 if(r-cr >= 180)  r-=360;
         else if(r-cr <= -180)  r+=360;
         if(Math.abs(r-cr) >= 90 && istipred(d, cd)) {
	   if(r-cr >= 90) r2 = (r-cr) - 90;
	   else r2 = 90+(r-cr);
	   d = Math.toRadians(d);
	   r2 = Math.toRadians(r2);
	   if(cd >= 0) {
	     D = Math.acos(Math.cos(d)*Math.sqrt(Math.tan(d)*Math.tan(d)+Math.cos(r2)*Math.cos(r2)));
	     D = Math.toDegrees(D);
	     E = Math.acos(Math.cos(d)*Math.sqrt(Math.tan(d)*Math.tan(d)+Math.sin(r2)*Math.sin(r2)));
	     E = Math.toDegrees(E);
	     d2 = D+(90-cd);
	   }
	   else {
	     D = Math.acos(Math.cos(-d)*Math.sqrt(Math.tan(-d)*Math.tan(-d)+Math.cos(r2)*Math.cos(r2)));
	     D = Math.toDegrees(D);
	     E = Math.acos(Math.cos(-d)*Math.sqrt(Math.tan(-d)*Math.tan(-d)+Math.sin(r2)*Math.sin(r2)));
	     E = Math.toDegrees(E);
	     d2 = -(D+(90+cd));
	   }
	   if(r-cr >= 90) r2 = E;
	   else r2 = -E;
         }
         else  { d2 = d-cd; r2 = r-cr;}
	 double rangle = Math.toRadians(r2);
	 double dangle = Math.toRadians(d2);
         obj[i].setv(dist*Math.tan(rangle), dist*Math.tan(dangle));
      }
      else {
         obj[i].hide();
      }
    }
    repaint();
  }
  void defview() {alpha = defalpha; cd = cr = 0; }
  void setview(double d, double r) {
    cd+=d;
    if(cd > 90) {cd = 180-cd; cr+=180;}
    else if(cd < -90) {cd = -180-cd; cr+=180;}
    cr+=r;
    if(cr >= 360) cr -= 360;
    else if(cr < 0) cr += 360;
    updview();
  }
  void viewback() {
    cd = -cd;
    cr += 180;
    if(cr >= 360) cr-=360;
  }
  void defzoom() {
    alpha = defalpha;
    defdist = dist = R/Math.tan(Math.toRadians(defalpha));
    updview();
  }
  void zoom(double by) {
     alpha += by;
     dist = R/Math.tan(Math.toRadians(alpha));
     updview();
  }
  void fix(int x) {
     curr = x;
     obj[x].change(0,0,0);
     for(int i = 0; i < n; ++i) {
        if(i == x) continue;
        double dist = Math.sqrt((obj[i].x-obj[x].x)*(obj[i].x-obj[x].x)
                           + (obj[i].y-obj[x].y)*(obj[i].y-obj[x].y)
                           + (obj[i].z-obj[x].z)*(obj[i].z-obj[x].z) );
        double d = Math.toDegrees(Math.asin((obj[i].z-obj[x].z)/dist));
        double r = kvadrant(obj[i].x-obj[x].x, obj[i].y-obj[x].y);
        obj[i].change(d,r,dist);
     }
     updview();
  }
  public int nadji_ime(String str) {
    for(int i = 0; i < n; ++i) if(str.equals(obj[i].getname()) ) return i;
    return -1;
  }
  public void input() {
     obj = new star[100];
     curr = 0;
     obj[0] = new star();
     obj[0].set(0,0,0, 0, 0); //default view, obj[0] is not star
     obj[0].rename("Zemlja");
     int kol = scan.nextInt(); m =scan.nextInt(); scan.nextLine();
     for(n = 1; n <= kol; ++n) {
        String name; name = scan.nextLine();
        double r = scan.nextDouble();
        double d = scan.nextDouble();
        double dist = scan.nextDouble();
	double mag1 = scan.nextDouble();
	double mag2 = scan.nextDouble();
        obj[n] = new star();
        obj[n].set(r, d, dist, mag1, mag2);
	obj[n].rename(name);
	scan.nextLine();
     }
     //inicijalizacija grafa povezanosti zvijezda
     graf = new int[m][2];
     //ucitavanje grafa
     for(int i = 0; i < m; ++i) {
       String s1 = scan.nextLine();
       String s2 = scan.nextLine();
       int a = nadji_ime(s1);
       int b = nadji_ime(s2);
       if(a == -1 || b == -1) continue;
       graf[i][0] = a; graf[i][1] = b;
     }
  }
  public void init() {
    posx = 50; posy = 50; defR = R = 200;
    defalpha = alpha = 40;
    dist = defdist = defR/Math.tan(Math.toRadians(defalpha));
    cd = 0; cr = 0;
    clickR = 5;
    sel = 0;
    kw = 120;
    bupw = buph = bdownw = bdownh = brightw = brighth = bleftw
         = blefth = bdvw = bdvh = bzoomh = bzoomw = 50;
    bupx = posx+R-bupw/2; bupy = posy+2*R+20;
    bdownx = posx+R-bdownw/2; bdowny = bupy+buph+brighth;
    brightx = posx+R+bupw/2; brighty = bupy+buph;
    bleftx = posx+R-bupw/2-bleftw; blefty = bupy+buph;
    bdvx = bupx; bdvy = blefty;
    bzoominx = bupx+5*bupw; bzoominy = bupy;
    bzoomoutx = bupx+5*bupw; bzoomouty = bdowny;
    bfixx = posx+2*R+posx; bfixy = posy+R;
    bfixw = 100; bfixh = 30;
    try {
      infile = new File("podaci.txt");
      scan = new Scanner(infile);
      input();
    }
    catch( FileNotFoundException ex )
    {
      ex.printStackTrace();
      return;
    }
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
      fix(0);
      repaint();
  }
  public void drawtrokut(int ax, int ay, int bx, int by, int cx, int cy) {
    g.drawLine(ax, ay, bx, by);
    g.drawLine(ax,ay,cx,cy);
    g.drawLine(bx,by,cx,cy);
  }
  public void draw1() {
    g.drawOval(posx, posy, 2*R, 2*R);
    g.drawLine(posx+R, posy+R, posx+R, posy+R);
  }
  public boolean mouseDown(Event evt, int x, int y) {
     if(x >= bupx && x < bupx+bupw && y >= bupy && y < bupy+buph)
       setview(5,0);
     else if(x >= bdownx && x < bdownx+bdownw && y >= bdowny && y < bdowny+bdownh)
       setview(-5,0);
     else if(x >= brightx && x < brightx+brightw && y >= brighty && y < brighty+brighth)
       setview(0,5);
     else if(x >= bleftx && x < bleftx+bleftw && y >= blefty && y < blefty+blefth)
       setview(0,-5);
     else if(x >= bdvx && x < bdvx+bdvw && y >= bdvy && y < bdvy+bdvh) {
       defzoom(); defview(); updview();
     }
     else if(x >= bzoominx && x <bzoominx+bzoomw && y >= bzoominy && y < bzoominy+bzoomh)
       zoom(2);
     else if(x >= bzoomoutx && x <bzoomoutx+bzoomw && y >= bzoomouty && y < bzoomouty+bzoomh)
       zoom(-2);
     else if(x >= bfixx && x < bfixx+bfixw && y >= bfixy && y < bfixy+bfixh) {
        viewback(); fix(sel);
     }
     for(int i = 0; i < n; ++i) {
       if(x >= 4*R && x < 4*R+kw && y >= posy+(i-1)*20 && y < posy+i*20) {
         fix(i);
       }
       else if(x >= 4*R-20 && x < 4*R+20 && y >= posy+(i-1)*20 && y < posy+i*20) {
         sel = i; cd = obj[i].getd(); cr = obj[i].getr(); updview(); repaint(); break;
       }
     }
     xx = x - posx - R; yy = y - posy - R;
     repaint();
     for(int i = 0; i < n; ++i) {
       if(!obj[i].visible()) continue;
       if((obj[i].getvx()-xx)*(obj[i].getvx()-xx)
         +(obj[i].getvy()-yy)*(obj[i].getvy()-yy)
         <= clickR*clickR) {
         sel = i; repaint(); break;
       }
     }
     return true;
  }
  public void drawbup() {
    g.setColor(Color.blue);
    g.fillRect(bupx, bupy, bupw, buph);
    g.setColor(Color.red);
    drawtrokut(bupx+bupw/2,bupy+buph/8, bupx, bupy+buph, bupx+bupw, bupy+buph);
  }
  public void drawbdown() {
    g.setColor(Color.blue);
    g.fillRect(bdownx, bdowny,bdownw,bdownh);
    g.setColor(Color.red);
    drawtrokut(bdownx+bdownw/2,bdowny+bdownh-bdownh/8, bdownx, bdowny, bdownx+bdownw, bdowny);
  }
  public void drawbright() {
    g.setColor(Color.green);
    g.fillRect(brightx,brighty,brightw,brighth);
    g.setColor(Color.red);
    drawtrokut(brightx, brighty, brightx, brighty+brighth, brightx+brightw-brightw/8, brighty+brighth/2);
  }
  public void drawbleft() {
    g.setColor(Color.green);
    g.fillRect(bleftx,blefty,bleftw,blefth);
    g.setColor(Color.red);
    drawtrokut(bleftx+bleftw/8, blefty+blefth/2, bleftx+bleftw, blefty, bleftx+bleftw, blefty+blefth);
  }
  public void drawdv() {
    g.setColor(Color.red);
    g.fillRect(bdvx, bdvy, bdvw, bdvh);
  }
  public void drawbzoomin() {
    g.setColor(Color.green);
    g.fillRect(bzoominx,bzoominy,bzoomw,bzoomh);
    g.setColor(Color.black);
    g.fillRect(bzoominx, bzoominy+bzoomh/2-bzoomh/12, bzoomw, bzoomh/6);
  }
  public void drawbzoomout() {
    g.setColor(Color.green);
    g.fillRect(bzoomoutx,bzoomouty,bzoomw,bzoomh);
    g.setColor(Color.black);
    g.fillRect(bzoomoutx, bzoomouty+bzoomh/2-bzoomh/12, bzoomw, bzoomh/6);
    g.fillRect(bzoomoutx+bzoomw/2-bzoomw/12, bzoomouty, bzoomw/6, bzoomh);
  }
  public void drawfix() {
    g.setColor(Color.gray);
    g.fillRect(bfixx, bfixy, bfixw, bfixh);
    g.setFont(font1);
    g.setColor(Color.red);
    g.drawString("Fiksiraj!", bfixx, bfixy+bfixh/2+bfixh/4);
    g.setFont(deffont);
  }
  public void drawgraph() {
   for(int i = 0; i < m; ++i) {
      if(!obj[ graf[i][0] ].visible() || !obj[ graf[i][1] ].visible() ) continue;
      if(graf[i][0] == curr || graf[i][1] == curr) continue;
      g.drawLine((int)Math.round(posx+R+obj[ graf[i][0] ].getvx()),
                   (int)Math.round(posy+R+obj[ graf[i][0] ].getvy()),
		    (int)Math.round(posx+R+obj[ graf[i][1] ].getvx()),
                   (int)Math.round(posy+R+obj[ graf[i][1] ].getvy()) );
    }
  }
  public void drawmap() {
    drawgraph();
    for(int i = 0; i < n; ++i) {
      if(obj[i].visible()) {
        if(i == sel) g.setColor(Color.red);
        g.drawOval((int)Math.round(posx+R+obj[i].getvx()) - obj[i].getsize()/2,
                   (int)Math.round(posy+R+obj[i].getvy()) - obj[i].getsize()/2,
         obj[i].getsize(), obj[i].getsize());
        g.drawString(""+obj[i].getname(), (int)Math.round(posx+R+obj[i].getvx()-5*obj[i].name.length()/2),
                   (int)Math.round(posy+R+obj[i].getvy()-2));
        if(i == sel) g.setColor(Color.black);
      }
    }
  }
  public void paint(Graphics gr) {
    g = gr;
    draw1(); drawbup(); drawbdown(); drawbright(); drawbleft(); drawbzoomin(); drawbzoomout(); drawfix(); drawdv();
    g.setColor(Color.black);
    g.setFont(font1);
    g.drawString("Stajalište:        "+obj[curr].name, posx, 30);
    g.drawString(""+obj[sel].getname(), posx+2*R+20, 40);
    g.drawString("Deklinacija:      "+roundto(obj[sel].getd(), 2), posx+2*R+20, 40+1*25);
    g.drawString("Rektascenzija: "+roundto(obj[sel].getr(), 2), posx+2*R+20, 40+2*25);
    g.drawString("Udaljenost:      "+roundto(obj[sel].getdist(), 2), posx+2*R+20, 40+3*25);
    if(sel != curr && sel != 0) {
      g.drawString("Magnituda (m1): "+roundto(obj[sel].getm1(), 2), posx+2*R+20, 40+4*25);
      if(!equal(obj[sel].getm1(), obj[sel].getm2()))
        g.drawString("Magnituda (m2): "+roundto(obj[sel].getm2(), 2), posx+2*R+20, 40+5*25);
   }
    //ispod
    g.drawString("Deklinacija:      "+roundto(cd, 2) , 0, 20+posy+2*R);
    g.drawString("Rektascenzija: "+ roundto(cr, 2), 0, 20+posy+2*R+20);
    g.drawString("Zoom: "+roundto(Math.toRadians(defalpha)/Math.toRadians(alpha), 5), posx/2, 20+posy+2*R+40);
    for(int i = 0; i < n; ++i) {
      g.drawString(""+obj[i].getname(), 4*R, posy+i*20);
      g.drawRect(4*R, posy+(i-1)*20, kw, 20);
      g.fillRect(4*R-20+1, posy+(i-1)*20+1, 20-2, 20-2);
    }
    g.setFont(deffont);
    drawmap();
  }
}
