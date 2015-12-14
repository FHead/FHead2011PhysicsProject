echo "\\\\begin{table}"
echo "\\\\centering"
echo "\\\\begin{tabular}{|c|c|}"
echo "   \\hline"
echo "   Sample & Percentage \\\\\\\\"
echo "   \\hline"
cat Result.txt | awk '{print $9,"&",$11,"\\\\"}'
echo "   \\hline"
echo "\\end{tabular}"
echo "\\\\caption{Percentage of events for each sample inside $\\Upsilon$ mass region (8.8-10.8~GeV)."
echo "   Denominator is all events passing \"(A or B or C) and Baseline\" cuts.}"
echo "\\end{table}"


