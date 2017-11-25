#!/usr/bin/env node

const svgson = require('svgson'),
      colors = require('colors'),
      argv = require('minimist')(process.argv.slice(2)),
      varName = argv.v;

// From .svg file
const fs = require('fs');

function stringify(d) {
    return JSON.stringify(d, null, 4);
}

function syntax() {
    console.log(`
Syntax: ./convert-lines.js -i <input_file> -v <output_variable_name> 
`);
}

function error(str) {
    console.log(('Error! ' + str).red);
    syntax();
    process.exit(1);
}

if (! argv.i) {
    error('No input file indicated!');
}

if (! argv.v) {
    error('No output variable name specified!');
}

const data = fs.readFileSync(argv.i, 'utf-8');



function hexify (number, nopadding) {
    let hex = Math.round(+number).toString(16)
    if ( !nopadding )
        hex = `${hex.length < 2 ? 0 : ''}${hex}`
    return hex
}

function processResult(svgJSON) {
    // console.log(stringify(svgJSON));
    // return;
    var varName = argv.i.split('.')[0];

    var output = '',
        numLines = 0,
        tab = '\t0x',
        EOL = ',\n',
        hexPrefix = '',
        children = svgJSON.myPaths.childs[1].childs,
        attrs  = svgJSON.myPaths.attrs,
        dimensions = [attrs.width, attrs.height];

    children.forEach(function(child, index) {
        if (child.name == 'line') {
            // console.log(child);
            numLines++;

            // output += '\n';

            output += [
                    (tab + hexify(child.attrs.x1)),
                    (tab + hexify(child.attrs.y1)),
                    (tab + hexify(child.attrs.x2)),
                    (tab + hexify(child.attrs.y2)),
                ].toString() + (index < children.length - 1 ? ',' : '');

             output += [
                    '\t\t// x1:' + Math.round(child.attrs.x1),
                    ' y1:' + Math.round(child.attrs.y1),
                    ' x2:' + Math.round(child.attrs.x1),
                    ' y2:'+ Math.round(child.attrs.y2),
                ].toString();

            output += (index < children.length - 1 ?  EOL : '');
        }

    });



console.log(`
// SVG Graphic source: ${argv.i}
// Number bytes ${(numLines * 4) + 3}
const PROGMEM uint8_t ${varName}[] = {
${tab}${hexify(dimensions[0])},\t// Width (${dimensions[0]} px)
${tab}${hexify(dimensions[1])},\t// Height (${dimensions[1]} px)
${tab}${hexify(numLines)},\t// Number of rows of coords (${numLines})
${output}
};`);

} //

svgson(data, {
    // svgo: true,
    title: 'myFile',
    pathsKey: 'myPaths',
    customAttrs: {
      foo: true
    }
}, processResult);




