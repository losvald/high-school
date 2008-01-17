program _queue;
type pokaz = ^tip;
     tip = record
             v: integer;
             prev: pokaz;
             next: pokaz;
     end;
     queue = record
               g: pokaz;
               r: pokaz;
             end;
var q: queue;
    x: integer;
procedure ispis(var Q: queue);
var p: pokaz;
begin
  p := q.r;
  while p <> NIL do
  begin
    write(p^.v, ' ');
    p := p^.prev;
  end;
end;
procedure init(var Q: queue);
begin
  Q.g := NIL;
  Q.r := NIL;
end;
procedure push(var Q: queue; x: integer);
var pom: pokaz;
begin
  new(pom);
  pom^.v := x;
  pom^.prev := NIL;
  pom^.next := Q.g;
  if Q.g = NIL then Q.r := pom
  else Q.g^.prev := pom;
  Q.g := pom;
end;
procedure pop(var Q: queue);
var pom: pokaz;
begin
  pom := Q.r;
  if Q.r^.prev <> NIL then Q.r^.prev^.next := NIL
  else Q.g := NIL;
  Q.r := Q.r^.prev;
  dispose(pom);
end;
function front(var Q: queue):integer; begin front := Q.r^.v; end;
function empty(var Q: queue):boolean; begin empty := (Q.g = NIL); end;
begin
  init(q);
  repeat
    readln(x);
    if x > 0 then push(q, x)
    else pop(q);
    ispis(q);
    writeln('Prazan = ', empty(q));
  until false;
  readln;
end.
