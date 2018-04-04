let component = ReasonReact.statelessComponent("CardView");

let make =
    (~handleToggleRevealed, ~handleEditCard, ~card: Board.card, _children) => {
  ...component,
  render: _self =>
    <div
      className=(Board.getClasses(card))
      onClick=(
        e => {
          ReactEventRe.Mouse.preventDefault(e);
          handleToggleRevealed(card.id);
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