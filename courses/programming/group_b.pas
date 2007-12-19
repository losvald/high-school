program grupa_b;
uses crt;
type pokaz = ^proizvod;
     proizvod = record
               sifra: string;
               god: integer;
               veza: pokaz;
             end;
     zapis = record
               sifra: string;
               god: integer;
             end;
var g: pokaz;
procedure upis;
var p, pom: pokaz;
    jos: char;
begin
  g := NIL;
  p := NIL;
  repeat
    new(pom);
    write('Sifra: '); readln(pom^.sifra);
    write('God: '); readln(pom^.god);
    pom^.veza := NIL;
    if g = NIL then g := pom
    else p^.veza := pom;
    p := pom;
    write('Ima jos (d/n)'); readln(jos);
  until jos in ['n', 'N'];
end;
procedure ispis;
var p: pokaz;
begin
  p := g;
  while p <> NIL do
  begin
    writeln('Sifra: ', p^.sifra, ' God. proizv.: ', p^.god);
    p := p^.veza;
  end;
  writeln;
end;
procedure prepis;
var f: file of zapis;
    x: zapis;
    p: pokaz;
begin
  assign(f, 'OTPIS');
  rewrite(f);
  p := g;
  while p <> NIL do
  begin
    x.sifra := p^.sifra;
    x.god := p^.god;
    if x.god < 1990 then
      write(f, x);
    p := p^.veza;
  end;
end;
procedure bubble;
var p: pokaz;
    gotovo: boolean;
    pom1: string;
    pom2: integer;
begin
  repeat
    gotovo := true;
    p := g;
    while p^.veza <> NIL do
    begin
      if p^.sifra > p^.veza^.sifra then
      begin
        pom1 := p^.sifra; p^.sifra := p^.veza^.sifra; p^.veza^.sifra := pom1;
        pom2 := p^.god; p^.god := p^.veza^.god; p^.veza^.god := pom2;
        gotovo := false;
      end;
      p := p^.veza;
    end;
  until gotovo;
end;
procedure ubaci;
var p, pom: pokaz;
begin
  new(pom);
  write('Sifra: '); readln(pom^.sifra);
  write('God: '); readln(pom^.god);
  p := g;
  if (g = NIL) or (pom^.sifra < g^.sifra) then
  begin
    pom^.veza := g;
    g := pom;
  end
  else
  begin
    while (p^.veza <> NIL) and (pom^.sifra > p^.veza^.sifra) do
      p := p^.veza;
    pom^.veza := p^.veza;
    p^.veza := pom;
  end;
end;
begin
  upis;
  ispis;
  prepis;
  bubble;
  ispis;
  ubaci;
  ispis;

  readln;
end.
