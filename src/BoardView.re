let component = ReasonReact.statelessComponent("BoardView");

let renderCard =
    (
      ~toggleRevealed,
      ~editCard,
      ~updateCard,
      mode: State.mode,
      card: Board.card,
    ) =>
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

let make = (~board, ~mode, ~toggleRevealed, ~editCard, ~updateCard, _children) => {
  ...component,
  render: _self =>
    <div className="board-view">
      (
        Belt.Array.concatMany(board)
        |> Belt.Array.map(
             _,
             renderCard(~toggleRevealed, ~editCard, ~updateCard, mode),
           )
        |> ReasonReact.arrayToElement
      )
    </div>,
};