// Generated by BUCKLESCRIPT VERSION 2.2.3, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Board$ReactTemplate = require("./Board.bs.js");

var component = ReasonReact.reducerComponent("BoardView");

function getClasses(card) {
  var match = card[/* cardType */0];
  var colorClass;
  switch (match) {
    case 0 : 
        colorClass = "red";
        break;
    case 1 : 
        colorClass = "blue";
        break;
    case 2 : 
        colorClass = "neutral";
        break;
    case 3 : 
        colorClass = "assassin";
        break;
    
  }
  return "card " + colorClass;
}

function renderCard(handleClick, card) {
  return React.createElement("div", {
              key: card[/* word */1],
              className: getClasses(card),
              onClick: Curry._1(handleClick, card[/* word */1])
            }, React.createElement("span", undefined, card[/* word */1]));
}

function make(words, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (self) {
      var __x = Belt_Array.concatMany(self[/* state */2][/* board */0]);
      return React.createElement("div", {
                  className: "board-view"
                }, Belt_Array.map(__x, (function (param) {
                        return renderCard((function (word, _) {
                                      return Curry._1(self[/* send */4], /* Click */[word]);
                                    }), param);
                      })));
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[
              /* board */Board$ReactTemplate.make_with_words(words),
              /* mode : View */0
            ];
    });
  newrecord[/* reducer */12] = (function (action, state) {
      var id = action[0];
      var match = state[/* mode */1];
      if (match) {
        if (match[0] === id) {
          return /* Update */Block.__(0, [/* record */[
                      /* board */state[/* board */0],
                      /* mode : View */0
                    ]]);
        } else {
          return /* Update */Block.__(0, [/* record */[
                      /* board */state[/* board */0],
                      /* mode : Editing */[id]
                    ]]);
        }
      } else {
        return /* Update */Block.__(0, [/* record */[
                    /* board */state[/* board */0],
                    /* mode : Editing */[id]
                  ]]);
      }
    });
  return newrecord;
}

exports.component = component;
exports.getClasses = getClasses;
exports.renderCard = renderCard;
exports.make = make;
/* component Not a pure module */
