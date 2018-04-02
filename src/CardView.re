let component = ReasonReact.statelessComponent("CardView");

let getClasses = (card: Board.card) => {
  let baseClass = "card";
  let colorClass =
    switch (card.cardType) {
    | Red => "red"
    | Blue => "blue"
    | Neutral => "neutral"
    | Assassin => "assassin"
    | Hidden => ""
    };
  baseClass ++ " " ++ colorClass;
};

let make = (~handleCycleType, ~handleEditCard, ~card: Board.card, _children) => {
  ...component,
  render: _self =>
    <div
      className=(getClasses(card))
      onClick=(
        e => {
          ReactEventRe.Mouse.preventDefault(e);
          handleCycleType(card.id);
        }
      )>
      <span> (ReasonReact.stringToElement(card.word)) </span>
      <button
        onClick=(
          e => {
            ReactEventRe.Mouse.stopPropagation(e);
            handleEditCard(card.id);
          }
        )
        className="edit">
        (ReasonReact.stringToElement("Edit"))
      </button>
    </div>,
};