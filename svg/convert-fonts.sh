yarn

includes="";

for fontFile in `find svg_docs/fontz -type f | sort`; do
    fileName=$(basename $fontFile);

    varName="font_`echo $fileName | awk -F\. '{print $1}'`"
    varName=`echo $varName | sed -e "s/__/_/g"`

    ./convert-path-font.js -i  ${fontFile} -v $varName -h "../evade/img/glyphs/${varName}.h" 


done


for header in `find ../evade/img/glyphs -type f | sort | grep -v DS_Store  `; do
    fileName=$(basename $header);
    echo "#include \"img/glyphs/${fileName}\""


done