program _bfs;
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
    x, n, m: integer;
    dist, pred: array[1..10000] of integer;
    adj: array[1..100, 1..100] of boolean;
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

procedure bfs(start: integer);
var i, u: integer;
begin
  for i := 1 to n do
  begin
    dist[i] := -1;
    pred[i] := -1;
  end;
  init(q);
  push(q, start);
  dist[start] := 0;
  while not empty(q) do
  begin
    u := front(q);
    for i := 1 to n do
      if adj[u, i] and (dist[i] = -1) then
      begin
        dist[i] := dist[u] + 1;
        pred[i] := u;
        push(q, i);
      end;
    pop(q);
  end;
  for i := 1 to n do
    write(dist[i], ' ');
end;
procedure upis;
var i, a, b: integer;
begin
  read(n); readln(m);
  for i:=1 to m do
  begin
    read(a); readln(b);
    adj[a, b] := true;
    adj[b, a] := true;
  end;
end;
begin
  upis;
  bfs(1);
  readln;
end.
