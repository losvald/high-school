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

import java.awt.*;
import java.applet.*;
import java.util.*;

public class Hanoi extends Applet implements Runnable
{
	int N = 100000; int Maxdisk = 16;
	int solmoves[] = new int[N], Nsolmoves;
	int Ndisk = -1; int csolmove; int biraniN = -1;
	int toranj[][] = new int[3][N];
	int totdisk[] = new int[N];
	int MoveDest[][] = {{1,2},{0,2},{0,1}};  //prvo = na koji toranj ako je kup paran s nekog stupca
	int cdisk = -1;
	boolean oknext = false; int moves;
	boolean reset = false, hide = false, toggleNo = false, help = false, about = false, main = false;
	int kx, ky;
	int bx = 20, by = 30, bw = 50, bh = 20;

	int Wstap = 14, Hstap = 400;
	int pozstapx[] =  {200,600,1000};
	int stapy = 20;
	int pocstap = stapy+Hstap;
	int Hdisk = 20;
	int Wval = 12;

	public Graphics g;
	AudioClip mySound;
	Thread runner;
	boolean mouseIn, mic, clicked = false;
	int pogodak = 0;
	int k_x, k_y;
	int r_x, r_y;
	int t_x = 0, t_y = 0;
	float acc;
	int score, sec, n_klika = 0, sec1, sec2;


	public void drawreset() {
		g.setColor(Color.yellow);
		g.fillRect(175, 550, 50, 20);
		g.setColor(Color.black);
		g.drawRect(175, 550, 50, 20);
		g.drawString("Reset", 182, 550+15);

	}
	public void drawnext() {
		g.setColor(Color.yellow);
		g.fillRect(100, 550, 50, 20);
		g.setColor(Color.black);
		g.drawRect(100, 550, 50, 20);
		g.drawString("Next",110, 550+15);
		if(Nsolmoves > 1)
			g.drawString("Solution found in "+Nsolmoves+" moves. Current move "+(csolmove+1)+"/"
					+Nsolmoves+".", 100, 530);
		else  g.drawString("Solution found in "+Nsolmoves+" move. Current move "+(csolmove+1)+"/"
				+Nsolmoves+".", 100, 530);
	}
	public void drawplay() {
		g.setColor(Color.yellow);
		g.fillRect(250, 550, 50, 20);
		g.setColor(Color.black);
		g.drawRect(250, 550, 50, 20);
		g.drawString("Play", 260, 550+15);
	}
	public void drawsolve() {
		g.setColor(Color.yellow);
		g.fillRect(250, 550, 50, 20);
		g.setColor(Color.black);
		g.drawRect(250, 550, 50, 20);
		g.drawString("Solve", 260, 550+15);
	}
	public void drawtoggleNo() {
		g.setColor(Color.yellow);
		g.fillRect(325, 550, 170, 20);
		g.setColor(Color.black);
		g.drawRect(325, 550, 170, 20);
		g.drawString("Show disk Numbers on/off", 335, 550+15);
	}
	public void drawhelp() {
		g.setColor(Color.yellow);
		g.fillRect(520, 550, 50, 20);
		g.setColor(Color.black);
		g.drawRect(520, 550, 50, 20);
		g.drawString("Help", 530, 550+15);
	}
	public void drawabout() {
		g.setColor(Color.yellow);
		g.fillRect(595, 550, 50, 20);
		g.setColor(Color.black);
		g.drawRect(595, 550, 50, 20);
		g.drawString("About", 605, 550+15);
	}
	public void drawmain() {
		g.setColor(Color.yellow);
		g.fillRect(670, 550, 50, 20);
		g.setColor(Color.black);
		g.drawRect(670, 550, 50, 20);
		g.drawString("Main", 680, 550+15);
	}
	public int power(int x, int y) {
		int res = 1;
		for(int i = 0; i < y; ++i) res*=x;
		return res;
	}
	public void init2() {
		totdisk[0] = Ndisk; totdisk[1] = totdisk[2] = 0;
		/*for(int i = 0; i < N; ++i)
          for(int j = 0; j < 3; ++j)
            toranj[j][i] = -1; */
		for(int i = 0; i < totdisk[0]; ++i) toranj[0][i] = Ndisk-i-1;
		csolmove = -1;

		sec1 =  (int) (Calendar.getInstance().getTimeInMillis()/1000);
		moves = 0;
	}
	public boolean Solved() {
		return totdisk[2] == Ndisk;
	}
	public int locate(int x) {
		for(int i = 0; i < 3; i++)
			if(totdisk[i] != 0 && toranj[i][totdisk[i]-1] == x) return i;
		return -1;
	}
	public void move(int x, int dest) {

		if(dest == -1) dest = MoveDest[x][totdisk[x]%2];
		else {
			sec2 = (int)(Calendar.getInstance().getTimeInMillis()/1000);
			++moves;
		}

		int t = toranj[x][totdisk[x]-1];
		toranj[dest][totdisk[dest]++] = t;
		totdisk[x]--;
	}
	public boolean OkMove(int x, int y) {
		if(x == y) return false;
		if(x < 0 || x > 2 || y < 0 || y > 2) return false;
		if(totdisk[x] == 0) return false;
		if(toranj[x][totdisk[x]-1] > toranj[y][totdisk[y]-1]
		                                       && totdisk[y] > 0) return false;
		return true;
	}
	public void ListMoves()  {
		int ind = 1;
		solmoves[0] = 0;
		for(int i = 1; i < Ndisk; ++i) {
			solmoves[ind] = i;
			int j;
			for(j = 0; j < ind; j++)
				solmoves[ind+j+1] = solmoves[j];
			ind += j+1;
		}
		Nsolmoves = ind;
	}
	public void solve() {
		hide = false;
		ListMoves();
		do {
			reset = false; init2(); repaint();
			for(int currsolmove = 0; currsolmove <= Nsolmoves; ++currsolmove) {
				oknext = false;
				for(;!(oknext && Nsolmoves != currsolmove || reset);) {
					if(hide) {
						init2(); repaint();
						return ;
					}
					else if(main) return ;
				}
				move(locate(solmoves[currsolmove]), -1);
				csolmove = currsolmove;
				repaint();
				if(reset) {
					break;
				}
			}
			reset = true;
		} while(!hide && reset);
		init2(); repaint();
	}
	public void startinit(int n) {
		Ndisk = n;
		MoveDest[0][0] = 1; MoveDest[0][1] = 2;
		MoveDest[1][0] = 0; MoveDest[1][1] = 2;
		MoveDest[2][0] = 0; MoveDest[2][1] = 1;
		Nsolmoves = (int) power(2,Ndisk)-1;

		/*totdisk = new int[Ndisk];
	solmoves = new int[Nsolmoves];
	toranj = new int[3][Ndisk];	*/


		reset = false; toggleNo = false;  oknext = false;
		cdisk = -1;

		init2();
	}

