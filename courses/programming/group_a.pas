program grupa_a;
uses crt;
type pokaz = ^osoba;
     osoba = record
               prez: string;
               god: integer;
               veza: pokaz;
             end;
     zapis = record
               prez: string;
               god: integer;
             end;
var g: pokaz;
procedure upis;
var pom: pokaz;
    jos: char;
begin
  g := NIL;
  repeat
    new(pom);
    write('Prezime: '); readln(pom^.prez);
    write('God: '); readln(pom^.god);
    pom^.veza := g;
    g := pom;
    write('Ima jos (d/n)'); readln(jos);
  until jos in ['n', 'N'];
end;
procedure ispis;
var p: pokaz;
begin
  p := g;
  while p <> NIL do
  begin
    writeln('Prezime: ', p^.prez, ' God. staza: ', p^.god);
    p := p^.veza;
  end;
end;
procedure prepis;
var f: file of zapis;
    x: zapis;
    p: pokaz;
begin
  assign(f, 'MIROVINA');
  rewrite(f);
  p := g;
  while p <> NIL do
  begin
    x.prez := p^.prez;
    x.god := p^.god;
    if x.god > 32 then
      write(f, x);
    p := p^.veza;
  end;
end;
procedure brisi;
var p, pom: pokaz;
    n, i: integer;
begin
  write('Kojeg zelis izbrisati?'); readln(n);
  p := g;
  if n = 1 then
  begin
    pom := g;
    g := g^.veza;
    dispose(pom);
  end
  else
  begin
    for i := 1 to n-2 do
      p := p^.veza;
    pom := p^.veza;
    p^.veza := pom^.veza;
    dispose(pom);
  end;
end;
procedure trazi;
var p: pokaz;
    prez: string;
    ima: boolean;
begin
  write('Prezime koje trazis?'); readln(prez);
  ima := false;
  p := g;
  while p <> NIL do
  begin
    if p^.prez = prez then
    begin
      writeln('Prezime: ', p^.prez, ' God. staza: ', p^.god);
      ima := true;
    end;
    p := p^.veza;
  end;
  if not ima then writeln('Nije nadjeno to ime!');
end;
begin
  upis;
  ispis;
  prepis;
  brisi;
  ispis;
  trazi;

  readln;
end.
