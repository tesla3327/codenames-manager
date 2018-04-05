open Express;

let port = 3333;

let app = express();

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

let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log @@ "Listening at http://localhost:" ++ string_of_int(3333)
  };

App.listen(app, ~port, ~onListen, ());