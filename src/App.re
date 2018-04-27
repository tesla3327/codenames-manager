/* Include sockets */
[%bs.raw "window.io = require(\"socket.io-client\")"];

/* Socket test */
module SocketClient = SocketIO.Client.Make(CodenamesSocket);

type state = {
  board: Board.t,
  mode: State.mode,
  socket: ref(option(SocketClient.t)),
};

type action =
  | UpdateBoard(Board.t)
  | UpdateCard(Board.card)
  | EditCard(string)
  | ToggleRevealed(string);

let component = ReasonReact.reducerComponent("App");

let trySendAction = (type a, socket, action, data: a) =>
  switch (socket) {
  | Some(io) => SocketClient.emit(io, action, data)
  | None => ()
  };

let make = (~words, _children) => {
  ...component,
  initialState: () => {
    board: Board.make_with_words(words),
    mode: View,
    socket: ref(None),
  },
  didMount: self => {
    let socket = SocketClient.create();
    SocketClient.on(socket, CodenamesSocket.UpdateBoard, obj =>
      self.send(UpdateBoard(obj))
    );
    self.state.socket := Some(socket);
    ReasonReact.NoUpdate;
  },
  reducer: (action, state) =>
    switch (action) {
    | UpdateBoard(board) => ReasonReact.Update({...state, board})
    | ToggleRevealed(id) =>
      ReasonReact.Update({
        ...state,
        board: Board.toggleRevealed(state.board, id),
      })
    | EditCard(id) => ReasonReact.Update({...state, mode: Editing(id)})
    | UpdateCard(card) =>
      ReasonReact.Update({
        ...state,
        mode: View,
        board: Board.updateCard(state.board, card),
      })
    },
  render: self =>
    <BoardView
      board=self.state.board
      mode=self.state.mode
      toggleRevealed=(
        id => {
          trySendAction(
            self.state.socket^,
            CodenamesSocket.ToggleRevealed,
            id,
          );
          self.send(ToggleRevealed(id));
        }
      )
      editCard=(id => self.send(EditCard(id)))
      updateCard=(
        card => {
          trySendAction(self.state.socket^, CodenamesSocket.UpdateCard, card);
          self.send(UpdateCard(card));
        }
      )
    />,
};