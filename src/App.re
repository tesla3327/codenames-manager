/* Include sockets */
[%bs.raw "window.io = require(\"socket.io-client\")"];

/* Socket test */
module SocketClient = SocketIO.Client.Make(CodenamesSocket.Common);

type state = {
  board: Board.t,
  mode: State.mode,
  socket: ref(option(SocketClient.t)),
};

type action =
  | UpdateBoard(array(string))
  | UpdateCard(Board.card)
  | EditCard(string)
  | ToggleRevealed(string);

let component = ReasonReact.reducerComponent("App");

let trySendAction = (type a, socket, action, data: a) => {
  %bs.raw
  {| console.log(action, data) |};
  switch (socket) {
  | Some(io) => SocketClient.emit(io, action, data)
  | None => ()
  };
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
    SocketClient.on(socket, CodenamesSocket.Common.UpdateBoard, obj =>
      self.send(UpdateBoard(obj))
    );
    SocketClient.on(socket, CodenamesSocket.Common.ToggleRevealed, id =>
      self.send(ToggleRevealed(id))
    );
    SocketClient.on(socket, CodenamesSocket.Common.UpdateCard, card =>
      self.send(UpdateCard(card))
    );
    self.state.socket := Some(socket);
    ReasonReact.NoUpdate;
  },
  reducer: (action, state) =>
    switch (action) {
    | UpdateBoard(words) =>
      ReasonReact.Update({...state, board: Board.make_with_words(words)})
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
        board:
          Board.updateCards(
            (card_: Board.card) =>
              if (card_.id === card.id) {
                Board.makeCard(
                  ~word=card.word,
                  ~cardType=card.cardType,
                  ~revealed=card.revealed,
                  card.id,
                );
              } else {
                card_;
              },
            state.board,
          ),
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
            CodenamesSocket.Common.ToggleRevealed,
            id,
          );
          self.send(ToggleRevealed(id));
        }
      )
      editCard=(id => self.send(EditCard(id)))
      updateCard=(
        card => {
          trySendAction(
            self.state.socket^,
            CodenamesSocket.Common.UpdateCard,
            card,
          );
          self.send(UpdateCard(card));
        }
      )
    />,
};