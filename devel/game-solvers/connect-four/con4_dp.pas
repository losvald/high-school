program permutacije;
var dp: array[0..7, 0..25] of INT64;
    b: array[0..7] of integer;
    i, j, curr: integer;
begin  {isto se racuna kao i na kolko nacina mozemo rasporedit 25 crnih i 24
       crvene figure na plocu 7x7}
  {b[x] - na koliko nacina mozemo u neki stupac staviti x figura neke boje}
  b[0] := 1; b[1] := 7; b[2] := 21; b[3] := 35;
  b[4] := 35; b[5] := 21; b[6] := 7; b[7] := 1;

  dp[0, 0] := 1;
  for curr := 1 to 7 do
    for i := 0 to 25 do
      for j := 0 to 7 do
        if i >= j then
          dp[curr, i] := dp[curr, i] + dp[curr-1, i-j] * b[j];
  writeln('The number of ways we can insert',
          '24 red i 25 yellow discs into a 7x7 board:');
  writeln(dp[7,24]);  {ili writeln(dp[7, 25]); }

  readln;
end.
