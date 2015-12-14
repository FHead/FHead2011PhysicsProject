cat ../BatchResult/* | cut --delim=' ' --field=2- > AllProcessedEvents
grep -v "0 0 0 0 0 0 0 0 0 0" AllProcessedEvents > ProcessedEvents
echo "Number of bad events = `grep '0 0 0 0 0 0 0 0 0 0' AllProcessedEvents | wc -l`/`wc -l AllProcessedEvents | cut --delim=' ' --field=1-1`"
rm AllProcessedEvents






