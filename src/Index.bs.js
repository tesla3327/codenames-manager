// Generated by BUCKLESCRIPT VERSION 2.2.3, PLEASE EDIT WITH CARE
'use strict';

var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var BoardView$ReactTemplate = require("./BoardView.bs.js");

var words = /* array */[
  "Date",
  "France",
  "Net",
  "Diamond",
  "Pass",
  "Knight",
  "Cross",
  "Tie"
];

ReactDOMRe.renderToElementWithId(ReasonReact.element(/* None */0, /* None */0, BoardView$ReactTemplate.make(words, /* array */[])), "app");

exports.words = words;
/*  Not a pure module */
