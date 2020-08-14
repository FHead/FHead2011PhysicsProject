#!/bin/bash

echo "var JECData ="
echo "{"
for Version in `ls Fragments/*`
do
   cat ${Version}
done
echo "}"
