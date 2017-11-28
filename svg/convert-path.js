#!/usr/bin/env node

const svgson = require('svgson'),
      colors = require('colors'),
      {parseSVG, makeAbsolute} = require('svg-path-parser'),
      argv = require('minimist')(process.argv.slice(2)),
      varName = argv.v;

function syntax() {
    console.log(`
Syntax: ./convert-path.js -i <input_file> -v <output_variable_name> 
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

// From .svg file
const fs = require('fs');

function stringify(d) {
    return JSON.stringify(d, null, 4);
}

const data = fs.readFileSync(argv.i, 'utf-8');



function hexify (val, nopadding) {
    // val = new Int8Array([val])[0];
    val &= 0xFF;

    var hex = val.toString(16).toUpperCase();
    return ("00" + hex).slice(-2);
}

function processResult(svgJSON) {
    const root = svgJSON.myPaths,
          target = root.childs[2].childs[0],
          dimensions = root.attrs.viewBox.replace('0 0 ', '').split(' '), // Width and height
          commands = makeAbsolute(parseSVG(target.attrs.d)),
          widthCenter = dimensions[0] / 2,
          heightCenter = dimensions[1] / 2;
    
    var output = '',
        numLines = 0,
        tab = '    ',
        EOL = ',\n',
        hexPrefix = '';

    commands.forEach(function(command, index) {
        if (command.code == 'L') {
            // console.log(child);
            numLines++;

            let { x, y, x0, y0 } = command;
           
            x -= widthCenter;
            y -= heightCenter;
            x0 -= widthCenter;
            y0 -= heightCenter;

            output += [
                tab + Math.round(x),
                tab + Math.round(y),
                tab + Math.round(x0),
                tab + Math.round(y0)
             ].toString();
            output += (index < commands.length - 1 ?  EOL : '');
        }

    });


console.log(`
// SVG Graphic source: ${argv.i}
// Number bytes ${(numLines * 4) + 3}
const PROGMEM BYTE ${varName}[] = {
${tab}${dimensions[0]},    // Width (${dimensions[0]} px)
${tab}${dimensions[1]},    // Height (${dimensions[1]} px)
${tab}${numLines},    // Number of rows of coords (${numLines})
//  x0,     y0,    x1,    y1
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




