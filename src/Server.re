open Express;

module Http = {
  type http;
  [@bs.module "http"] external make : App.t => http = "Server";
  [@bs.send] external listen : (http, int, unit => unit) => unit = "";
};

let port = 3333;

let app = express();

let http = Http.make(app);

App.get(app, ~path="/hello") @@
Middleware.from((_, _) => Response.sendString("hello!!!"));

let dirname: option(string) = [%bs.node __dirname];

let publicDir =
  switch (dirname) {
  | Some(dirname) => dirname ++ "/../build"
  | None => "./build"
  };

App.use(app) @@
(Static.make(publicDir, Static.defaultOptions()) |> Static.asMiddleware);

/* Setup Sockets */
module SocketServer = SocketIO.Server.Make(CodenamesSocket.Common);

let io = SocketServer.createWithHttp(http);

let words = [|
  "Date",
  "France",
  "Net",
  "Diamond",
  "Pass",
  "Knight",
  "Cross",
  "Tie",
  "Court",
  "Cotton",
  "Point",
  "Card",
  "Duck",
  "Star",
  "Slip",
  "Fighter",
  "Bridge",
  "Band",
  "Hood",
  "Olive",
  "Shop",
  "Match",
  "Ball",
  "Bow",
  "Mercury",
|];

SocketServer.onConnect(
  io,
  socket => {
    open SocketServer;
    Socket.emit(socket, CodenamesSocket.Common.UpdateBoard, words);
    Socket.on(
      socket,
      CodenamesSocket.Common.UpdateCard,
      data => {
        Js.log("Updating card: " ++ data);
        Socket.broadcast(socket, CodenamesSocket.Common.UpdateCard, data);
      },
    );
    Socket.on(
      socket,
      CodenamesSocket.Common.ToggleRevealed,
      id => {
        Js.log("Toggled: " ++ id);
        Socket.broadcast(socket, CodenamesSocket.Common.ToggleRevealed, id);
      },
    );
  },
);

let onListen = () =>
  Js.log @@ "Listening at http://localhost:" ++ string_of_int(3333);

Http.listen(http, port, onListen);