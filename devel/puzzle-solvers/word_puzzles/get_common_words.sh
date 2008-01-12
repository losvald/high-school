curl --header 'Host: coursera.cs.princeton.edu' --header 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8' --header 'Accept-Language: en-US,en;q=0.5' --header 'Content-Type: application/x-www-form-urlencoded' 'http://coursera.cs.princeton.edu/algs4/testing/boggle/dictionary-sowpods.txt' -O -J -L
# convert to lowercase and rename to common_words.txt
tr '[:upper:]' '[:lower:]' < dictionary-sowpods.txt > common_words.txt
rm -f dictionary-sowpods.txt
