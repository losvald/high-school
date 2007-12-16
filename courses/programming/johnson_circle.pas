program johnson_profi; {Slozenost: O(n * log n) }
uses crt;
var a: array[0..10000] of integer; {u TurboPascalu zbog memorije smije bit ovolko najvise}
    tree: array[0..20000] of integer; { znaci n < 5000 }
    n, k, offset, len: integer;
function get(x:integer):integer; { O(log n) }
var pos: integer;
begin
  x := x+1;
  pos := 1;
  while pos < 2*offset do
    if x <= tree[2*pos] then
      pos := 2*pos
    else
    begin
      x := x - tree[2*pos];
      pos := 2*pos+1;
    end;
  get := pos div 2 - offset;
end;
procedure erase(pos:integer); { O(log n) }
begin
  pos := get(pos) + offset;
  while pos > 0 do
  begin
    tree[pos] := tree[pos] - 1;
    pos := pos div 2;
  end;
end;
procedure insert(pos:integer); { O(log n) }
begin
  pos := pos + offset;
  tree[pos] := 1;
  pos := pos div 2;
  while pos > 0 do
  begin
    tree[pos] := tree[2*pos] + tree[2*pos+1];
    pos := pos div 2;
  end;
end;
function solve:integer;
var x, pos, i:integer;
begin
  pos := -1;
  while len > 1 do
  begin {pomakni se za k}
    pos := (pos+k) mod len; {ako je k > len onda uzimam samo k mod len}
    erase(pos); {izbrisi tog na kojem jesi }
    len := len - 1;
    pos := (pos+len-1) mod len;  {vrati se za jedan}
  end;
  for i := 0 to n-1 do  {nadji koji nije izbrisan }
    if tree[i+offset] > 0 then
      solve := a[i];
end;
procedure construct; { O(n * log n) }
var i:integer;
begin
  len := n;
  for i := 1 to n do a[i-1] := i;
  offset := 1;
  while offset < n do offset := offset * 2;
  for i:=0 to n-1 do insert(i);
end;
begin
  write('Upisi n (broj elemenata: '); readln(n);
  write('Upisi k (kojeg k-tog krizas): '); readln(k);
  construct;
  writeln('Rjesenje: ', solve);
  readln;
end.
