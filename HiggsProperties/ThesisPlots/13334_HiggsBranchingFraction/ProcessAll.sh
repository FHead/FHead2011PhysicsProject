FileLineAppend FourFermion.txt FourLepton.txt Four.txt
FileLineAppend TwoBoson.txt TwoFermion.txt Two.txt
FileLineAppend Four.txt Two.txt All.txt

cat All.txt | TextToTree BranchingRatio.root 30 "M:llqq:LLqq:lvqq:vvqq:qqqq:ffff:M2:eeee:eemm:llll:LLLL:evev:evmv:llvv:LLvv:M3:gg:AA:ZA:WW:ZZ:Gamma:M4:bb:tautau:mm:ss:cc:tt"

rm Four.txt Two.txt

