#!/usr/bin/env node
var segments = require('svg-line-segments');
var linearize = require('svg-linearize');
var loadsvg = require('load-svg');

loadsvg('2017-11-18_19-38-38.svg', function (err, svg) {
    var points = segments(linearize(svg));
    console.log(JSON.stringify(points), null,4);
});
