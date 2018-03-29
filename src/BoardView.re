type mode =
  | View
  | Editing(string);

type state = {
  board: Board.t,
  mode,
};

type action =
  | Click(string);

let component = ReasonReact.reducerComponent("BoardView");

let getClasses = (card: Board.card) => {
  let baseClass = "card";
  let colorClass =
    card.revealed ?
      switch (card.cardType) {
      | Red => "red"
      | Blue => "blue"
      | Neutral => "neutral"
      | Assassin => "assassin"
      } :
      "";
  baseClass ++ " " ++ colorClass;
};

let renderCard = (handleClick, card: Board.card) =>
  <div
    className=(getClasses(card))
    key=card.word
    onClick=(handleClick(card.word))>
    <span> (ReasonReact.stringToElement(card.word)) </span>
  </div>;

let make = (~words, _children) => {
  ...component,
  initialState: () => {board: Board.make_with_words(words), mode: View},
  reducer: (action, _state) =>
    switch (action) {
    | Click(_) => ReasonReact.NoUpdate
    },
  render: self =>
    <div className="board-view">
      (
        Belt.Array.concatMany(self.state.board)
        |> Belt.Array.map(
             _,
             renderCard((word, _e) => self.send(Click(word))),
           )
        |> ReasonReact.arrayToElement
      )
    </div>,
};