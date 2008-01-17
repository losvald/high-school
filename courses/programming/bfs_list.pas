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
     adj_list = array[1..1000] of queue;
var q: queue;
    x, n, m: integer;
    dist, pred: array[1..10000] of integer;
    adj: adj_list;

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
    p: pokaz;
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
    p := adj[u].g;
    while p <> NIL do
    begin
      if  dist[p^.v] = -1 then
      begin
        dist[p^.v] := dist[u] + 1;
        pred[p^.v] := u;
        push(q, p^.v);
      end;
      p := p^.next;
    end;
    pop(q);
  end;
  for i := 1 to n do
    write(dist[i], ' ');

end;
procedure rec(x:integer);
begin
  if pred[x] <> -1 then
    rec(pred[x]);
  writeln('(', x, ')');
end;
procedure upis;
var i, a, b: integer;
begin
  read(n); readln(m);
  for i := 1 to n do init(adj[i]);
  for i:=1 to m do
  begin
    read(a); readln(b);
    push(adj[a], b);
    push(adj[b], a);
  end;
end;
begin
  upis;
  bfs(1);

  writeln;
  rec(12);
  readln;
end.
{
15 12
12 13
13 14
14 15
1 2
2 3
3 4
4 5
5 6
6 12
1 11
11 14
1 4
}
