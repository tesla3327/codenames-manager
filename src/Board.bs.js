// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");

function makeCard($staropt$star, $staropt$star$1, $staropt$star$2, id) {
  var word = $staropt$star ? $staropt$star[0] : "";
  var cardType = $staropt$star$1 ? $staropt$star$1[0] : /* Neutral */2;
  var revealed = $staropt$star$2 ? $staropt$star$2[0] : false;
  return /* record */[
          /* id */id,
          /* word */word,
          /* revealed */revealed,
          /* cardType */cardType
        ];
}

function updateCards(func, board) {
  return Belt_Array.map(board, (function (row) {
                return Belt_Array.map(row, func);
              }));
}

function toggleRevealed(board, id) {
  return updateCards((function (card) {
                if (card[/* id */0] === id) {
                  return makeCard(/* Some */[card[/* word */1]], /* Some */[card[/* cardType */3]], /* Some */[!card[/* revealed */2]], card[/* id */0]);
                } else {
                  return card;
                }
              }), board);
}

function updateCard(board, card) {
  return updateCards((function (card_) {
                if (card_[/* id */0] === card[/* id */0]) {
                  return makeCard(/* Some */[card[/* word */1]], /* Some */[card[/* cardType */3]], /* Some */[card[/* revealed */2]], card[/* id */0]);
                } else {
                  return card_;
                }
              }), board);
}

function getClasses(card) {
  var match = card[/* cardType */3];
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
  var match$1 = card[/* revealed */2];
  return "card " + (colorClass + (" " + (
              match$1 ? "" : "hidden"
            )));
}

function stringToCardType(str) {
  switch (str) {
    case "assassin" : 
        return /* Assassin */3;
    case "blue" : 
        return /* Blue */1;
    case "neutral" : 
        return /* Neutral */2;
    case "red" : 
        return /* Red */0;
    default:
      return /* Neutral */2;
  }
}

function cardTypeToString(cardType) {
  switch (cardType) {
    case 0 : 
        return "red";
    case 1 : 
        return "blue";
    case 2 : 
        return "neutral";
    case 3 : 
        return "assassin";
    
  }
}

function getId(row, col) {
  return String(row) + String(col);
}

function make_with_words(words) {
  return Belt_Array.map(Belt_Array.range(0, 4), (function (row) {
                return Belt_Array.map(Belt_Array.range(0, 4), (function (col) {
                              var index = Caml_int32.imul(row, 5) + col | 0;
                              var id = getId(row, col);
                              if (words.length > index) {
                                return makeCard(/* Some */[Caml_array.caml_array_get(words, index)], /* None */0, /* None */0, id);
                              } else {
                                return makeCard(/* None */0, /* None */0, /* None */0, id);
                              }
                            }));
              }));
}

exports.makeCard = makeCard;
exports.updateCards = updateCards;
exports.toggleRevealed = toggleRevealed;
exports.updateCard = updateCard;
exports.getClasses = getClasses;
exports.stringToCardType = stringToCardType;
exports.cardTypeToString = cardTypeToString;
exports.getId = getId;
exports.make_with_words = make_with_words;
/* No side effect */
