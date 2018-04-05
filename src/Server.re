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
module SocketServer = SocketIO.Server.Make(SocketCommon);

let io = SocketServer.createWithHttp(http);

SocketServer.onConnect(
  io,
  socket => {
    open SocketServer;
    Js.log("New connection");
    Socket.on(socket, SocketCommon.Message, obj => Js.log(obj));
  },
);

let onListen = () =>
  Js.log @@ "Listening at http://localhost:" ++ string_of_int(3333);

Http.listen(http, port, onListen);