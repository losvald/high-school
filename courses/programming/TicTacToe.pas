program TicTacToe;
uses crt;
const MAX = 3;
var i, tko, gdje, best, curr, turn, pobjednik: integer;
    a: array[0..MAX, 0..MAX] of integer;
procedure print;
var i, j: integer;
begin
  for i:=0 to MAX-1 do
    for j:=0 to MAX-1 do
    begin
      if a[i, j] = 1 then write('O')
      else if a[i, j] = 2 then write('X')
      else write(' ');
      if j < MAX-1 then write('|')
      else writeln;
    end;
end;
function ok(pos: integer):boolean;
var x, y: integer;
begin
  x := pos mod MAX;
  y := pos div MAX;
  ok := (x >= 0) and (x < MAX) and (y >= 0) and (y < MAX) and (a[y, x] = 0);
end;
procedure postavi(pos, tko: integer);
begin
  a[pos div MAX, pos mod MAX] := tko+1;
end;
procedure makni(var pos: integer);
begin
  a[pos div MAX, pos mod MAX] := 0;
end;
function game_over(var pos: integer):integer;
var x, y, i, j, br: integer;
begin
  x := pos mod MAX;
  y := pos div MAX;
  game_over := -1; {-1 znaci da nema pobjednika tj. da je igra jos u tijeku }
  if(a[0, x] = a[1, x]) and (a[1, x] = a[2, x]) then
    game_over := a[0, x]
  else if (a[y, 0] = a[y, 1]) and (a[y, 1] = a[y, 2]) then
    game_over := a[y, 0]
  else if (x+y = MAX-1) and (a[2, 0] = a[1, 1]) and (a[1, 1] = a[0, 2]) then
    game_over := a[2, 0]
  else if (x+MAX-y-1 = MAX-1) and (a[0, 0] = a[1, 1]) and (a[1, 1] = a[2, 2]) then
    game_over := a[0, 0]
  else
  begin
    br := 0;
    for i := 0 to MAX-1 do
      for j := 0 to MAX-1 do
        if a[i, j] > 0 then
          br := br + 1;
    if br = MAX*MAX then
      game_over := 0; {0 znaci da je igra zavrsila nerjeseno }
  end;
end;
function probaj(tko: integer):integer;
var i, winner, r, best:integer;
begin {-1 TKO je izgubio     0 nerjeseno     1 TKO je pobijedio }
  best := -1;  { pretpostavi da si izgubio }
  for i := 0 to MAX*MAX-1 do
  begin
    if ok(i) then
    begin
      postavi(i, tko);
      winner := game_over(i);
      if winner > 0 then r := 1 { ako mozes pobijeti vrati 1 }
      else if winner = 0 then r := 0  { ako je nerjeseno vrati 0}
      else r := probaj(1 - tko);  {ako nije nerjeseno onda probaj dalje rekurzivno}
      makni(i);
      if r > best then best := r;
    end;
  end;
  probaj := -best; { minus je radi toga jer je drugi igrac pa trenutni zeli da ovaj ima sto manje }
end;
begin
  pobjednik := -1;
  turn := 0;
  while pobjednik = -1 do
  begin
    tko := turn mod 2;
    if tko = 0 then
    begin
      writeln('Ti si na potezu');
      repeat
        write('Upisi potez: ');
        readln(gdje);
      until ok(gdje-1);
      gdje := gdje - 1;
    end
    else
    begin
      writeln('Komp je na potezu!');
      best := -1;
      for i := 0 to MAX*MAX-1 do
        if ok(i) then
        begin
          postavi(i, 1);
          pobjednik := game_over(i);
          if pobjednik > 0 then curr := 1
          else if pobjednik = 0 then curr := 0
          else curr := probaj(0);
          makni(i);
          if curr > best then
          begin
            best := curr;
            gdje := i;
          end;
        end;
    end;
    postavi(gdje, tko);
    clrscr;
    print;
    pobjednik := game_over(gdje);
    turn := turn + 1;
  end;
  writeln; writeln;
  if pobjednik = 0 then writeln('Nerjeseno')
  else if pobjednik = 1 then writeln('Tvoja pobjeda!')
  else if pobjednik = 2 then writeln('Kompova pobjeda!');
  readln;
end.

