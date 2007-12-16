program za_peticu;
uses crt;
type pokaz = ^broj;
     broj = record
              x: integer;
              veza: pokaz;
     end;
var g: pokaz;
    n, k: integer;
procedure construct;
var i:integer;
    p: pokaz;
begin
  g := NIL;
  for i := n downto 1 do
  begin
    new(p);
    p^.x := i;
    p^.veza := g;
    g := p;
  end;
  while p^.veza <> NIL do
    p := p^.veza;
  p^.veza := g; {spoji u krug zadnji s prvim}
end;
function solve:integer;
var i:integer;
    p, pom: pokaz;
    korak, len: integer;
begin
  p := g;
  while p^.veza <> g do
    p := p^.veza;
  len := n;
  while p <> p^.veza do
  begin  {znamo da lista u ovom trenu sadrzi len elemenata pa nema smisla}
     { vrtit se po istom 2 ili vise puta zato MOD}
    korak := (k-1) mod len;  {moze i korak := k-1 al je to sporije ako k > n }
    for i := 1 to korak do
      p := p^.veza;
    pom := p^.veza;
    p^.veza := pom^.veza;
    dispose(pom);
    len := len - 1;
  end;
  solve := p^.x;
end;
begin
  write('Upisi n (broj elemenata): '); readln(n);
  write('Upisi k (kojeg k-tog krizas): '); readln(k);
  construct;
  writeln('Rjesenje: ', solve);
  readln;
end.
