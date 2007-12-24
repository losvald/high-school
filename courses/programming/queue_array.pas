program _queue2;
type queue = record
               a: array[0..10000] of integer;
               poc: integer;
               kraj: integer;
             end;
var q: queue;
    x: integer;
procedure ispis(var Q: queue);
var i: integer;
begin
  i := Q.poc;
  while i <> Q.kraj do
  begin
    write(Q.a[i], ' ');
    i := (i + 1) mod 10000;
  end;
end;
procedure init(var Q: queue);
begin
  Q.poc := 0;
  Q.kraj := 0;
end;
procedure push(var Q: queue; x: integer);
begin
  Q.a[Q.kraj] := x;
  Q.kraj := (Q.kraj + 1) mod 10000;
end;
procedure pop(var Q: queue);
begin
  Q.poc := (Q.poc + 1) mod 10000;
end;
function front(var Q: queue):integer;
begin
  front := Q.a[Q.poc];
end;
function empty(var Q: queue):boolean;
begin
  empty := (Q.poc = Q.kraj);
end;
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
