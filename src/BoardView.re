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
    switch (card.cardType) {
    | Red => "red"
    | Blue => "blue"
    | Neutral => "neutral"
    | Assassin => "assassin"
    };
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
  reducer: (action, state) =>
    switch (action) {
    | Click(id) =>
      switch (state.mode) {
      | Editing(prevId) when prevId === id =>
        ReasonReact.Update({...state, mode: View})
      | Editing(_)
      | View => ReasonReact.Update({...state, mode: Editing(id)})
      }
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