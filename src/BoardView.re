/* Include sockets */
[%bs.raw "window.io = require(\"socket.io-client\")"];

type mode =
  | View
  | Editing(string);

type state = {
  board: Board.t,
  mode,
};

type action =
  | UpdateCard(Board.card)
  | EditCard(string)
  | ToggleRevealed(string);

let component = ReasonReact.reducerComponent("BoardView");

/* Socket test */
module SocketClient = SocketIO.Client.Make(SocketCommon);

let socket = SocketClient.create();

let renderCard =
    (~toggleRevealed, ~editCard, ~updateCard, mode, card: Board.card) =>
  switch (mode) {
  | Editing(id) when id === card.id =>
    <EditCardView handleUpdateCard=updateCard key=card.id card />
  | Editing(_)
  | View =>
    card.word === "" ?
      <EmptyCardView card handleEditCard=editCard key=card.id /> :
      <CardView
        key=card.id
        card
        handleToggleRevealed=toggleRevealed
        handleEditCard=editCard
      />
  };

let make = (~words, _children) => {
  ...component,
  initialState: () => {board: Board.make_with_words(words), mode: View},
  didMount: self => {
    Js.log(self.state.board);
    ReasonReact.NoUpdate;
  },
  reducer: (action, state) =>
    switch (action) {
    | ToggleRevealed(id) =>
      SocketClient.emit(socket, SocketCommon.Message, "Clicked " ++ id);
      ReasonReact.Update({
        ...state,
        board: Board.toggleRevealed(state.board, id),
      });
    | EditCard(id) => ReasonReact.Update({...state, mode: Editing(id)})
    | UpdateCard(card) =>
      ReasonReact.Update({
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
    <div className="board-view">
      (
        Belt.Array.concatMany(self.state.board)
        |> Belt.Array.map(
             _,
             renderCard(
               ~toggleRevealed=id => self.send(ToggleRevealed(id)),
               ~editCard=id => self.send(EditCard(id)),
               ~updateCard=card => self.send(UpdateCard(card)),
               self.state.mode,
             ),
           )
        |> ReasonReact.arrayToElement
      )
    </div>,
};