	public void drawdisk(int x, int h, int val, boolean toggleNo) {
		int cx, cy;
		cx = pozstapx[x]+Wstap/2-Wval*(val+1);
		cy = pocstap - Hdisk*(h+1);

		g.fillRect(cx, cy, 2*Wval*(val+1), Hdisk);
		g.setColor(Color.blue);
		g.drawRect(cx, cy, 2*Wval*(val+1), Hdisk);
		if(toggleNo) {
			g.drawString(""+(val+1),cx+Wval*(val+1), cy+Hdisk/2+5);
		}

	}

	public void markclicked(int x) {
		g.setColor(Color.magenta);
		drawdisk(x, totdisk[x]-1, toranj[x][totdisk[x]-1], toggleNo);
	}

	public int okklik(int x, int y) {
		for(int i = 0; i < 3; ++i) {
			int gore = pocstap - Hdisk*(totdisk[i]-1+1);
			int dolje = gore-Hdisk;
			int lijevo = pozstapx[i]+Wstap/2-Wval*(toranj[i][totdisk[i]-1]+1);
			int desno = lijevo+2*Wval+(toranj[i][totdisk[i]-1]+1);
			if(x >= lijevo && x < desno && y >= gore && y < dolje) return i;
		}
		return 0;
	}
	public void init()
	{
		try
		{
			mySound=getAudioClip(getDocumentBase(),"gong.au");
		}
		catch (Exception e){}



	}
	public void start()
	{
		if (runner == null)
		{
			runner = new Thread (this);
			runner.start();
		}
	}
//	public void stop()
//	{
//		if (runner != null)
//		{
//			runner.stop();
//			runner = null;
//		}
//	}
	public void run()
	{
		for(;;) {
			hide = true; biraniN = -1;
			repaint();
			main = false;
			for(;biraniN < 0;) ;
			startinit(biraniN);
			repaint();

			while(true)
			{
				if(main) { break ;}
				else if(!hide) {
					solve();
				}
				/*//halt the thread for 1 second here
           try {runner.sleep(1000);}
           catch (Exception e) { }
           sec = today.getSeconds();
           pogodak = 0;
           t_x = r_x; t_y = r_y;
           while( (r_x == t_x) && (r_y == t_y) ) {
            r_x=(int)(Math.random()*230)+1+20;
            r_y=(int)(Math.random()*230)+1+20;
			  }
           repaint();*/
			}
		}
	}
	public boolean mouseDown(Event evt, int x, int y)
	{
		boolean bio = false;

		if(x >= 595 && y >= 550 && x < 595+50 && y < 550+20) {about ^= true; repaint(); return true;}
		else if(x >= 520 && y >= 550 && x < 520+50 && y < 550+20) {help ^= true; repaint(); return true;}
		if(biraniN < 0) {
			if(x >= bx && x < bx+bw && y >= by && y < by+bh*Maxdisk)
				biraniN = (y-by)/bh+1;
		}
		else {
			if(x >= 175 && y >= 550 && x < 175+50 && y < 550+20) {
				reset = true;
				clicked = false;
				if(hide) {
					init2(); //repaint();
				}
				repaint();
			}
			else if(x >= 670 && y >= 550 && x < 670+50 && y < 550+20) {
				main = true;
				clicked = false; about = false; help = false;
				repaint();
				return true;
			}
			else if(x >= 325 && y >= 550 && x < 325+170 && y < 550+20) {toggleNo ^= true; repaint(); }
			else if(!hide) {
				if(x >= 100 && y >= 550 && x < 100+50 && y < 550+20)
					oknext = true;
				else if(x >= 250 && y >= 550 && x < 250+50 && y < 550+20)
					hide = true;
			}
			else {
				if(x >= 250 && y >= 550 && x < 250+50 && y < 550+20) {
					hide = false;
					clicked = false;   //deselect
					repaint();
				}
				else if(!Solved()) {
					for(int i = 0; i < 3; ++i)
						if(x >= pozstapx[i] && x < pozstapx[i]+Wstap && y >= stapy && y < stapy+Hstap)
						{
							if(!clicked) {
								bio = true;
								clicked = true;    //select
								cdisk = i;
							}
							else if(cdisk >= 0) {
								boolean da = true;

								if(cdisk == i) da = false;
								if(totdisk[cdisk] == 0) da = false;
								if(totdisk[i] > 0)
									if(toranj[cdisk][totdisk[cdisk]-1] > toranj[i][totdisk[i]-1])
										da = false;
								if(da) {
									clicked = false;
									move(cdisk, i);
								}

							}
							repaint();
							break;
						}

				}
				if(clicked && !bio) {clicked = false; repaint();}
			}
		}

		return true;
	}
	public boolean mouseEnter(Event evt,int x,int y)
	{
		mouseIn=true;


		return true;
	}

