# ./a.out Forest.root openHLT-JEC.root Output-JEC.root >& EventJEC
# ./a.out Forest.root openHLT-GT.root Output-GT.root >& EventGT
./a.out Forest.root openHLT-Payload.root Output-Payload.root >& EventPayload

./b.out JEC
./b.out GT
./b.out Payload

