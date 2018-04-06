// Generated by BUCKLESCRIPT VERSION 2.2.3, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Board$ReactTemplate = require("./Board.bs.js");
var SocketIO$ReactTemplate = require("./SocketIO.bs.js");
var BoardView$ReactTemplate = require("./BoardView.bs.js");
var CodenamesSocket$ReactTemplate = require("./CodenamesSocket.bs.js");

((window.io = require("socket.io-client")));

var SocketClient = SocketIO$ReactTemplate.Client[/* Make */0](CodenamesSocket$ReactTemplate.Common);

var component = ReasonReact.reducerComponent("App");

function trySendAction(socket, action, data) {
  (( console.log(action, data) ));
  if (socket) {
    return Curry._3(SocketClient[/* emit */0], socket[0], action, data);
  } else {
    return /* () */0;
  }
}

function make(words, _) {
  var newrecord = component.slice();
  newrecord[/* didMount */4] = (function (self) {
      var socket = new io();
      Curry._3(SocketClient[/* on */1], socket, /* UpdateBoard */2, (function (obj) {
              return Curry._1(self[/* send */4], /* UpdateBoard */Block.__(0, [obj]));
            }));
      Curry._3(SocketClient[/* on */1], socket, /* ToggleRevealed */1, (function (id) {
              return Curry._1(self[/* send */4], /* ToggleRevealed */Block.__(3, [id]));
            }));
      Curry._3(SocketClient[/* on */1], socket, /* UpdateCard */0, (function (card) {
              return Curry._1(self[/* send */4], /* UpdateCard */Block.__(1, [card]));
            }));
      self[/* state */2][/* socket */2][0] = /* Some */[socket];
      return /* NoUpdate */0;
    });
  newrecord[/* render */9] = (function (self) {
      return ReasonReact.element(/* None */0, /* None */0, BoardView$ReactTemplate.make(self[/* state */2][/* board */0], self[/* state */2][/* mode */1], (function (id) {
                        trySendAction(self[/* state */2][/* socket */2][0], /* ToggleRevealed */1, id);
                        return Curry._1(self[/* send */4], /* ToggleRevealed */Block.__(3, [id]));
                      }), (function (id) {
                        return Curry._1(self[/* send */4], /* EditCard */Block.__(2, [id]));
                      }), (function (card) {
                        trySendAction(self[/* state */2][/* socket */2][0], /* UpdateCard */0, card);
                        return Curry._1(self[/* send */4], /* UpdateCard */Block.__(1, [card]));
                      }), /* array */[]));
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[
              /* board */Board$ReactTemplate.make_with_words(words),
              /* mode : View */0,
              /* socket */[/* None */0]
            ];
    });
  newrecord[/* reducer */12] = (function (action, state) {
      switch (action.tag | 0) {
        case 0 : 
            return /* Update */Block.__(0, [/* record */[
                        /* board */Board$ReactTemplate.make_with_words(action[0]),
                        /* mode */state[/* mode */1],
                        /* socket */state[/* socket */2]
                      ]]);
        case 1 : 
            var card = action[0];
            return /* Update */Block.__(0, [/* record */[
                        /* board */Board$ReactTemplate.updateCards((function (card_) {
                                if (card_[/* id */0] === card[/* id */0]) {
                                  return Board$ReactTemplate.makeCard(/* Some */[card[/* word */1]], /* Some */[card[/* cardType */3]], /* Some */[card[/* revealed */2]], card[/* id */0]);
                                } else {
                                  return card_;
                                }
                              }), state[/* board */0]),
                        /* mode : View */0,
                        /* socket */state[/* socket */2]
                      ]]);
        case 2 : 
            return /* Update */Block.__(0, [/* record */[
                        /* board */state[/* board */0],
                        /* mode : Editing */[action[0]],
                        /* socket */state[/* socket */2]
                      ]]);
        case 3 : 
            return /* Update */Block.__(0, [/* record */[
                        /* board */Board$ReactTemplate.toggleRevealed(state[/* board */0], action[0]),
                        /* mode */state[/* mode */1],
                        /* socket */state[/* socket */2]
                      ]]);
        
      }
    });
  return newrecord;
}

exports.SocketClient = SocketClient;
exports.component = component;
exports.trySendAction = trySendAction;
exports.make = make;
/*  Not a pure module */
