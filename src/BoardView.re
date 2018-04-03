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
  | CycleType(string);

let component = ReasonReact.reducerComponent("BoardView");

let renderCard = (~cycleType, ~editCard, ~updateCard, mode, card: Board.card) =>
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
               ~cycleType=id => self.send(CycleType(id)),
               ~editCard=id => self.send(EditCard(id)),
               ~updateCard=card => self.send(UpdateCard(card)),
               self.state.mode,
             ),
           )
        |> ReasonReact.arrayToElement
      )
    </div>,
};