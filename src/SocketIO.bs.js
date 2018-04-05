// Generated by BUCKLESCRIPT VERSION 2.2.3, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");

var toValidJson = (
function toJson(o) {
  switch (typeof o){
    case "boolean":
    case "number":
    case "string":
      return o;
    case "function":
      throw new Error("Cannot serialize functions");
    case "object":
      if (Array.isArray(o)){
        return [o.hasOwnProperty("tag") ? o.tag : -1, o.map(toJson)];
      }
      throw new Error("Cannot serialize unidentified object [" + o + "].")
  }
}
);

var fromValidJson = (
function fromJson(o) {
  switch (typeof o){
    case "boolean":
    case "number":
    case "string":
      return o;
    case "function":
      throw new Error("Cannot deserialize functions");
    case "object":
      if (Array.isArray(o)){
        var first = o[0]
        if (first == -1){
          return o[1].map(fromJson);
        } else {
          var a = o[1].map(fromJson);
          a.tag = first;
          return a
        }
      }
      throw new Error("Cannot deserialize unidentified object [" + o + "].")
  }
}
);

var Json = /* module */[
  /* toValidJson */toValidJson,
  /* fromValidJson */fromValidJson
];

var Common = /* module */[];

function Make(M) {
  var emit = function (socket, message, obj) {
    socket.emit(Curry._1(M[/* stringify */0], message), Curry._1(toValidJson, obj));
    return /* () */0;
  };
  var on = function (socket, message, func) {
    socket.on(Curry._1(M[/* stringify */0], message), (function (obj) {
            return Curry._1(func, Curry._1(fromValidJson, obj));
          }));
    return /* () */0;
  };
  return /* module */[
          /* emit */emit,
          /* on */on
        ];
}

var Client = /* module */[/* Make */Make];

function Make$1(M) {
  var emit = function (server, t, obj) {
    server.emit(Curry._1(M[/* stringify */0], t), Curry._1(toValidJson, obj));
    return /* () */0;
  };
  var on = function (socket, t, func) {
    socket.on(Curry._1(M[/* stringify */0], t), (function (obj) {
            return Curry._1(func, Curry._1(fromValidJson, obj));
          }));
    return /* () */0;
  };
  var emit$1 = function (socket, t, obj) {
    socket.emit(Curry._1(M[/* stringify */0], t), Curry._1(toValidJson, obj));
    return /* () */0;
  };
  var broadcast = function (socket, str, data) {
    socket.broadcast.emit(Curry._1(M[/* stringify */0], str), Curry._1(toValidJson, data));
    return /* () */0;
  };
  var once = function (socket, t, func) {
    socket.once(Curry._1(M[/* stringify */0], t), (function (obj) {
            return Curry._1(func, Curry._1(fromValidJson, obj));
          }));
    return /* () */0;
  };
  var volatileEmit = function (server, $$event, obj) {
    server.volatile.emit(Curry._1(M[/* stringify */0], $$event), Curry._1(toValidJson, obj));
    return /* () */0;
  };
  var Socket = /* module */[
    /* on */on,
    /* emit */emit$1,
    /* broadcast */broadcast,
    /* once */once,
    /* volatileEmit */volatileEmit
  ];
  var onConnect = function (io, cb) {
    io.on("connection", cb);
    return /* () */0;
  };
  return /* module */[
          /* emit */emit,
          /* Socket */Socket,
          /* onConnect */onConnect
        ];
}

var Server = /* module */[/* Make */Make$1];

exports.Json = Json;
exports.Common = Common;
exports.Client = Client;
exports.Server = Server;
/* toValidJson Not a pure module */
