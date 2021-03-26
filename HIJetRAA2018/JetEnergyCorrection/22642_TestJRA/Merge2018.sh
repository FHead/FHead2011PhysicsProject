hadd -f /tmp/chenyi/jra10to11.root Output2018/jra_1[01]*.root
hadd -f /tmp/chenyi/jra12to13.root Output2018/jra_1[23]*.root
hadd -f /tmp/chenyi/jra14to15.root Output2018/jra_1[45]*.root
hadd -f /tmp/chenyi/jra16to19.root Output2018/jra_1[6789]*.root
hadd -f /tmp/chenyi/jra2to3.root Output2018/jra_[23]*.root
hadd -f /tmp/chenyi/jra4to5.root Output2018/jra_[45]*.root
hadd -f /tmp/chenyi/jra6to7.root Output2018/jra_[67]*.root
hadd -f /tmp/chenyi/jra8to9.root Output2018/jra_[89]*.root

hadd -f jra2018.root /tmp/chenyi/jra*to*.root
