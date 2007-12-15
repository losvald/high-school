program za_test;
uses crt;
type pokaz = ^zapis;
     zapis = record
       v:integer;
       veza:pokaz;
     end;
var g: pokaz;
procedure ispis;
var p: pokaz;
begin
  p := g;
  while p <> NIL do
  begin
    writeln(p^.v, ' ');
    p := p^.veza;
  end;
end;
procedure bubble;
var p: pokaz;
    gotovo: boolean;
    tmp: integer;
begin
  repeat
    gotovo := true;
    p := g;
    while p^.veza <> NIL do
    begin
      if p^.v < p^.veza^.v then { < silazno, > uzlazno}
      begin
        tmp := p^.v; p^.v := p^.veza^.v; p^.veza^.v := tmp;
        gotovo := false;
      end;
      p := p^.veza;
    end;
  until gotovo;
end;
procedure usortlistu;
var p, pom: pokaz;
begin
  new(pom);
  writeln('Broj: '); readln(pom^.v);
  if pom^.v > g^.v then
  begin
    pom^.veza := g;
    g := pom;
  end
  else
  begin
    p := g;
    while (p^.veza <> NIL) and (pom^.v < p^.veza^.v) do
      p := p^.veza;
    pom^.veza := p^.veza;
    p^.veza := pom;
  end;
end;
procedure upis_kraj; {kad se uvijek ubacuje na kraj}
var p, pom: pokaz;
    jos: char;
begin
  g := NIL;
  repeat
    new(pom);
    write('Broj: '); readln(pom^.v);
    if g = NIL then
    begin
      pom^.veza := g;
      g := pom;
    end
    else
    begin
      p := g;
      while p^.veza <> NIL do
        p := p^.veza;
      pom^.veza := p^.veza;
      p^.veza := pom;
    end;
    writeln('Jos(d/n)?'); readln(jos);
  until jos in ['n', 'N'];
end;
procedure upis_pocetak; {kad se uvijek ubacuje na pocetak}
var pom: pokaz;
    jos: char;
begin
  g := NIL;
  repeat
    new(pom);
    write('Broj: '); readln(pom^.v);
    pom^.veza := g;
    g := pom;
    writeln('Jos(d/n)?'); readln(jos);
  until jos in ['n', 'N'];
end;
begin
  clrscr;
  writeln('Ovo je prba');
  upis_pocetak;
  bubble;
  ispis;
  usortlistu;
  ispis;
  readln;
end.