	public boolean mouseExit(Event evt,int x,int y)
	{
		mouseIn=false;
		return true;
	}
	public boolean mouseMove(Event evt, int x, int y)
	{
		return true;
	}
	public void paint(Graphics gr)
	{
		g = gr;
		//ispisuje tornjeve i stalak
		for(int i = 0; i < 3; i++)
			g.fillRect(pozstapx[i],stapy, Wstap, Hstap);
		g.setColor(Color.darkGray);
		g.fillRect(pozstapx[0]-150, stapy+Hstap, pozstapx[2]-pozstapx[0]+2*150+Wstap, stapy);
		drawmain();
		drawhelp(); drawabout();
		if(help) {
			g.setColor(Color.red);
			g.drawString("The goal of this game is to move all the disks"
					+" from the first tower to the last one.", 100, 620);
			g.drawString("You can move only one disk at a time and you can only move it to another"
					+ " tower with no disk on it or with a larger disk on it", 100, 640);
			g.setColor(Color.green);
			g.drawString("To move the disk from one tower to another, first click on the tower"
					+" you want to move the disk from, then on the tower you want to move the"
					+ " disk to.", 100, 660);
		}
		if(about) {
			g.setColor(Color.darkGray);
			g.drawString("TOWER OF HANOI v1.0     by LEO OSVALD", 100, 700);
			g.setColor(Color.blue);
			g.drawString("Please send bug reports and your opinion to <leden.os@gmail.com>", 100, 730);
		}

		if(biraniN < 0) {
			g.setColor(Color.black);
			g.drawString("Choose the number of disks:", 20, 20);
			for(int i = 0; i < Maxdisk; ++i) {
				g.drawRect(bx, by+bh*i, bw, bh);
				g.drawString(""+(i+1), bx+15, by+bh*i+bh/2+5);
			}
			return ;

		}
		if(Solved() && hide) {
			g.setColor(Color.blue);
			g.drawString("Congratulations you have solved the puzzle! Time: "
					+(sec2-sec1)+" sec     Moves: "+moves+"   (best possible = "+Nsolmoves+")", 100, 600);
		}
		drawreset(); drawtoggleNo();
		if(!hide)  {drawnext(); drawplay(); }
		else {drawsolve(); }


		//ispisuje poziciju svih diskova


		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < totdisk[i]; ++j) {
				g.setColor(Color.red);
				drawdisk(i, j, toranj[i][j], toggleNo);

			}
		}
		if(clicked) markclicked(cdisk);

	}


}
