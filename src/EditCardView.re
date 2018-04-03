type state = {cardState: Board.card};

type action =
  | ChangeWord(string)
  | ChangeType(Board.cardType);

let component = ReasonReact.reducerComponent("EditCardView");

let make = (~card: Board.card, ~handleUpdateCard, _children) => {
  ...component,
  initialState: () => {cardState: card},
  reducer: (action, state: state) =>
    switch (action) {
    | ChangeWord(word) =>
      ReasonReact.Update({
        cardState: {
          ...state.cardState,
          word,
        },
      })
    | ChangeType(cardType) =>
      ReasonReact.Update({
        cardState: {
          ...state.cardState,
          cardType,
        },
      })
    },
  render: self =>
    <div className="card edit">
      <input
        placeholder="Enter word"
        value=self.state.cardState.word
        onChange=(
          e => {
            let target = e |> ReactEventRe.Form.target;
            let dom = ReactDOMRe.domElementToObj(target);
            self.send(ChangeWord(dom##value));
          }
        )
      />
      <select>
        <option value="red"> (ReasonReact.stringToElement("Red")) </option>
        <option value="blue"> (ReasonReact.stringToElement("Blue")) </option>
        <option value="neutral">
          (ReasonReact.stringToElement("Neutral"))
        </option>
        <option value="assassin">
          (ReasonReact.stringToElement("Assassin"))
        </option>
      </select>
      <button
        _type="submit" onClick=(_e => handleUpdateCard(self.state.cardState))>
        (ReasonReact.stringToElement("Save"))
      </button>
    </div>,
};