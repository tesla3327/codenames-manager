// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var CardView$ReactTemplate = require("./CardView.bs.js");
var EditCardView$ReactTemplate = require("./EditCardView.bs.js");
var EmptyCardView$ReactTemplate = require("./EmptyCardView.bs.js");

var component = ReasonReact.statelessComponent("BoardView");

function renderCard(toggleRevealed, editCard, updateCard, mode, card) {
  var exit = 0;
  if (mode && mode[0] === card[/* id */0]) {
    return ReasonReact.element(/* Some */[card[/* id */0]], /* None */0, EditCardView$ReactTemplate.make(card, updateCard, /* array */[]));
  } else {
    exit = 1;
  }
  if (exit === 1) {
    var match = card[/* word */1] === "";
    if (match) {
      return ReasonReact.element(/* Some */[card[/* id */0]], /* None */0, EmptyCardView$ReactTemplate.make(editCard, card, /* array */[]));
    } else {
      return ReasonReact.element(/* Some */[card[/* id */0]], /* None */0, CardView$ReactTemplate.make(toggleRevealed, editCard, card, /* array */[]));
    }
  }
  
}

function make(board, mode, toggleRevealed, editCard, updateCard, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              var __x = Belt_Array.concatMany(board);
              return React.createElement("div", {
                          className: "board-view"
                        }, Belt_Array.map(__x, (function (param) {
                                return renderCard(toggleRevealed, editCard, updateCard, mode, param);
                              })));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.renderCard = renderCard;
exports.make = make;
/* component Not a pure module */
