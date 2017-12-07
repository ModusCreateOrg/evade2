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

var coords = [];

function processResult(svgJSON) {
// console.log(stringify(svgJSON))
// // return;
    const root = svgJSON.myPaths,
          childRoot = root.childs[2],
          group = childRoot;

    var dimensions;

    if (root.attrs.width) {
          dimensions = [root.attrs.width, root.attrs.height]; // Width and height
          // commands = makeAbsolute(parseSVG(group.attrs.d)),
          var widthCenter = dimensions[0] / 2,
                heightCenter = dimensions[1] / 2;
    }
    else if (root.attrs.viewBox) {
        const viewBox = root.attrs.viewBox.split(' ');

        dimensions = [ +viewBox[2], +viewBox[3] ];

        var widthCenter = dimensions[0] / 2,
                heightCenter = dimensions[1] / 2;    
    }

    var output = '',
        numLines = 0,
        tab = '    ',
        EOL = ',\n',
        hexPrefix = '';

    var numLines = 0;


    group.childs.forEach(function(path, pathIndex) {
        // console.log('\n****** NEW GROUP ******\n'.red)
        if (path.attrs.transform) {
            var  transform = path.attrs.transform.replace('translate(', '').replace(')','').split(' '),
                transformX = +transform[0],
                transformY = +transform[1];
        }
        else {
            var transformX = transformY = 0;
        }

        const commands = parseSVG(path.attrs.d);

        if (isNaN(transformY)) {
        transformY = 0;
        }
        
        // console.log(path.attrs.d)
        var mX = 0, // MoveToX
            mY = 0, // MoveToY
            x0 = 0,
            y0 = 0,
            x1 = 0,
            y1 = 0,
            newSegment = true,
            prevCommCode;



        commands.forEach(function(command) {
            var commandCode = command.code.toUpperCase(),
                relative = command.relative;

            // MoveTo -- Creating the path
            if (commandCode == 'M') {
                if (relative) {
                    x0 = mX = (command.x + x1);
                    y1 = mY = (command.y + y1);
                }
                else {
                    x0 = mX = command.x;
                    y0 = mY = command.y;
                }

                if (! newSegment) {
                    x1 = 0;
                    y1 = 0;
                    newSegment = true;   
                }
            }

            // Line To
            if (commandCode == 'L') {
                // if (prevCommCode == 'M' && coords.length > 0 || coords.length > 0) {
             
                // }
                if (prevCommCode != 'M') {
                    x0 = x1;
                    y0 = y1;
                }
                if (relative) {
                    // console.log('RELATIVE'.red, command)
                    x1 = command.x + x0;
                    y1 = command.y + y0;
                }
                else {

                    x1 = command.x;
                    y1 = command.y;
                }
                
            }

            // Quadratic curve 
            // Treat as line above. But use X1, Y1
            if (commandCode == 'Q') {
                x0 = x1;
                y1 = y1;

                if (relative) {
                    x1 = command.x1 + x1;
                    y1 = command.y1 + y1;
                }
                else {
                    x1 = command.x1;
                    y1 = command.y1;
                }
            }

            // Close Path
            if (commandCode == 'Z') {
                x0 = x1;
                y0 = y1;
                x1 = mX;
                y1 = mY;
            }

            if (commandCode == 'V') {
                if (prevCommCode == 'M') {
                    x1 = x0;
                    y1 = command.y;
                }
                else {
                    x0 = x1;
                    y0 = y1;
                    y1 = command.y;
                }
            }


            if (commandCode == 'H') {
                if (prevCommCode == 'M') {
                    y1 = y0;
                    x1 = command.x;
                }
                else {
                    x0 = x1;
                    y0 = y1;
                    x1 = command.x;
                }
            }



            // console.log(`${commandCode}  x=${command.x} y=${command.y}`);
            // console.log('\t' + stringify(command).green);
            // console.log('Coords ' + [x0, y0, x1, y1].toString(', ').yellow + '\n')

            if (commandCode != 'M') {
                // why push a "line" that is the same start and end?
                if (x0 == x1 && y0 == y1) {
                    // console.log('\n*************NEW'.blue);
                    newSegement = true;          
                }
                else {

                    newSegment = false;
                    coords.push([
                        x0 - widthCenter + transformX,
                        y0 - heightCenter + transformY, 
                        x1 - widthCenter + transformX, 
                        y1 - heightCenter + transformY
                    ]);  
                }
            }
            prevCommCode = commandCode;

          
        });

        
        

    });


    numLines += coords.length;

    coords.forEach(function(coord, index) {
        var x = coord[0],
            y = coord[1],
            x0 = coord[2],
            y0 = coord[3];
            
        // var x = coord[0] - widthCenter + transformX;
        //     y = coord[1] - heightCenter + transformY;
        //     x0 = coord[2] - widthCenter + transformX;
        //     y0 = coord[3] - heightCenter + transformY;
      
        // if (argv.d) {
        //     var x = coord[0],// - widthCenter;
        //         y = coord[1],// - heightCenter;
        //         x0 = coord[2],// - widthCenter;
        //         y0 = coord[3];// - heightCenter;
        // }

        output += [
            tab + Math.round(x),
            tab + Math.round(y),
            tab + Math.round(x0),
            tab + Math.round(y0)
         ].toString();
        output += (index < coords.length - 1 ?  EOL : EOL);
    });

    // output += '// EO PATH\n';

    dimensions[0] = Math.round(dimensions[0]);
    dimensions[1] = Math.round(dimensions[1]);

// // console.log(stringify(coords));

// return;
var hName = `${varName.toUpperCase()}_H`;

var finalOut = `
#ifndef ${hName}
#define ${hName}
// SVG Graphic source: ${argv.i}
// Number bytes ${(numLines * 4) + 3}
const PROGMEM BYTE ${varName}[] = {
${tab}${dimensions[0]},    // Width (${dimensions[0]} px)
${tab}${dimensions[1]},    // Height (${dimensions[1]} px)
${tab}${numLines},    // Number of rows of coords (${numLines})
//  x0,     y0,    x1,    y1
${output}
};
#endif
`;

    if (argv.h) {
        fs.writeFileSync(argv.h, finalOut, 'utf8');
        console.log(`Wrote header file to ${argv.h}`.green);
    }


    if (argv.p) {
        console.log(finalOut);
    }

} //



svgson(data, {
    // svgo: true,
    title: 'myFile',
    pathsKey: 'myPaths',
    customAttrs: {
      foo: true
    }
}, processResult);




