#!/bin/bash

echo "<html>"
echo "   <head>"
echo "      <title>L1 Files</title>"
echo "   </head>"
echo "   <body>"

for i in *pdf
do
   echo "      <a href=\"$i\">$i</a><br />"
done

echo "   </body>"
echo "</html>"
