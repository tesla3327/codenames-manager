type cardType =
  | Red
  | Blue
  | Neutral
  | Assassin;

type card = {
  id: string,
  word: string,
  revealed: bool,
  cardType,
};

let makeCard = (~word="", ~cardType=Neutral, ~revealed=false, id) => {
  id,
  cardType,
  word,
  revealed,
};

type t = array(array(card));

/* let make = () => Belt.Array.make(5, Belt.Array.make(5, makeCard()); */
/* let getNextCardType = cardType =>
   switch (cardType) {
   | Hidden => Red
   | Red => Blue
   | Blue => Neutral
   | Neutral => Assassin
   | Assassin => Hidden
   }; */
let updateCards = (func, board) =>
  Belt.(Array.map(board, row => Array.map(row, func)));

let toggleRevealed = (board, id) =>
  updateCards(
    card =>
      if (card.id === id) {
        makeCard(
          ~word=card.word,
          ~cardType=card.cardType,
          ~revealed=! card.revealed,
          card.id,
        );
      } else {
        card;
      },
    board,
  );

let getClasses = card => {
  let baseClass = "card";
  let colorClass =
    switch (card.cardType) {
    | Red => "red"
    | Blue => "blue"
    | Neutral => "neutral"
    | Assassin => "assassin"
    };
  baseClass ++ " " ++ colorClass ++ " " ++ (card.revealed ? "" : "hidden");
};

let stringToCardType = str =>
  switch (str) {
  | "red" => Red
  | "blue" => Blue
  | "assassin" => Assassin
  | "neutral"
  | _ => Neutral
  };

let cardTypeToString = cardType =>
  switch (cardType) {
  | Red => "red"
  | Blue => "blue"
  | Assassin => "assassin"
  | Neutral => "neutral"
  };

let getId = (row, col) => string_of_int(row) ++ string_of_int(col);

let make_with_words = words =>
  Belt.Array.(
    map(range(0, 4), row =>
      map(
        range(0, 4),
        col => {
          let index = row * 5 + col;
          let id = getId(row, col);
          if (length(words) > index) {
            makeCard(~word=words[index], id);
          } else {
            makeCard(id);
          };
        },
      )
    )
  );