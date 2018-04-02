type mode =
  | View
  | Editing(string);

type state = {
  board: Board.t,
  mode,
};

type action =
  | EditCard(string)
  | CycleType(string);

let component = ReasonReact.reducerComponent("BoardView");

let renderCard = (~cycleType, ~editCard, mode, card: Board.card) =>
  switch (mode) {
  | Editing(id) when id === card.id => <EditCardView key=card.id card />
  | Editing(_)
  | View =>
    card.word === "" ?
      <EmptyCardView handleEditCard=editCard card key=card.id /> :
      <CardView
        key=card.id
        card
        handleCycleType=cycleType
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
    | CycleType(id) =>
      ReasonReact.Update({
        ...state,
        board: Board.cycleCardType(state.board, id),
      })
    | EditCard(id) => ReasonReact.Update({...state, mode: Editing(id)})
    },
  render: self =>
    <div className="board-view">
      (
        Belt.Array.concatMany(self.state.board)
        |> Belt.Array.map(
             _,
             renderCard(
               ~cycleType=id => self.send(CycleType(id)),
               ~editCard=id => self.send(EditCard(id)),
               self.state.mode,
             ),
           )
        |> ReasonReact.arrayToElement
      )
    </div>,
};