program vj_test1;
uses crt;
type broj = record
             val: integer;
             next: ^broj;
           end;
var g, p: ^broj;
   f: text;
procedure bubble;
var pom: integer;
   gotovo: boolean;
begin
 repeat
   gotovo := true;
   p := g;
   while p^.next <> NIL do
   begin
     if p^.val < p^.next^.val then {dal je vrijednost slijedeceg manja od trenutnog}
     begin  {ako je onda zamijeni sadrzaj trenutnog (p^.val) }
         {sa sadrzajem slijedeceg (p^.next^.val) } {->PROMJENA SADRZAJA}
       pom := p^.val;
       p^.val := p^.next^.val;
       p^.next^.val := pom;
       gotovo := false; {ako je bilo zamjene onda nije gotov Bubble sort}
     end;
     p := p^.next;
   end;
 until gotovo;
end;
procedure prebroji;
var br: integer;
begin
 br := 0;
 p := g;
 while p <> NIL do
 begin
   if (p^.val >= 10) and (p^.val <= 20) then br := br + 1;
   p := p^.next;
 end;
 writeln('Broj brojeva u listi u intervali [10, 20]: ', br);
end;
procedure ispis2;
begin
 writeln('Ispis brojeva u listi manjih od 50:');
 p := g;
 while p <> NIL do
 begin
   if p^.val < 50 then write(p^.val, ' ');
   p := p^.next;
 end;
 writeln;
end;
procedure ispis;
begin
 writeln('Ispis liste:');
 p := g;
 while p <> NIL do
 begin
   write(p^.val, ' ');
   p := p^.next;
 end;
 writeln;
end;
procedure datoteka;
begin
 writeln('Spremanje u datoteku...');
 assign(f, 'dat.txt');
 rewrite(f);
 p := g;
 while p <> NIL do
 begin
   write(f, p^.val, ' ');
   p := p^.next;
 end;
 writeln(f);
 close(f);
end;
procedure insert_end(x:integer); {ubacuje na kraj liste}
var novi: ^broj;
begin
 new(novi); {alociraj memoriju za novi element liste}
 novi^.val := x; {spremi vrijednost koji zelis ubacit}
 p := g;
 if g = NIL then {ako je lista prazna}
 begin
   novi^.next := NIL;
   g := novi;
 end
 else {inace idi na zadnji element list}
 begin
   while p^.next <> NIL do
     p := p^.next;
   novi^.next := NIL; {sad je novi zadnji element pa mu je slijedeci NIL}
   p^.next := novi; {a slijedeci od bivseg zadnjeg je novi}
 end;
end;
procedure insert(x, pos:integer); {ubacuje x na pos-to mjesto}
var novi: ^broj;
   i: integer;
begin
 new(novi); {alociraj memoriju za novi element liste}
 novi^.val := x; {spremi vrijednost koji zelis ubacit}
 p := g;
 if pos = 1 then {ako ubacujemo na prvo mjesto}
 begin
   novi^.next := NIL;
   g := novi;
 end
 else {inace ubaci na mjesto pos}
 begin
   {sad smo na 1. mjestu, a trebamo se jos pomaknuti za pos-1 mjesta da bi dosli}
   {do onog neposredno prije pos-tog, jer nam on treba za preusmjerit vezu na novog}
   for i := 1 to pos-2 do
     p := p^.next;
   novi^.next := p^.next; {sad je slijedeci od novog onaj koji je prije bio na pos}
   p^.next := novi; {a slijedeci od pos-1 je sad novi (jer je on sad na pos) }
 end;
end;
procedure upis_n;
var x, n:integer;
begin
 writeln('Upisi neki broj: ');
 readln(x);
 writeln('Na koje mjesto ga zelis ubaciti');
 readln(n);
 insert(x, n); {ubaci x na n-to mjesto}
end;
procedure upis;
var x:integer;
begin
 g := NIL;
 checkeof := true;
 writeln('Upisuj brojeve (svaki u novi red), upisi EOF za kraj');
 while not EOF do
 begin
   readln(x);
   insert_end(x); {ubaci ucitani broj na kraj liste}
 end;
 readln; {ovo mora bit radi EOF-a}
end;
begin
 clrscr; {samo radi TURBO PASCALA!}
 upis; {A}
 ispis; {B}
 ispis2; {C}
 prebroji; {C}
 upis_n; {D}
 ispis; {D}
 bubble; {E}
 ispis; {E}
 datoteka; {F}

 readln;
end.
