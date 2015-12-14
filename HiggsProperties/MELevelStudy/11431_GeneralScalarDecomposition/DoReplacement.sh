cat ReplacedGeneralScalar.txt | tr -d '\n ' | sed "s/1\.0/1/g" | sed "s/0.5/1\/2/g" | sed "s/8192./8192/g" | sed "s/4096./4096/g" > ReplacedGeneralScalarSameLine.txt
