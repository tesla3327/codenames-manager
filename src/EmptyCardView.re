let component = ReasonReact.statelessComponent("EmptyCardView");

let make = (~handleEditCard, ~card: Board.card, _children) => {
  ...component,
  render: _self =>
    <div
      className="card empty"
      onClick=(
        e => {
          ReactEventRe.Mouse.preventDefault(e);
          handleEditCard(card.id);
        }
      )
    />,
};