for f in `find  svg_docs/enemies_output_from_ai -type f| grep svg`; do

	bn=$(basename $f);
        varName="enemy_`echo $bn | awk -F. '{print $1}' | sed -e "s/-/_/g"`"
	./convert-path-font.js -i $f -v $varName -h out/${varName}.h


done
