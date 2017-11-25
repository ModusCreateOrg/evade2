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



function hexify (val, nopadding) {
    // val = new Int8Array([val])[0];
    val &= 0xFF;

    var hex = val.toString(16).toUpperCase();
    return ("00" + hex).slice(-2);
}

function processResult(svgJSON) {
    // console.log(stringify(svgJSON));
    // return;

    var output = '',
        numLines = 0,
        tab = '\t0x',
        EOL = ',\n',
        hexPrefix = '',
        children = svgJSON.myPaths.childs[1].childs,
        attrs  = svgJSON.myPaths.attrs,
        dimensions = [attrs.width, attrs.height],
        widthCenter = dimensions[0] / 2,
        heightCenter = dimensions[1] / 2;

    children.forEach(function(child, index) {
        if (child.name == 'line') {
            // console.log(child);
            numLines++;

            // output += '\n';

            let x1 = child.attrs.x1 - widthCenter,
                y1 = child.attrs.y1 - heightCenter,
                x2 = child.attrs.x2 - widthCenter,
                y2 = child.attrs.y2 - heightCenter;

            output += [
                    (tab + hexify(x1)),
                    (tab + hexify(y1)),
                    (tab + hexify(x2)),
                    (tab + hexify(y2)),
                ].toString() + (index < children.length - 1 ? ',' : '');

             output += [
                    '\t\t// x1:' + Math.round(x1),
                    ' y1:' + Math.round(y1),
                    ' x2:' + Math.round(x2),
                    ' y2:'+ Math.round(y2),
                ].toString();

            output += (index < children.length - 1 ?  EOL : '');
        }

    });



console.log(`
// SVG Graphic source: ${argv.i}
// Number bytes ${(numLines * 4) + 3}
const PROGMEM int8_t ${varName}[] = {
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




